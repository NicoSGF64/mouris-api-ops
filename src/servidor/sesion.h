#ifndef SESION_H
#define SESION_H
#include <chrono>
#include <fachadabasedatos.h>
#include <usuario.h>
#include "errosautentificacion.h"

class Sesion
{
public:
    Sesion() = delete;
    Sesion(const std::string& dsn, const Usuario& usuario);

    static constexpr unsigned int minutosInvalidacion = 30;

    bool serValida() const;

    bool autenticar(const std::string_view nome, const std::string_view contrasinal);

    template<typename T>
    std::vector<T> listarInventario(bool permitirSesionCaducada = false)
    {
        if (!serValida() && !permitirSesionCaducada)
            throw ErroSesionCaducada();

        ultimaInactividade = std::chrono::steady_clock::now();
        return xestionador.listarInventario<T>();
    }

    template<typename T>
    std::vector<T> buscarInventario(const T &parametros, bool permitirSesionCaducada = false)
    {
        if (!serValida() && !permitirSesionCaducada)
            throw ErroSesionCaducada();

        ultimaInactividade = std::chrono::steady_clock::now();
        return xestionador.buscarInventario(parametros);
    }

    template <typename T>
    [[nodiscard]] std::unique_ptr<Imaxe> buscarImaxe(const T& parametros, bool permitirSesionCaducada = false)
    {
        if (!serValida() && !permitirSesionCaducada)
            throw ErroSesionCaducada();

        ultimaInactividade = std::chrono::steady_clock::now();
        return xestionador.buscarImaxe(parametros);
    }

    template<typename T>
    void engadirInventario(T &parametros, bool permitirSesionCaducada = false)
    {
        if (!serValida() && !permitirSesionCaducada)
            throw ErroSesionCaducada();

        ultimaInactividade = std::chrono::steady_clock::now();
        xestionador.engadirInventario(parametros);
    }

    template<typename T>
    void modificarInventario(const T &inicial, T &final, bool permitirSesionCaducada = false)
    {
        if (!serValida() && !permitirSesionCaducada)
            throw ErroSesionCaducada();

        ultimaInactividade = std::chrono::steady_clock::now();
        xestionador.modificarInventario(inicial, final);
    }

    template<typename T>
    void modificarInventario(const Imaxe &imaxe, const T &parametros, bool permitirSesionCaducada = false)
    {
        if (!serValida() && !permitirSesionCaducada)
            throw ErroSesionCaducada();

        ultimaInactividade = std::chrono::steady_clock::now();
        xestionador.modificarInventario(imaxe, parametros);
    }

    template<typename T>
    void eliminarInventario(const T &parametros, bool permitirSesionCaducada = false)
    {
        if (!serValida() && !permitirSesionCaducada)
            throw ErroSesionCaducada();

        ultimaInactividade = std::chrono::steady_clock::now();
        xestionador.eliminarInventario(parametros);
    }

    template <typename T>
    void eliminarImaxe(T& parametros, bool permitirSesionCaducada = false)
    {
        if (!serValida() && !permitirSesionCaducada)
            throw ErroSesionCaducada();

        ultimaInactividade = std::chrono::steady_clock::now();
        xestionador.eliminarImaxe(parametros);
    }

    Usuario getUsuario() const;
    void setUsuario(const Usuario &newUsuario);

private:
    std::chrono::time_point<std::chrono::steady_clock> ultimaInactividade;
    Usuario usuario;
    FachadaBaseDatos xestionador;
};

#endif // SESION_H
