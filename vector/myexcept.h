//
// Created by max on 07.04.19.
//

#ifndef VECTORISHKA_MYEXCEPT_H
#define VECTORISHKA_MYEXCEPT_H

#include <iostream>

const int Poison_for_exception = 0x0fffffff;

class myexcept {
private:
    myexcept*   reason_;
    int         num_error_;
    size_t      num_line_;
public:
                myexcept(size_t num_line, int num_error, myexcept* reason = nullptr);
    explicit    myexcept(myexcept* old);
                myexcept();
                ~myexcept();
    //const char* what();
    void        print(FILE* logi);
};


#endif //VECTORISHKA_MYEXCEPT_H
