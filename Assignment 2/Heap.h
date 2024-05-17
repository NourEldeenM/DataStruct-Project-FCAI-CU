#ifndef HEAP_H
#define HEAP_H
#include <bits/stdc++.h>
#include "Item.h" 

using namespace std;

template<typename Comparator>
class Heap {
private:
    vector<Item> heap;
    Comparator compare;
    bool isMinHeap;

    int parent(int index) const;
    int leftChild(int index) const;
    int rightChild(int index) const;
    void heapifyUp(int index);
    void heapifyDown(int index);
    void buildHeap();

public:
    Heap(Comparator comp, bool minHeap);

    void changeHeapType();
    void addItem(const Item &item);
    void removeItem();
    int size();
    void displayItems();
    void heapSort();
    void displaySortedByName(bool ascending = true);
    void displaySortedByPrice(bool ascending = true);
};


#endif // HEAP_H
