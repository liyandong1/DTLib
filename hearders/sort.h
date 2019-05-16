#ifndef SORT_H
#define SORT_H

#include "Object.h"
#include <iostream>
#include "Array.h"

using namespace std;
namespace DTlib
{

class Sort : public Object
{
private:
    Sort();
    Sort(const Sort& );
    Sort& operator = (const Sort& );

    template <typename T>

    static void Swap(T& a, T& b)
    {
        T c(a);
        a = b;
        b = c;
    }
    template <typename T>
    static void merge(T array[], T helper[], int left, int mid, int right, bool min2max = true)
    {
        int i = left;
        int j = mid + 1;
        int k = left;

        while((i <= mid) && (j <= right))
        {
            if(min2max ? (array[i] < array[j]) : (array[i] > array[j]))
            {
                helper[k++] = array[i++];
            }
            else
            {
                helper[k++] = array[j++];
            }
        }

        while(i <= mid)
        {
            helper[k++] = array[i++];
        }
        while(j <= right)
        {
            helper[k++] = array[j++];
        }

        for(i = left; i <= right; i++)
        {
            array[i] = helper[i];
        }
    }

    template <typename T>
    static void mergeSort(T array[], T helper[], int left, int right, bool min2max = true)
    {
        if(left == right)
        {
            return;
        }
        else
        {
            int mid = left + (right - left) / 2;
            mergeSort(array, helper, left, mid, min2max);
            mergeSort(array, helper, mid + 1, right, min2max);
            merge(array, helper, left, mid, right, min2max);
        }
    }

    template <typename T>
    static int Partition(T array[], int left, int right, bool min2max = true)
    {
            T pv = array[left];

            while(left < right)
            {
                    while((left < right) && (min2max ? (array[right] >= pv) : (array[right] <= pv)))
                    {
                            right--;
                    }
                    swap(array[right], array[left]);

                    while((left < right) && (min2max ? (array[left] <= pv) : (array[left] >= pv)))
                    {
                            left++;
                    }
                    swap(array[right], array[left]);

                    array[left] = pv;

            }
            return left;
    }

    template <typename T>
    static void Quick_(T array[], int left, int right, bool min2max = true)
    {
            int pivot;

            if(left < right)
            {
                    pivot = Partition(array, left, right, min2max);

                    Quick_(array, left, pivot -1, min2max);
                    Quick_(array, pivot + 1, right, min2max);
            }
    }

public:
    template <typename T>
    static void Select(T array[], int len, bool min2max = true)
    {
        for(int i = 0; i < len; i++)
        {
            int min = i;
            for(int j = i + 1; j < len; j++)
            {
                if(min2max ? (array[min] > array[j]) : (array[min] < array[j]))
                {
                    min = j;
                }
            }
            if(min != i)
            {
                swap(array[i], array[min]);
            }
        }
    }

    template <typename T>
    static void Insert(T array[], int len, bool min2max = true)
    {
            for(int i = 1; i < len; i++)
            {
                    int k = i;
                    T e = array[i];
                    for(int j = i - 1; (j >= 0) && ( min2max ? (array[j] > e) : (array[j] < e)); j--)
                    {
                        array[j + 1] = array[j];
                        k = j;
                    }
                    if(i != k)
                    {
                            array[k] = e;
                    }
            }
    }

    template <typename T>
    static void Bubble(T array[], int len, bool min2max)
    {
            for(int i = 0; i < len; i++)
            {
                    bool Exchange = true;
                    for(int j = len -1; (j > i) && (Exchange); j--)
                    {
                            Exchange = false;
                            if(min2max ? (array[j] < array[j - 1]) : (array[j] < array[j - 1]))
                            {
                                    swap(array[j], array[j - 1]);

                                    Exchange = true;
                            }
                    }
            }
    }

    template <typename T>
    static void Shell(T array[], int len, bool min2max)
    {
            int d = len;
            do
            {
                    d = d / 3 + 1;

                    for(int i = d; i < len; i += d)
                    {
                            int k = i;
                            T e = array[i];
                    for(int j = i - d; j >= 0; j -= d)
                    {
                            if(min2max ? (array[j] > e) : (array[j] < e))
                            {
                                    array[j + d] = array[j];
                                    k = j;
                            }
                            else
                            {
                                    break;
                            }
                    }
                    if(i != k)
                    {
                            array[k] = e;
                    }
                    }

            }while(d > 1);
    }

    template <typename T>
    static void Merge(T array[], int len, bool min2max = true)
    {
        T* helper = new T[len];

        if(helper != nullptr)
        {
            mergeSort(array, helper, 0, len - 1, min2max);
        }

        delete[] helper;
    }

    template <typename T>
    static void Quick(T array[], int len, bool min2max = true)
    {
            Quick_(array, 0, len - 1, min2max);
    }

    template <typename T>
    static void Select(Array<T>& array, bool min2max = true)
    {
        Select(array.array(), array.length(), min2max);
    }

    template <typename T>
    static void Bubble(Array<T>& array, bool min2max = true)
    {
        Bubble(array.array(), array.length(), min2max);
    }

    template <typename T>
    static void Insert(Array<T>& array, bool min2max = true)
    {
        Insert(array.array(), array.length(), min2max);
    }

    template <typename T>
    static void Shell(Array<T>& array, bool min2max = true)
    {
        Shell(array.array(), array.length(), min2max);
    }

    template <typename T>
    static void Merge(Array<T>& array, bool min2max = true)
    {
        Merge(array.array(), array.length(), min2max);
    }

    template <typename T>
    static void Quick(Array<T>& array, bool min2max = true)
    {
        Quick(array.array(), array.length(), min2max);
    }

};

}

#endif // SORT_H
