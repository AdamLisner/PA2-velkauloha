# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_COMMAND = /snap/clion/275/bin/cmake/linux/x64/bin/cmake

# The command to remove a file.
RM = /snap/clion/275/bin/cmake/linux/x64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/adam/Documents/School/velkauloha

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/adam/Documents/School/velkauloha/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/VelkaUloha.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/VelkaUloha.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/VelkaUloha.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/VelkaUloha.dir/flags.make

CMakeFiles/VelkaUloha.dir/test.cpp.o: CMakeFiles/VelkaUloha.dir/flags.make
CMakeFiles/VelkaUloha.dir/test.cpp.o: /home/adam/Documents/School/velkauloha/test.cpp
CMakeFiles/VelkaUloha.dir/test.cpp.o: CMakeFiles/VelkaUloha.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/adam/Documents/School/velkauloha/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/VelkaUloha.dir/test.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/VelkaUloha.dir/test.cpp.o -MF CMakeFiles/VelkaUloha.dir/test.cpp.o.d -o CMakeFiles/VelkaUloha.dir/test.cpp.o -c /home/adam/Documents/School/velkauloha/test.cpp

CMakeFiles/VelkaUloha.dir/test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/VelkaUloha.dir/test.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/adam/Documents/School/velkauloha/test.cpp > CMakeFiles/VelkaUloha.dir/test.cpp.i

CMakeFiles/VelkaUloha.dir/test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/VelkaUloha.dir/test.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/adam/Documents/School/velkauloha/test.cpp -o CMakeFiles/VelkaUloha.dir/test.cpp.s

CMakeFiles/VelkaUloha.dir/ASTBuilder.cpp.o: CMakeFiles/VelkaUloha.dir/flags.make
CMakeFiles/VelkaUloha.dir/ASTBuilder.cpp.o: /home/adam/Documents/School/velkauloha/ASTBuilder.cpp
CMakeFiles/VelkaUloha.dir/ASTBuilder.cpp.o: CMakeFiles/VelkaUloha.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/adam/Documents/School/velkauloha/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/VelkaUloha.dir/ASTBuilder.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/VelkaUloha.dir/ASTBuilder.cpp.o -MF CMakeFiles/VelkaUloha.dir/ASTBuilder.cpp.o.d -o CMakeFiles/VelkaUloha.dir/ASTBuilder.cpp.o -c /home/adam/Documents/School/velkauloha/ASTBuilder.cpp

CMakeFiles/VelkaUloha.dir/ASTBuilder.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/VelkaUloha.dir/ASTBuilder.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/adam/Documents/School/velkauloha/ASTBuilder.cpp > CMakeFiles/VelkaUloha.dir/ASTBuilder.cpp.i

CMakeFiles/VelkaUloha.dir/ASTBuilder.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/VelkaUloha.dir/ASTBuilder.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/adam/Documents/School/velkauloha/ASTBuilder.cpp -o CMakeFiles/VelkaUloha.dir/ASTBuilder.cpp.s

CMakeFiles/VelkaUloha.dir/AST.cpp.o: CMakeFiles/VelkaUloha.dir/flags.make
CMakeFiles/VelkaUloha.dir/AST.cpp.o: /home/adam/Documents/School/velkauloha/AST.cpp
CMakeFiles/VelkaUloha.dir/AST.cpp.o: CMakeFiles/VelkaUloha.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/adam/Documents/School/velkauloha/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/VelkaUloha.dir/AST.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/VelkaUloha.dir/AST.cpp.o -MF CMakeFiles/VelkaUloha.dir/AST.cpp.o.d -o CMakeFiles/VelkaUloha.dir/AST.cpp.o -c /home/adam/Documents/School/velkauloha/AST.cpp

CMakeFiles/VelkaUloha.dir/AST.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/VelkaUloha.dir/AST.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/adam/Documents/School/velkauloha/AST.cpp > CMakeFiles/VelkaUloha.dir/AST.cpp.i

CMakeFiles/VelkaUloha.dir/AST.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/VelkaUloha.dir/AST.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/adam/Documents/School/velkauloha/AST.cpp -o CMakeFiles/VelkaUloha.dir/AST.cpp.s

CMakeFiles/VelkaUloha.dir/CPos.cpp.o: CMakeFiles/VelkaUloha.dir/flags.make
CMakeFiles/VelkaUloha.dir/CPos.cpp.o: /home/adam/Documents/School/velkauloha/CPos.cpp
CMakeFiles/VelkaUloha.dir/CPos.cpp.o: CMakeFiles/VelkaUloha.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/adam/Documents/School/velkauloha/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/VelkaUloha.dir/CPos.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/VelkaUloha.dir/CPos.cpp.o -MF CMakeFiles/VelkaUloha.dir/CPos.cpp.o.d -o CMakeFiles/VelkaUloha.dir/CPos.cpp.o -c /home/adam/Documents/School/velkauloha/CPos.cpp

CMakeFiles/VelkaUloha.dir/CPos.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/VelkaUloha.dir/CPos.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/adam/Documents/School/velkauloha/CPos.cpp > CMakeFiles/VelkaUloha.dir/CPos.cpp.i

CMakeFiles/VelkaUloha.dir/CPos.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/VelkaUloha.dir/CPos.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/adam/Documents/School/velkauloha/CPos.cpp -o CMakeFiles/VelkaUloha.dir/CPos.cpp.s

# Object files for target VelkaUloha
VelkaUloha_OBJECTS = \
"CMakeFiles/VelkaUloha.dir/test.cpp.o" \
"CMakeFiles/VelkaUloha.dir/ASTBuilder.cpp.o" \
"CMakeFiles/VelkaUloha.dir/AST.cpp.o" \
"CMakeFiles/VelkaUloha.dir/CPos.cpp.o"

# External object files for target VelkaUloha
VelkaUloha_EXTERNAL_OBJECTS =

VelkaUloha: CMakeFiles/VelkaUloha.dir/test.cpp.o
VelkaUloha: CMakeFiles/VelkaUloha.dir/ASTBuilder.cpp.o
VelkaUloha: CMakeFiles/VelkaUloha.dir/AST.cpp.o
VelkaUloha: CMakeFiles/VelkaUloha.dir/CPos.cpp.o
VelkaUloha: CMakeFiles/VelkaUloha.dir/build.make
VelkaUloha: CMakeFiles/VelkaUloha.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/adam/Documents/School/velkauloha/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable VelkaUloha"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/VelkaUloha.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/VelkaUloha.dir/build: VelkaUloha
.PHONY : CMakeFiles/VelkaUloha.dir/build

CMakeFiles/VelkaUloha.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/VelkaUloha.dir/cmake_clean.cmake
.PHONY : CMakeFiles/VelkaUloha.dir/clean

CMakeFiles/VelkaUloha.dir/depend:
	cd /home/adam/Documents/School/velkauloha/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/adam/Documents/School/velkauloha /home/adam/Documents/School/velkauloha /home/adam/Documents/School/velkauloha/cmake-build-debug /home/adam/Documents/School/velkauloha/cmake-build-debug /home/adam/Documents/School/velkauloha/cmake-build-debug/CMakeFiles/VelkaUloha.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/VelkaUloha.dir/depend

