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
include blas/testing/CMakeFiles/cblat3.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include blas/testing/CMakeFiles/cblat3.dir/compiler_depend.make

# Include the progress variables for this target.
include blas/testing/CMakeFiles/cblat3.dir/progress.make

# Include the compile flags for this target's objects.
include blas/testing/CMakeFiles/cblat3.dir/flags.make

blas/testing/CMakeFiles/cblat3.dir/cblat3.f.o: blas/testing/CMakeFiles/cblat3.dir/flags.make
blas/testing/CMakeFiles/cblat3.dir/cblat3.f.o: /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/Programming_assignments/Chapter_5/include/eigen/blas/testing/cblat3.f
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building Fortran object blas/testing/CMakeFiles/cblat3.dir/cblat3.f.o"
	cd /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/blas/testing && /opt/homebrew/bin/gfortran $(Fortran_DEFINES) $(Fortran_INCLUDES) $(Fortran_FLAGS) -c /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/Programming_assignments/Chapter_5/include/eigen/blas/testing/cblat3.f -o CMakeFiles/cblat3.dir/cblat3.f.o

blas/testing/CMakeFiles/cblat3.dir/cblat3.f.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing Fortran source to CMakeFiles/cblat3.dir/cblat3.f.i"
	cd /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/blas/testing && /opt/homebrew/bin/gfortran $(Fortran_DEFINES) $(Fortran_INCLUDES) $(Fortran_FLAGS) -E /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/Programming_assignments/Chapter_5/include/eigen/blas/testing/cblat3.f > CMakeFiles/cblat3.dir/cblat3.f.i

blas/testing/CMakeFiles/cblat3.dir/cblat3.f.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling Fortran source to assembly CMakeFiles/cblat3.dir/cblat3.f.s"
	cd /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/blas/testing && /opt/homebrew/bin/gfortran $(Fortran_DEFINES) $(Fortran_INCLUDES) $(Fortran_FLAGS) -S /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/Programming_assignments/Chapter_5/include/eigen/blas/testing/cblat3.f -o CMakeFiles/cblat3.dir/cblat3.f.s

# Object files for target cblat3
cblat3_OBJECTS = \
"CMakeFiles/cblat3.dir/cblat3.f.o"

# External object files for target cblat3
cblat3_EXTERNAL_OBJECTS =

blas/testing/cblat3: blas/testing/CMakeFiles/cblat3.dir/cblat3.f.o
blas/testing/cblat3: blas/testing/CMakeFiles/cblat3.dir/build.make
blas/testing/cblat3: blas/libeigen_blas.dylib
blas/testing/cblat3: blas/testing/CMakeFiles/cblat3.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking Fortran executable cblat3"
	cd /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/blas/testing && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cblat3.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
blas/testing/CMakeFiles/cblat3.dir/build: blas/testing/cblat3
.PHONY : blas/testing/CMakeFiles/cblat3.dir/build

blas/testing/CMakeFiles/cblat3.dir/clean:
	cd /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/blas/testing && $(CMAKE_COMMAND) -P CMakeFiles/cblat3.dir/cmake_clean.cmake
.PHONY : blas/testing/CMakeFiles/cblat3.dir/clean

blas/testing/CMakeFiles/cblat3.dir/depend:
	cd /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/Programming_assignments/Chapter_5/include/eigen /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/Programming_assignments/Chapter_5/include/eigen/blas/testing /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/blas/testing /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/blas/testing/CMakeFiles/cblat3.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : blas/testing/CMakeFiles/cblat3.dir/depend

