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
include external/zlib/CMakeFiles/zlib.dir/depend.make

# Include the progress variables for this target.
include external/zlib/CMakeFiles/zlib.dir/progress.make

# Include the compile flags for this target's objects.
include external/zlib/CMakeFiles/zlib.dir/flags.make

external/zlib/CMakeFiles/zlib.dir/adler32.o: external/zlib/CMakeFiles/zlib.dir/flags.make
external/zlib/CMakeFiles/zlib.dir/adler32.o: ../external/zlib/adler32.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object external/zlib/CMakeFiles/zlib.dir/adler32.o"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/zlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/zlib.dir/adler32.o   -c /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/zlib/adler32.c

external/zlib/CMakeFiles/zlib.dir/adler32.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/zlib.dir/adler32.i"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/zlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/zlib/adler32.c > CMakeFiles/zlib.dir/adler32.i

external/zlib/CMakeFiles/zlib.dir/adler32.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/zlib.dir/adler32.s"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/zlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/zlib/adler32.c -o CMakeFiles/zlib.dir/adler32.s

external/zlib/CMakeFiles/zlib.dir/compress.o: external/zlib/CMakeFiles/zlib.dir/flags.make
external/zlib/CMakeFiles/zlib.dir/compress.o: ../external/zlib/compress.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object external/zlib/CMakeFiles/zlib.dir/compress.o"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/zlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/zlib.dir/compress.o   -c /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/zlib/compress.c

external/zlib/CMakeFiles/zlib.dir/compress.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/zlib.dir/compress.i"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/zlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/zlib/compress.c > CMakeFiles/zlib.dir/compress.i

external/zlib/CMakeFiles/zlib.dir/compress.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/zlib.dir/compress.s"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/zlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/zlib/compress.c -o CMakeFiles/zlib.dir/compress.s

external/zlib/CMakeFiles/zlib.dir/crc32.o: external/zlib/CMakeFiles/zlib.dir/flags.make
external/zlib/CMakeFiles/zlib.dir/crc32.o: ../external/zlib/crc32.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object external/zlib/CMakeFiles/zlib.dir/crc32.o"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/zlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/zlib.dir/crc32.o   -c /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/zlib/crc32.c

external/zlib/CMakeFiles/zlib.dir/crc32.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/zlib.dir/crc32.i"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/zlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/zlib/crc32.c > CMakeFiles/zlib.dir/crc32.i

external/zlib/CMakeFiles/zlib.dir/crc32.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/zlib.dir/crc32.s"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/zlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/zlib/crc32.c -o CMakeFiles/zlib.dir/crc32.s

external/zlib/CMakeFiles/zlib.dir/deflate.o: external/zlib/CMakeFiles/zlib.dir/flags.make
external/zlib/CMakeFiles/zlib.dir/deflate.o: ../external/zlib/deflate.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object external/zlib/CMakeFiles/zlib.dir/deflate.o"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/zlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/zlib.dir/deflate.o   -c /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/zlib/deflate.c

external/zlib/CMakeFiles/zlib.dir/deflate.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/zlib.dir/deflate.i"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/zlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/zlib/deflate.c > CMakeFiles/zlib.dir/deflate.i

external/zlib/CMakeFiles/zlib.dir/deflate.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/zlib.dir/deflate.s"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/zlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/zlib/deflate.c -o CMakeFiles/zlib.dir/deflate.s

external/zlib/CMakeFiles/zlib.dir/gzclose.o: external/zlib/CMakeFiles/zlib.dir/flags.make
external/zlib/CMakeFiles/zlib.dir/gzclose.o: ../external/zlib/gzclose.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object external/zlib/CMakeFiles/zlib.dir/gzclose.o"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/zlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/zlib.dir/gzclose.o   -c /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/zlib/gzclose.c

external/zlib/CMakeFiles/zlib.dir/gzclose.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/zlib.dir/gzclose.i"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/zlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/zlib/gzclose.c > CMakeFiles/zlib.dir/gzclose.i

external/zlib/CMakeFiles/zlib.dir/gzclose.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/zlib.dir/gzclose.s"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/zlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/zlib/gzclose.c -o CMakeFiles/zlib.dir/gzclose.s

external/zlib/CMakeFiles/zlib.dir/gzlib.o: external/zlib/CMakeFiles/zlib.dir/flags.make
external/zlib/CMakeFiles/zlib.dir/gzlib.o: ../external/zlib/gzlib.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object external/zlib/CMakeFiles/zlib.dir/gzlib.o"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/zlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/zlib.dir/gzlib.o   -c /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/zlib/gzlib.c

external/zlib/CMakeFiles/zlib.dir/gzlib.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/zlib.dir/gzlib.i"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/zlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/zlib/gzlib.c > CMakeFiles/zlib.dir/gzlib.i

external/zlib/CMakeFiles/zlib.dir/gzlib.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/zlib.dir/gzlib.s"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/zlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/zlib/gzlib.c -o CMakeFiles/zlib.dir/gzlib.s

external/zlib/CMakeFiles/zlib.dir/gzread.o: external/zlib/CMakeFiles/zlib.dir/flags.make
external/zlib/CMakeFiles/zlib.dir/gzread.o: ../external/zlib/gzread.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object external/zlib/CMakeFiles/zlib.dir/gzread.o"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/zlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/zlib.dir/gzread.o   -c /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/zlib/gzread.c

external/zlib/CMakeFiles/zlib.dir/gzread.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/zlib.dir/gzread.i"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/zlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/zlib/gzread.c > CMakeFiles/zlib.dir/gzread.i

external/zlib/CMakeFiles/zlib.dir/gzread.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/zlib.dir/gzread.s"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/zlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/zlib/gzread.c -o CMakeFiles/zlib.dir/gzread.s

external/zlib/CMakeFiles/zlib.dir/gzwrite.o: external/zlib/CMakeFiles/zlib.dir/flags.make
external/zlib/CMakeFiles/zlib.dir/gzwrite.o: ../external/zlib/gzwrite.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object external/zlib/CMakeFiles/zlib.dir/gzwrite.o"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/zlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/zlib.dir/gzwrite.o   -c /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/zlib/gzwrite.c

external/zlib/CMakeFiles/zlib.dir/gzwrite.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/zlib.dir/gzwrite.i"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/zlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/zlib/gzwrite.c > CMakeFiles/zlib.dir/gzwrite.i

external/zlib/CMakeFiles/zlib.dir/gzwrite.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/zlib.dir/gzwrite.s"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/zlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/zlib/gzwrite.c -o CMakeFiles/zlib.dir/gzwrite.s

external/zlib/CMakeFiles/zlib.dir/inflate.o: external/zlib/CMakeFiles/zlib.dir/flags.make
external/zlib/CMakeFiles/zlib.dir/inflate.o: ../external/zlib/inflate.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building C object external/zlib/CMakeFiles/zlib.dir/inflate.o"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/zlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/zlib.dir/inflate.o   -c /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/zlib/inflate.c

external/zlib/CMakeFiles/zlib.dir/inflate.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/zlib.dir/inflate.i"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/zlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/zlib/inflate.c > CMakeFiles/zlib.dir/inflate.i

external/zlib/CMakeFiles/zlib.dir/inflate.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/zlib.dir/inflate.s"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/zlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/zlib/inflate.c -o CMakeFiles/zlib.dir/inflate.s

external/zlib/CMakeFiles/zlib.dir/infback.o: external/zlib/CMakeFiles/zlib.dir/flags.make
external/zlib/CMakeFiles/zlib.dir/infback.o: ../external/zlib/infback.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building C object external/zlib/CMakeFiles/zlib.dir/infback.o"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/zlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/zlib.dir/infback.o   -c /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/zlib/infback.c

external/zlib/CMakeFiles/zlib.dir/infback.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/zlib.dir/infback.i"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/zlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/zlib/infback.c > CMakeFiles/zlib.dir/infback.i

external/zlib/CMakeFiles/zlib.dir/infback.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/zlib.dir/infback.s"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/zlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/zlib/infback.c -o CMakeFiles/zlib.dir/infback.s

external/zlib/CMakeFiles/zlib.dir/inftrees.o: external/zlib/CMakeFiles/zlib.dir/flags.make
external/zlib/CMakeFiles/zlib.dir/inftrees.o: ../external/zlib/inftrees.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building C object external/zlib/CMakeFiles/zlib.dir/inftrees.o"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/zlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/zlib.dir/inftrees.o   -c /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/zlib/inftrees.c

external/zlib/CMakeFiles/zlib.dir/inftrees.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/zlib.dir/inftrees.i"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/zlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/zlib/inftrees.c > CMakeFiles/zlib.dir/inftrees.i

external/zlib/CMakeFiles/zlib.dir/inftrees.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/zlib.dir/inftrees.s"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/zlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/zlib/inftrees.c -o CMakeFiles/zlib.dir/inftrees.s

external/zlib/CMakeFiles/zlib.dir/inffast.o: external/zlib/CMakeFiles/zlib.dir/flags.make
external/zlib/CMakeFiles/zlib.dir/inffast.o: ../external/zlib/inffast.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building C object external/zlib/CMakeFiles/zlib.dir/inffast.o"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/zlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/zlib.dir/inffast.o   -c /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/zlib/inffast.c

external/zlib/CMakeFiles/zlib.dir/inffast.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/zlib.dir/inffast.i"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/zlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/zlib/inffast.c > CMakeFiles/zlib.dir/inffast.i

external/zlib/CMakeFiles/zlib.dir/inffast.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/zlib.dir/inffast.s"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/zlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/zlib/inffast.c -o CMakeFiles/zlib.dir/inffast.s

external/zlib/CMakeFiles/zlib.dir/trees.o: external/zlib/CMakeFiles/zlib.dir/flags.make
external/zlib/CMakeFiles/zlib.dir/trees.o: ../external/zlib/trees.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building C object external/zlib/CMakeFiles/zlib.dir/trees.o"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/zlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/zlib.dir/trees.o   -c /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/zlib/trees.c

external/zlib/CMakeFiles/zlib.dir/trees.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/zlib.dir/trees.i"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/zlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/zlib/trees.c > CMakeFiles/zlib.dir/trees.i

external/zlib/CMakeFiles/zlib.dir/trees.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/zlib.dir/trees.s"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/zlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/zlib/trees.c -o CMakeFiles/zlib.dir/trees.s

external/zlib/CMakeFiles/zlib.dir/uncompr.o: external/zlib/CMakeFiles/zlib.dir/flags.make
external/zlib/CMakeFiles/zlib.dir/uncompr.o: ../external/zlib/uncompr.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building C object external/zlib/CMakeFiles/zlib.dir/uncompr.o"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/zlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/zlib.dir/uncompr.o   -c /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/zlib/uncompr.c

external/zlib/CMakeFiles/zlib.dir/uncompr.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/zlib.dir/uncompr.i"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/zlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/zlib/uncompr.c > CMakeFiles/zlib.dir/uncompr.i

external/zlib/CMakeFiles/zlib.dir/uncompr.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/zlib.dir/uncompr.s"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/zlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/zlib/uncompr.c -o CMakeFiles/zlib.dir/uncompr.s

external/zlib/CMakeFiles/zlib.dir/zutil.o: external/zlib/CMakeFiles/zlib.dir/flags.make
external/zlib/CMakeFiles/zlib.dir/zutil.o: ../external/zlib/zutil.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Building C object external/zlib/CMakeFiles/zlib.dir/zutil.o"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/zlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/zlib.dir/zutil.o   -c /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/zlib/zutil.c

external/zlib/CMakeFiles/zlib.dir/zutil.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/zlib.dir/zutil.i"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/zlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/zlib/zutil.c > CMakeFiles/zlib.dir/zutil.i

external/zlib/CMakeFiles/zlib.dir/zutil.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/zlib.dir/zutil.s"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/zlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/zlib/zutil.c -o CMakeFiles/zlib.dir/zutil.s

# Object files for target zlib
zlib_OBJECTS = \
"CMakeFiles/zlib.dir/adler32.o" \
"CMakeFiles/zlib.dir/compress.o" \
"CMakeFiles/zlib.dir/crc32.o" \
"CMakeFiles/zlib.dir/deflate.o" \
"CMakeFiles/zlib.dir/gzclose.o" \
"CMakeFiles/zlib.dir/gzlib.o" \
"CMakeFiles/zlib.dir/gzread.o" \
"CMakeFiles/zlib.dir/gzwrite.o" \
"CMakeFiles/zlib.dir/inflate.o" \
"CMakeFiles/zlib.dir/infback.o" \
"CMakeFiles/zlib.dir/inftrees.o" \
"CMakeFiles/zlib.dir/inffast.o" \
"CMakeFiles/zlib.dir/trees.o" \
"CMakeFiles/zlib.dir/uncompr.o" \
"CMakeFiles/zlib.dir/zutil.o"

# External object files for target zlib
zlib_EXTERNAL_OBJECTS =

external/zlib/libzlib.a: external/zlib/CMakeFiles/zlib.dir/adler32.o
external/zlib/libzlib.a: external/zlib/CMakeFiles/zlib.dir/compress.o
external/zlib/libzlib.a: external/zlib/CMakeFiles/zlib.dir/crc32.o
external/zlib/libzlib.a: external/zlib/CMakeFiles/zlib.dir/deflate.o
external/zlib/libzlib.a: external/zlib/CMakeFiles/zlib.dir/gzclose.o
external/zlib/libzlib.a: external/zlib/CMakeFiles/zlib.dir/gzlib.o
external/zlib/libzlib.a: external/zlib/CMakeFiles/zlib.dir/gzread.o
external/zlib/libzlib.a: external/zlib/CMakeFiles/zlib.dir/gzwrite.o
external/zlib/libzlib.a: external/zlib/CMakeFiles/zlib.dir/inflate.o
external/zlib/libzlib.a: external/zlib/CMakeFiles/zlib.dir/infback.o
external/zlib/libzlib.a: external/zlib/CMakeFiles/zlib.dir/inftrees.o
external/zlib/libzlib.a: external/zlib/CMakeFiles/zlib.dir/inffast.o
external/zlib/libzlib.a: external/zlib/CMakeFiles/zlib.dir/trees.o
external/zlib/libzlib.a: external/zlib/CMakeFiles/zlib.dir/uncompr.o
external/zlib/libzlib.a: external/zlib/CMakeFiles/zlib.dir/zutil.o
external/zlib/libzlib.a: external/zlib/CMakeFiles/zlib.dir/build.make
external/zlib/libzlib.a: external/zlib/CMakeFiles/zlib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_16) "Linking C static library libzlib.a"
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/zlib && $(CMAKE_COMMAND) -P CMakeFiles/zlib.dir/cmake_clean_target.cmake
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/zlib && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/zlib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
external/zlib/CMakeFiles/zlib.dir/build: external/zlib/libzlib.a

.PHONY : external/zlib/CMakeFiles/zlib.dir/build

external/zlib/CMakeFiles/zlib.dir/clean:
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/zlib && $(CMAKE_COMMAND) -P CMakeFiles/zlib.dir/cmake_clean.cmake
.PHONY : external/zlib/CMakeFiles/zlib.dir/clean

external/zlib/CMakeFiles/zlib.dir/depend:
	cd /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/xuemeng/work/flywave/mapnic/flywave-mapnik /home/xuemeng/work/flywave/mapnic/flywave-mapnik/external/zlib /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/zlib /home/xuemeng/work/flywave/mapnic/flywave-mapnik/build/external/zlib/CMakeFiles/zlib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : external/zlib/CMakeFiles/zlib.dir/depend

