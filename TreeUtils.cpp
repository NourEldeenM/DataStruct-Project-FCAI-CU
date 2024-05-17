#include "TreeUtils.h"
#include "Item.h"

void readItems(const string &filename, Tree &tree)
{
    ifstream inputFile(filename);
    if (!inputFile)
    {
        cerr << "Unable to open file: " << filename << endl;
        return;
    }

    string line;
    while (getline(inputFile, line))
    {
        istringstream iss(line);
        int quantity;
        if (!(iss >> quantity))
        {
            cerr << "Invalid input format: " << line << endl;
            continue;
        }
        for (int i = 0; i < quantity; ++i)
        {
            string name, category;
            int price;
            getline(inputFile >> ws, name);
            getline(inputFile >> ws, category);
            inputFile >> price;
            inputFile.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore newline

            Item item(name, category, price);
            tree.insert(item);
        }
    }

    inputFile.close();
}

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