#ifndef STUDENT_H
#define STUDENT_H

#include <string>
using namespace std;

// =============================================================
//  Student struct — one record in the system
// =============================================================

struct Student {
    string studentID;
    string fullName;
    string programmeCode;
    int    yearOfStudy;
    double cgpa;
    string contactNumber;
};

#endif
