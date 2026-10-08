#include <fachadaservidor.h>
#include "configurador/xestionadorpeticionsobxetoestudo.h"
#include "configurador/xestionadorpeticionsautenticar.h"
#include "configurador/xestionadorpeticionsimaxe.h"
#include "parseadorlineacomandos.h"

int main(int argc, char *argv[])
{
    ParseadorLineaComandos parseador;
    OpcionsPrograma opcions;

    try
    {
        opcions = parseador.obterOpcions(argc, argv);
    }
    catch (ErroSenParametroEsencial&)
    {
        std::cerr << "Faltan parámetros requiridos\n";
        return -1;
    }

    FachadaServidor servidor(opcions.rutaCertificado, opcions.rutaChave);

    constexpr std::string_view URIBenPatrimonial = "benpatrimonial";
    constexpr std::string_view URIEscultura = "escultura";
    constexpr std::string_view URILapida = "lapida";
    constexpr std::string_view URIMaterial = "material";
    constexpr std::string_view URIMotivoDecorativo = "motivodecorativo";
    constexpr std::string_view URIUsuarios = "usuario";
    constexpr std::string_view URIAutenticar = "autenticar";

    XestionadorPeticionsObxetoEstudo<BenPatrimonial> xpoBp(servidor);
    xpoBp.configurarPeticions(URIBenPatrimonial);

    XestionadorPeticionsObxetoEstudo<Escultura> xpoeE(servidor);
    xpoeE.configurarPeticions(URIEscultura);

    XestionadorPeticionsObxetoEstudo<Lapida> xpoeL(servidor);
    xpoeL.configurarPeticions(URILapida);

    XestionadorPeticionsObxetoEstudo<Material> xpoeM(servidor);
    xpoeM.configurarPeticions(URIMaterial);

    XestionadorPeticionsObxetoEstudo<MotivoDecorativo> xpoeMd(servidor);
    xpoeMd.configurarPeticions(URIMotivoDecorativo);

    XestionadorPeticionsObxetoEstudo<Usuario> xpoeU(servidor);
    xpoeU.configurarPeticions(URIUsuarios);

    XestionadorPeticionsAutenticar xpoeAuth(servidor, opcions.datosDSN);
    xpoeAuth.configurarPeticions(URIAutenticar);

    XestionadorPeticionsImaxe<BenPatrimonial> xpiB(servidor);
    xpiB.configurarPeticions(URIBenPatrimonial);

    XestionadorPeticionsImaxe<Escultura> xpiE(servidor);
    xpiE.configurarPeticions(URIEscultura);

    XestionadorPeticionsImaxe<Lapida> xpiL(servidor);
    xpiL.configurarPeticions(URILapida);

    servidor.atenderPeticions();

    return 0;
}
