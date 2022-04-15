cmake_minimum_required(VERSION 3.20)

set(CMAKE_TOOLCHAIN_FILE "vcpkg/scripts/buildsystems/vcpkg.cmake")
set(VCPKG_TARGET_TRIPLET "x64-windows-static")

cmake_policy(SET CMP0091 NEW)

project(Benchmarker)

add_executable(Benchmarker
    src/main.cpp
    Annotator/src/DataSerializer.cpp Annotator/src/TableMatches.cpp src/strategy/ALiorSolutionStrategy.cpp src/strategy/AQuentinSolutionStrategy.cpp
    5A-OpenCV-Poker/src/Main.cpp 5A-OpenCV-Poker/src/Image.cpp 5A-OpenCV-Poker/src/PokerAnalyzer.cpp 5A-OpenCV-Poker/src/PokerCard.cpp 5A-OpenCV-Poker/src/PokerTable.cpp
    OpenCV_Poker/src/Main.cpp OpenCV_Poker/src/DataSetCards.cpp OpenCV_Poker/src/MatchCards.cpp OpenCV_Poker/src/Card.cpp
    src/strategy/BaseLiorSolutionStrategy.cpp src/strategy/BaseQuentinSolutionStrategy.cpp
 "include/ASolutionStrategy.hpp" )

set_property(TARGET Benchmarker PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

target_compile_options(Benchmarker PRIVATE /Zc:__cplusplus)
target_compile_features(Benchmarker PRIVATE cxx_std_20)

find_package(OpenCV CONFIG REQUIRED)

target_link_libraries(Benchmarker PRIVATE
        ${OpenCV_LIBS})

add_custom_command(TARGET Benchmarker PRE_BUILD
        COMMAND robocopy ${PROJECT_SOURCE_DIR}/resources/ ${PROJECT_BINARY_DIR}/resources /E /NS /NC /NFL /NDL /NP /NJH /NJS  || cmd /c "exit /b 0")
