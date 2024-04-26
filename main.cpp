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
    cout << "\n";

    insertionSort(students, CompareByGPA(), "SortedByGPA.txt");
    insertionSort(students, CompareByName(), "SortedByName.txt");

    selectionSort(students, CompareByGPA(), "SortedByGPA.txt");
    selectionSort(students, CompareByName(), "SortedByName.txt");

    bubbleSort(students, CompareByGPA(), "SortedByGPA.txt");
    bubbleSort(students, CompareByName(), "SortedByName.txt");

    quickSort(students, CompareByGPA(), "SortedByGPA.txt");
    quickSort(students, CompareByName(), "SortedByName.txt");

    mergeSort(students, CompareByGPA(), "SortedByGPA.txt");
    mergeSort(students, CompareByName(), "SortedByName.txt");

    shellSort(students, CompareByGPA(), "SortedByGPA.txt");
    shellSort(students, CompareByName(), "SortedByName.txt");

    countSort(students, CompareByGPA(), "SortedByGPA.txt");

    return 0;
}
