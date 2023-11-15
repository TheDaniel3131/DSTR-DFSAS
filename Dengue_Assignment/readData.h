#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

using namespace std;

struct DengueData {
    int year;
    map<std::string, vector<int>> stateData; // State -> Cases by week
};

// Function to read and parse CSV data from a file
bool readCSV(const string& filename, vector<std::string>& header, vector<vector<string>>& rows) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << filename << endl;
        return false;
    }

    // Read the header
    string line;
    if (getline(file, line)) {
        istringstream ss(line);
        string cell;
        while (getline(ss, cell, ',')) { // Use tab character as delimiter
            header.push_back(cell);
        }
    }

    // Read the data rows
    while (getline(file, line)) {
        istringstream ss(line);
        vector<std::string> row;
        string cell;
        while (getline(ss, cell, ',')) { // Use tab character as delimiter
            row.push_back(cell);
        }
        rows.push_back(row);
    }

    return true;
}

// Function to view total dengue cases for a specific year and state
void viewTotalDengueCases(const map<int, DengueData>& annualData, int year, const string& state) {
    auto it = annualData.find(year);
    if (it != annualData.end()) {
        const DengueData& data = it->second;
        auto stateIt = data.stateData.find(state);
        if (stateIt != data.stateData.end()) {
            const vector<int>& cases = stateIt->second;
            int totalCases = 0;
            for (int casesInWeek : cases) {
                totalCases += casesInWeek;
            }
            cout << "Year: " << year << ", State: " << state << ", Total Cases: " << totalCases << endl;
        }
        else {
            cout << "State not found for the given year." << endl;
        }
    }
    else {
        cout << "Year not found in the data." << endl;
    }
}


// Function to parse and store weekly dengue data
void parseWeeklyDengueData(const std::vector<std::vector<std::string>>& weeklyDengueData, std::map<int, DengueData>& annualData, std::vector<std::string>& header) {
    // Assume the first column represents the year, the second column represents the week number, and the rest represent states
    for (const std::vector<std::string>& row : weeklyDengueData) {
        if (row.size() < 3) {
            std::cerr << "Invalid data format in weekly dengue cases data." << std::endl;
            continue;
        }

        int year, week;
        try {
            year = std::stoi(row[0]);
            week = std::stoi(row[1]);
        }
        catch (const std::invalid_argument& e) {
            std::cerr << "Invalid data format for year or week." << std::endl;
            continue;
        }

        if (year < 2018 || year > 2023) {
            std::cerr << "Invalid year in data: " << year << std::endl;
            continue;
        }

        DengueData& data = annualData[year];
        data.year = year;

        for (size_t i = 2; i < row.size(); i++) {
            int casesInWeek;
            try {
                casesInWeek = std::stoi(row[i]);
            }
            catch (const std::invalid_argument& e) {
                std::cerr << "Invalid data format for cases in week " << week << " for year " << year << ": " << row[i] << std::endl;
                continue;
            }
            data.stateData[header[i]].push_back(casesInWeek);
        }
    }
}
