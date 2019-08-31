CXXFLAGS = -Wall -std=c++11 -O2 -DNO_FREETYPE -I $(HOME)/libs/include 

all: main.exe

clean:
	rm -f main.exe *.o

main.exe: main.o Numeric.o Point.o Color.o ConvexHull.o ConvexPolygon.o PolygonCalculator.o
	$(CXX) $^ -o $@ -L $(HOME)/libs/lib -l PNGwriter -l png

main.o: main.cc Numeric.hh Point.hh Color.hh ConvexHull.hh ConvexPolygon.hh PolygonCalculator.hh

Numeric.o: Numeric.cc Numeric.hh

Point.o: Point.cc Point.hh Numeric.hh

Color.o : Color.cc Color.hh

ConvexHull.o : ConvexHull.cc ConvexHull.hh ConvexPolygon.hh Point.hh Numeric.hh

ConvexPolygon.o : ConvexPolygon.cc ConvexPolygon.hh Point.hh Color.hh ConvexHull.hh Numeric.hh

PolygonCalculator.o : PolygonCalculator.cc PolygonCalculator.hh ConvexPolygon.hh Point.hh Color.hh
