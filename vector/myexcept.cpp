//
// Created by max on 07.04.19.
//

#include "myexcept.h"

myexcept::myexcept():
    num_line_(0),
    num_error_(0),
    reason_(nullptr)
{}

//myexcept myexcept::operator=()
//{}

myexcept::myexcept(myexcept* old)
{
    num_line_   = old->num_line_;
    num_error_  = old->num_error_;
    reason_     = old->reason_;

    old->reason_ = nullptr;
}

myexcept::myexcept(size_t num_line, int num_error, myexcept* reason):
    num_error_(num_error),
    num_line_(num_line),
    reason_(nullptr)
{
    printf("%s: %p\n", __PRETTY_FUNCTION__, this);
    if (reason)
        reason_ = new myexcept(reason);
}

myexcept::~myexcept()
{
    printf("%s: %p\n", __PRETTY_FUNCTION__, this);
    if (this->reason_)
    {
        (this->reason_)->~myexcept();
        delete reason_;
    }

    num_error_  = Poison_for_exception;
    num_line_   = Poison_for_exception;
}

void myexcept::print(FILE* logi)
{
    printf("%s: %p\n", __PRETTY_FUNCTION__, this);
    if (logi != nullptr)
    {
        fprintf(logi, "In %lu error num %d <- ", num_line_, num_error_);
        if (reason_)
            (this->reason_)->print(logi);
    }
}
