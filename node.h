#ifndef NODE_H
#define NODE_H

#include "Acid.h"




class Node
{
public:
    Acid *acid;
    Node *next = nullptr, *prev = nullptr;
};

#endif // NODE_H
