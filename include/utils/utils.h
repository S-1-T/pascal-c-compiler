//
// Created by 69118 on 2020/9/10.
//

#ifndef PASCAL_C_COMPILER_UTILS_H
#define PASCAL_C_COMPILER_UTILS_H

#include <strstream>
#include <string>

using namespace std;

template <class T>
string to_str(T type)
{
    strstream ss;
    ss << type;
    string ret;
    ss >> ret;

    return ret;
}

#endif //PASCAL_C_COMPILER_UTILS_H
