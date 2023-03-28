#ifndef __MATHUTILS__H__
#define __MATHUTILS__H__

// C++ Headers
#include <vector>
#include <numeric> // std::accumulate
#include <iostream>
#include <algorithm>
#include <type_traits>

// Application Headers

template <typename T>
concept Integral = std::is_integral<T>::value;

Integral auto gcd(Integral auto a, Integral auto b)
{
    if (b == 0) 
        return a;
    return gcd(b, a % b);
}

[[depricated("Try to use some other method")]]
void depricated_test()
{
    std::cout << "This method is depricated" << std::endl;
}

std::vector<int> generate_sequence(const int& n)
{
    std::vector<int> v;
    auto i = 0;
    std::generate_n(std::back_inserter(v), n, [&](){return ++i;});
    return v;
}

auto generate_total(const std::vector<int>& v)
{
    auto i = std::accumulate(std::begin(v), std::end(v), 0);
    return i;
}

#endif  // __MATHUTILS__H__