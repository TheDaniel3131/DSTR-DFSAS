#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "dengueCase.h"
using namespace std;

struct Doctor {
    string username;
    string password;
    string state;
    string phoneNumber;
    // vector<DengueCase> reportedCases;
};

vector<Doctor> doctors;

// Define Node for Doctor linked list
struct DoctorNode {
    Doctor doctor;
    DoctorNode* next;

    DoctorNode(const Doctor& doc) : doctor(doc), next(nullptr) {}
};

// Linked List for Doctors
class DoctorList {
private:
    DoctorNode* head;

public:
    DoctorList() : head(nullptr) {}

    void addDoctor(const Doctor& doctor) {
        DoctorNode* newDoctor = new DoctorNode(doctor);
        if (head == nullptr) {
            head = newDoctor;
        }
        else {
            DoctorNode* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newDoctor;
        }
    }

    Doctor* findDoctor(const string& username, const string& state) {
        DoctorNode* temp = head;
        while (temp != nullptr) {
            if (temp->doctor.username == username && temp->doctor.state == state) {
                return &(temp->doctor);
            }
            temp = temp->next;
        }
        return nullptr;
    }

    ~DoctorList() {
        while (head != nullptr) {
            DoctorNode* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

Doctor* doctorLogin(const string& username, const string& password) {
    for (Doctor& doctor : doctors) {
        if (doctor.username == username && doctor.password == password) {
            return &doctor;
        }
    }
    return nullptr;
}

void manageDoctorPersonalInfo(Doctor& doctor) {
    cout << "      Manage Personal Information      " << endl;
    cout << "---------------------------------------" << endl;
    cout << "Doctor Name: " << doctor.username << endl;
    cout << "Current State of Residence: " << doctor.state << endl;
    cout << "Phone Number: " << doctor.phoneNumber << endl << endl;

    // Allow the doctor to update their information
    cout << "Update Information (Y/N): ";
    char choice;
    cin >> choice;
    if (choice == 'Y' || choice == 'y') {
        cout << endl << "      Update Personal Information      " << endl;
        cout << "---------------------------------------" << endl;
        cout << "Enter New State of Residence: ";
        cin >> doctor.state;
        cout << "Enter New Phone Number: ";
        cin >> doctor.phoneNumber;
        clearScreen();
        cout << "Information updated successfully." << endl;
    }
}


void reportDengueCase(Doctor& doctor) {
    DengueCase newCase;
    newCase.doctorInfo = doctor.username;

    cout << "           Report Dengue Case          " << endl;
    cout << "---------------------------------------" << endl;
    cout << "Enter Patient Name: ";
    cin >> newCase.patientName;
    cout << "Enter Patient Age: ";
    cin >> newCase.age;
    cout << "Enter Date: ";
    cin >> newCase.date;
    cout << "Enter State: "; // Prompt for the state
    cin >> newCase.state;

    allReportedCases.push_back(newCase);
    clearScreen();
    cout << endl << "Dengue case reported successfully." << endl << endl;
}


void viewDoctorDengueCases(const Doctor& doctor) {
    cout << "            View Dengue Case           " << endl;
    cout << "---------------------------------------" << endl;
    cout << "Dengue Cases Reported by " << doctor.username << ":" << endl;
    for (const DengueCase& dengueCase : allReportedCases) {
        cout << "Patient Name: " << dengueCase.patientName << endl;
        cout << "Patient Age: " << dengueCase.age << endl;
        cout << "Date: " << dengueCase.date << endl;
        cout << "Doctor Information: " << dengueCase.doctorInfo << endl;
        cout << "---------------------------------------" << endl << endl;
    }
}