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
include doc/snippets/CMakeFiles/compile_MatrixBase_cwiseArg.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include doc/snippets/CMakeFiles/compile_MatrixBase_cwiseArg.dir/compiler_depend.make

# Include the progress variables for this target.
include doc/snippets/CMakeFiles/compile_MatrixBase_cwiseArg.dir/progress.make

# Include the compile flags for this target's objects.
include doc/snippets/CMakeFiles/compile_MatrixBase_cwiseArg.dir/flags.make

doc/snippets/CMakeFiles/compile_MatrixBase_cwiseArg.dir/compile_MatrixBase_cwiseArg.cpp.o: doc/snippets/CMakeFiles/compile_MatrixBase_cwiseArg.dir/flags.make
doc/snippets/CMakeFiles/compile_MatrixBase_cwiseArg.dir/compile_MatrixBase_cwiseArg.cpp.o: doc/snippets/compile_MatrixBase_cwiseArg.cpp
doc/snippets/CMakeFiles/compile_MatrixBase_cwiseArg.dir/compile_MatrixBase_cwiseArg.cpp.o: /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/Programming_assignments/Chapter_5/include/eigen/doc/snippets/MatrixBase_cwiseArg.cpp
doc/snippets/CMakeFiles/compile_MatrixBase_cwiseArg.dir/compile_MatrixBase_cwiseArg.cpp.o: doc/snippets/CMakeFiles/compile_MatrixBase_cwiseArg.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object doc/snippets/CMakeFiles/compile_MatrixBase_cwiseArg.dir/compile_MatrixBase_cwiseArg.cpp.o"
	cd /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/doc/snippets && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT doc/snippets/CMakeFiles/compile_MatrixBase_cwiseArg.dir/compile_MatrixBase_cwiseArg.cpp.o -MF CMakeFiles/compile_MatrixBase_cwiseArg.dir/compile_MatrixBase_cwiseArg.cpp.o.d -o CMakeFiles/compile_MatrixBase_cwiseArg.dir/compile_MatrixBase_cwiseArg.cpp.o -c /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/doc/snippets/compile_MatrixBase_cwiseArg.cpp

doc/snippets/CMakeFiles/compile_MatrixBase_cwiseArg.dir/compile_MatrixBase_cwiseArg.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/compile_MatrixBase_cwiseArg.dir/compile_MatrixBase_cwiseArg.cpp.i"
	cd /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/doc/snippets && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/doc/snippets/compile_MatrixBase_cwiseArg.cpp > CMakeFiles/compile_MatrixBase_cwiseArg.dir/compile_MatrixBase_cwiseArg.cpp.i

doc/snippets/CMakeFiles/compile_MatrixBase_cwiseArg.dir/compile_MatrixBase_cwiseArg.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/compile_MatrixBase_cwiseArg.dir/compile_MatrixBase_cwiseArg.cpp.s"
	cd /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/doc/snippets && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/doc/snippets/compile_MatrixBase_cwiseArg.cpp -o CMakeFiles/compile_MatrixBase_cwiseArg.dir/compile_MatrixBase_cwiseArg.cpp.s

# Object files for target compile_MatrixBase_cwiseArg
compile_MatrixBase_cwiseArg_OBJECTS = \
"CMakeFiles/compile_MatrixBase_cwiseArg.dir/compile_MatrixBase_cwiseArg.cpp.o"

# External object files for target compile_MatrixBase_cwiseArg
compile_MatrixBase_cwiseArg_EXTERNAL_OBJECTS =

doc/snippets/compile_MatrixBase_cwiseArg: doc/snippets/CMakeFiles/compile_MatrixBase_cwiseArg.dir/compile_MatrixBase_cwiseArg.cpp.o
doc/snippets/compile_MatrixBase_cwiseArg: doc/snippets/CMakeFiles/compile_MatrixBase_cwiseArg.dir/build.make
doc/snippets/compile_MatrixBase_cwiseArg: doc/snippets/CMakeFiles/compile_MatrixBase_cwiseArg.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable compile_MatrixBase_cwiseArg"
	cd /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/doc/snippets && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/compile_MatrixBase_cwiseArg.dir/link.txt --verbose=$(VERBOSE)
	cd /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/doc/snippets && ./compile_MatrixBase_cwiseArg >/Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/doc/snippets/MatrixBase_cwiseArg.out

# Rule to build all files generated by this target.
doc/snippets/CMakeFiles/compile_MatrixBase_cwiseArg.dir/build: doc/snippets/compile_MatrixBase_cwiseArg
.PHONY : doc/snippets/CMakeFiles/compile_MatrixBase_cwiseArg.dir/build

doc/snippets/CMakeFiles/compile_MatrixBase_cwiseArg.dir/clean:
	cd /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/doc/snippets && $(CMAKE_COMMAND) -P CMakeFiles/compile_MatrixBase_cwiseArg.dir/cmake_clean.cmake
.PHONY : doc/snippets/CMakeFiles/compile_MatrixBase_cwiseArg.dir/clean

doc/snippets/CMakeFiles/compile_MatrixBase_cwiseArg.dir/depend:
	cd /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/Programming_assignments/Chapter_5/include/eigen /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/Programming_assignments/Chapter_5/include/eigen/doc/snippets /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/doc/snippets /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/doc/snippets/CMakeFiles/compile_MatrixBase_cwiseArg.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : doc/snippets/CMakeFiles/compile_MatrixBase_cwiseArg.dir/depend

