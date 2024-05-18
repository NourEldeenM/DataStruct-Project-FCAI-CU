#ifndef TREEUTILS_H
#define TREEUTILS_H


#include "Heap.h"
#include "AVL.h"
#include "BST.h"
#include <string>

template <typename Comparator>
void readItemsToHeap(const string &filename, Heap<Comparator> &tree);

template <typename Comparator>
void readItemsToBST(const string &filename, BinarySearchTree<Comparator> &tree);

template <typename Comparator>
void readItemsToAVL(const string &filename, AvlTree<Comparator> &tree);

#endif // TREEUTILS_H
