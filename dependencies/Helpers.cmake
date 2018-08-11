macro(prepare_dir dir)
    if(NOT EXISTS ${dir})
        file(MAKE_DIRECTORY ${dir})
    endif()
endmacro()

macro(clone dependency_name repo branch)
    message(STATUS "Cloning ${repo} to ${dir}")
    execute_process(COMMAND git clone --depth 1 --branch ${branch} "${repo}" "${${dependency_name}_source_dir}")
endmacro()

macro(set_compiler_specific_flags)
    # skip if already defined (if multiple dependencies are set up)
    if(NOT compiler_specific_flags)
        # check if VS is used - MSVC isn't defined since this project has language NONE
        string(REGEX MATCH "^Visual Studio.*" using_vs ${CMAKE_GENERATOR})
        if(using_vs)
            set(compiler_specific_flags /m /verbosity:minimal)
        endif()
    endif()
endmacro()

# pass CMake options as additional args
macro(build dependency_name)
    message(STATUS "Building ${dependency_name}")
    message(STATUS "  Source dir: ${${dependency_name}_source_dir}")
    message(STATUS "  Build dir: ${${dependency_name}_build_dir}")
    message(STATUS "  Install dir: ${${dependency_name}_install_dir}")
    prepare_dir(${${dependency_name}_build_dir})
    # see https://stackoverflow.com/a/24470998 for further explanaitions on single/multi-configuration generators
    # run CMake configuration - build type passed here is only used by single-conf generators
    execute_process(COMMAND ${CMAKE_COMMAND} ${ARGN} -DCMAKE_BUILD_TYPE=${SINGLE_CONFIGURATION_BUILD_TYPE} -DCMAKE_INSTALL_PREFIX=${${dependency_name}_install_dir} -G "${CMAKE_GENERATOR}" ${${dependency_name}_source_dir} WORKING_DIRECTORY ${${dependency_name}_build_dir})
    # build and install - build type passed here is only used by multi-conf generators
    # set some flags to optimize based on compiler
    set_compiler_specific_flags()
    # this var is only defined when using multi-configuration  generators
    if(NOT CMAKE_CONFIGURATION_TYPES)
        execute_process(COMMAND ${CMAKE_COMMAND} --build ${${dependency_name}_build_dir} --target install -- ${compiler_specific_flags})
    else()
        foreach(build_type IN ITEMS ${MULTI_CONFIGURATION_BUILD_TYPES})
            execute_process(COMMAND ${CMAKE_COMMAND} --build ${${dependency_name}_build_dir} --target install --config "${build_type}" -- ${compiler_specific_flags})
        endforeach()
    endif()
endmacro()
