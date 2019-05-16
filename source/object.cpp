#include "Object.h"
#include <cstdlib>
#include <iostream>

namespace DTlib
{
void* Object::operator new (unsigned int size) throw()
{
    //std::cout << "void* Oject::operator new (unsigned int size) throw() : " << size << std::endl;
    return malloc(size);
}
void Object::operator delete (void* p)
{
    //std::cout << "void Object::operator delete (void* p)" << std::endl;
    free(p);
}
void* Object::operator new[] (unsigned int size) throw()
{
    //std::cout << "void Object::operator new[] (unsigned int size) throw() : " << size << std::endl;
    return malloc(size);
}
void Object::operator delete[] (void* p)
{
    //std::cout << "void Object::operator delete[] (void* p)" << std::endl;
    free(p);
}
bool Object::operator == (const Object& obj)
{
    return (this == &obj);
}
bool Object::operator !=(const Object& obj)
{
    return (this != &obj);
}
Object::~Object()
{

}
}
