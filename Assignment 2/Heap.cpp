#include "Heap.h"

template<typename Comparator>
Heap<Comparator>::Heap(Comparator comp, bool minHeap) : compare(comp), isMinHeap(minHeap) {}

template<typename Comparator>
void Heap<Comparator>::changeHeapType() {
    isMinHeap = !isMinHeap;
    buildHeap();
}

template<typename Comparator>
void Heap<Comparator>::addItem(const Item &item) {
    heap.push_back(item);
    heapifyUp(size() - 1);
}

template<typename Comparator>
void Heap<Comparator>::removeItem() {
    if (size() == 0)
        return;
    heap[0] = heap.back();
    heap.pop_back();
    heapifyDown(0);
}

template<typename Comparator>
int Heap<Comparator>::size() {
    return heap.size();
}

template<typename Comparator>
void Heap<Comparator>::displayItems() {
    if (heap.empty())
        return void(cout << "Nothing to display. \n");
    for (auto &item: heap) {
        item.print();
    }
}

template<typename Comparator>
void Heap<Comparator>::heapSort() {
    vector<Item> temp = heap;
    buildHeap();
    vector<Item> sortedItems;
    while (!heap.empty()) {
        sortedItems.push_back(heap[0]);
        removeItem();
    }
    heap = temp;
    if (!isMinHeap)
        reverse(sortedItems.begin(), sortedItems.end());

    for (auto &item: sortedItems) {
        item.print();
    }
}

template<typename Comparator>
void Heap<Comparator>::displaySortedByName(bool ascending) {
    if (heap.empty())
        return void(cout << "Nothing to display. \n");
    vector<Item> Sorted = heap;
    sort(Sorted.begin(), Sorted.end(), [ascending](Item a, Item b) {
        return ascending ? a.getName() < b.getName() : a.getName() > b.getName();
    });

    for (const auto &item: Sorted) {
        item.print();
    }
}

template<typename Comparator>
void Heap<Comparator>::displaySortedByPrice(bool ascending) {
    if (heap.empty())
        return void(cout << "Nothing to display. \n");
    vector<Item> Sorted = heap;
    sort(Sorted.begin(), Sorted.end(), [ascending](Item a, Item b) {
        return ascending ? a.getPrice() < b.getPrice() : a.getPrice() > b.getPrice();
    });

    for (const auto &item: Sorted) {
        item.print();
    }
}

template<typename Comparator>
void Heap<Comparator>::buildHeap() {
    for (int i = size() / 2 - 1; i >= 0; --i) {
        heapifyDown(i);
    }
}

template<typename Comparator>
void Heap<Comparator>::heapifyDown(int index) {
    int l = leftChild(index);
    int r = rightChild(index);
    int smallestOrLargest = index;
    if (l < size() and ((isMinHeap and compare(heap[l], heap[index])) ||
                        (!isMinHeap and !compare(heap[index], heap[l])))) {
        smallestOrLargest = l;
    }

    if (r < size() and ((isMinHeap and compare(heap[r], heap[smallestOrLargest])) ||
                        (!isMinHeap and !compare(heap[smallestOrLargest], heap[r])))) {
        smallestOrLargest = r;
    }

    if (smallestOrLargest != index) {
        swap(heap[index], heap[smallestOrLargest]);
        heapifyDown(smallestOrLargest);
    }
}

template<typename Comparator>
void Heap<Comparator>::heapifyUp(int index) {
    if (index and ((isMinHeap and compare(heap[parent(index)], heap[index])) ||
                   (!isMinHeap and !compare(heap[index], heap[parent(index)])))) {
        swap(heap[index], heap[parent(index)]);
        heapifyUp(parent(index));
    }
}

template<typename Comparator>
int Heap<Comparator>::rightChild(int index) const {
    return (2 * index + 2);
}

template<typename Comparator>
int Heap<Comparator>::leftChild(int index) const {
    return (2 * index + 1);
}

template<typename Comparator>
int Heap<Comparator>::parent(int index) const {
    return (index - 1) / 2;
}
