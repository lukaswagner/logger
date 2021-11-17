cmake_minimum_required(VERSION 3.9)

# project settings

project(logger CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# dependencies

include(${CMAKE_SOURCE_DIR}/dependencies/DependencyStructure.cmake)
setup_dependency_structure(${CMAKE_SOURCE_DIR}/dependencies)

# sources

set(source_dir src)
set(include_dir include)
set(generated_header_dir ${CMAKE_BINARY_DIR}/generated)
set(test_dir test)

set(export_header
    ${generated_header_dir}/logger_export.hpp)

set(public_headers
    ${include_dir}/level.hpp
    ${include_dir}/line.hpp
    ${include_dir}/logger.hpp
    ${include_dir}/macros.hpp
    ${include_dir}/output.hpp
    ${export_header})

set(private_headers
    ${include_dir}/globals.hpp)

set(sources
    ${source_dir}/globals.cpp
    ${source_dir}/line.cpp
    ${source_dir}/logger.cpp
    ${source_dir}/output.cpp)

set(example_sources
    ${source_dir}/example.cpp)

set(test_headers
    ${test_dir}/fixtures.hpp)

set(test_sources
    ${test_dir}/datatypes.cpp
    ${test_dir}/enable_disable.cpp
    ${test_dir}/file.cpp
    ${test_dir}/fixtures.cpp
    ${test_dir}/macros.cpp
    ${test_dir}/output.cpp
    ${test_dir}/parameters.cpp)

# lib target

include_directories(${generated_header_dir})
include_directories(${include_dir})
add_library(logger STATIC ${public_headers} ${private_headers} ${sources})

include(GenerateExportHeader)
generate_export_header(logger
    BASE_NAME logger
    EXPORT_MACRO_NAME LOGGER_EXPORT
    EXPORT_FILE_NAME ${export_header}
    STATIC_DEFINE LOGGER_BUILT_AS_STATIC)

# install settings

set_target_properties(logger PROPERTIES PUBLIC_HEADER "${public_headers}")

include(GNUInstallDirs)
install(TARGETS logger
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# example executable

option(BUILD_EXAMPLE "Build example executable." OFF)

if (${BUILD_EXAMPLE})
	add_executable(example ${example_sources})
    target_link_libraries(example logger)
    set(VS_STARTUP_PROJECT example)
endif()

# tests

option(BUILD_TESTS "Build tests." OFF)

if(${BUILD_TESTS})
    find_package(GTest)
    include_directories(${GTEST_ROOT}/include)
    add_executable(tests ${test_headers} ${test_sources})
    target_link_libraries(tests ${GTEST_BOTH_LIBRARIES} Threads::Threads logger)
endif()

# documentation

option(BUILD_DOCS "Generate documentation." OFF)

if(${BUILD_DOCS})
    find_package(Doxygen)
    set(DOXYGEN_MACRO_EXPANSION YES)
    set(DOXYGEN_EXPAND_ONLY_PREDEF YES)
    set(DOXYGEN_PREDEFINED "LOGGER_EXPORT=")
    set(DOXYGEN_USE_MDFILE_AS_MAINPAGE "README.md")
    doxygen_add_docs(docs ${public_headers} ${CMAKE_SOURCE_DIR}/README.md)
endif()

# resharper style settings for VS

if(EXISTS ${CMAKE_SOURCE_DIR}/dependencies/cpp-style-settings/CMakeLists.txt)
    add_subdirectory(dependencies/cpp-style-settings EXCLUDE_FROM_ALL)
endif()
