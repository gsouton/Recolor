#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include "../include/game.h"
#include "../include/game_io.h"
#include "../include/game_rand.h"



/**
 * Autor Kevin Laveau Tanguy Laveau Alexandre Marty Gilles Souton
**/

static void display(cgame g){
  printf("nb coups joués : %u ; nb coups max : %u\n", game_nb_moves_cur(g), game_nb_moves_max(g));
  uint move_played = 0;
  for(uint y=0; y<game_height(g); y = y+1){
    for(uint x=0; x<game_width(g); x = x+1){
      move_played = game_cell_current_color(g, x, y);
      if(move_played >= 10){
        move_played = move_played + 55;
        printf("%c", move_played);
      }else{
        printf("%u",move_played);

      }
    }
    printf("\n");
  }
  printf("Jouer un coup: (0,1,2,3,r ou q ;  r pour redémarrer ou q pour quitter)\n");

} // display the game as a grid in a terminal




int main(int argc, char *argv[]){
  srand(time(NULL));
  game g = NULL;
  if(argc == 1){
    g = game_load("../data/solver/default_game.rec");
    assert(g);
  }
  else if(argc == 2){
    g = game_load(argv[1]);
    assert(g);
  }
  else if(argc == 4){
    uint width = atoi(argv[1]);
    uint height = atoi(argv[2]);
    uint max_moves = atoi(argv[3]);
    g = game_random_ext(width, height, false, 4, max_moves);
    assert(g);
  }
  else if(argc == 5){
    uint width = atoi(argv[1]);
    uint height = atoi(argv[2]);
    uint max_moves = atoi(argv[3]);
    uint max_color = atoi(argv[4]);
    g = game_random_ext(width, height, false, max_color, max_moves);
    assert(g);
  }
  else if(argc == 6){
    uint width = atoi(argv[1]);
    uint height = atoi(argv[2]);
    uint max_moves = atoi(argv[3]);
    uint max_color = atoi(argv[4]);
    bool wrap = false;
    if(strcmp(argv[5] ,"S") == 0){
      wrap = true;
    }
    g = game_random_ext(width, height, wrap, max_color, max_moves);
    assert(g);
  }
  //assert(g);
  cgame c_g = g;
  display(c_g);
  int key = 0;
  uint color = 0;
  while (game_is_over(c_g) != true){
    key = getc(stdin);
    color = key -'0';
    /*if(game_nb_moves_cur(g) >= game_nb_moves_max(c_g) ){
        game_delete(g);
        exit(EXIT_FAILURE);
    }*/
    if(key == 113 ){
      game_delete(g);
      printf("DOMMAGE\n");
      exit(EXIT_FAILURE);
    }
    if (key == 114 ){
      game_restart(g);
      display(g);
    }
    if ((key >= 48 && key <= 57)){
      color = key-'0';
      game_play_one_move(g, color);
      display(c_g);
    }
    if(key >= 65 && key <= 70){
      color = key - '7';
      game_play_one_move(g, color);
      display(c_g);
    }

  }
  printf("BRAVO\n");
  game_delete(g);

  return EXIT_SUCCESS;

}
