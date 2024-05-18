#include "MainIncludes.h"
#include "BST.cpp"
#include "AVL.cpp"
#include "Heap.cpp"

ComparByName compareName;
ComparByCategory compareCategory;
ComparByPrice comparePrice;

int main()
{
    string fileName = "items.txt";
    Menu menu;
    Item *item1 = new Item("Apple", "Fruit", 2);
    BinarySearchTree<PriceComparison> bst(item1, PriceComparison());
    Heap<CompareByPrice> heap(CompareByPrice(), false);
    AvlTree<ComparByName> avl(compareName);

    readItemsToBST(fileName, bst);
    readItemsToAVL(fileName, avl);
    readItemsToHeap(fileName, heap);

    int choice = 1;

    while ((choice >= 1 || choice <= 3) && choice != 0)
    {
        menu.display();
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            displayBstMenu(bst);
            break;
        }

        case 2:
        {
            displayAvlMenu(avl);
            break;
        }

        case 3:
        {
            displayHeapMenu(heap);
            break;
        }

        case 0:
        {
            cout << "Program Terminated.";
            break;
        }

        default:
            cout << "Invalid choice, Please try again\n"
                 << endl;
        }
    };

    return 0;
}
