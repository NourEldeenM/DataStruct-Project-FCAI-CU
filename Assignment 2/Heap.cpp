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

int main() {
    Heap<CompareByPrice> itemHeapByPrice(CompareByPrice(), false);
    int choice;
    string name, category;
    int price;
    itemHeapByPrice.addItem(Item("a", "1", 10));
    itemHeapByPrice.addItem(Item("b", "2", 100));
    itemHeapByPrice.addItem(Item("c", "3", 1000));
    itemHeapByPrice.addItem(Item("d", "4", 1000005));

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Add item\n";
        cout << "2. Remove item\n";
        cout << "3. Display items normally\n";
        cout << "4. Display items sorted by name ascending\n";
        cout << "5. Display items sorted by name descending\n";
        cout << "6. Display items sorted by price ascending\n";
        cout << "7. Display items sorted by price descending\n";
        cout << "8. Perform heap sort\n";
        cout << "9. Toggle heap type (min-heap/max-heap)\n";
        cout << "10. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Enter item name:  ";
                cin >> name;
                cout << "Enter item category:  ";
                cin >> category;
                cout << "Enter item price:  ";
                cin >> price;
                itemHeapByPrice.addItem(Item(name, category, price));
                break;
            case 2:
                itemHeapByPrice.removeItem();
                break;
            case 3:
                itemHeapByPrice.displayItems();
                break;
            case 4:
                itemHeapByPrice.displaySortedByName(true);
                break;
            case 5:
                itemHeapByPrice.displaySortedByName(false);
                break;
            case 6:
                itemHeapByPrice.displaySortedByPrice(true);
                break;
            case 7:
                itemHeapByPrice.displaySortedByPrice(false);
                break;
            case 8:
                itemHeapByPrice.heapSort();
                break;
            case 9:
                itemHeapByPrice.changeHeapType();
                cout << "Heap type toggled." << "\n";
                break;
            case 10:
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
    return 0;
}


