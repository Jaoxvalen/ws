#ifndef Btree_h
#define Btree_h


#include <cstddef>
#include "BNode.h"
#include "BNodeIteratorTree.h"
#include "Utils.h"


template<class T, template<typename TT> class C>
class Btree{
private:
    C<T> comp;
    BNode<T>** replace(BNode<T>** p)
    {
        //solo usar cuando se tiene dos hijos
        p=&((*p)->son[1]); //primero a la derecha
        while((*p)->son[0])//todo a la izquierda
        {
            p=&((*p)->son[0]);
        }
        return p;
    }
typedef IteratorTree<T> Iterator;
public:
    typedef IteratorInOrder<T> Iterator_in_order;
    typedef IteratorPostOrder<T> Iterator_post_order;
    typedef IteratorPreOrder<T> Iterator_pre_order;
    BNode<T> *root;
    Btree()
    {
        root=NULL;
    }
    bool find(T x, BNode<T> **&p)
    {
        p=&root;
        while(*p && (*p)->dat!=x)
        {
            //Todo: agregar la comparacion por Type
            //p=&((*p)->son[((*p)->dat<x)]);
            p=&((*p)->son[comp((*p)->dat,x)]);
        }
        return !!(*p);
    }
    bool insert(T x)
    {
        BNode<T> **p;
        if(find(x,p)) return false;
        *p=new BNode<T>(x);
        return true;
    }
    
    bool remove(T x)
    {
        BNode<T> **p;
        if(!find(x,p)) return false;
        //para el caso 2 que el nodo tenga dos hijos
        if((*p)->son[0] && (*p)->son[1])
        {
            BNode<T> **q=replace(p);
            (*p)->dat=(*q)->dat;
            p=q;
        }
        BNode<T> *t=*p;
        *p=(*p)->son[!((*p)->son[0])];
        delete t;
        return true;
    }
    Iterator begin()
    {
        Iterator x(root);
        //x++;
        return x;
    }
    Iterator end()
    {
        Iterator x(NULL);
        return x;
    }
    
};

#endif //Btree_h