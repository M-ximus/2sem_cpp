//
// Created by max on 11.03.19.
//

#include "vectorishka.h"
FILE* file_ = nullptr;
//!---------------------------------------------------------------------------------------------------------------------
//!
//!
//! \param size
//!---------------------------------------------------------------------------------------------------------------------
Vectorishka::Vectorishka(size_t size):
        data_ (new data_t [size] {}),
        size_ (0),
        capa_ (size),
        error (0)
{}


//!---------------------------------------------------------------------------------------------------------------------
//!
//!
//!---------------------------------------------------------------------------------------------------------------------
Vectorishka::~Vectorishka()
{
    delete [] data_;
    data_ = nullptr;
    size_ = Poison_for_size;
    capa_ = Poison_for_capa;
    error = Poison_for_error;
}


//!---------------------------------------------------------------------------------------------------------------------
//!
//!
//! \return
//!---------------------------------------------------------------------------------------------------------------------
data_t* Vectorishka::increase()
{
    if (capa_ == 0)
    {
        data_ = new data_t;
        if (data_ == nullptr)
            error = Alloc_fail;

        capa_ = 1;
        return data_;
    }

    size_t  new_capa = 2 * capa_;
    data_t* new_data = (data_t*) realloc(data_, new_capa);

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
//!
//!
//! \return
//!---------------------------------------------------------------------------------------------------------------------
data_t* Vectorishka::decrease()
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
    data_t* new_data = (data_t*) realloc(data_, new_capa);

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
//!
//!
//!
//!---------------------------------------------------------------------------------------------------------------------
int Vectorishka::pushback(data_t num)
{
    this->Ok();
    assert(std::isfinite(num));

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
//!
//!
//! \return
//!---------------------------------------------------------------------------------------------------------------------
int Vectorishka::Ok()
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
//!
//!
//! \return
//!---------------------------------------------------------------------------------------------------------------------
int Vectorishka::Dump()
{
    assert(file_ != nullptr);
    fprintf(file_, "Vectorishka:\n");
    fprintf(file_, "\tdata_ = %p\n", data_);

    if (data_ != nullptr)
    {
        for (int i = 0; i < capa_; i ++)
        {
            fprintf(file_, "\t\t data_[%d] = %lg\n", i, data_[i]);// Maybe poison, but it's array not stack
        }

    }
    fprintf(file_, "\tsize = %lu", size_);
    if (size_ > capa_)
        fprintf(file_, "(Bad size <= size > capacity)\n");
    fprintf(file_, "\tcapa = %lu\n", capa_);
}


//!---------------------------------------------------------------------------------------------------------------------
//!
//!
//!
//!---------------------------------------------------------------------------------------------------------------------

void* operator new(size_t num, const char* file_name, const char* func_prot, int line)
{
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

void* operator new[](size_t num, const char* file_name, const char* func_prot, int line)
{
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
//!
//!
//!---------------------------------------------------------------------------------------------------------------------
void Vectorishka::swap(Vectorishka &that)
{
    std::swap(data_, that.data_);
    std::swap(size_, that.size_);
    std::swap(capa_, that.capa_);
}

//!---------------------------------------------------------------------------------------------------------------------
//!
//! \param original
//! \return
//! --------------------------------------------------------------------------------------------------------------------
Vectorishka& Vectorishka::operator=(const Vectorishka& rhs) {
    this->Ok();
    Vectorishka copy(rhs);
    this->swap(copy);
    return *this;
}

//!---------------------------------------------------------------------------------------------------------------------
//!
//!
//! \param original
//!---------------------------------------------------------------------------------------------------------------------
Vectorishka::Vectorishka(const Vectorishka &original)
{
    if (original.size_ < 0 || original.capa_ < original.size_ || original.data_ == nullptr)
    {
        error = Constructor__error;
        return;
    }

    size_ = original.size_;
    capa_ = original.capa_;
    data_ = new data_t [original.size_];//(data_t*) calloc(original.size, sizeof(data_t));

    for(int i = 0; i < size_; i++)
        data_[i] = original.data_[i];

    fprintf(file_, "Copy constructor\n");
}

//!---------------------------------------------------------------------------------------------------------------------
//!
//! \param index
//! \return
//!---------------------------------------------------------------------------------------------------------------------
data_t& Vectorishka::operator[](size_t index)
{
    assert(index < capa_);

    if (index + 1 > size_)
        size_ = index + 1;

    return data_[index];
}

//!---------------------------------------------------------------------------------------------------------------------
//!
//!---------------------------------------------------------------------------------------------------------------------
Vectorishka Vectorishka::operator +(const Vectorishka &a)
{
    Vectorishka copy (a);
    copy += *(this);
    return copy;
}

//!---------------------------------------------------------------------------------------------------------------------
//!
//!---------------------------------------------------------------------------------------------------------------------
Vectorishka& Vectorishka::operator +=(const Vectorishka &a)
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
//!
//!---------------------------------------------------------------------------------------------------------------------
Vectorishka::Vectorishka(Vectorishka &&rhs):
    data_(nullptr),
    size_(0),
    error(0),
    capa_(0)
{
    this->swap(rhs);

    fprintf(file_, "Move constructor\n");
}

//!---------------------------------------------------------------------------------------------------------------------
//!
//!---------------------------------------------------------------------------------------------------------------------
Vectorishka& Vectorishka::operator=(Vectorishka &&rhs)
{
    this->swap(rhs);

    fprintf(file_, "Move =\n");
}