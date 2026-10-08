#ifndef XESTIONADORPETICIONSOBXETOESTUDO_H
#define XESTIONADORPETICIONSOBXETOESTUDO_H
#include "ixestionadorpeticions.h"

template <typename T>
class XestionadorPeticionsObxetoEstudo : public IXestionadorPeticions
{
public:
    XestionadorPeticionsObxetoEstudo() = delete;
    explicit XestionadorPeticionsObxetoEstudo(IServidor &fs) : IXestionadorPeticions(fs) {};

    void configurarPeticions(std::string_view uri) override
    {
        fs.getServidor().Get("/" + std::string(uri), [this](const httplib::Request &req, httplib::Response &res)
        {
            fs.executarPeticion(req, res, [this](const httplib::Request &req, httplib::Response &res){ return this->GetObxetoEstudo(req, res);});
        });

        fs.getServidor().Post("/" + std::string(uri), [this](const httplib::Request &req, httplib::Response &res)
        {
            fs.executarPeticion(req, res, [this](const httplib::Request &req, httplib::Response &res){ return this->PostObxetoEstudo(req, res);});
        });

        fs.getServidor().Put("/" + std::string(uri), [this](const httplib::Request &req, httplib::Response &res)
        {
            fs.executarPeticion(req, res, [this](const httplib::Request &req, httplib::Response &res){ return this->PutObxetoEstudo(req, res);});
        });

        fs.getServidor().Delete("/" + std::string(uri), [this](const httplib::Request &req, httplib::Response &res)
        {
            fs.executarPeticion(req, res, [this](const httplib::Request &req, httplib::Response &res){ return this->DeleteObxetoEstudo(req, res);});
        });
    }

private:
    void GetObxetoEstudo(const httplib::Request& req, httplib::Response& res)
    {
        // Coller a conexión asociada a un token específico
        Sesion c = fs.obterSesionUsuario(req);
        std::vector<T> resultados;

        if (!req.body.empty())
        {
            // Se temos un corpo, asumimos que o cliente quere buscar algo
            nlohmann::json j = nlohmann::json::parse(req.body);
            T parametros = j.get<T>();
            resultados = c.buscarInventario(parametros);
        }
        else
            resultados = c.listarInventario<T>();

        if(resultados.empty())
        {
            res.status = 204;
            return;
        }

        res.status = 200;
        nlohmann::json valores = resultados;
        res.set_content(valores.dump(), "application/json");
    }

    void PostObxetoEstudo(const httplib::Request& req, httplib::Response& res)
    {
        // Coller a conexión asociada a un token específico
        Sesion c = fs.obterSesionUsuario(req);

        if (req.body.empty())
        {
            res.status = 422;

            const nlohmann::json j =
            {
                {"error", "Requírese mandar un obxeto no corpo"}
            };

            res.set_content(j.dump(), "application/json");

            return;
        }

        nlohmann::json j = nlohmann::json::parse(req.body);
        T inicial = j.at(0).get<T>();

        if(c.buscarInventario(inicial).empty())
        {
            res.status = 404;
            const nlohmann::json j =
            {
                {"error", "Obxecto a modificar non existente"}
            };

            res.set_content(j.dump(), "application/json");

            return;
        }

        T final = j.at(1).get<T>();
        c.modificarInventario(inicial, final);

        res.status = 200;
    }

    void PutObxetoEstudo(const httplib::Request& req, httplib::Response& res)
    {
        // Coller a conexión asociada a un token específico
        Sesion c = fs.obterSesionUsuario(req);

        if (req.body.empty())
        {
            res.status = 422;
            return;
        }

        nlohmann::json j = nlohmann::json::parse(req.body);
        T valor = j.get<T>();
        c.engadirInventario<T>(valor);

        res.status = 201;
        res.set_content(nlohmann::json(valor).dump(), "application/json");
    }

    void DeleteObxetoEstudo(const httplib::Request& req, httplib::Response& res)
    {
        // Coller a conexión asociada a un token específico
        Sesion c = fs.obterSesionUsuario(req);

        if (req.body.empty())
        {
            res.status = 400;
            const nlohmann::json j =
            {
                {"error", "Requírese mandar un obxeto no corpo"}
            };

            res.set_content(j.dump(), "application/json");

            return;
        }

        nlohmann::json j = nlohmann::json::parse(req.body);
        T valor = j.get<T>();

        if(c.buscarInventario(valor).empty())
        {
            res.status = 404;
            const nlohmann::json j =
            {
                {"error", "Obxecto a borrar non existente"}
            };

            res.set_content(j.dump(), "application/json");

            return;
        }

        c.eliminarInventario(valor);

        res.status = 200;
    }
};

#endif // XESTIONADORPETICIONSOBXETOESTUDO_H
