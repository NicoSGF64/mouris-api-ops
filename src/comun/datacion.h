#ifndef DATACION_H
#define DATACION_H
#include <nlohmann/json.hpp>

struct Data
{
    unsigned short dia;
    unsigned short mes;
    int ano;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Data, dia, mes, ano);
};

#endif // DATACION_H
