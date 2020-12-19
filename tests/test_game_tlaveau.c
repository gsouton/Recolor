#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/game.h"

/** TEST game_new_empty **/
/* create a game with the tested function and check if all the cells are correctly initialized,
also check the maximum number of strokes */
bool test_game_new_empty(void) {
  game g = game_new_empty();
  assert(g != NULL);

  assert(game_nb_moves_max(g) == 0);

  assert(game_cell_current_color(g, 11, 11) == 0);

  for(unsigned int i = 0; i<SIZE; i++){
    for(unsigned int j = 0; j<SIZE ; j++){
      assert(game_cell_current_color(g, i, j) == 0);

    }
  }
  game_delete(g);
  return true;

}

/** TEST game_new **/
/* create a game with the tested function and check if all the cells are correctly initialized with the "cell" test set,
also check the maximum number of strokes */
bool test_game_new(void) {
  uint cell[SIZE*SIZE]=
    {0,0,0,2,0,2,1,0,1,0,3,0,
    0,3,3,1,1,1,1,3,2,0,1,0,
    1,0,1,2,3,2,3,2,0,3,3,2,
    2,3,1,0,3,2,1,1,1,2,2,0,
    2,1,2,3,3,3,3,2,0,1,0,0,
    0,3,3,0,1,1,2,3,3,2,1,3,
    1,1,2,2,2,0,0,1,3,1,1,2,
    1,3,1,3,1,0,1,0,1,3,3,3,
    0,3,0,1,0,0,2,1,1,1,3,0,
    1,3,1,0,0,0,3,2,3,1,0,0,
    1,3,3,1,1,2,2,3,2,0,0,2,
    2,0,2,3,0,1,1,1,2,3,0,1};
  game g = game_new(cell, 0);
  game g1 = game_new(cell, 2);
  assert(g);
  assert(g1);

  for(uint i = 0; i<SIZE; i++){
    for(uint j = 0; j<SIZE ; j++){
      assert(game_cell_current_color(g, i, j) == cell[i+j*SIZE]);
    }
  }
  assert(game_cell_current_color(g, 11, 11) == 1);
  assert(game_nb_moves_max(g1) <= 2);

  game_delete(g);
  return true;

}

/** TEST game_cell_current_color **/
// create a game and check if the function returns the expected color with the "cell" test set
bool test_game_cell_current_color(void) {
  uint cell[SIZE*SIZE]=
    {0,0,0,2,0,2,1,0,1,0,3,0,
    0,3,3,1,1,1,1,3,2,0,1,0,
    1,0,1,2,3,2,3,2,0,3,3,2,
    2,3,1,0,3,2,1,1,1,2,2,0,
    2,1,2,3,3,3,3,2,0,1,0,0,
    0,3,3,0,1,1,2,3,3,2,1,3,
    1,1,2,2,2,0,0,1,3,1,1,2,
    1,3,1,3,1,0,1,0,1,3,3,3,
    0,3,0,1,0,0,2,1,1,1,3,0,
    1,3,1,0,0,0,3,2,3,1,0,0,
    1,3,3,1,1,2,2,3,2,0,0,2,
    2,0,2,3,0,1,1,1,2,3,0,1};
  game g = game_new(cell, 12);
  cgame c_g = g;
  assert(g != NULL);
  assert(c_g);
  game_set_cell_init(g, 0, 0, 3);
  assert(game_cell_current_color(g, 0,0) == 3);

  return true;
}





void usage(int argc, char *argv[]) {
  fprintf(stderr, "Usage: %s <testname> [<...>]\n", argv[0]);
  exit(EXIT_FAILURE);
}



int main(int argc, char *argv[]){
    if (argc == 1) usage(argc, argv);

    fprintf(stderr, "=> Start test \"%s\"\n", argv[1]);
    bool ok = false;
    if(strcmp("game_new", argv[1]) == 0)
        ok = test_game_new();
    else if (strcmp("game_cell_current_color", argv[1]) == 0)
        ok = test_game_cell_current_color();
    else if (strcmp("game_new_empty", argv[1]) == 0)
        ok = test_game_new_empty();
    else {
        fprintf(stderr, "Error: test \"%s\" not found!\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    if (ok) {
    fprintf(stderr, "Test \"%s\" finished: SUCCESS\n", argv[1]);
    return EXIT_SUCCESS;
  } else {
    fprintf(stderr, "Test \"%s\" finished: FAILURE\n", argv[1]);
    return EXIT_FAILURE;
  }

}
