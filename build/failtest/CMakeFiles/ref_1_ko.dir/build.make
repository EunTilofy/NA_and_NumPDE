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
include failtest/CMakeFiles/ref_1_ko.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include failtest/CMakeFiles/ref_1_ko.dir/compiler_depend.make

# Include the progress variables for this target.
include failtest/CMakeFiles/ref_1_ko.dir/progress.make

# Include the compile flags for this target's objects.
include failtest/CMakeFiles/ref_1_ko.dir/flags.make

failtest/CMakeFiles/ref_1_ko.dir/ref_1.cpp.o: failtest/CMakeFiles/ref_1_ko.dir/flags.make
failtest/CMakeFiles/ref_1_ko.dir/ref_1.cpp.o: /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/Programming_assignments/Chapter_5/include/eigen/failtest/ref_1.cpp
failtest/CMakeFiles/ref_1_ko.dir/ref_1.cpp.o: failtest/CMakeFiles/ref_1_ko.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object failtest/CMakeFiles/ref_1_ko.dir/ref_1.cpp.o"
	cd /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/failtest && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT failtest/CMakeFiles/ref_1_ko.dir/ref_1.cpp.o -MF CMakeFiles/ref_1_ko.dir/ref_1.cpp.o.d -o CMakeFiles/ref_1_ko.dir/ref_1.cpp.o -c /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/Programming_assignments/Chapter_5/include/eigen/failtest/ref_1.cpp

failtest/CMakeFiles/ref_1_ko.dir/ref_1.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ref_1_ko.dir/ref_1.cpp.i"
	cd /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/failtest && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/Programming_assignments/Chapter_5/include/eigen/failtest/ref_1.cpp > CMakeFiles/ref_1_ko.dir/ref_1.cpp.i

failtest/CMakeFiles/ref_1_ko.dir/ref_1.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ref_1_ko.dir/ref_1.cpp.s"
	cd /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/failtest && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/Programming_assignments/Chapter_5/include/eigen/failtest/ref_1.cpp -o CMakeFiles/ref_1_ko.dir/ref_1.cpp.s

# Object files for target ref_1_ko
ref_1_ko_OBJECTS = \
"CMakeFiles/ref_1_ko.dir/ref_1.cpp.o"

# External object files for target ref_1_ko
ref_1_ko_EXTERNAL_OBJECTS =

failtest/ref_1_ko: failtest/CMakeFiles/ref_1_ko.dir/ref_1.cpp.o
failtest/ref_1_ko: failtest/CMakeFiles/ref_1_ko.dir/build.make
failtest/ref_1_ko: failtest/CMakeFiles/ref_1_ko.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ref_1_ko"
	cd /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/failtest && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ref_1_ko.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
failtest/CMakeFiles/ref_1_ko.dir/build: failtest/ref_1_ko
.PHONY : failtest/CMakeFiles/ref_1_ko.dir/build

failtest/CMakeFiles/ref_1_ko.dir/clean:
	cd /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/failtest && $(CMAKE_COMMAND) -P CMakeFiles/ref_1_ko.dir/cmake_clean.cmake
.PHONY : failtest/CMakeFiles/ref_1_ko.dir/clean

failtest/CMakeFiles/ref_1_ko.dir/depend:
	cd /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/Programming_assignments/Chapter_5/include/eigen /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/Programming_assignments/Chapter_5/include/eigen/failtest /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/failtest /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/failtest/CMakeFiles/ref_1_ko.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : failtest/CMakeFiles/ref_1_ko.dir/depend

