#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// Define the Item class
class Item
{
public:
    string itemName;
    string category;
    int price;

    Item(string n, string c, int p) : itemName(n), category(c), price(p) {}

    // Overload the less than operator for comparison based on itemName
    bool operator<(const Item &other) const
    {
        return itemName < other.itemName;
    }

    // Function to print the details of the item
    void print() const
    {
        cout << "Name: " << itemName << ", Category: " << category << ", Price: " << price << endl;
    }
};

class AvlNode
{
public:
    Item item;
    AvlNode *left;
    AvlNode *right;
    int height;
    AvlNode *root; // Add root member variable

    AvlNode(const Item &item) : item(item), left(nullptr), right(nullptr), height(0), root(nullptr) {} // Initialize root to nullptr in the constructor

    // Function declarations...

    void addItem(const Item &item);
    void removeItem(const string &itemName);
    void inorderTraversal(AvlNode *root) const;
    void display() const;
    void displayAscendingByName() const;
    void displayDescendingByName() const;
    void displayDescendingByNameHelper(AvlNode *node) const;
    void collectItems(AvlNode *node, std::vector<Item> &items) const;
    void displayAscendingByPrice() const;
    void displayDescendingByPrice() const;
};

// return the height for the node
int getHeight(AvlNode *N)
{
    if (N == nullptr)
        return -1;

    int leftHeight = getHeight(N->left);
    int rightHeight = getHeight(N->right);

    return max(leftHeight, rightHeight) + 1;
}

// Get the balance factor of each node
int getBalanceFactor(AvlNode *N)
{
    if (N == nullptr)
        return 0;
    return getHeight(N->left) - getHeight(N->right);
}

AvlNode *LL_Rotate(AvlNode *root)
{
    AvlNode *LCh = root->left;  // LCh  : left child
    AvlNode *LRCh = LCh->right; // LRCh   :left right child

    LCh->right = root;
    root->left = LRCh;

    root->height = getHeight(root);
    LCh->height = getHeight(LCh);
    return LCh;
}

AvlNode *RR_Rotate(AvlNode *root)
{
    AvlNode *rightCh = root->right;   // rightCh  : right child
    AvlNode *leftRCh = rightCh->left; // leftRCh :right child then right

    rightCh->left = root;
    root->right = leftRCh;

    root->height = getHeight(root);
    rightCh->height = getHeight(rightCh);
    return rightCh;
}

AvlNode *insert(AvlNode *node, const Item &item)
{
    if (node == nullptr)
    {
        return new AvlNode(item);
    }

    if (item.itemName < node->item.itemName)
    {
        node->left = insert(node->left, item);
    }
    else if (item.itemName > node->item.itemName)
    {
        node->right = insert(node->right, item);
    }
    else
    {
        return node;
    }

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    int balance = getBalanceFactor(node);

    if (balance > 1 && item.itemName < node->left->item.itemName)
    {
        return LL_Rotate(node);
    }

    if (balance < -1 && item.itemName > node->right->item.itemName)
    {
        return RR_Rotate(node);
    }

    if (balance > 1 && item.itemName > node->left->item.itemName)
    {
        node->left = RR_Rotate(node->left);
        return LL_Rotate(node);
    }

    if (balance < -1 && item.itemName < node->right->item.itemName)
    {
        node->right = LL_Rotate(node->right);
        return RR_Rotate(node);
    }

    return node;
}

AvlNode *minValueNode(AvlNode *node)
{
    AvlNode *current = node;
    while (current->left != nullptr)
    {
        current = current->left;
    }
    return current;
}

AvlNode *deleteNode(AvlNode *root, const string &key)
{
    if (root == nullptr)
    {
        return root;
    }
    if (key < root->item.itemName)
    {
        root->left = deleteNode(root->left, key);
    }
    else if (key > root->item.itemName)
    {
        root->right = deleteNode(root->right, key);
    }
    else
    {
        if ((root->left == nullptr) || (root->right == nullptr))
        {
            AvlNode *temp = root->left ? root->left : root->right;

            if (temp == nullptr)
            {
                temp = root;
                root = nullptr;
            }
            else
            {
                *root = *temp;
            }
            delete temp;
        }
        else
        {
            AvlNode *temp = minValueNode(root->right);

            root->item = temp->item;

            root->right = deleteNode(root->right, temp->item.itemName);
        }
    }

    if (root == nullptr)
    {
        return root;
    }

    root->height = getHeight(root);

    int balance = getBalanceFactor(root);

    if (balance > 1 && getBalanceFactor(root->left) >= 0)
    {
        return LL_Rotate(root);
    }

    if (balance > 1 && getBalanceFactor(root->left) < 0)
    {
        root->left = RR_Rotate(root->left);
        return LL_Rotate(root);
    }

    if (balance < -1 && getBalanceFactor(root->right) <= 0)
    {
        return RR_Rotate(root);
    }

    if (balance < -1 && getBalanceFactor(root->right) > 0)
    {
        root->right = LL_Rotate(root->right);
        return RR_Rotate(root);
    }

    return root;
}

void AvlNode::inorderTraversal(AvlNode *root) const
{
    if (root != nullptr)
    {
        inorderTraversal(root->left);
        cout << root->item.itemName << " - " << root->item.category << " - $" << root->item.price << endl;
        inorderTraversal(root->right);
    }
}

void AvlNode::addItem(const Item &item)
{
    root = insert(root, item);
}

void AvlNode::removeItem(const string &itemName)
{
    root = deleteNode(root, itemName);
}

void AvlNode::display() const
{
    cout << "Items in the AVL tree:" << endl;
    inorderTraversal(root);
}

void AvlNode::displayAscendingByName() const
{
    inorderTraversal(root);
}

void AvlNode::displayDescendingByNameHelper(AvlNode *node) const
{
    if (node != nullptr)
    {
        displayDescendingByNameHelper(node->right);
        cout << node->item.itemName << " - " << node->item.category << " - $" << node->item.price << endl;
        displayDescendingByNameHelper(node->left);
    }
}

void AvlNode::collectItems(AvlNode *node, std::vector<Item> &items) const
{
    if (node != nullptr)
    {
        collectItems(node->left, items);
        items.push_back(node->item);
        collectItems(node->right, items);
    }
}

bool priceAscendingComparator(const Item &a, const Item &b)
{
    return a.price < b.price;
}

void AvlNode::displayAscendingByPrice() const
{
    vector<Item> items;
    collectItems(root, items);

    sort(items.begin(), items.end(), priceAscendingComparator);

    for (const Item &item : items)
    {
        cout << item.itemName << " - " << item.category << " - $" << item.price << endl;
    }
}

bool priceDescendingComparator(const Item &a, const Item &b)
{
    return a.price > b.price;
}

void AvlNode::displayDescendingByPrice() const
{
    vector<Item> items;
    collectItems(root, items);

    sort(items.begin(), items.end(), priceDescendingComparator);

    for (const Item &item : items)
    {
        cout << item.itemName << " - " << item.category << " - $" << item.price << endl;
    }
}

int main()
{

    Item item1("Apple", "Fruit", 2);
    Item item2("Banana", "Fruit", 1);
    Item item3("Carrot", "Vegetable", 4);
    Item item4("Daikon", "Vegetable", 3);
    Item item5("Eggplant", "Vegetable", 6);
    Item item6("Fig", "Fruit", 5);

    AvlNode avl(item1);

    // Add some items to the tree
    avl.addItem(item1);
    avl.addItem(item2);
    avl.addItem(item3);
    avl.addItem(item4);
    avl.addItem(item5);
    avl.addItem(item6);

    // Display the items
    cout << "Items in the tree:\n";
    avl.display();

    // Delete an item
    cout << "\nDeleting 'Carrot'...\n";
    avl.removeItem("Carrot");

    // Display the items again
    cout << "Items in the tree after deletion:\n";
    avl.display();

    // Sort and display the items by name
    cout << "\nItems sorted by name (ascending):\n";
    avl.displayAscendingByName();

    // Sort and display the items by price
    cout << "\nItems sorted by price (ascending):\n";
    avl.displayAscendingByPrice();

    // Sort and display the items by price in descending order
    cout << "\nItems sorted by price (descending):\n";
    avl.displayDescendingByPrice();

    return 0;
}
