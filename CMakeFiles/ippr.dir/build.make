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
CMAKE_SOURCE_DIR = /home/wenjiequ/testjpeg

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/wenjiequ/testjpeg

# Include any dependencies generated for this target.
include CMakeFiles/ippr.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/ippr.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/ippr.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ippr.dir/flags.make

CMakeFiles/ippr.dir/jpeg.cpp.o: CMakeFiles/ippr.dir/flags.make
CMakeFiles/ippr.dir/jpeg.cpp.o: jpeg.cpp
CMakeFiles/ippr.dir/jpeg.cpp.o: CMakeFiles/ippr.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wenjiequ/testjpeg/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ippr.dir/jpeg.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ippr.dir/jpeg.cpp.o -MF CMakeFiles/ippr.dir/jpeg.cpp.o.d -o CMakeFiles/ippr.dir/jpeg.cpp.o -c /home/wenjiequ/testjpeg/jpeg.cpp

CMakeFiles/ippr.dir/jpeg.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ippr.dir/jpeg.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wenjiequ/testjpeg/jpeg.cpp > CMakeFiles/ippr.dir/jpeg.cpp.i

CMakeFiles/ippr.dir/jpeg.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ippr.dir/jpeg.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wenjiequ/testjpeg/jpeg.cpp -o CMakeFiles/ippr.dir/jpeg.cpp.s

CMakeFiles/ippr.dir/jpegwrite.cpp.o: CMakeFiles/ippr.dir/flags.make
CMakeFiles/ippr.dir/jpegwrite.cpp.o: jpegwrite.cpp
CMakeFiles/ippr.dir/jpegwrite.cpp.o: CMakeFiles/ippr.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wenjiequ/testjpeg/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/ippr.dir/jpegwrite.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ippr.dir/jpegwrite.cpp.o -MF CMakeFiles/ippr.dir/jpegwrite.cpp.o.d -o CMakeFiles/ippr.dir/jpegwrite.cpp.o -c /home/wenjiequ/testjpeg/jpegwrite.cpp

CMakeFiles/ippr.dir/jpegwrite.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ippr.dir/jpegwrite.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wenjiequ/testjpeg/jpegwrite.cpp > CMakeFiles/ippr.dir/jpegwrite.cpp.i

CMakeFiles/ippr.dir/jpegwrite.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ippr.dir/jpegwrite.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wenjiequ/testjpeg/jpegwrite.cpp -o CMakeFiles/ippr.dir/jpegwrite.cpp.s

CMakeFiles/ippr.dir/ddraw.cpp.o: CMakeFiles/ippr.dir/flags.make
CMakeFiles/ippr.dir/ddraw.cpp.o: ddraw.cpp
CMakeFiles/ippr.dir/ddraw.cpp.o: CMakeFiles/ippr.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wenjiequ/testjpeg/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/ippr.dir/ddraw.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ippr.dir/ddraw.cpp.o -MF CMakeFiles/ippr.dir/ddraw.cpp.o.d -o CMakeFiles/ippr.dir/ddraw.cpp.o -c /home/wenjiequ/testjpeg/ddraw.cpp

CMakeFiles/ippr.dir/ddraw.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ippr.dir/ddraw.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wenjiequ/testjpeg/ddraw.cpp > CMakeFiles/ippr.dir/ddraw.cpp.i

CMakeFiles/ippr.dir/ddraw.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ippr.dir/ddraw.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wenjiequ/testjpeg/ddraw.cpp -o CMakeFiles/ippr.dir/ddraw.cpp.s

CMakeFiles/ippr.dir/util.cpp.o: CMakeFiles/ippr.dir/flags.make
CMakeFiles/ippr.dir/util.cpp.o: util.cpp
CMakeFiles/ippr.dir/util.cpp.o: CMakeFiles/ippr.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wenjiequ/testjpeg/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/ippr.dir/util.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ippr.dir/util.cpp.o -MF CMakeFiles/ippr.dir/util.cpp.o.d -o CMakeFiles/ippr.dir/util.cpp.o -c /home/wenjiequ/testjpeg/util.cpp

CMakeFiles/ippr.dir/util.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ippr.dir/util.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wenjiequ/testjpeg/util.cpp > CMakeFiles/ippr.dir/util.cpp.i

CMakeFiles/ippr.dir/util.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ippr.dir/util.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wenjiequ/testjpeg/util.cpp -o CMakeFiles/ippr.dir/util.cpp.s

CMakeFiles/ippr.dir/morpho.cpp.o: CMakeFiles/ippr.dir/flags.make
CMakeFiles/ippr.dir/morpho.cpp.o: morpho.cpp
CMakeFiles/ippr.dir/morpho.cpp.o: CMakeFiles/ippr.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wenjiequ/testjpeg/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/ippr.dir/morpho.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ippr.dir/morpho.cpp.o -MF CMakeFiles/ippr.dir/morpho.cpp.o.d -o CMakeFiles/ippr.dir/morpho.cpp.o -c /home/wenjiequ/testjpeg/morpho.cpp

CMakeFiles/ippr.dir/morpho.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ippr.dir/morpho.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wenjiequ/testjpeg/morpho.cpp > CMakeFiles/ippr.dir/morpho.cpp.i

CMakeFiles/ippr.dir/morpho.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ippr.dir/morpho.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wenjiequ/testjpeg/morpho.cpp -o CMakeFiles/ippr.dir/morpho.cpp.s

CMakeFiles/ippr.dir/main.cpp.o: CMakeFiles/ippr.dir/flags.make
CMakeFiles/ippr.dir/main.cpp.o: main.cpp
CMakeFiles/ippr.dir/main.cpp.o: CMakeFiles/ippr.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wenjiequ/testjpeg/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/ippr.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ippr.dir/main.cpp.o -MF CMakeFiles/ippr.dir/main.cpp.o.d -o CMakeFiles/ippr.dir/main.cpp.o -c /home/wenjiequ/testjpeg/main.cpp

CMakeFiles/ippr.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ippr.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wenjiequ/testjpeg/main.cpp > CMakeFiles/ippr.dir/main.cpp.i

CMakeFiles/ippr.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ippr.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wenjiequ/testjpeg/main.cpp -o CMakeFiles/ippr.dir/main.cpp.s

# Object files for target ippr
ippr_OBJECTS = \
"CMakeFiles/ippr.dir/jpeg.cpp.o" \
"CMakeFiles/ippr.dir/jpegwrite.cpp.o" \
"CMakeFiles/ippr.dir/ddraw.cpp.o" \
"CMakeFiles/ippr.dir/util.cpp.o" \
"CMakeFiles/ippr.dir/morpho.cpp.o" \
"CMakeFiles/ippr.dir/main.cpp.o"

# External object files for target ippr
ippr_EXTERNAL_OBJECTS =

ippr: CMakeFiles/ippr.dir/jpeg.cpp.o
ippr: CMakeFiles/ippr.dir/jpegwrite.cpp.o
ippr: CMakeFiles/ippr.dir/ddraw.cpp.o
ippr: CMakeFiles/ippr.dir/util.cpp.o
ippr: CMakeFiles/ippr.dir/morpho.cpp.o
ippr: CMakeFiles/ippr.dir/main.cpp.o
ippr: CMakeFiles/ippr.dir/build.make
ippr: CMakeFiles/ippr.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/wenjiequ/testjpeg/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable ippr"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ippr.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ippr.dir/build: ippr
.PHONY : CMakeFiles/ippr.dir/build

CMakeFiles/ippr.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ippr.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ippr.dir/clean

CMakeFiles/ippr.dir/depend:
	cd /home/wenjiequ/testjpeg && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/wenjiequ/testjpeg /home/wenjiequ/testjpeg /home/wenjiequ/testjpeg /home/wenjiequ/testjpeg /home/wenjiequ/testjpeg/CMakeFiles/ippr.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ippr.dir/depend
