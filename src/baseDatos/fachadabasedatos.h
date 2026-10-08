#ifndef FACHADABASEDATOS_H
#define FACHADABASEDATOS_H
#include <vector>
#include <imaxe/imaxe.h>
#include <nanodbc/nanodbc.h>
#include <usuario.h>
#include "fabricadao.h"
#include "imaxedao.h"

class FachadaBaseDatos
{
public:
    FachadaBaseDatos() = default;
    FachadaBaseDatos(const std::string& dsn, const Usuario& u);

    template<typename T>
    [[nodiscard]] std::vector<T> listarInventario()
    {
        typename FabricaDAO<T>::dao dao;
        return dao.listarInventario(con);
    }

    template<typename T>
    [[nodiscard]] std::vector<T> buscarInventario(const T& parametros)
    {
        typename FabricaDAO<T>::dao dao;
        return dao.buscarInventario(parametros, con);
    }

    template <typename T>
    [[nodiscard]] std::unique_ptr<Imaxe> buscarImaxe(const T& parametros)
    {
        ImaxeDAO<T> dao;
        return dao.buscarInventario(parametros, con);
    }

    template<typename T>
    void engadirInventario(T &parametros)
    {
        typename FabricaDAO<T>::dao dao;
        dao.engadirInventario(parametros, con);
    }

    template<typename T>
    void engadirInventario(const Imaxe &imaxe, T &parametros)
    {
        ImaxeDAO<T> dao;
        return dao.engadirInventario(imaxe, parametros, con);
    }

    template<typename T>
    void modificarInventario(const T& inicial, T& final)
    {
        typename FabricaDAO<T>::dao dao;
        dao.modificarInventario(inicial, final, con);
    }

    template<typename T>
    void modificarInventario(const Imaxe &imaxe, const T &parametros)
    {
        ImaxeDAO<T> dao;
        dao.modificarInventario(imaxe, parametros, con);
    }

    template<typename T>
    void eliminarInventario(const T& parametros)
    {
        typename FabricaDAO<T>::dao dao;
        dao.eliminarInventario(parametros, con);
    }

    template <typename T>
    void eliminarImaxe(const T& parametros)
    {
        ImaxeDAO<T> dao;
        dao.eliminarInventario(parametros, con);
    }

private:
    nanodbc::connection con;
    std::string dsnBBDD;
};

#endif // FACHADABASEDATOS_H
