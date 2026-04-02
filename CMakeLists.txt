cmake_minimum_required(VERSION 3.16)
project(obs-competition-overlay)

set(CMAKE_CXX_STANDARD 17)

# Путь к OBS Studio SDK (указываем вручную)
set(OBS_STUDIO_PATH "${CMAKE_CURRENT_SOURCE_DIR}/obs-studio")

# Найдем нужные библиотеки вручную
set(OBS_LIBRARIES 
    "${OBS_STUDIO_PATH}/lib/obs.lib"
    "${OBS_STUDIO_PATH}/lib/obs-frontend-api.lib"
)

# Создаем плагин
add_library(${PROJECT_NAME} SHARED
    src/competition_overlay.cpp
)

# Указываем пути к заголовкам
target_include_directories(${PROJECT_NAME} PRIVATE
    "${OBS_STUDIO_PATH}/include"
    "${OBS_STUDIO_PATH}/include/libobs"
)

# Связываем с библиотеками
target_link_libraries(${PROJECT_NAME} 
    "${OBS_STUDIO_PATH}/lib/obs.lib"
    "${OBS_STUDIO_PATH}/lib/obs-frontend-api.lib"
)

install(TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION ${OBS_PLUGIN_DESTINATION}
)
