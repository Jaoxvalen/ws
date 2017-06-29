
#ifndef BNode_h
#define BNode_h

#include <cstddef>
template <class T>
class BNode
{
public:
    T dat;
    BNode<T>* son[2];
    BNode<T>() {
        son[0] = NULL;
        son[1]=NULL;
	}
	BNode<T>(T _dat, BNode<T> *_son) {
		dat = _dat;
        son = _son;
	}
    BNode<T>(T _dat) {
		dat = _dat;
        son[0] = NULL;
        son[1]=NULL;
	}
};
#endif //BNode_h