#include "Indice.h"
#include <fstream>

void insertarOrdenado(std::vector<EntradaIndice>& indice, const EntradaIndice& nueva) {
    auto it = indice.begin();
    while (it != indice.end() && strncmp(it->cuenta, nueva.cuenta, 10) < 0)
        ++it;
    indice.insert(it, nueva);
}

int buscarEnIndice(const std::vector<EntradaIndice>& indice, const std::string& cuenta) {
    for (int i = 0; i < (int)indice.size(); i++) {
        if (strncmp(indice[i].cuenta, cuenta.c_str(), 10) == 0)
            return i;
    }
    return -1;
}

std::vector<EntradaIndice> cargarIndice(const std::string& ruta) {
    std::vector<EntradaIndice> indice;
    std::ifstream archivo(ruta, std::ios::binary);
    if (!archivo.is_open()) return indice;

    EntradaIndice entrada;
    while (archivo.read(reinterpret_cast<char*>(&entrada), sizeof(EntradaIndice)))
        indice.push_back(entrada);

    return indice;
}

void guardarIndice(const std::string& ruta, const std::vector<EntradaIndice>& indice) {
    std::ofstream archivo(ruta, std::ios::binary | std::ios::trunc);
    for (const auto& entrada : indice)
        archivo.write(reinterpret_cast<const char*>(&entrada), sizeof(EntradaIndice));
}