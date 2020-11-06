#pragma once

#include <iostream>
#include <string.h>
#include <cmath>
#include <algorithm>

//---------------------------------------- [1] --------------------------------------------
//---------------------------------------- [2] --------------------------------------------
constexpr int factorial(int i){
    if(i == 1){
        return 1;
    }
    return i * factorial(i-1);
}
//---------------------------------------- [2] --------------------------------------------
uint32_t operator""_mybin(const char* s){
    //std::cout << __PRETTY_FUNCTION__ << std::endl;
    //std::cout << "str: " << s << std::endl;
    //"100000000" -> в значение 256
    uint32_t res = 0;
    for(int i=0, n=strlen(s); i<n; i++){
        bool curBit = (s[n-1-i] - '0');
        if(curBit){
            res +=  std::pow(2, i); // << i
        }
        //std::cout << "i: " << i << " curBit: " << curBit << " 2^i: " << std::pow(2, i) << " res: " << res << std::endl;
    }
    return res;
}

constexpr int constlen(const char* s, const int cnt = 0){
    if(*s == 0){
        return cnt;
    }
    return constlen(s+1, cnt+1);
}
constexpr uint32_t binCalc(const char* s, const int pos){
    if(pos < 0){
        return 0;
    }
    return (s[0]-'0') ? std::pow(2, pos) + binCalc(s+1, pos-1) : binCalc(s+1, pos-1);
}
constexpr uint32_t operator""_constexpr_bin(const char* s){
    //"100000000" -> в значение 256
    return binCalc(s, constlen(s)-1);
}

//---------------------------------------- [3] --------------------------------------------

std::string operator""_toBinStr(const char* s){
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    std::cout << "str: " << s << " len: " << strlen(s) << std::endl;
    //get num from string
    uint32_t res{0};
    for(int i=0, n=strlen(s); i<n; i++){
        res += (s[i]-'0') * pow(10, n-i-1);
    }
    std::cout << "res: " << res << std::endl;
    //get bin string from num
    std::string resStr;
    uint32_t cur = res;
    while(1){
        resStr += (std::fmod(cur, 2) + '0');
        cur/=2;
        if(cur == 1){
            resStr += '1';
            break;
        }
    }
    std::reverse(resStr.begin(), resStr.end());
    return resStr;
}
//---------------------------------------- [4] --------------------------------------------


template <class T>
class MinMax{
public:
    MinMax(){}
    constexpr MinMax(const T& min, const T& max) : _min(min), _max(max){}

    void setMin(const T& min){
        _min = min;
    }

    constexpr T getMin()const{
        return _min;
    }

    void setMax(const T& max){
        _max = max;
    }

    constexpr T getMax()const{
        return _max;
    }

    constexpr T get(const T& val) const{
        if(val > _max){
            return _max;
        }
        if(val < _min){
            return _min;
        }
        return val;
    }


private:

    T _min{};
    T _max{};

};




