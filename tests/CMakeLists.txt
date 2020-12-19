cmake_minimum_required(VERSION 3.7.2)

project(Game_recolor)


include_directories(${MyProject_SOURCE_DIR}/LibProject/inc)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}../src)


add_executable(test_game_gsouton test_game_gsouton.c)
add_executable(test_game_alemarty test_game_alemarty.c)
add_executable(test_game_tlaveau test_game_tlaveau.c)
add_executable(test_game_klaveau test_game_klaveau.c)


target_link_libraries(test_game_gsouton game)
target_link_libraries(test_game_tlaveau game)
target_link_libraries(test_game_alemarty game)
target_link_libraries(test_game_klaveau game)


add_custom_target(test_gsouton
  COMMAND ./test_game_gsouton game_copy
  COMMAND ./test_game_gsouton game_is_over
  COMMAND ./test_game_gsouton game_play_one_move
  COMMAND ./test_game_gsouton game_is_wrapping
  COMMAND ./test_game_gsouton game_new_empty_ext
  COMMAND ./test_game_gsouton game_new_ext
  COMMAND ./test_game_gsouton game_width
  COMMAND ./test_game_gsouton game_height)

add_custom_target(test_alemarty
  COMMAND ./test_game_alemarty game_set_cell_init
  COMMAND ./test_game_alemarty game_set_max_moves
  COMMAND ./test_game_alemarty game_nb_moves_max
  COMMAND ./test_game_alemarty game_load
  COMMAND ./test_game_alemarty game_save)

add_custom_target(test_klaveau
  COMMAND ./test_game_klaveau game_restart
  COMMAND ./test_game_klaveau game_nb_moves_cur
  COMMAND ./test_game_klaveau game_delete)

add_custom_target(test_tlaveau
  COMMAND ./test_game_tlaveau game_new
  COMMAND ./test_game_tlaveau game_cell_current_color
  COMMAND ./test_game_tlaveau game_new_empty)

add_dependencies(test_gsouton test_game_gsouton)
add_dependencies(test_alemarty test_game_alemarty)
add_dependencies(test_tlaveau test_game_tlaveau)
add_dependencies(test_klaveau test_game_klaveau)

add_test(test make test_gsouton test_alemarty test_tlaveau test_klaveau)



