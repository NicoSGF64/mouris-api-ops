#ifndef ESCULTURA_H
#define ESCULTURA_H

#include "benpatrimonial.h"

class Escultura : public BenPatrimonial
{
public:
    Escultura() = default;
    explicit Escultura(unsigned int id);
    Escultura(std::optional<std::string> santoRepresentado, std::optional<unsigned int> id, std::optional<std::string> nome, std::optional<std::string> descripcion, std::optional<float> altura, std::optional<float> anchura, std::optional<unsigned short> datacion, std::optional<std::string> seculo, std::optional<std::string> segmento, std::optional<std::string> estilo, std::optional<std::string> taller, const std::vector<Material> &materiais, const std::vector<MotivoDecorativo> &motivosDecorativos);

    std::optional<std::string> getSantoRepresentado() const;
    void setSantoRepresentado(std::optional<std::string> newSantoRepresentado);

    NLOHMANN_DEFINE_DERIVED_TYPE_INTRUSIVE(Escultura, BenPatrimonial, santoRepresentado);

private:
    std::optional<std::string> santoRepresentado;
};

#endif // ESCULTURA_H
