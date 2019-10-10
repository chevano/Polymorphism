/**
 
 The purpose of this lab is to practice the use of polymorphism in the context of shapes.
 A base class Polygon will be used to create Rectangle, Square, Hexagon, Pentagon.
 **/

#include <iostream>
#include <cmath>
using namespace std;

// Structure to contain an X and Y coordinate
struct coordinates {
    double x, y;
};

class polygon {
protected:
    // although every class inherits two sides, only rectangle will use the second side
    double x, y, side, side2; // coordinates of lower left corner and sides
public:    // virtual destructor
    virtual ~polygon();
    // all classes have the same functionality with setXY and setSide
    void setXY(double, double);
    void setSide(double, double); // note the side2 has a default value of 0
    // Pure virtual functions overwritten in derived classes
    virtual double perimeter()=0;
    virtual double area()=0;
    virtual coordinates center_of_gravity()=0;
};

/** Note 7. Make sure the destructors are made virtual
 No dynamic memory needs to be deallocated in this program **/
polygon::~polygon() {
    
}

/** "g. There should be a function to input the location of your object (x and y coordinates)"
	-> non virtual function. Defined once, available to all derived classes
 **/
void polygon::setXY(double x1, double y1) {
    x = x1;
    y = y1;
}
// set side for polygon/shape. Side 2 defaults to 0.
void polygon::setSide(double s, double s2=0) {
    side = s;
    side2 = s2;
}

class square : public polygon{
public:
    square();
    square(double, double, double);
    
    virtual double perimeter();
    virtual double area();
    virtual coordinates center_of_gravity();
};

// default constructor
square::square() {
    x = y = side = 0;
}

// generic constructor, side2 left undefined... not needed for square
square::square(double xcor, double ycor, double s) {
    x = xcor;
    y = ycor;
    side = s;
}

double square::perimeter() {
    return side * 4;
}

double square::area() {
    return side * side;
}

// Center of gravity function for square
coordinates square::center_of_gravity() {
    coordinates coord = {side / 2 + x, side / 2 + y};
    return coord;
}

class rectangle : public polygon{
public:
    rectangle();
    rectangle(double, double, double, double);
    
    virtual double perimeter();
    virtual double area();
    virtual coordinates center_of_gravity();
};

rectangle::rectangle() {
    x = y = side = side2 = 0;
}

rectangle::rectangle(double xcor, double ycor, double s1, double s2) {
    x = xcor;
    y = ycor;
    side = s1;
    side2 = s2;
}

double rectangle::perimeter() {
    return (side + side2) * 2;
}

double rectangle::area() {
    return side * side2;
}

coordinates rectangle::center_of_gravity() {
    coordinates coord = {side / 2 + x, side2 / 2 + y};
    return coord;
}

class pentagon : public polygon{
public:
    pentagon();
    pentagon(double, double, double);
    
    virtual double perimeter();
    virtual double area();
    virtual coordinates center_of_gravity();
};

pentagon::pentagon() {
    x = y = side = 0;
}

pentagon::pentagon(double xcor, double ycor, double s) {
    x = xcor;
    y = ycor;
    side = s;
}

double pentagon::perimeter() {
    return side * 5;
}

double pentagon::area() {
    return 5 * side * side * tan(54) / 4;
}

coordinates pentagon::center_of_gravity() {
    coordinates coord = {side / 2, side * tan(54) / 2};
    return coord;
}

class hexagon : public polygon {
public:
    hexagon();
    hexagon(double, double, double);
    
    virtual double perimeter();
    virtual double area();
    virtual coordinates center_of_gravity();
};

hexagon::hexagon() {
    x = y = side = 0;
}

hexagon::hexagon(double xcor, double ycor, double s) {
    x = xcor;
    y = ycor;
    side = s;
}

double hexagon::perimeter() {
    return side * 6;
}

double hexagon::area() {
    return 3 * pow(3,1/2) * side * side / 2;
}

coordinates hexagon::center_of_gravity() {
    coordinates coord = {side / 2, side * pow(3,1/2) / 2};
    return coord;
}

// f. The main program should have a function to display the menu with choices.
int menu();

int main() {
    // Note 4. The main program should have an array of 4 pointers to objects of type polygon.
    // Note 5. All these variables should be dynamically allocated.
    polygon *arr [4] = {new square(), new rectangle(), new pentagon(), new hexagon()};
    char cont = 'y';
    while (cont=='y') {
        int choice = menu()-1;
        
        cout << "Please enter the side length(s) ";
        double side1, side2=0;
        cin >> side1;
        if (choice==1) cin >> side2;
        
        double x, y;
        cout << "Please enter the coordinates of the bottom left corner ";
        cin >> x >> y;
        
        
        // Note 6. After the selection there will be a single function call using the array of pointers
        if (choice==1)
            arr[choice]->setSide(side1,side2);
        else
            arr[choice]->setSide(side1);
        
        arr[choice]->setXY(x,y);
        coordinates xy = arr[choice]->center_of_gravity();
        
        cout << "Area is " << arr[choice]->area();
        cout << ", Perimeter is " << arr[choice]->perimeter();
        cout << ", Center of gravity is (" << xy.x << "," << xy.y << ")" << endl;
        cout << "Input 'y' to continue ";
        cin >> cont;
        cout << endl;
    }
    
    for (int i=0; i<4; i++)
        delete arr[i];	// free up dynamically allocated memory
}

int menu() {
    int choice = 0;
    while(!choice) {
        cout << "Please enter your choice: " << endl;
        cout << "\t1. Square \t2.Rectangle" << endl;
        cout << "\t3. Pentagon \t4.Hexagon" << endl;
        cin >> choice;
        
        if (choice < 1 || choice > 4) 
		choice = 0;
    }
    
    return choice;
}
