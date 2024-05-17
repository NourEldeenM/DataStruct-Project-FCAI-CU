#include <bits/stdc++.h>

using namespace std;

// Define the Item class
class Item {
    string name;
    string category;
    int price;

public:
    Item(string n, string c, int p) : name(n), category(c), price(p){}

    string getName() const {
        return name;
    }

    int getPrice() const {
        return price;
    }

    string getCategory() const {
        return category;
    }

    bool operator==(Item *other) {
        return name == other->name && category == other->category && price == other->price;
    }

    Item* operator=(Item *other){
        this->name = other->name;
        this->category = other->category;
        this->price = other->price;
        return this;
    }

    // Function to print the details of the item
    void print() {
        cout << "Name: " << name << ", Category: " << category << ", Price: " << price << endl;
    }
};

struct CompareByName {
    bool operator()(Item *a, Item *b) const {
        return a->getName() < b->getName();
    }
};

struct CompareByCategory {
    bool operator()(Item *a, Item *b) const {
        return a->getCategory() < b->getCategory();
    }
};

struct CompareByPrice {
    bool operator()(Item *a, Item *b) const {
        return a->getPrice() < b->getPrice();
    }
};


template<typename Comparator>
class BinarySearchTree {
private:
    Item *data{};
    Comparator compare;
    BinarySearchTree *left{};
    BinarySearchTree *right{};

    // Function to find the node with the minimum value
    BinarySearchTree *min_node() {
        BinarySearchTree* cur = this;
        while (cur && cur->left)
            cur = cur->left;
        return cur;
    }

    // Function to delete a node and return a new node with the same data ( to avoid RTE )
    void special_delete(BinarySearchTree *child) {
        left = child->left;
        right = child->right;
        data = child->data;
        delete child;
    }

    // Delete the target node in the tree and return updated tree
    // Caller use updated tree to re-link with children!
    // Function to delete a node from the tree
    BinarySearchTree *delete_node(BinarySearchTree *node, Item *item) {
        if (!node)
            return nullptr;


        if (compare(item, node->data))
            node->left = delete_node(node->left, item);
        else if (compare(node->data, item))
            node->right = delete_node(node->right, item);
        else {
            // found the node: Handle deletion
            BinarySearchTree* tmp = node;

            if (!node->left && !node->right) {   // 0 children
                delete node;
//                return tmp;
                return nullptr;
            }
                // 1 child
            else if (!node->left)    // one child on the right
                node->special_delete(node->right);        // connect with child
            else if (!node->right)
                node->special_delete(node->left);        // connect with child
            else {   // 2 children use successor
                BinarySearchTree *mn = node->right->min_node();
                node->data = mn->data;
                node->right = delete_node(node->right, mn->data);
//                tmp = nullptr;
            }
//            if(tmp)
//                delete tmp;
        }
        return node;
    }

    // Function to display the nodes of the tree in order
    void display(BinarySearchTree *node) {
        if (node) {
            display(node->left);
            node->data->print();
            display(node->right);
        }
    }

    // Function to store the nodes of the tree in a vector in order of itemName
    void displaySortByName(BinarySearchTree *node, vector<Item *> &items) {
        if (node) {
            if (node->left)
                displaySortByName(node->left, items);
            items.push_back(node->data);
            if (node->right)
                displaySortByName(node->right, items);
        }
    }

    // Function to store the nodes of the tree in a vector in order of price
    void displaySortByPrice(BinarySearchTree *node, vector<Item *> &items) {
        if (node) {
            if (node->left)
                displaySortByPrice(node->left, items);
            items.push_back(node->data);
            if (node->right)
                displaySortByPrice(node->right, items);
        }
    }

public:

    BinarySearchTree(Item *data, Comparator comp) :
            data(data), compare(comp) {
    }

    // Function to insert a node into the tree
    void insert(Item *item) {
        if (compare(item, data)) {
            if (!left) {
                left = new BinarySearchTree(item, compare);
            }
            else
                left->insert(item);
        } else if (compare(data, item)) {
            if (!right)
                right = new BinarySearchTree(item, compare);
            else
                right->insert(item);
        }
//        else: already exits
    }

    // Function to delete a node from the tree
    bool delete_item(Item* item) {
        if (item->getName() == data->getName() && !left && !right)
            return false; // can't remove root in this structure
        delete_node(this, item);
        return true;
    }

    // Function to display the nodes of the tree in order
    void display() {
        display(this);
    }

    // Function to display the nodes of the tree sorted by itemName
    void displaySortByName(bool ascending) {
        vector<Item *> items;
        displaySortByName(this, items);
        sort(items.begin(), items.end(), [ascending](Item *first, Item *second) { return ascending ? first->getName() < second->getName() : first->getName() > second->getName(); });
        for (Item *item: items)
            item->print();
    }

    // Function to display the nodes of the tree sorted by price
    void displaySortByPrice(bool ascending) {
        vector<Item *> items;
        displaySortByPrice(this, items);
        sort(items.begin(), items.end(), [ascending](Item *first, Item *second) { return ascending ? first->getPrice() < second->getPrice() : first->getPrice() > second->getPrice(); });
        for (Item *item: items)
            item->print();
    }

    Item* search(Item *item) {
        BinarySearchTree *current = this;
        while (current) {
            if (item->getName() < current->data->getName())
                current = current->left;
            else if (current->data->getName() < item->getName())
                current = current->right;
            else
                return current->data;  // Found the item
        }
        return nullptr;  // Item not found
    }
};

int main() {

    Item* item1 = new Item("Apple", "Fruit", 2);
    BinarySearchTree<CompareByPrice> itemBSTByPrice(item1, CompareByPrice());
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
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        while (!(cin >> choice) || choice < 1 || choice > 8) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice. Please enter a number between 1 and 8: ";
        }

        switch (choice) {
            case 1: {
                cout << "Enter item name:  ";
                cin >> name;
                cout << "Enter item category:  ";
                cin >> category;
                cout << "Enter item price:  ";
                while (!(cin >> price)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid price. Please enter a number: ";
                }
                itemBSTByPrice.insert(new Item(name, category, price));
                break;
            }
            case 2: {
                cout << "Enter the name of item you want to delete:  ";
                cin >> name;
//                cout << "Enter item category:  ";
//                cin >> category;
//                cout << "Enter item price:  ";
//                cin >> price;
                Item *toDelete = itemBSTByPrice.search(new Item(name, "", 0));
                if (toDelete) {
                    if(itemBSTByPrice.delete_item(toDelete))
                        cout << "Item " << name << " deleted successfully.\n";
                    else
                        cout << "can't remove the root. \n";
                } else
                    cout << "Item not found\n";
                break;
            }
            case 3: {
                itemBSTByPrice.display();
                break;
            }
            case 4: {
                itemBSTByPrice.displaySortByName(true);
                break;
            }
            case 5: {
                itemBSTByPrice.displaySortByName(false);
                break;
            }
            case 6: {
                itemBSTByPrice.displaySortByPrice(true);
                break;
            }
            case 7: {
                itemBSTByPrice.displaySortByPrice(false);
                break;
            }
            case 8: {
                return 0;
            }
            default: {
                cout << "Invalid choice. Please try again.\n";
                break;
            }
        }
    }
}
/*
        Item* item1 = new Item("Apple", "Fruit", 2);
        Item* item2 = new Item("Banana", "Fruit", 1);
        Item* item3 = new Item("Carrot", "Vegetable", 4);
        Item* item4 = new Item("Daikon", "Vegetable", 3);
        Item* item5 = new Item("Eggplant", "Vegetable", 6);
        Item* item6 = new Item("Fig", "Fruit", 5);
*/
