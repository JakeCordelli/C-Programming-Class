#include <iostream>
#include "SDL.h"
using namespace std;

// Description: This program allows the user to draw on the window using the mouse.

// The program responds to the following keys:
// 'c' - clears the canvas
// 'r' - changes the color to red (function is a stub)
// 'g' - changes the color to green (function is a stub)
// 'b' - changes the color to blue (function is a stub)
// 's' - changes to a randomly selected color (function is a stub)
// 'f' - fills in the screen with the current color (optional; function is a stub)

// Assignment: Complete the function definitions for set_red, set_green, set_blue, and
// set_surprise. Note that these functions all use call by reference, so changing the
// parameters in the function will change the values of the corresponding arguments

// Challenge Problem (optional): Complete the 'fill' function allowing the user to
//    fill in the screen


// precondition: the user is ready to change the color to red
// postcondtion: the r,g,b, values are changed to 255, 0, and 0, respectively
void set_red(int &r, int &g, int &b);

// precondition: the user is ready to change the color to green
// postcondition: the r,g,b, values are changed to 0, 255, and 0, respectively
void set_green(int &r, int &g, int &b);

// precondition: the user is ready to change the color to blue
// postcondition: the r,g,b, values are changed to 0, 0, and 255
void set_blue(int &r, int &g, int &b);

// precondition: the user is ready for a surprise color
// postcondition: the arguments r, g, and b are each set to a random
//      integer between 0 and 255
void set_surprise(int &r, int &g, int &b);

// precondition: the user wants to fill the screen
// postcondition: the screen is set to the specified color (col)
void fill(Uint32 * pixels, int col);

// precondition: the user wants to draw a pixel
// postcondition: draws the pixels at mouse position (mouseX, mouseY)
//  using the specified color (col)
void draw_pixels(Uint32 * pixels, int mouseX, int mouseY, int col);


int main (int argc, char ** argv)
{
    bool leftMouseButtonDown = false;
    bool quit = false;
    SDL_Event event;
    
    SDL_Window * window = SDL_CreateWindow("CSC-210 Paint Program",
                                           SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
    
    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Texture * texture = SDL_CreateTexture(renderer,
                                              SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, 640, 480);
    Uint32 * pixels = new Uint32[640 * 480];
    
    // sets background color to black
    memset(pixels, 255, 640 * 480 * sizeof(Uint32));
    
    SDL_Surface *surface = SDL_CreateRGBSurface(0,640,480,32,0,0,0,0);
    
    // declare color variables
    int red = 0, green = 0, blue = 0, col = 0;
    
    
    while (!quit)
    {
        SDL_UpdateTexture(texture, NULL, pixels, 640 * sizeof(Uint32));
        SDL_WaitEvent(&event);
        
        switch (event.type)
        {
            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    leftMouseButtonDown = false;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    leftMouseButtonDown = true;
                }
            case SDL_MOUSEMOTION:
                if (leftMouseButtonDown)
                {
                    int mouseX = event.motion.x;
                    int mouseY = event.motion.y;
                    
                    //cout << "Mouse button pressed at (X,Y) = ";
                    //cout << "(" << mouseX << ", " << mouseY << ")" << endl;
                    
                    /* set the pixel color */
                    col = SDL_MapRGB(surface->format, red,green,blue);
                    
                    /* draw the pixels */
                    draw_pixels(pixels, mouseX, mouseY, col);
                    
                    
                }
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_r:
                        set_red(red, green, blue);
                        break;
                    case SDLK_g:
                        set_green(red, green, blue);
                        break;
                    case SDLK_b:
                        set_blue(red, green, blue);
                        break;
                    case SDLK_c:
                        memset(pixels, 255, 640 * 480 * sizeof(Uint32));
                        break;
                    case SDLK_s:
                        set_surprise(red, green, blue);
                        break;
                    case SDLK_f:
                        fill(pixels, col);
                }
                break;
            case SDL_QUIT:
                quit = true;
                break;
        }
        
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }
    
    delete[] pixels;
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}

// TO DO: The functions below are stubs; complete the functions as indicated
// to allow the user to change the colors. You should only change these
// function definitions and not change anything in main

// precondition: the user is ready to change the color to red
// postcondition: the r,g,b, values are changed to 255, 0, and 0, respectively
void set_red(int &r, int &g, int &b) {
    cout << "set_red function called\n";
	r = 255;
	g = 0;
	b = 0;
	
}

// precondition: the user is ready to change the color to green
// postcondition: the r,g,b, values are changed to 0, 255, and 0, respectively
void set_green(int &r, int &g, int &b) {
    cout << "set_green function called\n";
	int green = 255;
	r = 0;
	g = 255;
	b = 0;
}

// precondition: the user is ready to change the color to blue
// postconditino: the r,g,b, values are changed to 0, 0, and 255
void set_blue(int &r, int &g, int &b) {
    cout << "set_blue function called\n";
	int blue = 255;
	r = 0;
	g = 0;
	b = 255;
}

// precondition: the user is ready for a surprise color
// postcondition: the arguments r, g, and b are each set to a random
//  integer between 0 and 255
void set_surprise(int &r, int &g, int &b) {
    cout << "set_surprise function called\n";
}

// (optional)
// precondition: the user wants to fill the screen
// postcondition: the screen is set to the specified color (col)
// This stub currently fills in the 10th row
// Note that the window is 640 pixels across and 480 pixels up and down
void fill(Uint32 * pixels, int col) {
    
    int row = 10;
    // for each pixel in given row (column 0 - 639)
    for (int column = 0; column < 640; column++) {
        draw_pixels(pixels, column, row,col);
    }
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