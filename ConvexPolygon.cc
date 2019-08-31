#include "ConvexPolygon.hh"

#include <cmath>

using namespace std;

// *****************************************************************************

ConvexPolygon::ConvexPolygon (vector<Point> p, Color c) : polygon(p), color(c) {
    ConvexHull(polygon);
}

vector<Point> ConvexPolygon::get_vertices() const {
    return polygon;
}

Color ConvexPolygon::get_color() const {
    return color;
}

void ConvexPolygon::set_color(const Color &new_color) {
    color = new_color;
}

int ConvexPolygon::vertices() const {
    return polygon.size();
}

double ConvexPolygon::area() const {
    double polygon_area = 0;
    int j = polygon.size() - 1;

    for (int i = 0; i < (int) polygon.size(); ++i) {
        double x_terms = polygon[j].get_X() + polygon[i].get_X();
        double y_terms = polygon[j].get_Y() - polygon[i].get_Y();
        polygon_area += x_terms*y_terms;
        j = i;
    }

    return abs(0.5*polygon_area);
}

double ConvexPolygon::perimeter() const {
    int s = polygon.size();
    double polygon_perimeter = 0;

    for (int i = 0; i < s; ++i) {
        polygon_perimeter += polygon[i].distance(polygon[(i + 1)%s]);
    }

    return polygon_perimeter;
}

Point ConvexPolygon::centroid() const {
    Point centroid = polygon[0];

    for (int i = 1; i < (int) polygon.size(); ++i) {
        centroid += polygon[i];
    }

    return centroid*(1 / (double) polygon.size());
}

/* Returns true if the point p3 is at the left of the vector p1->p2, and false 
   otherwise. Note that returns false if points are collinear. */
bool left_of(const Point &p1, const Point &p2, const Point &p3) {
    double d1 = (p2.get_X() - p1.get_X())*(p3.get_Y() - p1.get_Y());
    double d2 = (p2.get_Y() - p1.get_Y())*(p3.get_X() - p1.get_X());
    return (d1 > d2 and not isEqual(d1, d2));
}

bool ConvexPolygon::contains(const Point &point) const {
    int s = polygon.size();

    if (s == 0) return false;
    if (s == 1) return (point == polygon[0]);
    
    /* The point is outside of the polygon if it's at the left of some edge. */
    for (int i = 0; i < s; ++i) {
        if (left_of(polygon[i], polygon[(i+1)%s], point)) return false;
    }
    return true;
}

/* Returns true if the point (x,y) lies in the edge between (x1,y1) and (x2,y2). */
bool in_the_edge (const double &x, const double &y, const double &x1,
                     const double &y1, const double &x2, const double &y2) {
    return (x >= min(x1,x2) or isEqual(x, min(x1,x2)))
            and (x <= max(x1,x2) or isEqual(x, max(x1,x2)))
                and (y >= min(y1,y2) or isEqual(y, min(y1,y2)))
                    and (y <= max(y1,y2) or isEqual(y, max(y1,y2)));
}

ConvexPolygon ConvexPolygon::intersection(const ConvexPolygon &p) const {
    /* Let's call P1 to the current polygon and P2 to the polygon p. */
    vector<Point> new_polygon;

    int s = polygon.size();
    int q = p.polygon.size();

    /* We add to new_polygon the vertices of P1 that lie inside of P2. */
    for (int i = 0; i < s; ++i) {
        if (p.contains(polygon[i])) {
            new_polygon.push_back(polygon[i]);
        }
    }

    /* We add to new_polygon the vertices of P2 that lie inside of P1. */
    for (int i = 0; i < q; ++i) {
        if (contains(p.polygon[i])) {
            new_polygon.push_back(p.polygon[i]);
        }
    }

    /* We add to new_polygon the intersection points of the edges of P1 and P2. */
    for (int i = 0; i < s; ++i) {
        /* We find the line equation a1*x + b1*y = c1 of the (i+1)-th edge of P1. */
        double x1 = polygon[i].get_X();
        double y1 = polygon[i].get_Y();
        double x2 = polygon[(i+1)%s].get_X();
        double y2 = polygon[(i+1)%s].get_Y();
  
        double a1 = y2 - y1; 
        double b1 = x1 - x2;
        double c1 = x1*y2 - y1*x2;

        for (int j = 0; j < q; ++j) {
            /* We find the line equation a2*x + b2*y = c2 of the (j+1)-th edge of P2. 
               We don't save the coefficients because calculating them it's a constant time operation
               and saving them costs memory. */
            double px1 = p.polygon[j].get_X();
            double py1 = p.polygon[j].get_Y();
            double px2 = p.polygon[(j+1)%q].get_X();
            double py2 = p.polygon[(j+1)%q].get_Y();

            double a2 = py2 - py1; 
            double b2 = px1 - px2;
            double c2 = px1*py2 - py1*px2;

            double det = a1*b2 - a2*b1;

            if (not isEqual(det, 0.)) {
                /* If the edges aren't parallel, we solve the system of equations
                   and check if the intersection lies on both edges. */

                double x = (b2*c1 - b1*c2) / det;
                double y = (a1*c2 - a2*c1) / det;
                
                bool edge1 = in_the_edge(x, y, x1, y1, x2, y2);
                bool edge2 = in_the_edge(x, y, px1, py1, px2, py2);

                if (edge1 and edge2) {
                    new_polygon.push_back(Point(x,y));
                }
            }
        }
    }
    return ConvexPolygon(new_polygon);
}

ConvexPolygon ConvexPolygon::convex_union(const ConvexPolygon &p) const {
    vector<Point> new_polygon = polygon;
    
    new_polygon.insert(new_polygon.end(), p.polygon.begin(), p.polygon.end());

    return ConvexPolygon(new_polygon);
}

ConvexPolygon ConvexPolygon::bounding_box() const {
    vector<Point> new_polygon;

    if (polygon.size() > 0) {
        double x_max, y_max, x_min, y_min;
        x_max = y_max = -INF;
        x_min = y_min = INF;

        for (int i = 0; i < (int) polygon.size(); ++i) {
            x_max = max(x_max, polygon[i].get_X());
            y_max = max(y_max, polygon[i].get_Y());
            x_min = min(x_min, polygon[i].get_X());
            y_min = min(y_min, polygon[i].get_Y());
        }

        new_polygon = {Point(x_min, y_min), Point(x_min, y_max), 
            Point(x_max, y_max), Point(x_max, y_min)};
    }

    return ConvexPolygon(new_polygon);
}

bool ConvexPolygon::operator == (const ConvexPolygon &p) const {
    if (polygon.size() != p.polygon.size()) return false;

    for (int i = 0; i < (int) polygon.size(); ++i) {
        if (polygon[i] != p.polygon[i]) return false;
    }

    return true;
}
