# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_SOURCE_DIR = /home/piternet/mimuw/pw-zad2/adorators-files/pn371273

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/piternet/mimuw/pw-zad2/adorators-files/pn371273/build

# Include any dependencies generated for this target.
include CMakeFiles/adorate.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/adorate.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/adorate.dir/flags.make

CMakeFiles/adorate.dir/adorate-seq.cpp.o: CMakeFiles/adorate.dir/flags.make
CMakeFiles/adorate.dir/adorate-seq.cpp.o: ../adorate-seq.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/piternet/mimuw/pw-zad2/adorators-files/pn371273/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/adorate.dir/adorate-seq.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/adorate.dir/adorate-seq.cpp.o -c /home/piternet/mimuw/pw-zad2/adorators-files/pn371273/adorate-seq.cpp

CMakeFiles/adorate.dir/adorate-seq.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/adorate.dir/adorate-seq.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/piternet/mimuw/pw-zad2/adorators-files/pn371273/adorate-seq.cpp > CMakeFiles/adorate.dir/adorate-seq.cpp.i

CMakeFiles/adorate.dir/adorate-seq.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/adorate.dir/adorate-seq.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/piternet/mimuw/pw-zad2/adorators-files/pn371273/adorate-seq.cpp -o CMakeFiles/adorate.dir/adorate-seq.cpp.s

CMakeFiles/adorate.dir/adorate-seq.cpp.o.requires:
.PHONY : CMakeFiles/adorate.dir/adorate-seq.cpp.o.requires

CMakeFiles/adorate.dir/adorate-seq.cpp.o.provides: CMakeFiles/adorate.dir/adorate-seq.cpp.o.requires
	$(MAKE) -f CMakeFiles/adorate.dir/build.make CMakeFiles/adorate.dir/adorate-seq.cpp.o.provides.build
.PHONY : CMakeFiles/adorate.dir/adorate-seq.cpp.o.provides

CMakeFiles/adorate.dir/adorate-seq.cpp.o.provides.build: CMakeFiles/adorate.dir/adorate-seq.cpp.o

CMakeFiles/adorate.dir/blimit.cpp.o: CMakeFiles/adorate.dir/flags.make
CMakeFiles/adorate.dir/blimit.cpp.o: ../blimit.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/piternet/mimuw/pw-zad2/adorators-files/pn371273/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/adorate.dir/blimit.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/adorate.dir/blimit.cpp.o -c /home/piternet/mimuw/pw-zad2/adorators-files/pn371273/blimit.cpp

CMakeFiles/adorate.dir/blimit.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/adorate.dir/blimit.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/piternet/mimuw/pw-zad2/adorators-files/pn371273/blimit.cpp > CMakeFiles/adorate.dir/blimit.cpp.i

CMakeFiles/adorate.dir/blimit.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/adorate.dir/blimit.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/piternet/mimuw/pw-zad2/adorators-files/pn371273/blimit.cpp -o CMakeFiles/adorate.dir/blimit.cpp.s

CMakeFiles/adorate.dir/blimit.cpp.o.requires:
.PHONY : CMakeFiles/adorate.dir/blimit.cpp.o.requires

CMakeFiles/adorate.dir/blimit.cpp.o.provides: CMakeFiles/adorate.dir/blimit.cpp.o.requires
	$(MAKE) -f CMakeFiles/adorate.dir/build.make CMakeFiles/adorate.dir/blimit.cpp.o.provides.build
.PHONY : CMakeFiles/adorate.dir/blimit.cpp.o.provides

CMakeFiles/adorate.dir/blimit.cpp.o.provides.build: CMakeFiles/adorate.dir/blimit.cpp.o

# Object files for target adorate
adorate_OBJECTS = \
"CMakeFiles/adorate.dir/adorate-seq.cpp.o" \
"CMakeFiles/adorate.dir/blimit.cpp.o"

# External object files for target adorate
adorate_EXTERNAL_OBJECTS =

adorate: CMakeFiles/adorate.dir/adorate-seq.cpp.o
adorate: CMakeFiles/adorate.dir/blimit.cpp.o
adorate: CMakeFiles/adorate.dir/build.make
adorate: CMakeFiles/adorate.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable adorate"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/adorate.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/adorate.dir/build: adorate
.PHONY : CMakeFiles/adorate.dir/build

CMakeFiles/adorate.dir/requires: CMakeFiles/adorate.dir/adorate-seq.cpp.o.requires
CMakeFiles/adorate.dir/requires: CMakeFiles/adorate.dir/blimit.cpp.o.requires
.PHONY : CMakeFiles/adorate.dir/requires

CMakeFiles/adorate.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/adorate.dir/cmake_clean.cmake
.PHONY : CMakeFiles/adorate.dir/clean

CMakeFiles/adorate.dir/depend:
	cd /home/piternet/mimuw/pw-zad2/adorators-files/pn371273/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/piternet/mimuw/pw-zad2/adorators-files/pn371273 /home/piternet/mimuw/pw-zad2/adorators-files/pn371273 /home/piternet/mimuw/pw-zad2/adorators-files/pn371273/build /home/piternet/mimuw/pw-zad2/adorators-files/pn371273/build /home/piternet/mimuw/pw-zad2/adorators-files/pn371273/build/CMakeFiles/adorate.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/adorate.dir/depend

