#ifndef BTREE_H
#define BTREE_H

#include "Tree.h"
#include "BTreeNode.h"
#include "Exception.h"
#include "LinkQueue.h"
#include <iostream>
#include "DynamicArray.h"

using namespace std;
namespace DTlib
{

enum BTTraversal
{
    PreOrder,
    InOrder,
    PostOrder,
    LevelOrder
};

template <typename T>
class BTree : public Tree<T>
{
protected:
    LinkQueue<BTreeNode<T>*> m_queue;

    virtual BTreeNode<T>* find(BTreeNode<T>* node, T value) const
    {
        BTreeNode<T>* ret = nullptr;

        if(node != nullptr)
        {
            if(node->value == value)
            {
                ret = node;
            }
            else
            {
                if(ret == nullptr)
                {
                   ret = find(node->left, value);
                }
                if(ret == nullptr)
                {
                    ret = find(node->right, value);
                }
            }
        }
        return ret;
    }


    virtual BTreeNode<T>* find(BTreeNode<T>* node, BTreeNode<T>* obj) const
    {
        BTreeNode<T>* ret = nullptr;

        if(node == obj)
        {
            ret = node;
        }
        else
        {
            if(node != nullptr)
            {
                if(ret == nullptr)
                {
                    ret = find(node->left, obj);
                }
                if(ret == nullptr)
                {
                    ret = find(node->right, obj);
                }
            }
        }

        return ret;
    }

    virtual bool insert(BTreeNode<T>* n, BTreeNode<T>* np, BTNodePos pos)
    {
        bool ret = true;

        if(pos == ANY)
        {
            if(np->left == nullptr)
            {
                np->left = n;
            }
            else if(np->right == nullptr)
            {
                np->right = n;
            }
            else
            {
                ret = false;
            }
        }
        else if(pos == LEFT)
        {
            if(np->left == nullptr)
            {
                np->left = n;
            }
            else
            {
                ret = false;
            }
        }
        else if(pos == RIGHT)
        {
            if(np->right == nullptr)
            {
                np->right = n;
            }
            else
            {
                ret = false;
            }
        }
        else
        {
            ret = false;
        }
        return ret;
    }

    //void remove(BTreeNode<T>* node, BTree<T>*& ret)
    void remove(BTreeNode<T>* node, BTree<T>*& ret)
    {
        ret = new BTree<T>();

        if(ret == nullptr)
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create new tree ...");
        }
        else
        {
            if(root() == node)
            {
                this->m_root = nullptr;
            }
            else
            {
                BTreeNode<T>* parent = dynamic_cast<BTreeNode<T>*>(node->parent);

                if(parent->left == node)
                {
                    parent->left = nullptr;
                }
                else if(parent->right == node)
                {
                    parent->right = nullptr;
                }
                node->parent = nullptr;
            }
            ret->m_root = node;
        }
    }

    virtual void free(BTreeNode<T>* node)
    {
        if(node != nullptr)
        {
            free(node->left);
            free(node->right);
            //cout << node->value << endl;
            if(node->flag())
            {
                delete node;
            }
        }
    }

    int count(BTreeNode<T>* node) const
    {
        /*
        int ret = 0;

        if(node != nullptr)
        {
            ret = count(node->left) + count(node->right) + 1;
        }
        */

        return (node != nullptr) ? (count(node->left) + count(node->right) + 1) : (0);
    }

    int height(BTreeNode<T>* node) const
    {
        int ret = 0;

        if(node != nullptr)
        {
            int lh = height(node->left);
            int rh = height(node->right);

            ret = (lh > rh ? lh : rh) + 1;
        }
        return ret;
    }

    int degree(BTreeNode<T>* node) const
    {
        int ret = 0;

        if(node != nullptr)
        {
            BTreeNode<T>* child[] = {node->left, node->right};
            ret = (!!node->left + !!node->right);

            for(int i = 0; (i < 2) && (ret < 2); i++)
            {
                int d = degree(child[i]);

                if(ret < d)
                {
                    ret = d;
                }
            }
            /*
            if(ret < 2)
            {
                int dl = degree(node->left);
                if(dl > ret)
                {
                    ret = dl;
                }
            }
            if(ret < 2)
            {
                int dr = degree(node->right);

                if(dr > ret)
                {
                    ret = dr;
                }
            }
            */

            /*
            int dl = degree(node->left);
            int dr = degree(node->right);

            ret = (!!node->left + !!node->right);

            if(ret < dl)
            {
                ret = dl;
            }
            if(ret < dr)
            {
                ret = dr;
            }
            */

        }

        return ret;
    }

    void preOrderTraversal(BTreeNode<T>* node, LinkQueue<BTreeNode<T>*>& queue)
    {
        if(node != nullptr)
        {
            queue.add(node);

            preOrderTraversal(node->left, queue);

            preOrderTraversal(node->right, queue);
        }
    }

    void inOrderTraversal(BTreeNode<T>* node, LinkQueue<BTreeNode<T>*>& queue)
    {
        if(node != nullptr)
        {

            inOrderTraversal(node->left, queue);

            queue.add(node);

            inOrderTraversal(node->right, queue);
        }
    }

    void postOrderTraversal(BTreeNode<T>* node, LinkQueue<BTreeNode<T>*>& queue)
    {
        if(node != nullptr)
        {

            postOrderTraversal(node->left, queue);

            postOrderTraversal(node->right, queue);

            queue.add(node);

        }
    }

    void levelOrderTraversal(BTreeNode<T>* node, LinkQueue<BTreeNode<T>*>& queue)
    {
        if(node != nullptr)
        {
            LinkQueue<BTreeNode<T>*> tmp;
            tmp.add(node);

            while(tmp.length() > 0)
            {
                BTreeNode<T>* n = tmp.front();

                if(n->left != nullptr)
                {
                    tmp.add(n->left);
                }
                if(n->right != nullptr)
                {
                    tmp.add(n->right);
                }
                tmp.remove();

                queue.add(n);
            }
        }
    }

    BTreeNode<T>* clone(BTreeNode< T >* node) const
    {
        BTreeNode<T>* ret = nullptr;

        if(node != nullptr)
        {
            ret = BTreeNode<T>::NewNode();

            if(ret != nullptr)
            {
                ret->value = node->value;

                ret->left = clone(node->left);

                ret->right = clone(node->right);

                if(ret->left != nullptr)
                {
                    ret->left->parent = ret;
                }
                if(ret->right != nullptr)
                {
                    ret->right->parent = ret;
                }
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create new node ...");
            }
        }
        return ret;
    }

    bool equal(BTreeNode<T>* lh, BTreeNode<T>* rh) const
    {
        if(lh == rh)
        {
            return true;
        }
        else if((lh != nullptr) && (rh != nullptr))
        {
            return ((lh->value == rh->value) && (equal(lh->left, rh->left)) && (equal(lh->right, rh->right)));
        }
        else
        {
            return false;
        }
    }

    BTreeNode<T>* add(BTreeNode<T>* lh, BTreeNode<T>* rh) const
    {
        BTreeNode<T>* ret = nullptr;

        if( (lh == nullptr) && (rh != nullptr) )
        {
            ret = clone(rh);
        }
        else if( (lh != nullptr) && (rh == nullptr) )
        {
            ret = clone(lh);
        }
        else if((lh != nullptr) && (rh != nullptr))
        {
            ret = BTreeNode<T>::NewNode();

            if(ret != nullptr)
            {
                ret->value = lh->value + rh->value;

                ret->left = add(lh->left, rh->left);

                ret->right = add(lh->right, rh->right);

                if(ret->left != nullptr)
                {
                    ret->left->parent = ret;
                }
                if(ret->right != nullptr)
                {
                    ret->right->parent = ret;
                }
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create new node ...");
            }
        }

        return ret;
    }

    void traversal(BTTraversal order, LinkQueue<BTreeNode<T>*>& queue)
    {
        switch (order)
        {
        case PreOrder:
            preOrderTraversal(root(), queue);
            break;
        case InOrder:
            inOrderTraversal(root(), queue);
            break;
        case PostOrder:
            postOrderTraversal(root(), queue);
            break;
        case LevelOrder:
            levelOrderTraversal(root(), queue);
            break;
        default:
            THROW_EXCEPTION(InvalidParameterException, "Parameter order is invalid ...");
            break;
        }
    }

    BTreeNode<T>* connect(LinkQueue<BTreeNode<T>*>& queue)
    {
        BTreeNode<T>* ret = nullptr;

        if(queue.length() > 0)
        {
            ret = queue.front();
            BTreeNode<T>* slider = queue.front();

            queue.remove();

            slider->left = nullptr;

            while (queue.length() > 0)
            {
                slider->right = queue.front();

                queue.front()->left = slider;

                slider = queue.front();

                queue.remove();
            }
            slider->right = nullptr;
        }

        return ret;
    }

public:
    bool insert(TreeNode<T>* node)
    {
        return insert(dynamic_cast<BTreeNode<T>*>(node), ANY);
    }

    virtual bool insert(BTreeNode<T>* node, BTNodePos pos)
    {
        bool ret = true;

        if(node != nullptr)
        {
            if(this->m_root == nullptr)
            {
                node->parent = nullptr;

                this->m_root = node;
            }
            else
            {
                BTreeNode<T>* np = find(node->parent);

                if(np != nullptr)
                {
                    ret = insert(dynamic_cast<BTreeNode<T>*>(node), np, pos);
                }
                else
                {
                    THROW_EXCEPTION(InvalidParameterException, "Invalid parent tree node ...");
                }
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Parameter node can't be nullptr ...");
        }

        return ret;
    }

    bool insert(const T& value, TreeNode<T>* parent)
    {
        return insert(value, parent, ANY);
    }

    virtual bool insert(const T& value, TreeNode<T>* parent, BTNodePos pos)
    {
        bool ret = true;
        BTreeNode<T>* node = BTreeNode<T>::NewNode();

        if(node == nullptr)
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create new node ...");
        }
        else
        {
            node->value = value;
            node->parent = parent;

            ret = insert(node, pos);

            if(!ret)
            {
                delete node;
            }
        }
        return ret;
    }

    SharedPointer< Tree<T> > remove(const T& value)
    {
        BTree<T>* ret = nullptr;

        BTreeNode<T>* node = find(value);

        if(node == nullptr)
        {
            THROW_EXCEPTION(InvalidParameterException, "Can't find the tree node via value ...");
        }
        else
        {
            remove(node, ret);

            m_queue.clear();
        }

        return ret;
    }

    SharedPointer< Tree<T> > remove(TreeNode<T>* node)
    {
        BTree<T>* ret = nullptr;

        node = find(node);

        if(node == nullptr)
        {
            THROW_EXCEPTION(InvalidParameterException, "Parameter node is invalid ...");
        }
        else
        {
            remove(dynamic_cast<BTreeNode<T>*>(node), ret);

            m_queue.clear();
        }

        return ret;
    }

    BTreeNode<T>* find(const T& value) const
    {
        return find(root(), value);
    }

    BTreeNode<T>* find(TreeNode<T>* node) const
    {
        return find(root(), dynamic_cast<BTreeNode<T>*>(node));
    }

    BTreeNode<T>* root() const
    {
        return dynamic_cast<BTreeNode<T>*>(this->m_root);
    }

    int degree() const
    {
        return degree(root());
    }

    int count() const
    {
        return count(root());
    }

    int height() const
    {
        return height(root());
    }

    void clear()
    {
        free(root());

        m_queue.clear();

        this->m_root = nullptr;
    }

    bool begin()
    {
        bool ret = (root() != nullptr);

        if(ret)
        {
            m_queue.clear();
            m_queue.add(root());
        }

        return ret;
    }

    bool end()
    {
        return (m_queue.length() == 0);
    }

    bool next()
    {
        bool ret = (m_queue.length() > 0);

        if(ret)
        {
            BTreeNode<T>* node = m_queue.front();

            m_queue.remove();

            if(node->left != nullptr)
            {
                m_queue.add(node->left);
            }
            if(node->right != nullptr)
            {
                m_queue.add(node->right);
            }

        }

        return ret;
    }

    T current()
    {
        if(!end())
        {
            return m_queue.front()->value;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No value at current position ...");
        }
    }

    SharedPointer<Array<T>> traversal(BTTraversal order)
    {
        DynamicArray<T>* ret = nullptr;
        LinkQueue<BTreeNode<T>*> queue;

        traversal(order, queue);
        /*
        switch (order)
        {
        case PreOrder:
            preOrderTraversal(root(), queue);
            break;
        case InOrder:
            inOrderTraversal(root(), queue);
            break;
        case PostOrder:
            postOrderTraversal(root(), queue);
            break;
        default:
            THROW_EXCEPTION(InvalidParameterException, "Parameter order is invalid ...");
            break;
        }
        */
        ret = new DynamicArray<T>(queue.length());

        if(ret != nullptr)
        {
            for(int i = 0; i < ret->length(); i++, queue.remove())
            {
                ret->set(i, queue.front()->value);
            }
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create array ...");
        }
        return ret;
    }

    SharedPointer<BTree<T>> clone() const
    {
        BTree<T>* ret = new BTree<T>();

        if(ret != nullptr)
        {
            ret->m_root = clone(root());
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create new BTree ...");
        }
        return ret;
    }

    bool operator== (const BTree<T>& btree)
    {
        return (equal(root(), btree.root()));
    }

    bool operator !=(const BTree<T>& btree)
    {
        return !(*this == btree);
    }

    SharedPointer< BTree<T> > add(const BTree<T>& btree) const
    {
        BTree<T>* ret = new BTree<T>();

        if(ret != nullptr)
        {
            ret->m_root = add(root(), btree.root());
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create new tree ...");
        }

        return ret;
    }

    BTreeNode<T>* thread(BTTraversal order)
    {
        BTreeNode<T>* ret = nullptr;

        LinkQueue<BTreeNode<T>*> queue;

        traversal(order, queue);

        ret = connect(queue);

        this->m_root = nullptr;

        m_queue.clear();

        return ret;
    }



    ~BTree()
    {
        clear();
    }

};

}

#endif // BTREE_H
