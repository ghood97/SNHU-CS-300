#include "HashTable.hpp"
#include "CSVparser.hpp"
#include <iostream>
#include <string>
using namespace std;

/// <summary>
/// Load all courses into a hash table
/// </summary>
/// <param name="csvPath"></param>
/// <param name="hashTable"></param>
void loadCourses(string csvPath, HashTable* hashTable) {
    cout << "Loading CSV file " << csvPath << endl;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    // read and display header row - optional
    vector<string> header = file.getHeader();
    for (auto const& c : header) {
        cout << c << " | ";
    }
    cout << "" << endl;

    try {
        // loop to read rows of a CSV file
        for (unsigned int i = 0; i < file.rowCount(); i++) {

            // Create a data structure and add to the collection of courses
            Course course;
            course.courseId = file[i][0];
            course.courseName = file[i][1];
            course.prerequisites = vector<string>();

            // Load variable number of prerequisites
            for (int j = 2; j < file[i].size(); j++)
            {
                course.prerequisites.push_back(file[i][j]);
            }

            // push course to the table
            hashTable->Insert(course);
        }
    }
    catch (csv::Error& e) {
        std::cerr << e.what() << std::endl;
    }
}


int main()
{
    string filePath;
    cout << "Welcome to ABCU's course catalog." << endl << endl;
    cout << "Enter the absolute path for the csv file of courses: ";
    cin >> filePath;

    HashTable* courseTable;

    Course course;
    courseTable = new HashTable();

    int choice = 0;
    while (choice != 9)
    {
        cout << "\nMenu:" << endl;
        cout << "\t1) Load Courses" << endl;
        cout << "\t2) Display All Courses" << endl;
        cout << "\t3) Display One Course" << endl;
        cout << "\t9) Exit" << endl;
        cin >> choice;

        switch (choice)
        {
        case 1:
            loadCourses(filePath, courseTable);
            cout << "Finished loading courses." << endl;
            break;
        case 2:
            cout << "Courses Catalog:" << endl << endl;
            courseTable->PrintAll();
            break;
        case 3:
            string courseId;
            cout << "Enter the course ID: ";
            cin >> courseId;

            course = courseTable->Search(courseId);
            if (course.courseId == "")
            {
                cout << "Course " << courseId << " not found.\n\n";
            }
            else
            {
                course.Print();
            }
        }
    }
    cout << "\nGoodbye." << endl;
    return 0;
}