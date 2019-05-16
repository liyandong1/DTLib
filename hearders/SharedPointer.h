#ifndef SHAREDPOINTER_H
#define SHAREDPOINTER_H
#include "Pointer.h"
#include "Exception.h"

namespace DTlib
{
template <typename T>
class SharedPointer : public Pointer<T>
{
protected:
    int* m_ref;
public:
    SharedPointer(T* p = nullptr) : m_ref(nullptr)
    {
        if(p)
        {
            this->m_ref = static_cast<int*>(malloc(sizeof(int)));
            if(this->m_ref)
            {
                *(this->m_ref) = 1;
                this->m_pointer = p;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create SharedPointer Object...");

            }
        }
    }
    SharedPointer(const SharedPointer<T>& obj)
    {
        this->m_ref = obj.m_ref;
        this->m_pointer = obj.m_pointer;

        if(this->m_ref)
        {
            (*this->m_ref)++;
        }
    }
    SharedPointer<T>& operator = (const SharedPointer<T>& obj)
    {
        if(this != &obj)
        {
            clear();
            this->m_ref = obj.m_ref;
            this->m_pointer = obj.m_pointer;

            if(this->m_ref)
            {
                (*this->m_ref)++;
            }
        }
        return *this;
    }
    void clear()
    {
        T* toDel = this->m_pointer;
        int* ref = this->m_ref;

        this->m_pointer = nullptr;
        this->m_ref = nullptr;

        if(ref)
        {
            (*ref)--;
            if(*ref == 0)
            {
                free(ref);
                delete toDel;
            }
        }
    }
    ~SharedPointer()
    {
        clear();
    }
};

template <typename T>
bool operator == (const SharedPointer<T>& l, const SharedPointer<T>& r)
{
    return (r.get() == l.get());
}

template <typename T>
bool operator != (const SharedPointer<T>& l, const SharedPointer<T>& r)
{
    return !(r == l);
}

}


#endif // SHAREPOINTER_H
