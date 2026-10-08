#ifndef ESTADOCONSERVACION_H
#define ESTADOCONSERVACION_H
#include <string>
#include <nlohmann/json.hpp>

struct estadoConservacion
{
    std::string marca;
    std::string razonamento;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(estadoConservacion, marca, razonamento);
};

#endif // ESTADOCONSERVACION_H
