#ifndef OBJECT_H
#define OBJECT_H


namespace DTlib
{
class Object
{
public:
    void* operator new (unsigned int size) throw();
    void operator delete (void* p);
    void* operator new[] (unsigned int size) throw();
    void operator delete[] (void*);
    bool operator == (const Object& obj);
    bool operator != (const Object& obj);
    virtual ~Object() = 0;
};
}

#endif // OBJECT_H
