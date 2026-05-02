#include <iostream>
#include <cmath>
#include <iomanip>
#include <algorithm>
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
struct Course {
    string code;        
    string title;
    int creditHours;    
};
struct Grade {
    string studentID;
    string code;         
    int midterm;
    int final;
    int total;
    string letterGrade;
};

const int MAX = 100;
Student students[MAX];
int countStudents = 0;

const int MAX_COURSES = 50;
Course courses[MAX_COURSES];
int courseCount = 0;

const int MAX_GRADES = 500;
Grade grades[MAX_GRADES];
int gradeCount = 0;

// Validation
bool isValidID(string id) {
    return id.length() == 8;
}

bool isValidPhone(string phone) {
    return phone.length() == 11 && phone.substr(0, 2) == "01";
}
//grade calculation
string calculateLetterGrade(int total) {
    if (total >= 93) return "A";
    else if (total >= 89 && total<=92) return "A-";
    else if (total >= 84 && total<=88) return "B+";
    else if (total >= 80 && total<=83) return "B";
    else if (total >= 76 && total<=79) return "B-";
    else if (total >= 73 && total<=75) return "C+";
    else if (total >= 70 && total<=72) return "C";
    else if (total >= 67 && total<=69) return "C-";
    else if (total >= 64 && total<=66) return "D+";
    else if (total >= 60 && total<=63) return "D";
    else return "F";
}

float letterToPoints(string letter) {
    if (letter == "A") return 4.0;
    else if (letter == "A-") return 3.7;
    else if (letter == "B+") return 3.3;
    else if (letter == "B") return 3.0;
    else if (letter == "B-") return 2.7;
    else if (letter == "C+") return 2.3;
    else if (letter == "C") return 2.0;
    else if (letter == "C-") return 1.7;
    else if (letter == "D+") return 1.3;
    else if (letter == "D") return 1.0;
    else return 0.0;
}
// 🔹 Temporary Course Data (REMOVE when teammate finishes Course Management)
void loadTempCourses() {
    courseCount = 3;
    
    courses[0].code = "CSE141";
    courses[0].title = "Intro to Programming";
    courses[0].creditHours = 3;
    
    courses[1].code = "MTH101";
    courses[1].title = "Calculus I";
    courses[1].creditHours = 4;
    
    courses[2].code = "PHY101";
    courses[2].title = "Physics I";
    courses[2].creditHours = 3;
}

// Add
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

// Display
void displayStudents() {
    for (int i = 0; i < countStudents; i++) {
        cout << "\nID: " << students[i].id
            << "\nName: " << students[i].name
            << "\nGPA: " << students[i].gpa << "\n";
    }
}

// Search
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

// Delete
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

//  Update
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
void enterGrade() {
    string studentID, code;
    int midterm, final;
    cout << "Enter Student ID." << endl;
    cin >> studentID;
    if (findStudentIndex(studentID) == -1) {
        cout << "Error:The student is not found." << endl;
        return;
    }
    cout << "Enter Course Code: ";
    cin >> code;

    int courseIndex = -1;
    for (int i = 0; i < courseCount; i++) {
        if (courses[i].code == code) {
            courseIndex = i;
            break;
        }
    }
    if (courseIndex == -1) {
        cout << "Error: Course not found." << endl;
        return;
    }
    for (int i = 0; i < gradeCount; i++) {
        if (grades[i].studentID == studentID && grades[i].code == code) {
            cout << "Error: Grade already entered for this course." << endl;;
            return;
        }
    }
    cout << "Enter Midterm Grade : ";
    cin >> midterm;
    if (midterm < 0 || midterm > 40) {
        cout << "Error: Midterm grade must be 0-40." << endl;;
        return;
    }
    cout << "Enter Final Grade : ";
    cin >> final;
    if (final < 0 || final > 60) {
        cout << "Error: Final grade must be 0-60." << endl;
        return;
    }
    int total = midterm + final;
    
    string letter = calculateLetterGrade(total);
    grades[gradeCount].studentID = studentID;
    grades[gradeCount].code = code;
    grades[gradeCount].midterm = midterm;
    grades[gradeCount].final = final;
    grades[gradeCount].total = total;
    grades[gradeCount].letterGrade = letter;
    gradeCount++;
    cout << "Total: " << total << "/100" << endl;;
    cout << "Letter Grade: " << letter << endl;
    cout << "Grade recorded successfully."<<endl;
}
void viewStudentGrades() {
    string studentID;
    cout << "Enter Student ID: ";
    cin >> studentID;

    
    if (findStudentIndex(studentID) == -1) {
        cout << "Student not found!"<<endl;
        return;
    }
    bool found = false;
    cout << endl << "--- Grades for " << studentID << " ---" << endl;
    for (int i = 0; i < gradeCount; i++) {
        if (grades[i].studentID == studentID) {
            string title = "Unknown";
            for (int j = 0; j < courseCount; j++) {
                if (courses[j].code == grades[i].code) {
                    title = courses[j].title;
                    break;
                }
            }
            cout << grades[i].code << " | " << title
                << " | Mid: " << grades[i].midterm
                << " | Final: " << grades[i].final
                << " | Total: " << grades[i].total
                << " | Grade: " << grades[i].letterGrade << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "No grades found for this student." << endl;
    }
}
void calculateGPA() {
    string studentID;
    cout << "Enter Student ID: ";
    cin >> studentID;

    int studentIndex = findStudentIndex(studentID);
    if (studentIndex == -1) {
        cout << "Student not found!" << endl;
        return;
    }

    float totalPoints = 0;
    int totalCredits = 0;
    for (int i = 0; i < gradeCount; i++) {
        if (grades[i].studentID == studentID) {
            
            for (int j = 0; j < courseCount; j++) {
                if (courses[j].code == grades[i].code) {
                    float points = letterToPoints(grades[i].letterGrade);
                    totalPoints += points * courses[j].creditHours;
                    totalCredits += courses[j].creditHours;
                    break;
                }
            }
        }
    }
    if (totalCredits == 0) {
        cout << "No grades recorded. GPA = 0.0" << endl;
        students[studentIndex].gpa = 0.0;
    }
    else {
        float gpa = totalPoints / totalCredits;
        students[studentIndex].gpa = gpa;
        cout << fixed << setprecision(2);
        cout << "GPA for " << students[studentIndex].name << ": " << gpa << endl;
    }
}
void generateTranscript() {
    string studentID;
    cout << "Enter Student ID: " << endl;
    cin >> studentID;

    int studentIndex = findStudentIndex(studentID);
    if (studentIndex == -1) {
        cout << "Student not found." << endl;
        return;
    }

    cout << endl << "========================================" << endl;
    cout << "           STUDENT TRANSCRIPT" << endl;
    cout << "========================================" << endl;
    cout << "Name: " << students[studentIndex].name << endl;
    cout << "ID: " << students[studentIndex].id << endl;
    cout << "Program: " << students[studentIndex].program << endl;
    cout << "Level: " << students[studentIndex].level << endl;
    cout << endl << "----------------------------------------" << endl;

    cout << left << setw(10) << "Course"
        << setw(25) << "Title"
        << setw(8) << "Credits"
        << setw(8) << "Grade"
        << setw(8) << "Points" << endl;
    cout << "----------------------------------------" << endl;

    float totalPoints = 0;
    int totalCredits = 0;

    for (int i = 0; i < gradeCount; i++) {
        if (grades[i].studentID == studentID) {
            for (int j = 0; j < courseCount; j++) {
                if (courses[j].code == grades[i].code) {
                    float points = letterToPoints(grades[i].letterGrade);
                    cout << left << setw(10) << courses[j].code
                        << setw(25) << courses[j].title
                        << setw(8) << courses[j].creditHours
                        << setw(8) << grades[i].letterGrade
                        << setw(8) << points << endl;
                    totalPoints += points * courses[j].creditHours;
                    totalCredits += courses[j].creditHours;
                    break;
                }
            }
        }
    }

    cout << "----------------------------------------" << endl;
    cout << "Total Credit Hours: " << totalCredits << endl;

    float gpa = (totalCredits > 0) ? totalPoints / totalCredits : 0.0;
    cout << fixed << setprecision(2);
    cout << "Cumulative GPA: " << gpa << endl;
    cout << "========================================" << endl;

    students[studentIndex].gpa = gpa;
}
//  Menu
void studentMenu() {
    int choice;

    do {
        cout << endl<<"--- Student Menu---"<<endl;
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
void gradesMenu() {
    int choice;

    do {
        cout << endl<< "=== Grades Management === " << endl;
        cout << "1. Enter Student Grades" << endl;
        cout << "2. View Student Grades" << endl;
        cout << "3. Calculate GPA" << endl;
        cout << "4. Generate Transcript" << endl;
        cout << "5. Back to Main Menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
        case 1: enterGrade(); break;
        case 2: viewStudentGrades(); break;
        case 3: calculateGPA(); break;
        case 4: generateTranscript(); break;
        case 5: cout << "Returning to main menu..." << endl; break;
        default: cout << "Invalid choice!" << endl;
        }
    } while (choice != 5);
}

int main() {
    loadTempCourses();  // TEMPORARY 

    int mainChoice;
    do {
        cout << endl<< "=== MAIN MENU === " << endl;
        cout << "1. Student Management" << endl;
        cout << "2. Course Management" << endl;
        cout << "3. Grades Management" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter choice: ";
        cin >> mainChoice;

        switch (mainChoice) {
        case 1: studentMenu(); break;
        case 2: cout << "Course Management" << endl; break;
        case 3: gradesMenu(); break;
        case 0: cout << "Goodbye!" << endl; break;
        default: cout << "Invalid choice!" << endl;
        }
    } while (mainChoice != 0);

    return 0;
}