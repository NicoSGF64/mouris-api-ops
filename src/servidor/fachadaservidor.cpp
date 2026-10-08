#include "fachadaservidor.h"
#include <nanodbc/nanodbc.h>
#include <nlohmann/json.hpp>
#include <cppcodec/base64_rfc4648.hpp>
#include <textoerrosbbdd.h>

FachadaServidor::FachadaServidor(const std::string &rutaCertificado, const std::string &rutaChave) : rutaCertificado(rutaCertificado),
    rutaChave(rutaChave), servidor(rutaCertificado.c_str(), rutaChave.c_str())
{

    fioInvalidacions = std::thread(&FachadaServidor::invalidarSesions, this);
}

FachadaServidor::~FachadaServidor()
{
    limparFios = true;
    fioInvalidacions.join();
}

void FachadaServidor::atenderPeticions()
{
    std::cout << "Servidor escoitando" << std::endl;
    servidor.listen("0.0.0.0", porto);
}

std::unordered_map<std::string, Sesion> &FachadaServidor::getConexions()
{
    return conexions;
}

httplib::SSLServer &FachadaServidor::getServidor()
{
    return servidor;
}

Usuario FachadaServidor::obterUsuarioPeticion(const std::string& cabeceira)
{
    constexpr std::string_view valorAutorizacion = "Basic ";
    // Non se atopa a palabra "Basic" cun espazo: mal formado a cabeceira de autorización
    if (cabeceira.substr(0, valorAutorizacion.size()).find(valorAutorizacion) == std::string::npos)
        throw ErroAutentificacion();

    std::string autorizacion = cppcodec::base64_rfc4648::decode<std::string>(cabeceira.substr(valorAutorizacion.size()));

    std::string nomeUsuario = autorizacion.substr(0, autorizacion.find_first_of(":"));

    return Usuario(nomeUsuario, autorizacion.substr(autorizacion.find_first_of(":") + 1));
}

void FachadaServidor::invalidarSesions()
{
    while(!limparFios)
    {
        {
            std::scoped_lock candado(mutexConexions);

            for (auto it = conexions.cbegin(); it != conexions.cend();)
            {
                if (!it->second.serValida())
                    it = conexions.erase(it);
                else
                    it++;
            };
        }

        constexpr std::chrono::minutes minutosLimpeza = std::chrono::minutes(Sesion::minutosInvalidacion);
        std::this_thread::sleep_for(minutosLimpeza);
    }
}

void FachadaServidor::executarPeticion(const httplib::Request &req, httplib::Response &res, std::function<void(const httplib::Request& req, httplib::Response& res)> funcion)
{
    try
    {
        std::scoped_lock<std::mutex> candado(mutexConexions);
        funcion(req, res);
    }

    catch (const std::range_error& e)
    {
        res.status = 401;

        const nlohmann::json j =
        {
            {"error", "Sesión xa existente"}
        };

        res.set_content(j.dump(), "application/json");
    }
    catch (const std::out_of_range& e)
    {
        res.status = 403;

        const nlohmann::json j =
        {
            {"error", "Requírese iniciar sesión"}
        };

        res.set_content(j.dump(), "application/json");
    }
    catch (const nlohmann::json::exception& e)
    {
        res.status = 422;
        const nlohmann::json j =
        {
            #ifdef DEBUG
            {"error", e.what()}
            #else
            {"error", "O JSON fornecido está mal formado"}
            #endif
        };

        res.set_content(j.dump(), "application/json");
    }
    catch (const ErroAutentificacion& e)
    {
        res.status = 403;
        const nlohmann::json j =
        {
            {"error", "Erro de autenticación"}
        };

        res.set_content(j.dump(), "application/json");
    }
    catch (const ErroSesionCaducada& e)
    {
        res.status = 403;
        const nlohmann::json j =
        {
            {"error", "Sesión caducada"}
        };

        res.set_content(j.dump(), "application/json");
    }
    catch (const nanodbc::database_error& e)
    {
        res.status = 500;

        #ifdef DEBUG
        std::string textoErro = e.what();
        #else
        std::string_view textoErro = "Erro interno da base de datos";


        if (std::string_view(e.what()).find(baseNonFuncional) != std::string::npos)
            textoErro = "A API non puido establecer unha conexión coa base de datos";
        else if (std::string_view(e.what()).find(parametroInvalidamenteNulo) != std::string::npos)
        {
            res.status = 422;
            textoErro = "Estableceuse un campo non candidato a ser nulo como nulo";
        }
        else if (std::string_view(e.what()).find(nbindeadoMal) != std::string::npos)
            textoErro = "Erro de programación interna do servidor (nº parámetros ligados erróneo)";
        else if (std::string_view(e.what()).find(lonxitudeLonga) != std::string::npos)
        {
            res.status = 422;
            textoErro = "A lonxitude dos parámetros é demasiado longa";
        }
        else if (std::string_view(e.what()).find(permisoDenegado))
        {
            res.status = 403;
            textoErro = "Permiso denegado para manipular as táboas necesarias";
        }
        #endif

        const nlohmann::json j =
        {
            {"error", textoErro}
        };

        res.set_content(j.dump(), "application/json");
    }
    catch (const std::exception& e)
    {
        res.status = 500;
        const nlohmann::json j =
        {
            #ifdef DEBUG
            {"error", e.what()}
            #else
            {"error", "Erro interno do servidor"}
            #endif
        };

        res.set_content(j.dump(), "application/json");
    }
}

Sesion FachadaServidor::obterSesionUsuario(const httplib::Request& peticion)
{
    std::string usuario = peticion.get_header_value("Authorization");
    Usuario novo = obterUsuarioPeticion(usuario);

    Sesion existente = conexions.at(novo.getNomeUsuario().value());

    if(!existente.autenticar(novo.getNomeUsuario().value(), novo.getContrasinal().value()))
        throw ErroAutentificacion();

    return existente;
}
