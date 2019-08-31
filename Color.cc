#include "Color.hh"

using namespace std;

// *****************************************************************************

Color::Color (double r, double g, double b) : r(r), g(g), b(b) {}

double Color::get_R () const {
    return r;
}

double Color::get_G () const {
    return g;
}	

double Color::get_B () const {
    return b;
}
