cmake_minimum_required(VERSION 3.16)
project(obs-competition-overlay)

set(CMAKE_CXX_STANDARD 17)

# Путь к OBS Studio SDK
set(OBS_SDK_PATH "${CMAKE_CURRENT_SOURCE_DIR}/obs-studio")

add_library(${PROJECT_NAME} SHARED
    src/sorevnovania.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
    "${OBS_SDK_PATH}/include"
    "${OBS_SDK_PATH}/include/libobs"
)

# Попробуем найти библиотеки
if(EXISTS "${OBS_SDK_PATH}/lib")
    target_link_directories(${PROJECT_NAME} PRIVATE "${OBS_SDK_PATH}/lib")
endif()

install(TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION ${OBS_PLUGIN_DESTINATION}
)
