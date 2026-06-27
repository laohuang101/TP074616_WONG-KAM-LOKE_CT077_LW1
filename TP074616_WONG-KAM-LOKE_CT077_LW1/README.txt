Algorithm: IntroSort (QuickSort + HeapSort + InsertionSort)

HOW TO COMPILE:

Open the solution file in Visual Studio 2022:
  TP074616_WONG-KAM-LOKE_CT077_LW1.slnx

Set the build configuration to Release (recommended for accurate benchmarking).
Press Ctrl+Shift+B to build, or go to Build > Build Solution.

HOW TO RUN:

Ensure all CSV dataset files are in the same directory as the compiled executable:
  students_500.csv
  students_2000.csv
  students_8000.csv
  students_30000.csv

Run the executable (it will auto run if compilation done in visual studio):
  StudentSystem.exe

The program loads students_500.csv by default on startup.
Use the interactive menu to switch datasets, perform searches, sort, or run benchmarks.

MENU OPTIONS
------------
1.  Display all records
2.  Add a record
3.  Delete a record
4.  Search by Student ID   (Linear Search, O(n))
5.  Search by Name         (Linear Search, O(n))
6.  Sort by CGPA Ascending  (IntroSort, O(n log n))
7.  Sort by CGPA Descending (IntroSort, O(n log n))
8.  Binary Search by CGPA
9.  Load a different dataset
10. Run full benchmark (all 4 datasets)
0.  Exit