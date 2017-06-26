

#include <iostream>
#include <string>
#include "List.h"
#include "BTree.h"
#include "Utils.h"

using namespace std;


int main(int argc, char **argv)
{
    
    cout<<"List:"<<endl;
    List<int> l;
    l.insert(4);
    l.insert(2);
    l.insert(1);
    l.insert(3);
    l.insert(5);
    l.insert(6);
    l.insert(7);
    
    List<int>::Iterator m;
    
    for(m=l.begin();m!=l.end();m++)
    {
        cout<<*m<<" ";
    }
    cout<<endl;
    cout<<endl;
    cout<<endl;

    
    cout<<"Binary Tree:"<<endl;
    
    Btree<int,LessComparator> t;
    t.insert(4);
    t.insert(2);
    t.insert(1);
    t.insert(3);
    t.insert(5);
    t.insert(6);
    t.insert(7);
    
    cout<<"Pre order:"<<endl;
    Btree<int,LessComparator>::Iterator_pre_order i;
    for(i=t.begin();i!=t.end();i++)
    {
        cout<<*i<<" ";
    }
    cout<<endl;
    
    cout<<"In order:"<<endl;
    Btree<int,LessComparator>::Iterator_in_order j;
    for(j=t.begin();j!=t.end();j++)
    {
        cout<<*j<<" ";
    }
    cout<<endl;
    
    cout<<"Post order:"<<endl;
    Btree<int,LessComparator>::Iterator_post_order k;
    for(k=t.begin();k!=t.end();k++)
    {
        cout<<*k<<" ";
    }
    cout<<endl;
    
    return 0;
}
