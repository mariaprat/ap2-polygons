#ifndef ConvexHull_hh
#define ConvexHull_hh

#include "Numeric.hh"
#include "Point.hh"

#include <vector>

using namespace std;

/** This file stores the function that finds the convex hull of a set of 
    points of class Point (see Point.hh).
    It allows for numerical precision considerations (see Numeric.hh). */

// *****************************************************************************

void ConvexHull (vector<Point> &p);

#endif

