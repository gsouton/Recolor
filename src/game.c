#include "../include/game.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct game_s {
  uint height;
  uint width;
  bool wrap_status;
  uint nbMaxMoves;
  uint currentMove;
  color* tabGame;
  color* cpyTabGame;
};

game game_new(color* cells, uint nb_moves_max) {
  assert(cells);

  game g = game_new_empty();


  for (uint i = 0; i < SIZE * SIZE; i++) {
    g->tabGame[i] = cells[i];
    g->cpyTabGame[i] = cells[i];  // set all cells of the grid to the same color
  }
  g->nbMaxMoves = nb_moves_max;
  g->currentMove = 0;
  g->height = SIZE;
  g->width = SIZE;
  g->wrap_status = false;
  return g;
}

game game_new_empty() {
  game g = (struct game_s*)malloc(sizeof(struct game_s));
  assert(g);

  g->tabGame = (color*)malloc(sizeof(color) * SIZE * SIZE);
  g->cpyTabGame = (color*)malloc(sizeof(color) * SIZE * SIZE);
  assert(g->tabGame);
  assert(g->cpyTabGame);

  g->nbMaxMoves = 0;
  g->currentMove = 0;
  g->height = SIZE;
  g->width = SIZE;
  g->wrap_status = false;
  for (uint i = 0; i < SIZE * SIZE; i++) {
    g->tabGame[i] = RED;
    g->cpyTabGame[i] = RED;
  }
  return g;
}

// takes as a parameter a game, coordinates and a color and assigns the color to
// the correct coordinates in the game
void game_set_cell_init(game g, uint x, uint y, color c) {
  assert(g);
  assert(g->tabGame);
  assert(x < g->width);
  assert(y < g->height);

  g->tabGame[x + y * g->width] = c;
}

void game_set_max_moves(game g, uint nb_max_moves) {
  assert(g);
  assert(nb_max_moves >= 0);
  g->nbMaxMoves = nb_max_moves;
}

// return the max moves for the game in parameter
uint game_nb_moves_max(cgame g) {
  assert(g);
  return g->nbMaxMoves;
}

// return the color to the coordinates pass in parameter in the game also pass
// in parameter
color game_cell_current_color(cgame g, uint x, uint y) {
  assert(g);
  assert(g->tabGame);
  // assert(x < g->width);
  assert(y < g->height);
  return g->tabGame[x + y * g->width];
}

// return the value of the current number of moves.
uint game_nb_moves_cur(cgame g) {
  assert(g);
  return g->currentMove;
}

static void aux(game g, color c, color previous_color, uint x, uint y) {
  cgame c_g = g;
  assert(g);
  assert(c_g);
  if (x >= g->width ||
      y >= g->height) {  // impossible to color cell with negative coordinate,
                         // superior or equal than width or height
    return;
  }
  if (game_cell_current_color(c_g, x, y) ==
      c) {  // if the current color on the cell is already the right one we do
            // nothing;
    return;
  }
  if (game_cell_current_color(c_g, x, y) !=
      previous_color) {  // if the color is different than the initial color we
                         // can't color them
    return;
  }
  game_set_cell_init(g, x, y, c);       // we color the given cell
  if (game_is_wrapping(c_g) == true) {  // we look if wrap is activated
    if (x == 0) {  // if we are located at the left extremity
      aux(g, c, previous_color, x + (game_width(c_g) - 1),
          y);  // color the corresponding right extremity
    }
    if (x == game_width(c_g) - 1) {  // if we are located at the right extremity
      aux(g, c, previous_color, x - (game_width(c_g) - 1),
          y);  // color the the corresponding right extremity
    }
    if (y == 0) {  // if we are at a top extremity
      aux(g, c, previous_color, x,
          game_height(c_g) -
              1);  // color the the corresponding bottom extremity
    }
    if (y == game_height(c_g) - 1) {    // if we are at a bottom extremity
      aux(g, c, previous_color, x, 0);  // color the corresponding top extremity
    }
  }
  aux(g, c, previous_color, x + 1, y);  // right
  aux(g, c, previous_color, x - 1, y);  // left
  aux(g, c, previous_color, x, y + 1);  // down
  aux(g, c, previous_color, x, y - 1);  // up
}

void game_play_one_move(game g, color c) {
  assert(g);                             // check pointer
  color previous_color = g->tabGame[0];  // we save the previous_color (0,0);
  aux(g, c, previous_color, 0, 0);       // algorithm that will fill the grid
  g->currentMove++;                      // increment currentMove
}

// return the clone of the game g
game game_copy(cgame g) {
  assert(g);
  assert(g->tabGame);
  assert(g->cpyTabGame);
  game copy =
      game_new_ext(game_width(g), game_height(g), g->tabGame,
                   game_nb_moves_max(g), game_is_wrapping(g));  // create
  copy->currentMove = g->currentMove;
  return copy;
}

void game_delete(game g) {
  assert(g);
  if (g->tabGame != NULL) {
    free(g->tabGame);
  }
  if (g->cpyTabGame != NULL) {
    free(g->cpyTabGame);
  }
  free(g);
  g = NULL;
  return;
}

static bool same_color(cgame g) {  // function that return true if all of the
                                   // cells are same colors else return false;
  assert(g);
  assert(g->tabGame);
  for (uint i = 0; i < g->height * g->width; i++) {
    if (g->tabGame[0] != g->tabGame[i]) {
      return false;
    }
  }
  return true;
}

// return true, if the game is over, false otherwise
bool game_is_over(cgame g) {
  assert(g);
  assert(g->tabGame);
  if (game_nb_moves_cur(g) <= game_nb_moves_max(g) &&
      same_color(g) == true) {  //
    return true;
  }
  return false;
}

static bool is_game_copy_uniform(game g) {
  uint color = g->cpyTabGame[0];
  for (uint i = 1; i < game_width(g) * game_height(g); i++) {
    if (g->cpyTabGame[i] != color) {
      return false;
    }
  }
  return true;
}

void game_restart(game g) {
  assert(g);
  assert(g->tabGame);
  assert(g->cpyTabGame);
  g->currentMove = 0;
  if (is_game_copy_uniform(g)) {
    for (uint i = 0; i < game_width(g) * game_height(g); i++) {
      g->cpyTabGame[i] = g->tabGame[i];
    }
  }
  for (uint i = 0; i < g->height * g->width; i++) {
    g->tabGame[i] = g->cpyTabGame[i];
  }
}

///////////////////////// V2 /////////////////////////

// return false if the game has a "wall" at the limits of the array, else return
// false
bool game_is_wrapping(cgame g) {
  assert(g);
  if (!g->wrap_status) {
    return false;
  }
  return true;
}

game game_new_empty_ext(uint width, uint height, bool wrapping) {
  assert(width > 0);   // check width
  assert(height > 0);  // check height
  game g = (struct game_s*)malloc(
      sizeof(struct game_s));  // allocation memory for struct game_s
  assert(g);                   // check for error allocation
  g->tabGame =
      (color*)malloc(sizeof(color) * width *
                     height);  // arrray that will be the grid of the game
  g->cpyTabGame = (color*)malloc(sizeof(color) * width *
                                 height);  // array that store the initial grid
  assert(g->tabGame);
  assert(g->cpyTabGame);  // check for allocation errors
  g->height = height;     // initialize height
  g->width = width;       // initialize width
  g->nbMaxMoves = 0;
  g->currentMove = 0;  // moves are all set to 0
  for (uint i = 0; i < width * height; i++) {
    g->tabGame[i] = RED;
    g->cpyTabGame[i] = RED;  // We fill all of the grid with the color RED
  }
  if (wrapping == true) {
    g->wrap_status = true;  // we set the wrapping status;
  } else {
    g->wrap_status = false;
  }
  return g;
}

game game_new_ext(uint width, uint height, color* cells, uint nb_moves_max,
                  bool wrapping) {
  assert(width > 0);
  assert(height > 0);
  assert(cells);
  // assert(nb_moves_max >= 0);

  game g = (struct game_s*)malloc(sizeof(struct game_s));
  assert(g);
  g->tabGame = (color*)malloc(sizeof(color) * height * width);
  g->cpyTabGame = (color*)malloc(sizeof(color) * height * width);
  assert(g->tabGame);
  assert(g->cpyTabGame);
  for (uint i = 0; i < height * width; i++) {
    g->tabGame[i] = cells[i];
    g->cpyTabGame[i] = cells[i];
  }

  g->height = height;
  g->width = width;
  g->nbMaxMoves = nb_moves_max;
  g->currentMove = 0;
  if (wrapping == true) {
    g->wrap_status = true;
  } else {
    g->wrap_status = false;
  }
  return g;
}

uint game_height(cgame game) {
  assert(game);
  return game->height;
}

uint game_width(cgame game) {
  assert(game);
  return game->width;
}
