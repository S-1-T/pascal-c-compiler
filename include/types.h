#pragma once

#ifndef PASCAL_C_COMPILER_TYPES_H
#define PASCAL_C_COMPILER_TYPES_H

#include <vector>

enum TYPES {
    VOID = -1, INT, _REAL, _BOOLEAN, _CHAR, RESERVED
};
enum SUBPROGRAM_TYPE {
    NONE = -1, FUNC, PROC
};  // NONE -> var/const/array
typedef std::vector<std::pair<int, int> > Ranges;  // not empty -> array

typedef std::vector<int> SubprogramArgsType;

#endif //PASCAL_C_COMPILER_TYPES_H
