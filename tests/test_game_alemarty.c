#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/game.h"
#include "../include/game_io.h"



/** TEST game_set_cell_init **/

/*  1) On crée un jeu
    2) On définie la couleur 3 pour la case (0,0) avec la fonction game_set_cell_init
    3) On vérifie avec la fonction game_cell_current_color que la couleur de la case est bien 3 */

bool test_game_set_cell_init(void){
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
    game g = game_new( cell, 12);
    assert(g);

    game_set_cell_init(g,0,0,3);
    assert(game_cell_current_color(g,0,0) == 3);

    game_delete(g);
    return true;
}

/** TEST game_set_max_moves **/

/*  1) On vérifie que le nombre de coup max est bien 0
    2) On définie le nombre de coup max à 16
    3) on vérifie que le nombre de coup est 16 */

bool test_game_set_max_moves(void){
    game g = game_new_empty();
    cgame c_g = g;
    assert(g);
    assert(c_g);

    assert(game_nb_moves_max(c_g) == 0);

    game_set_max_moves(g,16);
    assert(game_nb_moves_max(c_g) == 16);

    game_delete(g);
    return true;

}

/** TEST game_nb_moves_max **/

 /* 1) On crée un jeu
    2) On rentre les solutions dans un tableau
    3) On joue coup par coup les solutions et on verifie
    que le nombre de moves max est toujours égal à 12 */


bool test_game_nb_moves_max(void){
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
    assert(g);
    assert(c_g);

    int solution [] = {3, 1, 3, 1, 0, 3, 1, 0, 1, 3, 2, 0};
    for(unsigned int i = 0 ; i<SIZE; i++){
        game_play_one_move(g, solution[i]);
        assert(game_nb_moves_max(c_g) == 12);

    }
    game_delete(g);
    return true;
}

void usage(int argc, char *argv[]) {
  fprintf(stderr, "Usage: %s <testname> [<...>]\n", argv[0]);
  exit(EXIT_FAILURE);
}

bool test_game_load(void){
  game g = game_load("../data/default_game.rec");
  color cell[SIZE*SIZE]=
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
  assert(g);
  assert(game_width(g) == 12);
  assert(game_height(g) == 12);
  assert(game_nb_moves_max(g) == 12);
  assert(game_is_wrapping(g) == false);
  for(uint y = 0; y<game_height(g); y++){
    for(uint x = 0; x<game_width(g); x++){
      assert(game_cell_current_color(g, x, y) == cell[x + y*game_width(g)]);
    }
  }

  g = game_load("../data/horizontal_game2S.rec");
  color cell2[17*10] = {2, 2, 2, 2, 1, 1, 9, 6, 1, 4, 3, 2, 5, 1, 7, 1, 7,
                        2, 7, 4, 5, 5, 3, 9, 3, 1, 2, 7, 5, 5, 2, 6, 6, 7,
                        5, 9, 1, 5, 3, 9, 2, 8, 8, 2, 8, 5, 8, 2, 9, 5, 5,
                        5, 8, 1, 0, 9, 3, 9, 2, 7, 8, 2, 5, 8, 5, 6, 4, 0,
                        0, 5, 0, 2, 1, 0, 9, 8, 9, 7, 5, 2, 3, 7, 1, 1, 8,
                        1, 6, 5, 5, 2, 4, 9, 8, 3, 6, 5, 1, 1, 0, 0, 1, 3,
                        7, 4, 9, 6, 4, 7, 6, 5, 0, 4, 2, 4, 0, 5, 2 ,3, 2,
                        1, 0, 5, 0, 8, 5, 2, 9, 6, 2, 6, 5, 3, 6, 3, 5, 2,
                        6, 2, 4, 8, 1, 7, 7, 1, 0, 9, 4, 1, 9, 0, 6, 8, 8,
                        7, 7, 6, 3, 1, 9, 3, 3, 3, 0, 3, 2, 8, 9, 4, 9, 8};

  assert(game_width(g) == 17);
  assert(game_height(g) == 10);
  assert(game_nb_moves_max(g) == 24);
  assert(game_is_wrapping(g) == true);
  for(uint y = 0; y<game_height(g); y++){
    for(uint x = 0; x<game_width(g); x++){
      assert(game_cell_current_color(g, x, y) == cell2[x + y*game_width(g)]);
    }
  }

  return true;
}

bool test_game_save(void){
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
  assert(g);

  game_play_one_move(g, 2);
  game_save(c_g, "test.rec");
  game g2 = game_load("test.rec");
  uint cell2[SIZE*SIZE]=
  {2,2,2,2,0,2,1,0,1,0,3,0,
  2,3,3,1,1,1,1,3,2,0,1,0,
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
  assert(g2);
  assert(game_width(g2) == 12);
  assert(game_height(g2) == 12);
  assert(game_nb_moves_max(g2) == 12);
  //assert(game_nb_moves_cur(g2) == 1);
  for(uint y = 0; y<12; y++){
    for(uint x = 0; x<12 ; x++){
      assert(game_cell_current_color(g, x, y) == cell2[x+y*12]);
    }
  }

  return true;
}



int main(int argc, char *argv[]){
    if (argc == 1) usage(argc, argv);

    fprintf(stderr, "=> Start test \"%s\"\n", argv[1]);
    bool ok = false;
    if(strcmp("game_set_cell_init", argv[1]) == 0)
        ok = test_game_set_cell_init();
    else if (strcmp("game_set_max_moves", argv[1]) == 0)
        ok = test_game_set_max_moves();
    else if (strcmp("game_nb_moves_max", argv[1]) == 0)
        ok = test_game_nb_moves_max();
    else if (strcmp("game_load", argv[1]) == 0)
        ok = test_game_load();
    else if (strcmp("game_save", argv[1]) == 0)
        ok = test_game_save();
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
