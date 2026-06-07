#pragma once
#include <fstream>
#include "Alumno.h"
#include "Indice.h"

int calcularTamanio(const Alumno& a);
EntradaIndice escribirRegistro(std::fstream& dat, const Alumno& a);
Alumno leerRegistro(std::fstream& dat, const EntradaIndice& entrada);