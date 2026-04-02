cmake_minimum_required(VERSION 3.16)
project(obs-competition-overlay)

set(CMAKE_CXX_STANDARD 17)

# Найдем OBS Studio
find_package(OBS REQUIRED)

# Создаем плагин
add_library(${PROJECT_NAME} SHARED
    src/sorevnovania.cpp
)

target_link_libraries(${PROJECT_NAME} obs-lib)

install(TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION ${OBS_PLUGIN_DESTINATION}
)
