cmake_minimum_required(VERSION 3.18)

project(figcone_xml_deps)
include(seal_lake.cmake)

SealLake_v040_Bundle(
        NAME figcone_tree
        URL https://github.com/kamchatka-volcano/figcone_tree/releases/download/v2.2.0/figcone_tree-v2.2.0.zip
        SKIP_LOAD
        DESTINATION deps/figcone_tree
)

SealLake_v040_Bundle(
        NAME figcone_rapidxml
        SKIP_LOAD
        WILDCARDS *.hpp
        DESTINATION deps/figcone_rapidxml/
        GIT_REPOSITORY https://github.com/dwd/rapidxml.git
        GIT_TAG v1.0.0
        TEXT_REPLACEMENTS
        "namespace rapidxml" "namespace figcone::xml::rapidxml"
)