#include "Records.h"
#include "Search.h"
#include <fstream>
#include <sstream>
#include <iostream>

bool loadCSV(const string& filename, StudentArray& sa) {
    ifstream fin(filename);
    if (!fin.is_open()) {
        cerr << "  [ERROR] Cannot open: " << filename << endl;
        return false;
    }
    sa.clear();
    string line;
    getline(fin, line);

    while (getline(fin, line)) {
        if (line.empty()) continue;

        istringstream ss(line);
        string f1, f2, f3, f4, f5, f6;

        if (!getline(ss, f1, ',')) continue;
        if (!getline(ss, f2, ',')) continue;
        if (!getline(ss, f3, ',')) continue;
        if (!getline(ss, f4, ',')) continue;
        if (!getline(ss, f5, ',')) continue;
        getline(ss, f6, ',');

        Student s;
        s.studentID = f1;
        s.fullName = f2;
        s.programmeCode = f3;

        try { s.yearOfStudy = stoi(f4); }
        catch (...) { continue; } 

        try { s.cgpa = stod(f5); }
        catch (...) { continue; }

        if (s.cgpa < 0.0 || s.cgpa > 4.0) continue

        s.contactNumber = f6;
        sa.push_back(s);
    }

    fin.close();
    return true;
}

bool isDuplicateID(const StudentArray& sa, const string& id) {
    return linearSearchByID(sa, id) != -1;
}

bool addRecord(StudentArray& sa, const Student& s) {
    if (isDuplicateID(sa, s.studentID)) {
        cout << "  [ERROR] Student ID " << s.studentID << " already exists.\n";
        return false;
    }
    if (s.cgpa < 0.0 || s.cgpa > 4.0) {
        cout << "  [ERROR] Invalid CGPA " << s.cgpa << " (must be 0.00 - 4.00).\n";
        return false;
    }
    sa.push_back(s);
    return true;
}

bool deleteRecord(StudentArray& sa, const string& id) {
    int idx = linearSearchByID(sa, id);
    if (idx == -1) return false;
    sa.removeAt(idx);
    return true;
}
