#include "imaxepng.h"
#include <array>

ImaxePNG::ImaxePNG(const std::vector<uint8_t> &datos) : datos(datos)
{ }

std::vector<uint8_t> ImaxePNG::getDatos() const
{
    return datos;
}

void ImaxePNG::setDatos(const std::vector<uint8_t> &newDatos)
{
    datos = newDatos;
}

std::string ImaxePNG::getMIME() const
{
    return "image/png";
}

bool ImaxePNG::serValida() const
{
    return validarDatos(datos);
}

bool ImaxePNG::validarDatos(const std::vector<uint8_t> &datos)
{
    constexpr std::array inicioPNG{137, 80, 78, 71, 13, 10, 26, 10};

    if(datos.size() < inicioPNG.size())
        return false;

    for(size_t i = 0; i < inicioPNG.size(); i++)
    {
        if(inicioPNG.at(i) != datos.at(i))
            return false;
    }

    return true;
}
