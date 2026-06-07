#include <iostream>
#include <fstream>
#include "CliArgs.hpp"
#include "Alumno.h"
#include "Indice.h"
#include "Registro.h"

const std::string ARCHIVO_DAT    = "alumnos.dat";
const std::string ARCHIVO_INDICE = "indice.dat";

int main(int argc, const char* argv[]) {
    CliArgs args(argc, argv);

    if (!args.isGood()) {
        args.printUsage();
        return 1;
    }

    std::vector<EntradaIndice> indice = cargarIndice(ARCHIVO_INDICE);

    std::fstream dat(ARCHIVO_DAT, std::ios::in | std::ios::out | std::ios::binary);
    if (!dat.is_open()) {
        std::ofstream crear(ARCHIVO_DAT, std::ios::binary);
        crear.close();
        dat.open(ARCHIVO_DAT, std::ios::in | std::ios::out | std::ios::binary);
    }

    std::string parametro = args.getArgument();

    switch (args.cliCommand().value()) {

        case CliCommand::Agregar: {
            Alumno a = leerDesdeJSON(parametro);

            if (buscarEnIndice(indice, std::string(a.no_cuenta, 10)) != -1) {
                std::cout << " Ya existe un registro con esa cuenta.\n";
                break;
            }

            EntradaIndice entrada = escribirRegistro(dat, a);
            insertarOrdenado(indice, entrada);
            std::cout << "Alumno agregado correctamente.\n";
            break;
        }

        case CliCommand::Buscar: {
            int pos = buscarEnIndice(indice, parametro);
            if (pos == -1) {
                std::cout << "No se encontro el registro.\n";
                break;
            }

            Alumno a = leerRegistro(dat, indice[pos]);
            std::cout << "No. Cuenta : " << std::string(a.no_cuenta, 10) << "\n";
            std::cout << "Nombre     : " << a.nombre                     << "\n";
            std::cout << "Telefono   : " << std::string(a.telefono, 12)  << "\n";
            std::cout << "Edad       : " << a.edad                       << "\n";
            std::cout << "Fecha      : " << std::string(a.fecha, 8)      << "\n";
            break;
        }

        case CliCommand::Eliminar: {
            int pos = buscarEnIndice(indice, parametro);
            if (pos == -1) {
                std::cout << " No se encontro el registro.\n";
                break;
            }

            long offsetEliminado = indice[pos].offset;
            int  tamanioEliminado = indice[pos].tamanio;
            indice.erase(indice.begin() + pos);

            for (auto& e : indice) {
                if (e.offset > offsetEliminado)
                    e.offset -= tamanioEliminado;
            }

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
                EntradaIndice nueva = escribirRegistro(dat, a);
                insertarOrdenado(indice, nueva);
            }

            std::cout << "Registro eliminado correctamente.\n";
            break;
        }

        case CliCommand::Actualizar: {
            Alumno nuevo = leerDesdeJSON(parametro);
            int pos = buscarEnIndice(indice, std::string(nuevo.no_cuenta, 10));
            if (pos == -1) {
                std::cout << "No se encontro el registro a actualizar.\n";
                break;
            }

            long offsetViejo   = indice[pos].offset;
            int  tamanioViejo  = indice[pos].tamanio;
            indice.erase(indice.begin() + pos);

            for (auto& e : indice) {
                if (e.offset > offsetViejo)
                    e.offset -= tamanioViejo;
            }

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

            EntradaIndice nueva = escribirRegistro(dat, nuevo);
            insertarOrdenado(indice, nueva);

            std::cout << "Registro actualizado correctamente.\n";
            break;
        }


        default:
            std::cout << "Comando no manejado.\n";
            break;
    }

    guardarIndice(ARCHIVO_INDICE, indice);
    dat.close();

    return 0;
}