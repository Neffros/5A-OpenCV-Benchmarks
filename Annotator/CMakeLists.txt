cmake_minimum_required(VERSION 3.20)

set(CMAKE_TOOLCHAIN_FILE "vcpkg/scripts/buildsystems/vcpkg.cmake")
set(VCPKG_TARGET_TRIPLET "x64-windows-static")

cmake_policy(SET CMP0091 NEW)

project(Annotator)

add_executable(Annotator src/main.cpp src/DataSerializer.cpp src/DataSerializer.h src/TableMatches.h src/TableMatches.cpp)

set_property(TARGET Annotator PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

target_compile_options(Annotator PRIVATE /Zc:__cplusplus)
target_compile_features(Annotator PRIVATE cxx_std_20)

find_package(OpenCV CONFIG REQUIRED)

target_link_libraries(Annotator PRIVATE
        ${OpenCV_LIBS})

add_custom_command(TARGET Annotator PRE_BUILD
        COMMAND robocopy ${PROJECT_SOURCE_DIR}/resources/ ${PROJECT_BINARY_DIR}/resources /E /NS /NC /NFL /NDL /NP /NJH /NJS  || cmd /c "exit /b 0")
