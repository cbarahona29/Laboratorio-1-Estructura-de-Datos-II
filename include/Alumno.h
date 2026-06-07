#pragma once
#include <string>
#include "json.hpp"

struct Alumno {
    char        no_cuenta[10];
    std::string nombre;
    char        telefono[12];
    int         edad;
    char        fecha[8];
};

Alumno leerDesdeJSON(const std::string& rutaArchivo);