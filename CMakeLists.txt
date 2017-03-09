project(cpp-pybind11)
cmake_minimum_required(VERSION 3.0)

add_subdirectory(pybind11)

add_executable(main
    main.cpp
    util.cpp
    module.cpp
)
target_include_directories(main PRIVATE
    ${PYTHON_INCLUDE_DIRS}
    ${PYBIND11_INCLUDE_DIR}
)
target_link_libraries(main ${PYTHON_LIBRARIES})

file(COPY rtss.py DESTINATION ${CMAKE_BINARY_DIR})
