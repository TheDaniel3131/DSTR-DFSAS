#pragma once
#include <string>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <map>
#include "dengueCase.h"
#include "readData.h"

using namespace std;

struct User {
    string username;
    string password;
    string state;
    string phoneNumber;
    // vector<DengueCase> reportedCases;
    vector<std::string> alerts;
};

vector<User> users;

// Define Node for User linked list
struct UserNode {
    User user;
    UserNode* next;

    UserNode(const User& usr) : user(usr), next(nullptr) {}
};

// Linked List for Users
class UserList {
private:
    UserNode* head;

public:
    UserList() : head(nullptr) {}

    void addUser(const User& user) {
        UserNode* newUser = new UserNode(user);
        if (head == nullptr) {
            head = newUser;
        }
        else {
            UserNode* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newUser;
        }
    }

    User* findUser(const string& username, const string& state) {
        UserNode* temp = head;
        while (temp != nullptr) {
            if (temp->user.username == username && temp->user.state == state) {
                return &(temp->user);
            }
            temp = temp->next;
        }
        return nullptr;
    }

    ~UserList() {
        while (head != nullptr) {
            UserNode* temp = head;
            head = head->next;
            delete temp;
        }
    }
};


//void searchPastDengueFeverStatus(const User& user, const std::vector<DengueCase>& dengueCases);

// Function for user login
User* userLogin(const string& username, const string& password) {
    for (User& user : users) {
        if (user.username == username && user.password == password) {
            return &user;  // Return a pointer to the found user
        }
    }
    return nullptr;
}

User* userPointer = nullptr;

User* userLoginPointer(const string& username, const string& state) {
    for (User& user : users) {
        if (user.username == username && user.state == state) {
            return &user;
        }
    }
    return nullptr;
}

// Define a structure to hold state name and daily dengue cases
struct StateData {
    string stateName;
    int dailyCases;
};

// Compare function for sorting in descending order based on state name
bool compareStateData(const StateData& a, const StateData& b) {
    return a.stateName > b.stateName;
}

// Function to perform a simple bubble sort in descending order based on state name
void customSort(StateData arr[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (compareStateData(arr[j], arr[j + 1])) {
                // Swap if the compare function returns true
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}



// Function to view daily dengue cases for all states in descending order
void viewDailyDengueCases() {
    const int numStates = 15; // Update based on the actual number of states
    StateData states[numStates] = {
        {"JOHOR", 10},
        {"KEDAH", 15},
        {"KELANTAN", 5},
        {"MELAKA", 8},
        {"NEGERI SEMBILAN", 18},
        {"PAHANG", 4},
        {"PERAK", 2},
        {"PERLIS", 6},
        {"PULAU PINANG", 25},
        {"SABAH", 15},
        {"SARAWAK", 17},
        {"SELANGOR", 33},
        {"TERENGGANU", 9},
        {"WP KUALA LUMPUR", 35},
        {"WP LABUAN", 2}
        // Add data for other states
    };

    // Perform the custom sorting in descending order based on state name
    customSort(states, numStates);

    // Display the sorted daily dengue cases
    cout << "         View Daily Dengue Cases        " << endl; 
    cout << "****************************************" << endl;
    for (int i = 0; i < numStates; ++i) {
        cout << "*  " << setw(24) << left << states[i].stateName << "| " << setw(10) << states[i].dailyCases << "*" << endl;
    }
    cout << "****************************************" << endl << endl;
}


void manageUserPersonalInfo(User& user) {
    cout << "    Manage Personal Information    " << endl;
    cout << "-----------------------------------" << endl;
    cout << "Username: " << user.username << endl;
    cout << "Current State of Residence: " << user.state << endl;
    cout << "Phone Number: " << user.phoneNumber << endl;

    // Allow the user to update their information
    cout << "Update Information (Y/N): ";
    char choice;
    cin >> choice;
    if (choice == 'Y' || choice == 'y') {
        cout << "Enter New State of Residence: ";
        cin >> user.state;
        cout << "Enter New Phone Number: ";
        cin >> user.phoneNumber;
        cout << endl << "Information updated successfully." << endl;
    }
}


// Function to check and view dengue alerts for a user
void viewDengueAlert(const User& user) {
    // Check if the user has received a dengue alert
    if (!user.alerts.empty()) {
        cout << "Dengue Alert Messages for " << user.username << ":" << endl;
        for (const string& alert : user.alerts) {
            cout << alert << endl;
        }
    }
    else {
        cout << "No dengue alert messages for you." << endl;
    }
}

void searchPastDengueFeverStatus(const string &date)
{
    // Implement the functionality to search past dengue fever status based on user and cases
    // You can search the 'dengueCases' vector for cases related to the given user.
    // Example: Find and display the past dengue fever status for the user.
    cout << "Matching Dengue Cases for Date: " << date << endl;

    bool foundCases = false;
    for (const DengueCase &dengueCase : allReportedCases)
    {
        if (dengueCase.date == date)
        {
            // Display matching case details
            cout << "Patient Name: " << dengueCase.patientName << endl;
            cout << "Patient Age: " << dengueCase.age << endl;
            cout << "Date: " << dengueCase.date << endl;
            cout << "Doctor Information: " << dengueCase.doctorInfo << endl;
            cout << "---------------------------------------" << endl;
            foundCases = true;
        }
    }
    if (!foundCases)
    {
        cout << "No matching Dengue Cases found for Date: " << date << endl;
    }
    //std::cout << "Past Dengue Fever Status for User: " << user.username << std::endl;

    //bool foundCases = false;

    //for (const DengueCase& dengueCase : dengueCases) {
    //    if (dengueCase.patientName == user.username) {
    //        // Display details of past dengue fever cases reported by the user.
    //        std::cout << "Patient Name: " << dengueCase.patientName << std::endl;
    //        std::cout << "Patient Age: " << dengueCase.age << std::endl;
    //        std::cout << "Date: " << dengueCase.date << std::endl;
    //        std::cout << "State: " << dengueCase.state << std::endl;
    //        std::cout << "-------------------" << std::endl;
    //        foundCases = true;
    //    }
    //    if (!foundCases) {
    //        std::cout << "No past dengue fever cases found for the user." << std::endl;
    //    }
    //}
}
