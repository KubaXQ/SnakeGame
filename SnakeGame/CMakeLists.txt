find_package(SDL3 REQUIRED)
add_executable (SnakeGame "SnakeGame.cpp" "SnakeGame.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET SnakeGame PROPERTY CXX_STANDARD 20)
endif()


target_link_libraries(SnakeGame PRIVATE SDL3::SDL3)
