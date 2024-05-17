#ifndef TREEUTILS_H
#define TREEUTILS_H

#include "Tree.h"
#include <string>

void readItems(const string &filename, Tree &tree);

struct CompareByName;
struct CompareByCategory;
struct CompareByPrice;

#endif // TREEUTILS_H
