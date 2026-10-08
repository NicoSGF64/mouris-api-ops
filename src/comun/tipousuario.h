#ifndef TIPOUSUARIO_H
#define TIPOUSUARIO_H
#include <nlohmann/json.hpp>
#include <string>

class TipoUsuario
{
public:
    TipoUsuario() = default;
    explicit TipoUsuario(std::string_view);
    enum tiposUsuario {usuarioConsulturio, persoalTecnico, administradorSistema};

    tiposUsuario getTipo() const;
    static tiposUsuario getTipo(std::string_view nome);
    std::string getNomeTipo() const;
    void setTipo(tiposUsuario newTipo);
    void setTipo(std::string& newTipo);

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(TipoUsuario, tipo);

private:
    tiposUsuario tipo;
};

#endif // TIPOUSUARIO_H
