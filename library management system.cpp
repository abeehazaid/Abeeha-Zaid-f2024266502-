#include <iostream>
#include <cstring> // For string handling
#include <cstdio>  // For sprintf()

using namespace std;

const int MAX_STUDENTS = 100; // Maximum students allowed
const int MAX_LC = 4; // Learning commons limit
int studentCount = 0, noteCount = 0;

// Student structure
struct Student {
    char name[50];
    int id;
    char section[10];
    char bookBorrowed[50];
    char borrowDate[11];
    char returnDate[11];
};

// Learning Commons structure
struct LearningCommons {
    char timeSlot[20];
    char studentName[50];
    int studentQuantity;
};

// Global Arrays
Student students[MAX_STUDENTS];
LearningCommons lc[MAX_LC];
char managerNotes[100][100];

// Function to calculate return date
void calculateReturnDate(const char borrowDate[], char returnDate[]) {
    int day, month, year;
    
    // Extracting day, month, and year
    sscanf(borrowDate, "%d-%d-%d", &day, &month, &year);
    
    // Add 5 days
    day += 5;
    if (day > 30) { // Adjust for month-end
        day -= 30;
        month++;
        if (month > 12) {
            month = 1;
            year++;
        }
    }

    // Formatting return date
    sprintf(returnDate, "%02d-%02d-%04d", day, month, year);
}

// Function to add student record
void addStudent() {
    if (studentCount >= MAX_STUDENTS) {
        cout << "Student list is full!\n";
        return;
    }
    
    cout << "Enter student name: ";
    cin.ignore();
    cin.getline(students[studentCount].name, 50);
    
    cout << "Enter student ID: ";
    cin >> students[studentCount].id;
    
    cout << "Enter student section: ";
    cin.ignore();
    cin.getline(students[studentCount].section, 10);
    
    cout << "Enter book borrowed: ";
    cin.getline(students[studentCount].bookBorrowed, 50);
    
    cout << "Enter borrow date (DD-MM-YYYY): ";
    cin.getline(students[studentCount].borrowDate, 11);
    
    // Calculate return date
    calculateReturnDate(students[studentCount].borrowDate, students[studentCount].returnDate);
    
    cout << "Book must be returned by: " << students[studentCount].returnDate << "\n";

    studentCount++;
}

// Function to search for a book
void searchBook() {
    char bookName[50];
    cout << "Enter book name to search: ";
    cin.ignore();
    cin.getline(bookName, 50);

    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].bookBorrowed, bookName) == 0) {
            cout << "The book '" << bookName << "' is currently borrowed by " << students[i].name << " and will be returned on " << students[i].returnDate << ".\n";
            return;
        }
    }

    cout << "Book not found in borrowed records. It might be available.\n";
}

// Function to add manager notes
void addNote() {
    if (noteCount >= 100) {
        cout << "Note list is full!\n";
        return;
    }

    cout << "Enter note: ";
    cin.ignore();
    cin.getline(managerNotes[noteCount], 100);
    
    cout << "Note added successfully!\n";
    noteCount++;
}

// Function to display all notes
void viewNotes() {
    if (noteCount == 0) {
        cout << "No notes available.\n";
        return;
    }

    cout << "Manager Notes:\n";
    for (int i = 0; i < noteCount; i++) {
        cout << i + 1 << ". " << managerNotes[i] << "\n";
    }
}

// Function to book Learning Commons (LC)
void bookLC() {
    int lcNumber;
    
    cout << "Enter Learning Commons number (1-4): ";
    cin >> lcNumber;
    
    if (lcNumber < 1 || lcNumber > MAX_LC) {
        cout << "Invalid LC number!\n";
        return;
    }

    lcNumber--; // Convert to array index

    cout << "Enter time slot (e.g., 1-2 PM): ";
    cin.ignore();
    cin.getline(lc[lcNumber].timeSlot, 20);

    cout << "Enter student name: ";
    cin.getline(lc[lcNumber].studentName, 50);

    cout << "Enter number of students: ";
    cin >> lc[lcNumber].studentQuantity;

    cout << "LC " << (lcNumber + 1) << " booked successfully for " << lc[lcNumber].studentName << " from " << lc[lcNumber].timeSlot << " for " << lc[lcNumber].studentQuantity << " students.\n";
}

// Function to view LC bookings
void viewLCBookings() {
    cout << "Learning Commons Bookings:\n";
    for (int i = 0; i < MAX_LC; i++) {
        if (strlen(lc[i].timeSlot) == 0) {
            cout << "LC " << (i + 1) << ": Available\n";
        } else {
            cout << "LC " << (i + 1) << ": Booked by " << lc[i].studentName << " for " << lc[i].studentQuantity << " students from " << lc[i].timeSlot << ".\n";
        }
    }
}

// Main function
int main() {
    int choice;
    
    while (true) {
        cout << "\nLibrary Management System\n";
        cout << "1. Add Student Record\n";
        cout << "2. Search Book\n";
        cout << "3. Add Manager Note\n";
        cout << "4. View Notes\n";
        cout << "5. Book Learning Commons\n";
        cout << "6. View LC Bookings\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1: addStudent(); break;
            case 2: searchBook(); break;
            case 3: addNote(); break;
            case 4: viewNotes(); break;
            case 5: bookLC(); break;
            case 6: viewLCBookings(); break;
            case 7: cout << "Exiting...\n"; return 0;
            default: cout << "Invalid choice! Try again.\n";
        }
    }
}
