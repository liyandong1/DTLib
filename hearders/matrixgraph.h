#ifndef MATRIXGRAPH_H
#define MATRIXGRAPH_H

#include "Graph.h"
#include "DynamicArray.h"
#include "Exception.h"


namespace DTlib
{

template <int N, typename V, typename E>
class MatrixGraph : public Graph<V, E>
{
protected:
    V* m_vertexes[N];
    E* m_edge[N][N];
    int m_eCount;
public:
    MatrixGraph()
    {
        for(int i = 0; i < vCount(); i++)
        {
            m_vertexes[i] = nullptr;
            for(int j = 0; j < vCount(); j++)
            {
                m_edge[i][j] = nullptr;
            }
        }
        m_eCount = 0;
    }

    V getVertex(int i)
    {
        V ret;

        if(!getVertex(i, ret))
        {
            THROW_EXCEPTION(InvalidParameterException, "Index i...");
        }

        return ret;
    }

    bool getVertex(int i, V& value)
    {

        bool ret = ((i >= 0) && (i < vCount()));
        if(ret)
        {
            if(m_vertexes[i] != nullptr)
            {
                value = *(m_vertexes[i]);
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException, "No value assigned to this vertex ...");
            }
        }
        return ret;
    }

    bool setVertex(int i, const V& value)
    {
         bool ret = ((i >= 0) && (i < vCount()));

         if(ret)
         {
             V* data = m_vertexes[i];

             if(data == nullptr)
             {
                 data = new V();
             }
             if(data != nullptr)
             {
                 *data = value;

                 m_vertexes[i] = data;
             }
             else
             {
                 THROW_EXCEPTION(NoEnoughMemoryException, "No memory to story new vertex ...");
             }
         }
         return ret;
    }

    SharedPointer< Array<int> > getAdjacent(int i)
    {
        DynamicArray<int>* ret = nullptr;

        if( (i >= 0) && (i < vCount()))
        {
            int n = 0;

            for(int j = 0; j < vCount(); j++)
            {
                if(m_edge[i][j] != nullptr)
                {
                    n++;
                }
            }

            ret = new DynamicArray<int>(n);

            if(ret != nullptr)
            {
                for(int j = 0, k = 0; j < vCount(); j++)
                {
                    if(m_edge[i][j] != nullptr)
                    {
                        ret->set(k++, j);
                    }
                }
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create new ret object ...");
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Index i is invalid ...");
        }
        return ret;
    }

    bool isAdjacent(int i, int j)
    {
        return (i >= 0) && (i < vCount()) && (j >= 0) && (j < vCount()) && (m_edge[i][j] != nullptr);
    }

    E getEdge(int i, int j)
    {
        E ret;

        if(!getEdge(i, j, ret))
        {
            THROW_EXCEPTION(InvalidParameterException, "Index<i, j> is invalid ...");
        }

        return ret;
    }

    bool getEdge(int i, int j, E& value)
    {
        bool ret = ( (i >= 0) && (i < vCount())) &&
                   ( (j >= 0) && (j < vCount()));

        if(ret)
        {
            if(m_edge[i][j] != nullptr)
            {
                value = *(m_edge[i][j]);
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException, "No value assigned to this edge ...");
            }
        }
        return ret;
    }

    bool setEdge(int i, int j, const E& value)
    {
        bool ret = ( (i >= 0) && (i < vCount())) &&
                   ( (j >= 0) && (j < vCount()));

        if(ret)
        {
            E* ne = m_edge[i][j];

            if(ne == nullptr)
            {
                ne = new E();

                if(ne != nullptr)
                {
                    *ne = value;

                    m_edge[i][j] = ne;

                    m_eCount++;
                }
                else
                {
                    THROW_EXCEPTION(NoEnoughMemoryException, "No memory to store new edge value ...");
                }
            }
            else
            {
                *ne = value;
            }
        }
        return ret;
    }

    bool removeEdge(int i, int j)
    {
        bool ret = ( (i >= 0) && (i < vCount())) &&
                   ( (j >= 0) && (j < vCount()));

        if(ret)
        {
            E* toDel = m_edge[i][j];

            m_edge[i][j] = nullptr;

            if(toDel != nullptr)
            {
                m_eCount--;

                delete toDel;
            }
        }
        return ret;
    }
    int vCount()
    {
        return N;
    }

    int eCount()
    {
        return m_eCount;
    }

    int OD(int i)
    {
        int ret = 0;

        if( (i >= 0) && (i < vCount()))
        {
            for(int j = 0; j < vCount(); j++)
            {
                if(m_edge[i][j] != nullptr)
                {
                    ret++;
                }
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Index i is invalid ... ");
        }
        return ret;
    }

    int ID(int i)
    {
        int ret = 0;

        if( (i >= 0) && (i < vCount()))
        {
            for(int j = 0; j < vCount(); j++)
            {
                if(m_edge[j][i] != nullptr)
                {
                    ret++;
                }
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Index i is invalid ... ");
        }
        return ret;
    }

    ~MatrixGraph()
    {
        for(int i = 0; i < vCount(); i++)
        {
            m_vertexes[i] = nullptr;
            for(int j = 0; j < vCount(); j++)
            {
                delete m_edge[i][j];
            }
            delete m_vertexes[i];
        }
        m_eCount = 0;
    }
};

}

#endif // MATRIXGRAPH_H
