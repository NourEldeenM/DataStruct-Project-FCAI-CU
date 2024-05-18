#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H


#include "Item.h"

template <typename Comparator>
class BinarySearchTree
{
private:
    Item *data{};
    Comparator compare;
    BinarySearchTree *left{};
    BinarySearchTree *right{};

    BinarySearchTree *min_node();
    void special_delete(BinarySearchTree *child);
    BinarySearchTree *delete_node(BinarySearchTree *node, Item *item);
    void display(BinarySearchTree *node);
    void displaySortByName(BinarySearchTree *node, std::vector<Item *> &items);
    void displaySortByPrice(BinarySearchTree *node, std::vector<Item *> &items);

public:
    BinarySearchTree(Comparator comp);
    BinarySearchTree(Item *data, Comparator comp);

    void insert(Item *item);
    bool delete_item(Item *item);
    void display();
    void displaySortByName(bool ascending);
    void displaySortByPrice(bool ascending);
    Item *search(Item *item);
};

#endif // BINARYSEARCHTREE_H
