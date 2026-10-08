#ifndef BENPATRIMONIAL_H
#define BENPATRIMONIAL_H
#include <string>
#include <optional>
#include <vector>
#include "material.h"
#include "motivodecorativo.h"
#include "obxetoestudo.h"

class BenPatrimonial: public ObxetoEstudo
{
public:
    BenPatrimonial() = default;
    explicit BenPatrimonial(unsigned int id);
    BenPatrimonial(std::optional<unsigned int> id, std::optional<std::string> nome, std::optional<std::string> descripcion, std::optional<float> altura, std::optional<float> anchura, std::optional<unsigned short> datacion, std::optional<std::string> seculo, std::optional<std::string> segmento, std::optional<std::string> estilo, std::optional<std::string> taller, const std::vector<Material> &materiais, const std::vector<MotivoDecorativo> &motivosDecorativos);

    std::optional<unsigned int> getId() const;
    void setId(std::optional<unsigned int> newId);
    std::optional<std::string> getNome() const;
    void setNome(std::optional<std::string> newNome);
    std::optional<float> getAltura() const;
    std::optional<std::string> getDescripcion() const;
    void setDescripcion(std::optional<std::string> newDescripcion);
    void setAltura(std::optional<float> newAltura);
    std::optional<float> getAnchura() const;
    void setAnchura(std::optional<float> newAnchura);
    std::optional<unsigned short> getDatacion() const;
    void setDatacion(std::optional<unsigned short> newDatacion);
    std::optional<std::string> getSeculo() const;
    void setSeculo(std::optional<std::string> newSeculo);
    std::optional<std::string> getSegmento() const;
    void setSegmento(std::optional<std::string> newSegmento);
    std::optional<std::string> getEstilo() const;
    void setEstilo(std::optional<std::string> newEstilo);
    std::optional<std::string> getTaller() const;
    void setTaller(std::optional<std::string> newTaller);

    std::vector<Material> getMateriais() const;
    void setMateriais(const std::vector<Material> &newMateriais);
    std::vector<MotivoDecorativo> getMotivosDecorativos() const;
    void setMotivosDecorativos(const std::vector<MotivoDecorativo> &newMotivosDecorativos);

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(BenPatrimonial, id, nome, descripcion, altura, anchura, seculo, segmento, estilo, taller, materiais, motivosDecorativos);

protected:
    std::optional<unsigned int> id;
    std::optional<std::string> nome;
    std::optional<std::string> descripcion;
    std::optional<float> altura;
    std::optional<float> anchura;
    std::optional<unsigned short> datacion;
    std::optional<std::string> seculo;
    std::optional<std::string> segmento;
    std::optional<std::string> estilo;
    std::optional<std::string> taller;
    std::vector<Material> materiais;
    std::vector<MotivoDecorativo> motivosDecorativos;

};

#endif // BENPATRIMONIAL_H
