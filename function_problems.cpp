#include <iostream>
#include <cmath>
using namespace std;

// returns the minimum of the numbers x and y
// x - the value of the first number
// y - the value of the second number  
// returns 'true' if the integer 'x' is prime
// otherwise, the function returns 'false'
bool isPrime(int x);
int min(int v, int w); 
double hippo(double x);
double Max(double r, double z);

int main() {
	// 1. Recall that the 'sqrt' function returns the square root of its argument
	//    Use the sqrt function to output the square root of 21, in the form
	//    "the square root of 21 is 4.58258" (Note that the cmath library is
	//    already included) 
	double theSqrtofX = hippo(21);
	cout << "The square root of 21 is " << theSqrtofX << endl;


	// 2. The programmer-defined function 'min', whose declaration is given
	//    above, returns the minimun value of its two integer arguments. Use
	//    the 'min' function to output the minimum value of 21 and 10, in the
	//    form "the minimum of 21 and 10 is 10"
	double solution = min(21, 10);
	cout << "The minimum value of 21 and 10 is " << solution << endl;


	// 3. The programmer-defined function 'isPrime' returns true if the value
	//    of its argument is a prime number, and returns false otherwise.
	//    Use the 'isprime' function to determine whether or not the number 103
	//    is prime. You should then output either "103 is prime" or
	//    "103 is NOT prime".
	int result = isPrime(103);
	cout << "The number 103 ";
	if (result == 1)
		{
			cout << " is prime" << endl;
		}
			else
		{
			cout << " is NOT prime"<<endl;
		}


	// 4. Create a programmer-defined function named 'max' that returns the
	//    maximum value of its two integer arguments. The function does not
	//    output anything, but returns the maximum value. In order to do this,
	//    you must write both the function declaration (which goes before main)
	//    and the function definition (which goes after main). Then use this
	//    function to determine the max of 50 and 75, and output this value.
	double maxSolution = Max(50, 70);
	cout << "The minimum value of 50 and 70 is " << maxSolution << endl;
 }


															//These are where all of the functions are for the above outputs
					//This function returs the largest of the numbers x and y
double Max(double r, double z){
if (r > z) {
	return r;
}
else
{
	return z;
}
return 0;
 }


					//This function returns the minimum of the numbers x and y
 int min(int v, int w) {
 if (v > w) {
 return v;
 }
 else
 {
 return w;
 }
 return 0;
 }


					// This function determines whether or not the integer x is prime
 bool isPrime(int x) {
 x = abs(x);
 if (x == 2) return true;   // 2 is prime
 // for each number between 2 and x
 for (int i = 2; i < x; i++) {
 // if x is even divisble by that number, then x is not prime,
 // so return false
 if (x % i == 0) return false;
 }
 // x is not even divisble by any number between 2 and x, so it is prime
 return true;
 }

					//This function is to figure out the square root of a number
	double hippo(double s) {
		double squareRoot = sqrt(s);
		return squareRoot;
	}

