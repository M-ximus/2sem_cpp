//
// Created by max on 17.04.19.
//

#include "Proxy_bool.h"

Proxy_bool::Proxy_bool() :
    data_(0)
{}

Proxy_bool::Proxy_bool(const Proxy_bool &original)
{
    data_ = original.data_;//exception?
}

Proxy_bool::~Proxy_bool()
{
    data_ = Poison_for_bool;
}

Proxy_bool& Proxy_bool::operator = (const Proxy_bool& original)
{
    int index = data_ & 0xE0; //11100000
    index = index >> 5;
    int this_mask = 0x01;//00000001
    this_mask = this_mask << index;

    index = original.data_ & 0xE0; //11100000
    index = index >> 5;
    int original_mask = 0x01;//00000001
    original_mask = original_mask << index;

    if (original_mask & original.data_)
        data_ = data_ | this_mask;
    else
        data_ = data_ & (~this_mask);// example: 00001000 -> 11110111 & data_

    return *this;
}

Proxy_bool& Proxy_bool::operator = (bool rhs)
{
    int index = data_ & 0xE0; //11100000
    index = index >> 5;
    int mask = 0x01 << index;

    if (rhs)
        data_ = data_ | mask;
    else
        data_ = data_ & (~mask);

    return *this;
}

Proxy_bool Proxy_bool::operator + (const Proxy_bool& that)
{
    Proxy_bool copy(that);
    int index_copy = that.data_ & 0xE0;
    index_copy = index_copy >> 5;
    int mask_copy = 0x01 << index_copy;

    if (mask_copy & that.data_)
        return copy;

    int index_this = data_ & 0xE0;
    index_this = index_this >> 5;
    int mask_this = 0x01 << index_this;

    if (mask_this & data_)
    {
        copy.data_ = copy.data_ | mask_copy;
        return copy;
    }

    return copy;
}

Proxy_bool Proxy_bool::operator + (bool that)
{
    Proxy_bool copy((*this));
    if (!that)
        return copy;

    int index_copy = copy.data_ & 0xE0;
    index_copy = index_copy >> 5;
    int mask_copy = 0x01 << index_copy;

    copy.data_ = copy.data_ | mask_copy;
    return copy;
}

Proxy_bool::operator bool () const
{
    int index_this = data_ & 0xE0;
    index_this = index_this >> 5;
    int mask_this = 0x01 << index_this;

    if (mask_this & data_)
        return true;

    return false;
}