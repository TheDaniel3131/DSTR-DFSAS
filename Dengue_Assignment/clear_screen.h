#pragma once
#include <cstdlib>

using namespace std;

void clearScreen() {
#ifdef _WIN32
    // For Windows
    system("cls");
#else
    // Assume POSIX (Linux, macOS)
    system("clear");
#endif
}