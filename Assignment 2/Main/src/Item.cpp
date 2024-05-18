#include "Item.h"

Item::Item() : name(""), category(""), price(0) {}

Item::Item(const string &n, const string &c, int p) : name(n), category(c), price(p) {}

void Item::print() const
{
    cout << "Name: " << name << ", Category: " << category << ", Price: " << price << endl;
}

string Item::getName() const
{
    return name;
}

string Item::getCategory() const
{
    return category;
}

int Item::getPrice() const
{
    return price;
}

bool Item::operator<(const Item &other) const
{
    return name < other.name;
}

bool Item::operator>(const Item &other) const
{
    return name > other.name;
}

bool Item::operator==(const Item &other) const
{
    return name == other.name && category == other.category && price == other.price;
}

Item &Item::operator=(const Item &other)
{
    if (this != &other)
    {
        name = other.name;
        category = other.category;
        price = other.price;
    }
    return *this;
}

ostream &operator<<(ostream &os, const Item &item)
{
    os << "Name: " << item.name << ", Category: " << item.category << ", Price: " << item.price;
    return os;
}

istream &operator>>(istream &is, Item &item)
{
    cout << "Enter item name: ";
    getline(is >> ws, item.name);

    cout << "Enter item category: ";
    getline(is >> ws, item.category);

    cout << "Enter item price: ";
    is >> item.price;

    return is;
}
