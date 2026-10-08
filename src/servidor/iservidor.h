#ifndef ISERVIDOR_H
#define ISERVIDOR_H
#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <httplib.h>
#include <usuario.h>
#include <sesion.h>

class IServidor
{
public:
    virtual ~IServidor() = default;

    virtual std::unordered_map<std::string, Sesion>& getConexions() = 0;

    virtual httplib::SSLServer& getServidor() = 0;

    virtual Usuario obterUsuarioPeticion(const std::string& cabeceira) = 0;

    virtual Sesion obterSesionUsuario(const httplib::Request& peticion) = 0;

    virtual void executarPeticion(const httplib::Request &req, httplib::Response &res, std::function<void(const httplib::Request& req, httplib::Response& res)> funcion) = 0;
};

#endif // ISERVIDOR_H
