#ifndef IMAXEDAO_H
#define IMAXEDAO_H
#include <idao.h>
#include <imaxe/errosimaxe.h>
#include <imaxe/imaxe.h>
#include <obxetoestudo.h>
#include "fabricadao.h"

template <typename T>
class ImaxeDAO
{
public:
    static std::unique_ptr<Imaxe> buscarInventario(const T& obxeto, nanodbc::connection& con)
    {
        static_assert(std::is_base_of<ObxetoEstudo, T>::value, "T non é un T válido para que se teña que xestionar peticións deste");

        typename FabricaDAO<T>::dao dao;
        return dao.obterImaxe(obxeto, con);
    }

    static void engadirInventario(const Imaxe &parametros, T &obxeto, nanodbc::connection &con)
    {
        static_assert(std::is_base_of<ObxetoEstudo, T>::value, "T non é un T válido para que se teña que xestionar peticións deste");

        if(!parametros.serValida())
            throw ErroImaxeInvalida();

        typename FabricaDAO<T>::dao dao;
        dao.rexistrarImaxe(obxeto, parametros, con);
    }

    static void modificarInventario(const Imaxe &parametros, const T &obxeto, nanodbc::connection &con)
    {
        static_assert(std::is_base_of<ObxetoEstudo, T>::value, "T non é un T válido para que se teña que xestionar peticións deste");

        if(!parametros.serValida())
            throw ErroImaxeInvalida();

        typename FabricaDAO<T>::dao dao;
        dao.rexistrarImaxe(obxeto, parametros, con);
    }

    static void eliminarInventario(const T &obxeto, nanodbc::connection &con)
    {
        static_assert(std::is_base_of<ObxetoEstudo, T>::value, "T non é un T válido para que se teña que xestionar peticións deste");

        typename FabricaDAO<T>::dao dao;
        dao.eliminarImaxe(obxeto, con);
    }
};

#endif // IMAXEDAO_H
