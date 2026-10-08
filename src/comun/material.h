#ifndef MATERIAL_H
#define MATERIAL_H
#include <string>
#include "obxetoestudo.h"

class Material: public ObxetoEstudo
{
public:
    Material() = default;
    Material(const std::string &nome);

    std::string getNome() const;
    void setNome(const std::string &newNome);

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Material, nome);

private:
    std::string nome;
};

#endif // MATERIAL_H
