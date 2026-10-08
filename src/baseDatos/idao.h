#ifndef IDAO_H
#define IDAO_H
#include <imaxe/imaxe.h>
#include <vector>
#include <estadoConservacion.h>
#include <tipousuario.h>
#include "nanodbc/nanodbc.h"

template<typename T>
class IDAO
{
public:
    IDAO() = default;

    virtual std::vector<T> listarInventario(nanodbc::connection& con) = 0;

    virtual std::vector<T> buscarInventario(const T& parametros, nanodbc::connection& con) = 0;

    virtual void engadirInventario(T& parametros, nanodbc::connection& con) = 0;

    virtual void modificarInventario(const T& inicial, T& final, nanodbc::connection& con) = 0;

    virtual void eliminarInventario(const T& parametros, nanodbc::connection& con) = 0;

protected:
    std::string alias{};

    virtual void construirParametrosConsulta(const T& parametro, std::string& texto) = 0;
    virtual void construirParametrosActualizacion(const T& inicial, T& final, std::string& texto) = 0;
    virtual nanodbc::result ligarParametros(const T& parametro, nanodbc::statement& consulta, const bool actualizacion = false) = 0;
    virtual void ligarParametros(const T& inicial, const T& final, nanodbc::statement& consulta) = 0;

    template<typename U>
    constexpr void construirParametroConsulta(const std::optional<U>& opcion, std::string& texto, const std::string& nomeOpcion)
    {
        if (opcion)
            texto += alias + "." + nomeOpcion + " = ? AND ";
    }

    constexpr void construirParametroConsulta(const std::optional<std::string>& opcion, std::string& texto, const std::string& nomeOpcion, bool exacto = true)
    {
        if (opcion)
            texto += alias + "." + nomeOpcion + (exacto ? " = ?" : " LIKE '%' || ? || '%'") + " AND ";
    }

    constexpr void construirParametroConsulta(const std::optional<estadoConservacion>& opcion, std::string& texto, const std::string& nomeOpcion, bool exacto = true)
    {
        if(opcion)
            texto += alias + "." + nomeOpcion + "_marca = ? AND " + alias + "." + nomeOpcion + "_razonamento" + (exacto ? " = ?" : " LIKE '%' || ? || '%'") + " AND ";
    }

    constexpr void construirParametroConsulta(std::string& texto, const std::string& nomeOpcion, bool exacto = true)
    {
        texto += alias + "." + nomeOpcion + (exacto ? " = ?" : " LIKE '%' || ? || '%'") + " AND ";
    }

    template<typename U>
    static constexpr void construirParametroActualizacion(const U& opcion, std::string& texto, const std::string& nomeOpcion)
    {
        texto += " " + nomeOpcion + " = ?,";
    }

    template<typename U>
    static constexpr void construirParametroActualizacion(const std::optional<U>& opcion, std::string& texto, const std::string& nomeOpcion)
    {
        if (opcion)
            texto += " " + nomeOpcion + " = ?,";
    }

    template<typename U>
    static constexpr void ligarParametro(const U& ligadura, nanodbc::statement& consulta, unsigned short& pos)
    {
        consulta.bind(pos, std::addressof(ligadura));
        pos++;
    }

    static constexpr void ligarParametro(const std::string& ligadura, nanodbc::statement& consulta, unsigned short& pos)
    {
        consulta.bind(pos, ligadura.c_str());
        pos++;
    }

    static constexpr void ligarParametro(const estadoConservacion& ligadura, nanodbc::statement& consulta, unsigned short& pos)
    {
        consulta.bind(pos, ligadura.marca.c_str());
        consulta.bind(pos + 1, ligadura.razonamento.c_str());
        pos += 2;
    }

    template<typename U>
    static constexpr void ligarParametro(const std::optional<U>& ligadura, nanodbc::statement& consulta, unsigned short& pos, const bool insercion = false)
    {
        if (ligadura)
        {
            consulta.bind(pos, std::addressof(ligadura.value()));
            pos++;
        }
        else if (insercion)
        {
            consulta.bind_null(pos);
            pos++;
        }
    }

    static constexpr void ligarParametro(const std::optional<std::string>& ligadura, nanodbc::statement& consulta, unsigned short& pos, const bool insercion = false)
    {
        if (ligadura)
        {
            consulta.bind(pos, ligadura.value().c_str());
            pos++;
        }
        else if (insercion)
        {
            consulta.bind_null(pos);
            pos++;
        }
    }

    static constexpr void ligarParametro(const std::optional<estadoConservacion>& ligadura, nanodbc::statement& consulta, unsigned short& pos, const bool insercion = false)
    {
        if (ligadura)
        {
            consulta.bind(pos, ligadura.value().marca.c_str());
            consulta.bind(pos + 1, ligadura.value().razonamento.c_str());
            pos += 2;
        }
        else if (insercion)
        {
            consulta.bind_null(pos);
            consulta.bind_null(pos + 1);
            pos += 2;
        }
    }

    static constexpr void ligarParametro(const std::optional<TipoUsuario>& ligadura, nanodbc::statement& consulta, unsigned short& pos, const bool insercion = false)
    {
        if (ligadura)
        {
            consulta.bind(pos, ligadura.value().getNomeTipo().c_str());
            pos++;
        }
        else if (insercion)
        {
            consulta.bind_null(pos);
            pos++;
        }
    }

    template<typename U>
    static constexpr std::optional<U> obterAtributo(const nanodbc::result res, const std::string& nome)
    {
        if (!res.is_null(nome))
            return res.get<U>(nome);
        else
            return std::optional<U>{};
    }
};

#endif // IDAO_H
