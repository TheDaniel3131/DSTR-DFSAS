#pragma once
#include <string>
#include "mergeSort.h"

using namespace std;

struct Admin {
    string username;
    string password;
};

Admin admin{ "admin", "admin123" }; // Admin login credentials


// Function for admin login
bool adminLogin(const string& username, const string& password) {
    return (admin.username == username && admin.password == password);
}

// Function to view weekly dengue cases for all states in ascending order
bool compareRows(const vector<string>& row1, const vector<string>& row2) {
    // Assuming the week number is in the second column (index 1)
    int week1 = stoi(row1[1]);
    int week2 = stoi(row2[1]);
    return week1 < week2;
}

void viewWeeklyDengueCases(std::vector<std::vector<std::string>>& weeklyDengueData) {
    // Sort the data based on the week number in ascending order using merge sort
    mergeSort(weeklyDengueData, 0, weeklyDengueData.size() - 1);

    cout << "               Weekly Dengue Cases for All States (Sorted by Week Number)              " << endl;
    cout << "***************************************************************************************" << endl << endl;

    cout << setw(5) << "YEAR" << setw(5) << "WEEK";
    cout << setw(5) << "JOH" << setw(5) << "KED" << setw(5) << "KEL";
    cout << setw(5) << "MEL" << setw(5) << "NS";
    cout << setw(5) << "PAH" << setw(5) << "PER" << setw(5) << "PLS";
    cout << setw(5) << "PP" << setw(5) << "SAB";
    cout << setw(5) << "SAR" << setw(5) << "SEL";
    cout << setw(5) << "TER" << setw(5) << "KL";
    cout << setw(5) << "LAB" << endl;

    std::cout << "***************************************************************************************" << std::endl;

    for (const std::vector<std::string>& row : weeklyDengueData) {
        for (const std::string& cell : row) {
            cout << setw(5) << cell;
        }
        std::cout << std::endl;
    }
}

// Function to send dengue alerts to users
// Function to send a dengue alert message to a user
// Function to send a dengue alert message to a user
void sendDengueAlert(User& user, const string& alertMessage) {
    // Implement the logic to send a dengue alert message to the user here.
    // For simplicity, we'll just print the alert message here.
    cout << "Sending Dengue Alert to " << user.username << ": " << alertMessage << endl;
    user.alerts.push_back(alertMessage);
}

void viewTotalDengueCasesBarChart(const map<int, DengueData>& annualData) {
    for (const auto& data : annualData) {
        int year = data.first;
        const DengueData& dengueData = data.second;
        int totalCases = 0;

        for (const auto& stateData : dengueData.stateData) {
            for (int casesInWeek : stateData.second) {
                totalCases += casesInWeek;
            }
        }

        cout << year << ": ";
        for (int i = 0; i < totalCases; i += 10) {
            cout << "*";
        }
        cout << " (" << totalCases << ")" << endl << endl;
    }
}


// Function to perform admin tasks
void adminTasks(map<int, DengueData>& annualData, vector<vector<string>>& weeklyDengueData, vector<string>& header) {
    int adminChoice;
    string state; // Declare state variable outside the switch
    string userUsername; // Declare userUsername outside the switch
    //std::string userPassword;    // Declare userState outside the switch
    string userState;
    User* userToAlert = nullptr;  // Declare userToAlert outside the switch

    while (true) {
        cout << "*************************************************************************" << endl;
        cout << "*                             Admin Panel                               *" << endl;
        cout << "*************************************************************************" << endl;
        cout << "*1. Manage doctor accounts                                              *" << endl;
        cout << "*2. Manage user accounts                                                *" << endl;
        cout << "*3. Send an alert message to users                                      *" << endl;
        cout << "*4. View weekly dengue cases for all states                             *" << endl;
        cout << "*5. View total dengue cases reported in Malaysia between 2018 - 2023    *" << endl;
        cout << "*6. Exit                                                                *" << endl;
        cout << "*************************************************************************" << endl;
        cout << "Enter your choice: ";
        //std::cin >> adminChoice;
        while (!(cin >> adminChoice)) {
            clearScreen();
            //cout << "Invalid input. Please enter a number." << endl;
            clearInputBuffer(); // Clear the input buffer
            break;
            //cout << "Enter your choice: ";
        }

        switch (adminChoice) {
        case 1:
            int doctorOperation;
            cout << "Manage Doctor Accounts:" << endl;
            cout << "1. Add a New Doctor" << endl;
            cout << "2. Remove an Existing Doctor" << endl;
            cout << "Enter your choice: ";
            cin >> doctorOperation;
            clearScreen();

            if (doctorOperation == 1) {
                // Add a new doctor
                Doctor newDoctor;
                cout << endl << "           Add New Doctor Account            " << endl;
                cout << "*********************************************" << endl;
                cout << "Enter the username for the new doctor: ";
                cin >> newDoctor.username;
                cout << "Enter the password for the new doctor: ";
                cin >> newDoctor.password;
                cout << "Enter the state for the new doctor: ";
                cin >> newDoctor.state;
                cout << "Enter the phone number for the new doctor: ";
                cin >> newDoctor.phoneNumber;
                doctors.push_back(newDoctor);
                clearScreen();
                cout << "New doctor added successfully." << endl;
            }
            else if (doctorOperation == 2) {
                // Remove an existing doctor
                cout << endl << "           Remove Doctor Account             " << endl;
                cout << "*********************************************" << endl;
                string usernameToRemove;
                cout << "Enter the username of the doctor to remove: ";
                cin >> usernameToRemove;

                // Find and remove the doctor with the specified username
                auto doctorToRemove = remove_if(doctors.begin(), doctors.end(), [usernameToRemove](const Doctor& doc) {
                    return doc.username == usernameToRemove;
                    });
                if (doctorToRemove != doctors.end()) {
                    doctors.erase(doctorToRemove, doctors.end());
                    clearScreen();
                    cout << "Doctor removed successfully." << endl;
                }
                else {
                    clearScreen();
                    cout << "Doctor not found. Please check the username." << endl;
                }
            }
            else {
                clearScreen();
                cout << "Invalid choice for managing doctor accounts." << endl;
            }
            break;
        case 2:
            int userOperation;
            cout << "Manage User Accounts:" << endl;
            cout << "1. Add a New User" << endl;
            cout << "2. Remove an Existing User" << endl;
            cout << "Enter your choice: ";
            cin >> userOperation;
            clearScreen();

            if (userOperation == 1) {
                // Add a new user
                User newUser;
                cout << endl << "           Add New User Account            " << endl;
                cout << "*********************************************" << endl;
                std::cout << "Enter the username for the new user: ";
                std::cin >> newUser.username;
                cout << "Enter the password for the new user: ";
                cin >> newUser.password;
                std::cout << "Enter the state for the new user: ";
                std::cin >> newUser.state;
                std::cout << "Enter the phone number for the new user: ";
                std::cin >> newUser.phoneNumber;
                users.push_back(newUser);
                clearScreen();
                std::cout << "New user added successfully." << std::endl;
            }
            else if (userOperation == 2) {
                // Remove an existing user
                std::string usernameToRemove;
                cout << endl << "             Remove User Account             " << endl;
                cout << "*********************************************" << endl;
                std::cout << "Enter the username of the user to remove: ";
                std::cin >> usernameToRemove;

                // Find and remove the user with the specified username
                auto userToRemove = std::remove_if(users.begin(), users.end(), [usernameToRemove](const User& user) {
                    return user.username == usernameToRemove;
                    });
                if (userToRemove != users.end()) {
                    users.erase(userToRemove, users.end());
                    clearScreen();
                    std::cout << "User removed successfully." << std::endl;
                }
                else {
                    clearScreen();
                    std::cout << "User not found. Please check the username." << std::endl;
                }
            }
            else {
                clearScreen();
                std::cout << "Invalid choice for managing user accounts." << std::endl;
            }
            break;
        case 3:
            std::cout << "Enter the username of the user to send an alert to: ";
            std::cin >> userUsername;
            std::cout << "Enter the state of the user: ";
            std::cin >> userState;
            userToAlert = userLoginPointer(userUsername, userState);
            clearScreen();

            if (userToAlert) {
                sendDengueAlert(*userToAlert, "Dengue alert message for testing.");
            }
            else {
                //clearScreen();
                std::cout << "User not found. Please check the username and state." << std::endl;
            }
            break;
        case 4:
            clearScreen();
            viewWeeklyDengueCases(weeklyDengueData);
            break;

        case 5:
            clearScreen();
            cout << endl << "Total dengue cases reported in Malaysia between 2018 - 2023 (Bar Chart)" << endl;
            cout << "-----------------------------------------------------------------------" << endl << endl;
            viewTotalDengueCasesBarChart(annualData);
            cout << endl;

            break;

        case 6:
            clearScreen();
            cout << "Exiting admin menu." << endl;
            return;
        default:
            clearScreen();
            cout << "Invalid choice. Please try again." << endl;
        }
    }
}