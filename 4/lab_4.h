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
#include <array>
#include <memory>

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

class Human{
public:

    Human(const std::string& name) : _name(name){}

    std::string _name;
    bool isLive{true};


    std::shared_ptr<Human> _mother;
    std::shared_ptr<Human> _father;

    void print() const{
        std::cout << "me: " << _name;
        if(_father) std::cout << " father: " << _father->_name;
        if(_mother) std::cout << " mather: " << _mother->_name;
        std::cout << "\n" << _name << " childs: \n";
        for(const auto& c : _childs){
            c->print();
        }
    }

    std::list<std::shared_ptr<Human>> _childs;
};

std::shared_ptr<Human> child(std::shared_ptr<Human> m, std::shared_ptr<Human> f, const std::string& name){
    std::shared_ptr<Human> c = std::shared_ptr<Human>(new Human(name));
    c->_mother = m;
    c->_father = f;
    m->_childs.push_back(c);
    f->_childs.push_back(c);
    return c;
}


//---------------------------- [7] ----------------------------------

#define mydbg std::cout << __PRETTY_FUNCTION__ << std::endl

constexpr int constlen(const char* s, const int cnt = 0){
    if(*s == 0){
        return cnt;
    }
    return constlen(s+1, cnt+1);
}




template<typename T, size_t size>
class MyArray
{
public:

    MyArray() = default;
    MyArray(T&& a)
    {
        mydbg;
//        for(int i=0; i<size; i++){
//            ar[i] = a[i];
//        }
    }

    T ar[size]{}; //как обеспечить инициализацию элементов базового типа по умолчанию нулем?

};

MyArray() -> MyArray<int, 0>;
//size(const _Tp (&/*__array*/)[_Nm]) noexcept

MyArray(const char* s) -> MyArray<char, sizeof(s)>;

template <class T>
MyArray(T&& a) -> MyArray<T, sizeof(a)>;


//template<class T>
//MyArray(const std::initializer_list<T>& list) -> MyArray<T, 15>;
//MyArray(T ) - > MyArray<T, sizeof(T)>;



template <class T>
void test(T&& a){
    mydbg;
    std::cout << "sizeof(a): " << sizeof(a) << "\n";
    std::cout << "len(a): " << sizeof(a)/sizeof(*std::begin(a)) << "\n";
}

void test0(int (&a)[10]){
    mydbg;
//    //std::cout << "sizeof(a): " << sizeof(a) << "\n";
//    //std::cout << "len(a): " << sizeof(a)/sizeof(*std::begin(a)) << "\n";
}

