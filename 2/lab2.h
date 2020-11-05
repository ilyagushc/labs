#pragma once

#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <initializer_list>
#include <set>
#include <functional>


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
        _data = new T[_n];
    }

    MyQueue(const std::initializer_list<T>& list){
        _size = list.size();
        if(_n < _size){
            _n = _size;
        }
        _data = new T[_n];
        for(const auto& i : list){
            push(*new T(i));
        }
    }

    void push(const T& e){
        //кладем в конец
        *_last = e;
        _last++;
        _size++;

        if(_last == _data + _n-1){
            _last = _data;
        }
        if(_last == _first){
            //догнали голову перераспределение памяти
            int newN = _n*2;
            T* newData = new T[newN];
            T* cur = _first;
            T* newCur = newData;

            //копируем элементы
            while(cur != _last){
                newCur = cur;
                cur++;
                if(cur == _data+_n){
                    cur = _data;
                }
            }

        }
    }

    T pop(){
        if(_first == nullptr || _first == _last){
            //нет элементов
            return T();
        }

        //берем эелемент из начала
        T res = *_first;

        //двигаем указатель вперед
        _first++;

        //если пришли к концу - перешагиваем в начало
        if(_first == _data + _n){
            _first = _data;
        }

        return res;
    }

private:
    int _n{10};
    int _size;
    T* _data;
    T* _first{nullptr};
    T* _last{nullptr};
};



//----------------------------- [3] -----------------------------

template <class T>
class MyUniquePTR
{
public:
    MyUniquePTR(T *p){
        _data = p;
    }
    MyUniquePTR(T&& p){
        _data = p->get();
        p->reset();
    }
    MyUniquePTR& operator=(MyUniquePTR&& other){
        if(_data == other._data){
            other.reset();
            return *this;
        }
        if(other._data){
            if(_data){
                delete _data;
            }
            _data = other._data;
            other.reset();
        }
    }
    ~MyUniquePTR(){
        if(_data){
            delete _data;
        }
    }

    T* operator->(){
        return _data;
    }

    T& operator*(){
        if(_data){
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
            if(_data){
                delete _data;
            }
            _data = p;
            return;
        }

        if(_data){
            delete _data;
            _data = nullptr;
        }
    }



    MyUniquePTR(const MyUniquePTR& other) = delete;
    MyUniquePTR operator=(const MyUniquePTR& other) = delete;

private:
    T* _data{nullptr};
};
