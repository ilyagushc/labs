#pragma once

#include <iostream>
#include <string.h>
#include <cmath>

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
            res +=  std::pow(2, i);
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
