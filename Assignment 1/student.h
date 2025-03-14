#ifndef DATASTRUCT_PROJECT_FCAI_CU_STUDENT_H
#define DATASTRUCT_PROJECT_FCAI_CU_STUDENT_H

#include <bits/stdc++.h>
using namespace std;

class CompareByGPA;
class CompareByName;

class Student
{
public:
    string id;
    string name;
    double gpa;

    Student(string id, string name, double gpa);

    Student();

    string getId() const;

    void setId(string ID);

    string getName() const;

    void setName(string Name);

    double getGpa() const;

    void setGpa(double GPA);

    template <typename Compare>
    friend void insertionSort(vector<Student> &students, Compare comp, const string &filename);

    template <typename Compare>
    friend void selectionSort(vector<Student> &students, Compare comp, const string &filename);

    template <typename Compare>
    friend void bubbleSort(vector<Student> &students, Compare comp, const string &filename);

    template <typename Compare>
    friend void quickSort(vector<Student> &students, Compare comp, const string &filename);

    template <typename Compare>
    friend void mergeSort(vector<Student> &students, Compare comp, const string &filename);

    template <typename Compare>
    friend void shellSort(vector<Student> &students, Compare comp, const string &filename);

    template <typename Compare>
    friend void countSort(vector<Student> &students, Compare comp, const string &filename);
};

#endif // DATASTRUCT_PROJECT_FCAI_CU_STUDENT_H
