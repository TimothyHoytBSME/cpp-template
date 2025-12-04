#ifndef LOGGING_HPP
#define LOGGING_HPP

#include <cmath>
#include <iostream>
#include <cstdio>
#include <ostream>
#include <cstdint>

inline void clear_line(std::ostream& os) {
    os << "\33[2K\r";
}

inline void clear_lines(int count, std::ostream& os) {
    for(int c=0; c<count; c++){
        if(c>0){
            os<<"\033[A";
        }
        os << "\33[2K\r";
    }
}

// core: print any number of args to the given ostream (no newline)
template<typename... Ts>
inline void print(std::ostream &os, Ts&&... args){
    // fold expression: streams all args in order
    (os << ... << std::forward<Ts>(args));
}

template<typename... Ts>
inline void print(Ts&&... args){
    print(std::cerr, std::forward<Ts>(args)...);
    print(std::cout, std::forward<Ts>(args)...);
}

template<typename... Ts>
inline void printl(std::ostream &os, Ts&&... args){
    // fold expression: streams all args in order
    (os << ... << std::forward<Ts>(args));
    os << "\n";
}

template<typename... Ts>
inline void printl(Ts&&... args){
    printl(std::cerr, std::forward<Ts>(args)...);
    printl(std::cout, std::forward<Ts>(args)...);
}

// convenience: default to stdout
template<typename... Ts>
inline void log(Ts&&... args){
    print(std::cout, std::forward<Ts>(args)...);
}

// newline variant (print newline even with 0 args)
template<typename... Ts>
inline void logl(Ts&&... args){
    if constexpr (sizeof...(Ts) > 0){
        printl(std::cout, std::forward<Ts>(args)...);
    } else {
        std::cout << '\n';
    }
}

// same for stderr
template<typename... Ts>
inline void err(Ts&&... args){
    print(std::cerr, std::forward<Ts>(args)...);
}

template<typename... Ts>
inline void errl(Ts&&... args){
    if constexpr (sizeof...(Ts) > 0){
        printl(std::cerr, std::forward<Ts>(args)...);
    } else {
        std::cerr << '\n';
    }
}

inline std::string getSizeStr(unsigned long long allocation, std::ostream& os = std::cerr){
    bool lessthat1mb = allocation < 1024;
    if(lessthat1mb){
        return std::to_string(allocation) + " B";
    }else{
        float val = (float)allocation / 1024.0f;
        if (val < 1024){
            val = 0.01f*std::round(val*100);
            return std::to_string(val) + " KB";
        }else{
            val /= 1024.0f;
            if(val < 1024){
                val = 0.01f*std::round(val*100);
                return std::to_string(val) + " MB";
            }else{
                val /= 1024.0f;
                val = 0.01f*std::round(val*100);
                return std::to_string(val) + " GB";
            }
        }
    } 
}

inline bool convertToUint32_t(std::string str, uint32_t& uint){
    try {
        unsigned long temp_value = std::stoul(str, nullptr, 10);
        if (temp_value > std::numeric_limits<uint32_t>::max()) {
            errl("Value too large for uint32_t");
        }
        uint = static_cast<uint32_t>(temp_value);
        return true;
    } catch (const std::invalid_argument& e) {
        errl("Not a valid number"); return false;
    } catch (const std::out_of_range& e) {
        errl("Value too large"); return false;
    }
    errl("'",str,"' is not a uint32_t!"); return false;
}

inline std::string getInputStr(std::string prompt){
    std::string val = "";
    errl(prompt); 
    std::cin >> val;
    return val;
}

inline uint32_t getInputUint32_t(std::string prompt, uint32_t min, uint32_t max){
    uint32_t val = 0; bool valid = false;
    while(!valid){
        std::string ans = getInputStr(prompt);
        uint32_t uint;
        if(!convertToUint32_t(ans, uint)){errl();continue;}
        if(uint < min){errl("Min value: ", min);}
        else if(uint > max){errl("Max value: ", max);}
        else{val = uint; valid = true;} errl();
    } return val;
}

inline void enterToExit(){
    errl("\n\nPress Enter To Exit...");
    std::string res;
    std::getline(std::cin, res); 
    std::cin.get();
    std::cout<<"\n"<<std::flush;
    exit(0);
}

inline void flushAll(){
    std::cerr<<std::flush;
    std::cout<<std::flush;
}

inline void flush(std::ostream& os = std::cout){
    os<<std::flush;
}

#endif