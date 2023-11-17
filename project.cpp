#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool compareIgnoreCase(const string& str1, const string& str2) {
    string lowerStr1 = str1;
    string lowerStr2 = str2;

    // Convert both strings to lowercase
    transform(lowerStr1.begin(), lowerStr1.end(), lowerStr1.begin(), ::tolower);
    transform(lowerStr2.begin(), lowerStr2.end(), lowerStr2.begin(), ::tolower);

    return (lowerStr1 == lowerStr2);
}


class Authentication
{
    string userName;
    string userPassword;
    int loginAttempt;

public:
    Authentication() : loginAttempt(0) {} 
    bool login_status()
    {
          while (loginAttempt < 5)
    {
        cout << "Please enter your user name: ";
        getline(cin, userName);

        // Check if input is empty
        if (userName.empty()) {
            cout << "Error: User name cannot be empty. Please try again." << endl;
            continue;
        }

        cout << "Please enter your user password: ";
        getline(cin, userPassword);

        // Check if input is empty
        if (userPassword.empty()) {
            cout << "Error: Password cannot be empty. Please try again." << endl;
            continue;
        }

        // Compare case-insensitively
        if (compareIgnoreCase(userName, "gourav") && compareIgnoreCase(userPassword, "12345"))
        {
            cout << "Welcome Gourav!\n";
            cout << "You are now logged in!\n\n";
            return true;
        }
        else if (compareIgnoreCase(userName, "sanya") && compareIgnoreCase(userPassword, "12345"))
        {
            cout << "Welcome Sanya!\n";
            cout << "You are now logged in!\n\n";
            return true;
        }
        else
        {
            cout << "Invalid login attempt. Please try again.\n\n"
                 << '\n';
            loginAttempt++;
        }
    }
    cout << "Too many login attempts! The program will now terminate.";
    return false;
}
};

struct Student {
    int rollno; // Primary key, no duplicates allowed
    string firstName;
    string lastName;
    string course;
    string hostelName;
    int year; // Year of study
    string fatherName; // Father's name
    string motherName; // Mother's name
    string fatherMobile; // Father's mobile number
    string studentMobile; // Student's mobile number
    bool feePaid; // Indicates if fee is paid (true/false)
    Student* next;
};

class StudentDatabase {
private:
    Student* head;

public:
    StudentDatabase() : head(nullptr) {}

    // Function to add a student to the database
  void addStudent(const int& rollno, const string& firstName, const string& lastName, const string& course,
                const string& hostelName, int year, const string& fatherName,
                const string& motherName, const string& fatherMobile, const string& studentMobile,
                bool feePaid) {
    // Check if a student with the same roll number already exists
    if (searchStudent(rollno) != nullptr) {
        cout << "Student with Roll No " << rollno << " already exists." << endl;
        return;
    }

    Student* newStudent = new Student;
    newStudent->rollno = rollno;
    newStudent->firstName = firstName;
    newStudent->lastName = lastName;
    newStudent->course = course;
    newStudent->hostelName = hostelName;
    newStudent->year = year;
    newStudent->fatherName = fatherName;
    newStudent->motherName = motherName;
    newStudent->fatherMobile = fatherMobile;
    newStudent->studentMobile = studentMobile;
    newStudent->feePaid = feePaid;
    newStudent->next = nullptr;

      if (fatherMobile.length() != 10 || studentMobile.length() != 10) {
        cout << "Error: Phone numbers must be exactly 10 digits long." << endl;
        return;
    }


    if (head == nullptr) {
        head = newStudent;
    } else {
        Student* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newStudent;
    }
       if (firstName.empty() || lastName.empty() || course.empty() || hostelName.empty() ||
        fatherName.empty() || motherName.empty() || fatherMobile.empty() || studentMobile.empty()) {
        cout << "Some details are missing. Do you want to continue (y/n)? ";
        char choice;
        cin >> choice;

        if (choice != 'y' && choice != 'Y') {
            cout << "Student entry cancelled." << endl;
            return; // Return without adding the student
        }
    }

    // Add student to CSV file
    addStudentToCSV(*newStudent);

    cout << "Student with Roll No " << rollno << " has been added." << endl;
}

    void addStudentToCSV(const Student& s) {
        ofstream file("Students.csv", ios::app);
        if (file.is_open()) {
            file << s.rollno << ","
                 << s.firstName << ","
                 << s.lastName << ","
                 << s.course << ","
                 << s.hostelName << ","
                 << s.year << ","
                 << s.fatherName << ","
                 << s.motherName << ","
                 << s.fatherMobile << ","
                 << s.studentMobile << ","
                 << (s.feePaid ? "Yes" : "No") << ","<< endl;
            file.close();
        } else {
            cout << "Error opening file." << endl;
        }
    }

    void loadFromCSV() {
    ifstream file("Students.csv");
    if (file.is_open()) {
        int rollno, year;
        string firstName, lastName, course, hostelName, fatherName, motherName, fatherMobile, studentMobile, feePaidStr;
        bool feePaid;

        while (file >> rollno >> firstName >> lastName >> course >> hostelName >> year >> fatherName >> motherName >> fatherMobile >> studentMobile >> feePaidStr) {
            feePaid = (feePaidStr == "Yes");
            addStudent(rollno, firstName, lastName, course, hostelName, year, fatherName, motherName, fatherMobile, studentMobile, feePaid);
        }

        file.close();
    } else {
        cout << "Error opening file." << endl;
    }
}

    void listStudents() {
        Student* current = head;
        int recordCount = 0;

        while (current != nullptr) {
            recordCount++;
            cout << "Record: /n" << recordCount << endl;
            cout << "RollNo: " << current->rollno << endl;
            cout << "First Name: " << current->firstName << endl;
            cout << "Last Name: " << current->lastName << endl;
            cout << "Course: " << current->course << endl;
            cout << "Hostel Name: " << current->hostelName << endl;
            cout << "Year: " << current->year << endl;
            cout << "Father's Name: " << current->fatherName << endl;
            cout << "Mother's Name: " << current->motherName << endl;
            cout << "Father's Mobile No: " << current->fatherMobile << endl;
            cout << "Student's Mobile No: " << current->studentMobile << endl;
            cout << "Fee Paid: " << (current->feePaid ? "Yes" : "No") << endl;
            cout<<endl;
            current = current->next;
        }
    }

    Student* searchStudent(int rollNo) {
        Student* current = head;

        while (current != nullptr) {
            if (current->rollno == rollNo) {
                return current;
            }
            current = current->next;
        }

        return nullptr;
    }
    void showUnpaidStudents() {
    Student* current = head;
    int recordCount = 0;

    while (current != nullptr) {
        if (!current->feePaid) {
            recordCount++;
            cout << "Record: " << recordCount << endl;
            cout << "RollNo: " << current->rollno << endl;
            cout << "First Name: " << current->firstName << endl;
            cout << "Last Name: " << current->lastName << endl;
            cout << "Course: " << current->course << endl;
            cout << "Hostel Name: " << current->hostelName << endl;
            cout << "Year: " << current->year << endl;
            cout << "Student's Mobile No: " << current->studentMobile << endl;
            cout << "Fee Paid: " << (current->feePaid ? "Yes" : "No") << endl;
            cout<<endl;
        }
        current = current->next;
    }

    if (recordCount == 0) {
        cout << "No students have unpaid fees." << endl;
    }
}

  void modifyStudent(int rollNo, const string& firstName, const string& lastName, const string& course,
                   const string& hostelName, int year, const string& fatherName,
                   const string& motherName, const string& fatherMobile, const string& studentMobile,
                   bool feePaid) {
   Student* studentToUpdate = searchStudent(rollNo);

   if (studentToUpdate != nullptr) {
       studentToUpdate->rollno = rollNo;
       studentToUpdate->firstName = firstName;
       studentToUpdate->lastName = lastName;
       studentToUpdate->course = course;
       studentToUpdate->hostelName = hostelName;
       studentToUpdate->year = year;
       studentToUpdate->fatherName = fatherName;
       studentToUpdate->motherName = motherName;
       studentToUpdate->fatherMobile = fatherMobile;
       studentToUpdate->studentMobile = studentMobile;
       studentToUpdate->feePaid = feePaid;

       
        if (fatherMobile.length() != 10 || studentMobile.length() != 10) {
        cout << "Error: Phone numbers must be exactly 10 digits long." << endl;
        exit(1);
       
    }
   } else {
       cout << "Student with Roll No " << rollNo << " not found." << endl;
   }
}


    void deleteStudent(int rollNo) {
        if (head == nullptr) {
            cout << "The database is empty." << endl;
            return;
        }

        if (head->rollno == rollNo) {
            Student* temp = head;
            head = head->next;
            delete temp;
            cout << "Student with Roll No " << rollNo << " has been deleted." << endl;
            return;
        }

        Student* current = head;
        while (current->next != nullptr && current->next->rollno != rollNo) {
            current = current->next;
        }

        if (current->next != nullptr) {
            Student* temp = current->next;
            current->next = current->next->next;
            delete temp;
            cout << "Student with Roll No " << rollNo << " has been deleted." << endl;
        } else {
            cout << "Student with Roll No " << rollNo << " not found." << endl;
        }
    }

    ~StudentDatabase() {
        Student* current = head;

        while (current != nullptr) {
            Student* next = current->next;
            delete current;
            current = next;
        }
    }
};

int main() {
    Authentication auth;
    if (auth.login_status()) {
        StudentDatabase database;
        database.loadFromCSV();

        char choice;
        int rollno;  // Changed to int
        string firstName, lastName, course, hostelName, fatherName, motherName, fatherMobile, studentMobile;
        int year;
        bool feePaid;

        Student* result;  // Moved declaration here

        while (true) {
            cout << "\n====== STUDENT DATABASE MANAGEMENT SYSTEM ======";
            cout << "\n0. Search Record";
            cout << "\n1. Add Record";
            cout << "\n2. List Records";
            cout << "\n3. Modify Record";
            cout << "\n4. Delete Record";
            cout << "\n5. Fee defaulter record";
            cout << "\n6. Exit Program";
            cout << "\nSelect Your Choice: ";
            cout<<endl;
            cin >> choice;
            switch (choice) {
                case '0':
                    cout << "Enter Roll number to search: ";
                     if (!(cin >> rollno)) {
                            cout << "Error: Invalid input. Please enter a valid integer for RollNo." << endl;
                            cin.clear(); // Clear error flags
                            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                            break;
                            }
                    result = database.searchStudent(rollno);  // Assigned the result here
                    if (result != nullptr) {
                        cout << "Record found:" << endl;
                        cout<<'\n';
                        cout << "Roll No: " << result->rollno<< endl;
                        cout << "First Name: " << result->firstName << endl;
                        cout << "Last Name: " << result->lastName << endl;
                        cout << "Course: " << result->course << endl;
                        cout << "Year: "<< result->year <<endl;
                        cout << "Fee Paid: " << result->feePaid<<endl;
                    } else {
                        cout << "Record not found." << endl;
                    }
                    break;

                case '1':
                    cout << "Enter the RollNo: ";
                        if (!(cin >> rollno)) {
                            cout << "Error: Invalid input. Please enter a valid integer for RollNo." << endl;
                            cin.clear(); // Clear error flags
                            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                            break;// Terminate program
                        }
                    cout << "Enter the First Name: ";
                    cin >> firstName;
                    cout << "Enter the Last Name: ";
                    cin >> lastName;
                    cout << "Enter the Course: ";
                    cin >> course;
                    cout << "Enter the Hostel Name: ";
                    cin >> hostelName;
                    cout << "Enter the Year: ";
                     if (!(cin >> year)) {
                        cout << "Error: Invalid input. Please enter a valid integer for Year." << endl;
                        cin.clear(); // Clear error flags
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                        exit(1); // Terminate program
                    }
                    cout << "Enter Father's Name: ";
                    cin >> fatherName;
                    cout << "Enter Mother's Name: ";
                    cin >> motherName;
                    cout << "Enter Father's Mobile No: ";
                    cin >> fatherMobile;
                    cout << "Enter Student's Mobile No: ";
                    cin >> studentMobile;
                    cout << "Is Fee Paid (1 for Yes, 0 for No): ";
                    cin >> feePaid;
                 

                    database.addStudent(rollno, firstName, lastName, course, hostelName, year, fatherName,
                                        motherName, fatherMobile, studentMobile, feePaid);
                    break;

                case '2':

                    database.listStudents();
                    break;
                case '3':
                    cout << "Enter Roll number to modify: ";
                     if (!(cin >> rollno)) {
                            cout << "Error: Invalid input. Please enter a valid integer for RollNo." << endl;
                            cin.clear(); // Clear error flags
                            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                            break;// Terminate program
                            }
                    cout << "Enter the First Name: ";
                    cin >> firstName;
                    cout << "Enter the Last Name: ";
                    cin >> lastName;
                    cout << "Enter the Course: ";
                    cin >> course;
                    cout << "Enter the Hostel Name: ";
                    cin >> hostelName;
                    cout << "Enter the Year: ";
                    cin >> year;
                    cout << "Enter Father's Name: ";
                    cin >> fatherName;
                    cout << "Enter Mother's Name: ";
                    cin >> motherName;
                    cout << "Enter Father's Mobile No: ";
                    cin >> fatherMobile;
                    cout << "Enter Student's Mobile No: ";
                    cin >> studentMobile;
                    cout << "Is Fee Paid (1 for Yes, 0 for No): ";
                    cin >> feePaid;
                   
                    database.modifyStudent(rollno, firstName, lastName, course, hostelName, year,fatherName,
                                            motherName, fatherMobile, studentMobile, feePaid);
                    break;
                case '4':
                    cout << "Enter Roll number to delete: ";
                     if (!(cin >> rollno)) {
                            cout << "Error: Invalid input. Please enter a valid integer for RollNo." << endl;
                            cin.clear(); // Clear error flags
                            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                            break;// Terminate program
                            }
                    database.deleteStudent(rollno);
                    break;
                case '5':
                    database.showUnpaidStudents();
                    break;

                case '6':
                    cout << "Exiting the program..." << endl;
                    exit(1);
                    return 0;
                default:
                    cout << "Invalid choice. Please try again." << endl;
                    break;
            }
        }
    }
    return 0;
}
