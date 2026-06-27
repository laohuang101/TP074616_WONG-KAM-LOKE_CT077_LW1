DATASET SIZES:

  students_500.csv    —   500 records
  students_2000.csv   —  2000 records
  students_8000.csv   —  8000 records
  students_30000.csv  — 30000 records

Each step is approximately a 4x increase in n.

PURPOSE:

These four sizes are provided to allow empirical Big-O analysis by observing
how algorithm runtime scales as n grows. Use menu option 10 to run the full
benchmark across all four datasets automatically.

EXPECTED GROWTH PER 4x INCREASE IN n:

  O(1)       — ~1x   constant, no growth
  O(log n)   — ~1.1x very slow growth (e.g. binary search)
  O(n)       — ~4x   linear growth (e.g. linear search, display)
  O(n log n) — ~4.9x slightly above linear (e.g. IntroSort)
  O(n^2)     — ~16x  quadratic growth (e.g. bubble/selection sort)

HOW TO USE FOR ANALYSIS:

1. Run the benchmark via option 10.
2. Record the IntroSort time for each dataset size.
3. Compute the ratio between consecutive sizes (e.g. time at 2000 / time at 500).
4. Compare the ratio against the expected values above to confirm your
   algorithm's time complexity empirically.

CSV FORMAT:

Each file follows the same structure with a header row:
  studentID, fullName, programmeCode, yearOfStudy, cgpa, contactNumber

Records with invalid CGPA values (outside 0.00 to 4.00) are skipped on load.