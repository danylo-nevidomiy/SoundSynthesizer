cmake_minimum_required(VERSION 3.5)

project(SoundSynthesizer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_SOURCES
    main.cpp
    wavsynthesizer.h
    wavsynthesizer.cpp)

add_executable(SoundSynthesizer
    ${PROJECT_SOURCES}
)
