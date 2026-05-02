#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

struct Student {
    char id[10];
    char name[50];
    char nationalID[15];
    char gender;
    char dob[11];
    char phone[12];
    char program[5];
    int  level;
    double gpa;
};

void printLine() {
    cout << "+---------+---------------------+----------------+----+-----------+----+---------+------+" << endl;
}

void printHeader() {
    printLine();
    cout << "| " << setw(8)  << "ID"
         << " | " << setw(20) << "Name"
         << " | " << setw(14) << "National ID"
         << " | " << setw(3)  << "Gen"
         << " | " << setw(10) << "DOB"
         << " | " << setw(3)  << "Lvl"
         << " | " << setw(7)  << "Program"
         << " | " << setw(4)  << "GPA"
         << " |" << endl;
    printLine();
}

void printStudentRow(Student s) {
    cout << "| " << setw(8)  << s.id
         << " | " << setw(20) << s.name
         << " | " << setw(14) << s.nationalID
         << " | " << setw(3)  << s.gender
         << " | " << setw(10) << s.dob
         << " | " << setw(3)  << s.level
         << " | " << setw(7)  << s.program
         << " | ";
    int gpaInt = (int)s.gpa;
    int gpaDec = (int)((s.gpa - gpaInt) * 100 + 0.5);
    cout << setw(1) << gpaInt << ".";
    if (gpaDec < 10) cout << "0";
    cout << gpaDec << " |" << endl;
}

void bubbleSort(Student arr[], int count, int sortBy) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - 1 - i; j++) {
            bool shouldSwap = false;
            if (sortBy == 1 && strcmp(arr[j].id, arr[j+1].id) > 0)
                shouldSwap = true;
            else if (sortBy == 2 && strcmp(arr[j].name, arr[j+1].name) > 0)
                shouldSwap = true;
            else if (sortBy == 3 && arr[j].gpa < arr[j+1].gpa)
                shouldSwap = true;
            if (shouldSwap) {
                Student temp = arr[j];
                arr[j]       = arr[j+1];
                arr[j+1]     = temp;
            }
        }
    }
}

void displayAllStudents(Student students[], int count) {
    if (count == 0) {
        cout << "\n  No students found.\n";
        return;
    }
    cout << "\n--- Sort Options ---\n";
    cout << "1. Sort by ID\n";
    cout << "2. Sort by Name\n";
    cout << "3. Sort by GPA (highest first)\n";
    cout << "Enter choice: ";
    int choice;
    cin >> choice;
    if (choice < 1 || choice > 3) {
        cout << "Invalid choice. Showing unsorted list.\n";
        choice = 0;
    }
    Student temp[100];
    for (int i = 0; i < count; i++)
        temp[i] = students[i];
    if (choice >= 1 && choice <= 3)
        bubbleSort(temp, count, choice);
    cout << "\n========== Student List ==========\n";
    printHeader();
    for (int i = 0; i < count; i++)
        printStudentRow(temp[i]);
    printLine();
    cout << "  Total students: " << count << "\n";
    cout << "==================================\n";
}