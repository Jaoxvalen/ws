#ifndef BNodeIteratorTree_h
#define BNodeIteratorTree_h

#include <stack>
#include "BNodeState.h"


template<class T>
class IteratorTree
{
public:
    typedef BNodeState<T> NodeState;
    std::stack<NodeState*>pila;
    BNode<T>* actual;
    IteratorTree(){}
    IteratorTree(BNode<T> *nodeRef)
    {
        NodeState* e=new NodeState(nodeRef, 0);
        pila.push(e);
    }
    virtual IteratorTree<T>& iterar()
    {
        return *this;
    }
    T getValor()
    {
        return actual->dat;
    }
    
    IteratorTree<T>& operator ++()
    {
        return iterar();
    }
    IteratorTree<T> operator ++(int)
    {
        IteratorTree result(*this);
        ++(*this);
        return result;
    }
    bool operator !=(IteratorTree<T> x)
    {
        NodeState *b=x.pila.top();
        if(pila.size()==0)
        {
            return NULL!=b->nodeRef;
        }
        else
        {
            return actual!=b->nodeRef;
        }
        
    }
    T operator *()
    {
        return getValor();
    }
    
};


template<class T>
class IteratorInOrder: public IteratorTree<T>
{
public:
    IteratorInOrder& operator=(const IteratorTree<T>& c) {
        this->pila=c.pila;
        this->actual=c.actual;
        (*this)++;
        return *this;
    }
    IteratorInOrder():IteratorTree<T>(){}
    IteratorInOrder(BNode<T> *nodeRef):IteratorTree<T>(nodeRef)
    {
        NodeState* e=new NodeState(nodeRef, 0);
        this->pila.push(e);
    }
    typedef BNodeState<T> NodeState;
    IteratorTree<T>& iterar()
    {
        bool imprime=true;
        
        while(imprime && !(this->pila).empty())
        {
            NodeState *e=(this->pila).top();
            if(e->state==0)
            {
                e->state=1;//va a bajar a la izquierda
                if(e->nodeRef->son[0])
                {
                    NodeState* apilar=new NodeState(e->nodeRef->son[0],0);
                    (this->pila).push(apilar);
                }
            }
            else if(e->state==1)
            {
                e->state=2;//va a bajar a la derecha
                (this->pila).pop();//hacemos espacio para el hijo
                if(e->nodeRef->son[1])
                {
                    NodeState* apilar=new NodeState(e->nodeRef->son[1],0);
                    (this->pila).push(apilar);//metemos el hijo
                }
                (this->pila).push(e);//metemos en la cabeza al padre
                this->actual=e->nodeRef;
                imprime=false;
            }
            else if(e->state==2)
            {
                (this->pila).pop();
            }
        }
        return *this;
    }
    
};

template<class T>
class IteratorPostOrder: public IteratorTree<T>
{
public:
    IteratorPostOrder& operator=(const IteratorTree<T>& c) {
        this->pila=c.pila;
        this->actual=c.actual;
        (*this)++;
        return *this;
    }
    IteratorPostOrder():IteratorTree<T>(){}
    IteratorPostOrder(BNode<T> *nodeRef):IteratorTree<T>(nodeRef)
    {
        NodeState* e=new NodeState(nodeRef, 0);
        this->pila.push(e);
    }
    typedef BNodeState<T> NodeState;
    IteratorTree<T>& iterar()
    {
        bool imprime=true;
        
        while(imprime && !this->pila.empty())
        {
            NodeState *e=this->pila.top();
            if(e->state==0)
            {
                e->state=1;//va a bajar a la izquierda
                if(e->nodeRef->son[0])
                {
                    NodeState* apilar=new NodeState(e->nodeRef->son[0],0);
                    this->pila.push(apilar);
                }
            }
            else if(e->state==1)
            {
                e->state=2;//va a bajar a la derecha
                if(e->nodeRef->son[1])
                {
                    NodeState* apilar=new NodeState(e->nodeRef->son[1],0);
                    this->pila.push(apilar);
                }
            }
            else if(e->state==2)
            {
                e->state=3;//va a bajar a la izquierda
                this->actual=e->nodeRef;
                imprime=false;
            }
            else if(e->state==3)
            {
                this->pila.pop();
            }
        }
        return *this;
    }
};


template<class T>
class IteratorPreOrder: public IteratorTree<T>
{
public:
    IteratorPreOrder& operator=(const IteratorTree<T>& c) {
        this->pila=c.pila;
        this->actual=c.actual;
        (*this)++;
        return *this;
    }
    IteratorPreOrder():IteratorTree<T>(){}
    IteratorPreOrder(BNode<T> *nodeRef):IteratorTree<T>(nodeRef)
    {
        NodeState* e=new NodeState(nodeRef, 0);
        this->pila.push(e);
    }
    typedef BNodeState<T> NodeState;
    IteratorTree<T>& iterar()
    {
        bool imprime=true;
        
        while(imprime && !this->pila.empty())
        {
            NodeState *e=this->pila.top();
            if(e->state==0)
            {
                
                this->actual=e->nodeRef;//analizamos la raiz
                imprime=false;
                e->state=1;
        
                if(e->nodeRef->son[0])
                {
                    NodeState* apilar=new NodeState(e->nodeRef->son[0],0);
                    this->pila.push(apilar);
                }
            }
            else if(e->state==1)
            {
                e->state=2;//va a bajar a la derecha
                if(e->nodeRef->son[1])
                {
                    NodeState* apilar=new NodeState(e->nodeRef->son[1],0);
                    this->pila.push(apilar);
                }
            }
            else if(e->state==2)
            {
                this->pila.pop();
            }
        }
        return *this;
    }
};

/*template<class T>
class IteratorInOrder
{
public:
    typedef BNodeState<T> NodeState;
    std::stack<NodeState*>pila;
    BNode<T>* actual;
    IteratorInOrder(){}
    IteratorInOrder(BNode<T> *nodeRef)
    {
        NodeState* e=new NodeState(nodeRef, 0);
        pila.push(e);
    }

    IteratorInOrder<T>& iterar()
    {
        bool imprime=true;
        
        while(imprime && !pila.empty())
        {
            NodeState *e=pila.top();
            if(e->state==0)
            {
                e->state=1;//va a bajar a la izquierda
                if(e->nodeRef->son[0])
                {
                    NodeState* apilar=new NodeState(e->nodeRef->son[0],0);
                    pila.push(apilar);
                }
            }
            else if(e->state==1)
            {
                e->state=2;//va a bajar a la derecha
                pila.pop();//hacemos espacio para el hijo
                if(e->nodeRef->son[1])
                {
                    NodeState* apilar=new NodeState(e->nodeRef->son[1],0);
                    pila.push(apilar);//metemos el hijo
                }
                pila.push(e);//metemos en la cabeza al padre
                actual=e->nodeRef;
                imprime=false;
            }
            else if(e->state==2)
            {
                pila.pop();
            }
        }
        return *this;
    }
    T getValor()
    {
        return actual->dat;
    }
    
    IteratorInOrder<T>& operator ++()
    {
        return iterar();
    }
    IteratorInOrder<T> operator ++(int)
    {
        IteratorInOrder result(*this);
        ++(*this);
        return result;
    }
    bool operator !=(IteratorInOrder<T> x)
    {
        NodeState *b=x.pila.top();
        if(pila.size()==0)
        {
            return NULL!=b->nodeRef;
        }
        else
        {
            return actual!=b->nodeRef;
        }
        
    }
    T operator *()
    {
        return getValor();
    }
};


template<class T>
class IteratorPostOrder
{
public:
    typedef BNodeState<T> NodeState;
    std::stack<NodeState*>pila;
    BNode<T>* actual;
    IteratorPostOrder(){}
    IteratorPostOrder(BNode<T> *nodeRef)
    {
        NodeState* e=new NodeState(nodeRef, 0);
        pila.push(e);
    }

    IteratorPostOrder<T>& iterar()
    {
        bool imprime=true;
        
        while(imprime && !pila.empty())
        {
            NodeState *e=pila.top();
            if(e->state==0)
            {
                e->state=1;//va a bajar a la izquierda
                if(e->nodeRef->son[0])
                {
                    NodeState* apilar=new NodeState(e->nodeRef->son[0],0);
                    pila.push(apilar);
                }
            }
            else if(e->state==1)
            {
                e->state=2;//va a bajar a la derecha
                if(e->nodeRef->son[1])
                {
                    NodeState* apilar=new NodeState(e->nodeRef->son[1],0);
                    pila.push(apilar);
                }
            }
            else if(e->state==2)
            {
                e->state=3;//va a bajar a la izquierda
                actual=e->nodeRef;
                imprime=false;
            }
            else if(e->state==3)
            {
                pila.pop();
            }
        }
        return *this;
    }
    T getValor()
    {
        return actual->dat;
    }
    
    IteratorPostOrder<T>& operator ++()
    {
        return iterar();
    }
    IteratorPostOrder<T> operator ++(int)
    {
        IteratorPostOrder result(*this);
        ++(*this);
        return result;
    }
    bool operator !=(IteratorPostOrder<T> x)
    {
        NodeState *b=x.pila.top();
        if(pila.size()==0)
        {
            return NULL!=b->nodeRef;
        }
        else
        {
            return actual!=b->nodeRef;
        }
        
    }
    T operator *()
    {
        return getValor();
    }
};


template<class T>
class IteratorPreOrder
{
public:
    typedef BNodeState<T> NodeState;
    std::stack<NodeState*>pila;
    BNode<T>* actual;
    IteratorPreOrder(){}
    IteratorPreOrder(BNode<T> *nodeRef)
    {
        NodeState* e=new NodeState(nodeRef, 0);
        pila.push(e);
    }

    IteratorPreOrder<T>& iterar()
    {
        bool imprime=true;
        
        while(imprime && !pila.empty())
        {
            NodeState *e=pila.top();
            if(e->state==0)
            {
                
                actual=e->nodeRef;//analizamos la raiz
                imprime=false;
                e->state=1;
        
                if(e->nodeRef->son[0])
                {
                    NodeState* apilar=new NodeState(e->nodeRef->son[0],0);
                    pila.push(apilar);
                }
            }
            else if(e->state==1)
            {
                e->state=2;//va a bajar a la derecha
                if(e->nodeRef->son[1])
                {
                    NodeState* apilar=new NodeState(e->nodeRef->son[1],0);
                    pila.push(apilar);
                }
            }
            else if(e->state==2)
            {
                pila.pop();
            }
        }
        return *this;
    }
    T getValor()
    {
        return actual->dat;
    }
    
    IteratorPreOrder<T>& operator ++()
    {
        return iterar();
    }
    IteratorPreOrder<T> operator ++(int)
    {
        IteratorPreOrder result(*this);
        ++(*this);
        return result;
    }
    bool operator !=(IteratorPreOrder<T> x)
    {
        NodeState *b=x.pila.top();
        if(pila.size()==0)
        {
            return NULL!=b->nodeRef;
        }
        else
        {
            return actual!=b->nodeRef;
        }
        
    }
    T operator *()
    {
        return getValor();
    }
};

 * */


#endif //BNodeIteratorTree_h








