macro(setup_dependency_dirs dependency_name)
    set(${dependency_name}_base_dir ${dependency_dir}/${dependency_name})
    set(${dependency_name}_source_dir ${source_dir}/${dependency_name})
    set(${dependency_name}_build_dir ${${dependency_name}_base_dir}/${build_dir_suffix})
    set(${dependency_name}_install_dir ${${dependency_name}_base_dir}/${install_dir_suffix})
endmacro()

macro(setup_dependency_structure dependency_base_dir)

    # global settings

    set(dependency_dir ${dependency_base_dir}/${CMAKE_GENERATOR})
    set(source_dir ${dependency_base_dir}/sources)
    set(build_dir_suffix build)
    set(install_dir_suffix install)

    # googletest

    setup_dependency_dirs(googletest)
    set(GTEST_ROOT ${googletest_install_dir})

endmacro()
