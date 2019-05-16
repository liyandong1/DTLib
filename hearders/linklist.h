#ifndef LINKLIST_H
#define LINKLIST_H

#include "List.h"
#include "Exception.h"
#include <iostream>
namespace DTlib
{

template <typename T>

class LinkList : public List<T>
{
protected:
    struct Node : Object
    {
        T value;
        Node* next;
    };
    //mutable Node m_header;


    mutable struct : public Object
    {
        char reserved[sizeof(T)];
        Node* next;
    }m_header;

    int m_length;
    int m_step;
    Node* m_current;

    Node* position(int i) const
    {
        Node* ret = reinterpret_cast<Node*>(&m_header);
        for(int p = 0; p < i; p++)
        {
            ret = ret->next;
        }
        return ret;
    }
    virtual Node* create()
    {
        return new Node();
    }
    virtual void destory(Node* pn)
    {
        //std::cout << "virtual void destory(Node* pn)" << std::endl;
        delete pn;
    }
public:
    LinkList()
    {
        m_header.next = NULL;
        m_length = 0;
        m_step = 1;
        m_current = NULL;
    }
    bool insert(const T& e)
    {
        return insert(m_length, e);
    }
    bool insert(int i, const T& e)
    {


        bool ret = ((i >= 0) && (i <= m_length));
        if(ret)
        {
            Node* node =  create();

            //std::cout <<"Location : " << i << std::endl;
            if(node != NULL)
            {
                /*
                Node* current = &m_header;
                for(int p = 0; p < i; p++)
                {
                    current = current->next;
                }
                */
                //node->next = current->next;
                //原来是：node->next = position(i)->next;
                Node* current = position(i);//新的

                node->value = e;

                node->next = current->next;
                //current->next = node;
                //原来： position(i)->next = node;
                current->next = node;//新的
                m_length++;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No Memory to insert");
            }
        }
        //std::cout << "===============" << std::endl;
        return ret;
    }
    bool remove(int i)
    {
        bool ret = ((i >= 0) && (i < m_length));
        if(ret)
        {
            /*
            Node* current = &m_header;
            for(int p; p < i; p++)
            {
                current = current->next;
            }
            */
            //Node* toDel = current->next;
            Node* current  =position(i);//改了的，原来是：toDel = position(i)->next
            Node* toDel = current->next;
            //current->next = toDel->next;
            if(m_current == toDel)
            {
                m_current = toDel->next;
            }
            current->next = toDel->next;
            //原来是：position->next = toDel->next;

            m_length--;
            destory(toDel);
        }
        return ret;
    }
    bool set(int i, const T& e)
    {
        bool ret = ((i >= 0) && (i < m_length));

        if(ret)
        {
            /*
            Node* current = &m_header;

            for(int p = 0; p < i; p++)
            {
                current = current->next;
            }
            */
            //(current->next)->value = e;
            (position(i)->next)->value = e;
        }
        return ret;
    }
    virtual T get(int i) const
    {
        T ret;

        if(get(i, ret))
        {
            return ret;
        }
        else
        {
            THROW_EXCEPTION(IndexOutOfBoundsException,"Invalid Parameter i to get element");
        }
        return ret;
    }
    bool get(int i, T& e) const
    {
        bool ret = ((i >= 0) && (i < m_length));

        if(ret)
        {
            /*
            Node* current = &m_header;

            for(int p = 0; p < i; p++)
            {
                current = current->next;
            }
            */
            //e = current->next->value;
            e = position(i)->next->value;
        }
        return ret;
    }
    int find(const T& e) const
    {
        int ret = -1;
        int i = 0;
        Node* node = m_header.next;

        while(node)
        {
            if(node->value == e)
            {
                ret = i;
                break;
            }
            else
            {
                node = node->next;
                i++;
            }
        }
        return ret;
    }
    int length() const
    {
        return m_length;
    }
    void clear()
    {
        while(m_header.next)
        {
            Node* toDel = m_header.next;
            m_header.next = toDel->next;
            m_length--;
            destory(toDel);
        }

       // m_length = 0;
    }
    virtual bool move(int i, int step = 1)
    {
        bool ret = ((i >= 0) && (i < m_length) && (step > 0));
        if(ret)
        {
            m_current = position(i)->next;
            m_step = step;
        }
        return ret;
    }
    virtual bool end()
    {
        return (m_current == nullptr);
    }
    virtual T current()
    {
        if(!end())
        {
            return m_current->value;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No Value In Current...");
        }
    }
    virtual bool next()
    {
        int i = 0;
        while((i < m_step) && (!end()))
        {
            m_current = m_current->next;
            i++;
        }
        return (i == m_step);
    }
    ~LinkList()
    {
        clear();
    }
};
}

#endif // LINKLIST_H
