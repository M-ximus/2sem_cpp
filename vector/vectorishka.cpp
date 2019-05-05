//
// Created by max on 11.03.19.
//

#ifndef VECTORISHKA_VECTORISHKA_CPP
#define VECTORISHKA_VECTORISHKA_CPP
//#include "vectorishka.h"

FILE* file_ = nullptr;
//!---------------------------------------------------------------------------------------------------------------------
//! 2nd type of Avraam's guarantees
//!
//! \param size
//!---------------------------------------------------------------------------------------------------------------------
template <typename Type>
Vectorishka<Type>::Vectorishka(size_t size):
        size_ (0),
        capa_ (size),
        error (0)
{
    try
    {
        data_ = new Type [size];
    }
    catch (const std::bad_alloc &error)
    {
        throw error;
    }
}


//!---------------------------------------------------------------------------------------------------------------------
//!Noexcept destructor
//!
//!---------------------------------------------------------------------------------------------------------------------
template <typename Type>
Vectorishka<Type>::~Vectorishka()
{
    delete [] data_;
    data_ = nullptr;
    size_ = Poison_for_size;
    capa_ = Poison_for_capa;
    error = Poison_for_error;
}


//!---------------------------------------------------------------------------------------------------------------------
//!Function for reallocating array of elements
//!
//! \return
//!---------------------------------------------------------------------------------------------------------------------
template <typename Type>
Type* Vectorishka<Type>::increase()
{

    if (capa_ == 0)
    {
        data_ = new Type;
        if (data_ == nullptr)
            error = Alloc_fail;

        capa_ = 1;
        return data_;
    }

    size_t  new_capa = 2 * capa_;
    Type* new_data = (Type*) realloc(data_, new_capa);

    if (new_data == nullptr)
    {
        error = Alloc_fail;
        return data_;
    }

    capa_ = new_capa;
    data_ = new_data;
    return data_;
}


//!---------------------------------------------------------------------------------------------------------------------
//!Function for decrease array of elem for saving memory(has hysteresis)
//!
//! \return
//!---------------------------------------------------------------------------------------------------------------------
template <typename Type>
Type* Vectorishka<Type>::decrease()
{
    if (capa_ == 0)
    {
        error = Bad_call_of_dercrease;
        return data_;
    }

    if (data_ == nullptr)
    {
        error = Call_of_died_obj;
        return data_;
    }

    size_t  new_capa = capa_ / 2;
    Type* new_data = (Type*) realloc(data_, new_capa);

    if (new_data == nullptr)
    {
        error = Alloc_fail;
        return data_;
    }

    capa_ = new_capa;
    data_ = new_data;

    return data_;
}

//!---------------------------------------------------------------------------------------------------------------------
//!Function for using dinamic vectorishka. It push your elem to the end of array
//!
//! @Note It control only the latest elem.
//! @Note Example:
//! @Note   Vectorishka arr(10);
//! @Note   arr[5] = 2;
//! @Note   arr.pushback(23); // arr[6] = 23;
//!---------------------------------------------------------------------------------------------------------------------
template <typename Type>
int Vectorishka<Type>::pushback(Type num)
{
    this->Ok();
    int param = 0;

    if (size_ == capa_)
    {
        this->increase();
        this->Ok();
        param = 1;
    }

    data_[size_] = num;
    size_++;

    this->Ok();

    return param;
}


//!---------------------------------------------------------------------------------------------------------------------
//!Check your vectorishka. It can be changed(not const)
//!
//! \return error code
//!---------------------------------------------------------------------------------------------------------------------
template <typename Type>
int Vectorishka<Type>::Ok()
{
    if (error != 0)
    {
        this->Dump();
        return error;
    }

    if (size_ > capa_)
        error = Stack_overflow;
    if (data_ == nullptr && capa_ != 0)
        error = Zero_buff;

    if (error != 0)
        this->Dump();

    return error;
}


//!---------------------------------------------------------------------------------------------------------------------
//!Function that can print you vectorishka, it needs a pointer to the logfile
//!
//! \return 0 if it can't print to the logfile, else 1
//!---------------------------------------------------------------------------------------------------------------------
template <typename Type>
int Vectorishka<Type>::Dump()
{
    if(file_ == nullptr)
        return 0;

    std::ofstream cout(Log, std::ios_base::app);
    fprintf(file_, "Vectorishka:\n");
    fprintf(file_, "\tdata_ = %p\n", data_);

    if (data_ != nullptr)
    {
        for (int i = 0; i < capa_; i ++)
        {
            fprintf(file_, "\t\t data_[%d] =", i);// Maybe poison, but it's array, not stack
            cout << data_[i];
        }

    }
    fprintf(file_, "\tsize = %lu", size_);
    if (size_ > capa_)
        fprintf(file_, "(Bad size <= size > capacity)\n");
    fprintf(file_, "\tcapa = %lu\n", capa_);

    cout.close();
    return 1;
}


//!---------------------------------------------------------------------------------------------------------------------
//!Overloaded new for memory control
//!
//! \return pointer to the allocated memory
//!---------------------------------------------------------------------------------------------------------------------
void* operator new(size_t num, const char* file_name, const char* func_prot, int line)
{
    printf("%s:\n", __PRETTY_FUNCTION__);
    static uint num_of_call = 0;
    void* vector = new char[num];

    if (file_ != nullptr)
    {
        fprintf(file_, "Ya rodilsya in the %s in the function %s in the line - %d !!! ", file_name, func_prot, line);
        fprintf(file_, "I'm Luntik and have %lu bits and my serial number on the sleeve is %d", num, num_of_call);
    }

    num_of_call++;
    return vector;
}

//!---------------------------------------------------------------------------------------------------------------------
//!Overloaded new[] for memory control
//!
//! \return pointer to the allocated memory
//!---------------------------------------------------------------------------------------------------------------------
void* operator new[](size_t num, const char* file_name, const char* func_prot, int line)
{
    printf("%s:\n", __PRETTY_FUNCTION__);
    static uint num_of_call = 0;
    void* vector = new char[num];

    if (file_ != nullptr)
    {
        fprintf(file_, "Ya rodilsya in the %s in the function %s in the line - %d !!! ", file_name, func_prot, line);
        fprintf(file_, "I'm Luntik and have %lu bits and my serial number on the sleeve is %d", num, num_of_call);
    }

    num_of_call++;
    return vector;
}

//!---------------------------------------------------------------------------------------------------------------------
//!Function for swap info in two vectorishka
//!
//!
//!---------------------------------------------------------------------------------------------------------------------
template <typename Type>
void Vectorishka<Type>::swap(Vectorishka &that)
{
    std::swap(data_, that.data_);
    std::swap(size_, that.size_);
    std::swap(capa_, that.capa_);
}

//!---------------------------------------------------------------------------------------------------------------------
//!Overloaded operator= with swap&copy idiom
//!
//! \param Vectorishka& rhs
//! \return
//! --------------------------------------------------------------------------------------------------------------------
template <typename Type>
Vectorishka<Type>& Vectorishka<Type>::operator=(const Vectorishka& rhs) {
    this->Ok();
    Vectorishka copy(rhs);
    this->swap(copy);
    return *this;
}

//!---------------------------------------------------------------------------------------------------------------------
//!Copy constructor
//!
//! \param original
//! @Note print info that it was called
//!---------------------------------------------------------------------------------------------------------------------
template <typename Type>
Vectorishka<Type>::Vectorishka(const Vectorishka &original)
{
    if (original.size_ < 0 || original.capa_ < original.size_ || original.data_ == nullptr)
    {
        error = Constructor__error;
        return;
    }

    size_ = original.size_;
    capa_ = original.capa_;
    data_ = new Type [original.size_];//(data_t*) calloc(original.size, sizeof(data_t));

    for(int i = 0; i < size_; i++)
        data_[i] = original.data_[i];

    if(file_ != nullptr)
        fprintf(file_, "Copy constructor\n");
}

//!---------------------------------------------------------------------------------------------------------------------
//!Overloaded operator[]
//!
//! \param index
//! \return
//! @Note it doesn't check index
//!---------------------------------------------------------------------------------------------------------------------
template <typename Type>
Type& Vectorishka<Type>::operator[](size_t index)
{
    if (index + 1 > size_)
        size_ = index + 1;

    return data_[index];
}

//!---------------------------------------------------------------------------------------------------------------------
//!Overloaded operator+
//!
//!
//!---------------------------------------------------------------------------------------------------------------------
template <typename Type>
Vectorishka<Type> Vectorishka<Type>::operator +(const Vectorishka &a)
{
    Vectorishka copy (a);
    copy += *(this);
    return copy;
}

//!---------------------------------------------------------------------------------------------------------------------
//!Overloaded operator +=
//!
//! @Note Sometimes it call copyconstructor
//!---------------------------------------------------------------------------------------------------------------------
template <typename Type>
Vectorishka<Type>& Vectorishka<Type>::operator +=(const Vectorishka &a)
{
    if(a.capa_ > capa_)
    {
        Vectorishka copy(a);

        size_t counter = 0;
        if(size_ > copy.size_)
            counter = size_;
        else
            counter = copy.size_;

        for(int i = 0; i < counter; i ++)
            copy.data_[i] += data_[i];

        this->swap(copy);
    }
    else
    {
        size_t counter = 0;
        if (a.size_ > size_)
        {
            counter = a.size_;
            size_   = a.size_;
        }
        else
            counter = size_;

        for(int i = 0; i < counter; i++)
            data_[i] += a.data_[i];
    }
    return *this;
}

//!---------------------------------------------------------------------------------------------------------------------
//!Move constructor
//!---------------------------------------------------------------------------------------------------------------------
template <typename Type>
Vectorishka<Type>::Vectorishka(Vectorishka &&rhs):
    data_(nullptr),
    size_(0),
    error(0),
    capa_(0)
{
    this->swap(rhs);

    fprintf(file_, "Move constructor\n");
}

//!---------------------------------------------------------------------------------------------------------------------
//!Overloaded move operator =
//!
//! It print info into logfile
//!---------------------------------------------------------------------------------------------------------------------
template <typename Type>
Vectorishka<Type>& Vectorishka<Type>::operator=(Vectorishka &&rhs)
{
    this->swap(rhs);

    fprintf(file_, "Move =\n");
}

template <>
Vectorishka <Proxy_bool>::Vectorishka(size_t size):
        size_(size),
        error(0)
{
    if (size == 0)
    {
        capa_ = 0;
        data_ = nullptr;
    }
    else
    {
        size_t frame = sizeof(char) * 8;
        capa_ = size / frame;
        if (size % frame > 0)
            capa_++;

        data_ = new Proxy_bool[capa_];
        fprintf(file_, "mem bool = %p \n mem char = %p", data_, data_);
    }
}

#endif