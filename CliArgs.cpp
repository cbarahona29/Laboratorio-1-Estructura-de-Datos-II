#include <iostream>
#include "CliArgs.hpp"

void CliArgs::printUsage() {
    std::cout << "Uso: " << program << " <comando> [argumento]\n\n";
    std::cout << "Comandos requeridos:\n";
    std::cout << "  agregar <archivo_json>    \n";
    std::cout << "  eliminar <no_cuenta>      \n";
    std::cout << "  buscar <no_cuenta>        \n";
    std::cout << "  actualizar <archivo_json> \n";
    std::cout << "  clean-up                  \n";
}

void CliArgs::parse(int argc, const char* argv[]) {
    program = argv[0];

    if (argc < 2) {
        good = false;
        return;
    }

    std::string cmd = argv[1];

    if (cmd == "clean-up") {
        cli_command = CliCommand::CleanUp;
        return;
    }

    if (argc == 3) {
        argument = argv[2]; 

        if      (cmd == "agregar")    cli_command = CliCommand::Agregar;
        else if (cmd == "eliminar")   cli_command = CliCommand::Eliminar;
        else if (cmd == "buscar")     cli_command = CliCommand::Buscar;
        else if (cmd == "actualizar") cli_command = CliCommand::Actualizar;
        else                          good = false;
    } else {
        good = false;
    }
}