    #ifndef USUARIODAO_H
#define USUARIODAO_H
#include <vector>
#include "idao.h"
#include <usuario.h>
#include <nanodbc/nanodbc.h>

class UsuarioDAO : public IDAO<Usuario>
{
public:
    UsuarioDAO();

    std::vector<Usuario> listarInventario(nanodbc::connection& con) override;

    std::vector<Usuario> buscarInventario(const Usuario& parametros, nanodbc::connection& con) override;

    void engadirInventario(Usuario& parametros, nanodbc::connection& con) override;

    void modificarInventario(const Usuario& inicial, Usuario& final, nanodbc::connection& con) override;

    void eliminarInventario(const Usuario& parametros, nanodbc::connection& con) override;

private:

    void construirParametrosConsulta(const Usuario& parametro, std::string& texto) override;
    void construirParametrosActualizacion(const Usuario& inicial, Usuario& final, std::string& texto) override;
    nanodbc::result ligarParametros(const Usuario& parametro, nanodbc::statement& consulta, const bool actualizacion = false) override;
    void ligarParametros(const Usuario& inicial, const Usuario& final, nanodbc::statement& consulta) override;
};

#endif // USUARIODAO_H
