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

    friend void Insertion_sortByGpa(vector<Student> &students);
    friend void Insertion_sortByName(vector<Student> &students);
    friend void Selection_sortByGpa(vector<Student> &students);
    friend void Selection_sortByName(vector<Student> &students);
};

void Selection_sortByGpa(vector<Student> &students){
     for (int i = 0, j, least; i < students.size() - 1; i++)
    {

        for (j = i + 1, least = i; j < students.size(); j++)

            if (students[j].gpa < students[least].gpa)
                least = j;
        swap(students[least], students[i]);
    }
}

void Selection_sortByName(vector<Student> &students){
     for (int i = 0, j, least; i < students.size() - 1; i++)
    {

        for (j = i + 1, least = i; j < students.size(); j++)

            if (students[j].name < students[least].name)
                least = j;
        swap(students[least], students[i]);
    }
}





void Insertion_sortByGpa(vector<Student> &students)
{
    for (int i = 1, j; i < students.size(); i++)
    {
        Student tmp = students[i];

        for (j = i; j > 0 && tmp.gpa < students[j - 1].gpa; j--)
            students[j] = students[j - 1];
        students[j] = tmp;
    }
}
void Insertion_sortByName(vector<Student> &students)
{
    for (int i = 1, j; i < students.size(); i++)
    {
        Student tmp = students[i];

        for (j = i; j > 0 && tmp.name < students[j - 1].name; j--)
            students[j] = students[j - 1];
        students[j] = tmp;
    }
}

int main()
{
    // example to check code
    Student adel("20220173", "Adel", 3.32);
    Student zeyad("20220146", "zeyad", 3.45);
    vector<Student> students = {zeyad, adel};
    Selection_sortByName(students);
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