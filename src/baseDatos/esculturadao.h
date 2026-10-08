#ifndef ESCULTURADAO_H
#define ESCULTURADAO_H
#include "benpatrimonialdao.h"
#include <escultura.h>
#include <nanodbc/nanodbc.h>

class EsculturaDAO: public IDAOVisualizable<Escultura>
{
public:
    EsculturaDAO();

    std::vector<Escultura> listarInventario(nanodbc::connection& con) override;

    std::vector<Escultura> buscarInventario(const Escultura& parametros, nanodbc::connection& con) override;

    void engadirInventario(Escultura& parametros, nanodbc::connection& con) override;

    void modificarInventario(const Escultura& inicial, Escultura& final, nanodbc::connection& con) override;

    void eliminarInventario(const Escultura& parametros, nanodbc::connection& con) override;

    std::unique_ptr<Imaxe> obterImaxe(const Escultura& parametros, nanodbc::connection &con) override;

    void rexistrarImaxe(const Escultura& parametros, const Imaxe& imaxe, nanodbc::connection& con) override;

    void eliminarImaxe(const Escultura& parametros, nanodbc::connection &con) override;

private:
    BenPatrimonialDAO benPatrimonialDao;
    MaterialDAO materialDao;
    MotivoDecorativoDAO motivoDecorativoDao;

    void construirParametrosConsulta(const Escultura& parametro, std::string& texto) override;
    void construirParametrosActualizacion(const Escultura& inicial, Escultura& final, std::string& texto) override;
    nanodbc::result ligarParametros(const Escultura& parametro, nanodbc::statement& consulta, const bool actualizacion = false) override;
    void ligarParametros(const Escultura& inicial, const Escultura& final, nanodbc::statement& consulta) override;
};

#endif // ESCULTURADAO_H
