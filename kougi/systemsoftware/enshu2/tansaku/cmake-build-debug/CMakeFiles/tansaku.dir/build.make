# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/koji/project/kougi/systemsoftware/enshu2/tansaku

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/koji/project/kougi/systemsoftware/enshu2/tansaku/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/tansaku.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/tansaku.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/tansaku.dir/flags.make

CMakeFiles/tansaku.dir/enshu2.c.o: CMakeFiles/tansaku.dir/flags.make
CMakeFiles/tansaku.dir/enshu2.c.o: ../enshu2.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/koji/project/kougi/systemsoftware/enshu2/tansaku/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/tansaku.dir/enshu2.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/tansaku.dir/enshu2.c.o   -c /Users/koji/project/kougi/systemsoftware/enshu2/tansaku/enshu2.c

CMakeFiles/tansaku.dir/enshu2.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/tansaku.dir/enshu2.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/koji/project/kougi/systemsoftware/enshu2/tansaku/enshu2.c > CMakeFiles/tansaku.dir/enshu2.c.i

CMakeFiles/tansaku.dir/enshu2.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/tansaku.dir/enshu2.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/koji/project/kougi/systemsoftware/enshu2/tansaku/enshu2.c -o CMakeFiles/tansaku.dir/enshu2.c.s

CMakeFiles/tansaku.dir/enshu2.c.o.requires:

.PHONY : CMakeFiles/tansaku.dir/enshu2.c.o.requires

CMakeFiles/tansaku.dir/enshu2.c.o.provides: CMakeFiles/tansaku.dir/enshu2.c.o.requires
	$(MAKE) -f CMakeFiles/tansaku.dir/build.make CMakeFiles/tansaku.dir/enshu2.c.o.provides.build
.PHONY : CMakeFiles/tansaku.dir/enshu2.c.o.provides

CMakeFiles/tansaku.dir/enshu2.c.o.provides.build: CMakeFiles/tansaku.dir/enshu2.c.o


# Object files for target tansaku
tansaku_OBJECTS = \
"CMakeFiles/tansaku.dir/enshu2.c.o"

# External object files for target tansaku
tansaku_EXTERNAL_OBJECTS =

tansaku: CMakeFiles/tansaku.dir/enshu2.c.o
tansaku: CMakeFiles/tansaku.dir/build.make
tansaku: CMakeFiles/tansaku.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/koji/project/kougi/systemsoftware/enshu2/tansaku/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable tansaku"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tansaku.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/tansaku.dir/build: tansaku

.PHONY : CMakeFiles/tansaku.dir/build

CMakeFiles/tansaku.dir/requires: CMakeFiles/tansaku.dir/enshu2.c.o.requires

.PHONY : CMakeFiles/tansaku.dir/requires

CMakeFiles/tansaku.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/tansaku.dir/cmake_clean.cmake
.PHONY : CMakeFiles/tansaku.dir/clean

CMakeFiles/tansaku.dir/depend:
	cd /Users/koji/project/kougi/systemsoftware/enshu2/tansaku/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/koji/project/kougi/systemsoftware/enshu2/tansaku /Users/koji/project/kougi/systemsoftware/enshu2/tansaku /Users/koji/project/kougi/systemsoftware/enshu2/tansaku/cmake-build-debug /Users/koji/project/kougi/systemsoftware/enshu2/tansaku/cmake-build-debug /Users/koji/project/kougi/systemsoftware/enshu2/tansaku/cmake-build-debug/CMakeFiles/tansaku.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/tansaku.dir/depend

