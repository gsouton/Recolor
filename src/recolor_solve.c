#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>
#include <string.h>
#include "../include/game.h"
#include "../include/game_io.h"
#include "../include/recolor_solve.h"
#define STOP 87654567




int main(int argc, char *argv[]){
  if(argc != 4){
    usage();
  }
  char *file_sol = NULL;
  game g = game_load(argv[2]); // load a game
  history_g history = init_history(g);
  uint nb_moves = game_nb_moves_max(g) -1;
  tab_color nb_color = find_color(g);
  uint nb = 0;
  sorting_tab_color(nb_color, g);



  switch (detect_option(argv[1])) {
    case FIND_ONE:
      file_sol = strcat(argv[3], ".sol");
      clean_file(file_sol);
      solver(g, history, nb_moves, nb_color, file_sol, false, &nb); // search for solutions
      history = delete_history(history);// delete the entire list history
      delete_tab_color(nb_color);
      //game_delete(g);
      break;

    case NB_SOL:
      file_sol = strcat(argv[3], ".nbsol");
      clean_file(file_sol);
      solver(g, history, nb_moves, nb_color, file_sol, true, &nb);
      write_nb_sol(file_sol, nb);
       // search for solutions

      break;

    case FIND_MIN:
      file_sol = strcat(argv[3], ".sol");
      clean_file(file_sol);
      for(uint i = 1; i<=nb_moves; i++){
        solver(g, history, i, nb_color, file_sol, false, &nb); // search for solutions
        if(!is_file_empty(file_sol)){
          history = delete_history(history);// delete the entire list history
          break;
        }else{
          history = delete_history(history);
          g = game_load(argv[2]);
          game_restart(g);
          history = init_history(g);
        }
      }
      game_delete(g);
      history = delete_history(history);
      break;

    default :
      usage();
      exit(EXIT_FAILURE);
  }

  /*clean_file("../sol");
  game g = game_load("data/default_game.rec"); // load a game
  history_g history = init_history(g); // initialize history for this game

  solver(g, history); // search for solutions
  delete_history(history);// delete the entire list history*/
  if(is_file_empty(file_sol)){
    no_solution(file_sol);
  }
  history = delete_history(history);
  delete_tab_color(nb_color);

  return EXIT_SUCCESS;
}
