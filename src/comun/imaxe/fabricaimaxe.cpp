#include "fabricaimaxe.h"
#include "errosimaxe.h"
#include "imaxepng.h"
#include "imaxejpeg.h"

std::unique_ptr<Imaxe> FabricaImaxe::fabricar(std::string_view mime, const std::vector<uint8_t> &datos)
{
    if(datos.empty())
        return nullptr;

    if(mime == "image/png")
    {
        if(!ImaxePNG::validarDatos(datos))
            throw ErroImaxeInvalida();

        return std::make_unique<ImaxePNG>(ImaxePNG(datos));
    }
    else if (mime == "image/jpeg" || mime == "image/jpg")
    {
        if(!ImaxeJPEG::validarDatos(datos))
            throw ErroImaxeInvalida();

        return std::make_unique<ImaxeJPEG>(ImaxeJPEG(datos));
    }
    else
        throw ErroMIMEInvalido();

    return nullptr;
}
