# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/cdaini/IACLIB/lib

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/cdaini/IACLIB/lib/build

# Include any dependencies generated for this target.
include CMakeFiles/IALIB.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/IALIB.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/IALIB.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/IALIB.dir/flags.make

CMakeFiles/IALIB.dir/main.c.o: CMakeFiles/IALIB.dir/flags.make
CMakeFiles/IALIB.dir/main.c.o: ../main.c
CMakeFiles/IALIB.dir/main.c.o: CMakeFiles/IALIB.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cdaini/IACLIB/lib/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/IALIB.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/IALIB.dir/main.c.o -MF CMakeFiles/IALIB.dir/main.c.o.d -o CMakeFiles/IALIB.dir/main.c.o -c /home/cdaini/IACLIB/lib/main.c

CMakeFiles/IALIB.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/IALIB.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/cdaini/IACLIB/lib/main.c > CMakeFiles/IALIB.dir/main.c.i

CMakeFiles/IALIB.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/IALIB.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/cdaini/IACLIB/lib/main.c -o CMakeFiles/IALIB.dir/main.c.s

CMakeFiles/IALIB.dir/tools.c.o: CMakeFiles/IALIB.dir/flags.make
CMakeFiles/IALIB.dir/tools.c.o: ../tools.c
CMakeFiles/IALIB.dir/tools.c.o: CMakeFiles/IALIB.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cdaini/IACLIB/lib/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/IALIB.dir/tools.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/IALIB.dir/tools.c.o -MF CMakeFiles/IALIB.dir/tools.c.o.d -o CMakeFiles/IALIB.dir/tools.c.o -c /home/cdaini/IACLIB/lib/tools.c

CMakeFiles/IALIB.dir/tools.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/IALIB.dir/tools.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/cdaini/IACLIB/lib/tools.c > CMakeFiles/IALIB.dir/tools.c.i

CMakeFiles/IALIB.dir/tools.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/IALIB.dir/tools.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/cdaini/IACLIB/lib/tools.c -o CMakeFiles/IALIB.dir/tools.c.s

CMakeFiles/IALIB.dir/cnn_ops.c.o: CMakeFiles/IALIB.dir/flags.make
CMakeFiles/IALIB.dir/cnn_ops.c.o: ../cnn_ops.c
CMakeFiles/IALIB.dir/cnn_ops.c.o: CMakeFiles/IALIB.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cdaini/IACLIB/lib/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/IALIB.dir/cnn_ops.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/IALIB.dir/cnn_ops.c.o -MF CMakeFiles/IALIB.dir/cnn_ops.c.o.d -o CMakeFiles/IALIB.dir/cnn_ops.c.o -c /home/cdaini/IACLIB/lib/cnn_ops.c

CMakeFiles/IALIB.dir/cnn_ops.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/IALIB.dir/cnn_ops.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/cdaini/IACLIB/lib/cnn_ops.c > CMakeFiles/IALIB.dir/cnn_ops.c.i

CMakeFiles/IALIB.dir/cnn_ops.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/IALIB.dir/cnn_ops.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/cdaini/IACLIB/lib/cnn_ops.c -o CMakeFiles/IALIB.dir/cnn_ops.c.s

# Object files for target IALIB
IALIB_OBJECTS = \
"CMakeFiles/IALIB.dir/main.c.o" \
"CMakeFiles/IALIB.dir/tools.c.o" \
"CMakeFiles/IALIB.dir/cnn_ops.c.o"

# External object files for target IALIB
IALIB_EXTERNAL_OBJECTS =

IALIB: CMakeFiles/IALIB.dir/main.c.o
IALIB: CMakeFiles/IALIB.dir/tools.c.o
IALIB: CMakeFiles/IALIB.dir/cnn_ops.c.o
IALIB: CMakeFiles/IALIB.dir/build.make
IALIB: CMakeFiles/IALIB.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/cdaini/IACLIB/lib/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable IALIB"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/IALIB.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/IALIB.dir/build: IALIB
.PHONY : CMakeFiles/IALIB.dir/build

CMakeFiles/IALIB.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/IALIB.dir/cmake_clean.cmake
.PHONY : CMakeFiles/IALIB.dir/clean

CMakeFiles/IALIB.dir/depend:
	cd /home/cdaini/IACLIB/lib/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/cdaini/IACLIB/lib /home/cdaini/IACLIB/lib /home/cdaini/IACLIB/lib/build /home/cdaini/IACLIB/lib/build /home/cdaini/IACLIB/lib/build/CMakeFiles/IALIB.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/IALIB.dir/depend

