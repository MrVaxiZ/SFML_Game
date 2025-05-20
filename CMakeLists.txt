cmake_minimum_required(VERSION 3.10)
project(SFML_PlayGround)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(${CMAKE_SOURCE_DIR}/cpp)
include_directories(${CMAKE_SOURCE_DIR}/headers)
include_directories(/usr/local/include)

# Libraries
link_directories(/usr/local/lib)

file(GLOB_RECURSE SOURCES "cpp/*.cpp")

add_executable(SFML_PlayGround ${SOURCES})

target_link_libraries(SFML_PlayGround
    sfml-graphics-s
    sfml-window-s
    sfml-system-s
    sfml-audio-s
    pthread
    X11
    Xrandr
    Xcursor
    GL
    freetype
    openal
    vorbis
    vorbisenc
    vorbisfile
    FLAC
    sndfile
    udev
    Xi
)

# Copy assets
add_custom_command(
    TARGET SFML_PlayGround POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:SFML_PlayGround>/assets
)