#ifndef MENU_H
#define MENU_H

#include "BST.h"
#include "AVl.h"
#include "Heap.h"
#include "Item.h"
using namespace std;

class Menu
{
public:
    void display();
    void displayTreeItems();
};
template <typename Comparator>
void displayBstMenu(BinarySearchTree<Comparator> &bst);

template <typename Comparator>
void displayAvlMenu(AvlTree<Comparator> &avl);

template <typename Comparator>
void displayHeapMenu(Heap<Comparator> &itemHeap);

#endif // MENU_H
