cmake_minimum_required(VERSION 3.5)
project(rapidcheck_hack)

set(SOURCES test_main.cpp)

add_compile_options(-Wall -Wextra -Wdisabled-optimization --coverage)
set(CMAKE_CXX_STANDARD 14)

add_executable(test_main ${SOURCES})

add_subdirectory(x_rapidcheck)

#find_package(Boost COMPONENTS program_options)
#include_directories(${Boost_INCLUDE_DIRS})
#target_link_libraries(test_main ${Boost_LIBRARIES})

target_link_libraries(test_main --coverage)
target_link_libraries(test_main rapidcheck)

add_custom_target(coverage
    COMMAND lcov --directory . --zerocounters
    COMMAND ./test_main
    COMMAND lcov --directory . --capture --output-file coverage.info
    COMMAND genhtml coverage.info --output-directory coverage)
add_dependencies(coverage test_main)

add_custom_target(cppcheck VERBATIM
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    DEPENDS test_main
    COMMAND cppcheck --suppress=missingIncludeSystem
        "--template=[{severity}] {file}:{line} {message} ({id}) {callstack}"
        --enable=warning,performance,portability,style,information
        ${SOURCES} )

