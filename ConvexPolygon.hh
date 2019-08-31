#ifndef ConvexPolygon_hh
#define ConvexPolygon_hh

#include "Numeric.hh"
#include "Point.hh"
#include "Color.hh"
#include "ConvexHull.hh"

#include <vector>

using namespace std;

/** The ConvexPolygon class stores a convex polygon as a vector of points of
    Point class (see Point.hh) and a color of Color class (see Color.hh). It 
    also provides operations for convex polygons. 
    It uses the Convex Hull function included in ConvexHull.hh to find the 
    convex hull of a finite set of points.
    It allows for numerical precision considerations (see Numeric.hh). */

// *****************************************************************************

class ConvexPolygon  {
    private:
        /* Stores the vertices of the convex polygon in clockwise order starting
           from the point of minimum X coordinate (in case of tie, with minimum
           Y coordinate). 
           It only keeps the points that belong to the convex hull. */
        vector<Point> polygon;

        /* Color of the convex polygon. */
        Color color;

    public:
        /* Constructor. */
        ConvexPolygon(vector<Point> polygon = vector<Point>(), Color color = Color());

        /* Returns a vector of points with the polygon's vertices in clockwise
           order, starting from the point of minimum X coordinate (in case of 
           tie, with minimum Y coordinate). */
        vector<Point> get_vertices() const;

        /* Returns the color of the polygon. */
        Color get_color() const;

        /* Pre: new_color components are in [0,1].
           Changes the color of the polygon to new_color. */
        void set_color(const Color &new_color);

        /* Returns the number of vertices of the polygon's convex hull. */
        int vertices() const;

        /* Returns the area of the polygon's convex hull using Shoelace formula. */
        double area() const;

        /* Returns the perimeter of the polygon's convex hull. */
        double perimeter() const;

        /* Pre: the polygon has at least one point.
           Returns the centroid of the polygon's convex hull. */
        Point centroid() const;

        /* Returns true if the point p lies in (or on) the polygon, and false
           otherwise. */
        bool contains(const Point &point) const;

        /* Returns the (convex) intersection of the current polygon with the
           polygon p. */
        ConvexPolygon intersection(const ConvexPolygon &p) const;

        /* Returns the convex union of the current polygon with the polygon p. */
        ConvexPolygon convex_union(const ConvexPolygon &p) const;

        /* Returns a convex polygon with the four vertices of the minimum box
           within which all the points lie.
           Note that the bounding box can be degenerate. */
        ConvexPolygon bounding_box() const;

        /* Equal to operator.
           Two convex polygons are equal if their vector<Point> are equal. */
        bool operator == (const ConvexPolygon& p) const;
};


#endif
