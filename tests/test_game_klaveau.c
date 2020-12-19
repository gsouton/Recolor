#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/game.h"


/** TEST game_delete **/

/* on crée un jeu et on teste la fonction game_delete()
1) on initialise un jeu et ensuite on verifie si il a bien été supprimer
2) on retourne true si tel est le cas */

bool test_game_delete(){
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
  game_delete(g);
  return true;
}


/** TEST game_nb_moves_cur **/

/* on crée un jeu et on teste la fonction game_nb_moves_cur()
1) on initilise un jeu et on joue 2 coups avec la fonction game_play_one_move (x2)
2) une fois les coups joué, on regarde si la fonction retourne bien 2 si tel est le cas return true */
bool test_game_nb_moves_cur(){
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
	cgame c_g = g;
  assert(g);
	assert(c_g);
  game_play_one_move(g, 3);
  game_play_one_move(g, 2);
	assert(game_nb_moves_cur(c_g) == 2);
  return true;

}


/** TEST game_restart **/

/* on crée un jeu et on teste la fonction game_restart()
1) on initilise un jeu et on joue 1 coup avec la fonction play_one_move 
2) ensuite on utilise la fonction a tester et si elle "marche" correctement,
   apres l'appel a la fonction game_restart, le nombre de coup joue doit etre de 0
2) on le verifie avec l'appel a game_nb_moves_cur == 0 et return true si c'est bon */
bool test_game_restart(){
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
	cgame c_g = g;
	assert(g);
	assert(c_g);
  game_play_one_move(g, 3);
  game_restart(g);
	assert(game_nb_moves_cur(c_g) == 0);

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
   if(strcmp("game_restart", argv[1]) == 0)
    ok = test_game_restart();
  else if (strcmp("game_nb_moves_cur", argv[1]) == 0)
    ok = test_game_nb_moves_cur();
   else if (strcmp("game_delete", argv[1]) == 0)
    ok = test_game_delete();
  else {
    fprintf(stderr, "Error: test \"%s\" not found!\n", argv[1]);
    exit(EXIT_FAILURE);
  }

  if (ok) {
    fprintf(stderr, "Test \"%s\" finished: SUCCESS\n", argv[1]);
    return EXIT_SUCCESS;
  }
  else {
    fprintf(stderr, "Test \"%s\" finished: FAILURE\n", argv[1]);
    return EXIT_FAILURE;
  }
}
