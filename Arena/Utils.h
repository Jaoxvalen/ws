#ifndef Utils_h
#define Utils_h

#include "BNodeIteratorTree.h"

template<class T>
class LessComparator
{
    public:
    bool operator()(T a, T b)
    {
        return a<b;
    }
};

template<class T>
class GreaterComparator
{
    public:
    bool operator()(T a, T b)
    {
        return a>b;
    }
};

#endif //Utils_h