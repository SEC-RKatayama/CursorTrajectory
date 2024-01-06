
cmake_minimum_required(VERSION 3.25)

project(mouse_trajectory
    # LANGUAGES C++
)

# in-source ビルドガード
# if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
#     message(FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there. You may need to remove CMakeCache.txt. ")
# endif()


# Dependencies
# set(THREADS_PREFER_PTHREAD_FLAG ON)
# find_package(Threads REQUIRED)


include_directories(include)


add_executable(main src/main.cpp)
add_library(track src/track.cpp)
add_library(timer src/timer.cpp)
# add_library(draw draw.cpp)

target_link_libraries(main
  track
  timer
  # draw
)

# target_link_libraries(main
#     Threads::Threads
# )

install(TARGETS main
  DESTINATION lib/${PROJECT_NAME}
)
