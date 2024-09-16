cmake_minimum_required(VERSION 3.20)

project(mesh_project CXX)


add_subdirectory(src)

# file(GLOB_RECURSE HEADERS "source/*.h" "include/*.h")
set(INCLUDES "include")

add_executable(main
    "main.cpp"
)

set_property(TARGET main PROPERTY CXX_STANDARD 20)
target_link_libraries(main PRIVATE mesh_dependencies)
target_include_directories(main PRIVATE ${INCLUDES})