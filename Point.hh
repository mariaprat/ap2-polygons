#ifndef Point_hh
#define Point_hh

#include "Numeric.hh"

/** The Point class stores the coordinates of a two dimensional point in the
    Cartesian plane and provides operations for it.
    It allows for numerical precision considerations (see Numeric.hh). */

// *****************************************************************************

class Point  {
    private:
        /* X and Y coordinates of the point. */
        double x, y;

    public:
        /* Constructor. */
        Point(double x = 0, double y = 0);

        /* Destructor. */
        ~Point();

        /* Gets the X coordinate. */
        double get_X() const;

        /* Gets the Y coordinate. */
        double get_Y() const;

        /* Returns the 2-norm distance to the point p. */
        double distance(const Point& p) const;

        /* Returns the 2-norm distance to the origin. */
        double radius() const;

        /* Returns the angle of the polar coordinate of the point. */
        double angle() const;
        
        /* Returns the slope of the line that passes through the current point 
           and the point p.
           If two points are vertically aligned, returns INF. */ 
        double slope(const Point& p) const;

        /* Equal to operator.
           Two points are equal iff both X and Y coordinates are equal. */
        bool operator == (const Point& p) const;

        /* Not equal to operator. */
        bool operator != (const Point& p) const;

        /* Less than operator. 
           The point A is less than point B iff the X coordinate of A is smaller
           than the X coordinate of B. In case of tie, A is less than B iff the
           Y coordinate of A is smaller than the Y coordinate of B. */
        bool operator < (const Point& p) const;
        
        /* Greater than operator. 
           The point A is greater than point B iff the X coordinate of A is 
           greater than the X coordinate of B. In case of tie, A is greater than
           B iff the Y coordinate of A is greater than the Y coordinate of B. */        
        bool operator > (const Point& p) const;

        /* Creates a new point by adding the coordinates of two points. */
        Point operator + (const Point& p) const;

        /* Sum assignment operator. */
        Point operator += (const Point& p);

        /* Creates a new point by multiplying each coordinate by a real number. */
        Point operator * (const double& d) const;

        /* Product by a real number assignment operator. */
        Point operator *= (const double& d);
};

#endif
