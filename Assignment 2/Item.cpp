#include "Item.h"

Item::Item(const string &n, const string &c, int p) : itemName(n), category(c), price(p) {}

bool Item::operator<(const Item &other) const
{
    return itemName < other.itemName;
}

bool Item::operator>(const Item &other) const
{
    return itemName > other.itemName;
}

bool Item::operator==(const Item &other) const
{
    return itemName == other.itemName;
}

ostream &operator<<(ostream &os, const Item &item)
{
    os << "Name: " << item.itemName << ", Category: " << item.category << ", Price: " << item.price;
    return os;
}
