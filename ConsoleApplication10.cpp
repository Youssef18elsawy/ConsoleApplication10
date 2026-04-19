#include <iostream>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

struct Student {
    string id;
    string name;
    string nationalID;
    char gender;
    string dob;
    string phone;
    string program;
    int level;
    float gpa;
};

const int MAX = 100;
Student students[MAX];
int countStudents = 0;

// 🔹 Validation
bool isValidID(string id) {
    return id.length() == 8;
}

bool isValidPhone(string phone) {
    return phone.length() == 11 && phone.substr(0, 2) == "01";
}

// 🔹 Add
void addStudent() {
    if (countStudents >= MAX) {
        cout << "Array Full!\n";
        return;
    }

    Student s;

    cout << "Enter ID: ";
    cin >> s.id;

    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, s.name);

    cout << "Enter National ID: ";
    cin >> s.nationalID;

    cout << "Enter Gender: ";
    cin >> s.gender;

    cout << "Enter DOB: ";
    cin >> s.dob;

    cout << "Enter Phone: ";
    cin >> s.phone;

    cout << "Enter Program: ";
    cin >> s.program;

    cout << "Enter Level: ";
    cin >> s.level;

    s.gpa = 0;

    students[countStudents++] = s;

    cout << "Added!\n";
}

// 🔹 Display
void displayStudents() {
    for (int i = 0; i < countStudents; i++) {
        cout << "\nID: " << students[i].id
            << "\nName: " << students[i].name
            << "\nGPA: " << students[i].gpa << "\n";
    }
}

// 🔹 Search
int findStudentIndex(string id) {
    for (int i = 0; i < countStudents; i++) {
        if (students[i].id == id)
            return i;
    }
    return -1;
}

void searchStudent() {
    string id;
    cout << "Enter ID: ";
    cin >> id;

    int index = findStudentIndex(id);

    if (index != -1)
        cout << "Found: " << students[index].name << endl;
    else
        cout << "Not Found\n";
}

// 🔹 Delete
void deleteStudent() {
    string id;
    cout << "Enter ID: ";
    cin >> id;

    int index = findStudentIndex(id);

    if (index == -1) {
        cout << "Not Found\n";
        return;
    }

    for (int i = index; i < countStudents - 1; i++) {
        students[i] = students[i + 1];
    }

    countStudents--;
    cout << "Deleted!\n";
}

// 🔹 Update
void updateStudent() {
    string id;
    cout << "Enter ID: ";
    cin >> id;

    int index = findStudentIndex(id);

    if (index == -1) {
        cout << "Not Found\n";
        return;
    }

    cout << "Enter new name: ";
    cin.ignore();
    getline(cin, students[index].name);

    cout << "Enter new phone: ";
    cin >> students[index].phone;

    cout << "Updated!\n";
}

// 🔹 Menu
void studentMenu() {
    int choice;

    do {
        cout << "\n--- Student Menu ---\n";
        cout << "1. Add\n2. Display\n3. Search\n4. Update\n5. Delete\n0. Exit\n";
        cin >> choice;

        switch (choice) {
        case 1: addStudent(); break;
        case 2: displayStudents(); break;
        case 3: searchStudent(); break;
        case 4: updateStudent(); break;
        case 5: deleteStudent(); break;
        }

    } while (choice != 0);
}

int main() {
    studentMenu();
    return 0;
}
