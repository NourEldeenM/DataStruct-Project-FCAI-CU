#ifndef COMPARE_H
#define COMPARE_H

#include "student.h"

class CompareByGPA
{
public:
    bool operator()(const Student &a, const Student &b) const
    {
        return a.gpa < b.gpa;
    }
};

class CompareByName
{
public:
    bool operator()(const Student &a, const Student &b) const
    {
        return a.name < b.name;
    }
};

#endif // COMPARE_H
