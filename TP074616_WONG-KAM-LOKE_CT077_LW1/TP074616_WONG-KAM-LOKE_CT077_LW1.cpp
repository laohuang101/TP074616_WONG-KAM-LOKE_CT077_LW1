#include <algorithm>
#include <chrono>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;
using namespace chrono;

// =============================================================
//  DATA STRUCTURES
// =============================================================

struct Student {
    string studentID;
    string fullName;
    string programmeCode;
    int    yearOfStudy;
    double cgpa;
    string contactNumber;
};

struct StudentArray {
    Student* data;
    int      size;
    int      capacity;

    StudentArray() : data(nullptr), size(0), capacity(0) {}
    ~StudentArray() { delete[] data; }

    void reserve(int newCap) {
        Student* tmp = new Student[newCap];
        for (int i = 0; i < size; i++) tmp[i] = data[i];
        delete[] data;
        data = tmp;
        capacity = newCap;
    }

    void push_back(const Student& s) {
        if (size == capacity)
            reserve(capacity == 0 ? 16 : capacity * 2);
        data[size++] = s;
    }

    void removeAt(int idx) {
        for (int i = idx; i < size - 1; i++) data[i] = data[i + 1];
        size--;
    }

    void clear() { size = 0; }
};

// =============================================================
//  INTROSORT  (QuickSort + HeapSort + InsertionSort)
// =============================================================

static const int THRESHOLD = 16;

void insertionSort(Student* arr, int lo, int hi) {
    for (int i = lo + 1; i <= hi; i++) {
        Student key = arr[i];
        int j = i - 1;
        while (j >= lo && arr[j].cgpa > key.cgpa) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void siftDown(Student* arr, int root, int end) {
    while (true) {
        int largest = root;
        int left = 2 * root + 1;
        int right = 2 * root + 2;
        if (left <= end && arr[left].cgpa > arr[largest].cgpa) largest = left;
        if (right <= end && arr[right].cgpa > arr[largest].cgpa) largest = right;
        if (largest == root) break;
        swap(arr[root], arr[largest]);
        root = largest;
    }
}

void heapSort(Student* arr, int lo, int hi) {
    int      n = hi - lo + 1;
    Student* sub = arr + lo;
    for (int i = n / 2 - 1; i >= 0; i--) siftDown(sub, i, n - 1);
    for (int i = n - 1; i > 0; i--) {
        swap(sub[0], sub[i]);
        siftDown(sub, 0, i - 1);
    }
}

int medianOfThree(Student* arr, int lo, int hi) {
    int mid = lo + (hi - lo) / 2;
    if (arr[lo].cgpa > arr[mid].cgpa) swap(arr[lo], arr[mid]);
    if (arr[lo].cgpa > arr[hi].cgpa)  swap(arr[lo], arr[hi]);
    if (arr[mid].cgpa > arr[hi].cgpa)  swap(arr[mid], arr[hi]);
    swap(arr[mid], arr[hi - 1]);
    return hi - 1;
}

int partition(Student* arr, int lo, int hi) {
    int    pivotIdx = medianOfThree(arr, lo, hi);
    double pivot = arr[pivotIdx].cgpa;
    int i = lo, j = hi - 1;
    while (true) {
        while (arr[++i].cgpa < pivot) {}
        while (arr[--j].cgpa > pivot) {}
        if (i >= j) break;
        swap(arr[i], arr[j]);
    }
    swap(arr[i], arr[hi - 1]);
    return i;
}

void introsortUtil(Student* arr, int lo, int hi, int depthLimit) {
    int sz = hi - lo + 1;
    if (sz <= 1) return;
    if (sz <= THRESHOLD) { insertionSort(arr, lo, hi); return; }
    if (depthLimit == 0) { heapSort(arr, lo, hi); return; }
    if (hi - lo < 2) {
        if (arr[lo].cgpa > arr[hi].cgpa) swap(arr[lo], arr[hi]);
        return;
    }
    int p = partition(arr, lo, hi);
    introsortUtil(arr, lo, p - 1, depthLimit - 1);
    introsortUtil(arr, p + 1, hi, depthLimit - 1);
}

void introsort(StudentArray& sa) {
    if (sa.size <= 1) return;
    int depthLimit = static_cast<int>(2.0 * log2(sa.size));
    introsortUtil(sa.data, 0, sa.size - 1, depthLimit);
}

void reverseArray(StudentArray& sa) {
    for (int i = 0, j = sa.size - 1; i < j; i++, j--)
        swap(sa.data[i], sa.data[j]);
}

// =============================================================
//  FILE I/O
// =============================================================

bool loadCSV(const string& filename, StudentArray& sa) {
    ifstream fin(filename);
    if (!fin.is_open()) {
        cerr << "[ERROR] Cannot open: " << filename << endl;
        return false;
    }
    sa.clear();
    string line;
    getline(fin, line);
    while (getline(fin, line)) {
        if (line.empty()) continue;
        istringstream ss(line);
        Student s;
        string  tmp;
        getline(ss, s.studentID, ',');
        getline(ss, s.fullName, ',');
        getline(ss, s.programmeCode, ',');
        getline(ss, tmp, ','); s.yearOfStudy = stoi(tmp);
        getline(ss, tmp, ','); s.cgpa = stod(tmp);
        getline(ss, s.contactNumber, ',');
        sa.push_back(s);
    }
    fin.close();
    return true;
}

// =============================================================
//  DISPLAY
// =============================================================

void display(const StudentArray& sa, int maxRows = 10) {
    cout << "\n+------------+----------------------------------+-------+------+------+-----------------+\n";
    cout << "| StudentID  | Full Name                        | Prog  | Year | CGPA | Contact        |\n";
    cout << "+------------+----------------------------------+-------+------+------+-----------------+\n";
    for (int i = 0; i < min(sa.size, maxRows); i++) {
        const Student& s = sa.data[i];
        cout << "| " << s.studentID;
        for (int p = (int)s.studentID.size(); p < 10; p++) cout << ' ';
        cout << " | ";
        string name = s.fullName.size() > 32 ? s.fullName.substr(0, 32) : s.fullName;
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

// =============================================================
//  SEARCH
// =============================================================

int linearSearchByID(const StudentArray& sa, const string& id) {
    for (int i = 0; i < sa.size; i++)
        if (sa.data[i].studentID == id) return i;
    return -1;
}

int linearSearchByName(const StudentArray& sa, const string& name) {
    for (int i = 0; i < sa.size; i++)
        if (sa.data[i].fullName == name) return i;
    string nameLower = name;
    for (char& c : nameLower) c = (char)tolower(c);
    for (int i = 0; i < sa.size; i++) {
        string fn = sa.data[i].fullName;
        for (char& c : fn) c = (char)tolower(c);
        if (fn.find(nameLower) != string::npos) return i;
    }
    return -1;
}

int binarySearchByCGPA(const StudentArray& sa, double cgpa) {
    int lo = 0, hi = sa.size - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (sa.data[mid].cgpa < cgpa) lo = mid + 1;
        else if (sa.data[mid].cgpa > cgpa) hi = mid - 1;
        else                               return mid;
    }
    return -1;
}

// =============================================================
//  ADD / DELETE
// =============================================================

void addRecord(StudentArray& sa, const Student& s) { sa.push_back(s); }

bool deleteRecord(StudentArray& sa, const string& id) {
    int idx = linearSearchByID(sa, id);
    if (idx == -1) return false;
    sa.removeAt(idx);
    return true;
}

// =============================================================
//  BENCHMARK
// =============================================================

struct Timer {
    time_point<high_resolution_clock> t0;
    void      start() { t0 = high_resolution_clock::now(); }
    long long microseconds() {
        return duration_cast<chrono::microseconds>(
            high_resolution_clock::now() - t0).count();
    }
};

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
    cout << "  [T1] Load          : " << loadTime << " us   (n=" << sa.size << ")\n";

    timer.start();
    volatile double dummy = 0;
    for (int i = 0; i < sa.size; i++) dummy += sa.data[i].cgpa;
    (void)dummy;
    long long traverseTime = timer.microseconds();
    cout << "  [T2] Traverse      : " << traverseTime << " us\n";

    timer.start();
    for (int i = 0; i < 10; i++) {
        Student s;
        s.studentID = "TP99999" + to_string(i);
        s.fullName = "Test Student " + to_string(i);
        s.programmeCode = "CT101";
        s.yearOfStudy = 1;
        s.cgpa = 2.50 + i * 0.05;
        s.contactNumber = "011-0000000";
        addRecord(sa, s);
    }
    long long addTime = timer.microseconds() / 10;
    cout << "  [T3] Add (avg/10)  : " << addTime << " us\n";

    string id1 = sa.data[0].studentID;
    string id2 = sa.data[sa.size / 2].studentID;
    string id3 = sa.data[sa.size - 1].studentID;
    timer.start();
    linearSearchByID(sa, id1);
    linearSearchByID(sa, id2);
    linearSearchByID(sa, id3);
    linearSearchByID(sa, "TP000001");
    long long lsTime = timer.microseconds() / 4;
    cout << "  [T4] Linear Search : " << lsTime << " us  (avg of 4)\n";

    timer.start();
    introsort(sa);
    long long sortTime = timer.microseconds();
    cout << "  [T5] INTROSORT     : " << sortTime << " us  <- KEY METRIC\n";

    bool sorted = true;
    for (int i = 1; i < sa.size; i++)
        if (sa.data[i].cgpa < sa.data[i - 1].cgpa) { sorted = false; break; }
    cout << "       Sort correct  : " << (sorted ? "YES" : "NO") << "\n";
    cout << "       CGPA range    : " << sa.data[0].cgpa << " to " << sa.data[sa.size - 1].cgpa << "\n";

    double cgpa1 = sa.data[0].cgpa;
    double cgpa2 = sa.data[sa.size / 2].cgpa;
    double cgpa3 = sa.data[sa.size - 1].cgpa;
    timer.start();
    binarySearchByCGPA(sa, cgpa1);
    binarySearchByCGPA(sa, cgpa2);
    binarySearchByCGPA(sa, cgpa3);
    long long bsTime = timer.microseconds() / 3;
    cout << "  [T6] Binary Search : " << bsTime << " us  (avg of 3)\n";

    timer.start();
    for (int i = 0; i < 10 && sa.size > 0; i++) {
        string delID = sa.data[sa.size / 2].studentID;
        deleteRecord(sa, delID);
    }
    long long delTime = timer.microseconds() / 10;
    cout << "  [T7] Delete(avg/10): " << delTime << " us\n";

    cout << "\n  +------------------+---------------------------------+\n";
    cout << "  | Operation        | n = " << n;
    for (int p = (int)to_string(n).size(); p < 6; p++) cout << ' ';
    cout << "                        |\n";
    cout << "  +------------------+---------------------------------+\n";
    cout << "  | Load             | " << loadTime << " us\n";
    cout << "  | Traverse         | " << traverseTime << " us\n";
    cout << "  | Add (avg)        | " << addTime << " us\n";
    cout << "  | Linear Search    | " << lsTime << " us\n";
    cout << "  | INTROSORT (CGPA) | " << sortTime << " us   <- O(n log n)\n";
    cout << "  | Binary Search    | " << bsTime << " us   <- O(log n)\n";
    cout << "  | Delete (avg)     | " << delTime << " us\n";
    cout << "  +------------------+---------------------------------+\n";
}

// =============================================================
//  HELPER
// =============================================================

void printOne(const Student& s) {
    StudentArray tmp;
    tmp.push_back(s);
    display(tmp, 1);
}

// =============================================================
//  INTERACTIVE MENU
// =============================================================

void runMenu(StudentArray& sa) {
    int choice;
    do {
        cout << "\n================================================\n";
        cout << "  STUDENT RECORD SYSTEM  |  IntroSort O(nlogn)\n";
        cout << "================================================\n";
        cout << "  1. Display all records\n";
        cout << "  2. Add a record\n";
        cout << "  3. Delete a record\n";
        cout << "  4. Search by Student ID\n";
        cout << "  5. Search by Name\n";
        cout << "  6. Sort by CGPA (ascending)\n";
        cout << "  7. Sort by CGPA (descending)\n";
        cout << "  8. Run benchmark (all 4 datasets)\n";
        cout << "  0. Exit\n";
        cout << "  Choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            int rows;
            cout << "  Max rows to display (0 = all): ";
            cin >> rows; cin.ignore();
            display(sa, rows == 0 ? sa.size : rows);

        }
        else if (choice == 2) {
            Student s;
            cout << "  Student ID   : "; getline(cin, s.studentID);
            cout << "  Full Name    : "; getline(cin, s.fullName);
            cout << "  Programme    : "; getline(cin, s.programmeCode);
            cout << "  Year of Study: "; cin >> s.yearOfStudy; cin.ignore();
            cout << "  CGPA         : "; cin >> s.cgpa;        cin.ignore();
            cout << "  Contact No.  : "; getline(cin, s.contactNumber);
            addRecord(sa, s);
            cout << "  Record added. Total records: " << sa.size << "\n";

        }
        else if (choice == 3) {
            string id;
            cout << "  Enter Student ID to delete: "; getline(cin, id);
            if (deleteRecord(sa, id))
                cout << "  Record deleted. Total records: " << sa.size << "\n";
            else
                cout << "  Student ID not found.\n";

        }
        else if (choice == 4) {
            string id;
            cout << "  Enter Student ID: "; getline(cin, id);
            int idx = linearSearchByID(sa, id);
            if (idx == -1) cout << "  Not found.\n";
            else           printOne(sa.data[idx]);

        }
        else if (choice == 5) {
            string name;
            cout << "  Enter Full Name (or partial): "; getline(cin, name);
            int idx = linearSearchByName(sa, name);
            if (idx == -1) cout << "  Not found.\n";
            else           printOne(sa.data[idx]);

        }
        else if (choice == 6) {
            introsort(sa);
            cout << "  Sorted ascending by CGPA.\n";
            display(sa, 10);

        }
        else if (choice == 7) {
            introsort(sa);
            reverseArray(sa);
            cout << "  Sorted descending by CGPA.\n";
            display(sa, 10);

        }
        else if (choice == 8) {
            benchmark("students_500.csv", 500);
            benchmark("students_2000.csv", 2000);
            benchmark("students_8000.csv", 8000);
            benchmark("students_30000.csv", 30000);
            cout << "\n----------------------------------------------------\n";
            cout << "  BIG-O GROWTH RATIO ANALYSIS\n";
            cout << "----------------------------------------------------\n";
            cout << "  n: 500 -> 2000 -> 8000 -> 30000 (quadrupling each step)\n";
            cout << "  O(n log n) IntroSort grows ~4.9x per step\n";
            cout << "  (NOT 16x like O(n^2) Bubble Sort)\n\n";
            cout << "  Algorithm selection:\n";
            cout << "    Sub-array <= 16 elements  ->  InsertionSort\n";
            cout << "    Depth limit exceeded      ->  HeapSort\n";
            cout << "    Otherwise                 ->  QuickSort (median-of-3)\n";

        }
        else if (choice != 0) {
            cout << "  Invalid choice.\n";
        }

    } while (choice != 0);

    cout << "  Goodbye!\n";
}

// =============================================================
//  MAIN
// =============================================================

int main() {
    cout << "================================================\n";
    cout << "  ARRAY INTROSORT - Student Record System\n";
    cout << "  Algorithm: IntroSort (Quick+Heap+Insertion)\n";
    cout << "  Sort Complexity: O(n log n)\n";
    cout << "================================================\n";

    StudentArray sa;
    cout << "\n  Loading students_500.csv...\n";
    if (!loadCSV("students_500.csv", sa)) {
        cout << "  [WARN] Could not load default dataset.\n";
        cout << "         Place CSV files in the project folder.\n";
    }
    else {
        cout << "  Loaded " << sa.size << " records.\n";
    }

    runMenu(sa);
    return 0;
}