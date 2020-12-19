#!/usr/bin/bash

build=build

game=recolor_text
solver=recolor_solve
sdl_game=recolor_sdl


if $(mkdir $build) 
then
	echo -e "Create a build repository"
fi

echo -e "Moving into the build directory --> $(pwd)/$build"
cd $build

echo -e "cmake ../"
cmake ../

echo -e "Makefile"
make





