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
include doc/examples/CMakeFiles/class_CwiseUnaryOp_ptrfun.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include doc/examples/CMakeFiles/class_CwiseUnaryOp_ptrfun.dir/compiler_depend.make

# Include the progress variables for this target.
include doc/examples/CMakeFiles/class_CwiseUnaryOp_ptrfun.dir/progress.make

# Include the compile flags for this target's objects.
include doc/examples/CMakeFiles/class_CwiseUnaryOp_ptrfun.dir/flags.make

doc/examples/CMakeFiles/class_CwiseUnaryOp_ptrfun.dir/class_CwiseUnaryOp_ptrfun.cpp.o: doc/examples/CMakeFiles/class_CwiseUnaryOp_ptrfun.dir/flags.make
doc/examples/CMakeFiles/class_CwiseUnaryOp_ptrfun.dir/class_CwiseUnaryOp_ptrfun.cpp.o: /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/Programming_assignments/Chapter_5/include/eigen/doc/examples/class_CwiseUnaryOp_ptrfun.cpp
doc/examples/CMakeFiles/class_CwiseUnaryOp_ptrfun.dir/class_CwiseUnaryOp_ptrfun.cpp.o: doc/examples/CMakeFiles/class_CwiseUnaryOp_ptrfun.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object doc/examples/CMakeFiles/class_CwiseUnaryOp_ptrfun.dir/class_CwiseUnaryOp_ptrfun.cpp.o"
	cd /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/doc/examples && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT doc/examples/CMakeFiles/class_CwiseUnaryOp_ptrfun.dir/class_CwiseUnaryOp_ptrfun.cpp.o -MF CMakeFiles/class_CwiseUnaryOp_ptrfun.dir/class_CwiseUnaryOp_ptrfun.cpp.o.d -o CMakeFiles/class_CwiseUnaryOp_ptrfun.dir/class_CwiseUnaryOp_ptrfun.cpp.o -c /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/Programming_assignments/Chapter_5/include/eigen/doc/examples/class_CwiseUnaryOp_ptrfun.cpp

doc/examples/CMakeFiles/class_CwiseUnaryOp_ptrfun.dir/class_CwiseUnaryOp_ptrfun.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/class_CwiseUnaryOp_ptrfun.dir/class_CwiseUnaryOp_ptrfun.cpp.i"
	cd /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/doc/examples && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/Programming_assignments/Chapter_5/include/eigen/doc/examples/class_CwiseUnaryOp_ptrfun.cpp > CMakeFiles/class_CwiseUnaryOp_ptrfun.dir/class_CwiseUnaryOp_ptrfun.cpp.i

doc/examples/CMakeFiles/class_CwiseUnaryOp_ptrfun.dir/class_CwiseUnaryOp_ptrfun.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/class_CwiseUnaryOp_ptrfun.dir/class_CwiseUnaryOp_ptrfun.cpp.s"
	cd /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/doc/examples && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/Programming_assignments/Chapter_5/include/eigen/doc/examples/class_CwiseUnaryOp_ptrfun.cpp -o CMakeFiles/class_CwiseUnaryOp_ptrfun.dir/class_CwiseUnaryOp_ptrfun.cpp.s

# Object files for target class_CwiseUnaryOp_ptrfun
class_CwiseUnaryOp_ptrfun_OBJECTS = \
"CMakeFiles/class_CwiseUnaryOp_ptrfun.dir/class_CwiseUnaryOp_ptrfun.cpp.o"

# External object files for target class_CwiseUnaryOp_ptrfun
class_CwiseUnaryOp_ptrfun_EXTERNAL_OBJECTS =

doc/examples/class_CwiseUnaryOp_ptrfun: doc/examples/CMakeFiles/class_CwiseUnaryOp_ptrfun.dir/class_CwiseUnaryOp_ptrfun.cpp.o
doc/examples/class_CwiseUnaryOp_ptrfun: doc/examples/CMakeFiles/class_CwiseUnaryOp_ptrfun.dir/build.make
doc/examples/class_CwiseUnaryOp_ptrfun: doc/examples/CMakeFiles/class_CwiseUnaryOp_ptrfun.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable class_CwiseUnaryOp_ptrfun"
	cd /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/doc/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/class_CwiseUnaryOp_ptrfun.dir/link.txt --verbose=$(VERBOSE)
	cd /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/doc/examples && ./class_CwiseUnaryOp_ptrfun >/Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/doc/examples/class_CwiseUnaryOp_ptrfun.out

# Rule to build all files generated by this target.
doc/examples/CMakeFiles/class_CwiseUnaryOp_ptrfun.dir/build: doc/examples/class_CwiseUnaryOp_ptrfun
.PHONY : doc/examples/CMakeFiles/class_CwiseUnaryOp_ptrfun.dir/build

doc/examples/CMakeFiles/class_CwiseUnaryOp_ptrfun.dir/clean:
	cd /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/doc/examples && $(CMAKE_COMMAND) -P CMakeFiles/class_CwiseUnaryOp_ptrfun.dir/cmake_clean.cmake
.PHONY : doc/examples/CMakeFiles/class_CwiseUnaryOp_ptrfun.dir/clean

doc/examples/CMakeFiles/class_CwiseUnaryOp_ptrfun.dir/depend:
	cd /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/Programming_assignments/Chapter_5/include/eigen /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/Programming_assignments/Chapter_5/include/eigen/doc/examples /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/doc/examples /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/doc/examples/CMakeFiles/class_CwiseUnaryOp_ptrfun.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : doc/examples/CMakeFiles/class_CwiseUnaryOp_ptrfun.dir/depend

