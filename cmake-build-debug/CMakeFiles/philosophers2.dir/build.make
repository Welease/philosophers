# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
CMAKE_COMMAND = /private/var/folders/zz/zyxvpxvq6csfxvn_n003vd8w00yv_7/T/AppTranslocation/247BAC7B-F699-4244-A85F-592DF8E8F13B/d/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /private/var/folders/zz/zyxvpxvq6csfxvn_n003vd8w00yv_7/T/AppTranslocation/247BAC7B-F699-4244-A85F-592DF8E8F13B/d/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/welease/projects/philosophers

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/welease/projects/philosophers/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/philosophers2.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/philosophers2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/philosophers2.dir/flags.make

CMakeFiles/philosophers2.dir/philo_two/initing.c.o: CMakeFiles/philosophers2.dir/flags.make
CMakeFiles/philosophers2.dir/philo_two/initing.c.o: ../philo_two/initing.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/welease/projects/philosophers/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/philosophers2.dir/philo_two/initing.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/philosophers2.dir/philo_two/initing.c.o   -c /Users/welease/projects/philosophers/philo_two/initing.c

CMakeFiles/philosophers2.dir/philo_two/initing.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/philosophers2.dir/philo_two/initing.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/welease/projects/philosophers/philo_two/initing.c > CMakeFiles/philosophers2.dir/philo_two/initing.c.i

CMakeFiles/philosophers2.dir/philo_two/initing.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/philosophers2.dir/philo_two/initing.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/welease/projects/philosophers/philo_two/initing.c -o CMakeFiles/philosophers2.dir/philo_two/initing.c.s

CMakeFiles/philosophers2.dir/philo_two/main.c.o: CMakeFiles/philosophers2.dir/flags.make
CMakeFiles/philosophers2.dir/philo_two/main.c.o: ../philo_two/main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/welease/projects/philosophers/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/philosophers2.dir/philo_two/main.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/philosophers2.dir/philo_two/main.c.o   -c /Users/welease/projects/philosophers/philo_two/main.c

CMakeFiles/philosophers2.dir/philo_two/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/philosophers2.dir/philo_two/main.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/welease/projects/philosophers/philo_two/main.c > CMakeFiles/philosophers2.dir/philo_two/main.c.i

CMakeFiles/philosophers2.dir/philo_two/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/philosophers2.dir/philo_two/main.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/welease/projects/philosophers/philo_two/main.c -o CMakeFiles/philosophers2.dir/philo_two/main.c.s

CMakeFiles/philosophers2.dir/philo_two/parsing.c.o: CMakeFiles/philosophers2.dir/flags.make
CMakeFiles/philosophers2.dir/philo_two/parsing.c.o: ../philo_two/parsing.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/welease/projects/philosophers/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/philosophers2.dir/philo_two/parsing.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/philosophers2.dir/philo_two/parsing.c.o   -c /Users/welease/projects/philosophers/philo_two/parsing.c

CMakeFiles/philosophers2.dir/philo_two/parsing.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/philosophers2.dir/philo_two/parsing.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/welease/projects/philosophers/philo_two/parsing.c > CMakeFiles/philosophers2.dir/philo_two/parsing.c.i

CMakeFiles/philosophers2.dir/philo_two/parsing.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/philosophers2.dir/philo_two/parsing.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/welease/projects/philosophers/philo_two/parsing.c -o CMakeFiles/philosophers2.dir/philo_two/parsing.c.s

CMakeFiles/philosophers2.dir/philo_two/utils.c.o: CMakeFiles/philosophers2.dir/flags.make
CMakeFiles/philosophers2.dir/philo_two/utils.c.o: ../philo_two/utils.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/welease/projects/philosophers/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/philosophers2.dir/philo_two/utils.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/philosophers2.dir/philo_two/utils.c.o   -c /Users/welease/projects/philosophers/philo_two/utils.c

CMakeFiles/philosophers2.dir/philo_two/utils.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/philosophers2.dir/philo_two/utils.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/welease/projects/philosophers/philo_two/utils.c > CMakeFiles/philosophers2.dir/philo_two/utils.c.i

CMakeFiles/philosophers2.dir/philo_two/utils.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/philosophers2.dir/philo_two/utils.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/welease/projects/philosophers/philo_two/utils.c -o CMakeFiles/philosophers2.dir/philo_two/utils.c.s

# Object files for target philosophers2
philosophers2_OBJECTS = \
"CMakeFiles/philosophers2.dir/philo_two/initing.c.o" \
"CMakeFiles/philosophers2.dir/philo_two/main.c.o" \
"CMakeFiles/philosophers2.dir/philo_two/parsing.c.o" \
"CMakeFiles/philosophers2.dir/philo_two/utils.c.o"

# External object files for target philosophers2
philosophers2_EXTERNAL_OBJECTS =

philosophers2: CMakeFiles/philosophers2.dir/philo_two/initing.c.o
philosophers2: CMakeFiles/philosophers2.dir/philo_two/main.c.o
philosophers2: CMakeFiles/philosophers2.dir/philo_two/parsing.c.o
philosophers2: CMakeFiles/philosophers2.dir/philo_two/utils.c.o
philosophers2: CMakeFiles/philosophers2.dir/build.make
philosophers2: CMakeFiles/philosophers2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/welease/projects/philosophers/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking C executable philosophers2"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/philosophers2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/philosophers2.dir/build: philosophers2

.PHONY : CMakeFiles/philosophers2.dir/build

CMakeFiles/philosophers2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/philosophers2.dir/cmake_clean.cmake
.PHONY : CMakeFiles/philosophers2.dir/clean

CMakeFiles/philosophers2.dir/depend:
	cd /Users/welease/projects/philosophers/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/welease/projects/philosophers /Users/welease/projects/philosophers /Users/welease/projects/philosophers/cmake-build-debug /Users/welease/projects/philosophers/cmake-build-debug /Users/welease/projects/philosophers/cmake-build-debug/CMakeFiles/philosophers2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/philosophers2.dir/depend
