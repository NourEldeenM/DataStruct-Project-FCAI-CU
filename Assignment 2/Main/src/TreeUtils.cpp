#include "TreeUtils.h"
#include "Item.h"

struct CompareByName
{
    bool operator()(const Item &a, const Item &b) const
    {
        return a.getName() < b.getName();
    }
};

struct CompareByCategory
{
    bool operator()(const Item &a, const Item &b) const
    {
        return a.getCategory() < b.getCategory();
    }
};

struct CompareByPrice
{
    bool operator()(const Item &a, const Item &b) const
    {
        return a.getPrice() < b.getPrice();
    }
};

struct NameComparison {
    bool operator()(const Item *a, const Item *b) const {
        return a->getName() < b->getName();
    }
};

struct CategoryComparison {
    bool operator()(const Item *a, const Item *b) const {
        return a->getCategory() < b->getCategory();
    }
};

struct PriceComparison {
    bool operator()(const Item *a, const Item *b) const {
        return a->getPrice() < b->getPrice();
    }
};

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


template<typename Comparator>
void readItemsToHeap(const std::string &filename, Heap<Comparator> &tree) {
    std::ifstream inputFile(filename);
    if (!inputFile) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        // Read quantity
        int quantity;
        std::istringstream iss(line);
        if (!(iss >> quantity)) {
            continue; // Skip to next line
        }

        // Read items
        for (int i = 0; i < quantity; ++i) {
            std::string name, category;
            int price;

            if (!std::getline(inputFile, name) || name.empty()) {
                continue; // Skip to next item
            }

            if (!std::getline(inputFile, category) || category.empty()) {
                continue; // Skip to next item
            }

            if (!(inputFile >> price)) {
                inputFile.clear(); // Clear error flag
                inputFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore rest of the line
                continue; // Skip to next item
            }

            inputFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore newline

            // Construct item and add to tree
            Item item(name, category, price);
            tree.addItem(item);
        }
    }

    inputFile.close();
}

template<typename Comparator>
void readItemsToBST(const std::string &filename, BinarySearchTree<Comparator> &tree) {
    std::ifstream inputFile(filename);
    if (!inputFile) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        // Read quantity
        int quantity;
        std::istringstream iss(line);
        if (!(iss >> quantity)) {
            continue; // Skip to next line
        }

        // Read items
        for (int i = 0; i < quantity; ++i) {
            std::string name, category;
            int price;

            if (!std::getline(inputFile, name) || name.empty()) {
                continue; // Skip to next item
            }

            if (!std::getline(inputFile, category) || category.empty()) {
                continue; // Skip to next item
            }

            if (!(inputFile >> price)) {
                inputFile.clear(); // Clear error flag
                inputFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore rest of the line
                continue; // Skip to next item
            }

            inputFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore newline

            // Construct item and add to tree
            Item* item = new Item(name, category, price); // Dynamically allocate the item
            tree.insert(item); // Insert the item into the tree
        }
    }

    inputFile.close();
}

template<typename Comparator>
void readItemsToAVL(const std::string &filename, AvlTree<Comparator> &tree) {
    std::ifstream inputFile(filename);
    if (!inputFile) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        // Read quantity
        int quantity;
        std::istringstream iss(line);
        if (!(iss >> quantity)) {
            continue; // Skip to next line
        }

        // Read items
        for (int i = 0; i < quantity; ++i) {
            std::string name, category;
            int price;

            if (!std::getline(inputFile, name) || name.empty()) {
                continue; // Skip to next item
            }

            if (!std::getline(inputFile, category) || category.empty()) {
                continue; // Skip to next item
            }

            if (!(inputFile >> price)) {
                inputFile.clear(); // Clear error flag
                inputFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore rest of the line
                continue; // Skip to next item
            }

            inputFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore newline

            // Construct item and add to tree
            Item* item = new Item(name, category, price); // Dynamically allocate the item
            tree.addItem(*item); // Insert the item into the tree
        }
    }

    inputFile.close();
}



// Explicit instantiation of required templates
template void readItemsToHeap(const std::string &filename, Heap<CompareByName> &tree);
template void readItemsToHeap(const std::string &filename, Heap<CompareByPrice> &tree);
template void readItemsToHeap(const std::string &filename, Heap<CompareByCategory> &tree);

template void readItemsToBST(const std::string &filename, BinarySearchTree<NameComparison> &tree);
template void readItemsToBST(const std::string &filename, BinarySearchTree<PriceComparison> &tree);
template void readItemsToBST(const std::string &filename, BinarySearchTree<CategoryComparison> &tree);

template void readItemsToAVL(const std::string &filename, AvlTree<ComparByName> &tree);
template void readItemsToAVL(const std::string &filename, AvlTree<ComparByPrice> &tree);
template void readItemsToAVL(const std::string &filename, AvlTree<ComparByCategory> &tree);