#ifndef LAPIDADAO_H
#define LAPIDADAO_H
#include "idaovisualizable.h"
#include "materialdao.h"
#include "motivodecorativodao.h"
#include <lapida.h>
#include <nanodbc/nanodbc.h>

class LapidaDAO : public IDAOVisualizable<Lapida>
{
public:
    LapidaDAO();
    LapidaDAO(const MaterialDAO &materialDao, const MotivoDecorativoDAO &motivoDecorativoDao);

    std::vector<Lapida> listarInventario(nanodbc::connection& con) override;

    std::vector<Lapida> buscarInventario(const Lapida& parametros, nanodbc::connection& con) override;

    void engadirInventario(Lapida& parametros, nanodbc::connection& con) override;

    void modificarInventario(const Lapida& inicial, Lapida& final, nanodbc::connection& con) override;

    void eliminarInventario(const Lapida& parametros, nanodbc::connection& con) override;

    std::unique_ptr<Imaxe> obterImaxe(const Lapida& parametros, nanodbc::connection& con) override;

    void rexistrarImaxe(const Lapida& parametros, const Imaxe& imaxe, nanodbc::connection& con) override;

    void eliminarImaxe(const Lapida& parametros, nanodbc::connection& con) override;

protected:
    MaterialDAO materialDao;
    MotivoDecorativoDAO motivoDecorativoDao;

    void construirParametrosConsulta(const Lapida& parametro, std::string& texto) override;
    void construirParametrosActualizacion(const Lapida& inicial, Lapida& final, std::string& texto) override;
    nanodbc::result ligarParametros(const Lapida& parametro, nanodbc::statement& consulta, const bool insercion = false) override;
    void ligarParametros(const Lapida& inicial, const Lapida& final, nanodbc::statement& consulta) override;
};

#endif // LAPIDADAO_H
