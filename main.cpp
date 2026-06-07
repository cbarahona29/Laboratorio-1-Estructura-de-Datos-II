#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include "json.hpp"

using json = nlohmann::json;

// ── Registro de alumno ──────────────────────────────────
struct Alumno {
    char        no_cuenta[10];  // llave primaria, fijo 10 bytes
    std::string nombre;         // longitud variable
    char        telefono[12];   // fijo 12 bytes
    int         edad;           // 4 bytes
    char        fecha[8];       // fijo 8 bytes  (AAAAMMDD)
};

// ── Entrada del índice primario ─────────────────────────
struct EntradaIndice {
    char  cuenta[10];  // llave de búsqueda
    long  offset;      // posición en bytes dentro del .dat
    int   tamanio;     // tamaño total del registro
};

// ── Leer alumno desde archivo JSON ──────────────────────
Alumno leerDesdeJSON(const std::string& rutaArchivo) {
    // Abrir el archivo
    std::ifstream archivo(rutaArchivo);
    if (!archivo.is_open()) {
        throw std::runtime_error("No se pudo abrir el archivo: " + rutaArchivo);
    }

    // Parsear el JSON
    json j;
    archivo >> j;

    // Llenar el struct
    Alumno a;

    // Campos fijos — copiamos con strncpy para respetar el tamaño exacto
    strncpy(a.no_cuenta, j["no_cuenta"].get<std::string>().c_str(), 10);
    strncpy(a.telefono,  j["telefono"].get<std::string>().c_str(),  12);
    strncpy(a.fecha,     j["fecha"].get<std::string>().c_str(),      8);

    // Campo variable — string directo
    a.nombre = j["nombre"].get<std::string>();

    // Entero
    a.edad = j["edad"].get<int>();

    return a;
}

