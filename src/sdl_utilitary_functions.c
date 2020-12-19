
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "../include/game.h"
#include "../include/recolor_solve.h"
#include "../include/sdl_utilitary_functions.h"



struct environnement{


  SDL_Rect *tab_game; //position for the color of the grid emulating the grid of the game
  SDL_Rect *buttons; // positions for the buttons to click on

  SDL_Texture *curr_move; // texture for text moves_left_white.png
  SDL_Texture *moves_left; // texture for the text

  SDL_Texture *restart; // texture for the button restart.png

  SDL_Texture *restart_end; // restart button for losing screen restart_end.png
  SDL_Rect pos_restart; // position of this button restart;

  SDL_Texture *gameOver; // game over png for losing screen
  SDL_Texture *won; // png for wining cases;

  SDL_Texture *quit; // button quit quit.png
  SDL_Rect pos_quit; // position of the button quit

  char *charMove; // array that will store game_nb_moves_cur(g) in a string for text display

};


/*
@brief free the memory that were allocated
* @param @window a SDL_Window
* @param @ren SDL_Renderer
* @pre @p g is a valid pointer toward a game structure
* @pre @env valid pointer toward an environnement structure

*/

void clean(SDL_Window* window, SDL_Renderer* ren, Env env, game g, tab_color nb_color){
  free(env->charMove);
  SDL_DestroyTexture(env->quit);
  SDL_DestroyTexture(env->won);
  SDL_DestroyTexture(env->restart_end);
  SDL_DestroyTexture(env->restart);
  SDL_DestroyTexture(env->moves_left);
  SDL_DestroyTexture(env->curr_move);
  free(env->buttons);
  free(env->tab_game);

  delete_tab_color(nb_color);
  game_delete(g);
  SDL_DestroyRenderer(ren);
  SDL_DestroyWindow(window);


  free(env);
}

/*
@brief initialize the struct environnement
* @param @ren SDL_Renderer
* @pre @p g is a valid pointer toward a game structure
*/
Env init_env(SDL_Renderer *ren, uint nb_colors, game g){

  check_pointer( ren, "ren", "init_env");
  check_pointer( g, "g", "init_env");
  uint game_w = game_width(g);
  uint game_h = game_height(g);

  Env env = (struct environnement*) malloc(sizeof(struct environnement));
  if(env == NULL){
    malloc_error("env");
  }

  env->tab_game = (SDL_Rect*) malloc(sizeof(SDL_Rect)*game_w*game_h);
  if(env->tab_game == NULL){
    malloc_error("tab_game");
  }
  env->buttons = (SDL_Rect*) malloc(sizeof(SDL_Rect)*(nb_colors+1));
  if(env->buttons == NULL){
    malloc_error("buttons");
  }

  env->charMove = (char*) malloc(sizeof(char)*SIZE_BUFFER);
  if(env->charMove == NULL){
    malloc_error("env->charMove");
  }

  env->curr_move = IMG_LoadTexture(ren, STATUS_MOVES);
  error_init(env->curr_move, "<env->curr_move> IMG_LoadTexture");

  env->restart = IMG_LoadTexture(ren, RESTART);
  error_init(env->restart, "<env->restart> IMG_LoadTexture");

  env->gameOver = IMG_LoadTexture(ren, GAME_OVER);
  error_init(env->gameOver, "<env->gameOver> IMG_LoadTexture");

  env->won = IMG_LoadTexture(ren, WINNING);
  error_init(env->won, "<you_won> IMG_LoadTexture");

  env->quit = IMG_LoadTexture(ren, QUIT);
  error_init(env->quit, "<env->quit> IMG_LoadTexture");

  env->restart_end = IMG_LoadTexture(ren, RESTART_END);
  error_init(env->restart_end, "<env->restart_end> IMG_LoadTexture");

  set_moves_left(ren, g, env);

  return env;
}


/*
@brief display message if malloc error and exit the program
* @param name of your variable
*/
void malloc_error(char* name){
    fprintf(stderr, "Error allocation memory, %s\n", name);
    exit(EXIT_FAILURE);
}



/*
@brief will set the renderer to a given color
* @param @ren SDL_Renderer
* @pre color an unsigned int corresponding to a color of the game
*/
void set_color(SDL_Renderer *ren, uint color){
  check_pointer( ren,"ren" , "set_color");

  switch (color){
    case RED: // 0  red orange
      SDL_SetRenderDrawColor(ren, 0xB6, 0x40, 0x03, SDL_ALPHA_OPAQUE);
      break;
    case GREEN: // 1 dark turqoise
      SDL_SetRenderDrawColor(ren, 0x04, 0x84, 0x81, SDL_ALPHA_OPAQUE);
      break;
    case BLUE: // 2 //dark green/turquois
    SDL_SetRenderDrawColor(ren, 0x05, 0x53, 0x58, SDL_ALPHA_OPAQUE);
      break;
    case YELLOW: // 3 YELLOW
      SDL_SetRenderDrawColor(ren, 0xFE, 0x8C, 0x03, SDL_ALPHA_OPAQUE);
      break;
    case ORANGE: // 4 DARK orange
      SDL_SetRenderDrawColor(ren, 0xDF, 0x68, 0x13, SDL_ALPHA_OPAQUE);
      break;
    case LIGHT_PINK: // 5 violet
      SDL_SetRenderDrawColor(ren, 0xAF, 0x8E, 0xAA, SDL_ALPHA_OPAQUE);
      break;
    case PINK: // 6 dark rose
      SDL_SetRenderDrawColor(ren, 0xB9, 0x80, 0x77, SDL_ALPHA_OPAQUE);
      break;
    case DARK_GREEN: // 7 dark bordeaux red
      SDL_SetRenderDrawColor(ren, 0x87, 0x11, 0x08, SDL_ALPHA_OPAQUE);
      break;
    case LIGHT_BLUE: // 8 light grey
      SDL_SetRenderDrawColor(ren, 0xCC, 0xBB, 0xAA, SDL_ALPHA_OPAQUE);
      break;
    case DARK_YELLOW: // 9 pinkish
      SDL_SetRenderDrawColor(ren, 0xCC, 0x44, 0x66, SDL_ALPHA_OPAQUE);
      break;
    case SHIT: // 10 light blue
      SDL_SetRenderDrawColor(ren, 0x93, 0xB5, 0xD6, SDL_ALPHA_OPAQUE);
      break;
    case VIOLET: // 11 grey
      SDL_SetRenderDrawColor(ren, 0x9E, 0x9B, 0x99, SDL_ALPHA_OPAQUE);
      break;
    case GREEN_BLUE: //12 yellow
      SDL_SetRenderDrawColor(ren, 0xFF, 0xD1, 0x2D, SDL_ALPHA_OPAQUE);
      break;
    case WEIRD_GRAY: //13 grey-green
      SDL_SetRenderDrawColor(ren, 0xB5, 0xBA, 0x84, SDL_ALPHA_OPAQUE);
      break;
    case WEIRD_GREEN: //14 very light violet
      SDL_SetRenderDrawColor(ren,  0xE0, 0xCE, 0xC6, SDL_ALPHA_OPAQUE);
      break;
    case SKIN: // 15 green
      SDL_SetRenderDrawColor(ren, 0x60, 0x7C, 0x50, SDL_ALPHA_OPAQUE);
      break;
  }
}





/*
@brief  will draw a colorful grid of your given game
* @param @ren SDL_Renderer
* screen_w and screen_w integer represent the width and height of the window
* @pre @p g is a valid pointer toward a game structure
* @env a valid pointer toward an environnement struct

*/
bool color_grid(SDL_Renderer *ren, int screen_w, int screen_h, Env env, game g){
  check_pointer( ren, "ren" , "color_grid");
  check_pointer( env, "env" , "color_grid");
  check_pointer( g, "g" , "color_grid");


  int game_w = game_width(g);
  int game_h = game_height(g);

  SDL_SetRenderDrawColor(ren, 0x21, 0x21, 0x21, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(ren);
  screen_h = (screen_h*PERCENTAGE)/100;
  if(ren != NULL && screen_w > 0 && screen_h > 0 && env != NULL && g != NULL){
    for(uint y = 0; y<game_h; y++){
      for(uint x = 0; x<game_w; x++){
        uint color = game_cell_current_color(g, x, y);
        set_color(ren, color);
        env->tab_game[x+y*game_w].x = x*(screen_w/game_w) + (screen_w/100)/2 ;
        env->tab_game[x+y*game_w].y = y*(screen_h/game_h) + (screen_h/100)/2;
        env->tab_game[x+y*game_w].w = screen_w/game_w - (screen_w/100)/2;
        env->tab_game[x+y*game_w].h = screen_h/game_h - (screen_h/100)/2;
        SDL_RenderFillRect(ren, &env->tab_game[x+y*game_w]);
      }
    }
    return true;
  }
  return false;
}


/*
@brief will display number of movements left and the current number
* @param @ren SDL_Renderer
* @pre @p g is a valid pointer toward a game structure
* @env a valid pointer toward an environnement struct
* screen_h and screen_w the width and height of the window
*/
void display_status(SDL_Renderer *ren, game g, Env env, int screen_w, int screen_h){
  check_pointer( ren, "ren" , "display_status");
  check_pointer( g, "g" , "display_status");
  check_pointer( env, "env" , "display_status");



  SDL_Rect pos;
  pos.x = 25;
  pos.y = (screen_h*83)/100;
  SDL_QueryTexture(env->curr_move, NULL, NULL, &pos.w, &pos.h);
  SDL_RenderCopy(ren, env->curr_move, NULL, &pos);

  pos.x = pos.w + 30;
  pos.y = ((screen_h*83)/100)-1;

  SDL_QueryTexture(env->moves_left, NULL, NULL, &pos.w, &pos.h);
  SDL_RenderCopy(ren, env->moves_left, NULL, &pos);

}



/*
@brief  will return the number of movements left as a string for a given game

* @pre @p g is a valid pointer toward a game structure
* @charMove an array where to store the number convert as a string
*/
char* moves_left(game g, char * charMove){
  check_pointer( g, "g" , "moves_left");
  check_pointer( charMove, "charMove" , "moves_left");


  uint moves_left = game_nb_moves_max(g) - game_nb_moves_cur(g);
  snprintf(charMove, 10, "%u", moves_left);
  return charMove;
}

/*
@brief Rendering buttons to the window
* @param @ren SDL_Renderer
* screen_h and screen_w width and height of the window
* @pre @p g is a valid pointer toward a game structure
* @nb_color is a valid pointer toward a tab_color structure (used in solver see utilitary_functions_solver)
*/
void buttons(SDL_Renderer *ren, int screen_w, int screen_h, Env env, game g, tab_color nb_color){
  check_pointer( ren, "ren" , "buttons");
  check_pointer( env, "g" , "buttons");
  check_pointer( g, "g" , "buttons");
  check_pointer( nb_color, "nb_color" , "buttons");


  uint size_colors = number_of_colors(nb_color);
  #ifdef __ANDROID__
  buttons_android(ren, screen_w, screen_h, env, g, nb_color, size_colors);
  return;
  #endif


  for(uint i = 0; i<size_colors; i++){
    set_color(ren, one_color(nb_color, i));
    env->buttons[i].x = (((screen_w)/(size_colors+1))*(i+1));// - (screen_w/game_w - SIZE_BUTTONS/2);
    env->buttons[i].y = ((screen_h*(PERCENTAGE+10))/100);
    env->buttons[i].w = SIZE_BUTTONS;//screen_w/game_w - (screen_w/100)/2;
    env->buttons[i].h = SIZE_BUTTONS;//screen_h/game_h - (screen_h/100)/2;
    SDL_RenderFillRect(ren, &env->buttons[i]);
  }
  env->buttons[size_colors].x = (screen_w*80)/100;
  env->buttons[size_colors].y = (screen_h*83)/100;

  env->buttons[size_colors].w = 100;
  env->buttons[size_colors].h = 30;

  SDL_QueryTexture(env->restart, NULL, NULL, &env->buttons[size_colors].w, &env->buttons[size_colors].h);
  SDL_RenderCopy(ren, env->restart, NULL, &env->buttons[size_colors]);

}

void buttons_android(SDL_Renderer *ren, int screen_w, int screen_h, Env env, game g, tab_color nb_color, uint size_colors){
  uint i2 = 0;
  for(uint i = 0; i<size_colors; i++){
    set_color(ren, one_color(nb_color, i));
    if(i >= 8){
      env->buttons[i].x = (((screen_w)/(MAX_COLOR_LINE+1))*(i2+1)) - (SIZE_BUTTONS_ANDROID/2);// - (screen_w/game_w - SIZE_BUTTONS/2);
      env->buttons[i].y = screen_h - (SIZE_BUTTONS_ANDROID+5);//((screen_h*(PERCENTAGE+5))/100)+SIZE_BUTTONS+15;
      env->buttons[i].w = SIZE_BUTTONS_ANDROID;//screen_w/game_w - (screen_w/100)/2;
      env->buttons[i].h = SIZE_BUTTONS_ANDROID;//screen_h/game_h - (screen_h/100)/2;
      i2++;
    }else{
      env->buttons[i].x = (((screen_w)/(MAX_COLOR_LINE+1))*(i+1)) - (SIZE_BUTTONS_ANDROID/2);// - (screen_w/game_w - SIZE_BUTTONS/2);
      env->buttons[i].y = (screen_h - (2*SIZE_BUTTONS_ANDROID+20));
      env->buttons[i].w = SIZE_BUTTONS_ANDROID;//screen_w/game_w - (screen_w/100)/2;
      env->buttons[i].h = SIZE_BUTTONS_ANDROID;//screen_h/game_h - (screen_h/100)/2;
    }

    SDL_RenderFillRect(ren, &env->buttons[i]);
  }
  env->buttons[size_colors].x = screen_w - (SIZE_BUTTONS_ANDROID+10);
  env->buttons[size_colors].y = (screen_h*81)/100;
  env->buttons[size_colors].w = 100;
  env->buttons[size_colors].h = 30;

  SDL_QueryTexture(env->restart, NULL, NULL, &env->buttons[size_colors].w, &env->buttons[size_colors].h);
  SDL_RenderCopy(ren, env->restart, NULL, &env->buttons[size_colors]);
}



/*
@brief rendering the status of the game (number of movements left)
* @param @ren SDL_Renderer
* @pre @p g is a valid pointer toward a game structure
* @env is a valid pointer toward a game structure
*/
void set_moves_left(SDL_Renderer *ren, game g, Env env){
  check_pointer( ren, "ren" , "set_moves_left");
  check_pointer( g, "g" , "set_moves_left");
  check_pointer( env, "env" , "set_moves_left");


  SDL_Color color = {0xFF, 0xFF, 0xFF, 0xFF}; // set color to white

  TTF_Font *font = TTF_OpenFont(FONT, FONTSIZE);
  error_init(font, "<font> TTF_OpenFont");

  TTF_SetFontStyle(font, TTF_STYLE_BOLD); // TTF_STYLE_ITALIC | TTF_STYLE_NORMAL
  SDL_Surface * surf = TTF_RenderText_Blended(font, moves_left(g, env->charMove), color);
  error_init(surf, "<surf> TTF_RenderText_Blended");

  SDL_DestroyTexture(env->moves_left);
  env->moves_left = SDL_CreateTextureFromSurface(ren, surf);
  error_init(env->moves_left, "<env->moves_left> SDL_CreateTextureFromSurface");

  SDL_FreeSurface(surf);
  TTF_CloseFont(font);

}


/*
@brief process the click of the mouse during game
* @param @ren SDL_Renderer
* SDL_Point mouse
* @pre @p g is a valid pointer toward a game structure
* @env is a valid pointer toward an environnement struct
* @nb_color a valid pointer toward a tab_color struct
*/
void process(SDL_Renderer *ren, game g, Env env, tab_color nb_colors, SDL_Event event, bool *won){
  check_pointer( ren, "ren" , "processe");
  check_pointer( g, "g" , "processe");
  check_pointer( env, "env" , "processe");
  check_pointer( nb_colors, "nb_color" , "processe");
  int nb_color = number_of_colors(nb_colors);



  if(event.type == SDL_MOUSEBUTTONDOWN){
    SDL_Point mouse;
    SDL_GetMouseState(&mouse.x, &mouse.y);

    for(uint i = 0; i<number_of_colors(nb_colors); i++){
      if(check_collision(mouse.x, mouse.y, env->buttons[i].x, env->buttons[i].y, env->buttons[i].w, env->buttons[i].h)){
        game_play_one_move(g, one_color(nb_colors, i));
        set_moves_left(ren, g, env);
      }
    }
    if(check_collision(mouse.x, mouse.y, env->buttons[nb_color].x, env->buttons[nb_color].y, env->buttons[nb_color].w, env->buttons[nb_color].h)){
      game_restart(g);
      set_moves_left(ren, g, env);
      *won = false;
      return;
    }
  }
  #ifdef __ANDROID__
  if(event.type == SDL_FINGERDOWN){
    for(uint i = 0; i<number_of_colors(nb_colors); i++){
      if(event.tfinger.x >= env->buttons[i].x && event.tfinger.x <= env->buttons[i].w + env->buttons[i].x && event.tfinger.y >= env->buttons[i].y && event.tfinger.y <= env->buttons[i].y + env->buttons[i].h){
        game_play_one_move(g, one_color(nb_colors, i));
        set_moves_left(ren, g, env);
      }
    }
    if(event.tfinger.x >= env->buttons[nb_color].x && event.tfinger.x <= env->buttons[nb_color].w + env->buttons[nb_color].x && event.tfinger.y >= env->buttons[nb_color].y && event.tfinger.y <= env->buttons[nb_color].y + env->buttons[nb_color].h){
      game_restart(g);
      set_moves_left(ren, g, env);
        *won = false;
        return;
    }
  }
  #endif
}

bool process_winning(SDL_Window *window, SDL_Renderer *ren, game g, Env env, tab_color nb_colors, SDL_Event event, bool *won){
  check_pointer( ren, "ren" , "processe");
  check_pointer( g, "g" , "processe");
  check_pointer( env, "env" , "processe");
  check_pointer( nb_colors, "nb_color" , "processe");
  bool over = false;
  int w, h;
  SDL_GetWindowSize(window, &w, &h);

  if(event.type == SDL_MOUSEBUTTONDOWN){
    SDL_Point mouse;
    SDL_GetMouseState(&mouse.x, &mouse.y);

    if(mouse.x >= env->pos_restart.x && mouse.x <= env->pos_restart.w + env->pos_restart.x && mouse.y >= env->pos_restart.y && mouse.y <= env->pos_restart.y + env->pos_restart.h){
      game_restart(g);
      *won = false;
      set_moves_left(ren, g, env);
      return over;
    }
    if(mouse.x >= env->pos_quit.x && mouse.x <= env->pos_quit.w + env->pos_quit.x && mouse.y >= env->pos_quit.y && mouse.y <= env->pos_quit.y + env->pos_quit.h){
      over = true;
      return over;
    }
  }
  #ifdef __ANDROID__
  if(event.type == SDL_FINGERDOWN){
    if(check_collision(event.tfinger.x, event.tfinger.y, env->pos_restart.x, env->pos_restart.y, env->pos_restart.w, env->pos_restart.h)){
      game_restart(g);
      *won = false;
      set_moves_left(ren, g, env);
      return over;
    }
    if(check_collision(event.tfinger.x, event.tfinger.y, env->pos_quit.x, env->pos_quit.y, env->pos_quit.w, env->pos_quit.h)){
      over = true;
      return over;
    }
  }
  #endif

  return over;
}


bool check_collision(int pointer_x, int pointer_y, int object_x, int object_y, int object_width, int object_height){
  if(pointer_x >= object_x && pointer_x <= object_width + object_x && pointer_y >= object_y && pointer_y <= object_y + object_height){
    return true;
  }
  return false;

}
/*
@brief rendering the losing screen
* @param @ren SDL_Renderer
* @pre @p g is a valid pointer toward a game structure
* @env is a valid pointer toward an environnement struct
* screen_w and screen_h widht and height of the window

*/
void display_losing_screen(SDL_Renderer *ren, game g, Env env, int screen_w, int screen_h){
  check_pointer( ren, "ren" , "display_losing_screen");
  check_pointer( g, "g" , "display_losing_screen");
  check_pointer( env, "env" , "display_losing_screen");

  SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(ren);


  //SDL_QueryTexture(env->gameOver, NULL, NULL, &pos.w, &pos.h);
  //pos.x = (screen_w/2) - (pos.w)/2;
  //pos.y = (screen_h/3);
  SDL_RenderCopy(ren, env->gameOver, NULL, NULL);

  //SDL_QueryTexture(env->restart_end, NULL, NULL, &pos.w, &pos.h);
  env->pos_restart.x = (screen_w/(23/10))+24;
  env->pos_restart.y = (screen_h/(32/10))+24;
  env->pos_restart.w = 90;
  env->pos_restart.h = 160;
  //SDL_RenderCopy(ren, env->restart_end, NULL, &pos);


  //SDL_QueryTexture(env->quit, NULL, NULL, &pos.w, &pos.h);
  env->pos_quit.x = (screen_w/(56/10))+60;
  env->pos_quit.y = (screen_h/(31/10))+30;
  env->pos_quit.w = 90;
  env->pos_quit.h = 160;


}


/*
@brief process the mouse in case of a loosing game
* @param @ren SDL_Renderer
* SDL_Point mouse
* @pre @p g is a valid pointer toward a game structure
* @env is a valid pointer toward an environnement struct
*/
bool process_game_over(SDL_Renderer *ren, game g, Env env, SDL_Event event, bool *won){
  check_pointer( ren, "ren" , "process_game_over");
  check_pointer( g, "g" , "process_game_over");
  check_pointer( env, "env" , "process_game_over");

  bool over = false;
  if(event.type == SDL_MOUSEBUTTONDOWN){
    SDL_Point mouse;
    SDL_GetMouseState(&mouse.x, &mouse.y);

  if(mouse.x >= env->pos_restart.x && mouse.x <= env->pos_restart.w + env->pos_restart.x && mouse.y >= env->pos_restart.y && mouse.y <= env->pos_restart.y + env->pos_restart.h){
    game_restart(g);
    *won = false;
    set_moves_left(ren, g, env);
    return over;
  }
  if(mouse.x >= env->pos_quit.x && mouse.x <= env->pos_quit.w + env->pos_quit.x && mouse.y >= env->pos_quit.y && mouse.y <= env->pos_quit.y + env->pos_quit.h){
    over = true;
    return over;
  }
}

  #ifdef __ANDROID__
  if(event.type == SDL_FINGERDOWN){
    if(check_collision(event.tfinger.x, event.tfinger.y, env->pos_restart.x, env->pos_restart.y, env->pos_restart.w, env->pos_restart.h)){
      game_restart(g);
      *won = false;
      set_moves_left(ren, g, env);
      return over;
    }
    if(check_collision(event.tfinger.x, event.tfinger.y, env->pos_quit.x, env->pos_quit.y, env->pos_quit.w, env->pos_quit.h)){
      over = true;
      return over;
    }
  }
  #endif

  return over;

}

/*
@brief display error message while init_env
* @ptr a valid pointer
* @msg a message
*/
void error_init(void *ptr, char * msg){
  if(ptr == NULL){
    fprintf(stderr, "Error failure %s : %s\n",msg, SDL_GetError() );
    exit(EXIT_FAILURE);
  }

}


/*
@brief will check if you loose regarding the number of moves
* @g a valid pointer toward a game struct
*/
bool lost(game g){
  check_pointer( g, "g" , "lost");

  if(game_nb_moves_cur(g) < game_nb_moves_max(g)){
    return false;
  }
  return true;
}


/*
@brief will display a winning screen
* @ren a valid pointer toward renderer
* @g valid pointer toward game struct
* @env valid pointer toward environnement struct
* screenw and screen_h size of window
* nb_color a valid pointer toward a tab_color struct
*/
void display_winning_screen(SDL_Renderer *ren, game g, Env env, int screen_w, int screen_h, tab_color nb_color){
  check_pointer( ren, "ren" , "display_winning_screen");
  check_pointer( g, "g" , "display_winning_screen");
  check_pointer( env, "env" , "display_losing_screen");
  check_pointer( nb_color, "nb_color" , "display_losing_screen");


  //uint size_colors = number_of_colors(nb_color);
  SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(ren);


  SDL_RenderCopy(ren, env->won, NULL, NULL);


  env->pos_restart.x = (screen_w/(23/10)+30);
  env->pos_restart.y = (screen_h/(20/10)-30);
  env->pos_restart.w = 90;
  env->pos_restart.h = 160;

  env->pos_quit.x = (screen_w/(36/10));
  env->pos_quit.y = (screen_h/(22/10)-30);
  env->pos_quit.w = 90;
  env->pos_quit.h = 160;




  /*SDL_QueryTexture(env->restart, NULL, NULL, &env->buttons[size_colors].w, &env->buttons[size_colors].h);
  SDL_RenderCopy(ren, env->restart, NULL, &env->buttons[size_colors]);*/
}






/*
@Brief will make sure that the game cannot receive more than 16 colors
* nb of color
*/
void control_max_color(uint nb){
  if(nb > 16){
    fprintf(stderr, "achtung ! MAXIMUM number of colors is 16 \n");
    exit(EXIT_FAILURE);
  }
}

/*
@Brief Check if pointer is valid if not return error message and quit the program
* @ptr a pointer to a variable or structure
* @name the name of the check_pointer
* @function the name of the function
*/
void check_pointer(void *ptr, char *name, char *function){
  if(ptr == NULL){
    fprintf(stderr, "invalid pointer < %s > in function ---> %s\n", name, function );
    exit(EXIT_FAILURE);
  }
}
