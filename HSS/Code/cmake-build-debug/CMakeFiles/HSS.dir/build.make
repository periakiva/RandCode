# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.8

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/labuser/Downloads/clion-2017.2.2/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/labuser/Downloads/clion-2017.2.2/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/labuser/Dropbox/HSS

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/labuser/Dropbox/HSS/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/HSS.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/HSS.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/HSS.dir/flags.make

CMakeFiles/HSS.dir/main.cpp.o: CMakeFiles/HSS.dir/flags.make
CMakeFiles/HSS.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/labuser/Dropbox/HSS/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/HSS.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/HSS.dir/main.cpp.o -c /home/labuser/Dropbox/HSS/main.cpp

CMakeFiles/HSS.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/HSS.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/labuser/Dropbox/HSS/main.cpp > CMakeFiles/HSS.dir/main.cpp.i

CMakeFiles/HSS.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/HSS.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/labuser/Dropbox/HSS/main.cpp -o CMakeFiles/HSS.dir/main.cpp.s

CMakeFiles/HSS.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/HSS.dir/main.cpp.o.requires

CMakeFiles/HSS.dir/main.cpp.o.provides: CMakeFiles/HSS.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/HSS.dir/build.make CMakeFiles/HSS.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/HSS.dir/main.cpp.o.provides

CMakeFiles/HSS.dir/main.cpp.o.provides.build: CMakeFiles/HSS.dir/main.cpp.o


# Object files for target HSS
HSS_OBJECTS = \
"CMakeFiles/HSS.dir/main.cpp.o"

# External object files for target HSS
HSS_EXTERNAL_OBJECTS =

HSS: CMakeFiles/HSS.dir/main.cpp.o
HSS: CMakeFiles/HSS.dir/build.make
HSS: CMakeFiles/HSS.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/labuser/Dropbox/HSS/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable HSS"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/HSS.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/HSS.dir/build: HSS

.PHONY : CMakeFiles/HSS.dir/build

CMakeFiles/HSS.dir/requires: CMakeFiles/HSS.dir/main.cpp.o.requires

.PHONY : CMakeFiles/HSS.dir/requires

CMakeFiles/HSS.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/HSS.dir/cmake_clean.cmake
.PHONY : CMakeFiles/HSS.dir/clean

CMakeFiles/HSS.dir/depend:
	cd /home/labuser/Dropbox/HSS/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/labuser/Dropbox/HSS /home/labuser/Dropbox/HSS /home/labuser/Dropbox/HSS/cmake-build-debug /home/labuser/Dropbox/HSS/cmake-build-debug /home/labuser/Dropbox/HSS/cmake-build-debug/CMakeFiles/HSS.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/HSS.dir/depend

