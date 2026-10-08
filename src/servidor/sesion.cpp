#include "sesion.h"

Sesion::Sesion(const std::string& dsn, const Usuario& usuario) : ultimaInactividade(std::chrono::steady_clock::now()),
    usuario(usuario), xestionador(dsn, usuario)
{ }

bool Sesion::serValida() const
{
    return std::chrono::duration_cast<std::chrono::minutes>(std::chrono::steady_clock::now() - ultimaInactividade).count() < minutosInvalidacion;
}

bool Sesion::autenticar(const std::string_view nome, const std::string_view contrasinal)
{
    return nome == usuario.getNomeUsuario().value() && contrasinal == usuario.getContrasinal().value();
}

Usuario Sesion::getUsuario() const
{
    return usuario;
}

void Sesion::setUsuario(const Usuario &newUsuario)
{
    usuario = newUsuario;
}
