#pragma once
#include <type_traits>
#include <vector>
#include <set>
#include <list>
#include <deque>
#include <iostream>
#include <stack>
#include <queue>


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
//---------------------------- [3] ----------------------------------

//stack, queue, priority_queue
template <class T>
void printAdapt(const T& c){
    T tmp = c;
//    T::value_type var;

//    for(int i=0, n=c.size(); i<n; i++){
//        std::cout << tmp.pop() << " ";
//    }
//    std::cout << "\n";

//    decltype(auto) first = c.pop();
//    if constexpr(std::is_same<T, std::stack< T::value_type>>::value){
//        std::cout << "stack!\n";
//    }
//    if constexpr(std::is_same<T, std::queue<decltype (*std::begin(c))>>::value){
//        std::cout << "queue!\n";
//    }
//    if constexpr(std::is_same<T, std::priority_queue<decltype (*std::begin(c))>>::value){
//        std::cout << "priority_queue!\n";
//    }
}
//---------------------------- [4] ----------------------------------
