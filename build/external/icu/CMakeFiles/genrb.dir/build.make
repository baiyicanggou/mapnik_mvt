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
include external/icu/CMakeFiles/genrb.dir/depend.make

# Include the progress variables for this target.
include external/icu/CMakeFiles/genrb.dir/progress.make

# Include the compile flags for this target's objects.
include external/icu/CMakeFiles/genrb.dir/flags.make

external/icu/CMakeFiles/genrb.dir/no-op.cc.o: external/icu/CMakeFiles/genrb.dir/flags.make
external/icu/CMakeFiles/genrb.dir/no-op.cc.o: ../external/icu/no-op.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object external/icu/CMakeFiles/genrb.dir/no-op.cc.o"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/icu && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/genrb.dir/no-op.cc.o -c /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/icu/no-op.cc

external/icu/CMakeFiles/genrb.dir/no-op.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/genrb.dir/no-op.cc.i"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/icu && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/icu/no-op.cc > CMakeFiles/genrb.dir/no-op.cc.i

external/icu/CMakeFiles/genrb.dir/no-op.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/genrb.dir/no-op.cc.s"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/icu && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/icu/no-op.cc -o CMakeFiles/genrb.dir/no-op.cc.s

external/icu/CMakeFiles/genrb.dir/source/tools/genrb/errmsg.c.o: external/icu/CMakeFiles/genrb.dir/flags.make
external/icu/CMakeFiles/genrb.dir/source/tools/genrb/errmsg.c.o: ../external/icu/source/tools/genrb/errmsg.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object external/icu/CMakeFiles/genrb.dir/source/tools/genrb/errmsg.c.o"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/icu && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/genrb.dir/source/tools/genrb/errmsg.c.o   -c /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/icu/source/tools/genrb/errmsg.c

external/icu/CMakeFiles/genrb.dir/source/tools/genrb/errmsg.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/genrb.dir/source/tools/genrb/errmsg.c.i"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/icu && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/icu/source/tools/genrb/errmsg.c > CMakeFiles/genrb.dir/source/tools/genrb/errmsg.c.i

external/icu/CMakeFiles/genrb.dir/source/tools/genrb/errmsg.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/genrb.dir/source/tools/genrb/errmsg.c.s"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/icu && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/icu/source/tools/genrb/errmsg.c -o CMakeFiles/genrb.dir/source/tools/genrb/errmsg.c.s

external/icu/CMakeFiles/genrb.dir/source/tools/genrb/genrb.cpp.o: external/icu/CMakeFiles/genrb.dir/flags.make
external/icu/CMakeFiles/genrb.dir/source/tools/genrb/genrb.cpp.o: ../external/icu/source/tools/genrb/genrb.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object external/icu/CMakeFiles/genrb.dir/source/tools/genrb/genrb.cpp.o"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/icu && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/genrb.dir/source/tools/genrb/genrb.cpp.o -c /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/icu/source/tools/genrb/genrb.cpp

external/icu/CMakeFiles/genrb.dir/source/tools/genrb/genrb.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/genrb.dir/source/tools/genrb/genrb.cpp.i"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/icu && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/icu/source/tools/genrb/genrb.cpp > CMakeFiles/genrb.dir/source/tools/genrb/genrb.cpp.i

external/icu/CMakeFiles/genrb.dir/source/tools/genrb/genrb.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/genrb.dir/source/tools/genrb/genrb.cpp.s"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/icu && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/icu/source/tools/genrb/genrb.cpp -o CMakeFiles/genrb.dir/source/tools/genrb/genrb.cpp.s

external/icu/CMakeFiles/genrb.dir/source/tools/genrb/parse.cpp.o: external/icu/CMakeFiles/genrb.dir/flags.make
external/icu/CMakeFiles/genrb.dir/source/tools/genrb/parse.cpp.o: ../external/icu/source/tools/genrb/parse.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object external/icu/CMakeFiles/genrb.dir/source/tools/genrb/parse.cpp.o"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/icu && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/genrb.dir/source/tools/genrb/parse.cpp.o -c /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/icu/source/tools/genrb/parse.cpp

external/icu/CMakeFiles/genrb.dir/source/tools/genrb/parse.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/genrb.dir/source/tools/genrb/parse.cpp.i"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/icu && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/icu/source/tools/genrb/parse.cpp > CMakeFiles/genrb.dir/source/tools/genrb/parse.cpp.i

external/icu/CMakeFiles/genrb.dir/source/tools/genrb/parse.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/genrb.dir/source/tools/genrb/parse.cpp.s"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/icu && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/icu/source/tools/genrb/parse.cpp -o CMakeFiles/genrb.dir/source/tools/genrb/parse.cpp.s

external/icu/CMakeFiles/genrb.dir/source/tools/genrb/prscmnts.cpp.o: external/icu/CMakeFiles/genrb.dir/flags.make
external/icu/CMakeFiles/genrb.dir/source/tools/genrb/prscmnts.cpp.o: ../external/icu/source/tools/genrb/prscmnts.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object external/icu/CMakeFiles/genrb.dir/source/tools/genrb/prscmnts.cpp.o"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/icu && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/genrb.dir/source/tools/genrb/prscmnts.cpp.o -c /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/icu/source/tools/genrb/prscmnts.cpp

external/icu/CMakeFiles/genrb.dir/source/tools/genrb/prscmnts.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/genrb.dir/source/tools/genrb/prscmnts.cpp.i"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/icu && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/icu/source/tools/genrb/prscmnts.cpp > CMakeFiles/genrb.dir/source/tools/genrb/prscmnts.cpp.i

external/icu/CMakeFiles/genrb.dir/source/tools/genrb/prscmnts.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/genrb.dir/source/tools/genrb/prscmnts.cpp.s"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/icu && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/icu/source/tools/genrb/prscmnts.cpp -o CMakeFiles/genrb.dir/source/tools/genrb/prscmnts.cpp.s

external/icu/CMakeFiles/genrb.dir/source/tools/genrb/rbutil.c.o: external/icu/CMakeFiles/genrb.dir/flags.make
external/icu/CMakeFiles/genrb.dir/source/tools/genrb/rbutil.c.o: ../external/icu/source/tools/genrb/rbutil.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object external/icu/CMakeFiles/genrb.dir/source/tools/genrb/rbutil.c.o"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/icu && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/genrb.dir/source/tools/genrb/rbutil.c.o   -c /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/icu/source/tools/genrb/rbutil.c

external/icu/CMakeFiles/genrb.dir/source/tools/genrb/rbutil.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/genrb.dir/source/tools/genrb/rbutil.c.i"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/icu && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/icu/source/tools/genrb/rbutil.c > CMakeFiles/genrb.dir/source/tools/genrb/rbutil.c.i

external/icu/CMakeFiles/genrb.dir/source/tools/genrb/rbutil.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/genrb.dir/source/tools/genrb/rbutil.c.s"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/icu && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/icu/source/tools/genrb/rbutil.c -o CMakeFiles/genrb.dir/source/tools/genrb/rbutil.c.s

external/icu/CMakeFiles/genrb.dir/source/tools/genrb/read.c.o: external/icu/CMakeFiles/genrb.dir/flags.make
external/icu/CMakeFiles/genrb.dir/source/tools/genrb/read.c.o: ../external/icu/source/tools/genrb/read.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object external/icu/CMakeFiles/genrb.dir/source/tools/genrb/read.c.o"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/icu && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/genrb.dir/source/tools/genrb/read.c.o   -c /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/icu/source/tools/genrb/read.c

external/icu/CMakeFiles/genrb.dir/source/tools/genrb/read.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/genrb.dir/source/tools/genrb/read.c.i"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/icu && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/icu/source/tools/genrb/read.c > CMakeFiles/genrb.dir/source/tools/genrb/read.c.i

external/icu/CMakeFiles/genrb.dir/source/tools/genrb/read.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/genrb.dir/source/tools/genrb/read.c.s"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/icu && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/icu/source/tools/genrb/read.c -o CMakeFiles/genrb.dir/source/tools/genrb/read.c.s

external/icu/CMakeFiles/genrb.dir/source/tools/genrb/reslist.cpp.o: external/icu/CMakeFiles/genrb.dir/flags.make
external/icu/CMakeFiles/genrb.dir/source/tools/genrb/reslist.cpp.o: ../external/icu/source/tools/genrb/reslist.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object external/icu/CMakeFiles/genrb.dir/source/tools/genrb/reslist.cpp.o"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/icu && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/genrb.dir/source/tools/genrb/reslist.cpp.o -c /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/icu/source/tools/genrb/reslist.cpp

external/icu/CMakeFiles/genrb.dir/source/tools/genrb/reslist.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/genrb.dir/source/tools/genrb/reslist.cpp.i"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/icu && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/icu/source/tools/genrb/reslist.cpp > CMakeFiles/genrb.dir/source/tools/genrb/reslist.cpp.i

external/icu/CMakeFiles/genrb.dir/source/tools/genrb/reslist.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/genrb.dir/source/tools/genrb/reslist.cpp.s"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/icu && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/icu/source/tools/genrb/reslist.cpp -o CMakeFiles/genrb.dir/source/tools/genrb/reslist.cpp.s

external/icu/CMakeFiles/genrb.dir/source/tools/genrb/rle.c.o: external/icu/CMakeFiles/genrb.dir/flags.make
external/icu/CMakeFiles/genrb.dir/source/tools/genrb/rle.c.o: ../external/icu/source/tools/genrb/rle.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building C object external/icu/CMakeFiles/genrb.dir/source/tools/genrb/rle.c.o"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/icu && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/genrb.dir/source/tools/genrb/rle.c.o   -c /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/icu/source/tools/genrb/rle.c

external/icu/CMakeFiles/genrb.dir/source/tools/genrb/rle.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/genrb.dir/source/tools/genrb/rle.c.i"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/icu && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/icu/source/tools/genrb/rle.c > CMakeFiles/genrb.dir/source/tools/genrb/rle.c.i

external/icu/CMakeFiles/genrb.dir/source/tools/genrb/rle.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/genrb.dir/source/tools/genrb/rle.c.s"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/icu && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/icu/source/tools/genrb/rle.c -o CMakeFiles/genrb.dir/source/tools/genrb/rle.c.s

external/icu/CMakeFiles/genrb.dir/source/tools/genrb/ustr.c.o: external/icu/CMakeFiles/genrb.dir/flags.make
external/icu/CMakeFiles/genrb.dir/source/tools/genrb/ustr.c.o: ../external/icu/source/tools/genrb/ustr.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building C object external/icu/CMakeFiles/genrb.dir/source/tools/genrb/ustr.c.o"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/icu && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/genrb.dir/source/tools/genrb/ustr.c.o   -c /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/icu/source/tools/genrb/ustr.c

external/icu/CMakeFiles/genrb.dir/source/tools/genrb/ustr.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/genrb.dir/source/tools/genrb/ustr.c.i"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/icu && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/icu/source/tools/genrb/ustr.c > CMakeFiles/genrb.dir/source/tools/genrb/ustr.c.i

external/icu/CMakeFiles/genrb.dir/source/tools/genrb/ustr.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/genrb.dir/source/tools/genrb/ustr.c.s"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/icu && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/icu/source/tools/genrb/ustr.c -o CMakeFiles/genrb.dir/source/tools/genrb/ustr.c.s

external/icu/CMakeFiles/genrb.dir/source/tools/genrb/wrtjava.cpp.o: external/icu/CMakeFiles/genrb.dir/flags.make
external/icu/CMakeFiles/genrb.dir/source/tools/genrb/wrtjava.cpp.o: ../external/icu/source/tools/genrb/wrtjava.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object external/icu/CMakeFiles/genrb.dir/source/tools/genrb/wrtjava.cpp.o"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/icu && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/genrb.dir/source/tools/genrb/wrtjava.cpp.o -c /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/icu/source/tools/genrb/wrtjava.cpp

external/icu/CMakeFiles/genrb.dir/source/tools/genrb/wrtjava.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/genrb.dir/source/tools/genrb/wrtjava.cpp.i"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/icu && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/icu/source/tools/genrb/wrtjava.cpp > CMakeFiles/genrb.dir/source/tools/genrb/wrtjava.cpp.i

external/icu/CMakeFiles/genrb.dir/source/tools/genrb/wrtjava.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/genrb.dir/source/tools/genrb/wrtjava.cpp.s"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/icu && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/icu/source/tools/genrb/wrtjava.cpp -o CMakeFiles/genrb.dir/source/tools/genrb/wrtjava.cpp.s

external/icu/CMakeFiles/genrb.dir/source/tools/genrb/wrtxml.cpp.o: external/icu/CMakeFiles/genrb.dir/flags.make
external/icu/CMakeFiles/genrb.dir/source/tools/genrb/wrtxml.cpp.o: ../external/icu/source/tools/genrb/wrtxml.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object external/icu/CMakeFiles/genrb.dir/source/tools/genrb/wrtxml.cpp.o"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/icu && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/genrb.dir/source/tools/genrb/wrtxml.cpp.o -c /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/icu/source/tools/genrb/wrtxml.cpp

external/icu/CMakeFiles/genrb.dir/source/tools/genrb/wrtxml.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/genrb.dir/source/tools/genrb/wrtxml.cpp.i"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/icu && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/icu/source/tools/genrb/wrtxml.cpp > CMakeFiles/genrb.dir/source/tools/genrb/wrtxml.cpp.i

external/icu/CMakeFiles/genrb.dir/source/tools/genrb/wrtxml.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/genrb.dir/source/tools/genrb/wrtxml.cpp.s"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/icu && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/icu/source/tools/genrb/wrtxml.cpp -o CMakeFiles/genrb.dir/source/tools/genrb/wrtxml.cpp.s

# Object files for target genrb
genrb_OBJECTS = \
"CMakeFiles/genrb.dir/no-op.cc.o" \
"CMakeFiles/genrb.dir/source/tools/genrb/errmsg.c.o" \
"CMakeFiles/genrb.dir/source/tools/genrb/genrb.cpp.o" \
"CMakeFiles/genrb.dir/source/tools/genrb/parse.cpp.o" \
"CMakeFiles/genrb.dir/source/tools/genrb/prscmnts.cpp.o" \
"CMakeFiles/genrb.dir/source/tools/genrb/rbutil.c.o" \
"CMakeFiles/genrb.dir/source/tools/genrb/read.c.o" \
"CMakeFiles/genrb.dir/source/tools/genrb/reslist.cpp.o" \
"CMakeFiles/genrb.dir/source/tools/genrb/rle.c.o" \
"CMakeFiles/genrb.dir/source/tools/genrb/ustr.c.o" \
"CMakeFiles/genrb.dir/source/tools/genrb/wrtjava.cpp.o" \
"CMakeFiles/genrb.dir/source/tools/genrb/wrtxml.cpp.o"

# External object files for target genrb
genrb_EXTERNAL_OBJECTS =

external/icu/bin/genrb: external/icu/CMakeFiles/genrb.dir/no-op.cc.o
external/icu/bin/genrb: external/icu/CMakeFiles/genrb.dir/source/tools/genrb/errmsg.c.o
external/icu/bin/genrb: external/icu/CMakeFiles/genrb.dir/source/tools/genrb/genrb.cpp.o
external/icu/bin/genrb: external/icu/CMakeFiles/genrb.dir/source/tools/genrb/parse.cpp.o
external/icu/bin/genrb: external/icu/CMakeFiles/genrb.dir/source/tools/genrb/prscmnts.cpp.o
external/icu/bin/genrb: external/icu/CMakeFiles/genrb.dir/source/tools/genrb/rbutil.c.o
external/icu/bin/genrb: external/icu/CMakeFiles/genrb.dir/source/tools/genrb/read.c.o
external/icu/bin/genrb: external/icu/CMakeFiles/genrb.dir/source/tools/genrb/reslist.cpp.o
external/icu/bin/genrb: external/icu/CMakeFiles/genrb.dir/source/tools/genrb/rle.c.o
external/icu/bin/genrb: external/icu/CMakeFiles/genrb.dir/source/tools/genrb/ustr.c.o
external/icu/bin/genrb: external/icu/CMakeFiles/genrb.dir/source/tools/genrb/wrtjava.cpp.o
external/icu/bin/genrb: external/icu/CMakeFiles/genrb.dir/source/tools/genrb/wrtxml.cpp.o
external/icu/bin/genrb: external/icu/CMakeFiles/genrb.dir/build.make
external/icu/bin/genrb: external/icu/libicutools.a
external/icu/bin/genrb: external/icu/libicudata.a
external/icu/bin/genrb: external/icu/CMakeFiles/genrb.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Linking CXX executable bin/genrb"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/icu && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/genrb.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
external/icu/CMakeFiles/genrb.dir/build: external/icu/bin/genrb

.PHONY : external/icu/CMakeFiles/genrb.dir/build

external/icu/CMakeFiles/genrb.dir/clean:
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/icu && $(CMAKE_COMMAND) -P CMakeFiles/genrb.dir/cmake_clean.cmake
.PHONY : external/icu/CMakeFiles/genrb.dir/clean

external/icu/CMakeFiles/genrb.dir/depend:
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/xuemeng/work/flywave/mapnic/flywave-mapnik /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/icu /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/icu /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/icu/CMakeFiles/genrb.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : external/icu/CMakeFiles/genrb.dir/depend
