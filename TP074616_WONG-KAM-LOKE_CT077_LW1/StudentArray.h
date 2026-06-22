#ifndef STUDENTARRAY_H
#define STUDENTARRAY_H

#include "Student.h"

struct StudentArray {
    Student* data;
    int size;
    int capacity;

    StudentArray() : data(nullptr), size(0), capacity(0) {}
    ~StudentArray() { delete[] data; }

    void reserve(int newCap) {
        Student* tmp = new Student[newCap];
        for (int i = 0; i < size; i++) tmp[i] = data[i];
        delete[] data;
        data     = tmp;
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

inline void swapStudents(Student& a, Student& b) {
    Student tmp = a;
    a = b;
    b = tmp;
}

inline int myMin(int a, int b) { return a < b ? a : b; }

#endif
