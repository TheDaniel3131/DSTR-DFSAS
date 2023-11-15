#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm> 
#include <iomanip>
#include "clear_screen.h"
#include "clearInputBuffer.h"
#include "user.h"
#include "doctor.h"
#include "admin.h"
#include "readData.h"
#include "mergeSort.h"
#include "dengueCase.h"

using namespace std;

//vector<Doctor> doctors;
//vector<DengueCase> dengueCases;
vector<DengueCase> allReportedCases; // Definition of the global vector

int main() {
    DoctorList doctorsList;
    UserList usersList;
    string userUsername; // Declare userUsername
    string userPassword;    
    string userState;      // Declare userState
    string selectedState;
    string adminUsername, adminPassword;
    vector<string> annualDengueHeader;
    vector<vector<string>> annualDengueData;
    if (!readCSV("Annual number of dengue cases by state.csv", annualDengueHeader, annualDengueData)) {
        return 1;
    }

    vector<string> weeklyDengueHeader;
    vector<vector<string>> weeklyDengueData;
    if (!readCSV("Number of dengue fever cases weekly by state.csv", weeklyDengueHeader, weeklyDengueData)) {
        return 1;
    }

    map<int, DengueData> annualData; // Year -> DengueData
    parseWeeklyDengueData(weeklyDengueData, annualData, weeklyDengueHeader);

    string doctorUsername;
    string doctorPassword;
    bool doctorLoggedIn = false;
    Doctor* currentDoctor = nullptr;
    User* currentUser = nullptr;

    while (true) {
        cout << "*******************************************" << endl;
        cout << "*        Dengue Surveillance System       *" << endl;
        cout << "*******************************************" << endl;
        cout << "*1. Admin Login                           *" << endl;
        cout << "*2. Doctor Login                          *" << endl;
        cout << "*3. User Login                            *" << endl;
        cout << "*4. Register as a Doctor                  *" << endl;
        cout << "*5. Register as a User                    *" << endl;
        cout << "*6. Exit                                  *" << endl;
        cout << "*******************************************" << endl;
        cout << "Enter your choice: ";
        int choice;
        // cin >> choice;
        // 
        // Check if the input is of the expected type
        while (!(cin >> choice)) {
            clearScreen();
            //cout << "Invalid input. Please enter a number." << endl;
            clearInputBuffer(); // Clear the input buffer
            break;
            //cout << "Enter your choice: ";
        }

        switch (choice) {
        case 1:
            cout << "Enter admin username: ";
            cin >> adminUsername;
            cout << "Enter admin password: ";
            cin >> adminPassword;
            clearScreen();
            if (adminLogin(adminUsername, adminPassword)) {
                cout << "Admin login successful." << endl;
                adminTasks(annualData, weeklyDengueData, weeklyDengueHeader);
            }
            else {
                cout << "Admin login failed. Please try again." << std::endl;
            }
            break;
        case 2:
            cout << "Enter your username: ";
            cin >> doctorUsername;
            cout << "Enter your password: ";
            cin >> doctorPassword;
            clearScreen();

            currentDoctor = doctorLogin(doctorUsername, doctorPassword);
            if (currentDoctor) {
                cout << "Doctor login successful." << std::endl;
                doctorLoggedIn = true;

                while (doctorLoggedIn) {
                    //clearScreen();
                    cout << "****************************************" << std::endl;
                    cout << "*             Doctor Panel             *" << std::endl;
                    cout << "****************************************" << std::endl;
                    cout << "*1. Manage Personal Information        *" << std::endl;
                    cout << "*2. Report Dengue Case                 *" << std::endl;
                    cout << "*3. View Dengue Cases                  *" << std::endl;
                    cout << "*4. Find Dengue Cases by Patient Name  *" << std::endl;
                    cout << "*5. Find Dengue Cases by Age and State *" << std::endl;
                    cout << "*6. Logout                             *" << std::endl;
                    cout << "****************************************" << std::endl;
                    cout << "Enter your choice: ";
                    int doctorChoice;
                    //cin >> doctorChoice;
                    while (!(cin >> doctorChoice)) {
                        clearScreen();
                        //cout << "Invalid input. Please enter a number." << endl;
                        clearInputBuffer(); // Clear the input buffer
                        break;
                        //cout << "Enter your choice: ";
                    }

                    switch (doctorChoice) {
                    case 1:
                        clearScreen();
                        manageDoctorPersonalInfo(*currentDoctor);
                        break;
                    case 2:
                        clearScreen();
                        reportDengueCase(*currentDoctor);
                        break;
                    case 3:
                        clearScreen();
                        viewDoctorDengueCases(*currentDoctor);
                        break;
                    case 4: {
                        clearScreen();
                        cout << "   Find Dengue Cases by Patient Name   " << endl;
                        cout << "---------------------------------------" << endl;
                        string patientName;
                        cout << "Enter the patient's name: ";
                        cin >> patientName;
                        cout << "Matching Dengue Cases for Patient: " << patientName << endl;

                        for (const DengueCase& dengueCase : allReportedCases) {
                            if (dengueCase.patientName == patientName) {
                                // Display the matching case details
                                cout << "Patient Name: " << dengueCase.patientName << endl;
                                cout << "Patient Age: " << dengueCase.age << endl;
                                cout << "Date: " << dengueCase.date << endl;
                                cout << "Doctor Information: " << dengueCase.doctorInfo << endl;
                                cout << "---------------------------------------" << endl << endl;
                            }
                        }
                        break;
                    }
                    case 5: {
                        clearScreen();
                        cout << "   Find Dengue Cases by Age and State  " << endl;
                        cout << "---------------------------------------" << endl;
                        int age;
                        string state;
                        cout << "Enter the patient's age: ";
                        cin >> age;
                        cout << "Enter the state: ";
                        cin >> state;
                        cout << "Matching Dengue Cases for Age: " << age << " and State: " << state << endl;

                        for (const DengueCase& dengueCase : allReportedCases) {
                            if (dengueCase.age == age && dengueCase.state == state) { // Check both age and state
                                // Display the matching case details
                                cout << "Patient Name: " << dengueCase.patientName << endl;
                                cout << "Patient Age: " << dengueCase.age << endl;
                                cout << "Date: " << dengueCase.date << endl;
                                cout << "Doctor Information: " << dengueCase.doctorInfo << endl;
                                cout << "State: " << dengueCase.state << endl;
                                cout << "---------------------------------------" << endl << endl;
                            }
                        }
                        break;
                    }
                    case 6:
                        clearScreen();
                        cout << "Doctor logged out." << endl;
                        doctorLoggedIn = false;
                        currentDoctor = nullptr;
                        break;
                    default:
                        cout << "Invalid choice. Please try again." << endl;
                    }
                }
            }
            else {
                std::cout << "Doctor login failed. Please try again." << std::endl;
            }
            break;
        case 3:
            std::cout << "Enter your username: ";
            std::cin >> userUsername; // Change variable name to "userUsername"
            std::cout << "Enter your password: ";
            std::cin >> userPassword; // Change variable name to "userState"
            clearScreen();

            //if (userLogin(userUsername, userPassword)) { // Change function name to "userLogin"
              //  std::cout << "User login successful." << std::endl;
            if (User* currentUser = userLogin(userUsername, userPassword)) {
                cout << "User login successful." << endl;
                bool userLoggedIn = true; // Set to true upon successful login
                //User currentUser; // Populate with the current user's data
                //string date;
                while (userLoggedIn) {
                    cout << "****************************************" << endl;
                    cout << "*            User Dashboard            *" << endl;
                    cout << "****************************************" << endl;
                    cout << "*1. View Total Dengue Cases            *" << endl;
                    cout << "*2. View Daily Dengue Cases            *" << endl;
                    cout << "*3. View Dengue Alert Messages         *" << endl;
                    cout << "*4. Manage Personal Information        *" << endl;
                    cout << "*5. Search Past Dengue Fever Status    *" << endl;
                    cout << "*6. Logout                             *" << endl;
                    cout << "****************************************" << endl;
                    cout << "Enter your choice: ";
                    int userChoice;
                    //std::cin >> userChoice;
                    while (!(cin >> userChoice)) {
                        clearScreen();
                        //cout << "Invalid input. Please enter a number." << endl;
                        clearInputBuffer(); // Clear the input buffer
                        break;
                        //cout << "Enter your choice: ";
                    }

                    switch (userChoice) {
                    case 4:
                        // 1.2 Manage Personal Information
                        clearScreen();
                        manageUserPersonalInfo(*currentUser);
                        break;

                    case 1:
                        // 1.3 View Total Dengue Cases
                        clearScreen();
                        int selectedYear;
                        cout << endl << "        View Total Dengue Cases        " << endl;
                        cout << "---------------------------------------" << endl;
                        cout << "Enter year (2018-2023): ";
                        cin >> selectedYear;
                        cout << "Enter state: ";
                        cin >> selectedState;
                        cout << endl;

                        // Implement function to view total dengue cases for the selected year and state
                        viewTotalDengueCases(annualData, selectedYear, selectedState);
                        cout << endl;
                        break;

                    case 2:
                        // Call the function to view daily dengue cases
                        clearScreen();
                        viewDailyDengueCases();
                        // 1.4 View Daily Dengue Cases
                        break;

                    case 3:
                        // 1.5 View Dengue Alert Messages
                        clearScreen();
                        cout << "       View Dengue Alert Messages      " << endl;
                        cout << "---------------------------------------" << endl;
                        // Implement function to view dengue alert messages
                        viewDengueAlert(*currentUser);
                        cout << endl << endl;
                        break;

                    case 5: {
                        // 1.6 Search Past Dengue Fever Status
                        // Implement function to search past dengue fever status based on a date range
                        clearScreen();
                        cout << "    Search Past Dengue Fever Status    " << endl;
                        cout << "---------------------------------------" << endl;
                        string date;
                        cout << "Enter the Past Dengue Fever Date (DD-MM-YYYY): ";
                        cin >> date;
                        searchPastDengueFeverStatus(date);
                        break;

                        //cout << "Search Past Dengue Fever Status:" << endl;
                        //string date;
                        //cout << "Enter the Past Dengue Fever Date: ";
                        //cin >> date;
                        //cout << "Matching Dengue Cases for Date: " << date << endl;

                        //for (const DengueCase& dengueCase : currentUser->reportedCases) {
                        //    if (dengueCase.date == date) {
                        //        // Display the matching case details
                        //        cout << "Patient Name: " << dengueCase.patientName << endl;
                        //        cout << "Patient Age: " << dengueCase.age << endl;
                        //        cout << "Date: " << dengueCase.date << endl;
                        //        cout << "Doctor Information: " << dengueCase.doctorInfo << endl;
                        //        cout << "-------------------" << endl;
                        //    }
                        //}
                        break;
                    }
                    case 6:
                        // 1.7 Logout
                        clearScreen();
                        cout << "Logging out." << endl;
                        userLoggedIn = false;
                        break;

                    default:
                        cout << "Invalid choice. Please try again." << endl;
                    }
                }
            }
            else {
                std::cout << "User login failed. Please try again." << std::endl;
            }
            break;
        case 4: {
            Doctor newDoctor;
            cout << "Enter your username: ";
            cin >> newDoctor.username;
            cout << "Enter your password: ";
            cin >> newDoctor.password;
            cout << "Enter your state: ";
            cin >> newDoctor.state;
            cout << "Enter your phone number: ";
            cin >> newDoctor.phoneNumber;
            doctors.push_back(newDoctor);
            clearScreen();
            cout << "Doctor registration successful." << std::endl;
            break;
        }
        case 5: {
            User newUser;
            std::cout << "Enter your username: ";
            std::cin >> newUser.username;
            cout << "Enter your password: ";
            cin >> newUser.password;
            std::cout << "Enter your state: ";
            std::cin >> newUser.state;
            std::cout << "Enter your phone number: ";
            std::cin >> newUser.phoneNumber;
            users.push_back(newUser);
            clearScreen();
            std::cout << "User registration successful." << std::endl;
            break;
        }
        case 6:
            std::cout << "Exiting the Dengue Surveillance System." << std::endl;
            return 0;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }
    return 0;
}
