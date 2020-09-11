//
// Created by 69118 on 2020/9/10.
//

#ifndef PASCAL_C_COMPILER_EXCEPTIONS_H
#define PASCAL_C_COMPILER_EXCEPTIONS_H

#include <exception>

using std::exception;

class TypeException : public exception {
    const char* what() const noexcept override {
        return "无效的 Type";
    }
};

class StatementException : public exception {
    const char* what() const noexcept override {
        return "无效的 Statement";
    }
};

class FactorException : public exception {
    const char* what() const noexcept override {
        return "无效的 Factor";
    }
};

class UminusException : public exception {
    const char* what() const noexcept override {
        return "无效的 Uminus";
    }
};

class ConstException : public exception {
    const char* what() const noexcept override {
        return "无效的 Const";
    }
};

class OperatorException : public exception {
    const char* what() const noexcept override {
        return "无效的 Operator";
    }
};

#endif //PASCAL_C_COMPILER_EXCEPTIONS_H
