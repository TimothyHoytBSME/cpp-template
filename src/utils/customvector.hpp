#ifndef CUSTOM_VECTOR_HPP
#define CUSTOM_VECTOR_HPP

#include "logging.hpp"
#include <cstddef>
#include <vector>
#include <stdexcept>

template<typename T>
class VECTOR {
public:
    VECTOR() : _vector() {}
    
    explicit VECTOR(size_t count) : _vector(count) {}
    
    VECTOR(size_t count, const T& value) : _vector(count, value) {}
    
    template<typename InputIt>
    VECTOR(InputIt first, InputIt last) : _vector(first, last) {}
    
    VECTOR(std::initializer_list<T> init) : _vector(init) {}
    
    VECTOR(const VECTOR& other) : _vector(other._vector) {}
    VECTOR(const std::vector<T>& stdvec) : _vector(stdvec) {}
    
    VECTOR& operator=(const VECTOR& other) {
        if (this != &other) {
            _vector = other._vector;
        }
        return *this;
    }

    VECTOR& operator=(const std::vector<T>& stdvec) {
        if (static_cast<const std::vector<T>*>(&this->_vector) != &stdvec) {
            _vector = stdvec;
        }
        return *this;
    }
    
    VECTOR(VECTOR&& other) noexcept : _vector(std::move(other._vector)) {}
    VECTOR(std::vector<T>&& stdvec) noexcept : _vector(std::move(stdvec)) {}
    
    VECTOR& operator=(VECTOR&& other) noexcept {
        if (this != &other) {
            _vector = std::move(other._vector);
        }
        return *this;
    }

    VECTOR& operator=(std::vector<T>&& stdvec) noexcept {
        if (this->_vector != &stdvec) {
            _vector = std::move(stdvec);
        }
        return *this;
    }
    
    ~VECTOR() = default;
    
    T& at(size_t index) {
        if (index >= _vector.size()) {
            throw std::out_of_range("VECTOR::at() - Index out of range");
        }
        return _vector[index];
    }
    
    const T& at(size_t index) const {
        if (index >= _vector.size()) {
            throw std::out_of_range("VECTOR::at() - Index out of range");
        }
        return _vector[index];
    }

    T& operator[](size_t index) {
        if (index >= _vector.size()) {
            throw std::out_of_range("VECTOR::[] - Index out of range");
        }
        return _vector[index];
    }
    
    const T& operator[](size_t index) const {
        if (index >= _vector.size()) {
            throw std::out_of_range("VECTOR::[] - Index out of range");
        }
        return _vector[index];
    }
    
    T& front() {
        if (_vector.empty()) {
            throw std::out_of_range("VECTOR::front() - Vector is empty");
        }
        return _vector.front();
    }
    
    const T& front() const {
        if (_vector.empty()) {
            throw std::out_of_range("VECTOR::front() - Vector is empty");
        }
        return _vector.front();
    }
    
    T& back() {
        if (_vector.empty()) {
            throw std::out_of_range("VECTOR::back() - Vector is empty");
        }
        return _vector.back();
    }
    
    const T& back() const {
        if (_vector.empty()) {
            throw std::out_of_range("VECTOR::back() - Vector is empty");
        }
        return _vector.back();
    }
    
    T* data() {
        return _vector.data();
    }
    
    const T* data() const {
        return _vector.data();
    }
    
    size_t size() const {
        return _vector.size();
    }
    
    size_t capacity() const {
        return _vector.capacity();
    }
    
    bool empty() const {
        return _vector.empty();
    }
    
    void push_back(const T& value) {
        _vector.push_back(value);
    }
    
    void push_back(T&& value) {
        _vector.push_back(std::move(value));
    }
    
    template<typename... Args>
    T& emplace_back(Args&&... args) {
        return _vector.emplace_back(std::forward<Args>(args)...);
    }
    
    void pop_back() {
        if (_vector.empty()) {
            throw std::out_of_range("VECTOR::pop_back() - Vector is empty");
        }
        _vector.pop_back();
    }
    
    void clear() {
        _vector.clear();
    }
    
    void reserve(size_t new_capacity) {
        _vector.reserve(new_capacity);
    }
    
    void resize(size_t new_size) {
        _vector.resize(new_size);
    }
    
    void resize(size_t new_size, const T& value) {
        _vector.resize(new_size, value);
    }

    void shrink_to_fit() {
        _vector.shrink_to_fit();
    }
    
    void swap(VECTOR& other) noexcept {
        _vector.swap(other._vector);
    }
    
    typename std::vector<T>::iterator begin() {
        return _vector.begin();
    }
    
    typename std::vector<T>::const_iterator begin() const {
        return _vector.begin();
    }
    
    typename std::vector<T>::const_iterator cbegin() const {
        return _vector.cbegin();
    }
    
    typename std::vector<T>::iterator end() {
        return _vector.end();
    }
    
    typename std::vector<T>::const_iterator end() const {
        return _vector.end();
    }
    
    typename std::vector<T>::const_iterator cend() const {
        return _vector.cend();
    }
    
    typename std::vector<T>::reverse_iterator rbegin() {
        return _vector.rbegin();
    }
    
    typename std::vector<T>::const_reverse_iterator rbegin() const {
        return _vector.rbegin();
    }
    
    typename std::vector<T>::reverse_iterator rend() {
        return _vector.rend();
    }
    
    typename std::vector<T>::const_reverse_iterator rend() const {
        return _vector.rend();
    }
    
    typename std::vector<T>::iterator insert(typename std::vector<T>::const_iterator pos, const T& value) {
        if (pos < _vector.cbegin() || pos > _vector.cend()) {
            throw std::out_of_range("VECTOR::insert() - Invalid iterator");
        }
        return _vector.insert(pos, value);
    }
    
    typename std::vector<T>::iterator insert(typename std::vector<T>::const_iterator pos, T&& value) {
        if (pos < _vector.cbegin() || pos > _vector.cend()) {
            throw std::out_of_range("VECTOR::insert() - Invalid iterator");
        }
        return _vector.insert(pos, std::move(value));
    }

    typename std::vector<T>::iterator insert(typename std::vector<T>::const_iterator pos, size_t count, const T& value) {
        if (pos < _vector.cbegin() || pos > _vector.cend()) {
            throw std::out_of_range("VECTOR::insert() - Invalid iterator");
        }
        return _vector.insert(pos, count, value);
    }

    template<typename InputIt>
    typename std::vector<T>::iterator insert(typename std::vector<T>::const_iterator pos, InputIt first, InputIt last) {
        if (pos < _vector.cbegin() || pos > _vector.cend()) {
            throw std::out_of_range("VECTOR::insert() - Invalid iterator");
        }
        return _vector.insert(pos, first, last);
    }

    typename std::vector<T>::iterator insert(typename std::vector<T>::const_iterator pos, std::initializer_list<T> ilist) {
        if (pos < _vector.cbegin() || pos > _vector.cend()) {
            throw std::out_of_range("VECTOR::insert() - Invalid iterator");
        }
        return _vector.insert(pos, ilist);
    }
    
    typename std::vector<T>::iterator erase(typename std::vector<T>::const_iterator pos) {
        if (pos < _vector.cbegin() || pos >= _vector.cend()) {
            throw std::out_of_range("VECTOR::erase() - Invalid iterator");
        }
        return _vector.erase(pos);
    }
    
    typename std::vector<T>::iterator erase(typename std::vector<T>::const_iterator first, typename std::vector<T>::const_iterator last) {
        if (first < _vector.cbegin() || last > _vector.cend() || first > last) {
            throw std::out_of_range("VECTOR::erase() - Invalid iterator range");
        }
        return _vector.erase(first, last);
    }
    
    bool operator==(const VECTOR& other) const {
        return _vector == other._vector;
    }
    
    bool operator!=(const VECTOR& other) const {
        return _vector != other._vector;
    }
    
    bool operator<(const VECTOR& other) const {
        return _vector < other._vector;
    }
    
    bool operator<=(const VECTOR& other) const {
        return _vector <= other._vector;
    }
    
    bool operator>(const VECTOR& other) const {
        return _vector > other._vector;
    }
    
    bool operator>=(const VECTOR& other) const {
        return _vector >= other._vector;
    }

    bool operator==(const std::vector<T>& stdvec) const {
        return _vector == stdvec;
    }
    
    bool operator!=(const std::vector<T>& stdvec) const {
        return _vector != stdvec;
    }
    
    bool operator<(const std::vector<T>& stdvec) const {
        return _vector < stdvec;
    }
    
    bool operator<=(const std::vector<T>& stdvec) const {
        return _vector <= stdvec;
    }
    
    bool operator>(const std::vector<T>& stdvec) const {
        return _vector > stdvec;
    }
    
    bool operator>=(const std::vector<T>& stdvec) const {
        return _vector >= stdvec;
    }
    
    std::vector<T>& get_vector() {
        return _vector;
    }
    
    const std::vector<T>& get_vector() const {
        return _vector;
    }

private:
    std::vector<T> _vector;
};


inline void vectorTest(){
    bool allgood = true;
    
    errl("\n========== VECTOR CLASS TEST SUITE ==========\n");
    
    errl("Test 1: Construction");
    VECTOR<int> v1;
    allgood = allgood && (v1.size()==0);
    errl("  Default constructor: size ", allgood? "OK" : "ERROR");
    
    VECTOR<int> v2(5);
    allgood = allgood && (v2.size()==5);
    errl("  Size constructor: size ", allgood? "OK" : "ERROR");
    
    VECTOR<int> v3(3, 42);
    allgood = allgood && (v3.size()==3);
    errl("  Fill constructor: size ", allgood? "OK" : "ERROR");
    errl("  Fill vals: ", v3[0], ", ", v3[1], ", ", v3[2]);
    
    VECTOR<int> v4 = {1, 2, 3, 4, 5};
    allgood = allgood && (v4.size()==5);
    errl("  Initializer List constructor: size ", allgood? "OK" : "ERROR");
    errl("  Initializer List vals: ", v4[0], ", ", v4[1], ", ", v4[2], ", ", v4[3], ", ", v4[4]);
    
    errl("\nTest 2: Element Access for {1,2,3,4,5}");
    allgood = allgood && v4.at(0) == 1 && v4.at(2) == 3 && v4.at(4) == 5;
    errl(allgood? "  at() OK" : "  at() ERROR");
    
    allgood = allgood && v4.front() == 1 && v4.back() == 5;
    errl(allgood? "  front()/back() OK" : " front()/back() ERROR");
    
    try {
        v4.at(10);
        errl("  ERROR: Should have thrown exception!");
        allgood = false;
    } catch (const std::out_of_range& e) {
        errl("  OK, Caught expected exception: ", e.what());
    }
    
    try {
        v4[10];
        errl("  ERROR: Should have thrown exception!");
        allgood = false;
    } catch (const std::out_of_range& e) {
        errl("  OK, Caught expected exception: ", e.what());
    }
    errl();
    
    errl("Test 3: Modifiers (push_back/pop_back)");
    VECTOR<int> v5;
    v5.push_back(10);
    v5.push_back(20);
    v5.push_back(30);
    errl("  After push_back of 10, 20, 30 :");
    allgood = allgood && v5.size() == 3;
    errl("  size ", allgood? "OK" : "ERROR");
    allgood = allgood && v5[0] == 10 && v5[1] == 20 && v5[2] == 30;
    errl("  vals ", allgood? "OK" : "ERROR");
    v5.pop_back();
    v5.pop_back();
    v5.pop_back();
    allgood = allgood && v5.size() == 0;
    errl("  After pop_back() X 3: size ", allgood? "OK" : "ERROR");

    try {
        v5.pop_back();
        errl("  ERROR: Should have thrown exception!");
        allgood = false;
    } catch (const std::out_of_range& e) {
        errl("  Caught expected exception: ", e.what());
    }
    errl();
    
    errl("Test 4: Modifiers (emplace_back)");
    VECTOR<int> v6;
    v6.emplace_back(100);
    v6.emplace_back(200);
    errl("  After emplace_back of 100, 200 :");
    allgood = allgood && v6.size() == 2;
    errl("  size ", allgood? "OK" : "ERROR");
    allgood = allgood && v6[0] == 100 && v6[1] == 200;
    errl("  vals ", allgood? "OK" : "ERROR")    ;


    //todo: continue the allgood pattern from here, then final report

    errl("\nTest 5: Capacity Operations");
    VECTOR<int> v7 = {1, 2, 3};
    errl("  Initial: size=", v7.size(), ", capacity=", v7.capacity());
    v7.reserve(20);
    errl("  After reserve(20): size=", v7.size(), ", capacity=", v7.capacity());
    v7.resize(5, 99);
    errl("  After resize(5, 99): size=", v7.size(), ", values=[", v7[0], ", ", v7[1], ", ", v7[2], ", ", v7[3], ", ", v7[4], "]");
    v7.shrink_to_fit();
    errl("  After shrink_to_fit(): capacity=", v7.capacity(), "\n");
    
    errl("Test 6: Insert Operations");
    VECTOR<int> v8 = {1, 2, 5, 6};
    v8.insert(v8.begin() + 2, 3);
    errl("  After insert(pos+2, 3): [", v8[0], ", ", v8[1], ", ", v8[2], ", ", v8[3], ", ", v8[4], "]");
    
    VECTOR<int> v9 = {1, 2, 6};
    v9.insert(v9.begin() + 2, 2, 5);
    errl("  After insert(pos+2, 2, 5): [", v9[0], ", ", v9[1], ", ", v9[2], ", ", v9[3], ", ", v9[4], "]");
    
    VECTOR<int> v10 = {1, 2, 6};
    VECTOR<int> src = {3, 4, 5};
    v10.insert(v10.begin() + 2, src.begin(), src.end());
    errl("  After insert range: [", v10[0], ", ", v10[1], ", ", v10[2], ", ", v10[3], ", ", v10[4], ", ", v10[5], "]");
    
    VECTOR<int> v11 = {1, 2, 6};
    v11.insert(v11.begin() + 2, {3, 4, 5});
    errl("  After insert({3,4,5}): [", v11[0], ", ", v11[1], ", ", v11[2], ", ", v11[3], ", ", v11[4], ", ", v11[5], "]\n");
    
    errl("Test 7: Erase Operations");
    VECTOR<int> v12 = {1, 2, 3, 4, 5};
    v12.erase(v12.begin() + 2);
    errl("  After erase(pos+2): [", v12[0], ", ", v12[1], ", ", v12[2], ", ", v12[3], "]");
    
    VECTOR<int> v13 = {1, 2, 3, 4, 5};
    v13.erase(v13.begin() + 1, v13.begin() + 4);
    errl("  After erase(pos+1, pos+4): [", v13[0], ", ", v13[1], "]\n");
    
    errl("Test 8: Copy Operations");
    VECTOR<int> v14 = {1, 2, 3};
    VECTOR<int> v15 = v14;
    errl("  Copy constructor: v15=[", v15[0], ", ", v15[1], ", ", v15[2], "]");
    v15[0] = 99;
    errl("  Modified (v15[0]=99): ", v15[0], ", v14[0]=", v14[0], " (independent copies)");
    
    VECTOR<int> v16;
    v16 = v14;
    errl("  Copy assignment: v16=[", v16[0], ", ", v16[1], ", ", v16[2], "]\n");
    
    errl("Test 9: Move Operations");
    VECTOR<int> v17 = {10, 20, 30};
    VECTOR<int> v18 = std::move(v17);
    errl("  Move constructor: v18=[", v18[0], ", ", v18[1], ", ", v18[2], "], v17.size()=", v17.size());
    
    VECTOR<int> v19;
    v19 = std::move(v18);
    errl("  Move assignment: v19=[", v19[0], ", ", v19[1], ", ", v19[2], "], v18.size()=", v18.size());
    
    errl("Test 10: std::vector Compatibility");
    std::vector<int> stdv = {7, 8, 9};
    VECTOR<int> v20(stdv);
    errl("  From std::vector: v20=[", v20[0], ", ", v20[1], ", ", v20[2], "]");
    
    VECTOR<int> v21 = {4, 5, 6};
    v21 = stdv;
    errl("  Assign std::vector: v21=[", v21[0], ", ", v21[1], ", ", v21[2], "]");
    
    VECTOR<int> v22 = {11, 12, 13};
    std::vector<int> stdv2 = std::move(v22.get_vector());
    errl("  get_vector() and move: stdv2 size=", stdv2.size(), "\n");
    
    errl("Test 11: Iterator Operations");
    VECTOR<int> v23 = {5, 10, 15, 20, 25};
    err("  Forward iteration: ");
    for (auto it = v23.begin(); it != v23.end(); ++it) {
        err(*it);
        if(it != v23.end()-1){
            err(", ");
        }
    }
    errl();
    err("  Reverse iteration: ");
    for (auto it = v23.rbegin(); it != v23.rend(); ++it) {
        err(*it);
        if(it != v23.rend() + 1){
            err(", ");
        }
    }
    errl("\n");
    
    errl("Test 12: Comparison Operators");
    VECTOR<int> v24 = {1, 2, 3};
    VECTOR<int> v25 = {1, 2, 3};
    VECTOR<int> v26 = {1, 2, 4};
    errl("  v24 == v25: ", (v24 == v25 ? "true" : "false"));
    errl("  v24 != v26: ", (v24 != v26 ? "true" : "false"));
    errl("  v24 < v26: ", (v24 < v26 ? "true" : "false"));
    
    std::vector<int> stdv3 = {1, 2, 3};
    errl("  v24 == stdv3: ", (v24 == stdv3 ? "true" : "false"), "\n");
    
    errl("Test 13: Clear and Empty");
    VECTOR<int> v27 = {1, 2, 3, 4, 5};
    errl("  Before clear(): empty=", (v27.empty() ? "true" : "false"), ", size=", v27.size());
    v27.clear();
    errl("  After clear(): empty=", (v27.empty() ? "true" : "false"), ", size=", v27.size());
    
    try {
        errl("  Testing front() on empty vector...");
        v27.front();
        errl("  ERROR: Should have thrown exception!");
    } catch (const std::out_of_range& e) {
        errl("  Caught expected exception: ", e.what());
    }
    errl();
    
    errl("Test 14: Swap Operation");
    VECTOR<int> v28 = {1, 2, 3};
    VECTOR<int> v29 = {7, 8, 9, 10};
    errl("  Before swap: v28=[", v28[0], ", ", v28[1], ", ", v28[2], "], v29=[", v29[0], ", ", v29[1], ", ", v29[2], ", ", v29[3], "]");
    v28.swap(v29);
    errl("  After swap: v28=[", v28[0], ", ", v28[1], ", ", v28[2], ", ", v28[3], "], v29=[", v29[0], ", ", v29[1], ", ", v29[2], "]\n");
    
    errl("Test 15: Data Pointer Access");
    VECTOR<int> v30 = {100, 200, 300};
    int* ptr = v30.data();
    errl("  data() pointer: [", ptr[0], ", ", ptr[1], ", ", ptr[2], "]");
    
    errl("\n========== VECTOR CLASS TEST SUITE COMPLETE ==========\n");
}

#endif // end of file