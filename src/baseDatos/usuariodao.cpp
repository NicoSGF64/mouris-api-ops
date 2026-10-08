#include "usuariodao.h"
#include <string>

UsuarioDAO::UsuarioDAO()
{
    alias = 'u';
}

void UsuarioDAO::construirParametrosConsulta(const Usuario& parametro, std::string& texto)
{
    construirParametroConsulta(parametro.getNomeUsuario(), texto, "nome_usuario", false);
    if (parametro.getTipo())
        construirParametroConsulta(parametro.getTipo().value().getNomeTipo(), texto, "tipo_usuario", true);

    // Limpar o "AND " que sobra
    if (!texto.empty())
        texto.erase(texto.length() - 5);
}


void UsuarioDAO::construirParametrosActualizacion(const Usuario& inicial, Usuario& final, std::string& texto)
{
    construirParametroActualizacion(final.getNomeUsuario(), texto, "nome_usuario");
    construirParametroActualizacion(final.getTipo(), texto, "tipo_usuario");

    // Quitar a coma extra que sobra ao realizar construirParametroActualizacion e poñer un espazo para o WHERE
    if (!texto.empty())
        texto.back() = ' ';
}

nanodbc::result UsuarioDAO::ligarParametros(const Usuario& parametro, nanodbc::statement& consulta, const bool actualizacion)
{
    unsigned short posLigar = 0;
    const auto nomeUsuario = parametro.getNomeUsuario();
    const auto tipo = parametro.getNomeTipo();

    ligarParametro(nomeUsuario, consulta, posLigar, actualizacion);
    ligarParametro(tipo, consulta, posLigar, actualizacion);

    return consulta.execute();
}

void UsuarioDAO::ligarParametros(const Usuario& inicial, const Usuario& final, nanodbc::statement& consulta)
{
    unsigned short posLigar = 0;
    const auto nomeUsuarioFinal = final.getNomeUsuario();
    const auto tipoFinal = final.getNomeTipo();

    ligarParametro(nomeUsuarioFinal, consulta, posLigar);
    ligarParametro(tipoFinal, consulta, posLigar);

    const auto nomeUsuarioInicial = inicial.getNomeUsuario();
    ligarParametro(nomeUsuarioInicial, consulta, posLigar, false);

    consulta.execute();
}

std::vector<Usuario> UsuarioDAO::listarInventario(nanodbc::connection& con)
{
    nanodbc::statement exec(con);
    constexpr std::string_view textoExec {
            "SELECT * "
            "FROM usuarios u"};

    exec.prepare(textoExec.data());
    auto resultado = exec.execute();

    std::vector<Usuario> obtidoExecucion{};

    while (resultado.next())
    {
        obtidoExecucion.push_back(Usuario(resultado.get<std::string>("nome_usuario"),
                                         TipoUsuario(resultado.get<std::string>("tipo_usuario"))));
    }

    return obtidoExecucion;
}

std::vector<Usuario> UsuarioDAO::buscarInventario(const Usuario& parametros, nanodbc::connection& con)
{
    nanodbc::statement exec(con);
    std::string textoExec {
        "SELECT * "
        "FROM usuarios u "
        "WHERE "};

    construirParametrosConsulta(parametros, textoExec);

    exec.prepare(textoExec);

    auto resultado = ligarParametros(parametros, exec, false);

    std::vector<Usuario> obtidoExecucion{};

    while (resultado.next())
    {
        obtidoExecucion.push_back(Usuario(resultado.get<std::string>("nome_usuario"),
                                          TipoUsuario(resultado.get<std::string>("tipo_usuario"))));
    }

    return obtidoExecucion;
}

void UsuarioDAO::engadirInventario(Usuario& parametros, nanodbc::connection& con)
{
    // ODBC non permite PreparedStaments coa manipulación de usuarios (polo menos do nome e rol ao non ter comiñas) así que hai que validar manualmente con esta chapuza
    if((parametros.getNomeUsuario().value().find("\"") != std::string::npos)
    || (parametros.getNomeUsuario().value().find("\'") != std::string::npos)
    || (parametros.getNomeUsuario().value().find(":")  != std::string::npos)
    || (parametros.getContrasinal().value().find("\"") != std::string::npos)
    || (parametros.getContrasinal().value().find("\'") != std::string::npos)
    || (parametros.getContrasinal().value().find(":")) != std::string::npos)
        throw std::runtime_error("Non se permite comiñas ou dous puntos nos campos dun usuario");


    nanodbc::transaction trans(con);
    nanodbc::statement exec(con);
    std::string textoExec {
        "INSERT INTO usuarios(nome_usuario, tipo_usuario) "
        "VALUES(?, ?)"};

    exec.prepare(textoExec.data());

    ligarParametros(parametros, exec, true);

    if(parametros.getNomeUsuario())
    textoExec =
        "CREATE USER " + parametros.getNomeUsuario().value() +
        " WITH ENCRYPTED PASSWORD \'" + parametros.getContrasinal().value() + '\'' +
        " IN ROLE " + parametros.getNomeTipo().value();

    if(parametros.getTipo().value().getTipo() == TipoUsuario::administradorSistema)
        textoExec.append(" WITH GRANT OPTION");

    exec.prepare(textoExec.data());

    exec.execute();

    trans.commit();
}

void UsuarioDAO::modificarInventario(const Usuario& inicial, Usuario& final, nanodbc::connection& con)
{
    // ODBC non permite PreparedStaments coa manipulación de usuarios (polo menos do nome e rol ao non ter comiñas) así que hai que validar manualmente con esta chapuza
    // TODO: std::basic_string<>.contains() sálvame
    if((inicial.getNomeUsuario().value().find("\"") != std::string::npos)
    || (inicial.getNomeUsuario().value().find("\'") != std::string::npos)
    || (inicial.getNomeUsuario().value().find(":") != std::string::npos)
    || (inicial.getContrasinal().value().find("\"") != std::string::npos)
    || (inicial.getContrasinal().value().find("\'") != std::string::npos)
    || (inicial.getContrasinal().value().find(":") != std::string::npos)
    || (final.getNomeUsuario().value().find("\"") != std::string::npos)
    || (final.getNomeUsuario().value().find("\'") != std::string::npos)
    || (final.getNomeUsuario().value().find(":") != std::string::npos)
    || (final.getContrasinal().value().find("\"") != std::string::npos)
    || (final.getContrasinal().value().find("\'") != std::string::npos)
    || (final.getContrasinal().value().find(":")) != std::string::npos)
        throw std::runtime_error("Non se permite comiñas ou dous puntos nos campos dun usuario");

    nanodbc::transaction trans(con);

    nanodbc::statement exec(con);
    std::string textoExec {
        "UPDATE usuarios u "
        "SET"};

    construirParametrosActualizacion(inicial, final, textoExec);
    textoExec += "WHERE nome_usuario = ?";

    exec.prepare(textoExec.data());

    ligarParametros(inicial, final, exec);

    if(final.getContrasinal())
    {
        textoExec =
            "ALTER USER " + inicial.getNomeUsuario().value() +
            " WITH ENCRYPTED PASSWORD \'" + final.getContrasinal().value() + '\'';

        exec.prepare(textoExec.data());

        exec.execute();
    }

    if(inicial.getNomeUsuario() && final.getNomeUsuario())
    {
        if(inicial.getNomeUsuario().value() != final.getNomeUsuario().value())
        {
            textoExec = "ALTER USER " + inicial.getNomeUsuario().value() +
                        " RENAME TO " + final.getNomeUsuario().value();

            exec.prepare(textoExec.data());

            exec.execute();
        }
    }

    trans.commit();
}

void UsuarioDAO::eliminarInventario(const Usuario& parametros, nanodbc::connection& con)
{
    // ODBC non permite PreparedStaments coa manipulación de usuarios (polo menos do nome e rol ao non ter comiñas) así que hai que validar manualmente con esta chapuza
    if((parametros.getNomeUsuario().value().find("\"") != std::string::npos)
    || (parametros.getNomeUsuario().value().find("\'") != std::string::npos)
    || (parametros.getNomeUsuario().value().find(":")  != std::string::npos)
    || (parametros.getContrasinal().value().find("\"") != std::string::npos)
    || (parametros.getContrasinal().value().find("\'") != std::string::npos)
    || (parametros.getContrasinal().value().find(":")) != std::string::npos)
        throw std::runtime_error("Non se permite comiñas ou dous puntos nos campos dun usuario");

    nanodbc::transaction trans(con);

    nanodbc::statement exec(con);
    std::string textoExec {
        "DELETE FROM usuarios u "
        "WHERE nome_usuario = ?"
    };

    exec.prepare(textoExec.data());

    unsigned short pos = 0;
    ligarParametro(parametros.getNomeUsuario(), exec, pos);

    exec.execute();

    textoExec =
        "DROP USER " + parametros.getNomeUsuario().value();

    exec.prepare(textoExec.data());

    pos = 0;
    ligarParametro(parametros.getNomeUsuario(), exec, pos);

    exec.execute();

    trans.commit();
}
