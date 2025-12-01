
#include "logging.hpp"
#include <typeindex>
#include <typeinfo>
#include "baseTypes.hpp"

//this is a non-templated array class
class ARRAY{
    public:
        void* data = nullptr;
        size_t count = 0;
        size_t elementSize = 0;
        std::type_index typeindex{typeid(void)};
        void (*deleter)(void*) = nullptr;

        //The magic is done by passing a sample element, and the type is automatically stored
        template<typename T>
        ARRAY(const T& sample, const size_t N): typeindex(typeid(T)){
            elementSize = sizeof(T);
            count = (N == 0) ? 1 : N;
            T* p = new T[count];
            deleter = &_array_deleter<T>;   // use static template deleter

            try {
                for(size_t i = 0; i < count; ++i)
                    p[i] = sample;
            } catch(...) {
                delete[] static_cast<T*>(p);
                errl("BAD TYPE FOR ARRAY!");
                throw;
            }

            data = p;
            std::string tn = typeindex.name();
            errl("Created with type: ", tn);
        }

        ARRAY(const ARRAY&) noexcept = delete;
        ARRAY& operator=(const ARRAY&) noexcept = delete;
        
        ARRAY(ARRAY&& other) noexcept 
            : data(other.data),
            count(other.count),
            elementSize(other.elementSize),
            typeindex(other.typeindex),
            deleter(other.deleter)
        {
            other.data = nullptr;
            other.count = 0;
            other.elementSize = 0;
            other.deleter = nullptr;
            other.typeindex = typeid(void);
        }

        ARRAY& operator=(ARRAY&& other) noexcept {
            if (this == &other) {
                return *this;
            }
            _destroy();

            data = other.data;
            count = other.count;
            typeindex = other.typeindex;
            deleter = other.deleter;
            elementSize = other.elementSize;

            other.elementSize = 0;
            other.data = nullptr;
            other.count = 0;
            other.deleter = nullptr;
            return *this;
        }


        ~ARRAY() noexcept {
            _destroy();
        }

        explicit operator bool() const noexcept {
            return data != nullptr;
        }

        template<typename T>
        bool isType() const noexcept {
            return typeindex == typeid(T);
        }

        template<typename T>
        T& at(size_t i) {
            if (i >= count) {
                errl("INDEX OOR IN ARRAY.AT()!");
                throw std::out_of_range("ARRAY index out of range");
            }
            if(typeid(T) != typeindex) {
                errl("INCORRECT TYPE USED IN ARRAY.AT()!");
                throw std::bad_cast();
            }
            return static_cast<T*>(data)[i];
        }

        template<typename T>
        const T& at(size_t i) const {
            if (i >= count) {
                errl("INDEX OOR IN ARRAY.AT()!");
                throw std::out_of_range("ARRAY index out of range");
            }
            if(typeid(T) != typeindex) {
                errl("INCORRECT TYPE USED IN CONST ARRAY.AT()!");
                throw std::bad_cast();
            }
            return static_cast<const T*>(data)[i];
        }

        //templated pointer accessor with type guard
        //gets the raw pointer of underlying standard array
        template<typename T>
        T* getRawPointer() const{
            if(typeid(T) == typeindex){
                return static_cast<T*>(data);
            }else{
                std::string tn = typeid(T).name();
                errl("INCORRECT TYPE '", tn,"' USED TO GET RAW POINTER FROM ARRAY!");
                throw std::bad_cast();
            }
        }

        size_t size() const noexcept { return count; }
        std::string typeName() const { return typeindex.name(); }

    private:
        template<typename T> static void _array_deleter(void* ptr){ delete[] static_cast<T*>(ptr); }

        void _destroy() noexcept {
            if (deleter && data){
                deleter(data);
            }
            data = nullptr;
            count = 0;
            elementSize = 0;
            typeindex = typeid(void);
            deleter = nullptr;
        }
};

inline void arrayTest(){

    errl("CUSTOM ARRAY TEST");
    ARRAY test = ARRAY(testType1({4, 8.0f}), 30);

    errl("Type1: count ", test.count, ", typeindex: ", test.typeindex.name());

    testType1* t1p = test.getRawPointer<testType1>();
    if(t1p){
        errl("Type1[0].a: ", t1p[0].a, ", .b: ", t1p[0].b);
    }

    errl("Type1.at(0): ", test.at<testType1>(0).a, ", ", test.at<testType1>(0).b);

    try{
        testType2* t2p = test.getRawPointer<testType2>();
    }catch(...){
        errl("Bad type error thrown, good.");
    }


    try{
        testType3* t3p = test.getRawPointer<testType3>();
    }catch(...){
        errl("Bad type error thrown, good.");
    }
    
    //todo test all the other error catchers...
    
    errl();
}
