#ifndef LAB2_H
#define LAB2_H


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





#endif // LAB2_H
