/*
1. Write a program that finds the average of a set of grades entered by the user. 
   The program prompts the user to enter a grade, or the number -1 when finished. 
   (Note: this value of -1 is sometimes referred to as a sentinel value; in general a 
   sentinel value is a special value used to terminate a loop). The user 
   repeatedly enters a grade until a -1 is entered. At that point, the program proceeds 
   as follows: If no valid grade has been entered, the program outputs that no valid 
   grades have been entered. Otherwise, the program outputs the number of grades 
   entered, as well as the average (mean) grade	entered. 

   For example, if the user enters  95, 87, 92, and a -1, then the program outputs 
   that 3 grades have been entered, and that the average is 91.33 
   (Note: it is OK if your program shows more than 2 numbers after the decimal, 
   but your program must output a decimal value average if the average is not an integer). 

   Notes: When writing any non-trivial program, a good strategy is to break the	program 
   into a series of smaller programming tasks, complete and test each one, and then 
   continue.  Programmers almost never write an entire program 	all at once! 
   Follow the steps below to complete the program: 

   1.	Write a program that prompts the user to enter a grade, or a -1 if finished. 
	(In this step, the program prompts the user only one time). 
        The program outputs the number the user entered. 
   2.	Modify the program in (1) so that the steps in (1) are repeated until the user enters a -1. 
   3.	Modify the program in (2) to count the number of grades the user has entered. 
	(Note that you do not count a -1).  After the user enters a -1, the program 
	outputs the number of valid grades entered.
   4.	Modify the program in (3) as follows: If no valid grades are entered, 
 	the program outputs No valid grades have been entered. Otherwise, the program 
	calculates the average grade and outputs this average.
*/

#include <iostream>
using namespace std;

int main15() {

  int grade;
  double sum=0; //This calculates the sum of all of the grades. It is a double to prevent integer division
  //Setting a counter
  int count = 0; //Counts the number of grades entered in order to calculate the average of the grades

  //Do this 
  do{
	  cout << "Please enter the next grade, or a -1 if finished: ";
	  cin >> grade;
	  count++;
	  sum = sum+grade; //same as sum=sum+grade
	  cout << "You entered a: " << grade << endl;
  } while (grade != -1);
  //Until the user enters a -1
  cout << "The sum of all of the grades is: " << sum << endl;
  cout << "The number of grades you entered is: " << count-1 << endl; //the count subtracts the last input, which is the negative one
  //cout << "The average grade is: " << sum/count << endl;
  if (count == 0){
	  cout << "No valid grades entered\n";
  }
  else{
	  cout << "The average grade is: " << sum/count << endl;
  }
  return 0;
}
