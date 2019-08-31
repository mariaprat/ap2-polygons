#include "ConvexHull.hh"

#include <cmath>
#include <algorithm>

using namespace std;

// *****************************************************************************

struct comparison {
	Point pivot;
	bool operator() (const Point &a, const Point &b) {
		if (pivot.slope(a) == pivot.slope(b)) {
			return a.distance(pivot) < b.distance(pivot);
		}
		return pivot.slope(a) > pivot.slope(b);
	}
};

void sort_polygon(vector<Point> &polygon) {
	Point pivot = polygon[0];

	for (int i = 1; i < (int) polygon.size(); ++i) {
		pivot = min(pivot, polygon[i]);
	}

	/* We sort the points in clockwise order starting from the pivot.
	   The comparision structure allows for sorting while considering the pivot. */
	sort(polygon.begin(), polygon.end(), comparison{pivot});
}

/* Returns true if the point p3 is at the right of the vector p1->p2. */
bool right_of(const Point &p1, const Point &p2, const Point &p3) {
	double d1 = (p2.get_X() - p1.get_X())*(p3.get_Y() - p1.get_Y());
    double d2 = (p2.get_Y() - p1.get_Y())*(p3.get_X() - p1.get_X());
    return (d1 < d2 and not isEqual(d1, d2));
}

void ConvexHull (vector<Point> &p) {
	if (p.size() > 0) {
		sort_polygon(p);
		if (p.size() > 2) {
			vector<Point> q;

			/* We find the convex hull of the polygon using a modified Graham
			   scan that allows to have collinear and repeated points. */

			q.push_back(p[0]);
			int s = 1;
			while (s < (int) p.size() and p[0] == p[s]) {
				++s;
			}
			if (s < (int) p.size()) {
				q.push_back(p[s]);
				int m = 1;
				for (int k = s + 1; k < (int) p.size(); ++k) {
					while (m > 0 and not right_of(q[m-1], q[m], p[k])) {
						--m;
						q.pop_back();
					}
					++m;
					q.push_back(p[k]);
				}
			}
			p = q;
		}
	}
}
