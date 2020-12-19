#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include "../include/game.h"
#include "../include/game_io.h"
#include "../include/game_rand.h"
#include "../include/sdl_utilitary_functions.h"
#include "../include/recolor_solve.h"


int main(int argc, char *argv[]){

srand(time(NULL));

uint width = SIZE;
uint height = SIZE;
uint max_moves = 0;
uint max_color = NB_COLORS;

game g = NULL;
#ifdef __ANDROID__
g = game_random_ext(5, 5, false, 10, 16);
#else
switch (argc) {
  case 1:
    g = game_load("../data/solver/default_game.rec");
    assert(g);
    break;
  case 2:
    g = game_load(argv[1]);
    assert(g);
    break;
  case 3:
    fprintf(stderr, "error usage \n");
    exit(EXIT_FAILURE);
  case 4:
    width = atoi(argv[1]);
    height = atoi(argv[2]);
    max_moves = atoi(argv[3]);

    g = game_random_ext(width, height, false, max_color, max_moves);
    assert(g);
    break;

  case 5:
    width = atoi(argv[1]);
    height = atoi(argv[2]);
    max_moves = atoi(argv[3]);
    max_color = atoi(argv[4]);
    control_max_color(max_color);

    g = game_random_ext(width, height, false, max_color, max_moves);
    assert(g);
    break;
  case 6:
    width = atoi(argv[1]);
    height = atoi(argv[2]);
    max_moves = atoi(argv[3]);
    max_color = atoi(argv[4]);
    control_max_color(max_color);

    bool wrap = false;
    if(strcmp(argv[5] ,"S") == 0){
      wrap = true;
    }
    g = game_random_ext(width, height, wrap, max_color, max_moves);
    assert(g);
    break;
  default:
    break;

}
#endif




tab_color nb_color = find_color(g); // search the colors in the game g
uint colors = number_of_colors(nb_color); // get the numbers of colors of the game g


SDL_Window *window = NULL; // create a pointer window
SDL_Renderer *ren = NULL; //create a pointer rendere
Env env = NULL; // create an env pointer

/*****************************************************  SDL INITIALIZATION  ****************************************************************************/
/*
*video
*texte TTF
*IMG loading
*/

if(SDL_Init(SDL_INIT_VIDEO) != 0){ // init video for window and display
  fprintf(stderr, "SDL_Init failure; %s\n", SDL_GetError());
  exit(EXIT_FAILURE);
}

if(TTF_Init() != 0){ // init ttf for text
  fprintf(stderr, "TTF_Init error %s\n", SDL_GetError());
  exit(EXIT_FAILURE);
}

if (IMG_Init(IMG_INIT_PNG & IMG_INIT_PNG) != IMG_INIT_PNG){
  fprintf(stderr, "IMG_Init PNG failure %s\n", SDL_GetError() );
}

/**************************************************************************************************************************************/


/********************************************** initialization of variables *************************************************************/
/*

* window
* renderer
* environnement (and all textures)
* event
* some boolean for the game loop
*/


//create a window
window = SDL_CreateWindow(NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
if(window == NULL){
  fprintf(stderr, "SDL_CreateWindow failure, %s\n", SDL_GetError());
  exit(EXIT_FAILURE);
}

//create renderer

ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); //SDL_RENDERER_SOFTWARE );//| SDL_RENDERER_PRESENTVSYNC);


if(ren == NULL){
  fprintf(stderr, "SDL_CreateRenderer failure, %s\n", SDL_GetError());
  exit(EXIT_FAILURE);
}
SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0xFF, 0xFF); // set the color to White


env = init_env(ren, colors, g);

SDL_Event event;
bool quit = false;
bool won = false;

/*******************************************************************************************************************************************************/

/******************************************************* GAME LOOP ************************************************************************************/
//int  i = 0;
while(!quit){
  SDL_Point mouse;
  SDL_GetMouseState(&mouse.x, &mouse.y);

  while(SDL_PollEvent(&event)){ // waiting for event
    if(event.type == SDL_QUIT){
      quit = true;
    }

    if(won){
      if(process_winning(window, ren, g, env, nb_color, event, &won)){
        quit = true;
      } // if the game is won (winning screen)
    }else{
      if(!lost(g)){
        process(ren, g, env, nb_color, event, &won); // process if the game is not lost
      }else{
        if(process_game_over(ren, g, env, event, &won)){  // if the game is lost (game over screen)
          quit = true;
        }
      }
    }


    if(event.type == SDL_KEYDOWN){ // process keyboard inputs
      switch(event.key.keysym.sym){
        case(SDLK_r): // if 'r' is pressed
          game_restart(g);
          set_moves_left(ren, g, env);
          break;
        case(SDLK_ESCAPE): //'escape'
          quit = true;
          break;
      }
    }

    int screen_w, screen_h; // size of window width and height
    SDL_GetWindowSize(window, &screen_w, &screen_h); // adapt if resize

    if(game_is_over(g) != true){
      if(!lost(g)){

        color_grid(ren, screen_w, screen_h, env, g); // color the grid
        display_status(ren, g, env, screen_w, screen_h); // will display status of game (nb of moves left)
        buttons(ren, screen_w, screen_h, env, g, nb_color); // will display the buttons to click on

      }
      if(lost(g) && !won){ // if the game is lost

        display_losing_screen(ren,  g,  env,  screen_w,  screen_h); // will display the losing screen
      }

    }else{ // if the game is won

      won = true; // set won to true
      //color_grid(ren, screen_w, screen_h, env, g); // will color the grid drawn
      //display_status(ren, g, env, screen_w, screen_h); // will display status of game nb of moves left
      //buttons(ren, screen_w, screen_h, env, g, nb_color);
      display_winning_screen(ren,  g,  env,  screen_w,  screen_h, nb_color);



    }
    SDL_RenderPresent(ren); // refresh the screen to get the right display

  }


}

clean(window, ren, env, g, nb_color);

TTF_Quit();
IMG_Quit();
SDL_Quit();

return EXIT_SUCCESS;

}
