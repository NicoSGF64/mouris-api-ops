#ifndef LAPIDA_H
#define LAPIDA_H
#include <optional>
#include <vector>
#include "datacion.h"
#include "estadoConservacion.h"
#include "material.h"
#include "motivodecorativo.h"

class Lapida: public ObxetoEstudo
{
public:
    explicit Lapida(unsigned int id);
    Lapida(std::optional<unsigned int> id, std::optional<std::string> xeneoloxia, std::optional<std::string> epigrafia, std::optional<Data> datacion, std::optional<std::string> proxectoArquitectonico, std::optional<estadoConservacion> estadoConservacionBioloxico, std::optional<estadoConservacion> estadoConservacionAtmosferico, const std::vector<Material> &materiais, const std::vector<MotivoDecorativo> &motivosDecorativos);

    Lapida() = default;

    std::optional<unsigned int> getId() const;
    void setId(std::optional<unsigned int> newId);
    std::optional<std::string> getXenealoxia() const;
    void setXeneoloxia(std::optional<std::string> newXeneoloxia);
    std::optional<std::string> getEpigrafia() const;
    void setEpigrafia(std::optional<std::string> newEpigrafia);
    std::optional<Data> getDatacion() const;
    void setDatacion(std::optional<Data> newDatacion);
    std::optional<std::string> getProxectoArquitectonico() const;
    void setProxectoArquitectonico(std::optional<std::string> newProxectoArquitectonico);
    std::optional<estadoConservacion> getEstadoConservacionBioloxico() const;
    void setEstadoConservacionBioloxico(std::optional<estadoConservacion> newEstadoConservacionBioloxico);
    std::optional<estadoConservacion> getEstadoConservacionAtmosferico() const;
    void setEstadoConservacionAtmosferico(std::optional<estadoConservacion> newEstadoConservacionAtmosferico);

    std::vector<Material> getMateriais() const;
    void setMateriais(const std::vector<Material> &newMateriais);
    std::vector<MotivoDecorativo> getMotivosDecorativos() const;
    void setMotivosDecorativos(const std::vector<MotivoDecorativo> &newMotivosDecorativos);

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Lapida, id, xenealoxia, epigrafia, datacion, proxectoArquitectonico, estadoConservacionBioloxico, estadoConservacionAtmosferico, materiais, motivosDecorativos);

private:
    std::optional<unsigned int> id;
    std::optional<std::string> xenealoxia;
    std::optional<std::string> epigrafia;
    std::optional<Data> datacion;
    std::optional<std::string> proxectoArquitectonico;
    std::optional<estadoConservacion> estadoConservacionBioloxico;
    std::optional<estadoConservacion> estadoConservacionAtmosferico;
    std::vector<Material> materiais;
    std::vector<MotivoDecorativo> motivosDecorativos;
};

#endif // LAPIDA_H
