#include "BST.h"

template <typename Comparator>
BinarySearchTree<Comparator>::BinarySearchTree(Comparator comp) : data(nullptr), compare(comp), left(nullptr), right(nullptr)
{
}

template <typename Comparator>
BinarySearchTree<Comparator>::BinarySearchTree(Item *data, Comparator comp) : data(data), compare(comp), left(nullptr), right(nullptr)
{
}

template <typename Comparator>
BinarySearchTree<Comparator> *BinarySearchTree<Comparator>::min_node()
{
    BinarySearchTree *cur = this;
    while (cur && cur->left)
        cur = cur->left;
    return cur;
}

template <typename Comparator>
void BinarySearchTree<Comparator>::special_delete(BinarySearchTree *child)
{
    left = child->left;
    right = child->right;
    data = child->data;
    delete child;
}

template <typename Comparator>
BinarySearchTree<Comparator> *BinarySearchTree<Comparator>::delete_node(BinarySearchTree *node, Item *item)
{
    if (!node)
        return nullptr;

    if (compare(item, node->data))
        node->left = delete_node(node->left, item);
    else if (compare(node->data, item))
        node->right = delete_node(node->right, item);
    else
    {
        if (!node->left && !node->right)
        {
            delete node;
            return nullptr;
        }
        else if (!node->left)
        {
            node->special_delete(node->right);
        }
        else if (!node->right)
        {
            node->special_delete(node->left);
        }
        else
        {
            BinarySearchTree *mn = node->right->min_node();
            node->data = mn->data;
            node->right = delete_node(node->right, mn->data);
        }
    }
    return node;
}

template <typename Comparator>
void BinarySearchTree<Comparator>::display(BinarySearchTree *node)
{
    if (node)
    {
        display(node->left);
        node->data->print();
        display(node->right);
    }
}

template <typename Comparator>
void BinarySearchTree<Comparator>::displaySortByName(BinarySearchTree *node, std::vector<Item *> &items)
{
    if (node)
    {
        if (node->left)
            displaySortByName(node->left, items);
        items.push_back(node->data);
        if (node->right)
            displaySortByName(node->right, items);
    }
}

template <typename Comparator>
void BinarySearchTree<Comparator>::displaySortByPrice(BinarySearchTree *node, std::vector<Item *> &items)
{
    if (node)
    {
        if (node->left)
            displaySortByPrice(node->left, items);
        items.push_back(node->data);
        if (node->right)
            displaySortByPrice(node->right, items);
    }
}

template <typename Comparator>
void BinarySearchTree<Comparator>::insert(Item *item)
{
    if (data == nullptr)
    {
        data = new Item(*item);
    }
    else
    {
        if (compare(item, data))
        {
            if (!left)
            {
                left = new BinarySearchTree(compare);
            }
            left->insert(item);
        }
        else if (compare(data, item))
        {
            if (!right)
            {
                right = new BinarySearchTree(compare);
            }
            right->insert(item);
        }
    }
}

template <typename Comparator>
bool BinarySearchTree<Comparator>::delete_item(Item *item)
{
    if (item->getName() == data->getName() && !left && !right)
        return false;
    delete_node(this, item);
    return true;
}

template <typename Comparator>
void BinarySearchTree<Comparator>::display()
{
    display(this);
}

template <typename Comparator>
void BinarySearchTree<Comparator>::displaySortByName(bool ascending)
{
    std::vector<Item *> items;
    displaySortByName(this, items);
    std::sort(items.begin(), items.end(), [ascending](Item *first, Item *second)
              { return ascending ? first->getName() < second->getName() : first->getName() > second->getName(); });
    for (Item *item : items)
        item->print();
}

template <typename Comparator>
void BinarySearchTree<Comparator>::displaySortByPrice(bool ascending)
{
    std::vector<Item *> items;
    displaySortByPrice(this, items);
    std::sort(items.begin(), items.end(), [ascending](Item *first, Item *second)
              { return ascending ? first->getPrice() < second->getPrice() : first->getPrice() > second->getPrice(); });
    for (Item *item : items)
        item->print();
}

template <typename Comparator>
Item *BinarySearchTree<Comparator>::search(Item *item)
{
    BinarySearchTree *current = this;
    while (current)
    {
        if (item->getName() < current->data->getName())
            current = current->left;
        else if (current->data->getName() < item->getName())
            current = current->right;
        else
            return current->data;
    }
    return nullptr;
}

struct NameComparison
{
    bool operator()(const Item *a, const Item *b) const
    {
        return a->getName() < b->getName();
    }
};

struct CategoryComparison
{
    bool operator()(const Item *a, const Item *b) const
    {
        return a->getCategory() < b->getCategory();
    }
};

struct PriceComparison
{
    bool operator()(const Item *a, const Item *b) const
    {
        return a->getPrice() < b->getPrice();
    }
};

template class BinarySearchTree<NameComparison>;
template class BinarySearchTree<CategoryComparison>;
template class BinarySearchTree<PriceComparison>;