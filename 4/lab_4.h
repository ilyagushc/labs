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

    static int cnt;
    Human(const std::string& name) : _name(name){
        cnt++;
        std::cout << "+" << cnt << std::endl;
    }
    ~Human(){
        cnt--;
        std::cout << "-" << cnt << std::endl;
    }

    std::string _name;
    bool isLive{true};


    std::weak_ptr<Human> _mother;
    std::weak_ptr<Human> _father;

    void print() const{
        std::cout << "me: " << _name;
        if(_father.use_count())
            std::cout << " father: " << _father.lock()->_name;
        if(_mother.use_count())
            std::cout << " mather: " << _mother.lock()->_name;
        std::cout << "\n" << _name << " childs: \n";
        for(const auto& c : _childs){
            c.lock()->print();
        }
    }

    std::list<std::weak_ptr<Human>> _childs;
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
    MyArray(T* data){

        mydbg;

        for(int i=0; i<size; i++){
            ar[i] = data[i];
        }
    }

    T ar[size]{}; //как обеспечить инициализацию элементов базового типа по умолчанию нулем?
};


template <class T, size_t num>
MyArray(const T(&a)[num]) -> MyArray<T, num>;



auto print0 = [](const auto& c){
    for(int i=0; i<sizeof(c) / sizeof(c[0]); i++){
        std::cout << c[i] << " ";
    }
    std::cout << "\n";
};
