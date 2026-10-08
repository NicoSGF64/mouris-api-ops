#ifndef XESTIONADORPETICIONSIMAXE_H
#define XESTIONADORPETICIONSIMAXE_H
#include "imaxe/fabricaimaxe.h"
#include "ixestionadorpeticions.h"

template <typename T>
class XestionadorPeticionsImaxe : public IXestionadorPeticions
{
public:
    XestionadorPeticionsImaxe() = delete;
    explicit XestionadorPeticionsImaxe(IServidor &fs) : IXestionadorPeticions(fs) { };

    void configurarPeticions(std::string_view uri) override
    {
        fs.getServidor().Get("/imaxes/" + std::string(uri), [this](const httplib::Request &req, httplib::Response &res)
        {
            fs.executarPeticion(req, res, [this](const httplib::Request &req, httplib::Response &res){ return this->obterImaxe(req, res);});
        });

        fs.getServidor().Post("/imaxes/" + std::string(uri), [this](const httplib::Request &req, httplib::Response &res, const httplib::ContentReader &content_reader)
        {
            fs.executarPeticion(req, res, [this, content_reader](const httplib::Request &req, httplib::Response &res){ return this->modificarImaxe(req, res, content_reader);});
        });

        fs.getServidor().Put("/imaxes/" + std::string(uri), [this](const httplib::Request &req, httplib::Response &res, const httplib::ContentReader &content_reader)
        {
            fs.executarPeticion(req, res, [this, content_reader](const httplib::Request &req, httplib::Response &res){ return this->modificarImaxe(req, res, content_reader);});
        });

        fs.getServidor().Delete("/imaxes/" + std::string(uri), [this](const httplib::Request &req, httplib::Response &res)
        {
            fs.executarPeticion(req, res, [this](const httplib::Request &req, httplib::Response &res){ return this->eliminarImaxe(req, res);});
        });
    }

private:
    void obterImaxe(const httplib::Request& req, httplib::Response& res)
    {
        // Coller a conexión asociada a un token específico
        Sesion c = fs.obterSesionUsuario(req);

        if (req.body.empty())
        {
            res.status = 422;
            const nlohmann::json j =
            {
                {"error", "Falta o obxecto necesario para recuperar a imaxe"}
            };

            res.set_content(j.dump(), "application/json");

            return;
        }

        nlohmann::json j = nlohmann::json::parse(req.body);
        T valor = j.get<T>();

        std::unique_ptr<Imaxe> i = c.buscarImaxe(valor);

        if (i == nullptr)
        {
            res.status = 204;
            return;
        }

        res.status = 200;

        auto datos = i->getDatos();

        res.set_content(std::string(datos.begin(), datos.end()), i->getMIME());
    }

    void modificarImaxe(const httplib::Request& req, httplib::Response& res, const httplib::ContentReader &content_reader)
    {
        // Coller a conexión asociada a un token específico
        Sesion c = fs.obterSesionUsuario(req);

        // Debe ser multipart con json cos datos to obxeto + imaxe a gardar
        if (!req.is_multipart_form_data())
        {
            res.status = 422;
            const nlohmann::json j =
            {
                {"error", "Requírese un tipo de contido de formulario multipart con JSON do obxeto e imaxe"}
            };

            res.set_content(j.dump(), "application/json");
            return;
        }

        /* Método bastante apañado de obter imaxes:
         * Recibimos de orixe un multipart/form-data que debe ter unha imaxe e un json
         * a imaxe sabemos que vai ser de tipo image/_____ pero o json, polo menos probando con
         * cURL era transformado en application/octet-stream. O que se fai é buscar estas cabeceiras,
         * marcandoas cun booleano (serValorjson e serImaxe) e en caso de ser deste tipo de cabeceira
         * o procesamos debidamente ao ser esparramado nun simple char* con size_t. Só cambiamos de tipo
         * de procesamento (o segundo lambda chámase varias veces por cabeceira por motivos fora do meu entendemento)
         * cando detectamos un novo encabezado (os datos do mesmo tipo son transmitidos de inicio a fin sen interrupción).
         * Polo mencionado enriba, creamos búferes que vaian apañando cada parte, e ao final os serializamos en datos.
         */

        bool serValorjson = false;
        bool serImaxe = false;

        nlohmann::json obxeto;

        std::string mimeImaxe;
        std::vector<uint8_t> datosImaxe;

        content_reader(
        [&](const httplib::FormData &file)
        {
            // Comprobar que datos andamos a mirar
            serValorjson = false;
            serImaxe = false;

            if (file.name == "json" && (file.content_type == "application/octet-stream" || file.content_type == "application/json"))
                serValorjson = true;
            else if (file.name == "imaxe" && file.content_type.starts_with("image/"))
            {
                serImaxe = true;
                mimeImaxe = file.content_type;
            }
            else
            {
                // Mandouse un tipo ou formato que non deberían
                return false;
            }

            return true;
        },
        // Execútase varias veces por cabeceira
        [&](const char *data, size_t len)
        {
            if (serValorjson)
            {
                // Técnicamente falla se o JSON ven en varios cachos
                try
                {
                    std::string s(data, len);
                    obxeto = nlohmann::json::parse(s);
                }
                catch (nlohmann::json::exception&)
                {
                    res.status = 422;
                    const nlohmann::json j =
                    {
                        {"error", "Obxecto descoñecido (JSON inválido)"}
                    };

                    res.set_content(j.dump(), "application/json");

                    return false;
                }

                return true;
            }
            else if (serImaxe)
            {
                datosImaxe.reserve(len);
                for (size_t i = 0; i < len; ++i)
                    datosImaxe.push_back(data[i]);

                return true;
            }

            return false;
        });

        try
        {
            FabricaImaxe fi;
            std::unique_ptr<Imaxe> imaxe = fi.fabricar(mimeImaxe, datosImaxe);
            c.modificarInventario(*imaxe, obxeto.get<T>());
        }
        catch (ErroImaxeInvalida&)
        {
            res.status = 422;
            const nlohmann::json j =
            {
                {"error", "Imaxe inválida"}
            };

            res.set_content(j.dump(), "application/json");
            return;
        }
        catch (ErroMIMEInvalido&)
        {
            res.status = 422;
            const nlohmann::json j =
            {
                {"error", "Formato de imaxe inválido (só se permite PNG ou JPEG)"}
            };

            res.set_content(j.dump(), "application/json");
            return;
        }
    }

    void eliminarImaxe(const httplib::Request& req, httplib::Response& res)
    {
        // Coller a conexión asociada a un token específico
        Sesion c = fs.obterSesionUsuario(req);

        if (req.body.empty())
        {
            res.status = 400;
            return;
        }

        nlohmann::json j = nlohmann::json::parse(req.body);
        const T valor = j.get<T>();

        c.eliminarImaxe(valor);
    }
};

#endif // XESTIONADORPETICIONSIMAXE_H
