#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

int main() {
    string fileName;
    int choice;
    string courseNumber;

    cout << "Welcome" << endl;
    do {
        cout << "1. Load Data Structure." << endl;
        cout << "2. Print Course List." << endl;
        cout << "3. Print Course." << endl;
        cout << "4. EXIT" << endl;
        cout << "Pick an option";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter file name: ";
            cin >> fileName;
            loadDataStructure(fileName);
            break;
        case 2:
            printCourseList();
            break;
        case 3:
            cout << “Enter course number”;
            cin >> courseNumber;
            printCourse(courseNumber);
            break;
        case 4:
            cout << "EXIT" << endl;
            break;
        default:
            cout << choice << " is not a valid option." << endl;
        }
    } while (choice != 4);

    return 0;
}

struct Course {
    string courseId;
    string courseName;
    vector<string> prerequisites;
};

Vector<Course>courses;

// Function to load data from file into the data structure
void loadDataStructure(unordered_map<string, Course>& courses) {
    string fileName;
    cout << "Enter the file name containing course data: ";
    cin >> fileName;

    ifstream file(fileName);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << fileName << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        string courseId, courseName, prerequisite;
        size_t pos = line.find(',');
        courseId = line.substr(0, pos);
        courseName = line.substr(pos + 2); // Skip comma and space

        Course course;
        course.name = courseName;

        // Extract and add prerequisites
        while ((pos = line.find(',')) != string::npos) {
            prerequisite = line.substr(0, pos);
            course.prerequisites.push_back(prerequisite);
            line.erase(0, pos + 2); // Skip comma and space
        }

        courses.insert({ courseId, course });
    }

    file.close();
}

//function for printing course list 
void printCourseList() {
    sort(courses.begin(), courses.end(), [](Course& a, Course& b) {
        return a.courseNumber < b.courseNumber;
        });

    cout << "Course List:" << endl;
    for (auto& course : courses) {
        cout << course.courseNumber << ", " << course.courseTitle << endl;
    }
}
//function that prints course
void printCourse( string& courseNumber) {
    auto it = find_if(courses.begin(), courses.end(), [&](Course& c) {
        return c.courseNumber == courseNumber;
        });

    if (it != courses.end()) {//checks for course 
        cout << it->courseNumber << ", " << it->courseTitle << endl;//prints course info
        cout << "Prerequisites: ";//checks for prerequesites
        if (it->prerequisites.empty()) {
            cout << "None" << endl;
        }
        else {
            for (auto& prerequisite : it->prerequisites) {
                cout << prerequisite << ", ";//prints prerequisites 
            }
            cout << endl;
        }
    }
    else {
        cout << "Course not found." << endl;//error
    }
}

