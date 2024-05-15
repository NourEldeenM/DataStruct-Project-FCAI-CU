#ifndef ITEM_H
#define ITEM_H

#include <bits/stdc++.h>
using namespace std;

class Item
{
public:
    string itemName;
    string category;
    int price;

    Item(const string &n, const string &c, int p);

    bool operator<(const Item &other) const;
    bool operator>(const Item &other) const;
    bool operator==(const Item &other) const;

    friend ostream &operator<<(ostream &os, const Item &item);
};

#endif // ITEM_H
