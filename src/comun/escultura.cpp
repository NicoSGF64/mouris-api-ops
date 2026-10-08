#include "escultura.h"

Escultura::Escultura(unsigned int id) : BenPatrimonial(id)
{}

Escultura::Escultura(std::optional<std::string> santoRepresentado, std::optional<unsigned int> id, std::optional<std::string> nome, std::optional<std::string> descripcion, std::optional<float> altura, std::optional<float> anchura, std::optional<unsigned short> datacion, std::optional<std::string> seculo, std::optional<std::string> segmento, std::optional<std::string> estilo, std::optional<std::string> taller, const std::vector<Material> &materiais, const std::vector<MotivoDecorativo> &motivosDecorativos) :
    BenPatrimonial::BenPatrimonial(std::move(id), std::move(nome), std::move(descripcion), std::move(altura), std::move(anchura), std::move(datacion), std::move(seculo), std::move(segmento), std::move(estilo), std::move(taller), std::move(materiais), std::move(motivosDecorativos)), santoRepresentado(santoRepresentado)
{}

std::optional<std::string> Escultura::getSantoRepresentado() const
{
    return santoRepresentado;
}

void Escultura::setSantoRepresentado(std::optional<std::string> newSantoRepresentado)
{
    santoRepresentado = newSantoRepresentado;
}
