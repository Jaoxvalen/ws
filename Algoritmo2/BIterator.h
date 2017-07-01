#ifndef BNodeIteratorTree_h
#define BNodeIteratorTree_h

#include <stack>
#include "BNodeState.h"


class Inorder
{
public:
    const short LEFT=0;
    const short ROOT=1;
    const short RIGHT=2;
};

class Preorder
{
public:
    const short LEFT=1;
    const short ROOT=0;
    const short RIGHT=2;
};

class Postorder
{
public:
    const short LEFT=0;
    const short ROOT=2;
    const short RIGHT=1;
};

class ReverseInOrder
{
public:
    const short LEFT=2;
    const short ROOT=1;
    const short RIGHT=0;
};

class ReversePreOrder
{
public:
    const short LEFT=2;
    const short ROOT=0;
    const short RIGHT=1;
};

class ReversePostOrder
{
public:
    const short LEFT=1;
    const short ROOT=2;
    const short RIGHT=0;
};

template <class T, class O>
class BIterator
{
public:
    typedef BNodeState<T> NodeState; 
    std::stack<NodeState*>pila;
    bool isFinish=false;
    O o;
    
    BIterator& operator=(const BIterator<T,O>& c) {
        this->pila=c.pila;
        return *this;
    }
    
    bool operator !=(BIterator<T,O> x)
    {
       return (pila.top()->nodeRef!=x.pila.top()->nodeRef)&&!isFinish;
    }
    
    T operator *()
    {
        return pila.top()->nodeRef->dat;
    }
    
    BIterator<T,O>& operator ++()
    {
        while(!isFinish)
        {
            NodeState *p=pila.top();
            if(p->state==o.LEFT)
            {
                if(p->nodeRef->son[0])
                {
                    pila.push(new NodeState(p->nodeRef->son[0],0));
                }
                p->state++;    
            }
            else if(p->state==o.ROOT)
            {
                p->state++;
                return *this;
            }
            else if(p->state==o.RIGHT)
            {
                if(p->nodeRef->son[1])
                {
                    pila.push(new NodeState(p->nodeRef->son[1],0));
                }
                p->state++;
            }
            else if(p->state==3)
            {

                if(pila.size()>1)
                {
                    pila.pop();
                }
                else
                {
                    isFinish=true;
                }
            }
        }
    }
    BIterator<T,O> operator ++(int)
    {
        BIterator<T,O> result(*this);
        ++(*this);
        return result;
    }
};


#endif //BIterator_h


