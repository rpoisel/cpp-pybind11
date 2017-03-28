project(cpp-pybind11)
cmake_minimum_required(VERSION 3.0)

include(CTest)

if (RTS_TARGET_PLATFORM STREQUAL "linux-x86")
    set(PYTHONLIBS_FOUND TRUE)
    set(PYTHON_INCLUDE_DIRS /usr/include/python3.5m)
    set(PYTHON_LIBRARIES /usr/lib/i386-linux-gnu/libpython3.5m.so)
endif ()

add_subdirectory(pybind11)

add_library(Unity STATIC
    Unity/src/unity.c
)

target_include_directories(Unity PUBLIC
    Unity/src
)

add_library(PythonGlue STATIC
    util.cpp
    module.cpp
)

target_include_directories(PythonGlue PUBLIC
    ${PYTHON_INCLUDE_DIRS}
    ${PYBIND11_INCLUDE_DIR}
)

target_link_libraries(PythonGlue PUBLIC
    ${PYTHON_LIBRARIES}
)

add_executable(SampleApp
    sample.cpp
)

target_link_libraries(SampleApp
    PythonGlue
)

add_executable(CyclicApp
    cyclic.cpp
)

target_link_libraries(CyclicApp
    PythonGlue
    Unity
)

add_test(NAME SampleTest COMMAND $<TARGET_FILE:SampleApp> ${CMAKE_CURRENT_LIST_DIR}/rtss.py)
add_test(NAME CyclicTest COMMAND $<TARGET_FILE:CyclicApp> ${CMAKE_CURRENT_LIST_DIR}/rtss.py)