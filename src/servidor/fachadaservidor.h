#ifndef FACHADASERVIDOR_H
#define FACHADASERVIDOR_H
#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <mutex>
#include <httplib.h>
#include "iservidor.h"

class FachadaServidor : public IServidor
{
public:
    FachadaServidor() = delete;
    FachadaServidor(const std::string &rutaCertificado, const std::string &rutaChave);
    ~FachadaServidor() override;

    std::unordered_map<std::string, Sesion> &getConexions() override;

    httplib::SSLServer& getServidor() override;

    Usuario obterUsuarioPeticion(const std::string& cabeceira) override;

    Sesion obterSesionUsuario(const httplib::Request& peticion) override;

    void executarPeticion(const httplib::Request &req, httplib::Response &res, std::function<void(const httplib::Request& req, httplib::Response& res)> funcion) override;

    void atenderPeticions();

    static constexpr unsigned short porto = 8080;

private:
    std::string rutaCertificado;
    std::string rutaChave;

    httplib::SSLServer servidor;

    std::unordered_map<std::string, Sesion> conexions;
    std::mutex mutexConexions;

    void invalidarSesions();

    std::thread fioInvalidacions;
    bool limparFios = false;
};

#endif // FACHADASERVIDOR_H
