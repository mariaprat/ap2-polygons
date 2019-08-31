#include "Numeric.hh"

#include <cmath>

using namespace std;

// *****************************************************************************

bool isEqual (const double &a, const double &b) {
    return abs(a - b) <= EPS;
}