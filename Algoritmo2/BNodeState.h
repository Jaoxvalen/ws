#ifndef BNodeState_h
#define BNodeState_h

#include "BNode.h"

template<class T>
//enum states {VISITED,LEFTDOWN,COMEBACKLEFT,RIGHTDOWN};
class BNodeState
{
public:
    //typedef typename cTypes::T T;
    BNode<T> *nodeRef;
    int state;
    BNodeState(BNode<T>* _nodeRef, int _state)
    {
        nodeRef=_nodeRef;
        state=_state;
    }
};

#endif BNodeState_h