#include "Registro.h"
#include <cstring>
#include <cstdint>

int calcularTamanio(const Alumno& a) {
    return sizeof(a.no_cuenta)     
         + sizeof(a.telefono)       
         + sizeof(a.edad)            
         + sizeof(a.fecha)           
         + sizeof(uint16_t)         
         + a.nombre.size();          
}

EntradaIndice escribirRegistro(std::fstream& dat, const Alumno& a) {
    dat.seekp(0, std::ios::end);
    long offset = dat.tellp();

    dat.write(a.no_cuenta, sizeof(a.no_cuenta));
    dat.write(a.telefono,  sizeof(a.telefono));
    dat.write(reinterpret_cast<const char*>(&a.edad), sizeof(a.edad));
    dat.write(a.fecha,     sizeof(a.fecha));

    uint16_t longNombre = static_cast<uint16_t>(a.nombre.size());
    dat.write(reinterpret_cast<const char*>(&longNombre), sizeof(longNombre));
    dat.write(a.nombre.c_str(), longNombre);

    EntradaIndice entrada;
    strncpy(entrada.cuenta, a.no_cuenta, 10);
    entrada.offset  = offset;
    entrada.tamanio = calcularTamanio(a);

    return entrada;
}

Alumno leerRegistro(std::fstream& dat, const EntradaIndice& entrada) {
    dat.seekg(entrada.offset, std::ios::beg);

    Alumno a;

    dat.read(a.no_cuenta, sizeof(a.no_cuenta));
    dat.read(a.telefono,  sizeof(a.telefono));
    dat.read(reinterpret_cast<char*>(&a.edad), sizeof(a.edad));
    dat.read(a.fecha,     sizeof(a.fecha));

    uint16_t longNombre = 0;
    dat.read(reinterpret_cast<char*>(&longNombre), sizeof(longNombre));
    a.nombre.resize(longNombre);
    dat.read(&a.nombre[0], longNombre);

    return a;
} 