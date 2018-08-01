cmake_minimum_required(VERSION 3.0)
project(dependencies NONE)

option(CLEANUP_AFTER_INSTALL "Remove sources and built files after installing." OFF)

# see https://stackoverflow.com/a/24470998 for further explanaitions on single/multi-configuration generators
set(SINGLE_CONFIGURATION_BUILD_TYPE Release CACHE STRING "The configuration to build when using a single-conf generator.")
set(MULTI_CONFIGURATION_BUILD_TYPES Debug;Release CACHE STRING "The configurations to build when using a multi-conf generator.")

# set up dependency dir vars

include(${CMAKE_SOURCE_DIR}/DependencyStructure.cmake)
setup_dependency_structure(${CMAKE_SOURCE_DIR})

# load helper macros

include(${CMAKE_SOURCE_DIR}/Helpers.cmake)
prepare_dir(${dependency_dir})
message(STATUS "Using dependency_dir: ${dependency_dir}")

# clone and build googletest

if(EXISTS ${GTEST_ROOT})
    message(STATUS "Found GTEST_ROOT: ${GTEST_ROOT}")
else()
    prepare_dir(${googletest_base_dir})
    clone(googletest https://github.com/google/googletest.git/ master)
    build(googletest -DBUILD_GTEST=ON -DBUILD_GMOCK=OFF -DINSTALL_GTEST=ON -Dgtest_force_shared_crt=ON)
endif()

# cleanup

if(${CLEANUP_AFTER_INSTALL})
    message(STATUS "Removing sources and build output.")
    file(GLOB build_dirs ${dependency_dir}/*/build)
    file(REMOVE_RECURSE ${source_dir} ${build_dirs})
endif()
