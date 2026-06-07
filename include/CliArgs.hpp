#pragma once

#include <optional>
#include <string>

enum class CliCommand {
    Agregar,
    Eliminar,
    Buscar,
    Actualizar,
    CleanUp
};

class CliArgs {
public:
    CliArgs(int argc, const char* argv[]) {
        parse(argc, argv);
    }

    bool isGood() const { return good; }
    std::optional<CliCommand> cliCommand() const { return cli_command; }
    std::string getArgument() const { return argument; }

    void printUsage();

private:
    void parse(int argc, const char* argv[]);

private:
    std::string program;
    std::optional<CliCommand> cli_command;
    std::string argument; // Guarda el <archivo_json> o <no_cuenta>
    bool good = true;
};