#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include "../include/game.h"
#include "../include/game_io.h"

game game_load(char *filename){

  FILE *file;

  file = fopen(filename, "r");
  if (file == NULL) {
    fprintf(stderr, "Error couldn't open the file : %s\n", filename );
    exit(EXIT_FAILURE);
  }

  uint width, height, maxMoves;
  char swap;
  bool wrap = false;
  uint color;

  fscanf(file, "%u %u %u %c", &width, &height, &maxMoves, &swap);

  uint cell[width*height];

  for(int y = 0; y<height; y++){
    for(int x = 0; x<width; x++){
      fscanf(file, "%u", &color);
      cell[x+y*width] = color;
    }
  }


  if(swap == 'S'){
    wrap = true;
  }
  game g = game_new_ext(width, height, cell, maxMoves, wrap);

  fclose(file);

  return g;
}

void game_save(cgame g, char *filename){
  FILE *file = fopen(filename,"w+");
  if(file == NULL){
    printf("Erreur");
    exit(EXIT_FAILURE);
  }
  char swap;
  if(game_is_wrapping(g)){
    swap = 83;
  }else{
    swap = 78;
  }

  fprintf(file,"%u",game_width(g));
  fprintf(file," ");
  fprintf(file,"%u",game_height(g));
  fprintf(file," ");
  fprintf(file,"%u",game_nb_moves_max(g));
  fprintf(file," ");
  fprintf(file,"%c\n",swap);
  for(uint i=0; i<game_height(g);i++){
    for(uint j=0; j<game_width(g)-1;j++){
      fprintf(file,"%u ",game_cell_current_color(g,j,i));
    }
    fprintf(file,"%u",game_cell_current_color(g,game_width(g)-1,i));
    fprintf(file,"\n");
  }

  fclose(file);

}
