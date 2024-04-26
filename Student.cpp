#include "student.h"
#include "compare.h"

using namespace chrono;

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

// Insertion Sort
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

// Selection Sort
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

// Bubble Sort
template <typename Compare>
void bubbleSort(vector<Student> &students, Compare comp, const string &filename)
{
    ofstream outputFile(filename, ios::app);
    if (!outputFile.is_open())
    {
        cerr << "Error: Unable to open file for writing: "
             << "\n";
        return;
    }

    outputFile << "Algorithm name: Bubble Sort\n";
    auto start = high_resolution_clock::now();
    int n = students.size();
    int i, j;
    bool swapped;
    int number_of_comparisons = 0;
    for (i = 0; i < n - 1; i++)
    {
        swapped = false;
        for (j = 0; j < n - i - 1; j++)
        {
            number_of_comparisons++;
            // This is the original condition it should work but it sorts the students in descending order
            // if (comp(students[j], students[j + 1]))

            if (comp(students[j + 1], students[j]))
            {
                swap(students[j], students[j + 1]);
                swapped = true;
            }
        }
        if (!swapped)
            break;
    }
    outputFile << "Number of Comparisons equals: " << number_of_comparisons << "\n";
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    outputFile << "Time taken by algorithm: "
               << duration.count() << " microseconds"
               << "\n";
    for (const auto &student : students)
    {
        outputFile << student.name << '\n'
                   << student.id << '\n'
                   << student.gpa << "\n\n";
    }
}

template <typename Compare>
void quickSortFullParameters(vector<Student> &students, Compare comp, int i, int j, int &number_of_comparisons, const string &filename)
{
    ofstream outputFile(filename, ios::app);
    if (!outputFile.is_open())
    {
        cerr << "Error: Unable to open file for writing: " << filename << endl;
        return;
    }

    if (i >= j)
        return;
    Student pivot = students[(i + j) / 2];
    // partition
    int left = i, right = j;
    while (left <= right)
    {
        while (comp(students[left], pivot))
        {
            left++;
            number_of_comparisons++;
        }
        while (comp(pivot, students[right]))
        {
            right--;
            number_of_comparisons++;
        }
        if (left <= right)
        {
            swap(students[left], students[right]);
            left++;
            right--;
        }
    }
    if (i < right)
        quickSortFullParameters(students, comp, i, right, number_of_comparisons, filename);
    if (left < j)
        quickSortFullParameters(students, comp, left, j, number_of_comparisons, filename);
}

// Wrapper function
template <typename Compare>
void quickSort(vector<Student> &students, Compare comp, const string &filename)
{
    ofstream outputFile(filename, ios::app);
    if (!outputFile.is_open())
    {
        cerr << "Error: Unable to open file for writing: " << filename << endl;
        return;
    }
    outputFile << "Algorithm name: Quick Sort\n";
    auto start = high_resolution_clock::now();
    int number_of_comparisons = 0;
    quickSortFullParameters(students, comp, 0, students.size() - 1, number_of_comparisons, filename);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    outputFile << "Number of Comparisons equals: " << number_of_comparisons << endl;
    outputFile << "Time taken by algorithm: "
               << duration.count() << " microseconds" << endl;
    for (const auto &student : students)
    {
        outputFile << student.name << '\n'
                   << student.id << '\n'
                   << student.gpa << "\n\n";
    }
}

// Merge Sort
template <typename Compare>
void merge(vector<Student> &students, int l, int m, int r, int &number_of_comparisons, Compare comp)
{
    int s1 = m - l + 1;
    int s2 = r - m;

    vector<Student> L(s1);
    vector<Student> R(s2);

    for (int i = 0; i < s1; i++)
        L[i] = students[l + i];
    for (int j = 0; j < s2; j++)
        R[j] = students[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < s1 && j < s2)
    {
        if (comp(L[i], R[j]))
        {
            students[k] = L[i];
            i++;
        }
        else
        {
            students[k] = R[j];
            j++;
        }
        k++;
        number_of_comparisons++;
    }

    while (i < s1)
    {
        students[k] = L[i];
        i++;
        k++;
    }

    while (j < s2)
    {
        students[k] = R[j];
        j++;
        k++;
    }
}

template <typename Compare>
void mergeSort(vector<Student> &students, int l, int r, Compare comp, int &number_of_comparisons, const string &filename)
{

    if (l >= r)
        return;
    int m = l + (r - l) / 2;
    mergeSort(students, l, m, comp, number_of_comparisons, filename);
    mergeSort(students, m + 1, r, comp, number_of_comparisons, filename);
    merge(students, l, m, r, number_of_comparisons, comp);
}

// Wrapper Function
template <typename Compare>
void mergeSort(vector<Student> &students, Compare comp, const string &filename)
{
    ofstream outputFile(filename, ios::app);
    if (!outputFile.is_open())
    {
        cerr << "Error: Unable to open file for writing: " << filename << endl;
        return;
    }
    outputFile << "Algorithm name: Merge Sort\n";
    auto start = high_resolution_clock::now();
    int number_of_comparisons = 0;

    int students_size = students.size();
    mergeSort(students, 0, students_size - 1, comp, number_of_comparisons, filename);

    outputFile << "Number of Comparisons equals: " << number_of_comparisons << "\n";
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    outputFile << "Time taken by algorithm: "
               << duration.count() << " microseconds"
               << "\n";

    for (const auto &student : students)
    {
        outputFile << student.name << '\n'
                   << student.id << '\n'
                   << student.gpa << "\n\n";
    }
}

template <typename Compare>
void shellSortFull(vector<Student> &students, Compare comp, int &number_of_comparisons, const string &filename)
{
    for (int gap = students.size(); gap > 0; gap /= 2)
    {
        for (int i = gap; i < students.size(); i++)
        {
            Compare temp = students[i];

            for (int j = i; j >= gap && comp(students[j - gap], temp); j -= gap)
            {
                number_of_comparisons++;
                students[j] = students[j - gap];
            }
            students[j] = temp;
        }
    }
}

template <typename Compare>
void shellSort(vector<Student> &students, Compare comp, const string &filename)
{
    ofstream outputFile(filename, ios::app);
    if (!outputFile.is_open())
    {
        cerr << "Error: Unable to open file for writing: " << filename << endl;
        return;
    }
    outputFile << "Algorithm name: Shell Sort\n";
    auto start = high_resolution_clock::now();
    int number_of_comparisons = 0;
    shellSortFull(students, comp, number_of_comparisons, filename);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    outputFile << "Number of Comparisons equals: " << number_of_comparisons << endl;
    outputFile << "Time taken by algorithm: "
               << duration.count() << " microseconds" << endl;
    for (const auto &student : students)
    {
        outputFile << student.name << '\n'
                   << student.id << '\n'
                   << student.gpa << "\n\n";
    }
}

template void Insertion_sort(vector<Student> &, CompareByGPA);
template void Insertion_sort(vector<Student> &, CompareByName);

template void Selection_sort(vector<Student> &, CompareByGPA);
template void Selection_sort(vector<Student> &, CompareByName);

template void bubbleSort(vector<Student> &, CompareByGPA, const string &filename);
template void bubbleSort(vector<Student> &, CompareByName, const string &filename);

template void quickSort(vector<Student> &, CompareByGPA, const string &filename);
template void quickSort(vector<Student> &, CompareByName, const string &filename);

template void mergeSort(vector<Student> &, CompareByGPA, const string &filename);
template void mergeSort(vector<Student> &, CompareByName, const string &filename);