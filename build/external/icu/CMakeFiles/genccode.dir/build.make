# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/xuemeng/work/flywave/mapnic/flywave-mapnik

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build

# Include any dependencies generated for this target.
include external/icu/CMakeFiles/genccode.dir/depend.make

# Include the progress variables for this target.
include external/icu/CMakeFiles/genccode.dir/progress.make

# Include the compile flags for this target's objects.
include external/icu/CMakeFiles/genccode.dir/flags.make

external/icu/CMakeFiles/genccode.dir/source/tools/genccode/genccode.c.o: external/icu/CMakeFiles/genccode.dir/flags.make
external/icu/CMakeFiles/genccode.dir/source/tools/genccode/genccode.c.o: ../external/icu/source/tools/genccode/genccode.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object external/icu/CMakeFiles/genccode.dir/source/tools/genccode/genccode.c.o"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/icu && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/genccode.dir/source/tools/genccode/genccode.c.o   -c /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/icu/source/tools/genccode/genccode.c

external/icu/CMakeFiles/genccode.dir/source/tools/genccode/genccode.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/genccode.dir/source/tools/genccode/genccode.c.i"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/icu && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/icu/source/tools/genccode/genccode.c > CMakeFiles/genccode.dir/source/tools/genccode/genccode.c.i

external/icu/CMakeFiles/genccode.dir/source/tools/genccode/genccode.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/genccode.dir/source/tools/genccode/genccode.c.s"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/icu && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/icu/source/tools/genccode/genccode.c -o CMakeFiles/genccode.dir/source/tools/genccode/genccode.c.s

external/icu/CMakeFiles/genccode.dir/no-op.cc.o: external/icu/CMakeFiles/genccode.dir/flags.make
external/icu/CMakeFiles/genccode.dir/no-op.cc.o: ../external/icu/no-op.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object external/icu/CMakeFiles/genccode.dir/no-op.cc.o"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/icu && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/genccode.dir/no-op.cc.o -c /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/icu/no-op.cc

external/icu/CMakeFiles/genccode.dir/no-op.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/genccode.dir/no-op.cc.i"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/icu && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/icu/no-op.cc > CMakeFiles/genccode.dir/no-op.cc.i

external/icu/CMakeFiles/genccode.dir/no-op.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/genccode.dir/no-op.cc.s"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/icu && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/icu/no-op.cc -o CMakeFiles/genccode.dir/no-op.cc.s

# Object files for target genccode
genccode_OBJECTS = \
"CMakeFiles/genccode.dir/source/tools/genccode/genccode.c.o" \
"CMakeFiles/genccode.dir/no-op.cc.o"

# External object files for target genccode
genccode_EXTERNAL_OBJECTS =

external/icu/bin/genccode: external/icu/CMakeFiles/genccode.dir/source/tools/genccode/genccode.c.o
external/icu/bin/genccode: external/icu/CMakeFiles/genccode.dir/no-op.cc.o
external/icu/bin/genccode: external/icu/CMakeFiles/genccode.dir/build.make
external/icu/bin/genccode: external/icu/libicutools.a
external/icu/bin/genccode: external/icu/libicudata.a
external/icu/bin/genccode: external/icu/CMakeFiles/genccode.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable bin/genccode"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/icu && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/genccode.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
external/icu/CMakeFiles/genccode.dir/build: external/icu/bin/genccode

.PHONY : external/icu/CMakeFiles/genccode.dir/build

external/icu/CMakeFiles/genccode.dir/clean:
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/icu && $(CMAKE_COMMAND) -P CMakeFiles/genccode.dir/cmake_clean.cmake
.PHONY : external/icu/CMakeFiles/genccode.dir/clean

external/icu/CMakeFiles/genccode.dir/depend:
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/xuemeng/work/flywave/mapnic/flywave-mapnik /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/icu /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/icu /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/icu/CMakeFiles/genccode.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : external/icu/CMakeFiles/genccode.dir/depend

