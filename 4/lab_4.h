#pragma once
#include <type_traits>
#include <vector>
#include <set>
#include <list>
#include <deque>
#include <iostream>
#include <stack>
#include <queue>
#include <utility>

//---------------------------- [1] ----------------------------------

template <class T>
void print(const T& c){
    if constexpr(std::is_pointer<typename T::value_type>::value){
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
void printAdapt(T c){
    T tmp = c;

    while(tmp.size()){
        if constexpr ( std::is_same< std::queue<typename T::value_type>, T >::value ){
            std::cout << tmp.front() << " ";
        }
        if constexpr ( std::is_same< std::stack<typename T::value_type>, T >::value  || std::is_same< std::priority_queue<typename T::value_type>, T >::value ){
            std::cout << tmp.top() << " ";
        }
        tmp.pop();
    }
    std::cout << "\n";
}
//---------------------------- [6] ----------------------------------
template<typename T, size_t size>
class MyArray
{
    T ar[size]; //как обеспечить инициализацию элементов базового типа по умолчанию нулем?
    //…
};

