#include <bits/stdc++.h>

using namespace std;

class Student
{
public:
    string id;
    string name;
    double gpa;

    Student(string id, string name, double gpa)
    {
        this->id = id;
        this->name = name;
        this->gpa = gpa;
    }

  
    template <typename T, typename Compare>
    friend void Insertion_sort(vector<T> &items, Compare comp);
    template <typename Student, typename Compare>
    friend void Selection_sort(vector<Student> &students, Compare comp);
    
};
template <typename T, typename Compare>
void Insertion_sort(vector<T> &items, Compare comp)
{
    for (int i = 1, j; i < items.size(); i++)
    {
        T tmp = items[i];

        for (j = i; j > 0 && comp(tmp, items[j - 1]); j--)
            items[j] = items[j - 1];
        items[j] = tmp;
    }
}

template <typename student, typename Compare>
void Selection_sort(vector<student> &items, Compare comp)
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



int main()
{
    // example to check code
    Student adel("20220173", "Adel", 3.32);
    Student zeyad("20220146", "zeyad", 3.45);
    vector<Student> students = {zeyad, adel};
    Selection_sort(students,[](Student &a,Student &b)
    {return a.gpa<b.gpa;});
    cout << "*By GPA*\n";
    for (auto x : students)
        cout << x.name << '\n'
             << x.id << '\n'
             << x.gpa << "\n\n";

    // cout << "*By NAME*\n";
    // Insertion_sortByname(students);
    // for (auto x : students)
    // cout << x.name << '\n'
    //      << x.id << '\n'
    //      << x.gpa << "\n\n";
    return 0;
}