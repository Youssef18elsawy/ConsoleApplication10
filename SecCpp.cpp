#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

const int MAX = 100;

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

Student students[MAX];
int studentCount = 0;

int findByID(char *targetID) {
    for (int i = 0; i < studentCount; i++) {
        if (strcmp((students + i)->id, targetID) == 0)
            return i;
    }
    return -1;
}

int findByName(char *targetName) {
    for (int i = 0; i < studentCount; i++) {
        if (strcmp((students + i)->name, targetName) == 0)
            return i;
    }
    return -1;
}

int findByNationalID(char *targetNID) {
    for (int i = 0; i < studentCount; i++) {
        if (strcmp((students + i)->nationalID, targetNID) == 0)
            return i;
    }
    return -1;
}

void printOneStudent(Student *s) {
    int gpaInt = (int)s->gpa;
    int gpaDec = (int)((s->gpa - gpaInt) * 100 + 0.5);
    cout << "\n  ID         : " << s->id;
    cout << "\n  Name       : " << s->name;
    cout << "\n  National ID: " << s->nationalID;
    cout << "\n  Gender     : " << s->gender;
    cout << "\n  DOB        : " << s->dob;
    cout << "\n  Phone      : " << s->phone;
    cout << "\n  Program    : " << s->program;
    cout << "\n  Level      : " << s->level;
    cout << "\n  GPA        : " << gpaInt << ".";
    if (gpaDec < 10) cout << "0";
    cout << gpaDec << "\n";
}

void addStudent() {
    if (studentCount >= MAX) {
        cout << "\n  System is full.\n";
        return;
    }

    Student *s = students + studentCount;

    cout << "\n--- Add Student ---\n";
    cout << "Enter ID (YYPXXXX): ";
    cin >> s->id;

    if (findByID(s->id) != -1 && findByID(s->id) != studentCount) {
        cout << "  ID already exists.\n";
        return;
    }

    cout << "Enter Name (two words): ";
    cin.ignore();
    cin.getline(s->name, 50);

    cout << "Enter National ID (14 digits): ";
    cin >> s->nationalID;

    if (findByNationalID(s->nationalID) != -1) {
        cout << "  National ID already exists.\n";
        return;
    }

    cout << "Enter Gender (M/F): ";
    cin >> s->gender;

    cout << "Enter DOB (DD/MM/YYYY): ";
    cin >> s->dob;

    cout << "Enter Phone (01xxxxxxxxx): ";
    cin >> s->phone;

    cout << "Enter Program (CSE/CCE/MCT): ";
    cin >> s->program;

    cout << "Enter Level (1-4): ";
    cin >> s->level;

    s->gpa = 0.0;

    studentCount++;
    cout << "\n  Student added successfully.\n";
}

void searchStudent() {
    if (studentCount == 0) {
        cout << "\n  No students found.\n";
        return;
    }

    cout << "\n--- Search Student ---\n";
    cout << "1. By ID\n";
    cout << "2. By Name\n";
    cout << "3. By National ID\n";
    cout << "Enter choice: ";

    int choice;
    cin >> choice;
    int index = -1;

    if (choice == 1) {
        char targetID[10];
        cout << "Enter ID: ";
        cin >> targetID;
        index = findByID(targetID);
    }
    else if (choice == 2) {
        char targetName[50];
        cout << "Enter Name: ";
        cin.ignore();
        cin.getline(targetName, 50);
        index = findByName(targetName);
    }
    else if (choice == 3) {
        char targetNID[15];
        cout << "Enter National ID: ";
        cin >> targetNID;
        index = findByNationalID(targetNID);
    }
    else {
        cout << "  Invalid choice.\n";
        return;
    }

    if (index == -1)
        cout << "\n  Student not found.\n";
    else
        printOneStudent(students + index);
}

void updateStudent() {
    if (studentCount == 0) {
        cout << "\n  No students found.\n";
        return;
    }

    char targetID[10];
    cout << "\n--- Update Student ---\n";
    cout << "Enter Student ID to update: ";
    cin >> targetID;

    int index = findByID(targetID);
    if (index == -1) {
        cout << "  Student not found.\n";
        return;
    }

    Student *s = students + index;
    cout << "\n  Student found: " << s->name << "\n";
    cout << "1. Name\n";
    cout << "2. Phone\n";
    cout << "3. Level\n";
    cout << "4. Program\n";
    cout << "Enter choice: ";

    int choice;
    cin >> choice;

    if (choice == 1) {
        cout << "Enter new Name (two words): ";
        cin.ignore();
        cin.getline(s->name, 50);
    }
    else if (choice == 2) {
        cout << "Enter new Phone (01xxxxxxxxx): ";
        cin >> s->phone;
    }
    else if (choice == 3) {
        cout << "Enter new Level (1-4): ";
        cin >> s->level;
    }
    else if (choice == 4) {
        cout << "Enter new Program (CSE/CCE/MCT): ";
        cin >> s->program;
    }
    else {
        cout << "  Invalid choice.\n";
        return;
    }

    cout << "\n  Student updated successfully.\n";
}

void deleteStudent() {
    if (studentCount == 0) {
        cout << "\n  No students found.\n";
        return;
    }

    char targetID[10];
    cout << "\n--- Delete Student ---\n";
    cout << "Enter Student ID to delete: ";
    cin >> targetID;

    int index = findByID(targetID);
    if (index == -1) {
        cout << "  Student not found.\n";
        return;
    }

    cout << "\n  Student: " << (students + index)->name;
    cout << "\n  Confirm delete? (1=Yes / 0=No): ";
    int confirm;
    cin >> confirm;

    if (confirm != 1) {
        cout << "  Delete cancelled.\n";
        return;
    }

    for (int i = index; i < studentCount - 1; i++)
        *(students + i) = *(students + i + 1);

    studentCount--;
    cout << "  Student deleted successfully.\n";
}

void mainMenu() {
    int choice;
    do {
        cout << "\n=============================\n";
        cout << "  Student Information System  \n";
        cout << "=============================\n";
        cout << "1. Add Student\n";
        cout << "2. Search Student\n";
        cout << "3. Update Student\n";
        cout << "4. Delete Student\n";
        cout << "5. Display All Students\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if      (choice == 1) addStudent();
        else if (choice == 2) searchStudent();
        else if (choice == 3) updateStudent();
        else if (choice == 4) deleteStudent();
        else if (choice == 5) cout << "\n  [Student 4 function goes here]\n";
        else if (choice != 0) cout << "\n  Invalid choice.\n";

    } while (choice != 0);

    cout << "\n  Goodbye!\n";
}

int main() {
    mainMenu();
    return 0;
}