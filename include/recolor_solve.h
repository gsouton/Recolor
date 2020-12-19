#ifndef __RECOLOR_SOLVE_H__
#define __RECOLOR_SOLVE_H__

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>
#include <string.h>
#include "game.h"
#include "game_io.h"
#include "recolor_solve.h"
#define STOP 87654567


/**
 *
 * This is the solver who will try to find either a solution to a given or
 * return the number of solutions for a given game
 *
 * This solver is based on backtracking, the idea is to play until we can't play anymore
 * When the game is finished if it is not won the algorithm will come back on the choices made
 * and try another combinations of colors until it find a combination that will
 * win the game.
 *
 */


 /***********************************************************************************************************************************************/

 /**
  * @brief The structure pointer history_g that stores an history of games.
  * it is a double link list the implementation is kind of tricky.
  * We will always add a game to the list at the beginning.
  * So @previous would be the game play just before the last move done
  * and @next is the next movement (since normally we always look at the beginning of the list it is NULL but no always)
  * Exemple:
  * A game with 11 color the index indicate the state of the games

                (*previous)    (*previous)      (*previous)     (*previous)    (*previous)     (*previous)
    next<-g[10]----------->g[9]----------->g[8]----------->[g7]----------->[g6]----------->[g5]----------> ( etc....) ------> NULL

  **/
typedef struct history_game *history_g;

/**
 * @brief The structure pointer tab_color that stores an array fill with the colors of the game.
 * @tab will have all the colors of a game
 * @optim will serve to sort tab_color the idea is that we will put a weight on the colors that should be prioritize
 * @size is the size of @tab and also the number of color in the game

**/

typedef struct tab *tab_color;


/**
 * Enum of the number of option avaible for the arguments of main

 **/
typedef enum option_flag {FIND_ONE, NB_SOL, FIND_MIN, ERROR} option_f;


/**
 * @brief Search if an element is the array tab_color->tab
 * if the element is in return true else false
 * @param tab a pointer structure of tab_color
 * @param elem a unsigned int element to insert
 * @pre @p tab is a valid pointer toward a tab_color structure

 **/

bool is_elem_in_tab(tab_color tab, uint elem);

/* will insert an element in an array of type tab_color
if the element is already in the array the element will not be inserted */
void insert_one_time(tab_color tab, uint elem);
/* return an array of tab_color that contains the colors for a given game */
tab_color find_color(game g);

uint number_of_colors(tab_color nb_color);

/* free tab_nb_color*/
void delete_tab_color(tab_color color);

/* return a double link list history
take a game as parameter, an history and a color
will add the game at the beginning of the list
*/
history_g save_game_list(game g, history_g p, uint move);

/* delete an element at the beginning of the list
So delete the last game played */
history_g delete_last_game(history_g l);

/* Will delete the entire list */
history_g delete_history(history_g h);

/* will initialize the double link list
with a game that is just loaded*/
history_g init_history(game g);

/* display the serie of movment played since the beginning*/
void display_list(history_g l, uint last_element );

/* take a file an history, and the last color played
will write down the movement that have been played since the beginning of
the game*/
void write_solution(char * filename, history_g h, uint last_element );

/* will search for one solution on a given game, nb of movement allowed minus 1,
array of colors that are playable, and a file to write the solutions down
This algorithm is based on backtracking*/
void solver(game g, history_g l, uint nb_moves, tab_color nb_color ,char *file, bool all, uint *nb);


/* will clean a file
the file will be empty after this call */
void clean_file(char *filename);

/* Compare two string with each other
return true if they are the same
else return false */
bool compare_string(char* string1, char *string2);

/* for a given string of character will determine which option
is entered as arguments with the executable*/
option_f detect_option(char *option);

/* check if the file is empty
  return true if the file is empty
  return false else*/
bool is_file_empty(char *filename);

/*if no solution are find then the file will be empty
so this function will write that there is no solution
*/
void no_solution(char *filename);

void write_nb_sol(char *filename, uint nb_sol);


void usage(void);

uint find_index(tab_color nb_color, uint color);

uint find_max_index_optim(tab_color nb_color);

void add_to_optim(game g, uint x, uint y, tab_color nb_color, uint current_color);

void search(game g, uint x, uint y, tab_color nb_color, uint current_color);

void swap(tab_color nb_color, uint position1, uint position2 );


void sorting_tab_color(tab_color nb_color, game g);

uint one_color(tab_color nb_color, uint index);



#endif
