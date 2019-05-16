#ifndef TREENODE_H
#define TREENODE_H

#include "Object.h"

namespace DTlib
{

template <typename T>
class TreeNode : public Object
{
protected:
    bool m_flag;

    TreeNode(const TreeNode<T>&);
    TreeNode<T>& operator= (const TreeNode<T>&);

    void* operator new(unsigned int size) throw()
    {
        return Object::operator new(size);
    }
public:
    T value;
    TreeNode<T>* parent;

    TreeNode()
    {
        m_flag = false;
        parent = nullptr;
    }

    bool flag()
    {
        return m_flag;
    }

    virtual ~TreeNode() = 0;
};

template <typename T>
TreeNode<T>::~TreeNode()
{

}

}

#endif // TREENODE_H
