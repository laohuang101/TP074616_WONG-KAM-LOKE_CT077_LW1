#include "Search.h"
#include "Display.h"
#include <iostream>
using namespace std;

int linearSearchByID(const StudentArray& sa, const string& id) {
    for (int i = 0; i < sa.size; i++)
        if (sa.data[i].studentID == id) return i;
    return -1;
}

int linearSearchByName(const StudentArray& sa, const string& name) {
    for (int i = 0; i < sa.size; i++)
        if (sa.data[i].fullName == name) return i;

    string nameLower = name;
    for (int k = 0; k < (int)nameLower.size(); k++)
        nameLower[k] = (char)tolower(nameLower[k]);

    for (int i = 0; i < sa.size; i++) {
        string fn = sa.data[i].fullName;
        for (int k = 0; k < (int)fn.size(); k++) fn[k] = (char)tolower(fn[k]);
        if (fn.find(nameLower) != string::npos) return i;
    }
    return -1;
}

int binarySearchByCGPA(const StudentArray& sa, double cgpa) {
    const double epsilon = 1e-6; 
    int lo = 0, hi = sa.size - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (sa.data[mid].cgpa < cgpa - epsilon) lo = mid + 1;
        else if (sa.data[mid].cgpa > cgpa + epsilon) hi = mid - 1;
        else return mid;
    }
    return -1;
}

void searchAllByCGPA(const StudentArray& sa, double cgpa) {
    const double epsilon = 1e-6;
    StudentArray results;

    for (int i = 0; i < sa.size; i++) {
        if (sa.data[i].cgpa >= cgpa - epsilon && sa.data[i].cgpa <= cgpa + epsilon) {
            results.push_back(sa.data[i]);
        }
    }

    if (results.size == 0) {
        cout << "  No records with CGPA = " << cgpa << " found.\n";
    } else {
        cout << "  Found " << results.size << " record(s) with CGPA = " << cgpa << ":\n";
        display(results, results.size);
    }
}
