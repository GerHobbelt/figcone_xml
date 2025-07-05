cmake_minimum_required(VERSION 3.18)

project(figcone_xml VERSION 1.3.0 DESCRIPTION "rapidxml parser adapter for figcone library")
include(seal_lake.cmake)

SealLake_v040_IsInstallEnabled(INSTALL_FIGCONE_TREE)
find_package(figcone_tree 2.2.0 QUIET)
if (NOT TARGET figcone::figcone_tree)
    add_subdirectory(deps/figcone_tree)
endif()

SealLake_v040_ObjectLibrary(
        NAMESPACE figcone
        SOURCES
            src/paramparser.cpp
            src/parser.cpp
            src/utils.cpp
        COMPILE_FEATURES cxx_std_17
        INCLUDES
            ${CMAKE_CURRENT_LIST_DIR}/deps/figcone_rapidxml
        INTERFACE_LIBRARIES
            figcone::figcone_tree
        DEPENDENCIES
            figcone_tree 2.2.0
)
