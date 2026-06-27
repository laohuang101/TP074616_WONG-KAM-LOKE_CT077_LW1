#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <iostream>
using namespace std;
using namespace chrono;


struct Timer {
    time_point<high_resolution_clock> t0;

    void start() { t0 = high_resolution_clock::now(); }

    long long microseconds() {
        return duration_cast<chrono::microseconds>(
            high_resolution_clock::now() - t0).count();
    }

    void printElapsed(const string& label) {
        long long us = microseconds();
        double    ms = us / 1000.0;
        double    s  = us / 1000000.0;
        cout << "  [Time] " << label << ": "
             << us << " us"
             << "  (" << ms << " ms"
             << " / " << s  << " s)\n";
    }
};

#endif
