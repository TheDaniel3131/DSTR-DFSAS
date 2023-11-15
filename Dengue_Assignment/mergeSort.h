#pragma once
#include <string>
#include <vector>

using namespace std;

// Function to perform merge operation
void merge(vector<vector<string>>& data, int left, int middle, int right) {
    int i, j, k;
    int n1 = middle - left + 1;
    int n2 = right - middle;

    // Create temporary arrays
    vector<vector<string>> L, R;
    L.resize(n1);
    R.resize(n2);

    // Copy data to temp arrays L[] and R[]
    for (i = 0; i < n1; i++)
        L[i] = data[left + i];
    for (j = 0; j < n2; j++)
        R[j] = data[middle + 1 + j];

    i = 0;
    j = 0;
    k = left;

    // Merge the temp arrays back into data[left..right]
    while (i < n1 && j < n2) {
        // Compare cases here based on your specific field containing the cases
        if (stoi(L[i][1]) <= stoi(R[j][1])) { // Assuming the case number is at index 1
            data[k] = L[i];
            i++;
        }
        else {
            data[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if there are any
    while (i < n1) {
        data[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if there are any
    while (j < n2) {
        data[k] = R[j];
        j++;
        k++;
    }
}

// Function to implement merge sort
void mergeSort(vector<vector<string>>& data, int left, int right) {
    if (left < right) {
        int middle = left + (right - left) / 2;

        // Sort first and second halves
        mergeSort(data, left, middle);
        mergeSort(data, middle + 1, right);

        // Merge the sorted halves
        merge(data, left, middle, right);
    }
}