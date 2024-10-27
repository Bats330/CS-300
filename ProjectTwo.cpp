// =====================================================================
// Name        : ProjectTwo.cpp
// Author      : Joseph Eaton
// Date        : 10/16/2024
// Class       : CS-300: Project Two
// Description : Program designed to load a data file from a csv file,
//               print a course list in alphanumeric order, and print a 
//               specific course and any prerequisites
//=======================================================================

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <string>
#include <cctype>

using namespace std;

// Course structure to hold course information
struct Course {
    string courseNumber;
    string courseTitle;
    vector<string> prerequisites;
};

// Function prototypes
void loadCourseData(unordered_map<string, Course>& courses);
void printAllCourses(const unordered_map<string, Course>& courses);
void printCourseInfo(const unordered_map<string, Course>& courses, const string& courseNumber);
string toLowerCase(const string& str);

// Main function
int main() {
    unordered_map<string, Course> courses;
    int choice;

    do {
        // Display menu
        cout << "\nWelcome to the course planner\n" << endl;
        cout << "1. Load Data Structure" << endl;
        cout << "2. Print course list" << endl;
        cout << "3. Print course" << endl;
        cout << "9. Exit\n" << endl;
        cout << "What would you like to do? ";
        cin >> choice;

        // If statement to handle user choices
        //If user chooses 1 load file
        if (choice == 1) {
            loadCourseData(courses);
        }
        // If choice is 2 displays all courses in alphanumeric order
        else if (choice == 2) {
            printAllCourses(courses);
        }
        //if choice is 3 prompts user for course then displays that courses information including prerequisites
        else if (choice == 3) {
            string courseNumber;
            cout << "What course do you want to know about? ";
            cin >> courseNumber;
            printCourseInfo(courses, courseNumber);
        }
        //exits the program if user choice is 9 and thanks user.
        else if (choice == 9) {
            cout << "Thank you for using the course planner!" << endl;
        }
        else {
            // if user choice is anything other than 1,2,3,4 or 9 error message followed byprompting user to choose again
            cout << choice << " is not a valid option. Please choose again. " << endl;
        }
    } while (choice != 9);

    return 0;
}

// Function to load course informations from file
void loadCourseData(unordered_map<string, Course>& courses) {
    string filename;
    cout << "Enter the filename containing course information. ";
    cin >> filename;

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Could not open file " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        size_t pos = 0;
        string token;
        Course course;

        // If statement to extract courseNumber
        pos = line.find(',');
        if (pos != string::npos) {
            course.courseNumber = line.substr(0, pos); //gets the courseNumber
            line.erase(0, pos + 1); //removes from the information from the line
        }

        // If statement to extract courseTitle
        pos = line.find(',');
        if (pos != string::npos) {
            course.courseTitle = line.substr(0, pos); //gets the courseTitle
            line.erase(0, pos + 1); //removes from the information from the line
        }

        // while loop to extract each prerequisite seperated by commas
        while ((pos = line.find(',')) != string::npos) {
            //takes the first prerequisite 
            token = line.substr(0, pos);
            // Erases the processed prerequisite
            course.prerequisites.push_back(token);
            line.erase(0, pos + 1);
        }
        //Adds the last prerequisite if there is any left after the loop
        if (!line.empty()) {
            course.prerequisites.push_back(line);
        }
        // adds the course to the hashtable
        courses[course.courseNumber] = course;
    }

    file.close();
    cout << "\nCourse list loaded sucessfully." << endl;
}

// Function to print the courses in alphanumeric order
void printAllCourses(const unordered_map<string, Course>& courses) {
    if (courses.empty()) {
        cout << "No course data available. Please load data first." << endl;
        return;
    }

    // Creates a copy of the course vector then sorts.
    vector<string> courseNumbers;
    for (const auto& pair : courses) {
        courseNumbers.push_back(pair.first);
    }

    // Sorts the courses by course number
    sort(courseNumbers.begin(), courseNumbers.end());

    // Displays the sorted list
    cout << "\nCourses in alphanumeric order:" << endl;
    for (const auto& courseNumber : courseNumbers) {
        cout << courseNumber << ": " << courses.at(courseNumber).courseTitle << endl;
    }
}

// Function to ensure courses are found no matter the Case of the letter example: C or c
string toLowerCase(const string& str) {
    string lowerStr = str;
    for (char& c : lowerStr) {
        c = tolower(c);
    }
    return lowerStr;
}

// Function to the selected courses information.
void printCourseInfo(const unordered_map<string, Course>& courses, const string& courseNumber) {
    string lowerCourseNumber = toLowerCase(courseNumber); //converts to user input to lowercase for a more error free search.
    for (const auto& pair : courses) {
        if (toLowerCase(pair.first) == lowerCourseNumber) {
            //prints the course details if everything is found
            const Course& course = pair.second;
            cout << "\nCourse Number: " << course.courseNumber << endl;
            cout << "Course Title: " << course.courseTitle << endl;
            cout << "Prerequisites: " << (course.prerequisites.empty() ? "None" : "");
            for (size_t i = 0; i < course.prerequisites.size(); ++i) {
                cout << course.prerequisites[i]; //prints the each course prerequisite.
                if (i < course.prerequisites.size() - 1) {
                    cout << ", "; // adds a comma inbetween the prerequisites.
                }
            }
            cout << endl;
            return;
        }
    }
    //error message if the course is not found.
    cout << "Course not found: " << courseNumber << endl;
}

