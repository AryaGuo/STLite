# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /Users/guowenxuan/文档/学习资料/数据结构/STLite/deque

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/guowenxuan/文档/学习资料/数据结构/STLite/deque/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/deque.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/deque.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/deque.dir/flags.make

CMakeFiles/deque.dir/data/four.memcheck/code.cpp.o: CMakeFiles/deque.dir/flags.make
CMakeFiles/deque.dir/data/four.memcheck/code.cpp.o: ../data/four.memcheck/code.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/guowenxuan/文档/学习资料/数据结构/STLite/deque/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/deque.dir/data/four.memcheck/code.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/deque.dir/data/four.memcheck/code.cpp.o -c /Users/guowenxuan/文档/学习资料/数据结构/STLite/deque/data/four.memcheck/code.cpp

CMakeFiles/deque.dir/data/four.memcheck/code.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/deque.dir/data/four.memcheck/code.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/guowenxuan/文档/学习资料/数据结构/STLite/deque/data/four.memcheck/code.cpp > CMakeFiles/deque.dir/data/four.memcheck/code.cpp.i

CMakeFiles/deque.dir/data/four.memcheck/code.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/deque.dir/data/four.memcheck/code.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/guowenxuan/文档/学习资料/数据结构/STLite/deque/data/four.memcheck/code.cpp -o CMakeFiles/deque.dir/data/four.memcheck/code.cpp.s

CMakeFiles/deque.dir/data/four.memcheck/code.cpp.o.requires:

.PHONY : CMakeFiles/deque.dir/data/four.memcheck/code.cpp.o.requires

CMakeFiles/deque.dir/data/four.memcheck/code.cpp.o.provides: CMakeFiles/deque.dir/data/four.memcheck/code.cpp.o.requires
	$(MAKE) -f CMakeFiles/deque.dir/build.make CMakeFiles/deque.dir/data/four.memcheck/code.cpp.o.provides.build
.PHONY : CMakeFiles/deque.dir/data/four.memcheck/code.cpp.o.provides

CMakeFiles/deque.dir/data/four.memcheck/code.cpp.o.provides.build: CMakeFiles/deque.dir/data/four.memcheck/code.cpp.o


# Object files for target deque
deque_OBJECTS = \
"CMakeFiles/deque.dir/data/four.memcheck/code.cpp.o"

# External object files for target deque
deque_EXTERNAL_OBJECTS =

deque: CMakeFiles/deque.dir/data/four.memcheck/code.cpp.o
deque: CMakeFiles/deque.dir/build.make
deque: CMakeFiles/deque.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/guowenxuan/文档/学习资料/数据结构/STLite/deque/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable deque"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/deque.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/deque.dir/build: deque

.PHONY : CMakeFiles/deque.dir/build

CMakeFiles/deque.dir/requires: CMakeFiles/deque.dir/data/four.memcheck/code.cpp.o.requires

.PHONY : CMakeFiles/deque.dir/requires

CMakeFiles/deque.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/deque.dir/cmake_clean.cmake
.PHONY : CMakeFiles/deque.dir/clean

CMakeFiles/deque.dir/depend:
	cd /Users/guowenxuan/文档/学习资料/数据结构/STLite/deque/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/guowenxuan/文档/学习资料/数据结构/STLite/deque /Users/guowenxuan/文档/学习资料/数据结构/STLite/deque /Users/guowenxuan/文档/学习资料/数据结构/STLite/deque/cmake-build-debug /Users/guowenxuan/文档/学习资料/数据结构/STLite/deque/cmake-build-debug /Users/guowenxuan/文档/学习资料/数据结构/STLite/deque/cmake-build-debug/CMakeFiles/deque.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/deque.dir/depend

