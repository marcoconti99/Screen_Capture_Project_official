# cmake_minimum_required(VERSION <specify CMake version here>)
project(Screen_Capture_Project_official)
cmake_minimum_required(VERSION 3.19)
set(CMAKE_LEGACY_CYGWIN_WIN32 0)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_PREFIX_PATH libav-11.12/lib)
include_directories(libav-11.12/include)

add_executable(Screen_Capture_Project_official
        src/main.cpp
        src/ScreenRecorder.cpp
        src/ScreenRecorder.h)

find_library(AVCODEC_LIBRARY avcodec)
find_library(AVFORMAT_LIBRARY avformat)
find_library(SWSCALE_LIBRARY swscale)
find_library(AVDEVICE_LIBRARY avdevice)
find_library(AVUTIL_LIBRARY avutil)
find_library(SWRESAMPLE_LIBRARY swresample)
find_library(SWSCALE_LIBRARY swscale)

target_link_libraries(Screen_Capture_Project_official PRIVATE ${AVCODEC_LIBRARY})
target_link_libraries(Screen_Capture_Project_official PRIVATE ${AVFORMAT_LIBRARY})
target_link_libraries(Screen_Capture_Project_official PRIVATE ${SWSCALE_LIBRARY})
target_link_libraries(Screen_Capture_Project_official PRIVATE ${AVDEVICE_LIBRARY})
target_link_libraries(Screen_Capture_Project_official PRIVATE ${AVUTIL_LIBRARY})
#target_link_libraries(Screen_Capture_Project_official PRIVATE ${SWRESAMPLE_LIBRARY})
target_link_libraries(Screen_Capture_Project_official PRIVATE ${SWSCALE_LIBRARY})