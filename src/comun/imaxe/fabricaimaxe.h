#ifndef FABRICAIMAXE_H
#define FABRICAIMAXE_H
#include "imaxe.h"
#include <memory>
#include <vector>

class FabricaImaxe
{
public:
    FabricaImaxe() = default;

    std::unique_ptr<Imaxe> fabricar(std::string_view mime, const std::vector<uint8_t> &datos);
};

#endif // FABRICAIMAXE_H
