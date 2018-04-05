// File Name: rock_with_stubs.cpp
// Authors: Put group member names here 
// Description: Rock, Paper, Scissors Game
// Last Changed:   

// Assignment: The functions 'rps_computer', 'rps_player', 'find_winner', and
//   'play_again' are stubs. Modify the functions to complete the Rock,
//   Paper, Scissors Game    
//
// In this game, the player plays Rock, Paper, Scissors against the computer.
// The winner is determined by the fact that Rock crushes Scissors, 
// Paper covers Rock, and Scissors cuts Paper. 


#include <iostream>
#include <ctime>
#include <cctype>
using namespace std;

// randomly returns either R, P, or S for Rock, Paper, or Scissors
char rps_computer();

// Prompts the user to enter an R, P, or S, for Rock, Paper, or Scissors
// You should use the predefined toupper function to convert what
// the user enters to uppercase
// The user is repeatedly prompted to enter an R, P, or S until a valid
// character is entered
char rps_player();

// outputs what the player and computer plays, and returns a character
// corresponding to the winner with 'P' = player, 'C' = computer, and
// 'T' = tie   
// For example, if player is 'R' (rock) and the computer is 'S' scissors,
// the function will output: "Rock beats scissors" and returns a 'P' 
char find_winner(char player, char computer);

// prompts the user and returns true if the user wants to play again; 
// if not, the function returns false 
bool play_again();

int main2() {
  srand(time(NULL));
  char computer, player, winner;
  int p_count = 0, c_count = 0;
  bool again;

  do {

	cout << endl<<"Player Score: " << p_count << ", Computer Score: ";
	cout << c_count << endl;
	cout << "==========================================" << endl;

  	computer = rps_computer();
  	player = rps_player();
    winner = find_winner(player, computer);

	if (winner == 'P') {
		p_count++;	
	} else if (winner == 'C') {
		c_count++;
	}

  	again = play_again();
 
  } while (again);
  cout << endl<<"Thankyou for playing! The final score of the game is " << p_count-1 << " to " << c_count<<endl;
}


// This function is a stub; modify the function so that it
// randomly returns either R, P, or S for Rock, Paper, or Scissors
char rps_computer() {
	int X = 0;
	X = rand() % (3 - 1 + 1) + 1;
	if (X == 1)
	{
		return 'R';
	}
	else if (X == 2){
		return 'P';
	}
	else{
		return 'S';
	}
}


// This function is a stub; modify the function so that it
// prompts the user to enter an R, P, or S, for Rock, Paper, or Scissors
// Note that the predefined 'toupper' function is used to convert what
// the user enters to uppercase
// The user is repeatedly prompted to enter an R, P, or S until a valid
// character is entered
char rps_player() {
	char x;
	cout << "Enter in a Rock (r), Paper (p), or Scissor(s)"<<endl;
	cin >> x;
	if (x == 'r')
	{
		return 'R';
	}
	else if (x == 'p'){
		return 'P';
	}
	else if (x == 's'){
		return 'S';
	}
}

// this function is a stub; modify the function so that it
// outputs what the player and computer plays, along with the winner.
// The function returns a 'P' if the player wins, a 'C' if the
// computer wins, and a 'T' if it is a tie
char find_winner(char player, char computer) {
	cout << "The player plays: " << player << endl;
	cout << "The computer plays: " << computer << endl;

	/*
	if ('p'&&'s')
	{
		return 'S';
	}
	if ('s' && 'r')
	{
		return 'R';
	}
	if ('r'&& 'p')
	{
		return 'P';
	}
	*/
}

// This function is a stub; modify the function so that it
// prompts the user and returns true if the user wants to play again; 
// if not, the function returns false 
bool play_again() {
	int x;
	cout << "Would you like to play again? Enter 1 for yes or 0 for no"<<endl;
	cin >> x;
	if (x == 1)
	{
		return true;
	}

	if (x == 0)
	{
		return false;
	}
}


