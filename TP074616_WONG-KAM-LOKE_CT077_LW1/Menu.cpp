#include "Menu.h"
#include "Records.h"
#include "Search.h"
#include "Sort.h"
#include "Display.h"
#include "Benchmark.h"
#include "Timer.h"
#include <iostream>
using namespace std;

void runMenu(StudentArray& sa) {
    Timer timer;
    int   choice;

    do {
        cout << "\n================================================\n";
        cout << "  STUDENT RECORD SYSTEM  |  IntroSort O(nlogn)\n";
        cout << "================================================\n";
        cout << "  1.  Display all records\n";
        cout << "  2.  Add a record\n";
        cout << "  3.  Delete a record\n";
        cout << "  4.  Search by Student ID  (Linear  O(n))\n";
        cout << "  5.  Search by Name        (Linear  O(n))\n";
        cout << "  6.  Sort by CGPA Ascending  (IntroSort O(n log n))\n";
        cout << "  7.  Sort by CGPA Descending (IntroSort O(n log n))\n";
        cout << "  8.  Binary Search by CGPA (O(log n) — sort first!)\n";
        cout << "  9.  Load a different dataset\n";
        cout << "  10. Run full benchmark (all 4 datasets)\n";
        cout << "  0.  Exit\n";
        cout << "  Choice: ";
        cin >> choice;
        cin.ignore();
        if (choice == 1) {
            int rows;
            cout << "  Max rows to display (0 = all): ";
            cin >> rows; cin.ignore();
            timer.start();
            display(sa, rows == 0 ? sa.size : rows);
            timer.printElapsed("Display");
        }
        else if (choice == 2) {
            Student s;
            cout << "  Student ID    : "; getline(cin, s.studentID);
            cout << "  Full Name     : "; getline(cin, s.fullName);
            cout << "  Programme     : "; getline(cin, s.programmeCode);
            cout << "  Year of Study : "; cin >> s.yearOfStudy; 
            cin.ignore();
            cout << "  CGPA (0-4)    : "; cin >> s.cgpa;
            cin.ignore();
            cout << "  Contact No.   : "; getline(cin, s.contactNumber);
            timer.start();
            bool ok = addRecord(sa, s);
            timer.printElapsed("Add");
            if (ok) cout << "  Record added. Total records: " << sa.size << "\n";
        }
        else if (choice == 3) {
            string id;
            cout << "  Enter Student ID to delete: "; getline(cin, id);
            timer.start();
            bool ok = deleteRecord(sa, id);
            timer.printElapsed("Delete");
            if (ok) cout << "  Record deleted. Total records: " << sa.size << "\n";
            else    cout << "  Student ID not found.\n";
        }
        else if (choice == 4) {
            string id;
            cout << "  Enter Student ID: "; getline(cin, id);
            timer.start();
            int idx = linearSearchByID(sa, id);
            timer.printElapsed("Linear Search by ID");
            if (idx == -1) cout << "  Not found.\n";
            else printOne(sa.data[idx]);

        }
        else if (choice == 5) {
            string name;
            cout << "  Enter Full Name (or partial): "; getline(cin, name);
            timer.start();
            int idx = linearSearchByName(sa, name);
            timer.printElapsed("Linear Search by Name");
            if (idx == -1) cout << "  Not found.\n";
            else printOne(sa.data[idx]);
        }
        else if (choice == 6) {
            timer.start();
            introsort(sa);
            timer.printElapsed("IntroSort Ascending");
            cout << "  Sorted ascending by CGPA.\n";
            display(sa, 10);
        }
        else if (choice == 7) {
            timer.start();
            introsort(sa);
            reverseArray(sa);
            timer.printElapsed("IntroSort Descending");
            cout << "  Sorted descending by CGPA.\n";
            display(sa, 10);
        }
        else if (choice == 8) {
            double cgpa;
            cout << "  Enter CGPA to search (array must be sorted): ";
            cin >> cgpa; cin.ignore();
            timer.start();
            int idx = binarySearchByCGPA(sa, cgpa);
            timer.printElapsed("Binary Search by CGPA");
            if (idx == -1)
                cout << "  No record with CGPA = " << cgpa << " found.\n";
            else
                printOne(sa.data[idx]);
        }
        else if (choice == 9) {
            string fname;
			cout << " Options:\n";
            cout << " \t students_500.csv\n ";
			cout << " \t students_2000.csv\n ";
			cout << " \t students_8000.csv\n ";
			cout << " \t students_30000.csv\n";
            cout << " Enter filename:";
            getline(cin, fname);
            timer.start();
            bool ok = loadCSV(fname, sa);
            timer.printElapsed("Load CSV");
            if (ok) cout << "  Loaded " << sa.size << " records.\n";
        }
        else if (choice == 10) {
            runAllBenchmarks();

        }
        else if (choice != 0) {
            cout << "  Invalid choice. Please try again.\n";
        }

    } while (choice != 0);

    cout << "  Goodbye!\n";
}
