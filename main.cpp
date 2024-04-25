#include "student.h"
#include "compare.h"

vector<Student> readInputFromFile()
{
    vector<Student> students;
    ifstream fin("students.txt");
    if (fin.fail())
    {
        cout << "Error opening file\n";
        return students;
    }
    int num_Students;
    fin >> num_Students;
    fin.ignore(numeric_limits<streamsize>::max(), '\n');
    for (int i = 0; i < num_Students; ++i)
    {
        Student student;
        getline(fin, student.name);
        fin >> student.id;
        fin >> student.gpa;
        fin.ignore(numeric_limits<streamsize>::max(), '\n');
        students.push_back(student);
    }
    fin.close();
    return students;
}

int main()
{
    vector<Student> students = readInputFromFile();
    for (int i = 0; i < students.size(); ++i)
        cout << students[i].name << " " << students[i].id << " " << students[i].gpa << "\n";

    // example to check code
    cout << "\n";
    Selection_sort(students, CompareByGPA());
    cout << "Algorithm: Selection Sort\n";
    cout << "*By GPA*\n";
    for (auto x : students)
        cout << x.name << '\n'
             << x.id << '\n'
             << x.gpa << "\n\n";
    Selection_sort(students, CompareByName());
    cout << "Algorithm: Selection Sort\n";
    cout << "*By Name*\n";
    for (auto x : students)
        cout << x.name << '\n'
             << x.id << '\n'
             << x.gpa << "\n\n";
    Insertion_sort(students, CompareByGPA());
    cout << "Algorithm: Insertion Sort\n";
    cout << "*By GPA*\n";
    for (auto x : students)
        cout << x.name << '\n'
             << x.id << '\n'
             << x.gpa << "\n\n";
    Insertion_sort(students, CompareByName());
    cout << "Algorithm: Insertion Sort\n";
    cout << "*By Name*\n";
    for (auto x : students)
        cout << x.name << '\n'
             << x.id << '\n'
             << x.gpa << "\n\n";

    bubbleSort(students, CompareByGPA(), "SortedByGPA.txt");
    bubbleSort(students, CompareByName(), "SortedByName.txt");

    quickSort(students, CompareByGPA(), "SortedByGPA.txt");
    quickSort(students, CompareByName(), "SortedByName.txt");

    mergeSort(students, CompareByGPA(), "SortedByGPA.txt");
    mergeSort(students, CompareByName(), "SortedByName.txt");

    return 0;
}