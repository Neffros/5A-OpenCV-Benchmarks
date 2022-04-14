cmake_minimum_required(VERSION 3.20)

set(CMAKE_TOOLCHAIN_FILE "vcpkg/scripts/buildsystems/vcpkg.cmake")
set(VCPKG_TARGET_TRIPLET "x64-windows-static")

cmake_policy(SET CMP0091 NEW)

project(Benchmarking)

add_executable(Benchmarking src/main.cpp)

set_property(TARGET Benchmarking PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

target_compile_options(Benchmarking PRIVATE /Zc:__cplusplus)
target_compile_features(Benchmarking PRIVATE cxx_std_20)

find_package(OpenCV CONFIG REQUIRED)

target_link_libraries(Benchmarking PRIVATE
        ${OpenCV_LIBS})

add_custom_command(TARGET Benchmarking PRE_BUILD
        COMMAND robocopy ${PROJECT_SOURCE_DIR}/resources/ ${PROJECT_BINARY_DIR}/resources /E /NS /NC /NFL /NDL /NP /NJH /NJS  || cmd /c "exit /b 0")
