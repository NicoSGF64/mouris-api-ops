#ifndef MOTIVODECORATIVO_H
#define MOTIVODECORATIVO_H
#include <string>
#include "obxetoestudo.h"

class MotivoDecorativo: public ObxetoEstudo
{
public:
    MotivoDecorativo() = default;
    MotivoDecorativo(const std::string &nome);

    std::string getNome() const;
    void setNome(const std::string &newNome);

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(MotivoDecorativo, nome);

private:
    std::string nome;
};

#endif // MOTIVODECORATIVO_H
