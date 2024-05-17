#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Item {
public:
    string itemName;
    string category;
    int price;

    Item(string n, string c, int p) : itemName(n), category(c), price(p) {}

    string getName() const {
        return itemName;
    }

    int getPrice() const {
        return price;
    }

    string getCategory() const {
        return category;
    }

    void print() const {
        cout << "Name: " << itemName << ", Category: " << category << ", Price: " << price << endl;
    }
};







struct CompareByName {
    bool operator()(const Item &a, const Item &b) const {
        return a.getName() < b.getName();
    }
};

struct CompareByCategory {
    bool operator()(const Item &a, const Item &b) const {
        return a.getCategory() < b.getCategory();
    }
};

struct CompareByPrice {
    bool operator()(const Item &a, const Item &b) const {
        return a.getPrice() < b.getPrice();
    }
};







template<typename Comparator>
class AvlNode {
public:
    Item item;
    AvlNode *left;
    AvlNode *right;
    int height;
    Comparator comp;

    AvlNode(const Item &item, Comparator comp)
            : item(item), left(nullptr), right(nullptr), height(0), comp(comp) {}
};

template<typename Comparator>
class AvlTree {
private:
    AvlNode<Comparator> *root;
    Comparator comp;

    // Return the height for the node
    int getHeight(AvlNode<Comparator> *N) {
        if (N == nullptr)
            return -1;

        int leftHeight = getHeight(N->left);
        int rightHeight = getHeight(N->right);

        return max(leftHeight, rightHeight) + 1;
    }

    // Get the balance factor of each node
    int getBalanceFactor(AvlNode<Comparator> *N) {
        if (N == nullptr)
            return 0;
        return getHeight(N->left) - getHeight(N->right);
    }

    AvlNode<Comparator> *LL_Rotate(AvlNode<Comparator> *root) {
        AvlNode<Comparator> *LCh = root->left;  // LCh  : left child
        AvlNode<Comparator> *LRCh = LCh->right; // LRCh   : left right child

        LCh->right = root;
        root->left = LRCh;

        root->height = getHeight(root);
        LCh->height = getHeight(LCh);
        return LCh;
    }

    AvlNode<Comparator> *RR_Rotate(AvlNode<Comparator> *root) {
        AvlNode<Comparator> *rightCh = root->right;   // rightCh  : right child
        AvlNode<Comparator> *leftRCh = rightCh->left; // leftRCh : right child then right

        rightCh->left = root;
        root->right = leftRCh;

        root->height = getHeight(root);
        rightCh->height = getHeight(rightCh);
        return rightCh;
    }

    AvlNode<Comparator> *insert(AvlNode<Comparator> *node, const Item &item) {
        if (node == nullptr) {
            return new AvlNode<Comparator>(item, comp);
        }

        if (comp(item, node->item)) {
            node->left = insert(node->left, item);
        } else if (comp(node->item, item)) {
            node->right = insert(node->right, item);
        } else {
            return node;
        }

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));

        int balance = getBalanceFactor(node);

        if (balance > 1 && comp(item, node->left->item)) {
            return LL_Rotate(node);
        }

        if (balance < -1 && comp(node->right->item, item)) {
            return RR_Rotate(node);
        }

        if (balance > 1 && comp(node->left->item, item)) {
            node->left = RR_Rotate(node->left);
            return LL_Rotate(node);
        }

        if (balance < -1 && comp(item, node->right->item)) {
            node->right = LL_Rotate(node->right);
            return RR_Rotate(node);
        }

        return node;
    }

    AvlNode<Comparator> *minValueNode(AvlNode<Comparator> *node) {
        AvlNode<Comparator> *current = node;
        while (current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    AvlNode<Comparator> *deleteNode(AvlNode<Comparator> *root, const Item &item) {
        if (root == nullptr) {
            return root;
        }
        if (comp(item, root->item)) {
            root->left = deleteNode(root->left, item);
        } else if (comp(root->item, item)) {
            root->right = deleteNode(root->right, item);
        } else {
            if ((root->left == nullptr) || (root->right == nullptr)) {
                AvlNode<Comparator> *temp = root->left ? root->left : root->right;

                if (temp == nullptr) {
                    temp = root;
                    root = nullptr;
                } else {
                    *root = *temp;
                }
                delete temp;
            } else {
                AvlNode<Comparator> *temp = minValueNode(root->right);

                root->item = temp->item;

                root->right = deleteNode(root->right, temp->item);
            }
        }

        if (root == nullptr) {
            return root;
        }

        root->height = getHeight(root);

        int balance = getBalanceFactor(root);

        if (balance > 1 && getBalanceFactor(root->left) >= 0) {
            return LL_Rotate(root);
        }

        if (balance > 1 && getBalanceFactor(root->left) < 0) {
            root->left = RR_Rotate(root->left);
            return LL_Rotate(root);
        }

        if (balance < -1 && getBalanceFactor(root->right) <= 0) {
            return RR_Rotate(root);
        }

        if (balance < -1 && getBalanceFactor(root->right) > 0) {
            root->right = LL_Rotate(root->right);
            return RR_Rotate(root);
        }

        return root;
    }

    void inorderTraversal(AvlNode<Comparator> *root) const {
        if (root != nullptr) {
            inorderTraversal(root->left);
            cout << root->item.itemName << " - " << root->item.category << " - $" << root->item.price << endl;
            inorderTraversal(root->right);
        }
    }

    void collectItems(AvlNode<Comparator> *node, vector<Item> &items) const {
        if (node != nullptr) {
            collectItems(node->left, items);
            items.push_back(node->item);
            collectItems(node->right, items);
        }
    }

public:
    AvlTree(Comparator comp) : root(nullptr), comp(comp) {}

    void addItem(const Item &item) {
        root = insert(root, item);
    }

    void removeItem(const Item &item) {
        root = deleteNode(root, item);
    }

    void display() const {
        cout << "Items in the AVL tree:" << endl;
        inorderTraversal(root);
    }

    void displayAscendingByComparator() const {
        inorderTraversal(root);
    }

    void displayDescendingByComparatorHelper(AvlNode<Comparator> *node) const {
        if (node != nullptr) {
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

        for (const Item &item: items) {
            cout << item.itemName << " - " << item.category << " - $" << item.price << endl;
        }
    }

    void displayDescendingByPrice() const {
        vector<Item> items;
        collectItems(root, items);

        sort(items.begin(), items.end(), [](const Item &a, const Item &b) {
            return a.price > b.price;
        });

        for (const Item &item: items) {
            cout << item.itemName << " - " << item.category << " - $" << item.price << endl;
        }
    }
};

int main() {
    Item item1("Apple", "Fruit", 2);
    Item item2("Banana", "Fruit", 1);
    Item item3("Carrot", "Vegetable", 4);
    Item item4("Daikon", "Vegetable", 3);
    Item item5("Eggplant", "Vegetable", 6);
    Item item6("Fig", "Fruit", 5);
    CompareByName compareByName;
    AvlTree<CompareByName> avlByName(compareByName);
    avlByName.addItem(item1);
    avlByName.addItem(item2);
    avlByName.addItem(item3);
    avlByName.addItem(item4);
    avlByName.addItem(item5);
    avlByName.addItem(item6);

    cout << "\nItems sorted by name:" << endl;
    avlByName.display();


    CompareByCategory compareByCategory;
    AvlTree<CompareByCategory> avlByCategory(compareByCategory);
    avlByCategory.addItem(item1);
    avlByCategory.addItem(item2);
    avlByCategory.addItem(item3);
    avlByCategory.addItem(item4);
    avlByCategory.addItem(item5);
    avlByCategory.addItem(item6);

    cout << "\nItems sorted by category:" << endl;
    avlByCategory.display();

    CompareByPrice compareByPrice;
    AvlTree<CompareByPrice> avlByPrice(compareByPrice);
    avlByPrice.addItem(item1);
    avlByPrice.addItem(item2);
    avlByPrice.addItem(item3);
    avlByPrice.addItem(item4);
    avlByPrice.addItem(item5);
    avlByPrice.addItem(item6);

    cout << "\nItems sorted by price:" << endl;
    avlByPrice.display();

    return 0;
}
