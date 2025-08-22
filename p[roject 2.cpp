#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to hold course information
struct Course {
    string courseNumber;
    string courseTitle;
    vector<string> prerequisites;
};

// Function to load courses from a CSV file into a map
void loadCourses(const string& filename, map<string, Course>& courses) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Could not open file " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string courseNum, courseTitle, prereq;

        // Get course number
        getline(ss, courseNum, ',');
        // Get course title
        getline(ss, courseTitle, ',');

        Course course;
        course.courseNumber = courseNum;
        course.courseTitle = courseTitle;

        // Get prerequisites (if any)
        while (getline(ss, prereq, ',')) {
            course.prerequisites.push_back(prereq);
        }

        // Store in map
        courses[courseNum] = course;
    }

    file.close();
    cout << "Courses loaded successfully from " << filename << endl;
}

// Function to print all courses in alphanumeric order
void printCourseList(const map<string, Course>& courses) {
    cout << "\nHere is a sample schedule:\n" << endl;
    for (const auto& pair : courses) {
        cout << pair.second.courseNumber << ", " << pair.second.courseTitle << endl;
    }
    cout << endl;
}

// Function to print information about a specific course
void printCourseInfo(const map<string, Course>& courses, const string& courseNum) {
    auto it = courses.find(courseNum);
    if (it == courses.end()) {
        cout << "Course not found: " << courseNum << endl;
        return;
    }

    Course course = it->second;
    cout << course.courseNumber << ", " << course.courseTitle << endl;

    if (course.prerequisites.empty()) {
        cout << "Prerequisites: None" << endl;
    }
    else {
        cout << "Prerequisites: ";
        for (size_t i = 0; i < course.prerequisites.size(); i++) {
            cout << course.prerequisites[i];
            if (i < course.prerequisites.size() - 1) cout << ", ";
        }
        cout << endl;
    }
}

// Function to display the main menu
void displayMenu() {
    cout << "\nMenu Options:" << endl;
    cout << "  1. Load Data Structure" << endl;
    cout << "  2. Print Course List" << endl;
    cout << "  3. Print Course" << endl;
    cout << "  9. Exit" << endl;
    cout << "Enter choice: ";
}

// Main program
int main() {
    map<string, Course> courses;
    string filename;
    int choice = 0;

    cout << "Welcome to the ABCU Course Planner." << endl;

    while (choice != 9) {
        displayMenu();
        cin >> choice;

        switch (choice) {
        case 1: {
            cout << "Enter the file name: ";
            cin >> filename;
            loadCourses(filename, courses);
            break;
        }
        case 2:
            if (courses.empty()) {
                cout << "Error: No data loaded. Please load a file first." << endl;
            }
            else {
                printCourseList(courses);
            }
            break;
        case 3: {
            if (courses.empty()) {
                cout << "Error: No data loaded. Please load a file first." << endl;
            }
            else {
                string courseNum;
                cout << "Enter course number: ";
                cin >> courseNum;
                printCourseInfo(courses, courseNum);
            }
            break;
        }
        case 9:
            cout << "Thank you for using the ABCU Course Planner!" << endl;
            break;
        default:
            cout << "Invalid option. Please try again." << endl;
        }
    }

    return 0;
}
