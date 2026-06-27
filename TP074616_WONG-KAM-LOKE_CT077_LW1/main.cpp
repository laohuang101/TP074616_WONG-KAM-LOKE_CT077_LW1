#include "StudentArray.hpp"
#include "Records.hpp"
#include "Menu.hpp"
#include "Timer.hpp"
#include <iostream>
using namespace std;

int main() {
    cout << "================================================\n";
    cout << "  ARRAY INTROSORT - Student Record System\n";
    cout << "  Student  : WONG KAM LOKE  TP074616\n";
    cout << "  Algorithm: IntroSort (Quick + Heap + Insertion)\n";
    cout << "  Sort     : O(n log n)   Search: O(log n)\n";
    cout << "================================================\n";

    StudentArray sa;
    Timer        timer;

    cout << "\n  Loading students_500.csv...\n";
    timer.start();
    bool ok = loadCSV("students_500.csv", sa);
    timer.printElapsed("Load");

    if (!ok) {
        cout << "  [WARN] Could not load default dataset.\n";
        cout << "         Make sure CSV files are in the same folder as the .exe\n";
    } else {
        cout << "  Loaded " << sa.size << " records.\n";
    }

    runMenu(sa);
    return 0;
}
