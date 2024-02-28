/* Name   : ABCU Advising Assistance 
 * Course : CS300 - R3282
 * Author : Reed Murray
 * 
 * This program loads courses into a vector data structure, sorts the courses alphanumerically. It allows the user
 * to print all course information or search a specific course.
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

// define structure to hold course information
struct Course {
    string courseNum;
    string courseTitle;
    vector<string> coursePrereqs;   // Hold prerequisite course numbers
};

/**
* Loads courses into course structure and stores in vector
* 
* @return vector of course objects
*/
vector<Course> loadCourses() {
    vector<Course> courses;

    fstream courseInfo;
    courseInfo.open("CourseInformation.txt", ios::in);  // open file with read permission
    if (!courseInfo) {
        cout << "Error opening file" << endl;
        return courses;
    }

    // Read lines until end of file. Parse each line for course attributes
    while (!courseInfo.eof()) { 
        Course curCourse;
        string curLine;
        string delimiter = ",";

        getline(courseInfo, curLine); 

        string courseNum = curLine.substr(0, curLine.find(delimiter));  // Data before the first comma is the course number
        curLine.erase(0, courseNum.length() + 1);   // Delete used information from the line
        curCourse.courseNum = courseNum;

        string courseTitle = curLine.substr(0, curLine.find(delimiter));    // Data before the comma is the course title
        curLine.erase(0, courseTitle.length() + 1);
        curCourse.courseTitle = courseTitle;

        while (curLine.length() > 0) {      // Check for prerequisites, and add them to the course prereqs vector
            string prereq = curLine.substr(0, curLine.find(delimiter));
            curLine.erase(0, prereq.length() + 1);
            curCourse.coursePrereqs.push_back(prereq);
        }
        courses.push_back(curCourse);   // add Course to courses vector
    }

    return courses;
}

/**
*Sort the courses using selection sort algorithm
* 
* @param courses vector containing all courses
*/
vector<Course> selectionSort(vector<Course>& courses) {
    // Selection sort the courses
    size_t size = courses.size();
    int min;

    for (size_t pos = 0; pos < size - 1; ++pos) {
        min = pos;
        for (size_t j = pos; j < size; ++j) {
            if (courses[j].courseTitle.compare(courses[min].courseTitle) < 0) { // find minimum course number 
                min = j;
            }
        }
        if (min != pos) {
            swap(courses.at(pos), courses.at(min)); // Swap current with minimum 
        }
    }
    return courses;
}

/**
* Print all the courses in the in aphanumeric order
* 
* @param courses vector containing all the courses as Course objects
*/
static void printCourses(vector<Course> courses) {
    // Sort the courses before printing
    courses = selectionSort(courses);

    for (Course i : courses) {
        cout << " | Course Name: " << i.courseTitle << endl << " | Course Number: " << i.courseNum << endl << " | Prerequisites: ";
        for (string j : i.coursePrereqs) {
            cout << j << " | ";
        }
        cout << endl << endl;
    }
        
}

/**
* Print a course queried by the user
* 
* @param Vector of courses, course number of search key
*/
void printCourse(vector<Course> courses, string courseNum) {

    for (Course i : courses) {
        if (i.courseNum.compare(courseNum) == 0) {
            cout << " | Course Name: " << i.courseTitle << endl << " | Course Number: " << i.courseNum << endl << " | Prerequisites: ";
            for (string j : i.coursePrereqs) {
                // Loop through prerequisites to print them
                cout << j << " | ";
            }
            cout << endl << endl;
            return;
        }
    }
    cout << "Course not found" << endl;
}

/**
* Main function: display menu and facilitate user choices
*/

int main()
{
    clock_t ticks;
    vector<Course> courses;
    string courseSearch;
    int choice = 0;

    while (choice != 9) {
        cout << "MENU:" << endl;
        cout << "   1. Load Courses" << endl;
        cout << "   2. Print Courses" << endl;
        cout << "   3. Search Course" << endl;
        cout << "   9. Exit Program" << endl;
        cin >> choice;

        switch (choice) {
        
        case 1:
            ticks = clock();

            courses = loadCourses(); // Load the courses file into vector & sort them alphanumerically

            ticks = clock() - ticks;
            cout << ticks << " Clock ticks" << endl;
            cout << "Time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl; // Tracks the time to load the course file
            break;

        case 2:
            // Print all courses in alphanumeric order
            printCourses(courses);

            break;

        case 3:
            // Prompt user to enter a course to search and print
            cout << "Enter a Course Number to search: " << endl;
            cin >> courseSearch;

            printCourse(courses, courseSearch);

            break;
        }
    }
    cout << "Exiting program. Good-bye!" << endl;

    return 0;
}
