#include "lapida.h"

Lapida::Lapida(unsigned int id) : id(id)
{}

Lapida::Lapida(std::optional<unsigned int> id, std::optional<std::string> xeneoloxia, std::optional<std::string> epigrafia, std::optional<Data> datacion, std::optional<std::string> proxectoArquitectonico, std::optional<estadoConservacion> estadoConservacionBioloxico, std::optional<estadoConservacion> estadoConservacionAtmosferico, const std::vector<Material> &materiais, const std::vector<MotivoDecorativo> &motivosDecorativos) : id(std::move(id)),
    xenealoxia(std::move(xeneoloxia)),
    epigrafia(std::move(epigrafia)),
    datacion(std::move(datacion)),
    proxectoArquitectonico(std::move(proxectoArquitectonico)),
    estadoConservacionBioloxico(std::move(estadoConservacionBioloxico)),
    estadoConservacionAtmosferico(std::move(estadoConservacionAtmosferico)),
    materiais(materiais),
    motivosDecorativos(motivosDecorativos)
{}

std::optional<unsigned int> Lapida::getId() const
{
    return id;
}

void Lapida::setId(std::optional<unsigned int> newId)
{
    id = newId;
}

std::optional<std::string> Lapida::getXenealoxia() const
{
    return xenealoxia;
}

void Lapida::setXeneoloxia(std::optional<std::string> newXeneoloxia)
{
    xenealoxia = newXeneoloxia;
}

std::optional<std::string> Lapida::getEpigrafia() const
{
    return epigrafia;
}

void Lapida::setEpigrafia(std::optional<std::string> newEpigrafia)
{
    epigrafia = newEpigrafia;
}

std::optional<Data> Lapida::getDatacion() const
{
    return datacion;
}

void Lapida::setDatacion(std::optional<Data> newDatacion)
{
    datacion = newDatacion;
}

std::optional<std::string> Lapida::getProxectoArquitectonico() const
{
    return proxectoArquitectonico;
}

void Lapida::setProxectoArquitectonico(std::optional<std::string> newProxectoArquitectonico)
{
    proxectoArquitectonico = newProxectoArquitectonico;
}

std::optional<estadoConservacion> Lapida::getEstadoConservacionBioloxico() const
{
    return estadoConservacionBioloxico;
}

void Lapida::setEstadoConservacionBioloxico(std::optional<estadoConservacion> newEstadoConservacionBioloxico)
{
    estadoConservacionBioloxico = newEstadoConservacionBioloxico;
}

std::optional<estadoConservacion> Lapida::getEstadoConservacionAtmosferico() const
{
    return estadoConservacionAtmosferico;
}

void Lapida::setEstadoConservacionAtmosferico(std::optional<estadoConservacion> newEstadoConservacionAtmosferico)
{
    estadoConservacionAtmosferico = newEstadoConservacionAtmosferico;
}

std::vector<Material> Lapida::getMateriais() const
{
    return materiais;
}

void Lapida::setMateriais(const std::vector<Material> &newMateriais)
{
    materiais = newMateriais;
}

std::vector<MotivoDecorativo> Lapida::getMotivosDecorativos() const
{
    return motivosDecorativos;
}

void Lapida::setMotivosDecorativos(const std::vector<MotivoDecorativo> &newMotivosDecorativos)
{
    motivosDecorativos = newMotivosDecorativos;
}