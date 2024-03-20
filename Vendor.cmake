include(FetchContent)

# Raylib defines
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE)

# Enet defines
set(ENET_STATIC    ON  CACHE BOOL "" FORCE)
set(ENET_SHARED    OFF CACHE BOOL "" FORCE)
set(ENET_TEST      OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG master
    GIT_PROGRESS TRUE
)

FetchContent_Declare(
    raygui
    GIT_REPOSITORY https://github.com/raysan5/raygui.git
    GIT_TAG master
    GIT_PROGRESS TRUE
)

FetchContent_Declare(
    enet
    GIT_REPOSITORY https://github.com/zpl-c/enet.git
    GIT_TAG master
    GIT_PROGRESS TRUE
)

FetchContent_MakeAvailable(raylib raygui enet)

target_link_libraries(${PROJECT_NAME} PRIVATE raylib enet_static -lm)
target_include_directories(${PROJECT_NAME} PRIVATE
    ${raygui_SOURCE_DIR}/src/
)
