#include <bits/stdc++.h>
#include "Student.h"

using namespace std;

vector<Student> readInputFromFile() {
    vector<Student> students;
    ifstream fin("students.txt");
    if (fin.fail()) {
        cout << "Error opening file\n";
        return students;
    }
    int num_Students;
    fin >> num_Students;
    fin.ignore();
    for (int i = 0; i < num_Students; ++i) {
        Student student;
        fin.ignore();
        getline(fin, student.name);
        fin >> student.id;
        fin.ignore();
        fin >> student.gpa;
        fin.ignore();
        students.push_back(student);
    }
    fin.close();
    return students;
}

int main() {
    vector<Student> students = readInputFromFile();
    // example to check code
    Selection_sort(students, [](Student &a, Student &b) { return a.gpa < b.gpa; });
    cout << "*By GPA*\n";
    for (auto x: students)
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