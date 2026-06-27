#include "Benchmark.hpp"
#include "StudentArray.hpp"
#include "Records.hpp"
#include "Search.hpp"
#include "Sort.hpp"
#include "Display.hpp"
#include "Timer.hpp"
#include <iostream>
using namespace std;

void benchmark(const string& filename, int n) {
    StudentArray sa;
    Timer        timer;

    cout << "\n----------------------------------------------------\n";
    cout << "  BENCHMARKING: " << filename << "  (n = " << n << ")\n";
    cout << "----------------------------------------------------\n";

    timer.start();
    bool ok = loadCSV(filename, sa);
    long long loadTime = timer.microseconds();
    if (!ok) return;
    cout << "  [T1] Load             : " << loadTime << " us"
        << "  (" << loadTime / 1000.0 << " ms)\n";

    timer.start();
    volatile double dummy = 0;
    for (int i = 0; i < sa.size; i++) dummy += sa.data[i].cgpa;
    (void)dummy;
    long long traverseTime = timer.microseconds();
    cout << "  [T2] Traverse/Display : " << traverseTime << " us"
        << "  (" << traverseTime / 1000.0 << " ms)\n";

    timer.start();
    for (int i = 0; i < 10; i++) {
        Student s;
        s.studentID = "TP00000" + to_string(i);
        s.fullName = "Bench Student " + to_string(i);
        s.programmeCode = "CT101";
        s.yearOfStudy = 1;
        s.cgpa = 2.50 + i * 0.05;
        s.contactNumber = "011-0000000";
        sa.push_back(s);
    }
    long long addTime = timer.microseconds() / 10;
    cout << "  [T3] Add (avg/10)     : " << addTime << " us"
        << "  (" << addTime / 1000.0 << " ms)\n";

    string id1 = sa.data[0].studentID;
    string id2 = sa.data[sa.size / 2].studentID;
    string id3 = sa.data[sa.size - 1].studentID;
    timer.start();
    linearSearchByID(sa, id1);
    linearSearchByID(sa, id2);
    linearSearchByID(sa, id3);
    linearSearchByID(sa, "TP999999"); 
    long long lsTime = timer.microseconds() / 4;
    cout << "  [T4] Linear Search    : " << lsTime << " us"
        << "  (" << lsTime / 1000.0 << " ms)  avg of 4\n";

    timer.start();
    introsort(sa);
    long long sortTime = timer.microseconds();
    bool sorted = true;
    for (int i = 1; i < sa.size; i++)
        if (sa.data[i].cgpa < sa.data[i - 1].cgpa) { sorted = false; break; }
    cout << "  [T5] INTROSORT        : " << sortTime << " us"
        << "  (" << sortTime / 1000.0 << " ms)  <- KEY METRIC\n";
    cout << "       Sort correct     : " << (sorted ? "YES" : "NO") << "\n";
    cout << "       CGPA range       : " << sa.data[0].cgpa
        << " to " << sa.data[sa.size - 1].cgpa << "\n";

    double c1 = sa.data[0].cgpa;
    double c2 = sa.data[sa.size / 2].cgpa;
    double c3 = sa.data[sa.size - 1].cgpa;
    timer.start();
    binarySearchByCGPA(sa, c1);
    binarySearchByCGPA(sa, c2);
    binarySearchByCGPA(sa, c3);
    long long bsTime = timer.microseconds() / 3;
    cout << "  [T6] Binary Search    : " << bsTime << " us"
        << "  (" << bsTime / 1000.0 << " ms)  avg of 3\n";

    timer.start();
    for (int i = 0; i < 10 && sa.size > 0; i++) {
        string delID = sa.data[sa.size / 2].studentID;
        deleteRecord(sa, delID);
    }
    long long delTime = timer.microseconds() / 10;
    cout << "  [T7] Delete (avg/10)  : " << delTime << " us"
        << "  (" << delTime / 1000.0 << " ms)\n";

    cout << "\n  +--------------------+---------------+----------+-----------+\n";
    cout << "  | Operation          |     us        |    ms    |     s     |\n";
    cout << "  +--------------------+---------------+----------+-----------+\n";

    auto row = [](const string& op, long long us) {
        cout << "  | " << op;
        for (int p = (int)op.size(); p < 18; p++) cout << ' ';
        cout << " | ";
        cout.width(9); cout << us << " us  | ";
        cout.width(7); cout.precision(3); cout << fixed << us / 1000.0 << " ms | ";
        cout.width(9); cout.precision(6); cout << fixed << us / 1000000.0 << " s |\n";
        };

    row("Load", loadTime);
    row("Traverse/Display", traverseTime);
    row("Add (avg)", addTime);
    row("Linear Search", lsTime);
    row("INTROSORT", sortTime);
    row("Binary Search", bsTime);
    row("Delete (avg)", delTime);
    cout << "  +--------------------+---------------+----------+-----------+\n";
}


void runAllBenchmarks() {
    benchmark("students_500.csv", 500);
    benchmark("students_2000.csv", 2000);
    benchmark("students_8000.csv", 8000);
    benchmark("students_30000.csv", 30000);

    cout << "\n----------------------------------------------------\n";
    cout << "  BIG-O GROWTH RATIO ANALYSIS\n";
    cout << "----------------------------------------------------\n";
    cout << "  n: 500 -> 2000 -> 8000 -> 30000 (quadrupling each step)\n\n";
    cout << "  Expected growth per 4x increase in n:\n";
    cout << "    O(1)      : ~1x   (constant)\n";
    cout << "    O(log n)  : ~1.1x (binary search)\n";
    cout << "    O(n)      : ~4x   (linear search, display)\n";
    cout << "    O(n log n): ~4.9x (IntroSort) <- confirm your sort times\n";
    cout << "    O(n^2)    : ~16x  (bubble sort, selection sort)\n\n";
    cout << "  Algorithm selection in IntroSort:\n";
    cout << "    Sub-array <= 16 elements  ->  InsertionSort  (cache-friendly)\n";
    cout << "    Depth limit exceeded      ->  HeapSort       (O(n log n) guarantee)\n";
    cout << "    Otherwise                 ->  QuickSort      (median-of-3 pivot)\n";
}
