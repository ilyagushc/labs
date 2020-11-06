#pragma once
#include <type_traits>
#include <vector>
#include <set>
#include <list>
#include <deque>
#include <iostream>


//---------------------------- [1] ----------------------------------

template <class T>
void print(const T& c){
    if(!std::size(c)){
        return;
    }

    //remove reference
    auto e = *std::begin(c);
    if constexpr(std::is_pointer<decltype (e)>::value){
        for(const auto&  i : c){
            std::cout << *i << ", ";
        }
    }
    else{
        for(const auto&  i : c){
            std::cout << i << " ";
        }
    }
    std::cout << std::endl;
}


//---------------------------- [2] ----------------------------------
template <class T1, class T2>
void sum2elem(T1& e1, const T2& e2){
    if constexpr( std::is_same<T1, std::vector<T2>>::value){
        for(auto& e : e1){
            e += e2;
        }
    }
}
