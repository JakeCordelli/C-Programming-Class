#include <iostream>
#include <cmath>
using namespace std;

// precondition: the length and width of a rectangle have been initialized
// postcondition: outputs a description of the rectangle, including the area 
void describe (double length, double width);


// precondition: length and width have been initialized
// postcondition: the value of length is replaced with new_length and 
//		  the value of width is replaced by new_width 
void changeDimensions (double &length, double &width, double new_length, double new_width);


// precondition: length and width have been initialized
// postcondition: returns the length of the diagonal of the rectangle with given length and width
double calcDiagonal (double length, double width);

// precondition: length and width have been initialized
// postcondition: returns the area of a rectangle with the given length and given width
double calcArea (double length, double width);

// draws a rectangle
// precondition: the length and width have been initialized
// postcondition: the function draws a rectangle of the given length and width, 
// 	that is filled in with the specified character. 
// 	The length and width will be rounded to the nearest integer
void drawRectangle(double length, double width, char fill);


int main() {

  	double l = 3, w = 5;

  // 1. Use the 'describe' function to display a message describing a rectangle with length and
  // 	width given by the variables 'l' and 'w'.
	cout << "The Describe Function: " << endl;
	describe(l, w);
	cout << endl;

  // 2. Use the changeDimensions function to change the length to 15 and the width to 4. Then 
  // 	use the 'describe' function to display a message describing the new rectangle 
	cout << "The changeDimensions Function: " << endl;
	changeDimensions(l, w, 15, 4);
	describe(l, w);
	cout << endl;

  // 3. Use the 'drawRectangle' function to draw the rectangle created in (3). The rectangle
  // 	should be filled in with X's 
	cout << "The drawRectangle Function: ";
	drawRectangle(l, w, 'x');

  // 4. Use the 'calcDiagonal' to calculate the length of the diagonal for the rectangle you
  // 	created in (3), and then output this value. 


  // 5. Create a function called makeSquare that works as follows.
  //    The function is a void function that takes two double arguments, a length and a width. 
  // 	The function calculates the area using the calcArea function, then changes the value 
  //    of the length and width to equal the square root of the area. This results in a square 
  //    that has the same area as the initial rectangle.

  //    Write an appropriate precondition and postcondition before the function declaration. 
  //    Call the makeSquare function, then call the 'describe' function to confirm the result 

 
  return 0;
}

// describes a rectangle with given length and width
void describe (double length, double width) {
  cout << "Dimensions (l x w): " << length << " x " << width << endl;
  cout << "Area: " << calcArea(length, width) << endl;  
}

// changes the dimensions of a rectangle 
void changeDimensions (double &length, double &width, double new_length, double new_width) {
   length = new_length;
   width = new_width;
}

// returns the length of the diagonal, using 
// the Pythagorean Theorem: a^2 + b^2 = c^2
double calcDiagonal (double length, double width) {
  double ans = sqrt(length*length + width*width);
  return ans; 
}

// returns area = length * width
double calcArea (double length, double width) {
  return length*width;
}


// draws a rectangle
void drawRectangle(double length, double width, char fill) {

  length = round(length); 
  width = round(width);

  cout << endl;
  cout << "A rectangle with dimensions " << length << " x " << width << " appears below:\n";
  for (int i = 0; i < width; i++) {	  	// for each row (corresponding to width) 
  	for (int j = 0; j < length; j++) {	//   for each column (corresponding to length)
		cout << fill;			// 	output character
  	 }
	 cout << endl;				//   go to next row	
  }
  cout << endl;
}

