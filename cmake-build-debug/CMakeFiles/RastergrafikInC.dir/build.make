# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.21

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
CMAKE_COMMAND = /cygdrive/c/Users/simon/AppData/Local/JetBrains/CLion2021.3/cygwin_cmake/bin/cmake.exe

# The command to remove a file.
RM = /cygdrive/c/Users/simon/AppData/Local/JetBrains/CLion2021.3/cygwin_cmake/bin/cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /cygdrive/c/Users/simon/CLionProjects/RastergrafikInC

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /cygdrive/c/Users/simon/CLionProjects/RastergrafikInC/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/RastergrafikInC.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/RastergrafikInC.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/RastergrafikInC.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/RastergrafikInC.dir/flags.make

CMakeFiles/RastergrafikInC.dir/main.c.o: CMakeFiles/RastergrafikInC.dir/flags.make
CMakeFiles/RastergrafikInC.dir/main.c.o: ../main.c
CMakeFiles/RastergrafikInC.dir/main.c.o: CMakeFiles/RastergrafikInC.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cygdrive/c/Users/simon/CLionProjects/RastergrafikInC/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/RastergrafikInC.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/RastergrafikInC.dir/main.c.o -MF CMakeFiles/RastergrafikInC.dir/main.c.o.d -o CMakeFiles/RastergrafikInC.dir/main.c.o -c /cygdrive/c/Users/simon/CLionProjects/RastergrafikInC/main.c

CMakeFiles/RastergrafikInC.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/RastergrafikInC.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /cygdrive/c/Users/simon/CLionProjects/RastergrafikInC/main.c > CMakeFiles/RastergrafikInC.dir/main.c.i

CMakeFiles/RastergrafikInC.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/RastergrafikInC.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /cygdrive/c/Users/simon/CLionProjects/RastergrafikInC/main.c -o CMakeFiles/RastergrafikInC.dir/main.c.s

CMakeFiles/RastergrafikInC.dir/draw.c.o: CMakeFiles/RastergrafikInC.dir/flags.make
CMakeFiles/RastergrafikInC.dir/draw.c.o: ../draw.c
CMakeFiles/RastergrafikInC.dir/draw.c.o: CMakeFiles/RastergrafikInC.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cygdrive/c/Users/simon/CLionProjects/RastergrafikInC/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/RastergrafikInC.dir/draw.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/RastergrafikInC.dir/draw.c.o -MF CMakeFiles/RastergrafikInC.dir/draw.c.o.d -o CMakeFiles/RastergrafikInC.dir/draw.c.o -c /cygdrive/c/Users/simon/CLionProjects/RastergrafikInC/draw.c

CMakeFiles/RastergrafikInC.dir/draw.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/RastergrafikInC.dir/draw.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /cygdrive/c/Users/simon/CLionProjects/RastergrafikInC/draw.c > CMakeFiles/RastergrafikInC.dir/draw.c.i

CMakeFiles/RastergrafikInC.dir/draw.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/RastergrafikInC.dir/draw.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /cygdrive/c/Users/simon/CLionProjects/RastergrafikInC/draw.c -o CMakeFiles/RastergrafikInC.dir/draw.c.s

# Object files for target RastergrafikInC
RastergrafikInC_OBJECTS = \
"CMakeFiles/RastergrafikInC.dir/main.c.o" \
"CMakeFiles/RastergrafikInC.dir/draw.c.o"

# External object files for target RastergrafikInC
RastergrafikInC_EXTERNAL_OBJECTS =

RastergrafikInC.exe: CMakeFiles/RastergrafikInC.dir/main.c.o
RastergrafikInC.exe: CMakeFiles/RastergrafikInC.dir/draw.c.o
RastergrafikInC.exe: CMakeFiles/RastergrafikInC.dir/build.make
RastergrafikInC.exe: CMakeFiles/RastergrafikInC.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/cygdrive/c/Users/simon/CLionProjects/RastergrafikInC/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable RastergrafikInC.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/RastergrafikInC.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/RastergrafikInC.dir/build: RastergrafikInC.exe
.PHONY : CMakeFiles/RastergrafikInC.dir/build

CMakeFiles/RastergrafikInC.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/RastergrafikInC.dir/cmake_clean.cmake
.PHONY : CMakeFiles/RastergrafikInC.dir/clean

CMakeFiles/RastergrafikInC.dir/depend:
	cd /cygdrive/c/Users/simon/CLionProjects/RastergrafikInC/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /cygdrive/c/Users/simon/CLionProjects/RastergrafikInC /cygdrive/c/Users/simon/CLionProjects/RastergrafikInC /cygdrive/c/Users/simon/CLionProjects/RastergrafikInC/cmake-build-debug /cygdrive/c/Users/simon/CLionProjects/RastergrafikInC/cmake-build-debug /cygdrive/c/Users/simon/CLionProjects/RastergrafikInC/cmake-build-debug/CMakeFiles/RastergrafikInC.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/RastergrafikInC.dir/depend

