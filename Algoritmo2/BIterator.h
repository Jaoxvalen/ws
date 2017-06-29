#ifndef BNodeIteratorTree_h
#define BNodeIteratorTree_h

#include <stack>
#include "BNodeState.h"
#include "BIteratorTypes.h"



template<class T>
class Inorder
{
    BIterator<T> operator ()(BIterator<T> &self)
    {
        return self;
    }
};


template <class T>
class BIterator
{
public:
    typedef BNodeState<T> NodeState; 
    std::stack<NodeState*>pila;
    bool isFinish=false;
    
    BIterator& operator=(const BIterator<T>& c) {
        this->pila=c.pila;
        return *this;
    }
    
    bool operator !=(BIterator<T> x)
    {
       return (pila.top()->nodeRef!=x.pila.top()->nodeRef)&&!isFinish;
    }
    
    T operator *()
    {
        return pila.top()->nodeRef->dat;
    }
    
    BIterator<T>& operator ++()
    {
        while(!isFinish)
        {
            NodeState *p=pila.top();
            if(p->state==0)
            {
                if(p->nodeRef->son[0])
                {
                    pila.push(new NodeState(p->nodeRef->son[0],0));
                }
                p->state++;    
            }
            else if(p->state==1)
            {
                pila.pop();
                if(p->nodeRef->son[1])
                {
                    pila.push(new NodeState(p->nodeRef->son[1],0));
                }
                p->state++;
                pila.push(p);
            }
            else if(p->state==2)
            {
                p->state++;
                return *this;
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
    BIterator<T> operator ++(int)
    {
        BIterator<T> result(*this);
        ++(*this);
        return result;
    }
};


#endif //BIterator_h


