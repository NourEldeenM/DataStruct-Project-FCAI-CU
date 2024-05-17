#ifndef TREE_H
#define TREE_H

#include "Item.h"

class Tree
{
public:
    virtual void insert(const Item &value) = 0;
    virtual void printInOrder() const = 0;
    virtual ~Tree() = default;
};

#endif // TREE_H
