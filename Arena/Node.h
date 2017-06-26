#ifndef Node_h
#define Node_h

#include <cstddef>

template<class T>
class Node{
public:
	T dat;
	Node *next;
	Node<T>() {
        next=NULL;
	}
	Node<T>(T _dat, Node<T> *_next) {
		next = _next;
		dat = _dat;
	}
};

#endif Node_h