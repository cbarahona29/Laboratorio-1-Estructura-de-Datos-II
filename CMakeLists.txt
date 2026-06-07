cmake_minimum_required(VERSION 3.20)
project(Lab1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(lab1
    main.cpp
    Alumno.cpp
    Indice.cpp
    Registro.cpp
    CliArgs.cpp
)