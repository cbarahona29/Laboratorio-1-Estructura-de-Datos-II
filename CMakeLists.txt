cmake_minimum_required(VERSION 3.20)
project(Lab1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(lab1
    src/main.cpp
    src/Alumno.cpp
    src/Indice.cpp
    src/Registro.cpp
    src/CliArgs.cpp
)