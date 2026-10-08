#include "xestionadorpeticionsautenticar.h"
#include "sesion.h"
#include "errosautentificacion.h"
#include <textoerrosbbdd.h>

XestionadorPeticionsAutenticar::XestionadorPeticionsAutenticar(IServidor &fs, const std::string& dsn) : IXestionadorPeticions(fs), dsn(dsn)
{ }


void XestionadorPeticionsAutenticar::configurarPeticions(std::string_view uri)
{
    fs.getServidor().Post("/" + std::string(uri), [this](const httplib::Request &req, httplib::Response &res)
    {
        fs.executarPeticion(req, res, [this](const httplib::Request &req, httplib::Response &res){ return this->login(req, res); });
    });

    fs.getServidor().Delete("/" + std::string(uri), [this](const httplib::Request &req, httplib::Response &res)
    {
        fs.executarPeticion(req, res, [this](const httplib::Request &req, httplib::Response &res){ return this->logout(req, res); });
    });
}

void XestionadorPeticionsAutenticar::login(const httplib::Request &req, httplib::Response &res)
{
    Usuario u = fs.obterUsuarioPeticion(req.get_header_value("Authorization"));

    if(fs.getConexions().contains(u.getNomeUsuario().value()))
        throw ErroAutentificacion();

    try
    {
        fs.getConexions().insert({u.getNomeUsuario().value(), Sesion(dsn, u)});
    }
    catch (nanodbc::database_error& e)
    {
        if(std::string_view(e.what()).find(credenciaisIncorrectas) == std::string::npos)
            throw e;

        res.status = 401;

        const nlohmann::json j =
        {
            {"error", "Nome de usuario ou contrasinal incorrectas"}
        };

        res.set_content(j.dump(), "application/json");
        return;
    }

    res.status = 200;
}

void XestionadorPeticionsAutenticar::logout(const httplib::Request &req, httplib::Response &res)
{
    Usuario u = fs.obterUsuarioPeticion(req.get_header_value("Authorization"));

    try
    {
        fs.getConexions().at(u.getNomeUsuario().value());
    }
    catch (...)
    {
        throw ErroAutentificacion();
    }

    // Comprobar se a contrasinal do usuario que estamos a pechar sesión é correcta,
    // para que non poda un usuario arbitrario pechar remotamente sesións
    if(!fs.getConexions().at(u.getNomeUsuario().value()).autenticar(u.getNomeUsuario().value(), u.getContrasinal().value()))
        throw ErroAutentificacion();

    fs.getConexions().erase(u.getNomeUsuario().value());

    res.status = 200;
}
