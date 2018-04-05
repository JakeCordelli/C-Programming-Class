#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <cstdlib>
#include "SDL.h"
using namespace std;

// Description: This is a one-player pong game. We will modify the 'bounce' function,
// and the 'we_missed_one' function to complete the game. We will also read in the
// 'pong_scores.txt' file to specify the previous scores before each game

// GLOBAL VARIABLES
const int MAX_X = 640;
const int MAX_Y = 480;
const int MAX_BALLS = 10;
const int PLAYER_SIZE = 500;

// precondition: a number of balls equal to 'size' are in play
// postcondition: the direction of the balls change if they hit either of the
void bounce(int balls[][2], int directions[][2], int size);


// precondition: a number of balls equal to 'size' are in play
// postcondition: returns true if a ball gets passed the paddle with the
//   given 'X' position; the size of the paddle is PLAYER_SIZE
bool we_missed_one(int X, int balls[][2], int directions[][2], int size);



void reset_balls(int balls[][2], int directions[][2]);

// draws a pixel at the point (mouseX, mouseY) in the corresponding color 'col'
void draw_player(Uint32 * pixels, int mouseX, int mouseY, int col);


void draw_balls(Uint32 *pixels, int balls[][2], int col, int size);

// if necessary, adjusts the values of X and Y to reflect valid screen points
// X must be IN (1, 630) and Y  must be in (1, 478)
void adjustXY(int &X, int &Y);

// pixels matching background color are set to lighter color for several iterations and then cleared
void update_pixels(Uint32 * pixels, int bg);


void move_balls(Uint32 *pixels, int balls[][2], int ball_directions[][2], int size);


int main(int argc, char ** argv)
{
    
    /* display welcome message and have user select difficulty */
    cout << "Welcome to the PONG game!" << endl;

    
    char a;
    // TO DO: open file 'pong_scores' and display the previous scores
    
    // declare input file stream object named 'fin'
	ifstream fin;

    // open "pong_scores.txt"
	fin.open("pong_scores.txt");

    // if file has been opened,
    //  read and display contents
	if (!fin.fail()){
		fin.get(a);
		while (!fin.eof()){
			cout << a; 
			fin.get(a);
		}
	}

    cout << endl << endl;
    cout << "Please enter your name: ";
    char name[100] = "";
    int i = 0;
    cin.get(a);
    while (a!='\n') {
        name[i] = a;
        i++;
        cin.get(a);
    }
    name[i] = '\0';
    
    cout << "Thank you, " << name << ". Press any key to begin play...\n";
    cin.get(a);
    
    
    // open file for appending
    ofstream fout;
    fout.open("pong_scores.txt", fstream::app);
    
    
    /* Initialize SDL variables */
    SDL_Event event;
    
    SDL_Window * window = SDL_CreateWindow("CSC-210 Pong Program",
                                           SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, MAX_X, MAX_Y, 0);
    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Texture * texture = SDL_CreateTexture(renderer,
                                              SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, MAX_X, MAX_Y);
    Uint32 * pixels = new Uint32[MAX_X * MAX_Y ];
    memset(pixels, 255, MAX_X * MAX_Y * sizeof(Uint32));
    int bg = pixels[0];
    SDL_Surface *surface = SDL_CreateRGBSurface(0, MAX_X, MAX_Y, 32, 0, 0, 0, 0);
    
    srand(time(0));
    
    // declare color variables
    int col_player = 0, col_goal = 0;
    col_player = SDL_MapRGB(surface->format, 0, 0, 0);  // player is black
    col_goal = SDL_MapRGB(surface->format, 255, 0, 0);  // goal is red
    
    /* Main Variables */
    int player[2] = {205, 640};        // x,y position of the player (the paddle)
    int balls[MAX_BALLS][2];           // x,y position of each ball
    int ball_directions[MAX_BALLS][2]; // (x,y) direction of movement for each ball
   
    // randomize the positions of the balls
    reset_balls(balls, ball_directions);
    
    char direction = 'r';  // u = up, d = down, l = left, r = right
    bool quit = false;
    long int score = 0;
    
    /* Display initial game */
    draw_player(pixels, player[0], player[1], col_player);
        
//    draw_goal(pixels, goalX, goalY, col_goal);
    SDL_UpdateTexture(texture, NULL, pixels, 640 * sizeof(Uint32));
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
    
    
    /* player selects difficulty */
    int delay = 0;
    int num_balls = 1;
    
    cout << "Click the mouse to begin...\n";
    do {
        SDL_WaitEvent(&event);
    } while (event.type != SDL_MOUSEBUTTONDOWN);
    
    while (!quit)
    {
        SDL_UpdateTexture(texture, NULL, pixels, 640 * sizeof(Uint32));
        SDL_WaitEventTimeout(&event, delay);
        
        switch (event.type) {
                
            /* get the direction*/
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_LEFT:
                        direction = 'l';
                        break;
                    case SDLK_RIGHT:
                        direction = 'r';
                        break;
                }
                break;
            case SDL_QUIT:
                quit = true;
                break;
        }
        
        /* Move the player appropriately */
        if (direction != 'n') {
            if (direction == 'l') player[0]--;
            else if (direction == 'r') player[0]++;
            score++;
            adjustXY(player[0], player[1]);
            update_pixels(pixels, bg);
            draw_player(pixels, player[0], player[1], col_player);
   
            move_balls(pixels, balls, ball_directions, num_balls);
            draw_balls(pixels, balls, col_goal, num_balls);
    
            
            // check whether we've missed any, in which case, game over
            bool missed = we_missed_one(player[0], balls, ball_directions, num_balls);
            if (missed) {
                cout << "FINAL SCORE = " << score << endl;
                fout << name << ": " << score << endl;
                cout << "Press 'c' to continue to 'q' to quit\n";
                bool need_response = true;
                
                while (need_response) {
                
                    SDL_WaitEvent(&event);

                    switch (event.type) {
                        
                        case SDL_KEYDOWN:
                            switch (event.key.keysym.sym) {
                                case SDLK_q:
                                    quit = true;
                                    need_response = false;
                                    break;
                                case SDLK_c:
                                    need_response = false;
                                    break;
                            }
                    }
                }
                
                direction = 'n';
                score = 0;
                num_balls = 1;
                reset_balls(balls, ball_directions);
                
                
            }

            // TO DO: if score > 500, use 2 balls
			if (score > 500){
				num_balls = 2;
			}
            
            
            // bounce if appropriate
            bounce(balls, ball_directions, num_balls);
        
            if (score %100 == 0) cout << "Score = " << score << endl;
    
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, texture, NULL, NULL);
            SDL_RenderPresent(renderer);
        }
        
    }
    
    delete[] pixels;
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
 
    fout.close();
    return 0;
}


// TO DO
// precondition: a number of balls equal to 'size' are in play
// postcondition: the direction of the balls change if they hit either of the
//  4 walls
void bounce(int balls[][2], int directions[][2], int size) {
    
    // for each ball
    for (int i= 0; i < size; i++) {
        // if we've reached the bottom (MAX_Y), change direction
		if (balls[i][1] >= MAX_Y){
			directions[i][1] = -1; 
		}
        // if we've reached the top (1), change direction
		if (balls[i][1] <=1){
			directions[i][1] = 1;
		}
        // if we've reached the right-hand side (MAX_X), change direction
		if (balls[i][0] >= MAX_X){
			directions[i][0] = -1;
		}
        // if we've reached the left-hand side (1), change direction
		if (balls[i][0] <= 1){
			directions[i][0] = 1;
		}
    }
}

// TO DO
// precondition: a number of balls equal to 'size' are in play
// postcondition: returns true if a ball gets passed the paddle with the
//  given 'X' position; the size of the paddle is PLAYER_SIZE
bool we_missed_one(int X, int balls[][2], int directions[][2], int size) {
    
    // for each ball
    for (int i= 0; i < size; i++) {

		int diff = abs(X - balls[i][0]);
		if (balls[i][1] >= MAX_Y && diff>PLAYER_SIZE / 2) {
			return true;
		}




        // if the ball hits the bottom and is not caught by the paddle,
        // then we missed one (so return true)
        
    }

    return false;
}

// TO DO: change default y-direction
void reset_balls(int balls[][2], int directions[][2]) {
    for (int index = 0; index < MAX_BALLS; index++) {
      balls[index][0] = 200 + rand()% 201 - 100;   // x position
      balls[index][1] = 50 +rand()%101 -50;	   // y position
      directions[index][0] = 1;			   // x direction
      directions[index][1] = 1;			   // y direction
    }
}


// updates player pixels, which includes ~10 trailing pixels from current location
void update_pixels(Uint32 * pixels, int bg) {
    for (int i = 0; i < 640 * 480; i++) {
        if (pixels[i] == 0) {
            pixels[i] = 10;
        }
        else if (pixels[i] < bg) {
            pixels[i]++;
        }
        if (pixels[i] > 20) pixels[i] = bg;
    }
}

// adjusts X and Y so that they are within the window
void adjustXY(int &X, int &Y) {
    if (X <= 0) X = 1;
    else if (X > MAX_X) X = MAX_X;
    
    if (Y <= 0) Y = 1;
    else if (Y > MAX_Y) Y = MAX_Y;
}

// randomly moves the goal if difficulty != 1
// which is currently enforced by adjustXY()
// optionally, you can have the goal respond to the 'direction' that the player is
// moving, which will be 'u', 'd', 'l', or 'r' for up, down, left, or right,
// respectively
void move_balls(Uint32 *pixels, int balls[][2], int ball_directions[][2], int size) {
    for (int i = 0; i < size;i++) {
        balls[i][0] += ball_directions[i][0];
        balls[i][1] += ball_directions[i][1];
        adjustXY(balls[i][0], balls[i][1]);
    }
}

// draws the pixels
void draw_player(Uint32 * pixels, int mouseX, int mouseY, int col) {
    int X,Y;
    for (int addY = -5; addY <= 5; addY++) {
        for (int addX = -(PLAYER_SIZE/2); addX <= PLAYER_SIZE/2; addX++) {
            X = mouseX + addX;
            Y = mouseY + addY;
            adjustXY(X,Y);
            pixels[(Y) * 640 + X] = col;
        }
    }
}

// draws the goal: includes current location with 2 surrounding points on all sides
void draw_balls(Uint32 *pixels, int balls[][2], int col, int size) {
    int X,Y;

  for (int i = 0; i < size; i++) {
    for (int addY = -2; addY <= 2; addY++) {
        for (int addX = -3; addX <= 3; addX++) {
            X = balls[i][0] + addX;
            Y = balls[i][1] + addY;
            adjustXY(X,Y);
            pixels[(Y) * 640 + X] = col;
        }
    }
  }
}


