#include "imaxejpeg.h"
#include <array>

ImaxeJPEG::ImaxeJPEG(const std::vector<uint8_t> &datos) : datos(datos)
{ }

std::vector<uint8_t> ImaxeJPEG::getDatos() const
{
    return datos;
}

void ImaxeJPEG::setDatos(const std::vector<uint8_t> &newDatos)
{
    datos = newDatos;
}

std::string ImaxeJPEG::getMIME() const
{
    return "image/jpeg";
}

bool ImaxeJPEG::serValida() const
{
    return validarDatos(datos);
}

bool ImaxeJPEG::validarDatos(const std::vector<uint8_t> &datos)
{
    // Sacado de https://en.wikipedia.org/wiki/Magic_number_(programming)#In_files
    constexpr std::array comezoJPEG{255, 216};
    constexpr std::array finJPEG{255, 217};

    if(datos.size() < 4)
        return false;

    if(datos.at(0) == comezoJPEG.at(0) && datos.at(1) == comezoJPEG.at(1) && datos.at(datos.size() - 2) == finJPEG.at(0) && datos.back() == finJPEG.at(1))
        return true;

    return false;
}
