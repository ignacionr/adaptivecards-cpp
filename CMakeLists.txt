cmake_minimum_required(VERSION 3.30)

project(adaptivecards-cpp LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

FetchContent_Declare(
  glaze
  GIT_REPOSITORY https://github.com/stephenberry/glaze.git
  GIT_TAG main
  GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(glaze)

# Add the library
add_library(adaptivecards-cpp
  src/ac.cpp
)
target_link_libraries(adaptivecards-cpp PRIVATE glaze::glaze)
target_include_directories(adaptivecards-cpp PUBLIC include)

# Add the executable
add_executable(ac-test 
    src/test.cpp
    src/ac.cpp
)
target_link_libraries(ac-test PRIVATE glaze::glaze adaptivecards-cpp)
target_include_directories(ac-test PRIVATE include)
