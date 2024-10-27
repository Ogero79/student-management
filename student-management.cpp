#include <iostream>
#include <string>
#include <limits>

using namespace std;

const int MAX_STUDENTS = 100; // Max number of students

// Structure to represent student information
struct Student {
    string name;
    int age;
    float marks[3];   // Array to store marks for 3 subjects
    float averageMarks;
};

// Function prototypes
void addStudent(Student students[], int &count);
void displayStudents(const Student students[], int count);
void calculateAverageMarks(Student &student);
void sortStudentsByAverage(Student students[], int count);
Student findHighestAverage(const Student students[], int count);
Student findLowestAverage(const Student students[], int count);
float calculateClassAverage(const Student students[], int count);
void clearInput(); // Utility function to clear invalid input

int main() {
    Student students[MAX_STUDENTS];
    int count = 0;  // Number of students
    int choice;

    do {
        cout << "\n--- Student Management System ---\n";
        cout << "1. Add New Student Record\n";
        cout << "2. Display All Student Records\n";
        cout << "3. Sort Students by Average Marks\n";
        cout << "4. Find Student with Highest Average Marks\n";
        cout << "5. Find Student with Lowest Average Marks\n";
        cout << "6. Calculate Class Average\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent(students, count);
                break;
            case 2:
                displayStudents(students, count);
                break;
            case 3:
                sortStudentsByAverage(students, count);
                displayStudents(students, count);
                break;
            case 4:
                {
                    Student highest = findHighestAverage(students, count);
                    cout << "Student with Highest Average Marks: " << highest.name << " - " << highest.averageMarks << endl;
                }
                break;
            case 5:
                {
                    Student lowest = findLowestAverage(students, count);
                    cout << "Student with Lowest Average Marks: " << lowest.name << " - " << lowest.averageMarks << endl;
                }
                break;
            case 6:
                cout << "Class Average Marks: " << calculateClassAverage(students, count) << endl;
                break;
            case 7:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 7);

    return 0;
}

// Function to add a new student
void addStudent(Student students[], int &count) {
    if (count >= MAX_STUDENTS) {
        cout << "Cannot add more students.\n";
        return;
    }

    Student newStudent;
    cout << "Enter name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
    getline(cin, newStudent.name);

    cout << "Enter age: ";
    while (!(cin >> newStudent.age) || newStudent.age < 0) {
        cout << "Invalid input! Enter a positive age: ";
        clearInput();
    }

    cout << "Enter marks for 3 subjects:\n";
    for (int i = 0; i < 3; i++) {
        cout << "Subject " << i + 1 << ": ";
        while (!(cin >> newStudent.marks[i]) || newStudent.marks[i] < 0 || newStudent.marks[i] > 100) {
            cout << "Invalid input! Enter a mark between 0 and 100: ";
            clearInput();
        }
    }

    calculateAverageMarks(newStudent);
    students[count] = newStudent;
    count++;
}

// Function to display all student records
void displayStudents(const Student students[], int count) {
    cout << "\n--- Student Records ---\n";
    for (int i = 0; i < count; i++) {
        cout << "Name: " << students[i].name << ", Age: " << students[i].age
             << ", Average Marks: " << students[i].averageMarks << endl;
    }
}

// Function to calculate average marks for a student
void calculateAverageMarks(Student &student) {
    float sum = 0;
    for (int i = 0; i < 3; i++) {
        sum += student.marks[i];
    }
    student.averageMarks = sum / 3;
}

// Function to sort students by average marks (selection sort)
void sortStudentsByAverage(Student students[], int count) {
    for (int i = 0; i < count - 1; i++) {
        int maxIdx = i;
        for (int j = i + 1; j < count; j++) {
            if (students[j].averageMarks > students[maxIdx].averageMarks) {
                maxIdx = j;
            }
        }
        if (maxIdx != i) {
            swap(students[i], students[maxIdx]);
        }
    }
    cout << "Students sorted by average marks.\n";
}

// Function to find the student with the highest average marks
Student findHighestAverage(const Student students[], int count) {
    Student highest = students[0];
    for (int i = 1; i < count; i++) {
        if (students[i].averageMarks > highest.averageMarks) {
            highest = students[i];
        }
    }
    return highest;
}

// Function to find the student with the lowest average marks
Student findLowestAverage(const Student students[], int count) {
    Student lowest = students[0];
    for (int i = 1; i < count; i++) {
        if (students[i].averageMarks < lowest.averageMarks) {
            lowest = students[i];
        }
    }
    return lowest;
}

// Function to calculate the class average
float calculateClassAverage(const Student students[], int count) {
    float totalAverage = 0;
    for (int i = 0; i < count; i++) {
        totalAverage += students[i].averageMarks;
    }
    return (count > 0) ? (totalAverage / count) : 0;
}

// Function to clear invalid input
void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
