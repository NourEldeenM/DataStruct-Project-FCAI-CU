#include "AVL.h"

template <typename Comparator>
AvlTree<Comparator>::AvlNode::AvlNode(const Item &i) : item(i), left(nullptr), right(nullptr), height(1) {}

template <typename Comparator>
int AvlTree<Comparator>::getHeight(AvlNode *node) const
{
    return node ? node->height : 0;
}

template <typename Comparator>
int AvlTree<Comparator>::getBalanceFactor(AvlNode *node) const
{
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

template <typename Comparator>
void AvlTree<Comparator>::updateHeight(AvlNode *node)
{
    if (node)
    {
        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    }
}

template <typename Comparator>
typename AvlTree<Comparator>::AvlNode *AvlTree<Comparator>::LL_Rotate(AvlNode *node)
{
    AvlNode *newRoot = node->left;
    node->left = newRoot->right;
    newRoot->right = node;
    updateHeight(node);
    updateHeight(newRoot);
    return newRoot;
}

template <typename Comparator>
typename AvlTree<Comparator>::AvlNode *AvlTree<Comparator>::RR_Rotate(AvlNode *node)
{
    AvlNode *newRoot = node->right;
    node->right = newRoot->left;
    newRoot->left = node;
    updateHeight(node);
    updateHeight(newRoot);
    return newRoot;
}

template <typename Comparator>
typename AvlTree<Comparator>::AvlNode *AvlTree<Comparator>::insert(AvlNode *node, const Item &item)
{
    if (!node)
        return new AvlNode(item);

    if (comp(item, node->item))
    {
        node->left = insert(node->left, item);
    }
    else if (comp(node->item, item))
    {
        node->right = insert(node->right, item);
    }
    else
    {
        return node;
    }

    updateHeight(node);
    int balance = getBalanceFactor(node);

    if (balance > 1)
    {
        if (comp(item, node->left->item))
        {
            return LL_Rotate(node);
        }
        else
        {
            node->left = RR_Rotate(node->left);
            return LL_Rotate(node);
        }
    }

    if (balance < -1)
    {
        if (comp(node->right->item, item))
        {
            return RR_Rotate(node);
        }
        else
        {
            node->right = LL_Rotate(node->right);
            return RR_Rotate(node);
        }
    }

    return node;
}

template <typename Comparator>
typename AvlTree<Comparator>::AvlNode *AvlTree<Comparator>::minValueNode(AvlNode *node) const
{
    AvlNode *current = node;
    while (current && current->left)
    {
        current = current->left;
    }
    return current;
}

template <typename Comparator>
typename AvlTree<Comparator>::AvlNode *AvlTree<Comparator>::deleteNode(AvlNode *root, const Item &item)
{
    if (!root)
        return root;

    if (comp(item, root->item))
    {
        root->left = deleteNode(root->left, item);
    }
    else if (comp(root->item, item))
    {
        root->right = deleteNode(root->right, item);
    }
    else
    {
        if (!root->left || !root->right)
        {
            AvlNode *temp = root->left ? root->left : root->right;
            if (!temp)
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
            root->right = deleteNode(root->right, temp->item);
        }
    }

    if (!root)
        return root;

    updateHeight(root);
    int balance = getBalanceFactor(root);

    if (balance > 1)
    {
        if (getBalanceFactor(root->left) >= 0)
        {
            return LL_Rotate(root);
        }
        else
        {
            root->left = RR_Rotate(root->left);
            return LL_Rotate(root);
        }
    }

    if (balance < -1)
    {
        if (getBalanceFactor(root->right) <= 0)
        {
            return RR_Rotate(root);
        }
        else
        {
            root->right = LL_Rotate(root->right);
            return RR_Rotate(root);
        }
    }

    return root;
}

template <typename Comparator>
void AvlTree<Comparator>::inorderTraversal(AvlNode *root) const
{
    if (root)
    {
        inorderTraversal(root->left);
        root->item.print();
        inorderTraversal(root->right);
    }
}

template <typename Comparator>
void AvlTree<Comparator>::collectItems(AvlNode *node, std::vector<Item> &items) const
{
    if (node)
    {
        collectItems(node->left, items);
        items.push_back(node->item);
        collectItems(node->right, items);
    }
}

template <typename Comparator>
void AvlTree<Comparator>::displayDescendingByComparatorHelper(AvlNode *node) const
{
    if (node)
    {
        displayDescendingByComparatorHelper(node->right);
        node->item.print();
        displayDescendingByComparatorHelper(node->left);
    }
}

template <typename Comparator>
AvlTree<Comparator>::AvlTree(Comparator c) : root(nullptr), comp(c) {}

template <typename Comparator>
void AvlTree<Comparator>::addItem(const Item &item)
{
    root = insert(root, item);
}

template <typename Comparator>
void AvlTree<Comparator>::removeItem(Item &item)
{
    root = deleteNode(root, item);
}

template <typename Comparator>
void AvlTree<Comparator>::display() const
{
    std::cout << "Items in the AVL tree:" << std::endl;
    inorderTraversal(root);
}

template <typename Comparator>
void AvlTree<Comparator>::displayAscendingByComparator() const
{
    inorderTraversal(root);
}

template <typename Comparator>
void AvlTree<Comparator>::displayDescendingByComparator() const
{
    displayDescendingByComparatorHelper(root);
}

template <typename Comparator>
void AvlTree<Comparator>::displaySortedByPrice(bool ascending)
{
    std::vector<Item> items;
    std::function<void(AvlNode *)> inorderCollect = [&](AvlNode *node)
    {
        if (node)
        {
            inorderCollect(node->left);
            items.push_back(node->item);
            inorderCollect(node->right);
        }
    };
    inorderCollect(root);

    if (ascending)
    {
        std::sort(items.begin(), items.end(), [](const Item &a, const Item &b)
                  { return a.getPrice() < b.getPrice(); });
    }
    else
    {
        std::sort(items.begin(), items.end(), [](const Item &a, const Item &b)
                  { return a.getPrice() > b.getPrice(); });
    }

    for (const auto &item : items)
    {
        item.print();
    }
}
struct ComparByName
{
    bool operator()(const Item &a, const Item &b) const
    {
        return a.getName() < b.getName();
    }
};

struct ComparByCategory
{
    bool operator()(const Item &a, const Item &b) const
    {
        return a.getCategory() < b.getCategory();
    }
};

struct ComparByPrice
{
    bool operator()(const Item &a, const Item &b) const
    {
        return a.getPrice() < b.getPrice();
    }
};

template class AvlTree<ComparByName>;
template class AvlTree<ComparByPrice>;
template class AvlTree<ComparByCategory>;
