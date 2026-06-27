#include "Display.hpp"
#include <iostream>
using namespace std;

void display(const StudentArray& sa, int maxRows) {
    cout << "\n+------------+----------------------------------+-------+------+------+-----------------+\n";
    cout << "| StudentID  | Full Name                        | Prog  | Year | CGPA | Contact         |\n";
    cout << "+------------+----------------------------------+-------+------+------+-----------------+\n";

    int limit = myMin(sa.size, maxRows);
    for (int i = 0; i < limit; i++) {
        const Student& s = sa.data[i];

        cout << "| " << s.studentID;
        for (int p = (int)s.studentID.size(); p < 10; p++) cout << ' ';
        cout << " | ";

        string name = (int)s.fullName.size() > 32 ? s.fullName.substr(0, 32) : s.fullName;
        cout << name;
        for (int p = (int)name.size(); p < 32; p++) cout << ' ';
        cout << " | ";

        cout << s.programmeCode;
        for (int p = (int)s.programmeCode.size(); p < 5; p++) cout << ' ';
        cout << " |  " << s.yearOfStudy << "   | ";

        cout.precision(2);
        cout << fixed << s.cgpa << " | ";

        cout << s.contactNumber;
        for (int p = (int)s.contactNumber.size(); p < 15; p++) cout << ' ';
        cout << " |\n";
    }

    cout << "+------------+----------------------------------+-------+------+------+-----------------+\n";
    if (sa.size > maxRows)
        cout << "  ... and " << (sa.size - maxRows) << " more records.\n";
    cout << "  Total records: " << sa.size << "\n";
}


void printOne(const Student& s) {
    StudentArray tmp;
    tmp.push_back(s);
    display(tmp, 1);
}
