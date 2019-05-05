//
// Created by max on 17.04.19.
//

#ifndef VECTORISHKA_PROXY_BOOL_H
#define VECTORISHKA_PROXY_BOOL_H

const unsigned char Poison_for_bool = 0xaa;//10101010

class Proxy_bool{
private:
    unsigned char data_;
public:
    Proxy_bool(const Proxy_bool& original);
    Proxy_bool();
    ~Proxy_bool();

    Proxy_bool& operator = (const Proxy_bool& original);
    Proxy_bool& operator = (bool rhs);
    Proxy_bool  operator + (const Proxy_bool& that);
    Proxy_bool  operator + (bool that);
    operator bool () const;
};


#endif //VECTORISHKA_PROXY_BOOL_H
