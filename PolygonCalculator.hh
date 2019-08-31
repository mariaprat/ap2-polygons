#ifndef PolygonCalculator_hh
#define PolygonCalculator_hh

#include "Numeric.hh"
#include "Point.hh"
#include "Color.hh"
#include "ConvexPolygon.hh"

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <sstream>

using namespace std;

/** This file stores the functions used by the Polygon Calculator. */

// *****************************************************************************

/** Prints the output of an error in the appropiate format. */
void print_error(string error);

/** Prints the output of a comment in the appropiate format. */
void comment();

/** Expects an identifier and a list of points. Example: p1 0 0 1 1 0 1 
    Associates the identifier with the convex hull of the given points.
    If the identifier was previously used, it discards the previous polygon. */
void polygon(istringstream& iss, map<string,ConvexPolygon>& index);

/** Expects an identifier. Prints the identifier and the vertices in the convex 
    hull, in clockwise order starting from the leftmost (if tie, lowest) point. */
void print(istringstream& iss, map<string,ConvexPolygon>& index);

/** Expects an identifier. Prints the area of the given polygon. */
void area(istringstream& iss, map<string,ConvexPolygon>& index);

/** Expects an identifier. Prints the perimeter of the given polygon. */
void perimeter(istringstream &iss, map<string,ConvexPolygon> &index);

/** Expects an identifier. Prints the number of vertices of the given polygon. */
void vertices(istringstream& iss, map<string,ConvexPolygon>& index);

/** Expects an identifier. Prints the centroid (if exists) of the given polygon. */
void centroid(istringstream& iss, map<string,ConvexPolygon>& index);

/** Prints all polygon identifiers, lexycographically sorted. */
void list(istringstream& iss, map<string,ConvexPolygon>& index);

/** Expects a file name and some identifiers. Saves the given polygons in the file.
    If the file already exists, it discards its previous content. */
void save(istringstream &iss, map<string,ConvexPolygon>& index);

/** Expects the name of an existing file in the current directory. Loads the 
    polygons stored in the file, formated as the "print" function output. */
void load(istringstream &iss, map<string,ConvexPolygon>& index);

/** Expects an identifier and three numbers in [0,1]. Links the color to the polygon. */
void setcol(istringstream &iss, map<string,ConvexPolygon>& index);

/** Expects a file name and a list of identifiers. Draws the coloured polygons in 
    a 500x500 pixels PNG file with white background. Coordinates are scaled to fit
    in the 498x498 central part, preserving the original aspect ratio. */
void draw(istringstream &iss, map<string,ConvexPolygon>& index);

/** Expects two or three identifiers. TWO IDS: updates the first polygon to its 
    intersection with the second one. THREE IDS: associates the first polygon
    to the intersection of the other two. */
void intersection(istringstream &iss, map<string,ConvexPolygon>& index);

/** Expects two or three identifiers. TWO IDS: updates the first polygon to its 
    convex union with the second one. THREE IDS: associates the first polygon
    to the convex union of the other two. */
void convex_union(istringstream &iss, map<string,ConvexPolygon>& index);

/** Expects two identifiers. Prints "yes" if the first polygon is inside the 
    second and "no" otherwise. */
void inside(istringstream &iss, map<string,ConvexPolygon>& index);

/** Expects a list of identifiers. Associates the bounding box of the given 
    polygons to the first identifier. */
void bbox(istringstream &iss, map<string,ConvexPolygon>& index);

/** Expects an identifier. Deletes the given polygon from the list of polygons. */
void delete_polygon(istringstream &iss, map<string,ConvexPolygon>& index);

#endif