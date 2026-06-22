#ifndef RECORDS_H
#define RECORDS_H

#include "StudentArray.h"

// =============================================================
//  Record operations — Add, Delete, Load from CSV
// =============================================================

bool loadCSV    (const string& filename, StudentArray& sa);
bool addRecord  (StudentArray& sa, const Student& s);
bool deleteRecord(StudentArray& sa, const string& id);
bool isDuplicateID(const StudentArray& sa, const string& id);

#endif
