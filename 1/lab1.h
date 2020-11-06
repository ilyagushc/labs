#pragma once

#include <vector>
#include <list>
#include <set>
#include <deque>
#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <type_traits>
#include <iterator>

template<class T1>
auto testSum(const T1& c1) {
    std::cout << *std::begin(c1);
    //sizeof(std::begin(c1));
	return 0;
}

template <class T1, class T2>
auto SumCont(const T1& c1, const T2& c2)
{
    std::vector<decltype (*std::begin(c1)+ *std::begin(c2))> res;
    int n1 = std::size(c1), n2 = std::size(c2);
    if (n1 < n2) {
        std::transform(std::begin(c1), std::end(c1), std::begin(c2), std::back_inserter(res), [](const auto& i1, const auto& i2) {
            return i1 + i2;
            });
        auto it = std::begin(c2);
        std::advance(it, std::size(c1));
        std::copy(it, std::end(c2), std::back_inserter(res));
        return res;
    }
    else {
        std::transform(std::begin(c2), std::end(c2), std::begin(c1), std::back_inserter(res), [](const auto& i1, const auto& i2) {
            return i1 + i2;
            });
        auto it = std::begin(c1);
        std::advance(it, std::size(c2));
        std::copy(it, std::end(c1), std::back_inserter(res));
        return res;
    }
};

//------------------------------ 10 --------------------------------------
template<typename T>
struct EnumMap
{
    static std::map<std::string, T> _map;
    static const auto& getMap() { return _map; }
};


class StringToEnumException : public std::exception{
public:
    const char* what() const noexcept override{
        return "bad string for enum";
    }
};


template<class T>
T stringToEnum(const std::string& s)
{
    auto& m = EnumMap<T>::_map;
    if(m.find(s) != m.end()){
        return m[s];
    }
    throw StringToEnumException();

    //лучше так:
    return m.at(s);
}

template<class T>
std::string enumToString(const T& e){
    for(const auto& [key, val] : EnumMap<T>::_map){
        if(val == e){
            return key;
        }
    }
    return std::string("");
}

enum class COLORS{White, Red, Black, Yellow};


template<>
std::map<std::string, COLORS> EnumMap<COLORS>::_map
{
    {"White",   COLORS::White},
    {"Red",     COLORS::Red},
    {"Black",   COLORS::Black},
    {"Yellow",  COLORS::Yellow}
};




