# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

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
CMAKE_SOURCE_DIR = /home/crazy/3-compilerh/c1recognizer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/crazy/3-compilerh/c1recognizer/build

# Utility rule file for rapidjson.

# Include the progress variables for this target.
include CMakeFiles/rapidjson.dir/progress.make

CMakeFiles/rapidjson: CMakeFiles/rapidjson-complete


CMakeFiles/rapidjson-complete: externals/rapidjson/src/rapidjson-stamp/rapidjson-install
CMakeFiles/rapidjson-complete: externals/rapidjson/src/rapidjson-stamp/rapidjson-mkdir
CMakeFiles/rapidjson-complete: externals/rapidjson/src/rapidjson-stamp/rapidjson-download
CMakeFiles/rapidjson-complete: externals/rapidjson/src/rapidjson-stamp/rapidjson-patch
CMakeFiles/rapidjson-complete: externals/rapidjson/src/rapidjson-stamp/rapidjson-configure
CMakeFiles/rapidjson-complete: externals/rapidjson/src/rapidjson-stamp/rapidjson-build
CMakeFiles/rapidjson-complete: externals/rapidjson/src/rapidjson-stamp/rapidjson-install
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/crazy/3-compilerh/c1recognizer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Completed 'rapidjson'"
	/usr/bin/cmake -E make_directory /home/crazy/3-compilerh/c1recognizer/build/CMakeFiles
	/usr/bin/cmake -E touch /home/crazy/3-compilerh/c1recognizer/build/CMakeFiles/rapidjson-complete
	/usr/bin/cmake -E touch /home/crazy/3-compilerh/c1recognizer/build/externals/rapidjson/src/rapidjson-stamp/rapidjson-done

externals/rapidjson/src/rapidjson-stamp/rapidjson-install: externals/rapidjson/src/rapidjson-stamp/rapidjson-build
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/crazy/3-compilerh/c1recognizer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "No install step for 'rapidjson'"
	cd /home/crazy/3-compilerh/c1recognizer/build/externals/rapidjson/src/rapidjson-build && /usr/bin/cmake -E echo_append
	cd /home/crazy/3-compilerh/c1recognizer/build/externals/rapidjson/src/rapidjson-build && /usr/bin/cmake -E touch /home/crazy/3-compilerh/c1recognizer/build/externals/rapidjson/src/rapidjson-stamp/rapidjson-install

externals/rapidjson/src/rapidjson-stamp/rapidjson-mkdir:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/crazy/3-compilerh/c1recognizer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Creating directories for 'rapidjson'"
	/usr/bin/cmake -E make_directory /home/crazy/3-compilerh/c1recognizer/build/externals/rapidjson/src/rapidjson
	/usr/bin/cmake -E make_directory /home/crazy/3-compilerh/c1recognizer/build/externals/rapidjson/src/rapidjson-build
	/usr/bin/cmake -E make_directory /home/crazy/3-compilerh/c1recognizer/build/externals/rapidjson
	/usr/bin/cmake -E make_directory /home/crazy/3-compilerh/c1recognizer/build/externals/rapidjson/tmp
	/usr/bin/cmake -E make_directory /home/crazy/3-compilerh/c1recognizer/build/externals/rapidjson/src/rapidjson-stamp
	/usr/bin/cmake -E make_directory /home/crazy/3-compilerh/c1recognizer/build/externals/rapidjson/src
	/usr/bin/cmake -E touch /home/crazy/3-compilerh/c1recognizer/build/externals/rapidjson/src/rapidjson-stamp/rapidjson-mkdir

externals/rapidjson/src/rapidjson-stamp/rapidjson-download: externals/rapidjson/src/rapidjson-stamp/rapidjson-gitinfo.txt
externals/rapidjson/src/rapidjson-stamp/rapidjson-download: externals/rapidjson/src/rapidjson-stamp/rapidjson-mkdir
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/crazy/3-compilerh/c1recognizer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Performing download step (git clone) for 'rapidjson'"
	cd /home/crazy/3-compilerh/c1recognizer/build/externals/rapidjson/src && /usr/bin/cmake -P /home/crazy/3-compilerh/c1recognizer/build/externals/rapidjson/tmp/rapidjson-gitclone.cmake
	cd /home/crazy/3-compilerh/c1recognizer/build/externals/rapidjson/src && /usr/bin/cmake -E touch /home/crazy/3-compilerh/c1recognizer/build/externals/rapidjson/src/rapidjson-stamp/rapidjson-download

externals/rapidjson/src/rapidjson-stamp/rapidjson-patch: externals/rapidjson/src/rapidjson-stamp/rapidjson-download
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/crazy/3-compilerh/c1recognizer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "No patch step for 'rapidjson'"
	/usr/bin/cmake -E echo_append
	/usr/bin/cmake -E touch /home/crazy/3-compilerh/c1recognizer/build/externals/rapidjson/src/rapidjson-stamp/rapidjson-patch

externals/rapidjson/src/rapidjson-stamp/rapidjson-configure: externals/rapidjson/tmp/rapidjson-cfgcmd.txt
externals/rapidjson/src/rapidjson-stamp/rapidjson-configure: externals/rapidjson/src/rapidjson-stamp/rapidjson-skip-update
externals/rapidjson/src/rapidjson-stamp/rapidjson-configure: externals/rapidjson/src/rapidjson-stamp/rapidjson-patch
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/crazy/3-compilerh/c1recognizer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "No configure step for 'rapidjson'"
	cd /home/crazy/3-compilerh/c1recognizer/build/externals/rapidjson/src/rapidjson-build && /usr/bin/cmake -E echo_append
	cd /home/crazy/3-compilerh/c1recognizer/build/externals/rapidjson/src/rapidjson-build && /usr/bin/cmake -E touch /home/crazy/3-compilerh/c1recognizer/build/externals/rapidjson/src/rapidjson-stamp/rapidjson-configure

externals/rapidjson/src/rapidjson-stamp/rapidjson-build: externals/rapidjson/src/rapidjson-stamp/rapidjson-configure
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/crazy/3-compilerh/c1recognizer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "No build step for 'rapidjson'"
	cd /home/crazy/3-compilerh/c1recognizer/build/externals/rapidjson/src/rapidjson-build && /usr/bin/cmake -E echo_append
	cd /home/crazy/3-compilerh/c1recognizer/build/externals/rapidjson/src/rapidjson-build && /usr/bin/cmake -E touch /home/crazy/3-compilerh/c1recognizer/build/externals/rapidjson/src/rapidjson-stamp/rapidjson-build

externals/rapidjson/src/rapidjson-stamp/rapidjson-skip-update: externals/rapidjson/src/rapidjson-stamp/rapidjson-download
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/crazy/3-compilerh/c1recognizer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "No skip-update step for 'rapidjson'"
	cd /home/crazy/3-compilerh/c1recognizer/build/externals/rapidjson/src/rapidjson && /usr/bin/cmake -E echo_append
	cd /home/crazy/3-compilerh/c1recognizer/build/externals/rapidjson/src/rapidjson && /usr/bin/cmake -E touch /home/crazy/3-compilerh/c1recognizer/build/externals/rapidjson/src/rapidjson-stamp/rapidjson-skip-update

rapidjson: CMakeFiles/rapidjson
rapidjson: CMakeFiles/rapidjson-complete
rapidjson: externals/rapidjson/src/rapidjson-stamp/rapidjson-install
rapidjson: externals/rapidjson/src/rapidjson-stamp/rapidjson-mkdir
rapidjson: externals/rapidjson/src/rapidjson-stamp/rapidjson-download
rapidjson: externals/rapidjson/src/rapidjson-stamp/rapidjson-patch
rapidjson: externals/rapidjson/src/rapidjson-stamp/rapidjson-configure
rapidjson: externals/rapidjson/src/rapidjson-stamp/rapidjson-build
rapidjson: externals/rapidjson/src/rapidjson-stamp/rapidjson-skip-update
rapidjson: CMakeFiles/rapidjson.dir/build.make

.PHONY : rapidjson

# Rule to build all files generated by this target.
CMakeFiles/rapidjson.dir/build: rapidjson

.PHONY : CMakeFiles/rapidjson.dir/build

CMakeFiles/rapidjson.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/rapidjson.dir/cmake_clean.cmake
.PHONY : CMakeFiles/rapidjson.dir/clean

CMakeFiles/rapidjson.dir/depend:
	cd /home/crazy/3-compilerh/c1recognizer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/crazy/3-compilerh/c1recognizer /home/crazy/3-compilerh/c1recognizer /home/crazy/3-compilerh/c1recognizer/build /home/crazy/3-compilerh/c1recognizer/build /home/crazy/3-compilerh/c1recognizer/build/CMakeFiles/rapidjson.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/rapidjson.dir/depend

