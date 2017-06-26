#ifndef BNodeState_h
#define BNodeState_h


#include "BNode.h"

template<class T>
//enum states {VISITED,LEFTDOWN,COMEBACKLEFT,RIGHTDOWN};
class BNodeState
{
public:
    BNode<T> *nodeRef;
    /*
     *Inorder Estados: 
     * 0:recien visitado
     * 1:visita la izquierda
     * 2:regresa despues de visitar la izquierda
    */
    int state;
    BNodeState(BNode<T>* _nodeRef, int _state)
    {
        nodeRef=_nodeRef;
        state=_state;
    }
};

#endif BNodeState_h