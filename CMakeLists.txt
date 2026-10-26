cmake_minimum_required(VERSION 3.10)
project(tnap_rw)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.1.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(game src/main.cpp src/game.cpp src/texture_manager.cpp src/texture_changer.cpp src/render_object.cpp)
target_include_directories(game PUBLIC include/)
target_compile_features(game PRIVATE cxx_std_23)
target_link_libraries(game PRIVATE SFML::Graphics)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT main)
