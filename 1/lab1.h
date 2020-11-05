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

