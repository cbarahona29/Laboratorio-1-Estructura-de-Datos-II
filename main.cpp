#include <iostream>
#include <fstream>
#include "CliArgs.hpp"
#include "Alumno.h"
#include "Indice.h"
#include "Registro.h"

// Rutas de los archivos de datos
const std::string ARCHIVO_DAT    = "data/alumnos.dat";
const std::string ARCHIVO_INDICE = "data/indice.dat";

int main(int argc, const char* argv[]) {
    CliArgs args(argc, argv);

    if (!args.isGood()) {
        args.printUsage();
        return 1;
    }

    // Cargar índice en memoria al iniciar
    std::vector<EntradaIndice> indice = cargarIndice(ARCHIVO_INDICE);

    // Abrir archivo de datos
    std::fstream dat(ARCHIVO_DAT, std::ios::in | std::ios::out | std::ios::binary);
    if (!dat.is_open()) {
        // Si no existe, crearlo
        std::ofstream crear(ARCHIVO_DAT, std::ios::binary);
        crear.close();
        dat.open(ARCHIVO_DAT, std::ios::in | std::ios::out | std::ios::binary);
    }

    std::string parametro = args.getArgument();

    switch (args.cliCommand().value()) {

        case CliCommand::Agregar: {
            Alumno a = leerDesdeJSON(parametro);

            // Verificar duplicado
            if (buscarEnIndice(indice, std::string(a.no_cuenta, 10)) != -1) {
                std::cout << "[!] Ya existe un registro con esa cuenta.\n";
                break;
            }

            EntradaIndice entrada = escribirRegistro(dat, a);
            insertarOrdenado(indice, entrada);
            std::cout << "[+] Alumno agregado correctamente.\n";
            break;
        }

        case CliCommand::Buscar: {
            int pos = buscarEnIndice(indice, parametro);
            if (pos == -1) {
                std::cout << "[!] No se encontró el registro.\n";
                break;
            }

            Alumno a = leerRegistro(dat, indice[pos]);
            std::cout << "No. Cuenta : " << std::string(a.no_cuenta, 10) << "\n";
            std::cout << "Nombre     : " << a.nombre                     << "\n";
            std::cout << "Teléfono   : " << std::string(a.telefono, 12)  << "\n";
            std::cout << "Edad       : " << a.edad                       << "\n";
            std::cout << "Fecha      : " << std::string(a.fecha, 8)      << "\n";
            break;
        }

        case CliCommand::Eliminar: {
            int pos = buscarEnIndice(indice, parametro);
            if (pos == -1) {
                std::cout << "[!] No se encontró el registro.\n";
                break;
            }

            // Hard delete: quitar del índice y reajustar offsets
            long offsetEliminado = indice[pos].offset;
            int  tamanioEliminado = indice[pos].tamanio;
            indice.erase(indice.begin() + pos);

            // Ajustar offsets de los registros que estaban después
            for (auto& e : indice) {
                if (e.offset > offsetEliminado)
                    e.offset -= tamanioEliminado;
            }

            // Reconstruir el .dat sin ese registro
            std::vector<Alumno> alumnos;
            for (const auto& e : indice) {
                alumnos.push_back(leerRegistro(dat, e));
            }

            dat.close();
            std::ofstream reescribir(ARCHIVO_DAT, std::ios::binary | std::ios::trunc);
            reescribir.close();
            dat.open(ARCHIVO_DAT, std::ios::in | std::ios::out | std::ios::binary);

            // Recalcular offsets desde cero
            indice.clear();
            for (const auto& a : alumnos) {
                EntradaIndice nueva = escribirRegistro(dat, a);
                insertarOrdenado(indice, nueva);
            }

            std::cout << "[+] Registro eliminado correctamente.\n";
            break;
        }

        case CliCommand::Actualizar: {
            Alumno nuevo = leerDesdeJSON(parametro);
            int pos = buscarEnIndice(indice, std::string(nuevo.no_cuenta, 10));
            if (pos == -1) {
                std::cout << "[!] No se encontró el registro a actualizar.\n";
                break;
            }

            // Eliminar el viejo del índice
            long offsetViejo   = indice[pos].offset;
            int  tamanioViejo  = indice[pos].tamanio;
            indice.erase(indice.begin() + pos);

            for (auto& e : indice) {
                if (e.offset > offsetViejo)
                    e.offset -= tamanioViejo;
            }

            // Reconstruir .dat sin el viejo
            std::vector<Alumno> alumnos;
            for (const auto& e : indice) {
                alumnos.push_back(leerRegistro(dat, e));
            }

            dat.close();
            std::ofstream reescribir(ARCHIVO_DAT, std::ios::binary | std::ios::trunc);
            reescribir.close();
            dat.open(ARCHIVO_DAT, std::ios::in | std::ios::out | std::ios::binary);

            indice.clear();
            for (const auto& a : alumnos) {
                EntradaIndice e = escribirRegistro(dat, a);
                insertarOrdenado(indice, e);
            }

            // Agregar el nuevo al final
            EntradaIndice nueva = escribirRegistro(dat, nuevo);
            insertarOrdenado(indice, nueva);

            std::cout << "[+] Registro actualizado correctamente.\n";
            break;
        }

        case CliCommand::CleanUp:
            std::cout << "[!] Este proyecto usa Hard Delete, clean-up no es necesario.\n";
            break;

        default:
            std::cout << "[!] Comando no manejado.\n";
            break;
    }

    // Persistir índice al cerrar
    guardarIndice(ARCHIVO_INDICE, indice);
    dat.close();

    return 0;
}