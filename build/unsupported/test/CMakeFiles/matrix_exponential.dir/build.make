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

# Utility rule file for matrix_exponential.

# Include any custom commands dependencies for this target.
include unsupported/test/CMakeFiles/matrix_exponential.dir/compiler_depend.make

# Include the progress variables for this target.
include unsupported/test/CMakeFiles/matrix_exponential.dir/progress.make

matrix_exponential: unsupported/test/CMakeFiles/matrix_exponential.dir/build.make
.PHONY : matrix_exponential

# Rule to build all files generated by this target.
unsupported/test/CMakeFiles/matrix_exponential.dir/build: matrix_exponential
.PHONY : unsupported/test/CMakeFiles/matrix_exponential.dir/build

unsupported/test/CMakeFiles/matrix_exponential.dir/clean:
	cd /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/unsupported/test && $(CMAKE_COMMAND) -P CMakeFiles/matrix_exponential.dir/cmake_clean.cmake
.PHONY : unsupported/test/CMakeFiles/matrix_exponential.dir/clean

unsupported/test/CMakeFiles/matrix_exponential.dir/depend:
	cd /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/Programming_assignments/Chapter_5/include/eigen /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/Programming_assignments/Chapter_5/include/eigen/unsupported/test /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/unsupported/test /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/unsupported/test/CMakeFiles/matrix_exponential.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : unsupported/test/CMakeFiles/matrix_exponential.dir/depend

