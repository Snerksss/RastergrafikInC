# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.21

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2021.3.2\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2021.3.2\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\simon\CLionProjects\RastergrafikInC

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\simon\CLionProjects\RastergrafikInC\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/RastergrafikInC.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/RastergrafikInC.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/RastergrafikInC.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/RastergrafikInC.dir/flags.make

CMakeFiles/RastergrafikInC.dir/main.c.obj: CMakeFiles/RastergrafikInC.dir/flags.make
CMakeFiles/RastergrafikInC.dir/main.c.obj: ../main.c
CMakeFiles/RastergrafikInC.dir/main.c.obj: CMakeFiles/RastergrafikInC.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\simon\CLionProjects\RastergrafikInC\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/RastergrafikInC.dir/main.c.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/RastergrafikInC.dir/main.c.obj -MF CMakeFiles\RastergrafikInC.dir\main.c.obj.d -o CMakeFiles\RastergrafikInC.dir\main.c.obj -c C:\Users\simon\CLionProjects\RastergrafikInC\main.c

CMakeFiles/RastergrafikInC.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/RastergrafikInC.dir/main.c.i"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\simon\CLionProjects\RastergrafikInC\main.c > CMakeFiles\RastergrafikInC.dir\main.c.i

CMakeFiles/RastergrafikInC.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/RastergrafikInC.dir/main.c.s"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\simon\CLionProjects\RastergrafikInC\main.c -o CMakeFiles\RastergrafikInC.dir\main.c.s

# Object files for target RastergrafikInC
RastergrafikInC_OBJECTS = \
"CMakeFiles/RastergrafikInC.dir/main.c.obj"

# External object files for target RastergrafikInC
RastergrafikInC_EXTERNAL_OBJECTS =

RastergrafikInC.exe: CMakeFiles/RastergrafikInC.dir/main.c.obj
RastergrafikInC.exe: CMakeFiles/RastergrafikInC.dir/build.make
RastergrafikInC.exe: CMakeFiles/RastergrafikInC.dir/linklibs.rsp
RastergrafikInC.exe: CMakeFiles/RastergrafikInC.dir/objects1.rsp
RastergrafikInC.exe: CMakeFiles/RastergrafikInC.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\simon\CLionProjects\RastergrafikInC\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable RastergrafikInC.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\RastergrafikInC.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/RastergrafikInC.dir/build: RastergrafikInC.exe
.PHONY : CMakeFiles/RastergrafikInC.dir/build

CMakeFiles/RastergrafikInC.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\RastergrafikInC.dir\cmake_clean.cmake
.PHONY : CMakeFiles/RastergrafikInC.dir/clean

CMakeFiles/RastergrafikInC.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\simon\CLionProjects\RastergrafikInC C:\Users\simon\CLionProjects\RastergrafikInC C:\Users\simon\CLionProjects\RastergrafikInC\cmake-build-debug C:\Users\simon\CLionProjects\RastergrafikInC\cmake-build-debug C:\Users\simon\CLionProjects\RastergrafikInC\cmake-build-debug\CMakeFiles\RastergrafikInC.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/RastergrafikInC.dir/depend
