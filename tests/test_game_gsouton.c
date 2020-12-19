#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/game.h"

struct game_s {
    uint height;
    uint width;
    bool wrap_status;
    uint nbMaxMoves;
    uint currentMove;
    color* tabGame;
    color* cpyTabGame;

};

/* **************** TEST void game_play_one_move(game g, color c); **************** */

/* on crée un jeu et on teste la fonction game_play_one_move(game g, color c)
1) on joue la solution du jeu et verifie si les couleurs sont bien modifié
2) on verifie egalement que le nombre de coups joué actuellemnt */

bool test_game_play_one_move(void){
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
  game g = game_new(cell, 12); // create a new game
  cgame c_g = g;
  assert(g);
  assert(c_g); // check pointers

  int solution [] = {3, 1, 3, 1, 0, 3, 1, 0, 1, 3, 2, 0};
  for(unsigned int i = 0 ; i<SIZE; i++){
    game_play_one_move(g, solution[i]);
    assert(game_cell_current_color(c_g, 0, 0) == solution[i]); //play solution[] and check if the right color is asigned to postion (0,0);

    assert(game_nb_moves_cur(c_g) == i+1); // play and check the number of current move

  }
  assert(game_is_over(c_g));// after playing the game it's supposed to be over


  game_delete(g); // free g

/*****************************************V2****************************************************/
color cell_rect [7*5] =
      {0, 3, 0, 0, 0, 3, 0,
       3, 3, 2, 0, 0, 2, 0,
       0, 0, 0, 3, 3, 2, 0,
       3, 3, 0, 3, 3, 2, 3,
       3, 3, 0, 3, 0, 3, 3};

color cell_rect_s [7*5] = // solution of cell_rect after playing color 1
      {1, 3, 1, 1, 1, 3, 1,
       3, 3, 2, 1, 1, 2, 1,
       1, 1, 1, 3, 3, 2, 1,
       3, 3, 1, 3, 3, 2, 3,
       3, 3, 1, 3, 1, 3, 3};

  g = game_new_ext(7, 5, cell_rect, 10, true); // crate a game with wrap_status == true and rectangle grid
  assert(g); // check pointer
  game_play_one_move(g, 1); // play one move
  /*for(uint i = 0; i<7*5; i++){
    assert(g->tabGame[i] == cell_rect_s[i]); // check if the move was played well
  }*/
  for(uint y = 0; y < 5; y++){
    for(uint x = 0; x <7; x++){
      assert(game_cell_current_color(g, x, y) == cell_rect_s[x+(y*game_width(g))]);

    }
  }

  game_delete(g);

  return true;

}

/* **************** TEST game_copy(cgame g); **************** */

/*  on crée un jeu et teste la fonction game_copy(cgame g)
1) on fait une copie du jeu et verifie si elle a été créée
on joue la solution associé au jeu
2) on regarde si le nombre de mouvements max correspond
3) on vérifie si le nombre de coup joués correspond
4) on vérifie si les grilles sont identiques en comparant les couleurs
*/

bool test_game_copy(void){

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
  game g = game_new( cell, 12); // initialisation d'une grille de jeu
  cgame c_g = g;
  assert(g);
  assert(c_g); // check pointers

  game copy_g = game_copy(c_g);
  assert(copy_g); /// check pointer copy

  int solution [] = { 3,1, 3, 1, 0, 3, 1, 0, 1, 3, 2, 0};
  for (unsigned int i = 0; i < SIZE; i++){
    game_play_one_move(g ,solution[i]); // play on g
    copy_g = game_copy(c_g); // create a copy of g
    cgame c_copy_g = copy_g; // create a copy of copy
    assert(copy_g);
    assert(c_copy_g); // check pointer
    assert(game_nb_moves_max(c_copy_g) == game_nb_moves_max(c_g)); // number of maximum moves supposed to be the same on both copies

    for(uint j=0; j<SIZE; j = j+1){
      assert(game_cell_current_color(c_copy_g, i, j) == game_cell_current_color(c_g, i, j)); // check if grid are the same

    }
    assert(game_nb_moves_cur(c_copy_g) == game_nb_moves_cur(c_g)); // check if number of currentMove are the same


  }
  game_delete(g); // free g;
  return true;
}



/* **************** TEST game_is_over(cgame g); **************** */
/* on crée un jeu et on teste test_game_is_over
1) on teste game_is_over sur le jeu juste créée  */


bool test_game_is_over(void){
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
  game g = game_new( cell, 12); // initialisation d'une grille de jeu
  cgame c_g = g;
  assert(g);
  assert(c_g); // check pointer

  assert(!game_is_over(c_g)); // game is supposed to not be over

  int solution[] = {3, 1, 3, 1, 0, 3, 1, 0, 1, 3, 2};
  for(uint i = 0; i<SIZE-1; i++){
    game_play_one_move(g, solution[i]); //play solution until the last move
    assert(!game_is_over(c_g)); // game still not supposed to be over for each move

  }
  game_play_one_move(g, 0); // play the last move
  assert(game_nb_moves_cur(g) == 12); // check number of current move
  assert(game_is_over(g)); // game now supposed to be over

  game_delete(g);
  return true;

}


/* **************** TEST game_is_wrapping(cgame g); **************** */

bool test_game_is_wrapping(void){
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
/*************Test wrap_status sur fonctions V1 game_new game_new_empty *****************/

  game g = game_new( cell, 12); // create a game without wrap
  cgame c_g = g;
  assert(g);
  assert(c_g);// check pointers

  assert(!game_is_wrapping(c_g)); // wrapping supposed to be false

  game_delete(g); // free game

  g = game_new_empty(); // create a new game without wrap
  c_g = g;
  assert(g);
  assert(c_g); // check pointers

  assert(!game_is_wrapping(c_g)); // wrap supposed to be false

  game_delete(g); // free g

  /***********Test wrap sur fonctions V2 game_new_ext game_new_empty_ext********************/

  g = game_new_empty_ext(12, 13, false); // create a game without wrap
  c_g = g;
  assert(g);
  assert(c_g); // check pointers
  assert(!game_is_wrapping(c_g)); // wrap supposed to be false

  game_delete(g);// free game

  g = game_new_empty_ext(12, 14, true); // create a game with wrap == true
  c_g = g;
  assert(g);
  assert(c_g); // check pointers
  assert(game_is_wrapping(c_g)); // wrap supposed to be true;

  game_delete(g); // free g;

  g = game_new_ext(12, 13, cell, 12, false); // create a game without wrap
  c_g = g;
  assert(g);
  assert(c_g); // check pointers
  assert(!game_is_wrapping(c_g)); // wrapping supposed to be false

  game_delete(g); // free game

  g = game_new_ext(12, 12, cell, 13, true); // game with wrap == true
  c_g = g;
  assert(g);
  assert(c_g); // check pointers
  assert(game_is_wrapping(c_g)); // wrapping supposed to be true

  game_delete(g); // free g

  return true;

}


/****************** Test game_new_empty_ext;*********************/

bool test_game_new_empty_ext(void){
  game g = game_new_empty_ext(12, 12, false); // create a game with game_new_ext width = 12; height = 12 ;wrap = false
  cgame c_g = g;
  assert(g);
  assert(c_g); //check pointers
  assert(game_width(g) == 12);
  assert(game_height(g) == 12); // check width and height
  assert(!game_is_wrapping(c_g)); // wrap_status supposed to be false
  assert(game_nb_moves_max(c_g) == 0); // nb_moves_max supposed to be at 0
  assert(game_nb_moves_cur(c_g) == 0); // nb_moves_cur supposed to be at 0

  for(uint y = 0; y < game_height(g); y++){
    for(uint x = 0; x < game_width(g); x++){
      assert(game_cell_current_color(c_g, x, y) == RED); // the grid supposed to be initialized to RED

    }
  }
  game_delete(g); // free game


  g = game_new_empty_ext(14, 13, true); // create a game with width = 14; height = 13= wrap_status = true;
  c_g = g;
  assert(g);
  assert(c_g);// check pointers
  assert(game_width(g) == 14);// width supposed to be at 14
  assert(game_height(g) == 13);// height supposed to be at 13
  assert(game_is_wrapping(c_g)); // wrap_status supposed to be true
  assert(game_nb_moves_max(c_g) == 0); // nb moves max supposed to be at 0
  assert(game_nb_moves_cur(c_g) == 0); // nb current moves supposed to be at 0

  for(uint y = 0; y < game_height(g); y++){
    for(uint x = 0; x < game_width(g); x++){
      assert(game_cell_current_color(c_g, x, y) == RED); // grid of the game supposed to be initialized RED

    }
  }
  game_delete(g); // free game

  return true;

}

/************** Test : game_new_ext; *****************/

bool test_game_new_ext(void){
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
  game g = game_new_ext(SIZE, SIZE, cell, 13, false); // create a game with width = SIZE; height = SIZE; grid of cell[] , nb moves = 13 and wrap_status = false
  cgame c_g = g;
  assert(g);
  assert(c_g);// check pointers
  assert(game_width(g) == SIZE);
  assert(game_height(g) == SIZE); // check if width and heigth == SIZE
  assert(!game_is_wrapping(c_g)); // check that wrap_status == false
  assert(game_nb_moves_max(c_g) == 13);  // check nb max moves == 13
  assert(game_nb_moves_cur(c_g) == 0); // check nb cur moves == 0

  for(uint y = 0; y < game_height(g); y++){
    for(uint x = 0; x < game_width(g); x++){
      assert(game_cell_current_color(c_g, x, y) == cell[SIZE*y+x]); // check that the colors of the grid correspond to cell
    }
  }
  game_delete(g); // free game

  g = game_new_ext(SIZE, SIZE, cell, 10, true);// game with w = SIZE; h = SIZE, grid of cell , 10 max moves and wrap_status = true
  c_g = g;
  assert(g);
  assert(c_g); // check pointers
  assert(game_width(g) == SIZE); // chec width == SIZE
  assert(game_height(g) == SIZE); // check height == SIZE
  assert(game_is_wrapping(c_g)); //check wrap_status == true
  assert(game_nb_moves_max(c_g) == 10); // check nb max moves == 10
  assert(game_nb_moves_cur(c_g) == 0); // checl nb cur moves == 0

  for(uint y = 0; y < game_height(g); y++){
    for(uint x = 0; x < game_width(g); x++){
      assert(game_cell_current_color(c_g, x, y) == cell[SIZE*y+x]); // check the grid

    }
  }
  game_delete(g); // free game

  return true;

}

/************ Test game_width **************/
bool test_game_width(void){
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
  game g = game_new_empty(); // create a game empty
  cgame c_g = g;
  assert(g);
  assert(c_g); // check pointers
  assert(game_width(c_g) == SIZE); //check taht width == SIZE

  game_delete(g); // free game

  g = game_new_empty_ext(13, 14, false); // create game w = 13 h = 14
  c_g = g;
  assert(g);
  assert(c_g); // check pointers
  assert(game_width(c_g) == 13); // check width == 13;

  game_delete(g); // free game

  g = game_new(cell, 13); // create a game w = SIZE
  c_g = g;
  assert(g);
  assert(c_g);// check pointers
  assert(game_width(c_g) == SIZE); // check witdh == SIZE

  game_delete(g); // free game

  g = game_new_ext(16, 11, cell, 14, false); // create game w = 16
  c_g = g;
  assert(g);
  assert(c_g);
  assert(game_width(c_g) == 16); // check width == 16

  game_delete(g); // free game
  return true;
}

/*************** test_game_height(void) ****************************
*************same test than game_width but with height**************************/
bool test_game_height(void){
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
  game g = game_new_empty();
  cgame c_g = g;
  assert(g);
  assert(c_g);
  assert(game_height(c_g) == SIZE);

  game_delete(g);

  g = game_new_empty_ext(13, 14, false);
  c_g = g;
  assert(g);
  assert(c_g);
  assert(game_height(c_g) == 14);

  game_delete(g);

  g = game_new(cell, 13);
  c_g = g;
  assert(g);
  assert(c_g);
  assert(game_height(c_g) == SIZE);

  game_delete(g);

  g = game_new_ext(16, 11, cell, 14, false);
  c_g = g;
  assert(g);
  assert(c_g);
  assert(game_height(c_g) == 11);

  game_delete(g);
  return true;
}

void usage(int argc, char *argv[]) {
  fprintf(stderr, "Usage: %s <testname> [<...>]\n", argv[0]);
  exit(EXIT_FAILURE);
}

int main(int argc, char * argv[]){
  if (argc == 1) usage(argc, argv);

  // start test
  fprintf(stderr, "=> Start test \"%s\"\n", argv[1]);
  bool ok = false;
  if (strcmp("game_copy", argv[1]) == 0)
    ok = test_game_copy();
  else if (strcmp("game_is_over", argv[1]) == 0)
    ok = test_game_is_over();
  else if (strcmp("game_play_one_move", argv[1]) == 0)
    ok = test_game_play_one_move();
  else if (strcmp("game_is_wrapping", argv[1]) == 0)
    ok = test_game_is_wrapping();
  else if (strcmp("game_new_empty_ext", argv[1]) == 0)
    ok = test_game_new_empty_ext();
  else if (strcmp("game_new_ext", argv[1]) == 0)
    ok = test_game_new_ext();
  else if (strcmp("game_width", argv[1]) == 0)
    ok = test_game_width();
  else if (strcmp("game_height", argv[1]) == 0)
    ok = test_game_height();
  else{
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
