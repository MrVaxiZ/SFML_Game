#!/bin/bash

echo "[1/5] Czyszczenie śmieci z Windowsa..."

# Usuwamy pliki Visual Studio i binaria
rm -rf SFML_PlayGround/*.vcxproj*
rm -rf SFML_PlayGround/*.sln
rm -rf SFML_PlayGround/*.aps
rm -rf SFML_PlayGround/x64
rm -rf x64
rm -rf build
rm -rf SFML_PlayGround/Logs

echo "[2/5] Tworzenie nowej struktury src/ i include/..."
mkdir -p src include

# Przenosimy pliki .cpp do src/
mv SFML_PlayGround/*.cpp src/ 2>/dev/null

# Przenosimy pliki .h do include/
mv SFML_PlayGround/*.h include/ 2>/dev/null

echo "[3/5] Czyszczenie starych CMakeLists.txt..."
rm -f CMakeLists.txt

echo "[4/5] Tworzenie nowego CMakeLists.txt..."
cat <<EOF > CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(SFML_PlayGround)

set(CMAKE_CXX_STANDARD 17)
set(SFML_STATIC_LIBRARIES TRUE)

# Include path
include_directories(include)

# Wyszukiwanie źródeł automatycznie
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Pakiet SFML
find_package(SFML 3 REQUIRED COMPONENTS graphics window system audio)

# Budowanie
add_executable(SFML_PlayGround \${SOURCES})

# Linkowanie SFML
target_link_libraries(SFML_PlayGround PRIVATE sfml-graphics sfml-window sfml-system sfml-audio)
EOF

echo "[5/5] Gotowe! Możesz teraz budować projekt:"
echo "  cmake -B build && cmake --build build -j\$(nproc)"
