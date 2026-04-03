cmake_minimum_required(VERSION 3.16)
project(pricoles)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# OBS Studio находится в подмодуле
set(OBS_STUDIO_DIR "${CMAKE_CURRENT_SOURCE_DIR}/obs-studio")

if(NOT EXISTS "${OBS_STUDIO_DIR}/CMakeLists.txt")
    message(FATAL_ERROR "OBS Studio submodule not found. Run: git submodule update --init --recursive")
endif()

message(STATUS "Using OBS Studio from: ${OBS_STUDIO_DIR}")

# Добавляем OBS Studio как подпроект
add_subdirectory("${OBS_STUDIO_DIR}" obs-studio EXCLUDE_FROM_ALL)

# Добавляем исходный файл плагина
add_library(${PROJECT_NAME} SHARED
    src/sorevnovania.cpp
)

# Ссылаемся на OBS
target_link_libraries(${PROJECT_NAME} PRIVATE
    obs
)

# Копируем заголовки OBS
target_include_directories(${PROJECT_NAME} PRIVATE
    "${OBS_STUDIO_DIR}/libobs"
)

# Настройки для Windows DLL
set_target_properties(${PROJECT_NAME} PROPERTIES
    PREFIX ""
    SUFFIX ".dll"
)
