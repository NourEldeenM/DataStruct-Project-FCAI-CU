#include <bits/stdc++.h>

using namespace std;

// Define the Item class
class Item {
public:
    string itemName;
    string category;
    int price;
    Item* left;
    Item* right;

    Item(string n, string c, int p) : itemName(n), category(c), price(p), left(nullptr), right(nullptr){}

    // Overload the less than operator for comparison based on itemName
    bool operator<(const Item&other){
        return itemName < other.itemName;
    }

    // Function to print the details of the item
    void print(){
        cout<<"Name: "<<itemName<<", Category: "<<category<<", Price: "<<price<<endl;
    }

};


class BinarySearchTree {
private:
    Item* root;  // Root of the binary search tree

    // Function to find the node with the minimum value
    Item* min_node(Item* cur){
        while(cur && cur->left)
            cur = cur->left;
        return cur;
    }

    // Function to delete a node and return a new node with the same data ( to avoid RTE )
    Item* special_delete(Item* child){
        Item* tmp = new Item(child->itemName, child->category, child->price);
        tmp->left = child->left;
        tmp->right = child->right;
        delete child;
        return tmp;
    }

    // Function to delete a node from the tree
    Item* delete_node(Item* node, const string& name){
        if(!node)
            return nullptr;

        if(name < node->itemName)
            node->left = delete_node(node->left, name);
        else if(name > node->itemName)
            node->right = delete_node(node->right, name);
        else {
            if(!node->left && !node->right) {   // 0 children
                delete node;
                return nullptr;
            }
            // 1 child
            else if(!node->left)    // one child on the right
                node = special_delete(node->right);		// connect with child
            else if(!node->right)
                node = special_delete(node->left);		// connect with child
            else{   // 2 children use successor
                Item* mn = min_node(node->right);
                node->itemName = mn->itemName;
                node->category = mn->category;
                node->price = mn->price;
                node->right = delete_node(node->right, mn->itemName);
            }
        }
        return node;
    }

    // Function to insert a node into the tree
    void insert(Item* node, const string& name, const string& category, int price){
        if(name < node->itemName){
            if(!node->left)
                node->left = new Item(name, category, price);
            else
                insert(node->left, name, category, price);
        }
        else if(name > node->itemName){
            if(!node->right)
                node->right = new Item(name, category, price);
            else
                insert(node->right, name, category, price);
        }
//        else: already exits
    }

    // Function to display the nodes of the tree in order
    void display(Item* node){
        if(node){
            display(node->left);
            node->print();
            display(node->right);
        }
    }

    // Function to store the nodes of the tree in a vector in order of itemName
    void displaySortByName(Item* node, vector<Item*> &items){
        if(node){
            if(node->left)
                displaySortByName(node->left, items);
            items.push_back(node);
            if(node->right)
                displaySortByName(node->right, items);
        }
    }

    // Function to store the nodes of the tree in a vector in order of price
    void displaySortByPrice(Item* node, vector<Item*> &items){
        if(node){
            if(node->left)
                displaySortByPrice(node->left, items);
            items.push_back(node);
            if(node->right)
                displaySortByPrice(node->right, items);
        }
    }

public:

    BinarySearchTree() :
            root(nullptr) {
    }

    // Function to insert a node into the tree
    void insert(const string& name, const string& category, int price){
        if(!root)
            root = new Item(name, category, price);
        else
            insert(root, name, category, price);
    }

    // Function to delete a node from the tree
    void delete_value(const string& name){
        if(name == root->itemName)
            return ; // can't remove root in this structure
        delete_node(root, name);
    }

    // Function to display the nodes of the tree in order
    void display(){
        display(root);
    }

    // Function to display the nodes of the tree sorted by itemName
    void displaySortByName(bool ascending){
        vector<Item*> items;
        displaySortByName(root, items);
        if(!ascending)
            reverse(items.begin(), items.end());
        for(Item* item : items)
            item->print();
    }

    // Function to display the nodes of the tree sorted by price
    void displaySortByPrice(bool ascending){
        vector<Item*> items;
        displaySortByPrice(root, items);
        if(ascending)
            sort(items.begin(), items.end(),[] (Item* first, Item* second) {return first->price < second->price;});
        else
            sort(items.begin(), items.end(), [] (Item* first, Item* second) {return first->price > second->price;});
        for(Item* item: items)
            item->print();
    }
};

int main(){
    BinarySearchTree bst;

    // Add some items to the tree
    bst.insert("Apple", "Fruit", 2);
    bst.insert("Banana", "Fruit", 1);
    bst.insert("Carrot", "Vegetable", 4);
    bst.insert("Daikon", "Vegetable", 3);
    bst.insert("Eggplant", "Vegetable", 6);
    bst.insert("Fig", "Fruit", 5);

    // Display the items
    cout << "Items in the tree:\n";
    bst.display();

    // Delete an item
    cout << "\nDeleting 'Carrot'...\n";
    bst.delete_value("Carrot");

    // Display the items again
    cout << "Items in the tree after deletion:\n";
    bst.display();

    // Sort and display the items by name
    cout << "\nItems sorted by name (ascending):\n";
    bst.displaySortByName(true);

    cout << "\nItems sorted by name (descending):\n";
    bst.displaySortByName(false);

    // Sort and display the items by price
    cout << "\nItems sorted by price (ascending):\n";
    bst.displaySortByPrice(true);

    cout << "\nItems sorted by price (descending):\n";
    bst.displaySortByPrice(false);

    return 0;
}
