cmake_minimum_required(VERSION 3.16)
project(pricoles)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Путь к OBS Studio SDK
set(OBS_SDK_PATH "${CMAKE_CURRENT_SOURCE_DIR}/obs-studio")

add_library(${PROJECT_NAME} SHARED
    src/sorevnovania.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
    "${OBS_SDK_PATH}/include"
    "${OBS_SDK_PATH}/include/libobs"
    "${OBS_SDK_PATH}/include/libobs/util"
    "${OBS_SDK_PATH}/include/libobs/obs-frontend-api"
)

target_link_directories(${PROJECT_NAME} PRIVATE
    "${OBS_SDK_PATH}/lib"
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    obs
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    PREFIX ""
    SUFFIX ".dll"
)

install(TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION ${OBS_PLUGIN_DESTINATION}
)