#ifndef SEARCH_H
#define SEARCH_H

#include "StudentArray.h"

int linearSearchByID  (const StudentArray& sa, const string& id);
int linearSearchByName(const StudentArray& sa, const string& name);
int binarySearchByCGPA(const StudentArray& sa, double cgpa);

#endif
