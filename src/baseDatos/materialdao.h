#ifndef MATERIALDAO_H
#define MATERIALDAO_H
#include "idaocomponedor.h"
#include <benpatrimonial.h>
#include <escultura.h>
#include <lapida.h>
#include <material.h>
#include <nanodbc/nanodbc.h>

class MaterialDAO : public IDAOComponedor<Material>
{
public:
    MaterialDAO();

    std::vector<Material> listarInventario(nanodbc::connection& con) override;

    std::vector<Material> buscarInventario(const Material& parametros, nanodbc::connection& con) override;

    void engadirInventario(Material& parametros, nanodbc::connection& con) override;

    void modificarInventario(const Material& inicial, Material& final, nanodbc::connection& con) override;

    void eliminarInventario(const Material& parametros, nanodbc::connection& con) override;

    void asociarComponentesElemento(const BenPatrimonial& elemento, nanodbc::connection& con) override;
    void asociarComponentesElemento(const Escultura& elemento, nanodbc::connection& con) override;
    void asociarComponentesElemento(const Lapida& elemento, nanodbc::connection& con) override;

    void modificarComponentesElemento(const BenPatrimonial& inicial, const BenPatrimonial& final, nanodbc::connection& con) override;
    void modificarComponentesElemento(const Escultura& inicial, const Escultura& final, nanodbc::connection& con) override;
    void modificarComponentesElemento(const Lapida& inicial, const Lapida& final, nanodbc::connection& con) override;

    std::vector<Material> obterComponentesElemento(const BenPatrimonial& elemento, nanodbc::connection& con) override;
    std::vector<Material> obterComponentesElemento(const Escultura& elemento, nanodbc::connection& con) override;
    std::vector<Material> obterComponentesElemento(const Lapida& elemento, nanodbc::connection& con) override;

protected:
    void construirParametrosConsulta(const Material& parametro, std::string& texto) override;
    void construirParametrosActualizacion(const Material& inicial, Material& final, std::string& texto) override;
    nanodbc::result ligarParametros(const Material& parametro, nanodbc::statement& consulta, const bool actualizacion = false) override;
    void ligarParametros(const Material& inicial, const Material& final, nanodbc::statement& consulta) override;
};

#endif // MATERIALDAO_H
