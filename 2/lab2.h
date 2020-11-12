#pragma once

#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <initializer_list>
#include <set>
#include <functional>

#define mydbg std::cout << __PRETTY_FUNCTION__ << "\n"

template <class T>
void print(const T& c){
    for(const auto& e : c){
        std::cout << e << " ";
    }
    std::cout << std::endl;
}




//----------------------------- [1] -----------------------------

template <class T>
class MyVec{
public:
    MyVec(){}
    MyVec(const std::initializer_list<T>& l){
        add(l);
    }

    void add(const std::initializer_list<T>& l){
        std::copy_if(std::begin(l), std::end(l), std::back_inserter(_v), [this](const auto& e){
            if(!_diapason){
                return std::find(_v.begin(), _v.end(), e) == _v.end();
            }
            else if(e >= _min && e <= _max){
                return std::find(_v.begin(), _v.end(), e) == _v.end();
            }

            return false;
        });
    }

    void del(const std::initializer_list<T>& l){

        for(const auto& e : l){
            std::vector<T> tmp;
            std::copy_if(_v.begin(), _v.end(), std::back_inserter(tmp), [this, &e](const auto& vElem){
               return e != vElem;
            });
            _v = tmp;
        }
    }

    MyVec(T min, T max){
        if(min < max){
            _diapason = true;
            _min = min;
            _max = max;
        }
    }
    bool setMinMax(T min, T max) {
        if(min > max){
            return false;
        }
        _diapason = true;
        _min = min;
        _max = max;

        std::vector<T> tmp;
        std::copy_if(_v.begin(), _v.end(), std::back_inserter(tmp), [this](const auto& e){
            if(e >= _min && e <= _max ){
                return true;
            }
            return false;
        });
        _v = tmp;

    }

    void sort(std::function<bool(const T& e1, const T& e2)> func){
        std::sort(_v.begin(), _v.end(), func);
    }

    void print(){
        for(const auto& i : _v){
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }

private:
    T _min;
    T _max;
    bool _diapason{false};
    std::vector<T> _v;
};


//----------------------------- [2] -----------------------------
template <class T>
class MyQueue{
public:
    MyQueue(){
        init();
    }
    ~MyQueue(){delete[] arr;}

    MyQueue(std::initializer_list<T> list){
        init(std::size(list));
        for(const auto& i : list){
            push(i);
        }
    }

    MyQueue(int size, const T& e){
        init(size);
        for(int i=0; i<size; i++){
            push(e);
        }
    }

    MyQueue(const MyQueue& other){
        curSize = other.curSize;
        arr = new T[curSize];
        first = other.first;
        last = other.last;
        for(int i=0; i<curSize; i++){
            arr[i] = other.arr[i];
        }
    }

    MyQueue(MyQueue&& other){
        arr = other.arr;
        curSize = other.curSize;
        first = other.first;
        last = other.last;

        other.init();
    }

    MyQueue& operator=(const MyQueue& other){
        curSize = other.curSize;
        arr = new T[curSize];
        first = other.first;
        last = other.last;

        for(int i=0; i<curSize; i++){
            arr[i] = other.arr[i];
        }
        return *this;
    }

    MyQueue& operator=(MyQueue&& other){

        delete[] arr;

        arr = other.arr;
        curSize = other.curSize;
        first = other.first;
        last = other.last;

        other.init();
    }



    void init(int size = 0){
        if(size){
            curSize = size;
        }
        arr = new T[curSize];
        first = 0;
        last = 0;
        cnt = 0;
    }

    void push(const T& e){
        arr[first] = e;
        first++;
        cnt++;


        if(first == curSize){
            //std::cout << "resize\n";
            curSize *= 2;
            T* newArr = new T[curSize];
            for(int i = last; i < first; i++){
                newArr[i] = arr[i];
            }
            T* delArr = arr;
            arr = newArr;
            delete[] arr;
        }
    }
    T pop(){
        if(!cnt){
            return T{};
        }
        cnt--;
        int iRes = last;
        last++;
        return arr[iRes];
    }


    void print(){
        if(!cnt){
            return;
        }
        for(int i=last; i<=first; i++){
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;
    }


    class iterator : public std::iterator<std::forward_iterator_tag, MyQueue>
    {
    public:
        iterator(T* p) : data(p){}
        iterator(const iterator& other){data = other.data;}
        iterator& operator=(const iterator& other) {data = other.data; return *this;}
        bool operator!=(iterator const& other) const {return data != other.data;}
        bool operator==(iterator const& other) const {return data == other.data;}
        T& operator*() const {return *data;}
        iterator& operator++() {data++; return *this;}

        T* data;
    };

    iterator begin(){return iterator(&arr[last]);}
    iterator end(){return iterator(&arr[first]);}//указывает на элемент за последним в очереди


private:
    T *arr;
    int first;
    int last;
    int curSize{2};
    int cnt{0};
};


//----------------------------- [3] -----------------------------

template <class T>
class MyUniquePTR
{
public:
    MyUniquePTR() = default;
    MyUniquePTR(const MyUniquePTR& other) = delete;
    MyUniquePTR operator=(const MyUniquePTR& other) = delete;


    MyUniquePTR(T *p){
        _data = p;
    }
    MyUniquePTR(MyUniquePTR&& p){
        _data = p._data;
        p._data = nullptr;
    }

    MyUniquePTR& operator=(MyUniquePTR&& other){
        if(_data == other._data){
            other._data = nullptr;
            return *this;
        }

        if(_data != nullptr){
            delete _data;
        }

        _data = other._data;
        other._data = nullptr;
    }

    ~MyUniquePTR(){
        if(_data != nullptr){
            delete _data;
        }
    }

    T* operator->(){
        return _data;
    }

    T& operator*(){
        if(_data != nullptr){
            return *_data;
        }
        throw std::exception();
    }
    operator bool() const{
        return _data;
    }
    T* get(){
        return _data;
    }
    void reset(T* p = nullptr){
        if(p){
            if(_data != nullptr){
                delete _data;
            }
            _data = p;
            return;
        }

        if(_data != nullptr){
            delete _data;
            _data = nullptr;
        }
    }




private:
    T* _data{nullptr};
};
