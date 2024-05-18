#ifndef AVLTREE_H
#define AVLTREE_H

#include "Item.h"

template<typename Comparator>
class AvlTree {
private:
    struct AvlNode {
        Item item;
        AvlNode* left;
        AvlNode* right;
        int height;
        AvlNode(const Item& i);
    };

    AvlNode* root;
    Comparator comp;

    int getHeight(AvlNode* node) const;
    int getBalanceFactor(AvlNode* node) const;
    void updateHeight(AvlNode* node);
    AvlNode* LL_Rotate(AvlNode* node);
    AvlNode* RR_Rotate(AvlNode* node);
    AvlNode* insert(AvlNode* node, const Item& item);
    AvlNode* minValueNode(AvlNode* node) const;
    AvlNode* deleteNode(AvlNode* root, const Item& item);
    void inorderTraversal(AvlNode* root) const;
    void collectItems(AvlNode* node, std::vector<Item>& items) const;
    void displayDescendingByComparatorHelper(AvlNode* node) const;

public:
    AvlTree(Comparator c);
    void addItem(const Item& item);
    void removeItem(Item& item);
    void display() const;
    void displayAscendingByComparator() const;
    void displayDescendingByComparator() const;
    void displaySortedByPrice(bool ascending = true);
};

#endif // AVLTREE_H
