file(GLOB_RECURSE HEADERS "${CMAKE_SOURCE_DIR}/include/*.h")

add_library(mesh_dependencies STATIC
    "TVertex.cpp"
    "TFace.cpp"
    "THalfEdge.cpp"
    "TMesh.cpp"
    "predicates2.cpp"
    "utils.cpp"
    ${HEADERS}
)

set_property(TARGET mesh_dependencies PROPERTY CXX_STANDARD 20)
target_include_directories(mesh_dependencies PRIVATE "${CMAKE_SOURCE_DIR}/include")