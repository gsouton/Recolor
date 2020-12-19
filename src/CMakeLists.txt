cmake_minimum_required(VERSION 3.7.2)

project(Game_recolor)


include_directories(${SDL2_ALL_INC})
add_executable(recolor_sdl sdl_recolor_text.c)
target_link_libraries(recolor_sdl ${SDL2_ALL_LIBS} m)
target_link_libraries(recolor_sdl game)

include_directories(${Game_recolor_SOURCE_DIR}/include)

add_library(game game.c game_io.c sdl_utilitary_functions.c utilitary_functions_solver.c game_rand.c)

add_executable(recolor_text recolor_text.c)
add_executable(recolor_solve recolor_solve.c)


target_link_libraries(recolor_text game)

target_link_libraries(recolor_solve game)







