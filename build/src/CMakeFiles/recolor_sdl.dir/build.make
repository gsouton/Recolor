# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/gilles/Documents/projects/recolor-tdm4-c

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/gilles/Documents/projects/recolor-tdm4-c/build

# Include any dependencies generated for this target.
include src/CMakeFiles/recolor_sdl.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/recolor_sdl.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/recolor_sdl.dir/flags.make

src/CMakeFiles/recolor_sdl.dir/sdl_recolor_text.c.o: src/CMakeFiles/recolor_sdl.dir/flags.make
src/CMakeFiles/recolor_sdl.dir/sdl_recolor_text.c.o: ../src/sdl_recolor_text.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gilles/Documents/projects/recolor-tdm4-c/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object src/CMakeFiles/recolor_sdl.dir/sdl_recolor_text.c.o"
	cd /home/gilles/Documents/projects/recolor-tdm4-c/build/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/recolor_sdl.dir/sdl_recolor_text.c.o   -c /home/gilles/Documents/projects/recolor-tdm4-c/src/sdl_recolor_text.c

src/CMakeFiles/recolor_sdl.dir/sdl_recolor_text.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/recolor_sdl.dir/sdl_recolor_text.c.i"
	cd /home/gilles/Documents/projects/recolor-tdm4-c/build/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/gilles/Documents/projects/recolor-tdm4-c/src/sdl_recolor_text.c > CMakeFiles/recolor_sdl.dir/sdl_recolor_text.c.i

src/CMakeFiles/recolor_sdl.dir/sdl_recolor_text.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/recolor_sdl.dir/sdl_recolor_text.c.s"
	cd /home/gilles/Documents/projects/recolor-tdm4-c/build/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/gilles/Documents/projects/recolor-tdm4-c/src/sdl_recolor_text.c -o CMakeFiles/recolor_sdl.dir/sdl_recolor_text.c.s

# Object files for target recolor_sdl
recolor_sdl_OBJECTS = \
"CMakeFiles/recolor_sdl.dir/sdl_recolor_text.c.o"

# External object files for target recolor_sdl
recolor_sdl_EXTERNAL_OBJECTS =

src/recolor_sdl: src/CMakeFiles/recolor_sdl.dir/sdl_recolor_text.c.o
src/recolor_sdl: src/CMakeFiles/recolor_sdl.dir/build.make
src/recolor_sdl: src/libgame.a
src/recolor_sdl: src/CMakeFiles/recolor_sdl.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/gilles/Documents/projects/recolor-tdm4-c/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable recolor_sdl"
	cd /home/gilles/Documents/projects/recolor-tdm4-c/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/recolor_sdl.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/recolor_sdl.dir/build: src/recolor_sdl

.PHONY : src/CMakeFiles/recolor_sdl.dir/build

src/CMakeFiles/recolor_sdl.dir/clean:
	cd /home/gilles/Documents/projects/recolor-tdm4-c/build/src && $(CMAKE_COMMAND) -P CMakeFiles/recolor_sdl.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/recolor_sdl.dir/clean

src/CMakeFiles/recolor_sdl.dir/depend:
	cd /home/gilles/Documents/projects/recolor-tdm4-c/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/gilles/Documents/projects/recolor-tdm4-c /home/gilles/Documents/projects/recolor-tdm4-c/src /home/gilles/Documents/projects/recolor-tdm4-c/build /home/gilles/Documents/projects/recolor-tdm4-c/build/src /home/gilles/Documents/projects/recolor-tdm4-c/build/src/CMakeFiles/recolor_sdl.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/recolor_sdl.dir/depend
