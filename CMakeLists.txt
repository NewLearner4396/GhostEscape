cmake_minimum_required(VERSION 3.10.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

get_filename_component(PROJECT_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${PROJECT_NAME} VERSION 0.0.1 LANGUAGES C CXX)

if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/bin)

set(TARGET "${PROJECT_NAME}-${CMAKE_SYSTEM_NAME}-${CMAKE_BUILD_TYPE}")
add_executable(${TARGET}
    "core/Game.cpp"
    "core/Object.cpp"
    "core/ObjectAffiliate.cpp"
    "core/ObjectWorld.cpp"
    "core/AssetStore.cpp"
    "core/Actor.cpp"
    "core/Scene.cpp"
    "affiliate/Sprite.cpp"
    "affiliate/SpriteAnim.cpp"
    "affiliate/Collider.cpp"
    "raw/Status.cpp"
    "world/Effect.cpp"
    "src/main.cpp"
    "src/Player.cpp"
    "src/Enemy.cpp"
    "src/Spawner.cpp"
    "src/SceneMain.cpp"
)
target_include_directories(${TARGET} PRIVATE 
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
    "${CMAKE_CURRENT_SOURCE_DIR}/core"
    "${CMAKE_CURRENT_SOURCE_DIR}/affiliate"
    "${CMAKE_CURRENT_SOURCE_DIR}/raw"
    "${CMAKE_CURRENT_SOURCE_DIR}/world"
)


# Here add find package for external libraries
find_package(SDL3 REQUIRED) 
find_package(SDL3_ttf REQUIRED)
find_package(SDL3_image REQUIRED)
find_package(SDL3_mixer REQUIRED)
find_package(glm REQUIRED)

target_link_libraries(${TARGET}
    ${SDL3_LIBRARIES}
    SDL3_ttf::SDL3_ttf
    SDL3_image::SDL3_image
    SDL3_mixer::SDL3_mixer
    glm::glm
)

if(MSVC AND CMAKE_BUILD_TYPE STREQUAL "Release")
    target_link_options(${TARGET} PRIVATE "/subsystem:windows")
endif()