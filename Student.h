#ifndef DATASTRUCT_PROJECT_FCAI_CU_STUDENT_H
#define DATASTRUCT_PROJECT_FCAI_CU_STUDENT_H

#include "bits/stdc++.h"

using namespace std;

class Student {
public:
    string id;
    string name;
    double gpa;

    Student(string id, string name, double gpa);

    Student();

    string getId() const { return id; }

    void setId(string ID) { this->id = ID; }

    string getName() const { return name; }

    void setName(string Name) { this->name = Name; }

    double getGpa() const { return gpa; }

    void setGpa(double GPA) { this->gpa = GPA; }

    template<typename T, typename Compare>
    friend void Insertion_sort(vector<Student> &items, Compare comp);

    template<typename Student, typename Compare>
    friend void Selection_sort(vector<Student> &students, Compare comp);

};


#endif //DATASTRUCT_PROJECT_FCAI_CU_STUDENT_H
