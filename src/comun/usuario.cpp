#include "usuario.h"

Usuario::Usuario(const std::string& newNomeUsuario) : nomeUsuario(newNomeUsuario)
{ }

Usuario::Usuario(std::optional<std::string> nomeUsuario, std::optional<TipoUsuario> tipo) : nomeUsuario(std::move(nomeUsuario)),
    tipo(std::move(tipo))
{}

Usuario::Usuario(std::optional<std::string> nomeUsuario, std::optional<std::string> contrasinal) : nomeUsuario(std::move(nomeUsuario)),
    contrasinal(std::move(contrasinal))
{}

Usuario::Usuario(std::optional<std::string> nomeUsuario, std::optional<std::string> contrasinal, std::optional<TipoUsuario> tipo) : nomeUsuario(std::move(nomeUsuario)),
    contrasinal(std::move(contrasinal)),
    tipo(std::move(tipo))
{}

Usuario::Usuario(std::optional<std::string> nomeUsuario, std::optional<std::string> contrasinal, std::string_view tipo) : nomeUsuario(std::move(nomeUsuario)),
    contrasinal(std::move(contrasinal)), tipo(tipo)
{}

void Usuario::setTipo(std::optional<TipoUsuario> newTipo)
{
    tipo = newTipo;
}

void Usuario::setTipo(std::string newTipo)
{
    if(tipo)
        tipo.value().setTipo(newTipo);
}

std::optional<std::string> Usuario::getNomeTipo() const
{
    if(tipo)
        return tipo.value().getNomeTipo();
    else
        return {};
}

std::optional<std::string> Usuario::getNomeUsuario() const
{
    return nomeUsuario;
}

void Usuario::setNomeUsuario(std::optional<std::string> newNomeUsuario)
{
    nomeUsuario = newNomeUsuario;
}

std::optional<std::string> Usuario::getContrasinal() const
{
    return contrasinal;
}

void Usuario::setContrasinal(std::optional<std::string> newContrasinal)
{
    contrasinal = newContrasinal;
}

std::optional<TipoUsuario> Usuario::getTipo() const
{
    return tipo;
}
