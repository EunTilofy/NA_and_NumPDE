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
include doc/snippets/CMakeFiles/compile_SelfAdjointEigenSolver_operatorInverseSqrt.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include doc/snippets/CMakeFiles/compile_SelfAdjointEigenSolver_operatorInverseSqrt.dir/compiler_depend.make

# Include the progress variables for this target.
include doc/snippets/CMakeFiles/compile_SelfAdjointEigenSolver_operatorInverseSqrt.dir/progress.make

# Include the compile flags for this target's objects.
include doc/snippets/CMakeFiles/compile_SelfAdjointEigenSolver_operatorInverseSqrt.dir/flags.make

doc/snippets/CMakeFiles/compile_SelfAdjointEigenSolver_operatorInverseSqrt.dir/compile_SelfAdjointEigenSolver_operatorInverseSqrt.cpp.o: doc/snippets/CMakeFiles/compile_SelfAdjointEigenSolver_operatorInverseSqrt.dir/flags.make
doc/snippets/CMakeFiles/compile_SelfAdjointEigenSolver_operatorInverseSqrt.dir/compile_SelfAdjointEigenSolver_operatorInverseSqrt.cpp.o: doc/snippets/compile_SelfAdjointEigenSolver_operatorInverseSqrt.cpp
doc/snippets/CMakeFiles/compile_SelfAdjointEigenSolver_operatorInverseSqrt.dir/compile_SelfAdjointEigenSolver_operatorInverseSqrt.cpp.o: /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/Programming_assignments/Chapter_5/include/eigen/doc/snippets/SelfAdjointEigenSolver_operatorInverseSqrt.cpp
doc/snippets/CMakeFiles/compile_SelfAdjointEigenSolver_operatorInverseSqrt.dir/compile_SelfAdjointEigenSolver_operatorInverseSqrt.cpp.o: doc/snippets/CMakeFiles/compile_SelfAdjointEigenSolver_operatorInverseSqrt.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object doc/snippets/CMakeFiles/compile_SelfAdjointEigenSolver_operatorInverseSqrt.dir/compile_SelfAdjointEigenSolver_operatorInverseSqrt.cpp.o"
	cd /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/doc/snippets && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT doc/snippets/CMakeFiles/compile_SelfAdjointEigenSolver_operatorInverseSqrt.dir/compile_SelfAdjointEigenSolver_operatorInverseSqrt.cpp.o -MF CMakeFiles/compile_SelfAdjointEigenSolver_operatorInverseSqrt.dir/compile_SelfAdjointEigenSolver_operatorInverseSqrt.cpp.o.d -o CMakeFiles/compile_SelfAdjointEigenSolver_operatorInverseSqrt.dir/compile_SelfAdjointEigenSolver_operatorInverseSqrt.cpp.o -c /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/doc/snippets/compile_SelfAdjointEigenSolver_operatorInverseSqrt.cpp

doc/snippets/CMakeFiles/compile_SelfAdjointEigenSolver_operatorInverseSqrt.dir/compile_SelfAdjointEigenSolver_operatorInverseSqrt.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/compile_SelfAdjointEigenSolver_operatorInverseSqrt.dir/compile_SelfAdjointEigenSolver_operatorInverseSqrt.cpp.i"
	cd /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/doc/snippets && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/doc/snippets/compile_SelfAdjointEigenSolver_operatorInverseSqrt.cpp > CMakeFiles/compile_SelfAdjointEigenSolver_operatorInverseSqrt.dir/compile_SelfAdjointEigenSolver_operatorInverseSqrt.cpp.i

doc/snippets/CMakeFiles/compile_SelfAdjointEigenSolver_operatorInverseSqrt.dir/compile_SelfAdjointEigenSolver_operatorInverseSqrt.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/compile_SelfAdjointEigenSolver_operatorInverseSqrt.dir/compile_SelfAdjointEigenSolver_operatorInverseSqrt.cpp.s"
	cd /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/doc/snippets && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/doc/snippets/compile_SelfAdjointEigenSolver_operatorInverseSqrt.cpp -o CMakeFiles/compile_SelfAdjointEigenSolver_operatorInverseSqrt.dir/compile_SelfAdjointEigenSolver_operatorInverseSqrt.cpp.s

# Object files for target compile_SelfAdjointEigenSolver_operatorInverseSqrt
compile_SelfAdjointEigenSolver_operatorInverseSqrt_OBJECTS = \
"CMakeFiles/compile_SelfAdjointEigenSolver_operatorInverseSqrt.dir/compile_SelfAdjointEigenSolver_operatorInverseSqrt.cpp.o"

# External object files for target compile_SelfAdjointEigenSolver_operatorInverseSqrt
compile_SelfAdjointEigenSolver_operatorInverseSqrt_EXTERNAL_OBJECTS =

doc/snippets/compile_SelfAdjointEigenSolver_operatorInverseSqrt: doc/snippets/CMakeFiles/compile_SelfAdjointEigenSolver_operatorInverseSqrt.dir/compile_SelfAdjointEigenSolver_operatorInverseSqrt.cpp.o
doc/snippets/compile_SelfAdjointEigenSolver_operatorInverseSqrt: doc/snippets/CMakeFiles/compile_SelfAdjointEigenSolver_operatorInverseSqrt.dir/build.make
doc/snippets/compile_SelfAdjointEigenSolver_operatorInverseSqrt: doc/snippets/CMakeFiles/compile_SelfAdjointEigenSolver_operatorInverseSqrt.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable compile_SelfAdjointEigenSolver_operatorInverseSqrt"
	cd /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/doc/snippets && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/compile_SelfAdjointEigenSolver_operatorInverseSqrt.dir/link.txt --verbose=$(VERBOSE)
	cd /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/doc/snippets && ./compile_SelfAdjointEigenSolver_operatorInverseSqrt >/Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/doc/snippets/SelfAdjointEigenSolver_operatorInverseSqrt.out

# Rule to build all files generated by this target.
doc/snippets/CMakeFiles/compile_SelfAdjointEigenSolver_operatorInverseSqrt.dir/build: doc/snippets/compile_SelfAdjointEigenSolver_operatorInverseSqrt
.PHONY : doc/snippets/CMakeFiles/compile_SelfAdjointEigenSolver_operatorInverseSqrt.dir/build

doc/snippets/CMakeFiles/compile_SelfAdjointEigenSolver_operatorInverseSqrt.dir/clean:
	cd /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/doc/snippets && $(CMAKE_COMMAND) -P CMakeFiles/compile_SelfAdjointEigenSolver_operatorInverseSqrt.dir/cmake_clean.cmake
.PHONY : doc/snippets/CMakeFiles/compile_SelfAdjointEigenSolver_operatorInverseSqrt.dir/clean

doc/snippets/CMakeFiles/compile_SelfAdjointEigenSolver_operatorInverseSqrt.dir/depend:
	cd /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/Programming_assignments/Chapter_5/include/eigen /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/Programming_assignments/Chapter_5/include/eigen/doc/snippets /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/doc/snippets /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/doc/snippets/CMakeFiles/compile_SelfAdjointEigenSolver_operatorInverseSqrt.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : doc/snippets/CMakeFiles/compile_SelfAdjointEigenSolver_operatorInverseSqrt.dir/depend

