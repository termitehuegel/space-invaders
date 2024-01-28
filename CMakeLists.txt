cmake_minimum_required(VERSION 3.16)
project(space-invaders VERSION 0.1.0.0 HOMEPAGE_URL https://github.com/termitehuegel/space-invaders LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(space-invaders src/main.cpp
        src/hud.cpp
        src/header/hud.h
        src/player.cpp
        src/header/player.h
        src/projectile.cpp
        src/header/projectile.h
        src/enemy.cpp
        src/header/enemy.h
        src/enemyController.cpp
        src/header/enemyController.h
        src/header/gameState.h
        src/header/assetManager.h
        src/assetManager.cpp
        src/header/game.h
        src/game.cpp
        src/header/menu.h
        src/menu.cpp
)
target_link_libraries(space-invaders PRIVATE sfml-graphics)
target_compile_features(space-invaders PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
            TARGET space-invaders
            COMMENT "Copy OpenAL DLL"
            PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:space-invaders>
            POST_BUILD COMMAND "${CMAKE_COMMAND}" -E copy_directory "${CMAKE_SOURCE_DIR}/src/assets" $<TARGET_FILE_DIR:space-invaders>/assets
            VERBATIM)
endif()

install(TARGETS space-invaders)