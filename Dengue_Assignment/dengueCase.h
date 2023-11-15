#pragma once
#include <string>
#include <vector>

using namespace std;

// Define structures for Dengue cases and Users
struct DengueCase {
    string patientName;
    int age;
    string date;
    string doctorInfo;
    string state;
};

// Extend denguecase.h file to make it global
extern vector<DengueCase> allReportedCases;