#include "parseadorlineacomandos.h"
#include <cstring>
#include <fstream>
#include <array>
#include <iostream>
#include <algorithm>

OpcionsPrograma ParseadorLineaComandos::obterOpcions(int argc, char *argv[])
{
    OpcionsPrograma opcions;

    if(argc < OpcionsPrograma::numeroParametrosEsenciais * 2)
        throw ErroSenParametroEsencial("Faltan parámetros esenciais");

    // i = 1 ao non necesitar o nome do arquivo
    for (int i = 1; i < argc; i++)
    {
        // Porque para comprobar
        if(i + 1 == argc)
            break;

        if(std::strcmp(argv[i], "-c") == 0 || std::strcmp(argv[i], "--certificado") == 0)
            opcions.rutaCertificado = configurarOpcion(argv, i);
        else if(std::strcmp(argv[i], "-k") == 0 || std::strcmp(argv[i], "--chave") == 0)
            opcions.rutaChave = configurarOpcion(argv, i);
        else if(std::strcmp(argv[i], "-b" ) == 0 || std::strcmp(argv[i], "--dsn") == 0)
        {
            std::ifstream arquivo{configurarOpcion(argv, i)};
            std::string paramConexion{};
            if (!arquivo)
                throw std::runtime_error("Arquivo de configuracion non existente");
            else
            {
                while(std::getline(arquivo, paramConexion))
                    opcions.datosDSN += paramConexion + ";";
            }

            opcions.datosDSN.pop_back();
        }
        else
        {
            std::cout << "Opción de comados descoñecida: " << argv[i] << '\n';
        }
    }

    std::array<std::string_view, 3> valores{opcions.rutaChave, opcions.rutaChave, opcions.datosDSN};

    const auto it = std::find_if(valores.begin(), valores.end(), [](std::string_view valor)
    {
        return valor.empty();
    });

    if(it != valores.end())
        throw ErroSenParametroEsencial("Faltan parámetros esenciais");

    return opcions;
}

constexpr std::string ParseadorLineaComandos::configurarOpcion(char *lineacomandos[], int &posicion)
{
    posicion++;
    return lineacomandos[posicion];
}
