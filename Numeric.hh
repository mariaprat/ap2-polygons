#ifndef numeric_hh
#define numeric_hh

/** This file stores constant values and functions to deal with numerical
    precision issues. */

// *****************************************************************************
    
/* Maximum value for double numbers. */
const double INF = 1./0.;

/* Absolute tolerance used to compare numeric values. */
const double EPS = 1e-12; 

/** Number of decimal digits to print after the decimal dot. */
const int PRECISION = 3;

/* Returns true if the values are considered numerically equal and false otherwise. */
bool isEqual (const double &a, const double &b);

#endif
