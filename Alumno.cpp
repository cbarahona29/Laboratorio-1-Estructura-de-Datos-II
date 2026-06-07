#include "Alumno.h"
#include <fstream>
#include <stdexcept>
#include <cstring>

using json = nlohmann::json;

Alumno leerDesdeJSON(const std::string& rutaArchivo) {
    std::ifstream archivo(rutaArchivo);
    if (!archivo.is_open())
        throw std::runtime_error("No se pudo abrir: " + rutaArchivo);

    json j;
    archivo >> j;

    Alumno a;
    strncpy(a.no_cuenta, j["no_cuenta"].get<std::string>().c_str(), 10);
    strncpy(a.telefono,  j["telefono"].get<std::string>().c_str(),  12);
    strncpy(a.fecha,     j["fecha"].get<std::string>().c_str(),      8);
    a.nombre = j["nombre"].get<std::string>();
    a.edad   = j["edad"].get<int>();

    return a;
}