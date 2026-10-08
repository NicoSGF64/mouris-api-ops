#include "benpatrimonial.h"

BenPatrimonial::BenPatrimonial(unsigned int id) : id(id) { }

BenPatrimonial::BenPatrimonial(std::optional<unsigned int> id, std::optional<std::string> nome, std::optional<std::string> descripcion, std::optional<float> altura, std::optional<float> anchura, std::optional<unsigned short> datacion, std::optional<std::string> seculo, std::optional<std::string> segmento, std::optional<std::string> estilo, std::optional<std::string> taller, const std::vector<Material> &materiais, const std::vector<MotivoDecorativo> &motivosDecorativos) : id(std::move(id)),
    nome(std::move(nome)),
    descripcion(std::move(descripcion)),
    altura(std::move(altura)),
    anchura(std::move(anchura)),
    datacion(std::move(datacion)),
    seculo(std::move(seculo)),
    segmento(std::move(segmento)),
    estilo(std::move(estilo)),
    taller(std::move(taller)),
    materiais(materiais),
    motivosDecorativos(motivosDecorativos)
{}

std::optional<unsigned int> BenPatrimonial::getId() const
{
    return id;
}

void BenPatrimonial::setId(std::optional<unsigned int> newId)
{
    id = newId;
}

std::optional<std::string> BenPatrimonial::getNome() const
{
    return nome;
}

void BenPatrimonial::setNome(std::optional<std::string> newNome)
{
    nome = newNome;
}

std::optional<std::string> BenPatrimonial::getDescripcion() const
{
    return descripcion;
}

void BenPatrimonial::setDescripcion(std::optional<std::string> newDescripcion)
{
    descripcion = newDescripcion;
}

std::optional<float> BenPatrimonial::getAltura() const
{
    return altura;
}

void BenPatrimonial::setAltura(std::optional<float> newAltura)
{
    altura = newAltura;
}

std::optional<float> BenPatrimonial::getAnchura() const
{
    return anchura;
}

void BenPatrimonial::setAnchura(std::optional<float> newAnchura)
{
    anchura = newAnchura;
}

std::optional<unsigned short> BenPatrimonial::getDatacion() const
{
    return datacion;
}

void BenPatrimonial::setDatacion(std::optional<unsigned short> newDatacion)
{
    datacion = newDatacion;
}

std::optional<std::string> BenPatrimonial::getSeculo() const
{
    return seculo;
}

void BenPatrimonial::setSeculo(std::optional<std::string> newSeculo)
{
    seculo = newSeculo;
}

std::optional<std::string> BenPatrimonial::getSegmento() const
{
    return segmento;
}

void BenPatrimonial::setSegmento(std::optional<std::string> newSegmento)
{
    segmento = newSegmento;
}

std::optional<std::string> BenPatrimonial::getEstilo() const
{
    return estilo;
}

void BenPatrimonial::setEstilo(std::optional<std::string> newEstilo)
{
    estilo = newEstilo;
}

std::optional<std::string> BenPatrimonial::getTaller() const
{
    return taller;
}

void BenPatrimonial::setTaller(std::optional<std::string> newTaller)
{
    taller = newTaller;
}

std::vector<Material> BenPatrimonial::getMateriais() const
{
    return materiais;
}

void BenPatrimonial::setMateriais(const std::vector<Material> &newMateriais)
{
    materiais = newMateriais;
}

std::vector<MotivoDecorativo> BenPatrimonial::getMotivosDecorativos() const
{
    return motivosDecorativos;
}
