#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>
#include <string.h>
#include "../include/game.h"
#include "../include/game_io.h"
#include "../include/recolor_solve.h"


/*Double link list that store the history of games
for a series of movements played*/
struct history_game{
  game game;
  uint move;
  struct history_game *previous;
  struct history_game *next;
};

/* Array that will store all of the colors that are playable
for a game*/
struct tab{
  uint *tab;
  uint *optim;
  uint size;
};

/* option flag use to determine which option will be called */

/*function that search for an elemnt in an Array of type tab_color
if the element is in the array return true, false else*/
bool is_elem_in_tab(tab_color tab, uint elem){
  int i = 0;
  while(i<tab->size){
    if(tab->tab[i] == elem){
      return true;
    }
    i++;
  }
  return false;
}

/* will insert an element in an array of type tab_color
if the element is already in the array the element will not be inserted */
void insert_one_time(tab_color tab, uint elem){
  if(tab->size == 0){
    tab->tab[tab->size] = elem;
    tab->size++;
  }
  if(!is_elem_in_tab(tab, elem)){
    tab->tab[tab->size] = elem;
    tab->size++;
  }

}
/* return an array of tab_color that contains the colors for a given game */
tab_color find_color(game g){
  assert(g);
  tab_color tab = (tab_color) malloc(sizeof(struct tab));
  assert(tab);
  tab->tab = (uint*) malloc(16*sizeof(uint));
  tab->optim = (uint*) malloc(16*sizeof(uint));
  assert(tab->optim);
  assert(tab->tab);
  for(uint i = 0; i<16; i++){
    tab->optim[i] = 0;
  }
  tab->size = 0;
  uint current_color = 0;
  for(uint y = 0; y<game_height(g); y++){
    for(uint x = 0; x<game_height(g); x++){
      current_color = game_cell_current_color(g, x, y);
      insert_one_time(tab, current_color);
    }
  }
  return tab;
}

uint number_of_colors(tab_color nb_color){
  return nb_color->size;
}

/* free tab_nb_color*/
void delete_tab_color(tab_color color){
  if(color != NULL){
    if(color->tab != NULL){
      free(color->tab);
    }
    if(color->optim != NULL){
      free(color->optim);
    }
    free(color);
    color = NULL;
  }
}

/* return a double link list history
take a game as parameter, an history and a color
will add the game at the beginning of the list
*/
history_g save_game_list(game g, history_g p, uint move){
  history_g l = (history_g) malloc(sizeof(struct history_game));
  if(l == NULL){
    fprintf(stderr, "Malloc error create list\n");
    exit(EXIT_FAILURE);
  }
  l->game = game_copy(g);
  l->move = move;
  l->previous = p;
  l->next = NULL;
  p->next = l;

  return l;
}

/* delete an element at the beginning of the list
So delete the last game played */
history_g delete_last_game(history_g l){
  if(l != NULL){
    history_g p = l;
    l = l->previous;
    l->next = NULL;
    if(p->game != NULL){
      game_delete(p->game);
      p->game = NULL;
    }
    free(p);
    p = NULL;
    return l;
  }
  return l;
}

/* Will delete the entire list */
history_g delete_history(history_g h){
  while(h != NULL){
    history_g tmp = h;
    h = h->previous;
    if(tmp->game != NULL){
      game_delete(tmp->game);
      tmp->game = NULL;
    }
    free(tmp);
    tmp = NULL;
  }
  return h;
}

/* will initialize the double link list
with a game that is just loaded*/
history_g init_history(game g){
  history_g h = (history_g) malloc(sizeof(struct history_game));
  assert(h);
  h->game = game_copy(g);
  h->previous = NULL;
  h->next = NULL;
  h->move = STOP;
  return h;
}

/* display the serie of movment played since the beginning*/
void display_list(history_g l, uint last_element ){
  history_g p = l;
  while(p->previous != NULL){
    p = p->previous;
  }
  while(p->next != NULL){
    p = p->next;
    printf("%u ", p->move);

  }
  printf("%u \n", last_element);
}

/* return the color on the game of the grid at (0,0)
*/
uint current_color(game g){
  return game_cell_current_color(g, 0, 0);
}

/* take a file an history, and the last color played
will write down the movement that have been played since the beginning of
the game*/
void write_solution(char * filename, history_g h, uint last_element ){
  FILE *file = fopen(filename, "a");
  if(file == NULL){
    fprintf(stderr, "Error couldn't open the file \n");
    exit(EXIT_FAILURE);
  }
  history_g p = h;
  while(p->previous != NULL){
    p = p->previous;
  }
  while(p->next != NULL){
    p = p->next;
    fprintf(file, "%u ", p->move);
  }
  fprintf(file,"%u \n", last_element);

  fclose(file);
}

uint color_of_current_game(game g){
  tab_color nb_color = find_color(g);
  uint color = nb_color->size;
  delete_tab_color(nb_color);
  return color;

}


/* will search for one solution on a given game, nb of movement allowed minus 1,
array of colors that are playable, and a file to write the solutions down
This algorithm is based on backtracking*/
void solver(game g, history_g l, uint nb_moves, tab_color nb_color ,char *file, bool all, uint *nb){
    for(uint i = 0; i < nb_color->size; i++){
      if(game_nb_moves_max(g) - game_nb_moves_cur(g) < nb_color->size-1 && color_of_current_game(g) == nb_color->size){
        game_delete(g);
        return;
      }
      if(current_color(l->game) != nb_color->tab[i]){
        if(game_nb_moves_cur(g) < nb_moves){
          game_play_one_move(g, nb_color->tab[i]);

          if(game_is_over(g) == true){
            //display_list(l, i);
            if(!all){
              write_solution(file, l, nb_color->tab[i]);
              exit(EXIT_SUCCESS);
            }
          }
          l = save_game_list(g, l, nb_color->tab[i]);

          solver(g, l, nb_moves, nb_color, file, all, nb);
          l = delete_last_game(l);
          g = game_copy(l->game);

        }else{
          game_delete(g);
          g = game_copy(l->game);
          game_play_one_move(g, nb_color->tab[i]);

          if(game_is_over(g) == true){
            //display_list(l, i);
            *nb = *nb+1;
            if(!all){
              write_solution(file, l, nb_color->tab[i]);
              exit(EXIT_SUCCESS);
            }

          }

        }
      }
    }
    game_delete(g);
}




/* will clean a file
the file will be empty after this call */
void clean_file(char *filename){
  FILE *file = fopen(filename, "w+");
  if(file == NULL){
    fprintf(stderr, "couldn't open the file %s \n", filename );
    exit(EXIT_FAILURE);
  }
  fclose(file);
}

/* Compare two string with each other
return true if they are the same
else return false */
bool compare_string(char* string1, char *string2){
  char *tmp1 = string1;
  char *tmp2 = string2;
  while(*tmp1 != '\0' && *tmp2 != '\0'){
    if(*tmp1 != *tmp2){
      return false;
    }
    tmp1++;
    tmp2++;
  }
  return true;
}

/* for a given string of character will determine which option
is entered as arguments with the executable*/
option_f detect_option(char *option){
  char *find_one = "FIND_ONE";
  char *nb_sol = "NB_SOL";
  char *find_min = "FIND_MIN";
  if(compare_string(option, find_one)){
    return FIND_ONE;
  }
  if(compare_string(option, nb_sol)){
    return NB_SOL;
  }
  if(compare_string(option, find_min)){
    return FIND_MIN;
  }
  return ERROR;
}

/* check if the file is empty
  return true if the file is empty
  return false else*/
bool is_file_empty(char *filename){
  FILE *file = fopen(filename, "r");
  if(file == NULL){
    fprintf(stderr, "couldnt open %s\n", filename );
    exit(EXIT_FAILURE);
  }
  char elem[3] = "";
  fgets(elem, 3, file);
  if(elem[0] == '\0'){
    fclose(file);
    return true;
  }
  fclose(file);
  return false;
}

/*if no solution are find then the file will be empty
so this function will write that there is no solution
*/
void no_solution(char *filename){
  FILE *file = fopen(filename, "w+");
  assert(file);
  fprintf(file, "NO SOLUTION\n");
  fclose(file);
}

void write_nb_sol(char *filename, uint nb_sol){
  FILE *file = fopen(filename, "w+");
  if(file == NULL){
    fprintf(stderr, "couldnt open the file : %s\n", filename );
    exit(EXIT_FAILURE);
  }
  fprintf(file, "NB_SOL = %u\n",nb_sol);
  fclose(file);
}


void usage(void){
  fprintf(stderr, "Wrong use, here what's expected : \
  n./recolor_solve FIND_ONE|NB_SOL|FIND_MIN <nom_fichier_pb> <prefix_fichier_sol>\n" );
  exit(EXIT_FAILURE);
}

uint find_index(tab_color nb_color, uint color){
  int i = 0;
  while(nb_color->tab[i] != color){
    i++;
  }
  return i;
}

uint find_max_index_optim(tab_color nb_color){
  uint max = nb_color->optim[0];
  uint index = 0;
  for(uint i = 1; i<nb_color->size; i++){
    if(nb_color->optim[i] > max){
      max = nb_color->optim[i];
      index = i;
    }
  }
  return index;
}

void add_to_optim(game g, uint x, uint y, tab_color nb_color, uint current_color){
  uint index = find_index(nb_color, current_color);
  nb_color->optim[index]++;

}

void search(game g, uint x, uint y, tab_color nb_color, uint current_color){
  if( x >= game_width(g) || y >= game_height(g)){ // impossible to color cell with negative coordinate, superior or equal than width or height
    return;
  }
  if(game_cell_current_color(g, x, y) == current_color){
    search(g, x+1, y, nb_color, current_color); //right
    search(g, x, y+1, nb_color, current_color); //down
  }
  if(game_cell_current_color(g, x, y) != current_color){
    add_to_optim(g, x+1, y, nb_color, game_cell_current_color(g, x, y)); //right
    add_to_optim(g, x, y+1, nb_color, game_cell_current_color(g, x, y)); //down
  }
}

void swap(tab_color nb_color, uint position1, uint position2 ){
  uint tmp = nb_color->tab[position1];
  nb_color->tab[position1] = nb_color->tab[position2];
  nb_color->tab[position2] = tmp;
}

void reset_optim(tab_color nb_color){
  for(uint i = 0; i<nb_color->size; i++){
    nb_color->optim[i] = 0;
  }
}


void sorting_tab_color(tab_color nb_color, game g){
  game c_g = game_copy(g);
  uint position = 0;
  for(uint i = 0; i<nb_color->size-1; i++){
    search(c_g, 0, 0, nb_color, game_cell_current_color(c_g, 0, 0));
    game_play_one_move(c_g, nb_color->tab[find_max_index_optim(nb_color)]);
    swap(nb_color, position, find_max_index_optim(nb_color));
    position++;
    reset_optim(nb_color);

  }
  game_delete(c_g);
}

uint one_color(tab_color nb_color, uint index){
  return nb_color->tab[index];
}
