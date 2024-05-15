#include <bits/stdc++.h>

using namespace std;

// Define the Item class
class Item {
public:
    string itemName;
    string category;
    int price;

    Item(string n, string c, int p) : itemName(n), category(c), price(p){}

    // Overload the less than operator for comparison based on itemName
    bool operator<(const Item &other) {
        return itemName < other.itemName;
    }

    bool operator>(const Item &other) {
        return itemName > other.itemName;
    }

    bool operator==(const Item &other) {
        return itemName == other.itemName && category == other.category && price == other.price;
    }

    Item* operator=(const Item*other){
        this->itemName = other->itemName;
        this->category = other->category;
        this->price = other->price;
        return this;
    }

    // Function to print the details of the item
    void print() {
        cout << "Name: " << itemName << ", Category: " << category << ", Price: " << price << endl;
    }

};


class BinarySearchTree {
private:
    Item *data{};
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

        if (item < node->data)
            node->left = delete_node(node->left, item);
        else if (item > node->data)
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

    BinarySearchTree(Item* data) :
            data(data) {
    }

    // Function to insert a node into the tree
    void insert(Item* item) {
        if (item < data) {
            if (!left) {
                left = new BinarySearchTree(item);
            }
            else
                left->insert(item);
        } else if (item > data) {
            if (!right)
                right = new BinarySearchTree(item);
            else
                right->insert(item);
        }
//        else: already exits
    }

    // Function to delete a node from the tree
    void delete_item(Item* item) {
        if (item == data && !left && !right)
            return; // can't remove root in this structure
        delete_node(this, item);
    }

    // Function to display the nodes of the tree in order
    void display() {
        display(this);
    }

    // Function to display the nodes of the tree sorted by itemName
    void displaySortByName(bool ascending) {
        vector<Item *> items;
        displaySortByName(this, items);
        if (!ascending)
            reverse(items.begin(), items.end());
        for (Item *item: items)
            item->print();
    }

    // Function to display the nodes of the tree sorted by price
    void displaySortByPrice(bool ascending) {
        vector<Item *> items;
        displaySortByPrice(this, items);
        if (ascending)
            sort(items.begin(), items.end(), [](Item *first, Item *second) { return first->price < second->price; });
        else
            sort(items.begin(), items.end(), [](Item *first, Item *second) { return first->price > second->price; });
        for (Item *item: items)
            item->print();
    }
};

int main() {

    Item* item1 = new Item("Apple", "Fruit", 2);
    Item* item2 = new Item("Banana", "Fruit", 1);
    Item* item3 = new Item("Carrot", "Vegetable", 4);
    Item* item4 = new Item("Daikon", "Vegetable", 3);
    Item* item5 = new Item("Eggplant", "Vegetable", 6);
    Item* item6 = new Item("Fig", "Fruit", 5);

    BinarySearchTree* bst = new BinarySearchTree(item1);

    // Add some items to the tree
    bst->insert(item2);
    bst->insert(item3);
    bst->insert(item4);
    bst->insert(item5);
    bst->insert(item6);

    // Display the items
    cout << "Items in the tree:\n";
    bst->display();

    // Delete an item
    cout << "\nDeleting 'Carrot'...\n";
    bst->delete_item(item3);

    // Display the items again
    cout << "Items in the tree after deletion:\n";
    bst->display();
    // Display the items
    cout << "Items in the tree:\n";
    bst->display();

    // Sort and display the items by name
    cout << "\nItems sorted by name (ascending):\n";
    bst->displaySortByName(true);

    cout << "\nItems sorted by name (descending):\n";
    bst->displaySortByName(false);

    // Sort and display the items by price
    cout << "\nItems sorted by price (ascending):\n";
    bst->displaySortByPrice(true);

    cout << "\nItems sorted by price (descending):\n";
    bst->displaySortByPrice(false);

    return 0;
}
