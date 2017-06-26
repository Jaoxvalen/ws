#ifndef List_h
#define List_h

#include "NodeIteratorList.h"
#include "Node.h"

template<class T>
class List {
	Node<T> *head;
public:
    typedef NodeIteratorList<T> Iterator;
	List<T>() {
        head=NULL;
	}
	List<T>(Node<T> *_head) {
		head = _head;
	}
    
	bool find(T x, Node<T> **&p) {
		p = &head;
		while (*p && x > (*p)->dat) {
			p = &((*p)->next);
		}
		return *p && x == (*p)->dat;
	}
	bool insert(T x) {
		Node<T> **p;
		if (find(x, p)) {
			return false;
		}
		Node<T>*t = new Node<T>(x, *p);
		(*p) = t;
		return true;
	}
	bool remove(T x) {
		Node<T> **p;
		if (!find(x, p)) {
			return false;
		}
		Node<T>*t = *p;
		*p=(*p)->next;
		delete t;
		return true;
	}
    
    //propios para la iteracion
    NodeIteratorList<T> begin()
    {
        NodeIteratorList<T> x(head);
        return x;
    }
    NodeIteratorList<T> end()
    {
        NodeIteratorList<T> x(NULL);
        return x;
    }
};

#endif List_h