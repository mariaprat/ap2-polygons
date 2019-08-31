#include "ConvexPolygon.hh"
#include "PolygonCalculator.hh"

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

/* ************************* Convex Polygon Calculator *************************

    The Convex Polygon Calculator provides an interface to operate with Convex
    Polygons. More information can be found in the README file. 

    This file stores the main function of the polygon calculator. 

    See ConvexPolygon.hh for more information about the Convex Polygon class.
    See PolygonCalculator.hh for more information about the Polygon Calculator
    functions. */

// *****************************************************************************

int main() {
    cout.setf(ios::fixed);
    cout.precision(PRECISION);

    cout << "Welcome to the Polygon Calculator. Enter your commands:" << endl;
    
    /** This map links the polygons' identifiers to the convex polygons they
        represent.
        It stores the list of defined polygons. */
    map<string,ConvexPolygon> index;

    bool keep_going = true;

    string command;
    /* Each command should be in the same line. */

    while (keep_going and getline(cin, command)) {
        istringstream iss(command);
        
        string instruction;
        iss >> instruction;

             if (instruction == "#")            comment();
        else if (instruction == "polygon")      polygon(iss, index);
        else if (instruction == "print")        print(iss, index);
        else if (instruction == "area")         area(iss, index);
        else if (instruction == "perimeter")    perimeter(iss, index);
        else if (instruction == "vertices")     vertices(iss, index);
        else if (instruction == "centroid")     centroid(iss, index);
        else if (instruction == "list")         list(iss, index);
        else if (instruction == "save")         save(iss, index);
        else if (instruction == "load")         load(iss, index);
        else if (instruction == "setcol")       setcol(iss, index);
        else if (instruction == "draw")         draw(iss, index);
        else if (instruction == "intersection") intersection(iss, index);
        else if (instruction == "union")        convex_union(iss, index);
        else if (instruction == "inside")       inside(iss, index);
        else if (instruction == "bbox")         bbox(iss, index);
        else if (instruction == "delete")       delete_polygon(iss, index);
        else if (instruction == "exit")         keep_going = false;

        else if (not instruction.empty())       print_error("unrecognized command");
    }
}

