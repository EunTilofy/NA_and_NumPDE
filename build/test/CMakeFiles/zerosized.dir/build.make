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
include test/CMakeFiles/zerosized.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include test/CMakeFiles/zerosized.dir/compiler_depend.make

# Include the progress variables for this target.
include test/CMakeFiles/zerosized.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/zerosized.dir/flags.make

test/CMakeFiles/zerosized.dir/zerosized.cpp.o: test/CMakeFiles/zerosized.dir/flags.make
test/CMakeFiles/zerosized.dir/zerosized.cpp.o: /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/Programming_assignments/Chapter_5/include/eigen/test/zerosized.cpp
test/CMakeFiles/zerosized.dir/zerosized.cpp.o: test/CMakeFiles/zerosized.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/CMakeFiles/zerosized.dir/zerosized.cpp.o"
	cd /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/test && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT test/CMakeFiles/zerosized.dir/zerosized.cpp.o -MF CMakeFiles/zerosized.dir/zerosized.cpp.o.d -o CMakeFiles/zerosized.dir/zerosized.cpp.o -c /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/Programming_assignments/Chapter_5/include/eigen/test/zerosized.cpp

test/CMakeFiles/zerosized.dir/zerosized.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/zerosized.dir/zerosized.cpp.i"
	cd /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/test && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/Programming_assignments/Chapter_5/include/eigen/test/zerosized.cpp > CMakeFiles/zerosized.dir/zerosized.cpp.i

test/CMakeFiles/zerosized.dir/zerosized.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/zerosized.dir/zerosized.cpp.s"
	cd /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/test && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/Programming_assignments/Chapter_5/include/eigen/test/zerosized.cpp -o CMakeFiles/zerosized.dir/zerosized.cpp.s

# Object files for target zerosized
zerosized_OBJECTS = \
"CMakeFiles/zerosized.dir/zerosized.cpp.o"

# External object files for target zerosized
zerosized_EXTERNAL_OBJECTS =

test/zerosized: test/CMakeFiles/zerosized.dir/zerosized.cpp.o
test/zerosized: test/CMakeFiles/zerosized.dir/build.make
test/zerosized: test/CMakeFiles/zerosized.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable zerosized"
	cd /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/zerosized.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/zerosized.dir/build: test/zerosized
.PHONY : test/CMakeFiles/zerosized.dir/build

test/CMakeFiles/zerosized.dir/clean:
	cd /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/test && $(CMAKE_COMMAND) -P CMakeFiles/zerosized.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/zerosized.dir/clean

test/CMakeFiles/zerosized.dir/depend:
	cd /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/Programming_assignments/Chapter_5/include/eigen /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/Programming_assignments/Chapter_5/include/eigen/test /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/test /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/test/CMakeFiles/zerosized.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/zerosized.dir/depend

