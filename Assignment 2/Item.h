#ifndef ITEM_H
#define ITEM_H

#include <bits/stdc++.h>
using namespace std;

class Item
{
private:
    string name;
    string category;
    int price;

public:
    Item();
    Item(const string &n, const string &c, int p);
    void print() const;
    string getName() const;
    int getPrice() const;
    string getCategory() const;

    bool operator<(const Item &other) const;
    bool operator>(const Item &other) const;
    bool operator==(const Item &other) const;
    Item &operator=(const Item &other);

    friend ostream &operator<<(ostream &os, const Item &item);
    friend istream &operator>>(istream &is, Item &item);
};

#endif // ITEM_H
