#ifndef _UTILS_H_
#define _UTILS_H_

// C++ headers
#include <string>
#include <cstdlib>
#include <typeinfo>
#include <cxxabi.h>
#include <iostream>

template<typename T>
std::string get_type()
{
    int status;
    std::string name = typeid(T).name();

    auto demangled_name = abi::__cxa_demangle(name.c_str(), nullptr, nullptr, &status);

    if (status == 0)
    {
        name = demangled_name;
        std::free(demangled_name);
    }
    printf("%s\n", name.c_str());
    return name;
}

template<typename T1, typename T2>
bool type_name_is_equal()
{
    return get_type<T1>() == get_type<T2>();
}

template<typename T1, typename T2>
bool type_size_is_equal()
{
    return sizeof(T1) == sizeof(T2);
}

template<typename T1, typename T2>
bool are_equal()
{
    return type_name_is_equal<T1, T2>() && type_size_is_equal<T1, T2>();
}

#endif         // _UTILS_H_