#ifndef PARSEADORLINEACOMANDOS_H
#define PARSEADORLINEACOMANDOS_H
#include <stdexcept>
#include <string>

struct OpcionsPrograma
{
    std::string rutaCertificado;
    std::string rutaChave;
    std::string datosDSN;
    static constexpr unsigned short numeroParametrosEsenciais = 0;
};

class ErroSenParametroEsencial : public std::runtime_error
{
public:
    explicit ErroSenParametroEsencial(const std::string& what_arg) : std::runtime_error(what_arg) {};
};

class ParseadorLineaComandos
{
public:
    ParseadorLineaComandos() = default;
    OpcionsPrograma obterOpcions(int argc, char *argv[]);
private:
    constexpr std::string configurarOpcion(char *lineacomandos[], int& posicion);
};

#endif // PARSEADORLINEACOMANDOS_H
