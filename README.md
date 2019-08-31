# Polygon Calculator

A simple Polygon Calculator that provides an intuitive interface to operate with convex polygons.

## Description

The Polygon Calculator provides a fully operational interface where you can run all the commands described in the project [statement](https://github.com/jordi-petit/ap2-poligons-2019) and more.

### Custom classes

The *ConvexPolygon* class has been designed to represent and manipulate convex polygons.

The *Color* class stores an RGB color.

The *Point* class represents a two-dimensional point and provides operations for it.

### Additional features

#### Delete

The `delete` command allows you to remove a previously defined polygon.

##### Example

```bash
polygon p1
delete p1
```
#### Exit

If you want to suspend the Polygon Calculator interface, you can use the `exit` command to get back to the command line.

##### Example

```bash
exit
```

## Installation

### Prerequisites

The Polygon Calculator is a C++11 program.

It uses the open source graphics library [PNGwriter](https://github.com/pngwriter/pngwriter). The installation instructions can be found [here](https://github.com/jordi-petit/ap2-imatges/).

### Installing (Linux)

Download the ZIP file that contains the source code and uncompress it.

Get inside the directory with the source code:

```bash
cd PolygonCalculator
```

Build the project:

```bash
make
```

Finally, execute the interface:

```bash
/.main.exe
```

## Usage

Once inside the interface, simply enter the commands in the terminal.

The interface has been designed to detect possible errors and inform about them (but not all!). In some cases, if the first part of the command is understandable, it ignores the incorrect part and warns you about it.

### Test cases

The **test_cases** folder includes a set of test examples to check the functionality of both the Polygon Calculator interface and the *ConvexPolygon* class (note that the latter is effectively checked by the first).

- Test case #1: all commands

	Add the file `t1_morepolygons.txt` to the executable directory. Copy the content of `test1_input.txt` and paste it to the interface. The expected terminal output is included in `test1_output.txt`. A file equal to `test1_polygons.txt` should have been created, together with two figures equal to `figure1.png` and `figure2.png`.

- Test case #2: big polygons

	Add the file `circles.txt` to the executable directory. Copy the content of `test2_input.txt` and paste it to the interface. The expected terminal output is included in `test2_output.txt`. Three figures equal to `cercles.png`, `eclpise.png` and `strange.png` should have been created.

	Note that the result can differ from the expected because of numerical issues.

	The intersection command can take more than five seconds to finish because of the big size of the polygons.

- Test case #3: intersections

	Copy the content of `test3_input.txt` and paste it to the interface. The expected terminal output is included in `test3_output.txt`. Three figures equal to `figure1.png`, `figure2.png` and `figure3.png` should have been created.

- Test case #4: errors and warnings

	Copy the content of `test4_input.txt` and paste it to the interface. The expected terminal output is included in `test4_output.txt`. A figure equal to `example.png` and an empty file equal to `example.txt` should have been created.

## Implementation and design details

The project has been designed to be easily modifiable and with output format easily customizable. Multiple files allow to group similar functions and variables, while maintaining an ordered and understandable code.

#### Files

The *main* file is the source code of the project.

The *PolygonCalculator* files store the functions called by the interface.

The *ConvexHull* files provide functions for the *ConvexPolygon* class to calculate the convex hull of a set of points.

The *Numeric* files provide constant values and functions to deal with numerical issues.

#### *Point* class

The *Point* class is an standard implementation of a two-dimensional point in the Cartesian plane. It includes useful functions to manipulate and obtain information about a point.

Note that we have redefined the equal to operator (==) to easily cope with numerical considerations. This decision is justified by bearing in mind that if exact precision is wanted, it can be achieved by only changing the tolerance value in the *Numerical* files.

#### *ConvexPolygon* class

The *ConvexPolygon* class stores two attributes: a vector of *Points* and a *Color*. The vector of *Points* has been chosen because it is a simple and easy editable implementation of a set of points that allows for considerable operations.

We have decided to include the color of a polygon as an attribute because of two main reasons. First, because we don't need to add an additional map between polygons and colors. And second, and most importantly, because it will be easier to add new features to the color class. For example, we could easily implement transformations between RGB and HSV colors.

##### Algorithm complexity and implementation details

We believe that it's interesting to discuss about the algorithm complexity of the following functions. Let `n` be the initial number of points in the vector of points of a given polygon.

- Convex hull of a polygon (*ConvexHull - ConvexHull.cc*)

	Creating a simple polygon (*sort_polygon - ConvexHull.cc*) runs in O(nlogn) time because of sorting. This function determines the overall complexity of the Graham scan.

- Intersection of polygons (*intersection - ConvexPolygon.cc*)

	We have implemented an O(n²) intersecting algorithm. Although this complexity could be improved, it is fast enough for the requirements of this project and for the most of the polygons users will be working with.

As additional comments, we want to make clear that we are aware that some functions (for example, *draw - PolygonCalculator.cc*) are quite long. However, because of its simplicity we have decided to keep it that way instead of dividing it in subfunctions. Moreover, in the *draw* function we draw the polygon edge by edge instead of using the function `polygon` in `PNGwriter` because it gave problems in corner cases.
