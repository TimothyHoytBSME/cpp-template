
#ifndef  ARRAYPTR_HPP
#define ARRAYPTR_HPP

#include "logging.hpp"
#include <typeindex>
#include "baseTypes.hpp"


// This is a non-templated class used to access a standard array with safety
// todo: finish
class ARRAYPTR {
public:
    void* data = nullptr;
    size_t count = 0;
    std::type_index typeindex{typeid(void)};

    ARRAYPTR() noexcept = default;

    // initializer for a mutable C-array
    template<typename T>
    void init(T* ptr, size_t N) noexcept {
        if(init<T>(N)){
            data = static_cast<void*>(ptr);
        }
    }

    // initializer for a const C-array (stores as non-const pointer; be careful)
    template<typename T>
    void init(const T* ptr, size_t N) noexcept {
        if(init<T>(N)){
            data = const_cast<T*>(ptr);
        }
    }

    ARRAYPTR(const ARRAYPTR&) noexcept = delete;
    ARRAYPTR& operator=(const ARRAYPTR&) noexcept = delete;
    ARRAYPTR(ARRAYPTR&&) noexcept = delete;
    ARRAYPTR& operator=(ARRAYPTR&&) noexcept = delete;

    template<typename T>
    T* getPointer() const {
        if (!initialized) {
            errl("ARRAYPTR not initialized; getPointer() returned nullptr.");
            return nullptr;
        }
        if (typeid(T) == typeindex) {
            return static_cast<T*>(data);
        } else {
            errl("INCORRECT TYPE '", typeid(T).name(), "' USED!");
            return nullptr;
        }
    }

    size_t size() const noexcept { return count; }
    std::string typeName() const { return typeindex.name(); }
    bool isInitialized() const noexcept { return initialized; }

private:
    bool initialized = false;

    template<typename T>
    bool init(size_t N){
        if (initialized) {
            errl("ARRAYPTR already initialized; init() ignored.");
            return false;
        }
        count = N;
        typeindex = typeid(T);
        initialized = true;
        return true;
    }
};


inline void arrayPtrTest(){
    errl("TEST2");
    testType1 arr[] = {{1,2}, {3,4}, {5,6}, {7,8}};
    
    ARRAYPTR arrptr;
    arrptr.init(arr,4);

    testType1* arr2 = arrptr.getPointer<testType1>();
    
    if(arr2){
        errl("arr[0].a: ", arr2[0].a, ", .b: ", arr2[0].b);
    }
}


#endif //end of file