cmake_minimum_required(VERSION 3.14)
project(my_project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

execute_process(
    COMMAND python3-config --extension-suffix
    OUTPUT_VARIABLE PY_MOD_SUFFIX
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

include(FetchContent)
FetchContent_Declare(
    pybind11
    GIT_REPOSITORY https://github.com/pybind/pybind11.git
    GIT_TAG        v2.11.1  # 指定 pybind11 版本
)
FetchContent_MakeAvailable(pybind11)

set(MODULE_NAME test_module)
add_library(${MODULE_NAME} MODULE src/module.cpp src/accumulator.h)
target_link_libraries(${MODULE_NAME} PRIVATE pybind11::module)
set_target_properties(${MODULE_NAME} PROPERTIES PREFIX "" SUFFIX ${PY_MOD_SUFFIX})

add_executable(main src/main.cpp src/accumulator.h)