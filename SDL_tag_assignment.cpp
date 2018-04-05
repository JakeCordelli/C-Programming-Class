#include <iostream>
#include <string>
#include <ctime>
#include "SDL.h"
using namespace std;

// Description: This program implements a simple 'tag' game where the player
// uses the arrow keys to chase and catch the red point. In 'easy' mode
// the red point is stationary; in 'medium' mode the goal is a moving target;
// in 'difficult' mode the player moves very quickly

// Assignment: The function select_difficulty() is a stub. Modify its
// function definition to prompt the user to select a difficulty level,
// with 1 = easy, 2 = medium, and 3 = hard. The function returns the integer
// entered by the user. The user must enter a valid number between 1 and 3.
// Therefore, if an invalid number is entered, the user is repeatedly asked
// to enter a number again until a valid number is entered.

// Challenge Problem: In 'medium' and 'difficult' mode the red point moves
// randomly, and is not really *that* difficult to catch. Modify the update_goal
// function so that the red point 'runs away' from the player. However, the point
// should not be impossible to catch.

// displays welcome message
void welcome();

// prompts the user for the level of difficulty (either 1, 2, or 3)
// and returns the integer
int select_difficulty();

// draws a pixel at the point (mouseX, mouseY) in the corresponding color 'col'
void draw_pixels(Uint32 * pixels, int mouseX, int mouseY, int col);

// if necessary, adjusts the values of X and Y to reflect valid screen points
// X must be IN (1, 630) and Y  must be in (1, 478)
void adjustXY(int &X, int &Y);

// pixels matching background color are set to lighter color for several iterations and then cleared
void update_pixels(Uint32 * pixels, int bg);

// returns TRUE if the player tags the red point; a tag is awarded if (X,Y) is within 2 pixels of (goalX, goalY)
bool player_wins(int X, int Y, int goalX, int goalY);

// draws the (goalX, goalY) point in the specified color
void draw_goal(Uint32 *pixels, int goalX, int goalY, int col);

// if the player wins, randomly color random points on the screen
void winning_screen(Uint32 * pixels, SDL_Surface *surface, SDL_Renderer * renderer, SDL_Texture * texture);

// if difficulty is not 0, then the point moves 1 unit away from (X,Y)
void update_goal(Uint32 *pixels, int &X, int &Y, int difficulty, char direction);

int main (int argc, char ** argv)
{
    /* Initialize SDL variables */
    SDL_Event event;
    
    SDL_Window * window = SDL_CreateWindow("CSC-210 Tag Program",
                                           SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Texture * texture = SDL_CreateTexture(renderer,
                                              SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, 640, 480);
    Uint32 * pixels = new Uint32[640 * 480];
    memset(pixels, 255, 640 * 480 * sizeof(Uint32));
    int bg = pixels[0];
    SDL_Surface *surface = SDL_CreateRGBSurface(0, 640, 480, 32, 0, 0, 0, 0);
    
    srand(time(NULL));
    
    // declare color variables
    int col_player = 0, col_goal = 0;
    col_player = SDL_MapRGB(surface->format, 0, 0, 0);  // player is black
    col_goal = SDL_MapRGB(surface->format, 255, 0, 0);  // goal is red
    
    /* Initial player and goal positions */
    int X = 5, Y = 5, goalX = 350, goalY = 300;
    
    char direction = 'r';  // u = up, d = down, l = left, r = right
    bool quit = false;
    bool winner = false;
    long int score = 0;
    
    /* Display initial game */
    draw_pixels(pixels, X, Y, col_player);
    draw_goal(pixels, goalX, goalY, col_goal);
    SDL_UpdateTexture(texture, NULL, pixels, 640 * sizeof(Uint32));
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
    
    /* display welcome message and have user select difficulty */
    welcome();
    
    /* player selects difficulty */
    int difficulty = select_difficulty();
    int delay = 1;
    if (difficulty == 3) delay = 0;
	if (difficulty == 2) delay = 5;
	if (difficulty == 1) delay = 10;

    cout << "Click the mouse to begin...\n";
    do {
        SDL_WaitEvent(&event);
    } while (event.type != SDL_MOUSEBUTTONDOWN);

    while (!quit)
    {
        SDL_UpdateTexture(texture, NULL, pixels, 640 * sizeof(Uint32));
        SDL_WaitEventTimeout(&event, delay);
        score++;
        switch (event.type) {
                
                /* get the direction*/
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_DOWN:
                        direction = 'd';
                        break;
                    case SDLK_UP:
                        direction = 'u';
                        break;
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
            if (direction == 'u') Y--;
            else if (direction == 'd') Y++;
            else if (direction == 'l') X--;
            else if (direction == 'r') X++;
            
            adjustXY(X, Y);
            update_pixels(pixels, bg);
            draw_pixels(pixels, X, Y, col_player);
            update_goal(pixels, goalX, goalY, difficulty, direction);
            draw_goal(pixels, goalX, goalY, col_goal);
            
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, texture, NULL, NULL);
            SDL_RenderPresent(renderer);
        }
        
        /* do we have a winner? */
        winner = player_wins(X, Y, goalX, goalY);
        if (winner) {
            quit = true;
            winning_screen(pixels, surface, renderer, texture);
        }
        
        if (score %100 == 0) cout << "Score = " << score << endl;
        
    }
    
    if (winner) {
        cout << "------------------------------\n";
        cout << "Congratulations, Player Wins!\n";
        cout << "Score = " << score << endl;
    }
    delete[] pixels;
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}

void welcome() {
    cout << "Use the arrow keys to catch the red dot.\n";
    cout << "The player with the lowest score wins!\n";
}

// TO DO: This function is a stub; modify this function to
// prompt the user to select a level of difficulty. The user
// is repeatedly prompted until either a 1 (easy), 2 (medium),
// or 3 (hard) is entered
int select_difficulty() {
	double difficulty;
	if (difficulty < 0);
	{
		cout << "Select a difficulty (1 (easy),2 (medium), or 3 (hard)):" << endl;
		cin >> difficulty;
	}
	if (difficulty >3);
	{
		cout << "Select a difficulty (1 (easy),2 (medium), or 3 (hard)):" << endl;
		cin >> difficulty;
	}
	cout << "The difficutly you selected is: " << difficulty << endl;
	return difficulty;


void winning_screen(Uint32 *pixels, SDL_Surface *surface, SDL_Renderer * renderer, SDL_Texture * texture) {
    int X, Y, col;
    for (int i = 0; i < 3000; i++) {
        X = rand() % 629+1;
        Y = rand() % 477+1;
        col = SDL_MapRGB(surface->format, rand() % 256, rand() % 256, rand() % 256);
        draw_pixels(pixels, X, Y, col);
        SDL_UpdateTexture(texture, NULL, pixels, 640 * sizeof(Uint32));
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }
}

// player wins if he/she is within 2 pixels of the goal
bool player_wins(int X, int Y, int goalX, int goalY) {
    if (abs(X - goalX) <= 2 && abs(Y - goalY) <= 2) return true;
    return false;
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
    if (X < 1) X = 1;
    else if (X > 630) X = 630;
    
    if (Y < 1) Y = 1;
    else if (Y > 478) Y = 478;
}

// randomly moves the goal if difficulty != 1
// which is currently enforced by adjustXY()
// optionally, you can have the goal respond to the 'direction' that the player is
// moving, which will be 'u', 'd', 'l', or 'r' for up, down, left, or right,
// respectively
void update_goal(Uint32 *pixels, int &X, int &Y, int difficulty, char direction) {
    if (difficulty == 1) return;
    int changex = rand() % 2 * 2 - 1;   //changex is either -1 or +1
    int changey = rand() % 2 * 2 - 1;   // changey is either -1 or + 1
    X = X + changex*2;  // goal will move 2 pixels to the left or right
    Y = Y + changey*2; // goal will move 2 pixels up or down
    adjustXY(X, Y);
}

// draws the pixels
void draw_pixels(Uint32 * pixels, int mouseX, int mouseY, int col) {
    pixels[mouseY * 640 + mouseX] = col;
    pixels[mouseY * 640 + mouseX-1] = col;
    pixels[mouseY * 640 + mouseX+1] = col;
    pixels[(mouseY+1) * 640 + mouseX] = col;
    pixels[(mouseY-1) * 640 + mouseX] = col;
    pixels[(mouseY+1) * 640 + mouseX-1] = col;
    pixels[(mouseY+1) * 640 + mouseX+1] = col;
    pixels[(mouseY-1) * 640 + mouseX-1] = col;
    pixels[(mouseY-1) * 640 + mouseX+1] = col;
}

// draws the goal: includes current location with 2 surrounding points on all sides
void draw_goal(Uint32 *pixels, int goalX, int goalY, int col) {
    draw_pixels(pixels, goalX, goalY, col);
    draw_pixels(pixels, goalX+1, goalY, col);
    draw_pixels(pixels, goalX-1, goalY, col);
    draw_pixels(pixels, goalX, goalY-1, col);
    draw_pixels(pixels, goalX + 1, goalY-1, col);
    draw_pixels(pixels, goalX - 1, goalY-1, col);
    draw_pixels(pixels, goalX, goalY+1, col);
    draw_pixels(pixels, goalX + 1, goalY+1, col);
    draw_pixels(pixels, goalX - 1, goalY+1, col);
}

