# Recolor
University Project
## Overview

It's a game (also university project) where you are given a grid with cells of different colors,
And your goal is to color the grid entirely with one color.
To accomplish that the rules are really simple:

* You can choose beetween a predifined number of colors.
* You will always change the color in the top left corner of the grid.
* Any cells that is directly in contact (left, right, up, down) with the current color cell will see his color change.
* You have limited number of choices if you don't manage to recolor the grid before this number arrive to 0 it's Game over.

## Setup
You can either create your own build directory and then use cmake or run setup.sh

* Choice 1:\
    ./setup.sh
 
* Choice 2:\
    mkdir build\
      cd build\
      cmake ..\
      make
 
Then you will find executables in build/src

* recolor_sdl is the game with a graphical interface implemented with SDL.
* recolor_text is a game within the terminal without graphical interface.
* recolor_solve is a solver able to find certain solutions for a given game in parameters through a file **Still working on this**.

## Important
You will need:
    * cmake 
    * SLD2

   
 
 
