#ifndef BTREENODE_H
#define BTREENODE_H

#include "TreeNode.h"

namespace DTlib
{

enum BTNodePos
{
    ANY,
    LEFT,
    RIGHT
};

template <typename T>

class BTreeNode : public TreeNode<T>
{

public:
    BTreeNode<T>* left;
    BTreeNode<T>* right;

    BTreeNode()
    {
        left = nullptr;
        right = nullptr;
    }

    static BTreeNode<T>* NewNode()
    {
        BTreeNode<T>* ret = new BTreeNode<T>();

        if(ret != nullptr)
        {
            ret->m_flag = true;
        }
    }
};

}

#endif // BTREENODE_H
