//
// Created by max on 11.03.19.
//

#ifndef VECTORISHKA_VECTORISHKA_H
#define VECTORISHKA_VECTORISHKA_H

#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cassert>
#include <utility>
#include <cstring>
#include <fstream>
#include "Proxy_bool.h"

//typedef double data_t;
extern FILE* file_;
const char Log[] = "/home/max/CLionProjects/vectorishka/Plotina.logi";

const size_t Poison_for_size = 12345;
const size_t Poison_for_capa = 54321;
const size_t Poison_for_error = 5051;

enum {
    Alloc_fail = 7,
    Bad_call_of_dercrease = 45,
    Call_of_died_obj = 57,
    Zero_buff = 33,
    Stack_overflow = 35,
    Constructor__error = 53,
};

template <typename Type>
class Vectorishka {
private:
    Type*   data_;
    size_t  size_;
    size_t  capa_;
    int     error;

    Type* increase();
    Type* decrease();
    void swap(Vectorishka& that);
public:
    explicit Vectorishka(size_t size = 1);
    Vectorishka(const Vectorishka &original);
    Vectorishka(Vectorishka &&rhs);
    ~Vectorishka();
    int pushback(Type num);
    int Ok();
    int Dump();
    Vectorishka& operator = (const Vectorishka &original);
    Type&      operator [](size_t index);
    Vectorishka  operator + (const Vectorishka &a);
    Vectorishka& operator +=(const Vectorishka &a);
    Vectorishka& operator = (Vectorishka &&rhs);
};

void* operator new  (size_t num, const char* file_name, const char* func_prot, int line);
void* operator new[](size_t num, const char* file_name, const char* func_prot, int line);

/*#define delete( x ) \
{\
    delete x; \
    if (file_ != nullptr)\
    {\
        if ( x != nullptr)\
            fprintf(file_, "Oh my God!!! They killed Kenny!!! In the %s in the function %s in the line - %d\n", __FILE__, __PRETTY_FUNCTION__, __LINE__);\
        else\
            fprintf(file_, "You wanted kill Luntik secondly in the %s in the function %s in the line - %d", __FILE__, __PRETTY_FUNCTION__, __LINE__);\
    }\
}

#define delete_sq( x ) \
{\
    delete[] x; \
    if (file_ != nullptr)\
    {\
        if ( x != nullptr)\
            fprintf(file_, "Oh my God!!! They killed Kenny!!! In the %s in the function %s in the line - %d\n", __FILE__, __PRETTY_FUNCTION__, __LINE__);\
        else\
            fprintf(file_, "You wanted kill Luntik secondly in the %s in the function %s in the line - %d", __FILE__, __PRETTY_FUNCTION__, __LINE__);\
    }\
}
*/

#include "vectorishka.cpp"

#endif //VECTORISHKA_VECTORISHKA_H
