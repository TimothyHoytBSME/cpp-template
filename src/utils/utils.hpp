#ifndef UTILS_HPP
#define UTILS_HPP

#include "logging.hpp"
#include "baseTypes.hpp"
#include "customvector.hpp"
#include "arrayPtr.hpp"
#include <random>
#include <chrono>
#include <stdexcept>
#include <regex>

inline void runUtilsTests(){
    arrayPtrTest();
    vectorTest();
}

inline float randFloat(){
    unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
    return distribution(generator);
}

inline float randFloat(float min, float max){
    if (max <= min){
        throw std::invalid_argument("randFloat(min,max) max is <= min !!!");
    }
    return min + randFloat()*(max-min);
}

#endif // end of file