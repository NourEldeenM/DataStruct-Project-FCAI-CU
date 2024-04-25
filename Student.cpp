#include "student.h"
#include "compare.h"

Student::Student(string id, string name, double gpa)
{
    this->id = id;
    this->name = name;
    this->gpa = gpa;
}

Student::Student()
{
    this->id = "";
    this->name = "";
    this->gpa = 0;
}

string Student::getId() const
{
    return id;
}

void Student::setId(string ID)
{
    this->id = ID;
}

string Student::getName() const
{
    return name;
}

void Student::setName(string Name)
{
    this->name = Name;
}

double Student::getGpa() const
{
    return gpa;
}

void Student::setGpa(double GPA)
{
    this->gpa = GPA;
}

template <typename Compare>
void Insertion_sort(vector<Student> &items, Compare comp)
{
    for (int i = 1, j; i < items.size(); i++)
    {
        Student tmp = items[i];
        for (j = i; j >= 0 && comp(tmp, items[j - 1]); j--)
            items[j] = items[j - 1];
        items[j] = tmp;
    }
}

template <typename Compare>
void Selection_sort(vector<Student> &items, Compare comp)
{
    for (int i = 0; i < items.size() - 1; i++)
    {
        int minIndex = i;
        for (int j = i + 1; j < items.size(); j++)
        {
            if (comp(items[j], items[minIndex]))
            {
                minIndex = j;
            }
        }
        if (minIndex != i)
        {
            swap(items[i], items[minIndex]);
        }
    }
}

template <typename Compare>
void bubbleSort(vector<Student> &students, Compare comp)
{
    int n = students.size();
    int i, j;
    bool swapped;
    for (i = 0; i < n - 1; i++)
    {
        swapped = false;
        for (j = 0; j < n - i - 1; j++)
        {
            if (comp(students[j], students[j + 1]))
            {
                swap(students[j], students[j + 1]);
                swapped = true;
            }
        }
        if (!swapped)
            break;
    }
}

template <typename Compare>
void quickSort(vector<Student> &students, Compare comp, int i, int j)
{
    if (i >= j)
        return;
    Student pivot = students[(i + j) / 2];
    // partition
    int left = i, right = j;
    while (left <= right)
    {
        while (comp(students[left], pivot))
            left++;
        while (comp(pivot, students[right]))
            right--;
        if (left <= right)
        {
            swap(students[left], students[right]);
            left++;
            right--;
        }
    };
    if (i < right)
        quickSort(students, comp, i, right);
    if (left < j)
        quickSort(students, comp, left, j);
}

// Wrapper function
template <typename Compare>
void quickSort(vector<Student> &students, Compare comp)
{
    quickSort(students, comp, 0, students.size() - 1);
}

template void Insertion_sort(vector<Student> &, CompareByGPA);
template void Insertion_sort(vector<Student> &, CompareByName);
template void Selection_sort(vector<Student> &, CompareByGPA);
template void Selection_sort(vector<Student> &, CompareByName);
template void bubbleSort(vector<Student> &, CompareByGPA);
template void bubbleSort(vector<Student> &, CompareByName);
template void quickSort(vector<Student> &, CompareByGPA);
template void quickSort(vector<Student> &, CompareByName);