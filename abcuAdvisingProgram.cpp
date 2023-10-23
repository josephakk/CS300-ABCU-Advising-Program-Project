// =================================
// Name: Joseph Kawamoto
// Class: CS300 23EW1
// Professor: Terry Atkison
// Date: 10/10/2023
// =================================
 
// abcuAdvisingProgram.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

//Designate Course object structure
struct Course {
	string courseNumber;
	string courseTitle;
	string prerequisites;
	string tempString;
};

//Load and parse .csv files
void loadFile(unordered_map<string, Course>& courseData, const string& filePath) {
	ifstream inputFile(filePath);
	if (!inputFile.is_open()) {
		cerr << "Error opening the file." << endl;
		return;
	}

	string line;
	while (getline(inputFile, line)) {
		stringstream inputString(line);

		string courseNumber, courseTitle, prerequisites;
		getline(inputString, courseNumber, ',');
		getline(inputString, courseTitle, ',');
		getline(inputString, prerequisites);

		//Removes the characters in front of the course numbers
		if (courseNumber.size() >= 3 && courseNumber[0] == '\xEF' && courseNumber[1] == '\xBB' && courseNumber[2] == '\xBF') {
			courseNumber.erase(0, 3);
		}

		//Removes the double quotations before and after course number
		courseNumber.erase(remove(courseNumber.begin(), courseNumber.end(), '\"'), courseNumber.end());
		prerequisites.erase(remove(prerequisites.begin(), prerequisites.end(), '\"'), prerequisites.end());

		Course c;
		c.courseNumber = courseNumber;
		c.courseTitle = courseTitle;
		c.prerequisites = prerequisites;

		courseData[courseNumber] = c;
	}
}

//Print course list
void printCourseList(const unordered_map<string, Course>& courseData) {
	cout << "Course List: " << endl;
	for (const auto& entry : courseData) {
		cout << "Course Number: " << entry.second.courseNumber << endl;
		cout << "Course Title: " << entry.second.courseTitle << endl;
		cout << "Prerequisites: " << entry.second.prerequisites << endl;
		cout << "---------------------------" << endl;
	}
}

//Search for and print specific courses from course list
void printSpecificCourse(const unordered_map<string, Course>& courseData) {
	string courseNumber;
	cout << "Enter the course number: ";
	cin.ignore();
	getline(cin, courseNumber); 

	courseNumber = courseNumber;
	
	transform(courseNumber.begin(), courseNumber.end(), courseNumber.begin(), ::toupper);

	auto it = courseData.find(courseNumber);
	if (it != courseData.end()) {
		const Course& course = it->second;
		cout << "Course Number: " << course.courseNumber << endl;
		cout << "Course Title: " << course.courseTitle << endl;
		cout << "Prerequisites: " << course.prerequisites << endl;
	}
	else {
		cout << "Course not found." << endl;
	}
}

int main() {
	int inputOption = 0;
	unordered_map<string, Course> courseData;

	cout << "Welcome to the ABCU Advising Program" << endl;

	while (inputOption != 4) {
		cout << "Please make a selection from the menu below: " << endl;
		cout << "1: Load Data Structure" << endl;
		cout << "2: Print Course List" << endl;
		cout << "3: Print Course" << endl;
		cout << "4: Exit" << endl;
		cout << " " << endl;
		cin >> inputOption;

		switch (inputOption) {
		case 1:
			loadFile(courseData, "ABCUAdvisingProgramInput.csv");
			cout << "Data loaded successfully!" << endl;
			break;
		case 2:
			printCourseList(courseData);
			break;
		case 3:
			printSpecificCourse(courseData);
			break;
		case 4:
			cout << "Exiting the program." << endl;
			return 0;
		default:
			cout << "Invalid input. Please select a valid option." << endl;
			break;
		}

		if (cin.fail()) {
			cout << "Invalid input. Please enter a valid option." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}

	return 0;
}
