#ifndef MOTIVODECORATIVODAO_H
#define MOTIVODECORATIVODAO_H
#include "idaocomponedor.h"
#include <motivodecorativo.h>
#include <nanodbc/nanodbc.h>

class MotivoDecorativoDAO : public IDAOComponedor<MotivoDecorativo>
{
public:
    MotivoDecorativoDAO();

    std::vector<MotivoDecorativo> listarInventario(nanodbc::connection& con) override;

    std::vector<MotivoDecorativo> buscarInventario(const MotivoDecorativo& parametros, nanodbc::connection& con) override;

    void engadirInventario(MotivoDecorativo& parametros, nanodbc::connection& con) override;

    void modificarInventario(const MotivoDecorativo& inicial, MotivoDecorativo& final, nanodbc::connection& con) override;

    void eliminarInventario(const MotivoDecorativo& parametros, nanodbc::connection& con) override;

    void asociarComponentesElemento(const BenPatrimonial& elemento, nanodbc::connection& con) override;
    void asociarComponentesElemento(const Escultura& elemento, nanodbc::connection& con) override;
    void asociarComponentesElemento(const Lapida& elemento, nanodbc::connection& con) override;

    void modificarComponentesElemento(const BenPatrimonial& inicial, const BenPatrimonial& final, nanodbc::connection& con) override;
    void modificarComponentesElemento(const Escultura& inicial, const Escultura& final, nanodbc::connection& con) override;
    void modificarComponentesElemento(const Lapida& inicial, const Lapida& final, nanodbc::connection& con) override;

    std::vector<MotivoDecorativo> obterComponentesElemento(const BenPatrimonial& elemento, nanodbc::connection& con) override;
    std::vector<MotivoDecorativo> obterComponentesElemento(const Escultura& elemento, nanodbc::connection& con) override;
    std::vector<MotivoDecorativo> obterComponentesElemento(const Lapida& elemento, nanodbc::connection& con) override;


protected:
    void construirParametrosConsulta(const MotivoDecorativo& parametro, std::string& texto) override;
    void construirParametrosActualizacion(const MotivoDecorativo& inicial, MotivoDecorativo& final, std::string& texto) override;
    nanodbc::result ligarParametros(const MotivoDecorativo& parametro, nanodbc::statement& consulta, const bool actualizacion = false) override;
    void ligarParametros(const MotivoDecorativo& inicial, const MotivoDecorativo& final, nanodbc::statement& consulta) override;
};

#endif // MOTIVODECORATIVODAO_H
