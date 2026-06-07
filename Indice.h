#pragma once
#include <vector>
#include <string>
#include <cstring>

struct EntradaIndice {
    char  cuenta[10];
    long  offset;
    int   tamanio;
};

void insertarOrdenado(std::vector<EntradaIndice>& indice, const EntradaIndice& nueva);
int  buscarEnIndice(const std::vector<EntradaIndice>& indice, const std::string& cuenta);
std::vector<EntradaIndice> cargarIndice  (const std::string& ruta);
void guardarIndice(const std::string& ruta, const std::vector<EntradaIndice>& indice);