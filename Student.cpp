#include "Student.h"

Student::Student(string id, string name, double gpa) {
    this->id = id;
    this->name = name;
    this->gpa = gpa;
}

Student::Student() {
    this->id = "";
    this->name = "";
    this->gpa = 0;
}


template<typename T, typename Compare>
void Insertion_sort(vector<Student> &items, Compare comp) {
    for (int i = 1, j; i < items.size(); i++) {
        T tmp = items[i];

        for (j = i; j > 0 && comp(tmp, items[j - 1]); j--)
            items[j] = items[j - 1];
        items[j] = tmp;
    }
}

template<typename student, typename Compare>
void Selection_sort(vector<student> &items, Compare comp) {
    for (int i = 0; i < items.size() - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < items.size(); j++) {
            if (comp(items[j], items[minIndex])) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            swap(items[i], items[minIndex]);
        }
    }
}

template<typename student, typename Compare>

void bubbleSort(vector<Student> &students, Compare comp) {
    int n = students.size();
    int i, j;
    bool swapped;
    for (i = 0; i < n - 1; i++) {
        swapped = false;
        for (j = 0; j < n - i - 1; j++) {
            if (comp(students[j], students[j + 1])) {
                swap(students[j], students[j + 1]);
                swapped = true;
            }
        }
        if (!swapped)
            break;
    }
}
