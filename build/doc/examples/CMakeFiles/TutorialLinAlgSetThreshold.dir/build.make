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
include doc/examples/CMakeFiles/TutorialLinAlgSetThreshold.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include doc/examples/CMakeFiles/TutorialLinAlgSetThreshold.dir/compiler_depend.make

# Include the progress variables for this target.
include doc/examples/CMakeFiles/TutorialLinAlgSetThreshold.dir/progress.make

# Include the compile flags for this target's objects.
include doc/examples/CMakeFiles/TutorialLinAlgSetThreshold.dir/flags.make

doc/examples/CMakeFiles/TutorialLinAlgSetThreshold.dir/TutorialLinAlgSetThreshold.cpp.o: doc/examples/CMakeFiles/TutorialLinAlgSetThreshold.dir/flags.make
doc/examples/CMakeFiles/TutorialLinAlgSetThreshold.dir/TutorialLinAlgSetThreshold.cpp.o: /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/Programming_assignments/Chapter_5/include/eigen/doc/examples/TutorialLinAlgSetThreshold.cpp
doc/examples/CMakeFiles/TutorialLinAlgSetThreshold.dir/TutorialLinAlgSetThreshold.cpp.o: doc/examples/CMakeFiles/TutorialLinAlgSetThreshold.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object doc/examples/CMakeFiles/TutorialLinAlgSetThreshold.dir/TutorialLinAlgSetThreshold.cpp.o"
	cd /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/doc/examples && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT doc/examples/CMakeFiles/TutorialLinAlgSetThreshold.dir/TutorialLinAlgSetThreshold.cpp.o -MF CMakeFiles/TutorialLinAlgSetThreshold.dir/TutorialLinAlgSetThreshold.cpp.o.d -o CMakeFiles/TutorialLinAlgSetThreshold.dir/TutorialLinAlgSetThreshold.cpp.o -c /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/Programming_assignments/Chapter_5/include/eigen/doc/examples/TutorialLinAlgSetThreshold.cpp

doc/examples/CMakeFiles/TutorialLinAlgSetThreshold.dir/TutorialLinAlgSetThreshold.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TutorialLinAlgSetThreshold.dir/TutorialLinAlgSetThreshold.cpp.i"
	cd /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/doc/examples && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/Programming_assignments/Chapter_5/include/eigen/doc/examples/TutorialLinAlgSetThreshold.cpp > CMakeFiles/TutorialLinAlgSetThreshold.dir/TutorialLinAlgSetThreshold.cpp.i

doc/examples/CMakeFiles/TutorialLinAlgSetThreshold.dir/TutorialLinAlgSetThreshold.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TutorialLinAlgSetThreshold.dir/TutorialLinAlgSetThreshold.cpp.s"
	cd /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/doc/examples && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/Programming_assignments/Chapter_5/include/eigen/doc/examples/TutorialLinAlgSetThreshold.cpp -o CMakeFiles/TutorialLinAlgSetThreshold.dir/TutorialLinAlgSetThreshold.cpp.s

# Object files for target TutorialLinAlgSetThreshold
TutorialLinAlgSetThreshold_OBJECTS = \
"CMakeFiles/TutorialLinAlgSetThreshold.dir/TutorialLinAlgSetThreshold.cpp.o"

# External object files for target TutorialLinAlgSetThreshold
TutorialLinAlgSetThreshold_EXTERNAL_OBJECTS =

doc/examples/TutorialLinAlgSetThreshold: doc/examples/CMakeFiles/TutorialLinAlgSetThreshold.dir/TutorialLinAlgSetThreshold.cpp.o
doc/examples/TutorialLinAlgSetThreshold: doc/examples/CMakeFiles/TutorialLinAlgSetThreshold.dir/build.make
doc/examples/TutorialLinAlgSetThreshold: doc/examples/CMakeFiles/TutorialLinAlgSetThreshold.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable TutorialLinAlgSetThreshold"
	cd /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/doc/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TutorialLinAlgSetThreshold.dir/link.txt --verbose=$(VERBOSE)
	cd /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/doc/examples && ./TutorialLinAlgSetThreshold >/Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/doc/examples/TutorialLinAlgSetThreshold.out

# Rule to build all files generated by this target.
doc/examples/CMakeFiles/TutorialLinAlgSetThreshold.dir/build: doc/examples/TutorialLinAlgSetThreshold
.PHONY : doc/examples/CMakeFiles/TutorialLinAlgSetThreshold.dir/build

doc/examples/CMakeFiles/TutorialLinAlgSetThreshold.dir/clean:
	cd /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/doc/examples && $(CMAKE_COMMAND) -P CMakeFiles/TutorialLinAlgSetThreshold.dir/cmake_clean.cmake
.PHONY : doc/examples/CMakeFiles/TutorialLinAlgSetThreshold.dir/clean

doc/examples/CMakeFiles/TutorialLinAlgSetThreshold.dir/depend:
	cd /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/Programming_assignments/Chapter_5/include/eigen /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/Programming_assignments/Chapter_5/include/eigen/doc/examples /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/doc/examples /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/doc/examples/CMakeFiles/TutorialLinAlgSetThreshold.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : doc/examples/CMakeFiles/TutorialLinAlgSetThreshold.dir/depend

