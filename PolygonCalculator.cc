#include "PolygonCalculator.hh"

#include <iomanip>
#include <cmath>
#include <vector>
#include <pngwriter.h>

using namespace std;

// *****************************************************************************

void print_error(string error) {
    cout << "error: " << error << "." << endl;
}

/** Prints the output of a warning in the appropiate format. */
void print_warning(string warning) {
    cout << "warning: " << warning << "." << endl;
}

void comment() {
    cout << "#" << endl;
}

/** Prints the output of a valid command without answer in the appropiate format. */
void print_valid() {
    cout << "ok" << endl;
}

void polygon(istringstream& iss, map<string,ConvexPolygon>& index) {
    string id;
    if (iss >> id) {
        bool some_error = false;
        vector<Point> vPolygon;
        double x, y;
        while (iss >> x) {
            if (iss >> y) {
                vPolygon.push_back(Point(x, y));
            } else {
                print_error("not an even number of coordinates");
                some_error = true;
            }
        }
        string s;
        if (iss >> s) {
            print_warning("some commands have been ignored");
        }
        if (not some_error) {
            index[id] = ConvexPolygon(vPolygon);
            print_valid();
        }
    } else {
        print_error("wrong type or number of arguments");
    }
}

/* Prints the polygon identified by "id" with vertices in "p" to "output" stream. */
void print_polygon(const string &id, const vector<Point> &p, ostream &output = cout) {
    output << fixed << setprecision(PRECISION);
    output << id;
    for (int i = 0; i < (int) p.size(); ++i) {
        output << " " << p[i].get_X() << " " << p[i].get_Y();
    }
    output << endl;
}

void print(istringstream& iss, map<string,ConvexPolygon>& index) {
    string id;
    if (iss >> id) {
        string s;
        if (iss >> s) {
            print_error("wrong type or number of arguments");
        } else {
            if (not index.count(id)) {
                print_error("undefined polygon");
            } else {
                ConvexPolygon Polygon = index[id];
                vector<Point> Vertices = Polygon.get_vertices();

                print_polygon(id, Vertices);
            }
        }
    } else {
        print_error("wrong type or number of arguments");
    }
}

void area(istringstream& iss, map<string,ConvexPolygon>& index) {
    string id;
    if (iss >> id) {
        string s;
        if (iss >> s) {
            print_warning("some commands have been ignored");
        } else {
            if (not index.count(id)) {
                print_error("undefined polygon");
            } else {
                cout << index[id].area() << endl;
            }
        }
    } else {
        print_error("wrong type or number of arguments");
    }
}

void perimeter(istringstream &iss, map<string,ConvexPolygon> &index) {
    string id;
    if (iss >> id) {
        string s;
        if (iss >> s) {
            print_warning("some commands have been ignored");
        } else {
            if (not index.count(id)) {
                print_error("undefined polygon");
            } else {
                cout << index[id].perimeter() << endl;
            }
        }
    } else {
        print_error("wrong type or number of arguments");
    }
}

void vertices(istringstream& iss, map<string,ConvexPolygon>& index) {
    string id;
    if (iss >> id) {
        string s;
        if (iss >> s) {
            print_warning("some commands have been ignored");
        } else {
            if (not index.count(id)) {
                print_error("undefined polygon");
            } else {
                cout << index[id].vertices() << endl;
            }
        }
    } else {
        print_error("wrong type or number of arguments");
    }
}

void centroid(istringstream& iss, map<string,ConvexPolygon>& index) {
    string id;
    if (iss >> id) {
        string s;
        if (iss >> s) {
            print_warning("some commands have been ignored");
        } else {
            if (not index.count(id)) {
                print_error("undefined polygon");
            } else {
                if (index[id].vertices() > 0) {
                    Point centroid = index[id].centroid();
                    cout << centroid.get_X() << " " << centroid.get_Y() << endl;
                } else {
                    print_error("empty polygon, centroid not defined");
                }
            }
        }
    } else {
        print_error("wrong type or number of arguments");
    }
}

void list(istringstream& iss, map<string,ConvexPolygon>& index) {
    string s;
    if (iss >> s) {
        print_warning("some commands have been ignored");
    }

    if (index.empty()) {
        print_error("no defined polygons");
    } else {
        bool first = true;
        for (auto polygons : index) {
            if (not first) cout << " ";
            cout << polygons.first;
            first = false;
        }
        cout << endl;
    }
}

void save(istringstream &iss, map<string,ConvexPolygon>& index) {
    string namefile;
    if (iss >> namefile) {
        ofstream file;
        file.open(namefile);
        bool undefined = false;
        string id;
        while (iss >> id) {
            if (not index.count(id)) {
                undefined = true;
            } else {
                vector<Point> Vertices = index[id].get_vertices();
                print_polygon(id, Vertices, file);
            }
        }
        file.close();
        if (undefined) print_warning("unable to save some undefined polygon(s)");
        else print_valid();
    } else {
        print_error("wrong type or number of arguments");
    }
}

void load(istringstream &iss, map<string,ConvexPolygon>& index) {
    string namefile;
    if (iss >> namefile) {
        ifstream file;
        file.open(namefile);
        if (file.is_open()) {
            string polygon;
            bool some_warning = false;
            while(getline(file, polygon)) {
                istringstream new_iss(polygon);
                string id;
                new_iss >> id;
                vector<Point> vPolygon;
                bool some_error = false;
                double x, y;
                while (new_iss >> x) {
                    if (new_iss >> y) {
                        vPolygon.push_back(Point(x, y));
                    } else {
                        print_error("not an even number of coordinates");
                        some_error = true;
                        some_warning = true;
                    }
                }
                string s;
                if (new_iss >> s) {
                    print_warning("some commands have been ignored");
                }
                if (not some_error) {
                    ConvexPolygon Polygon(vPolygon);
                    index[id] = Polygon;
                }
            }
            file.close();
            if (not some_warning) print_valid();
            else print_warning("unable to load some incorrectly defined polygon(s)");
        } else {
            print_error("unable to open file");
        }
    } else {
        print_error("wrong type or number of arguments");
    }
}

void setcol(istringstream &iss, map<string,ConvexPolygon>& index) {
    string id;
    if (iss >> id) {
        if (not index.count(id)) {
            print_error("undefined polygon");
        } else {
            double r, g, b;
            if (iss >> r >> g >> b) {
                if (r >= 0 and r <= 1 and g >= 0 and g <= 1 and b >= 0 and b <= 1) {
                    index[id].set_color(Color(r,g,b));
                    print_valid();
                } else {
                    print_error("color components should be in [0,1]");
                }
            } else {
                print_error("wrong type or number of arguments");
            }
            string s;
            if (iss >> s) {
                print_warning("some commands have been ignored");
            }
        }
    } else {
        print_error("wrong type or number of arguments");
    }
}

void draw(istringstream &iss, map<string,ConvexPolygon>& index) {
    bool some_error = false;

    string file_name;
    if (iss >> file_name) {
        vector<ConvexPolygon> to_draw;

        double x_min, y_min, x_max, y_max;
        x_min = y_min = INF;
        x_max = y_max = -INF;

        string id;
        while (iss >> id) {
            if (not index.count(id)) {
                some_error = true;
            } else {
                ConvexPolygon p = index[id];
                to_draw.push_back(p);
                ConvexPolygon bbox = p.bounding_box();
                vector<Point> v_bbox = bbox.get_vertices();
                for (auto p : v_bbox) {
                    x_min = min(x_min, p.get_X());
                    y_min = min(y_min, p.get_Y());
                    x_max = max(x_max, p.get_X());
                    y_max = max(y_max, p.get_Y());
                }
            }
        }

        double width = x_max - x_min;
        double height = y_max - y_min;
        double side = max(width, height);
        double scale = 497./side;

        int x0 = 2 + round(0.5*(497 - scale*width));
        int y0 = 2 + round(0.5*(497 - scale*height));

        pngwriter image(500, 500, 1.0, file_name.c_str());

        for (auto p : to_draw) {
            Color c = p.get_color();

            vector<Point> vp = p.get_vertices();
            int s = vp.size();

            for (int i = 0; i < s; ++i) {
                /* Draw edge between i-th and i+1-th points. */

                int x1 = x0 + round(scale*(vp[i].get_X() - x_min));
                int x2 = x0 + round(scale*(vp[(i+1)%s].get_X() - x_min));

                double slope = vp[i].slope(vp[(i+1)%s]);

                int y1 = y0 + round(scale*(vp[i].get_Y() - y_min));
                int y2 = y0 + round(scale*(vp[(i+1)%s].get_Y() - y_min));

                if (slope == INF) {
                    /* Vertical line. */
                    for (int y = min(y1,y2); y <= max(y1,y2); ++y) {
                        image.plot(x1, y, c.get_R(), c.get_G(), c.get_B());
                    }
                } else {
                    for (int x = min(x1,x2); x <= max(x1,x2); ++x) {
                        int y = y1 + round(slope*x - slope*x1);
                        image.plot(x, y, c.get_R(), c.get_G(), c.get_B());
                    }
                }
            }
        }
        
        image.close();
        if (some_error) print_warning("unable to draw some undefined polygon(s)");
        else print_valid();
    } else {
        print_error("wrong type or number of arguments");
    }
}

void intersection(istringstream &iss, map<string,ConvexPolygon>& index) {
    string id1, id2;
    if (iss >> id1 >> id2) {
        bool some_error = false;
        string id3;
        if (iss >> id3) {
            string s;
            if (iss >> s) {
                print_warning("some commands have been ignored");
            }
            if (not index.count(id2) or not index.count(id3)) {
                print_error("undefined polygon(s)");
                some_error = true;
            } else {
                index[id1] = index[id2].intersection(index[id3]);
            }
        } else {
            if (not index.count(id1) or not index.count(id2)) {
                print_error("undefined polygon(s)");
                some_error = true;
            } else {
                index[id1] = index[id1].intersection(index[id2]);
            }
        }
        if (not some_error) print_valid();
    } else {
        print_error("wrong type or number of arguments");
    }
}

void convex_union(istringstream &iss, map<string,ConvexPolygon>& index) {
    string id1, id2;
    if (iss >> id1 >> id2) {
        bool some_error = false;
        string id3;
        if (iss >> id3) {
            string s;
            if (iss >> s) {
                print_warning("some commands have been ignored");
            }
            if (not index.count(id2) or not index.count(id3)) {
                print_error("undefined polygon(s)");
                some_error = true;
            } else {
                index[id1] = index[id2].convex_union(index[id3]);
            }
        } else {
            if (not index.count(id1) or not index.count(id2)) {
                print_error("undefined polygon(s)");
                some_error = true;
            } else {
                index[id1] = index[id1].convex_union(index[id2]);
            }
        }
        if (not some_error) print_valid();
    } else {
        print_error("wrong type or number of arguments");
    }
}

void inside(istringstream &iss, map<string,ConvexPolygon>& index) {
    string id1, id2;
    if (iss >> id1 >> id2) {
        string s;
        if (iss >> s) {
            print_warning("some commands have been ignored");
        }
        if (not index.count(id1) or not index.count(id2)) {
            print_error("undefined polygon(s)");
        } else {
            ConvexPolygon their_intersection = index[id1].intersection(index[id2]);
            if (their_intersection == index[id1]) cout << "yes" << endl;
            else cout << "no" << endl;
        }
    } else {
        print_error("wrong type or number of arguments");
    }
}

void bbox(istringstream &iss, map<string,ConvexPolygon>& index) {
    string new_id;
    if (iss >> new_id) {
        double x_min, y_min, x_max, y_max;
        x_min = y_min = INF;
        x_max = y_max = -INF;

        bool undefined = false;
        bool read = false;

        string id;
        while (iss >> id) {
            read = true;
            if (not index.count(id)) {
                undefined = true;
            } else {
                vector<Point> p = index[id].get_vertices();
                for (int i = 0; i < int(p.size()); ++i) {
                    x_max = max(x_max, p[i].get_X());
                    y_max = max(y_max, p[i].get_Y());
                    x_min = min(x_min, p[i].get_X());
                    y_min = min(y_min, p[i].get_Y());
                }
            }
        }

        if (undefined) {
            print_error("undefined polygon(s)");
        } else {
            if (read) {
                vector<Point> vPolygon = {Point(x_min, y_min), Point(x_min, y_max),
                    Point(x_max, y_max), Point(x_max, y_min)};
                index[new_id] = ConvexPolygon(vPolygon);
                print_valid();
            } else {
                print_error("wrong type or number of arguments");
            }
        }
    } else {
        print_error("wrong type or number of arguments");
    }
}

void delete_polygon(istringstream &iss, map<string,ConvexPolygon>& index) {
    string id;
    if (iss >> id) {
        string s;
        if (iss >> s) {
            print_warning("some commands have been ignored");
        }

        if (not index.count(id)) {
            print_error("undefined polygon(s)");
        } else {
            index.erase(id);
            print_valid();
        }
    } else {
        print_error("wrong type or number of arguments");
    }
}
