# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

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
CMAKE_COMMAND = /cygdrive/c/Users/Marco/AppData/Local/JetBrains/CLion2021.1/cygwin_cmake/bin/cmake.exe

# The command to remove a file.
RM = /cygdrive/c/Users/Marco/AppData/Local/JetBrains/CLion2021.1/cygwin_cmake/bin/cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /cygdrive/c/Users/Marco/CLionProjects/Screen_Capture_Project_official

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /cygdrive/c/Users/Marco/CLionProjects/Screen_Capture_Project_official/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Screen_Capture_Project_official.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Screen_Capture_Project_official.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Screen_Capture_Project_official.dir/flags.make

CMakeFiles/Screen_Capture_Project_official.dir/src/main.cpp.o: CMakeFiles/Screen_Capture_Project_official.dir/flags.make
CMakeFiles/Screen_Capture_Project_official.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cygdrive/c/Users/Marco/CLionProjects/Screen_Capture_Project_official/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Screen_Capture_Project_official.dir/src/main.cpp.o"
	/usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Screen_Capture_Project_official.dir/src/main.cpp.o -c /cygdrive/c/Users/Marco/CLionProjects/Screen_Capture_Project_official/src/main.cpp

CMakeFiles/Screen_Capture_Project_official.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Screen_Capture_Project_official.dir/src/main.cpp.i"
	/usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /cygdrive/c/Users/Marco/CLionProjects/Screen_Capture_Project_official/src/main.cpp > CMakeFiles/Screen_Capture_Project_official.dir/src/main.cpp.i

CMakeFiles/Screen_Capture_Project_official.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Screen_Capture_Project_official.dir/src/main.cpp.s"
	/usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /cygdrive/c/Users/Marco/CLionProjects/Screen_Capture_Project_official/src/main.cpp -o CMakeFiles/Screen_Capture_Project_official.dir/src/main.cpp.s

CMakeFiles/Screen_Capture_Project_official.dir/src/ScreenRecorder.cpp.o: CMakeFiles/Screen_Capture_Project_official.dir/flags.make
CMakeFiles/Screen_Capture_Project_official.dir/src/ScreenRecorder.cpp.o: ../src/ScreenRecorder.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cygdrive/c/Users/Marco/CLionProjects/Screen_Capture_Project_official/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Screen_Capture_Project_official.dir/src/ScreenRecorder.cpp.o"
	/usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Screen_Capture_Project_official.dir/src/ScreenRecorder.cpp.o -c /cygdrive/c/Users/Marco/CLionProjects/Screen_Capture_Project_official/src/ScreenRecorder.cpp

CMakeFiles/Screen_Capture_Project_official.dir/src/ScreenRecorder.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Screen_Capture_Project_official.dir/src/ScreenRecorder.cpp.i"
	/usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /cygdrive/c/Users/Marco/CLionProjects/Screen_Capture_Project_official/src/ScreenRecorder.cpp > CMakeFiles/Screen_Capture_Project_official.dir/src/ScreenRecorder.cpp.i

CMakeFiles/Screen_Capture_Project_official.dir/src/ScreenRecorder.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Screen_Capture_Project_official.dir/src/ScreenRecorder.cpp.s"
	/usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /cygdrive/c/Users/Marco/CLionProjects/Screen_Capture_Project_official/src/ScreenRecorder.cpp -o CMakeFiles/Screen_Capture_Project_official.dir/src/ScreenRecorder.cpp.s

# Object files for target Screen_Capture_Project_official
Screen_Capture_Project_official_OBJECTS = \
"CMakeFiles/Screen_Capture_Project_official.dir/src/main.cpp.o" \
"CMakeFiles/Screen_Capture_Project_official.dir/src/ScreenRecorder.cpp.o"

# External object files for target Screen_Capture_Project_official
Screen_Capture_Project_official_EXTERNAL_OBJECTS =

Screen_Capture_Project_official.exe: CMakeFiles/Screen_Capture_Project_official.dir/src/main.cpp.o
Screen_Capture_Project_official.exe: CMakeFiles/Screen_Capture_Project_official.dir/src/ScreenRecorder.cpp.o
Screen_Capture_Project_official.exe: CMakeFiles/Screen_Capture_Project_official.dir/build.make
Screen_Capture_Project_official.exe: ../libav-11.12/lib/libavcodec.dll.a
Screen_Capture_Project_official.exe: ../libav-11.12/lib/libavformat.dll.a
Screen_Capture_Project_official.exe: ../libav-11.12/lib/libswscale.dll.a
Screen_Capture_Project_official.exe: ../libav-11.12/lib/libavdevice.dll.a
Screen_Capture_Project_official.exe: ../libav-11.12/lib/libavutil.dll.a
Screen_Capture_Project_official.exe: ../libav-11.12/lib/libswscale.dll.a
Screen_Capture_Project_official.exe: ../libav-11.12/lib/libavdevice.dll.a
Screen_Capture_Project_official.exe: ../libav-11.12/lib/libavutil.dll.a
Screen_Capture_Project_official.exe: CMakeFiles/Screen_Capture_Project_official.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/cygdrive/c/Users/Marco/CLionProjects/Screen_Capture_Project_official/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable Screen_Capture_Project_official.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Screen_Capture_Project_official.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Screen_Capture_Project_official.dir/build: Screen_Capture_Project_official.exe

.PHONY : CMakeFiles/Screen_Capture_Project_official.dir/build

CMakeFiles/Screen_Capture_Project_official.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Screen_Capture_Project_official.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Screen_Capture_Project_official.dir/clean

CMakeFiles/Screen_Capture_Project_official.dir/depend:
	cd /cygdrive/c/Users/Marco/CLionProjects/Screen_Capture_Project_official/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /cygdrive/c/Users/Marco/CLionProjects/Screen_Capture_Project_official /cygdrive/c/Users/Marco/CLionProjects/Screen_Capture_Project_official /cygdrive/c/Users/Marco/CLionProjects/Screen_Capture_Project_official/cmake-build-debug /cygdrive/c/Users/Marco/CLionProjects/Screen_Capture_Project_official/cmake-build-debug /cygdrive/c/Users/Marco/CLionProjects/Screen_Capture_Project_official/cmake-build-debug/CMakeFiles/Screen_Capture_Project_official.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Screen_Capture_Project_official.dir/depend

