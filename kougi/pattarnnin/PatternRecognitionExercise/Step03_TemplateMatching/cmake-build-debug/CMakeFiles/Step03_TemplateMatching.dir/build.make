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
CMAKE_SOURCE_DIR = /Users/koji/project/kougi/pattarnnin/PatternRecognitionExercise/Step03_TemplateMatching

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/koji/project/kougi/pattarnnin/PatternRecognitionExercise/Step03_TemplateMatching/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Step03_TemplateMatching.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Step03_TemplateMatching.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Step03_TemplateMatching.dir/flags.make

CMakeFiles/Step03_TemplateMatching.dir/main.cpp.o: CMakeFiles/Step03_TemplateMatching.dir/flags.make
CMakeFiles/Step03_TemplateMatching.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/koji/project/kougi/pattarnnin/PatternRecognitionExercise/Step03_TemplateMatching/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Step03_TemplateMatching.dir/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Step03_TemplateMatching.dir/main.cpp.o -c /Users/koji/project/kougi/pattarnnin/PatternRecognitionExercise/Step03_TemplateMatching/main.cpp

CMakeFiles/Step03_TemplateMatching.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Step03_TemplateMatching.dir/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/koji/project/kougi/pattarnnin/PatternRecognitionExercise/Step03_TemplateMatching/main.cpp > CMakeFiles/Step03_TemplateMatching.dir/main.cpp.i

CMakeFiles/Step03_TemplateMatching.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Step03_TemplateMatching.dir/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/koji/project/kougi/pattarnnin/PatternRecognitionExercise/Step03_TemplateMatching/main.cpp -o CMakeFiles/Step03_TemplateMatching.dir/main.cpp.s

CMakeFiles/Step03_TemplateMatching.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/Step03_TemplateMatching.dir/main.cpp.o.requires

CMakeFiles/Step03_TemplateMatching.dir/main.cpp.o.provides: CMakeFiles/Step03_TemplateMatching.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/Step03_TemplateMatching.dir/build.make CMakeFiles/Step03_TemplateMatching.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/Step03_TemplateMatching.dir/main.cpp.o.provides

CMakeFiles/Step03_TemplateMatching.dir/main.cpp.o.provides.build: CMakeFiles/Step03_TemplateMatching.dir/main.cpp.o


# Object files for target Step03_TemplateMatching
Step03_TemplateMatching_OBJECTS = \
"CMakeFiles/Step03_TemplateMatching.dir/main.cpp.o"

# External object files for target Step03_TemplateMatching
Step03_TemplateMatching_EXTERNAL_OBJECTS =

Step03_TemplateMatching: CMakeFiles/Step03_TemplateMatching.dir/main.cpp.o
Step03_TemplateMatching: CMakeFiles/Step03_TemplateMatching.dir/build.make
Step03_TemplateMatching: CMakeFiles/Step03_TemplateMatching.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/koji/project/kougi/pattarnnin/PatternRecognitionExercise/Step03_TemplateMatching/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Step03_TemplateMatching"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Step03_TemplateMatching.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Step03_TemplateMatching.dir/build: Step03_TemplateMatching

.PHONY : CMakeFiles/Step03_TemplateMatching.dir/build

CMakeFiles/Step03_TemplateMatching.dir/requires: CMakeFiles/Step03_TemplateMatching.dir/main.cpp.o.requires

.PHONY : CMakeFiles/Step03_TemplateMatching.dir/requires

CMakeFiles/Step03_TemplateMatching.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Step03_TemplateMatching.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Step03_TemplateMatching.dir/clean

CMakeFiles/Step03_TemplateMatching.dir/depend:
	cd /Users/koji/project/kougi/pattarnnin/PatternRecognitionExercise/Step03_TemplateMatching/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/koji/project/kougi/pattarnnin/PatternRecognitionExercise/Step03_TemplateMatching /Users/koji/project/kougi/pattarnnin/PatternRecognitionExercise/Step03_TemplateMatching /Users/koji/project/kougi/pattarnnin/PatternRecognitionExercise/Step03_TemplateMatching/cmake-build-debug /Users/koji/project/kougi/pattarnnin/PatternRecognitionExercise/Step03_TemplateMatching/cmake-build-debug /Users/koji/project/kougi/pattarnnin/PatternRecognitionExercise/Step03_TemplateMatching/cmake-build-debug/CMakeFiles/Step03_TemplateMatching.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Step03_TemplateMatching.dir/depend
