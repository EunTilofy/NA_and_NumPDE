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
include unsupported/test/CMakeFiles/idrs_2.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include unsupported/test/CMakeFiles/idrs_2.dir/compiler_depend.make

# Include the progress variables for this target.
include unsupported/test/CMakeFiles/idrs_2.dir/progress.make

# Include the compile flags for this target's objects.
include unsupported/test/CMakeFiles/idrs_2.dir/flags.make

unsupported/test/CMakeFiles/idrs_2.dir/idrs.cpp.o: unsupported/test/CMakeFiles/idrs_2.dir/flags.make
unsupported/test/CMakeFiles/idrs_2.dir/idrs.cpp.o: /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/Programming_assignments/Chapter_5/include/eigen/unsupported/test/idrs.cpp
unsupported/test/CMakeFiles/idrs_2.dir/idrs.cpp.o: unsupported/test/CMakeFiles/idrs_2.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object unsupported/test/CMakeFiles/idrs_2.dir/idrs.cpp.o"
	cd /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/unsupported/test && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT unsupported/test/CMakeFiles/idrs_2.dir/idrs.cpp.o -MF CMakeFiles/idrs_2.dir/idrs.cpp.o.d -o CMakeFiles/idrs_2.dir/idrs.cpp.o -c /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/Programming_assignments/Chapter_5/include/eigen/unsupported/test/idrs.cpp

unsupported/test/CMakeFiles/idrs_2.dir/idrs.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/idrs_2.dir/idrs.cpp.i"
	cd /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/unsupported/test && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/Programming_assignments/Chapter_5/include/eigen/unsupported/test/idrs.cpp > CMakeFiles/idrs_2.dir/idrs.cpp.i

unsupported/test/CMakeFiles/idrs_2.dir/idrs.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/idrs_2.dir/idrs.cpp.s"
	cd /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/unsupported/test && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/Programming_assignments/Chapter_5/include/eigen/unsupported/test/idrs.cpp -o CMakeFiles/idrs_2.dir/idrs.cpp.s

# Object files for target idrs_2
idrs_2_OBJECTS = \
"CMakeFiles/idrs_2.dir/idrs.cpp.o"

# External object files for target idrs_2
idrs_2_EXTERNAL_OBJECTS =

unsupported/test/idrs_2: unsupported/test/CMakeFiles/idrs_2.dir/idrs.cpp.o
unsupported/test/idrs_2: unsupported/test/CMakeFiles/idrs_2.dir/build.make
unsupported/test/idrs_2: unsupported/test/CMakeFiles/idrs_2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable idrs_2"
	cd /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/unsupported/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/idrs_2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
unsupported/test/CMakeFiles/idrs_2.dir/build: unsupported/test/idrs_2
.PHONY : unsupported/test/CMakeFiles/idrs_2.dir/build

unsupported/test/CMakeFiles/idrs_2.dir/clean:
	cd /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/unsupported/test && $(CMAKE_COMMAND) -P CMakeFiles/idrs_2.dir/cmake_clean.cmake
.PHONY : unsupported/test/CMakeFiles/idrs_2.dir/clean

unsupported/test/CMakeFiles/idrs_2.dir/depend:
	cd /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/Programming_assignments/Chapter_5/include/eigen /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/Programming_assignments/Chapter_5/include/eigen/unsupported/test /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/unsupported/test /Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/build/unsupported/test/CMakeFiles/idrs_2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : unsupported/test/CMakeFiles/idrs_2.dir/depend

