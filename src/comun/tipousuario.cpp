#include "tipousuario.h"
#include <stdexcept>

TipoUsuario::tiposUsuario TipoUsuario::getTipo() const
{
    return tipo;
}

TipoUsuario::TipoUsuario(std::string_view nome)
{
    if (nome == "usuario_consultorio")
         tipo = tiposUsuario::usuarioConsulturio;
    else if (nome == "usuario_tecnico")
        tipo = tiposUsuario::persoalTecnico;
    else if (nome == "administrador_sistema")
        tipo = tiposUsuario::administradorSistema;
}

TipoUsuario::tiposUsuario TipoUsuario::getTipo(std::string_view nome)
{
    if (nome == "usuario_consultorio")
        return tiposUsuario::usuarioConsulturio;
    else if (nome == "usuario_tecnico")
        return tiposUsuario::persoalTecnico;
    else if (nome == "administrador_sistema")
        return tiposUsuario::administradorSistema;
    else
        throw std::runtime_error("Tipo de usuario inválido");
}

std::string TipoUsuario::getNomeTipo() const
{
    switch (tipo)
    {
    case tiposUsuario::usuarioConsulturio:
        return "usuario_consultorio";
        break;
    case tiposUsuario::persoalTecnico:
        return "usuario_tecnico";
        break;
    case tiposUsuario::administradorSistema:
        return "administrador_sistema";
        break;
    default:
        return {};
        break;
    }
}

void TipoUsuario::setTipo(tiposUsuario newTipo)
{
    tipo = newTipo;
}

void TipoUsuario::setTipo(std::string &newTipo)
{
    if (newTipo == "usuario_consultorio")
        tipo = tiposUsuario::usuarioConsulturio;
    else if (newTipo == "usuario_tecnico")
        tipo = tiposUsuario::persoalTecnico;
    else if (newTipo == "administrador_sistema")
        tipo = tiposUsuario::administradorSistema;
}
