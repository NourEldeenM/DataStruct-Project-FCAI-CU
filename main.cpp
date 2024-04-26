#include "student.h"
#include "compare.h"

vector<Student> readInputFromFile();

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
