
cmake_minimum_required(VERSION 3.25)

project(mouse_trajectory)

# in-source ビルドガード
# if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
#     message(FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there. You may need to remove CMakeCache.txt. ")
# endif()

# options
option(ENABLE_DEBUGMODE_TRACK "To display verbose informations of tracking part in stdout or stderr" OFF)
option(ENABLE_DEBUGMODE_DRAW  "To display verbose informations of drawing  part in stdout or stderr" OFF)
option(ENABLE_DEBUGMODE_TIMER "To display verbose informations of timer    part in stdout or stderr" OFF)

# Dependencies
find_package(OpenCV REQUIRED)


include_directories(include)


add_executable(main src/main.cpp)
add_library(track src/track.cpp)
add_library(timer src/timer.cpp)
add_library(draw src/draw.cpp)

if(ENABLE_DEBUGMODE_TRACK)
  target_compile_definitions(track PUBLIC -DDEBUGMODE_TRACK)
endif(ENABLE_DEBUGMODE_TRACK)

if(ENABLE_DEBUGMODE_DRAW)
  target_compile_definitions(draw PUBLIC -DDEBUGMODE_DRAW)
endif(ENABLE_DEBUGMODE_DRAW)

if(ENABLE_DEBUGMODE_TIMER)
  target_compile_definitions(timer PUBLIC -DDEBUGMODE_TIMER)
endif(ENABLE_DEBUGMODE_TIMER)

target_link_libraries(draw
  ${OpenCV_LIBS}
)

target_link_libraries(main
  track
  timer
  draw
)


install(TARGETS track timer draw
  DESTINATION lib
)
