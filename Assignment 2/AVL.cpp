#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Item {
    string itemName;
    string category;
    double price;

    Item(string name, string cat, double pr) : itemName(name), category(cat), price(pr) {}
};

struct CompareByName {
    bool operator()(const Item& a, const Item& b) const {
        return a.itemName < b.itemName;
    }
};

struct CompareByCategory {
    bool operator()(const Item& a, const Item& b) const {
        return a.category < b.category;
    }
};

struct CompareByPrice {
    bool operator()(const Item& a, const Item& b) const {
        return a.price < b.price;
    }
};

template<typename Item, typename Comparator>
class AvlTree {
private:
    struct AvlNode {
        Item item;
        AvlNode* left;
        AvlNode* right;
        int height;
        AvlNode(const Item& i) : item(i), left(nullptr), right(nullptr), height(1) {}
    };

    AvlNode* root;
    Comparator comp;

    int getHeight(AvlNode* node) const {
        return node ? node->height : 0;
    }

    int getBalanceFactor(AvlNode* node) const {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    void updateHeight(AvlNode* node) {
        if (node) {
            node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        }
    }

    AvlNode* LL_Rotate(AvlNode* node) {
        AvlNode* newRoot = node->left;
        node->left = newRoot->right;
        newRoot->right = node;
        updateHeight(node);
        updateHeight(newRoot);
        return newRoot;
    }

    AvlNode* RR_Rotate(AvlNode* node) {
        AvlNode* newRoot = node->right;
        node->right = newRoot->left;
        newRoot->left = node;
        updateHeight(node);
        updateHeight(newRoot);
        return newRoot;
    }

    AvlNode* insert(AvlNode* node, const Item& item) {
        if (!node) return new AvlNode(item);

        if (comp(item, node->item)) {
            node->left = insert(node->left, item);
        } else if (comp(node->item, item)) {
            node->right = insert(node->right, item);
        } else {
            return node; // Duplicate items are not allowed
        }

        updateHeight(node);
        int balance = getBalanceFactor(node);

        if (balance > 1) {
            if (comp(item, node->left->item)) {
                return LL_Rotate(node);
            } else {
                node->left = RR_Rotate(node->left);
                return LL_Rotate(node);
            }
        }

        if (balance < -1) {
            if (comp(node->right->item, item)) {
                return RR_Rotate(node);
            } else {
                node->right = LL_Rotate(node->right);
                return RR_Rotate(node);
            }
        }

        return node;
    }

    AvlNode* minValueNode(AvlNode* node) const {
        AvlNode* current = node;
        while (current && current->left) {
            current = current->left;
        }
        return current;
    }

    AvlNode* deleteNode(AvlNode* root, const Item& item) {
        if (!root) return root;

        if (comp(item, root->item)) {
            root->left = deleteNode(root->left, item);
        } else if (comp(root->item, item)) {
            root->right = deleteNode(root->right, item);
        } else {
            if (!root->left || !root->right) {
                AvlNode* temp = root->left ? root->left : root->right;
                if (!temp) {
                    temp = root;
                    root = nullptr;
                } else {
                    *root = *temp;
                }
                delete temp;
            } else {
                AvlNode* temp = minValueNode(root->right);
                root->item = temp->item;
                root->right = deleteNode(root->right, temp->item);
            }
        }

        if (!root) return root;

        updateHeight(root);
        int balance = getBalanceFactor(root);

        if (balance > 1) {
            if (getBalanceFactor(root->left) >= 0) {
                return LL_Rotate(root);
            } else {
                root->left = RR_Rotate(root->left);
                return LL_Rotate(root);
            }
        }

        if (balance < -1) {
            if (getBalanceFactor(root->right) <= 0) {
                return RR_Rotate(root);
            } else {
                root->right = LL_Rotate(root->right);
                return RR_Rotate(root);
            }
        }

        return root;
    }

    void inorderTraversal(AvlNode* root) const {
        if (root) {
            inorderTraversal(root->left);
            cout << root->item.itemName << " - " << root->item.category << " - $" << root->item.price << endl;
            inorderTraversal(root->right);
        }
    }

    void collectItems(AvlNode* node, vector<Item>& items) const {
        if (node) {
            collectItems(node->left, items);
            items.push_back(node->item);
            collectItems(node->right, items);
        }
    }

public:
    AvlTree(Comparator c) : root(nullptr), comp(c) {}

    void addItem(const Item& item) {
        root = insert(root, item);
    }

    void removeItem(const Item& item) {
        root = deleteNode(root, item);
    }

    void display() const {
        cout << "Items in the AVL tree:" << endl;
        inorderTraversal(root);
    }

    void displayAscendingByComparator() const {
        inorderTraversal(root);
    }

    void displayDescendingByComparatorHelper(AvlNode* node) const {
        if (node) {
            displayDescendingByComparatorHelper(node->right);
            cout << node->item.itemName << " - " << node->item.category << " - $" << node->item.price << endl;
            displayDescendingByComparatorHelper(node->left);
        }
    }

    void displayDescendingByComparator() const {
        displayDescendingByComparatorHelper(root);
    }

    void displayAscendingByPrice() const {
        vector<Item> items;
        collectItems(root, items);
        sort(items.begin(), items.end(), CompareByPrice());

        for (const auto& item : items) {
            cout << item.itemName << " - " << item.category << " - $" << item.price << endl;
        }
    }

    void displayDescendingByPrice() const {
        vector<Item> items;
        collectItems(root, items);
        sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
            return a.price > b.price;
        });

        for (const auto& item : items) {
            cout << item.itemName << " - " << item.category << " - $" << item.price << endl;
        }
    }
};

int main() {
    CompareByName compareByName;
    CompareByCategory compareByCategory;
    CompareByPrice compareByPrice;

    AvlTree<Item, CompareByName> treeByName(compareByName);
    AvlTree<Item, CompareByCategory> treeByCategory(compareByCategory);
    AvlTree<Item, CompareByPrice> treeByPrice(compareByPrice);

    vector<Item> items = {
            {"Apple", "Fruit", 2},
            {"Banana", "Fruit", 1},
            {"Daikon", "Vegetable", 3},
            {"Bread", "Bakery", 6},
            {"Milk", "Dairy", 10}
    };

    for (const auto& item : items) {
        treeByName.addItem(item);
        treeByCategory.addItem(item);
        treeByPrice.addItem(item);
    }

    cout << "Display all items:" << endl;
    treeByName.display();

    cout << "\nDisplay ascending by name:" << endl;
    treeByName.displayAscendingByComparator();

    cout << "\nDisplay descending by name:" << endl;
    treeByName.displayDescendingByComparator();

    cout << "\nDisplay ascending by category:" << endl;
    treeByCategory.displayAscendingByComparator();

    cout << "\nDisplay descending by category:" << endl;
    treeByCategory.displayDescendingByComparator();

    cout << "\nDisplay ascending by price:" << endl;
    treeByPrice.displayAscendingByPrice();

    cout << "\nDisplay descending by price:" << endl;
    treeByPrice.displayDescendingByPrice();

    return 0;
}