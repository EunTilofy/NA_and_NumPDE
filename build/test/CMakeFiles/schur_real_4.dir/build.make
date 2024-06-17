# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.26.4/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.26.4/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/Programming_assignments/Chapter_5/include/eigen

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build

# Include any dependencies generated for this target.
include test/CMakeFiles/schur_real_4.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include test/CMakeFiles/schur_real_4.dir/compiler_depend.make

# Include the progress variables for this target.
include test/CMakeFiles/schur_real_4.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/schur_real_4.dir/flags.make

test/CMakeFiles/schur_real_4.dir/schur_real.cpp.o: test/CMakeFiles/schur_real_4.dir/flags.make
test/CMakeFiles/schur_real_4.dir/schur_real.cpp.o: /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/Programming_assignments/Chapter_5/include/eigen/test/schur_real.cpp
test/CMakeFiles/schur_real_4.dir/schur_real.cpp.o: test/CMakeFiles/schur_real_4.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/CMakeFiles/schur_real_4.dir/schur_real.cpp.o"
	cd /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/test && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT test/CMakeFiles/schur_real_4.dir/schur_real.cpp.o -MF CMakeFiles/schur_real_4.dir/schur_real.cpp.o.d -o CMakeFiles/schur_real_4.dir/schur_real.cpp.o -c /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/Programming_assignments/Chapter_5/include/eigen/test/schur_real.cpp

test/CMakeFiles/schur_real_4.dir/schur_real.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/schur_real_4.dir/schur_real.cpp.i"
	cd /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/test && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/Programming_assignments/Chapter_5/include/eigen/test/schur_real.cpp > CMakeFiles/schur_real_4.dir/schur_real.cpp.i

test/CMakeFiles/schur_real_4.dir/schur_real.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/schur_real_4.dir/schur_real.cpp.s"
	cd /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/test && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/Programming_assignments/Chapter_5/include/eigen/test/schur_real.cpp -o CMakeFiles/schur_real_4.dir/schur_real.cpp.s

# Object files for target schur_real_4
schur_real_4_OBJECTS = \
"CMakeFiles/schur_real_4.dir/schur_real.cpp.o"

# External object files for target schur_real_4
schur_real_4_EXTERNAL_OBJECTS =

test/schur_real_4: test/CMakeFiles/schur_real_4.dir/schur_real.cpp.o
test/schur_real_4: test/CMakeFiles/schur_real_4.dir/build.make
test/schur_real_4: test/CMakeFiles/schur_real_4.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable schur_real_4"
	cd /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/schur_real_4.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/schur_real_4.dir/build: test/schur_real_4
.PHONY : test/CMakeFiles/schur_real_4.dir/build

test/CMakeFiles/schur_real_4.dir/clean:
	cd /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/test && $(CMAKE_COMMAND) -P CMakeFiles/schur_real_4.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/schur_real_4.dir/clean

test/CMakeFiles/schur_real_4.dir/depend:
	cd /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/Programming_assignments/Chapter_5/include/eigen /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/Programming_assignments/Chapter_5/include/eigen/test /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/test /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/test/CMakeFiles/schur_real_4.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/schur_real_4.dir/depend

