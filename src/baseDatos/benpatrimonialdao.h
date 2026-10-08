#ifndef BENPATRIMONIALDAO_H
#define BENPATRIMONIALDAO_H
#include "idaovisualizable.h"
#include "materialdao.h"
#include "motivodecorativodao.h"
#include <benpatrimonial.h>
#include <nanodbc/nanodbc.h>

class BenPatrimonialDAO : public IDAOVisualizable<BenPatrimonial>
{
public:
    BenPatrimonialDAO();
    BenPatrimonialDAO(const MaterialDAO &materialDao, const MotivoDecorativoDAO &motivoDecorativoDao);

    std::vector<BenPatrimonial> listarInventario(nanodbc::connection& con) override;

    std::vector<BenPatrimonial> buscarInventario(const BenPatrimonial& parametros, nanodbc::connection& con) override;

    void engadirInventario(BenPatrimonial& parametros, nanodbc::connection& con) override;

    void modificarInventario(const BenPatrimonial& inicial, BenPatrimonial& final, nanodbc::connection& con) override;

    void eliminarInventario(const BenPatrimonial& parametros, nanodbc::connection& con) override;

    std::unique_ptr<Imaxe> obterImaxe(const BenPatrimonial& parametros, nanodbc::connection &con) override;

    void rexistrarImaxe(const BenPatrimonial& parametros, const Imaxe& imaxe, nanodbc::connection& con) override;

    void eliminarImaxe(const BenPatrimonial& parametros, nanodbc::connection &con) override;

private:
    MaterialDAO materialDao;
    MotivoDecorativoDAO motivoDecorativoDao;

    void construirParametrosConsulta(const BenPatrimonial& parametro, std::string& texto) override;
    void construirParametrosActualizacion(const BenPatrimonial& inicial, BenPatrimonial& final, std::string& texto) override;
    nanodbc::result ligarParametros(const BenPatrimonial& parametro, nanodbc::statement& consulta, const bool actualizacion = false) override;
    void ligarParametros(const BenPatrimonial& inicial, const BenPatrimonial& final, nanodbc::statement& consulta) override;

    friend class EsculturaDAO;
};

#endif // BENPATRIMONIALDAO_H
