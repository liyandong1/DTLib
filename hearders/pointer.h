#ifndef POINTER_H
#define POINTER_H

#include "Object.h"

namespace DTlib
{
template <typename T>

class Pointer : public Object
{
protected:
    T* m_pointer;
public:
    Pointer(T* p = nullptr)
    {
        m_pointer = p;
    }
    T* operator -> ()
    {
        return m_pointer;
    }
    T& operator * ()
    {
        return *m_pointer;
    }
    const T* operator -> () const
    {
        return m_pointer;
    }
    const T& operator * () const
    {
        return *m_pointer;
    }
    bool idNull() const
    {
        return (m_pointer == nullptr);
    }
    T* get() const
    {
        return m_pointer;
    }
};

}

#endif // POINTER_H
