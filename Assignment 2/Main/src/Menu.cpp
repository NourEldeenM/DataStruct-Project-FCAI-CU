#include "Menu.h"
#include "Heap.h"
#include "BST.h"
#include "AVL.h"
#include "TreeUtils.cpp"

void Menu::display()
{
    cout << "Choose a data structure:" << endl;
    cout << "1. Binary Search Tree (BST)" << endl;
    cout << "2. AVL Tree" << endl;
    cout << "3. Heap" << endl;
    cout << "Enter 0 to Exit" << endl;
    cout << "Enter your choice: ";
}

void Menu::displayTreeItems()
{
    cout << "\nTree Menu:\n";
    cout << "1. Add item\n";
    cout << "2. Remove item\n";
    cout << "3. Display items normally\n";
    cout << "4. Display items sorted by name ascending\n";
    cout << "5. Display items sorted by name descending\n";
    cout << "6. Display items sorted by price ascending\n";
    cout << "7. Display items sorted by price descending\n";
}

template <typename Comparator>
void displayBstMenu(BinarySearchTree<Comparator> &bst)
{
    int treeChoice = 1, price;
    Item itemToRemove, itemToAdd;
    string name;
    while (treeChoice != 0)
    {
        cout << "\nTree Menu:\n";
        cout << "1. Add item\n";
        cout << "2. Remove item\n";
        cout << "3. Display items normally\n";
        cout << "4. Display items sorted by name ascending\n";
        cout << "5. Display items sorted by name descending\n";
        cout << "6. Display items sorted by price ascending\n";
        cout << "7. Display items sorted by price descending\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> treeChoice;
        switch (treeChoice)
        {
        case 1:
            cin >> itemToAdd;
            bst.insert(&itemToAdd);
            break;
        case 2:
        {
            cin >> itemToRemove;
            bst.delete_item(&itemToRemove);
            break;
        }
        case 3:
            cout << "Tree Items:\n";
            bst.display();
            break;
        case 4:
            cout << "Items Sorted by Name Ascendingly:\n";
            bst.displaySortByName(true);
            break;
        case 5:
            cout << "Items Sorted by Name Descendingly:\n";
            bst.displaySortByName(false);
            break;
        case 6:
            cout << "Items Sorted by Price Ascendingly:\n";
            bst.displaySortByPrice(true);
            break;
        case 7:
            cout << "Items Sorted by Price Descendingly:\n";
            bst.displaySortByPrice(false);
            break;
        case 0:
            cout << "Tree Operations Ended.\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }
}

template <typename Comparator>
void displayAvlMenu(AvlTree<Comparator> &avl)
{
    int treeChoice = 1, price;
    Item itemToRemove, itemToAdd;
    while (treeChoice != 0)
    {
        cout << "\nTree Menu:\n";
        cout << "1. Add item\n";
        cout << "2. Remove item\n";
        cout << "3. Display items normally\n";
        cout << "4. Display items sorted by name ascending\n";
        cout << "5. Display items sorted by name descending\n";
        cout << "6. Display items sorted by price ascending\n";
        cout << "7. Display items sorted by price descending\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> treeChoice;
        switch (treeChoice)
        {
        case 1:
            cin >> itemToAdd;
            avl.addItem(itemToAdd);
            break;
        case 2:
            cin >> itemToRemove;
            avl.removeItem(itemToRemove);
            break;
        case 3:
            cout << "Tree Items:\n";
            avl.display();
            break;
        case 4:
            cout << "Items Sorted by Name Ascendingly:\n";
            avl.displayAscendingByComparator();
            break;
        case 5:
            cout << "Items Sorted by Name Descendingly:\n";
            avl.displayDescendingByComparator();
            break;
        case 6:
            cout << "Items Sorted by Price Ascendingly:\n";
            avl.displaySortedByPrice(true);
            break;
        case 7:
            cout << "Items Sorted by Price Descendingly:\n";
            avl.displaySortedByPrice(false);
            break;
        case 0:
            cout << "Tree Operations Ended.\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }
}

template <typename Comparator>
void displayHeapMenu(Heap<Comparator> &itemHeap)
{
    int treeChoice = 1;
    Item itemToAdd;
    while (treeChoice != 0)
    {
        cout << "\nTree Menu:\n";
        cout << "1. Add item\n";
        cout << "2. Remove item\n";
        cout << "3. Display items normally\n";
        cout << "4. Display items sorted by name ascending\n";
        cout << "5. Display items sorted by name descending\n";
        cout << "6. Display items sorted by price ascending\n";
        cout << "7. Display items sorted by price descending\n";
        cout << "8. Perform heap sort\n";
        cout << "9. Toggle heap type (min-heap/max-heap)\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> treeChoice;
        switch (treeChoice)
        {
        case 1:
            cin >> itemToAdd;
            itemHeap.addItem(itemToAdd);
            break;
        case 2:
            itemHeap.removeItem();
            break;
        case 3:
            cout << "Tree Items:\n";
            itemHeap.displayItems();
            break;
        case 4:
            cout << "Items Sorted by Name Ascendingly:\n";
            itemHeap.displaySortedByName(true);
            break;
        case 5:
            cout << "Items Sorted by Name Descendingly:\n";
            itemHeap.displaySortedByName(false);
            break;
        case 6:
            cout << "Items Sorted by Price Ascendingly:\n";
            itemHeap.displaySortedByPrice(true);
            break;
        case 7:
            cout << "Items Sorted by Price Descendingly:\n";
            itemHeap.displaySortedByPrice(false);
            break;
        case 8:
            itemHeap.heapSort();
            break;
        case 9:
            itemHeap.changeHeapType();
            cout << "Heap type toggled." << "\n";
            break;
        case 0:
            cout << "Tree Operations Ended.\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }
}

template void displayHeapMenu(Heap<CompareByName> &itemHeap);
template void displayHeapMenu(Heap<CompareByPrice> &itemHeap);
template void displayHeapMenu(Heap<CompareByCategory> &itemHeap);

template void displayAvlMenu(AvlTree<ComparByName> &avl);
template void displayAvlMenu(AvlTree<ComparByPrice> &avl);
template void displayAvlMenu(AvlTree<ComparByCategory> &avl);

template void displayBstMenu(BinarySearchTree<NameComparison> &bst);
template void displayBstMenu(BinarySearchTree<PriceComparison> &bst);
template void displayBstMenu(BinarySearchTree<CategoryComparison> &bst);