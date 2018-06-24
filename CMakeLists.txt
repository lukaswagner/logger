cmake_minimum_required(VERSION 3.6)

# project settings

project(logger CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# sources

set(source_dir src)
set(include_dir include)
set(generated_header_dir ${CMAKE_BINARY_DIR}/generated)

set(export_header
    ${generated_header_dir}/logger_export.hpp)

set(public_headers
	${include_dir}/logger.hpp
    ${export_header})

set(sources
	${source_dir}/logger.cpp)

set(example_sources
    ${source_dir}/example.cpp)

# lib target

include_directories(${generated_header_dir})
add_library(logger SHARED ${public_headers} ${sources})

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
