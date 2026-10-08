#ifndef USUARIO_H
#define USUARIO_H
#include <string>
#include "optionaljson.hpp"
#include "tipousuario.h"
#include "obxetoestudo.h"

class Usuario: public ObxetoEstudo
{
public:
    explicit Usuario(const std::string &nomeUsuario);
    Usuario(std::optional<std::string> nomeUsuario, std::optional<TipoUsuario> tipo);
    Usuario(std::optional<std::string> nomeUsuario, std::optional<std::string> contrasinal);
    Usuario(std::optional<std::string> nomeUsuario, std::optional<std::string> contrasinal, std::string_view tipo);
    Usuario(std::optional<std::string> nomeUsuario, std::optional<std::string> contrasinal, std::optional<TipoUsuario> tipo);

    Usuario() = default;

    std::optional<std::string> getNomeTipo() const;

    std::optional<std::string> getNomeUsuario() const;
    void setNomeUsuario(std::optional<std::string> newNomeUsuario);
    std::optional<std::string> getContrasinal() const;
    void setContrasinal(std::optional<std::string> newContrasinal);

    std::optional<TipoUsuario> getTipo() const;

    void setTipo(std::optional<TipoUsuario> newTipo);
    void setTipo(std::string newTipo);

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Usuario, nomeUsuario, contrasinal, tipo);

private:
    std::optional<std::string> nomeUsuario;
    std::optional<std::string> contrasinal;
    std::optional<TipoUsuario> tipo;
};

#endif // USUARIO_H
