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



template <typename T> class MyQueue {
    public:
        using value_type = T;
        using pointer = T*;
        using reference = T&;
        using const_reference = const T&;
        using size_type = std::size_t;
        class Iterator;
        using iterator = Iterator;
        using const_iterator = const Iterator;

        MyQueue(size_type size, const T& v = T{}) :
            last{size},
            length{size},
            capacity{size}
        {
            data = new value_type[capacity];
            for (size_type i = 0; i < size; ++i) {
                data[i] = v;
            }
        }
        MyQueue(std::initializer_list<T> il) :
            last{0},
            length{il.size()}
        {
            capacity = length * 2;
            data = new value_type[capacity];
            for (const auto& el : il) {
                data[last++] = el;
            }
        }
        MyQueue(const MyQueue& other) :
            first{other.first},
            last{other.last},
            length{other.length},
            capacity{other.capacity}
        {
            data = new value_type[capacity];
            int i = 0;
            for (const auto& el : other) {
                data[i++] = el;
            }
        }
        MyQueue(MyQueue&& other) :
            first{other.first},
            last{other.last},
            length{other.length},
            capacity{other.capacity},
            data{other.data}
        {
            other.first = 0;
            other.last = 1;
            other.length = 0;
            other.capacity = 0;
            other.data = nullptr;
        }
        MyQueue& operator=(std::initializer_list<T> il) {
            first = 0;
            last = 0;
            length = il.size();
            if (capacity < il.size()) {
                capacity = length * 2;
                delete[] data;
                data = new value_type[capacity];
            }
            for (const auto& el : il) {
                data[last++] = el;
            }
            return *this;
        }
        MyQueue& operator=(const MyQueue& other) {
            if (this == &other) return *this;
            first = other.first;
            last = other.last;
            length = other.length;
            capacity = other.capacity;
            delete[] data;
            data = new value_type[capacity];
            for (size_type i = 0; i < capacity; ++i) {
                data[i] = other.data[i];
            }
            return *this;
        }
        MyQueue& operator=(MyQueue&& other) {
            if (this == &other) return *this;
            first = other.first;
            last = other.last;
            length = other.length;
            capacity = other.capacity;
            delete[] data;
            data = other.data;
            other.first = 0;
            other.last = 1;
            other.length = 0;
            other.capacity = 0;
            other.data = nullptr;
            return *this;
        }
        ~MyQueue() {
            if (data) delete[] data;
        }
        bool operator==(const MyQueue& other) const {
            return data == other.data;
        }
        bool operator!=(const MyQueue& other) const {
            return not (*this == other);
        }
        size_type size() const {
            return length;
        }
        bool empty() const {
            return not length;
        }
        value_type pop() {
            if (empty()) throw std::range_error("MyQueue::pop(): queue is empty.");
            value_type result{data[first++]};
            if (first == capacity) first = 0;
            first = first % capacity;
            --length;
            return result;
        }
        void push(const_reference v) {
            ++last;
            ++length;
            if (last > capacity) {
                last = 1;
            }
            if (last == first) {
                size_type new_capacity = length * 2;
                pointer new_data = new value_type[new_capacity];
                size_type current = first;
                size_type new_current = 0;
                while (current + 1 != last) {
                    current = first++ % capacity;
                    new_data[new_current++] = data[current];
                }
                delete[] data;
                data = new_data;
                first = 0;
                last = new_current;
                capacity = new_capacity;
            }
            data[last - 1] = v;
        }
    public:
        class Iterator : public std::iterator<std::forward_iterator_tag, T> {
            friend class MyQueue;
            public:
                Iterator() {}
                Iterator& operator++() {
                    ++current;
                    if (current == holder.last) return *this;
                    current %= holder.capacity;
                    return *this;
                }
                T& operator*() const { return holder.data[current]; }
                bool operator==(const Iterator& other) const {
                    if (holder.length == 0) return true;
                    return holder == other.holder and current == other.current;
                }
                bool operator!=(const Iterator& other) const {
                    return not (*this == other);
                }
            protected:
                Iterator(const MyQueue& holder, size_type current) :
                    holder{holder},
                    current{current}
                {}
                const MyQueue& holder;
                size_type current;
        };
        iterator begin() { return iterator{*this, first}; }
        iterator end() { return iterator{*this, last}; }
        const_iterator begin() const { return iterator{*this, first}; }
        const_iterator end() const { return iterator{*this, last}; }
    private:
        size_type first = 0;
        size_type last = 1;
        size_type length = 0;
        size_type capacity = 10;
        pointer data = nullptr;
};


template <class T>
class MyQueue0{
public:
    MyQueue0(){
        init();
    }
    ~MyQueue0(){delete[] arr;}

    MyQueue0(std::initializer_list<T> list){
        init(std::size(list));
        for(const auto& i : list){
            push(i);
        }
    }

    MyQueue0(int size, const T& e){
        init(size);
        for(int i=0; i<size; i++){
            push(e);
        }
    }

    MyQueue0(const MyQueue0& other){
        curSize = other.curSize;
        arr = new T[curSize];
        first = other.first;
        last = other.last;
        for(int i=0; i<curSize; i++){
            arr[i] = other.arr[i];
        }
    }

    MyQueue0(MyQueue0&& other){
        arr = other.arr;
        curSize = other.curSize;
        first = other.first;
        last = other.last;

        other.init();
    }

    MyQueue0& operator=(const MyQueue0& other){
        curSize = other.curSize;
        arr = new T[curSize];
        first = other.first;
        last = other.last;

        for(int i=0; i<curSize; i++){
            arr[i] = other.arr[i];
        }
        return *this;
    }

    MyQueue0& operator=(MyQueue0&& other){

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


    class iterator : public std::iterator<std::forward_iterator_tag, MyQueue0>
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
