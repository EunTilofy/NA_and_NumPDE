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
include test/CMakeFiles/commainitializer_1.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include test/CMakeFiles/commainitializer_1.dir/compiler_depend.make

# Include the progress variables for this target.
include test/CMakeFiles/commainitializer_1.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/commainitializer_1.dir/flags.make

test/CMakeFiles/commainitializer_1.dir/commainitializer.cpp.o: test/CMakeFiles/commainitializer_1.dir/flags.make
test/CMakeFiles/commainitializer_1.dir/commainitializer.cpp.o: /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/Programming_assignments/Chapter_5/include/eigen/test/commainitializer.cpp
test/CMakeFiles/commainitializer_1.dir/commainitializer.cpp.o: test/CMakeFiles/commainitializer_1.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/CMakeFiles/commainitializer_1.dir/commainitializer.cpp.o"
	cd /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/test && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT test/CMakeFiles/commainitializer_1.dir/commainitializer.cpp.o -MF CMakeFiles/commainitializer_1.dir/commainitializer.cpp.o.d -o CMakeFiles/commainitializer_1.dir/commainitializer.cpp.o -c /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/Programming_assignments/Chapter_5/include/eigen/test/commainitializer.cpp

test/CMakeFiles/commainitializer_1.dir/commainitializer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/commainitializer_1.dir/commainitializer.cpp.i"
	cd /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/test && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/Programming_assignments/Chapter_5/include/eigen/test/commainitializer.cpp > CMakeFiles/commainitializer_1.dir/commainitializer.cpp.i

test/CMakeFiles/commainitializer_1.dir/commainitializer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/commainitializer_1.dir/commainitializer.cpp.s"
	cd /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/test && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/Programming_assignments/Chapter_5/include/eigen/test/commainitializer.cpp -o CMakeFiles/commainitializer_1.dir/commainitializer.cpp.s

# Object files for target commainitializer_1
commainitializer_1_OBJECTS = \
"CMakeFiles/commainitializer_1.dir/commainitializer.cpp.o"

# External object files for target commainitializer_1
commainitializer_1_EXTERNAL_OBJECTS =

test/commainitializer_1: test/CMakeFiles/commainitializer_1.dir/commainitializer.cpp.o
test/commainitializer_1: test/CMakeFiles/commainitializer_1.dir/build.make
test/commainitializer_1: test/CMakeFiles/commainitializer_1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable commainitializer_1"
	cd /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/commainitializer_1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/commainitializer_1.dir/build: test/commainitializer_1
.PHONY : test/CMakeFiles/commainitializer_1.dir/build

test/CMakeFiles/commainitializer_1.dir/clean:
	cd /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/test && $(CMAKE_COMMAND) -P CMakeFiles/commainitializer_1.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/commainitializer_1.dir/clean

test/CMakeFiles/commainitializer_1.dir/depend:
	cd /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/Programming_assignments/Chapter_5/include/eigen /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/Programming_assignments/Chapter_5/include/eigen/test /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/test /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/test/CMakeFiles/commainitializer_1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/commainitializer_1.dir/depend

