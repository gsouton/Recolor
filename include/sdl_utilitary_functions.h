#ifndef __DRAW_FUN_H__
#define __DRAW_FUN_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>


#include <stdio.h>
#include <stdbool.h>
#include "game.h"
#include "recolor_solve.h"


#define NAME "recolor_sdl" // title of window
#define SIZE_BUFFER 5 // buffer of charMove
#define FONT "../data/Arial.ttf" // path to Arial.ttf
#define FONTSIZE 16
#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 600
#define MAX_COLOR_LINE 8
#define SIZE_BUTTONS 35
#define SIZE_BUTTONS_ANDROID 78
#define PERCENTAGE 80 // the percentage of the screen that will be occupied by the grid for the game
                      // the other 20% will be for the buttons and display of informations

/************** PNG **********************************/
#ifdef __ANDROID__
#define STATUS_MOVES "../data/moves_left_android.png"
#define RESTART "../data/reset_buttonAndroid.png"
#else
#define STATUS_MOVES "../data/moves_left_white.png"
#define RESTART "../data/restart_white.png"
#endif
#define GAME_OVER "../data/gameOverAndroid.png"
#define WINNING "../data/winAndroid.png"
#define QUIT "../data/quit.png"
#define RESTART_END "../data/restart_end.png"

/***************************************************/



/***** ALL colors of the game ******/
// 0 1 2 3 are defined in game.h
#define ORANGE 4
#define LIGHT_PINK 5
#define PINK 6
#define DARK_GREEN 7
#define LIGHT_BLUE 8
#define DARK_YELLOW 9
#define SHIT 10
#define VIOLET 11
#define GREEN_BLUE 12
#define WEIRD_GRAY 13
#define WEIRD_GREEN 14
#define SKIN 15
/*********************************/



typedef struct environnement *Env;



/*
@brief display message if malloc error and exit the program
* @param name of your variable
*/
void malloc_error(char* name);


/*
@brief initialize the struct environnement
* @param @ren SDL_Renderer
* @pre @p g is a valid pointer toward a game structure
*/
Env init_env(SDL_Renderer *ren, uint nb_colors, game g);

/*
@brief  will draw a colorful grid of your given game
* @param @ren SDL_Renderer
* screen_w and screen_w integer represent the width and height of the window
* @pre @p g is a valid pointer toward a game structure
* @env a valid pointer toward an environnement struct

*/
bool color_grid(SDL_Renderer *ren, int screen_w, int screen_h, Env env, game g);

/*
@brief will set the renderer to a given color
* @param @ren SDL_Renderer
* @pre color an unsigned int corresponding to a color of the game
*/
void set_color(SDL_Renderer *ren, uint color);



/*
@brief will display number of movements left and the current number
* @param @ren SDL_Renderer
* @pre @p g is a valid pointer toward a game structure
* @env a valid pointer toward an environnement struct
* screen_h and screen_w the width and height of the window
*/
void display_status(SDL_Renderer *ren, game g, Env env, int screen_w, int screen_h);

/*
@brief Rendering buttons to the window
* @param @ren SDL_Renderer
* screen_h and screen_w width and height of the window
* @pre @p g is a valid pointer toward a game structure
* @nb_color is a valid pointer toward a tab_color structure (used in solver see utilitary_functions_solver)
*/
void buttons(SDL_Renderer *ren, int screen_w, int screen_h, Env env, game g, tab_color nb_color);


/*
@brief rendering the losing screen
* @param @ren SDL_Renderer
* @pre @p g is a valid pointer toward a game structure
* @env is a valid pointer toward an environnement struct
* screen_w and screen_h widht and height of the window

*/
void display_losing_screen(SDL_Renderer *ren, game g, Env env, int screen_w, int screen_h);

/*
@brief process the click of the mouse during game
* @param @ren SDL_Renderer
* SDL_Point mouse
* @pre @p g is a valid pointer toward a game structure
* @env is a valid pointer toward an environnement struct
* @nb_color a valid pointer toward a tab_color struct
*/
void process(SDL_Renderer *ren, game g,Env env, tab_color nb_colors, SDL_Event event, bool *won);


/*
@brief  will return the number of movements left as a string for a given game

* @pre @p g is a valid pointer toward a game structure
* @charMove an array where to store the number convert as a string
*/
char *moves_left(game g, char *charMove);


/*
@brief display error message while init_env
* @ptr a valid pointer
* @msg a message
*/
void error_init(void *ptr, char * msg);

/*
@brief rendering the status of the game (number of movements left)
* @param @ren SDL_Renderer
* @pre @p g is a valid pointer toward a game structure
* @env is a valid pointer toward a game structure
*/
void set_moves_left(SDL_Renderer *ren, game g, Env env);

/*
@brief process the mouse in case of a loosing game
* @param @ren SDL_Renderer
* SDL_Point mouse
* @pre @p g is a valid pointer toward a game structure
* @env is a valid pointer toward an environnement struct
*/
bool process_game_over(SDL_Renderer *ren, game g, Env env, SDL_Event event, bool *won);


/*
@brief will check if you loose regarding the number of moves
* @g a valid pointer toward a game struct
*/
bool lost(game g);


/*
@brief will display a winning screen
* @ren a valid pointer toward renderer
* @g valid pointer toward game struct
* @env valid pointer toward environnement struct
* screenw and screen_h size of window
* nb_color a valid pointer toward a tab_color struct
*/
void display_winning_screen( SDL_Renderer *ren, game g, Env env, int screen_w, int screen_h, tab_color nb_color);


/*
@brief free the memory that were allocated
* @param @window a SDL_Window
* @param @ren SDL_Renderer
* @pre @p g is a valid pointer toward a game structure
* @pre @env valid pointer toward an environnement structure

*/
void clean(SDL_Window* window, SDL_Renderer* ren, Env env, game g, tab_color nb_color);


/*
@Brief will make sure that the game cannot receive more than 16 colors
* nb of color
*/
void control_max_color(uint nb);


/*
@Brief Check if pointer is valid if not return error message and quit the program
* @ptr a pointer to a variable or structure
* @name the name of the check_pointer
* @function the name of the function
*/
void check_pointer(void *ptr, char *name, char *function);


bool check_collision(int pointer_x, int pointer_y, int object_x, int object_y, int object_width, int object_height);

void buttons_android(SDL_Renderer *ren, int screen_w, int screen_h, Env env, game g, tab_color nb_color, uint size_colors);

void display_winning_screenAndroid(SDL_Renderer *ren, game g, Env env, int screen_w, int screen_h, tab_color nb_color, uint size_colors);

bool process_winning(SDL_Window *window, SDL_Renderer *ren, game g, Env env, tab_color nb_colors, SDL_Event event, bool *won);





#endif
