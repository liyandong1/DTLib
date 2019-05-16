#ifndef SMARTPOINT_H
#define SMARTPOINT_H

#include "Pointer.h"

namespace DTlib
{
template <typename T>
class SmartPoint : public Pointer<T>
{
public:
    SmartPoint(T* p = NULL) : Pointer<T>(p)
    {

    }
    SmartPoint(const SmartPoint<T>& obj) : Pointer<T>(nullptr)
    {
        this->m_pointer = obj.m_pointer;

        const_cast<SmartPoint<T>&>(obj).m_pointer = NULL;
        std::cout << "SmartPoint(const SmartPoint<T>& obj)" << std::endl;

    }
    SmartPoint<T>& operator = (const SmartPoint<T>& obj)
    {
        if(this != &obj)
        {
            T* p = this->m_pointer;

            this->m_pointer = obj.m_pointer;
            const_cast<SmartPoint<T>&>(obj).m_pointer = NULL;
            delete p;
            std::cout << "SmartPoint<T>& operator = (const SmartPoint<T>& obj)" << std::endl;
        }
        return *this;
    }
    ~SmartPoint()
    {
        delete this->m_pointer;
    }

};
}
#endif // SMARTPOINT_H
