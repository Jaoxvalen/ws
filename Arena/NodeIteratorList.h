
#ifndef NodeIteratorList_h
#define NodeIteratorList_h

#include <cstddef>

template<class T>
class Node;

template <class T> 
class NodeIteratorList
{
public:
    Node<T> *nodeRef;
    NodeIteratorList()
    {
        nodeRef=NULL;
    }
    NodeIteratorList(Node<T>* x)
    {
        nodeRef=x;
    }
    
    NodeIteratorList<T>& operator ++()
    {
        if(nodeRef)
        {
            nodeRef=nodeRef->next;
        }
        return *this;
    }
    
    NodeIteratorList<T> operator ++(int)
    {
        NodeIteratorList<T> result(*this);
        ++(*this);
        return result;
    }
    
    bool operator !=(NodeIteratorList<T> x)
    {
        return x.nodeRef!=nodeRef;
    }
    T operator *()
    {
        return nodeRef->dat;
    }
};

#endif NodeIteratorList_h