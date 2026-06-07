#include <iostream>
#include "CliArgs.hpp"

int main(int argc, const char* argv[]) {
    CliArgs args(argc, argv);

    if (!args.isGood()) {
        args.printUsage();
        return 1;
    }

    std::string parametro = args.getArgument();

    std::cout << "    PRUEBA DE COMANDOS     \n";

    switch (args.cliCommand().value()) {
        case CliCommand::Agregar:
            std::cout << "Comando detectado: agregar\n";
            std::cout << "test\n";
            break;

        case CliCommand::Eliminar:
            std::cout << "Comando detectado: eliminar\n";
            std::cout << "test\n";
            break;

        case CliCommand::Buscar:
            std::cout << "Comando detectado: buscar\n";
            std::cout << "test\n";
            break;

        case CliCommand::Actualizar:
            std::cout << "Comando detectado: actualizar\n";
            std::cout << "test\n";
            break;

        case CliCommand::CleanUp:
            std::cout << "Comando detectado: clean-up\n";
            std::cout << "test\n";
            break;

        default:
            std::cout << "[!] Comando no manejado en el switch.\n";
            break;
    }


    return 0;
}