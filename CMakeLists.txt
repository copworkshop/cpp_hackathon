cmake_minimum_required(VERSION 3.2)

project(PlantWorld
    LANGUAGES
        C CXX
)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}" "${CMAKE_SOURCE_DIR}/cmake")
# To get it work with conan cmake_find_package generator
set(CMAKE_FIND_PACKAGE_PREFER_CONFIG ON)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_BINARY_DIR})
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${CMAKE_BINARY_DIR})
 

option(ENABLE_TESTS "Enable tests" ON)
option(ENABLE_STATIC_ANALYSIS "Enables static analysis. Requires CPPCheck" OFF)
option(ENABLE_CODE_COVERAGE "Enables code coverage." ON)
option(CI_CD_COVERAGE "Checker for CI" OFF)

if(CMAKE_VERSION VERSION_LESS "3.1")
    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++14")
    endif()
else()
    set(CMAKE_CXX_STANDARD 14)
endif()

if(ENABLE_STATIC_ANALYSIS)
    set(CMAKE_CXX_CPPCHECK "cppcheck")
endif()

if(ENABLE_CODE_COVERAGE)
    if(CMAKE_COMPILER_IS_GNUCXX)
        include(CodeCoverage)
        append_coverage_compiler_flags()
        set(COVERAGE_EXCLUDES "PWTests/*") 
    endif()
endif()

add_subdirectory(PWCommon)
add_subdirectory(PWServer)
add_subdirectory(PWGRPCService)

if(ENABLE_TESTS)
    enable_testing()
    add_subdirectory(PWTests)
endif()
