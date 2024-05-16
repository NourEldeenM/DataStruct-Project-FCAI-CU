#include "bits/stdc++.h"
 
using namespace std;
 
class Item {
    string name;
    string category;
    int price;
 
public:
    Item(string name, string category, int p) : name(name), category(category), price(p) {}
 
    string getName() const {
        return name;
    }
 
    int getPrice() const {
        return price;
    }
 
    string getCategory() const {
        return category;
    }
 
    bool operator<(const Item &other) const {
        return price < other.price;
    }
 
    bool operator>(const Item &other) const {
        return price > other.price;
    }
 
    void print() const {
        cout << "Item Name: " << name << ", Category: " << category << ", Price: " << price << "\n";
    }
};
 
class Heap {
private:
    vector<Item> heap;
    bool isMinHeap;
 
    int parent(int index) const { return (index - 1) / 2; }
 
    int leftChild(int index) const { return (2 * index + 1); }
 
    int rightChild(int index) const { return (2 * index + 2); }
 
    void heapifyUp(int index) {
        if (index and ((isMinHeap and heap[parent(index)] > heap[index]) ||
                       (!isMinHeap and heap[parent(index)] < heap[index]))) {
            swap(heap[index], heap[parent(index)]);
            heapifyUp(parent(index));
        }
    }
 
    void heapifyDown(int index) {
        int l = leftChild(index);
        int r = rightChild(index);
        int smallestOrLargest = index;
        if (l < size() and ((isMinHeap and heap[l] < heap[index]) ||
                            (!isMinHeap and heap[l] > heap[index]))) {
            smallestOrLargest = l;
        }
 
        if (r < size() and ((isMinHeap and heap[r] < heap[smallestOrLargest]) ||
                            (!isMinHeap and heap[r] > heap[smallestOrLargest]))) {
            smallestOrLargest = r;
        }
 
        if (smallestOrLargest != index) {
            swap(heap[index], heap[smallestOrLargest]);
            heapifyDown(smallestOrLargest);
        }
    }
 
    void buildHeap() {
        for (int i = size() / 2 - 1; i >= 0; --i) {
            heapifyDown(i);
        }
    }
 
public:
    Heap(bool minHeap = true) : isMinHeap(minHeap) {}
 
    void changeHeapType() {
        isMinHeap = !isMinHeap;
        buildHeap();
    }
 
    void addItem(const Item &item) {
        heap.push_back(item);
        heapifyUp(size() - 1);
    }
 
    void removeItem() {
        if (size() == 0)
            return;
        heap[0] = heap.back();
        heap.pop_back();
        heapifyDown(0);
    }
 
    int size() {
        return heap.size();
    }
 
//    vector<Item> getHeap() {
//        return heap;
//    }
 
    void displayItems() {
        if (heap.empty())
            return void(cout << "Nothing to display. \n");
        for (auto &item: heap) {
            item.print();
        }
    }
 
    void heapSort() {
//        for (int i = size() / 2 - 1; i >= 0; i--)
//            heapifyDown(i);
//        for (int i = size() - 1; i >= 0; i--) {
//            auto temp = heap[0];
//            heap[0] = heap[i];
//            heap[i] = temp;
//            heapifyDown(0);
//        }
//        if (!isMinHeap)
//            reverse(heap.begin(), heap.end());
//        for (auto &item: heap) {
//            item.print();
//        }
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
 
    void displaySortedByName(bool ascending = true) {
        if (heap.empty())
            return void(cout << "Nothing to display. \n");
        sort(heap.begin(), heap.end(), [ascending](Item a, Item b) {
            return ascending ? a.getName() < b.getName() : a.getName() > b.getName();
        });
 
        for (const auto &item: heap) {
            item.print();
        }
    }
 
    void displaySortedByPrice(bool ascending = true) {
        if (heap.empty())
            return void(cout << "Nothing to display. \n");
        sort(heap.begin(), heap.end(), [ascending](Item a, Item b) {
            return ascending ? a.getPrice() < b.getPrice() : a.getPrice() > b.getPrice();
        });
 
        for (const auto &item: heap) {
            item.print();
        }
    }
};
 
int main() {
    Heap itemHeap(false);
    int choice;
    string name, category;
    int price;
 
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
                itemHeap.addItem(Item(name, category, price));
                break;
            case 2:
                itemHeap.removeItem();
                break;
            case 3:
                itemHeap.displayItems();
                break;
            case 4:
                itemHeap.displaySortedByName(true);
                break;
            case 5:
                itemHeap.displaySortedByName(false);
                break;
            case 6:
                itemHeap.displaySortedByPrice(true);
                break;
            case 7:
                itemHeap.displaySortedByPrice(false);
                break;
            case 8:
                itemHeap.heapSort();
                break;
            case 9:
                itemHeap.changeHeapType();
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
 
 