#include "Sort.hpp"
#include <cmath>

static const int THRESHOLD = 16; 

static void insertionSort(Student* arr, int lo, int hi) {
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

static void siftDown(Student* arr, int root, int end) {
    while (true) {
        int largest = root;
        int left = 2 * root + 1;
        int right = 2 * root + 2;
        if (left <= end && arr[left].cgpa > arr[largest].cgpa) largest = left;
        if (right <= end && arr[right].cgpa > arr[largest].cgpa) largest = right;
        if (largest == root) break;
        swapStudents(arr[root], arr[largest]);
        root = largest;
    }
}

static void heapSort(Student* arr, int lo, int hi) {
    int      n = hi - lo + 1;
    Student* sub = arr + lo;
    for (int i = n / 2 - 1; i >= 0; i--) siftDown(sub, i, n - 1);
    for (int i = n - 1; i > 0; i--) {
        swapStudents(sub[0], sub[i]);
        siftDown(sub, 0, i - 1);
    }
}

static int medianOfThree(Student* arr, int lo, int hi) {
    int mid = lo + (hi - lo) / 2;
    if (arr[lo].cgpa > arr[mid].cgpa) swapStudents(arr[lo], arr[mid]);
    if (arr[lo].cgpa > arr[hi].cgpa)  swapStudents(arr[lo], arr[hi]);
    if (arr[mid].cgpa > arr[hi].cgpa)  swapStudents(arr[mid], arr[hi]);
    swapStudents(arr[mid], arr[hi - 1]);
    return hi - 1;
}

static int partitionArr(Student* arr, int lo, int hi) {
    int    pivotIdx = medianOfThree(arr, lo, hi);
    double pivot = arr[pivotIdx].cgpa;
    int i = lo, j = hi - 1;
    while (true) {
        while (arr[++i].cgpa < pivot) {}
        while (arr[--j].cgpa > pivot) {}
        if (i >= j) break;
        swapStudents(arr[i], arr[j]);
    }
    swapStudents(arr[i], arr[hi - 1]);
    return i;
}

static void introsortUtil(Student* arr, int lo, int hi, int depthLimit) {
    int sz = hi - lo + 1;
    if (sz <= 1)          return;
    if (sz <= THRESHOLD) { insertionSort(arr, lo, hi); return; }
    if (depthLimit == 0) { heapSort(arr, lo, hi);      return; }
    if (hi - lo < 2) {
        if (arr[lo].cgpa > arr[hi].cgpa) swapStudents(arr[lo], arr[hi]);
        return;
    }
    int p = partitionArr(arr, lo, hi);
    introsortUtil(arr, lo, p - 1, depthLimit - 1);
    introsortUtil(arr, p + 1, hi, depthLimit - 1);
}

void introsort(StudentArray& sa) {
    if (sa.size <= 1) return;
    int depthLimit = static_cast<int>(2.0 * log2((double)sa.size));
    introsortUtil(sa.data, 0, sa.size - 1, depthLimit);
}

void reverseArray(StudentArray& sa) {
    for (int i = 0, j = sa.size - 1; i < j; i++, j--)
        swapStudents(sa.data[i], sa.data[j]);
}
