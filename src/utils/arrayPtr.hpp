#ifndef ARRAYPTR_HPP
#define ARRAYPTR_HPP

#include "logging.hpp"
#include <cstddef>
#include <stdexcept>
#include "baseTypes.hpp"
#include <array>

// Gives a safe interface for an existing standard array
// requires external array to remain valid.
template<typename T>
class ARRAYPTR {
    public:
        ARRAYPTR() noexcept = delete;
        ARRAYPTR(ARRAYPTR&& other) noexcept = delete;

        ARRAYPTR(const ARRAYPTR& other) noexcept
            : _externalptr(other._externalptr), _count(other._count)
        {}

        template<size_t N>
        ARRAYPTR(T (&arr)[N]) noexcept
            : _externalptr(arr), _count(N)
        {}

        template <size_t N>
        ARRAYPTR(std::array<T, N>& arr)
            : _externalptr(arr.data()), _count(N)
        {
            if (N == 0) {
                throw std::invalid_argument("ARRAYPTR std::array constructor called with size 0!");
            }
        }

        ARRAYPTR& operator=(ARRAYPTR&& other) noexcept = delete;

        ARRAYPTR& operator=(const ARRAYPTR& other){
            if (this == &other) return *this;
            if(other._externalptr == nullptr){
                throw std::invalid_argument("ARRAYPTR assignment called with nullptr!");
            }
            _externalptr = other._externalptr;
            _count = other._count;
            return *this;
        }

        template <size_t N>
        ARRAYPTR& operator=(T (&arr)[N]) noexcept {
            _externalptr = arr;
            _count = N;
            return *this;
        }

        template <size_t N>
        ARRAYPTR& operator=(std::array<T, N>& arr) {
            if (N == 0) {
                throw std::invalid_argument("ARRAYPTR assignment called with size 0!");
            }
            T* ptr = const_cast<T*>(arr.data());
            _externalptr = ptr;
            _count = N;
            return *this;
        }
        
        T& operator[](size_t index) {
            if(index >= _count){
                throw std::out_of_range("ARRAYPTR::[] index OOB!");
            }
            return _externalptr[index];
        }

        const T& operator[](size_t index) const {
            if(index >= _count){
                throw std::out_of_range("ARRAYPTR::[] index OOB!");
            }
            return _externalptr[index];
        }

        ~ARRAYPTR() = default;

        T& at(size_t index) {
            if (index >= _count) {
                throw std::out_of_range("ARRAYPTR::at() index OOB!");
            }
            return _externalptr[index];
        }

        const T& at(size_t index) const {
            if (index >= _count) {
                throw std::out_of_range("ARRAYPTR::at() index OOB!");
            }
            return _externalptr[index];
        }
        
        T& front() {
            if (_externalptr == nullptr) {
                throw std::out_of_range("ARRAYPTR::front() called on empty array");
            }
            return _externalptr[0];
        }

        const T& front() const {
            if (_externalptr == nullptr) {
                throw std::out_of_range("ARRAYPTR::front() called on empty array");
            }
            return _externalptr[0];
        }

        T& back() {
            if (_externalptr == nullptr) {
                throw std::out_of_range("ARRAYPTR::back() called on empty array");
            }
            return _externalptr[_count - 1];
        }

        const T& back() const {
            if (_externalptr == nullptr) {
                throw std::out_of_range("ARRAYPTR::back() called on empty array");
            }
            return _externalptr[_count - 1];
        }
        
        T* getPointer() noexcept { return _externalptr; }
        const T* getPointer() const noexcept { return _externalptr; }
        T* begin() noexcept { return _externalptr; }
        const T* begin() const noexcept { return _externalptr; }
        T* end() noexcept { return _externalptr + _count; }
        const T* end() const noexcept { return _externalptr + _count; }
        const T* cbegin() const noexcept { return _externalptr; }
        const T* cend() const noexcept { return _externalptr + _count; }

        size_t size() const noexcept { return _count; }

    private:
        T* _externalptr = nullptr;
        size_t _count = 0;
};

inline void arrayPtrTest() {
    errl("\n========== ARRAYPTR CLASS TEST SUITE ==========\n");

    errl("C-array tests");
    int a1[] = {1, 2, 3};
    ARRAYPTR<int> p1(a1);     
    if (p1.size() != 3) errl("FAIL: p1.size() != 3");
    else errl("PASS: p1.size() == 3");

    if (p1[0] != 1) errl("FAIL: p1[0] != 1"); else errl("PASS: p1[0] == 1");
    p1[1] = 20;
    if (a1[1] != 20) errl("FAIL: mutation via p1 didn't propagate"); else errl("PASS: mutation via p1 propagated");

    try {
        p1.at(3);
        errl("FAIL: p1.at(3) did not throw");
    } catch (const std::out_of_range& e) {
        errl("PASS: p1.at(3) threw: ", e.what());
    } catch (...) {
        errl("FAIL: p1.at(3) threw unexpected exception");
    }

    try {
        volatile int x = p1[3]; (void)x;
        errl("FAIL: p1[3] did not throw");
    } catch (const std::out_of_range& e) {
        errl("PASS: p1[3] threw: ", e.what());
    } catch (...) {
        errl("FAIL: p1[3] threw unexpected exception");
    }

    int sum = 0;
    for (auto it = p1.begin(); it != p1.end(); ++it) sum += *it;
    if (sum != (a1[0] + a1[1] + a1[2])) errl("FAIL: iteration sum mismatch");
    else errl("PASS: iteration OK");

    ARRAYPTR<int> p1copy = p1;
    p1copy[0] = 100;
    if (a1[0] != 100) errl("FAIL: copy ctor did not share underlying array");
    else errl("PASS: copy ctor shares underlying array");

    int b1[] = {7, 8, 9, 10};
    p1 = b1; 
    if (p1.size() != 4) errl("FAIL: p1.size() after rebind != 4");
    else errl("PASS: p1.size() after rebind == 4");
    if (p1[2] != 9) errl("FAIL: p1[2] != 9 after rebind"); else errl("PASS: p1[2] == 9 after rebind");

    errl("std::array tests");
    std::array<int, 3> sa = {4, 5, 6};
    ARRAYPTR<int> ps(sa);
    if (ps.size() != 3) errl("FAIL: ps.size() != 3"); else errl("PASS: ps.size() == 3");
    ps[0] = 40;
    if (sa[0] != 40) errl("FAIL: mutation via ps didn't propagate"); else errl("PASS: mutation via ps propagated");

    p1 = sa; 
    if (p1.size() != 3) errl("FAIL: p1.size() after std::array assign != 3"); else errl("PASS: p1.size() after std::array assign == 3");

    ARRAYPTR<int> p2 = ps;
    p2[1] = 500;
    if (sa[1] != 500) errl("FAIL: copy-assignment did not share underlying std::array"); else errl("PASS: copy-assignment shares underlying std::array");

    if (p1.front() != sa.front()) errl("FAIL: front() mismatch"); else errl("PASS: front() OK");
    if (p1.back() != sa.back()) errl("FAIL: back() mismatch"); else errl("PASS: back() OK");

    const ARRAYPTR<int> constView = p1;
    const int* raw = constView.getPointer();
    if (raw == nullptr) errl("FAIL: constView.getPointer() returned nullptr");
    else errl("PASS: constView.getPointer() non-null");

    int csum = 0;
    for (auto it = constView.begin(); it != constView.end(); ++it) csum += *it;
    if (csum == 0) errl("WARN: constView iteration produced sum 0 (possible valid data)");
    else errl("PASS: constView iteration OK (sum=", csum, ")");

    errl("Compound type (testType1) tests");
    testType1 tarr[] = {{1,2},{3,4},{5,6}};
    ARRAYPTR<testType1> tp(tarr);
    tp[1].a = 77;
    if (tarr[1].a != 77) errl("FAIL: compound type mutation via ARRAYPTR didn't propagate");
    else errl("PASS: compound type mutation propagated");

    errl("\n========== ARRAYPTR CLASS TEST SUITE COMPLETE ==========\n");

}

#endif // end of file