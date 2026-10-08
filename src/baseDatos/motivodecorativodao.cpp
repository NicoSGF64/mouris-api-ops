#include "motivodecorativodao.h"

MotivoDecorativoDAO::MotivoDecorativoDAO()
{
    alias = "md";
}

void MotivoDecorativoDAO::construirParametrosConsulta(const MotivoDecorativo& parametro, std::string& texto)
{
    construirParametroConsulta(parametro.getNome(), texto, "nome", true);

    // Limpar o "AND " que sobra
    if (!texto.empty())
        texto.erase(texto.length() - 5);
}


void MotivoDecorativoDAO::construirParametrosActualizacion(const MotivoDecorativo& inicial, MotivoDecorativo& final, std::string& texto)
{
    construirParametroActualizacion(final.getNome(), texto, "nome");

    // Quitar a coma extra que sobra ao realizar construirParametroActualizacion e poñer un espazo para o WHERE
    if (!texto.empty())
        texto.back() = ' ';
}

nanodbc::result MotivoDecorativoDAO::ligarParametros(const MotivoDecorativo& parametro, nanodbc::statement& consulta, const bool actualizacion)
{
    unsigned short posLigar = 0;
    const auto nomeMotivoDecorativo = parametro.getNome();

    ligarParametro(nomeMotivoDecorativo, consulta, posLigar, actualizacion);

    return consulta.execute();
}

void MotivoDecorativoDAO::ligarParametros(const MotivoDecorativo& inicial, const MotivoDecorativo& final, nanodbc::statement& consulta)
{
    unsigned short posLigar = 0;
    const auto nomeMotivoDecorativoFinal = final.getNome();

    ligarParametro(nomeMotivoDecorativoFinal, consulta, posLigar);

    const auto nomeMotivoDecorativoInicial = inicial.getNome();
    ligarParametro(nomeMotivoDecorativoInicial, consulta, posLigar, false);

    consulta.execute();
}

std::vector<MotivoDecorativo> MotivoDecorativoDAO::listarInventario(nanodbc::connection& con)
{
    nanodbc::statement exec(con);
    constexpr std::string_view textoExec {
        "SELECT * "
        "FROM motivos_decorativos mb"};

    exec.prepare(textoExec.data());
    auto resultado = exec.execute();

    std::vector<MotivoDecorativo> obtidoExecucion{};

    while (resultado.next())
        obtidoExecucion.push_back(MotivoDecorativo(resultado.get<std::string>("nome")));

    return obtidoExecucion;
}

std::vector<MotivoDecorativo> MotivoDecorativoDAO::buscarInventario(const MotivoDecorativo& parametros, nanodbc::connection& con)
{
    nanodbc::statement exec(con);
    std::string textoExec {
        "SELECT * "
        "FROM motivos_decorativos mb "
        "WHERE "};

    construirParametrosConsulta(parametros, textoExec);

    exec.prepare(textoExec);

    auto resultado = ligarParametros(parametros, exec, false);

    std::vector<MotivoDecorativo> obtidoExecucion{};

    while (resultado.next())
        obtidoExecucion.push_back(MotivoDecorativo(resultado.get<std::string>("nome")));

    return obtidoExecucion;
}

void MotivoDecorativoDAO::engadirInventario(MotivoDecorativo& parametros, nanodbc::connection& con)
{
    nanodbc::transaction trans(con);
    nanodbc::statement exec(con);
    std::string textoExec {
        "INSERT INTO motivos_decorativos(nome) "
        "VALUES(?, ?)"};

    exec.prepare(textoExec.data());

    ligarParametros(parametros, exec, true);
}

void MotivoDecorativoDAO::modificarInventario(const MotivoDecorativo& inicial, MotivoDecorativo& final, nanodbc::connection& con)
{
    nanodbc::statement exec(con);
    std::string textoExec {
        "UPDATE motivos_decorativos "
        "SET"};

    construirParametrosActualizacion(inicial, final, textoExec);
    textoExec += "WHERE nome = ?";

    exec.prepare(textoExec.data());

    ligarParametros(inicial, final, exec);
}

void MotivoDecorativoDAO::eliminarInventario(const MotivoDecorativo& parametros, nanodbc::connection& con)
{
    nanodbc::transaction trans(con);

    nanodbc::statement exec(con);
    std::string textoExec {
        "DELETE FROM motivos_decorativos mb "
        "WHERE nome = ?"
    };

    exec.prepare(textoExec.data());

    unsigned short pos = 0;
    ligarParametro(parametros.getNome(), exec, pos);

    exec.execute();
}

void MotivoDecorativoDAO::asociarComponentesElemento(const BenPatrimonial& elemento, nanodbc::connection& con)
{
    nanodbc::statement exec(con);
    constexpr std::string_view textoExec{
        "INSERT INTO decorar_mobles(id_ben_moble, nome_motivo_decorativo) "
        "VALUES (?, ?)"
    };

    exec.prepare(textoExec.data());

    auto idBenMoble = elemento.getId().value();

    for (auto&& i: elemento.getMotivosDecorativos())
    {
        unsigned short posLigar = 0;
        exec.prepare(textoExec.data());

        auto nomeMotivoDecorativo = i.getNome();

        ligarParametro(idBenMoble, exec, posLigar);
        ligarParametro(nomeMotivoDecorativo, exec, posLigar);

        exec.execute();
    }
}

void MotivoDecorativoDAO::asociarComponentesElemento(const Escultura& elemento, nanodbc::connection& con)
{
    asociarComponentesElemento(static_cast<BenPatrimonial>(elemento), con);
}

void MotivoDecorativoDAO:: asociarComponentesElemento(const Lapida& elemento, nanodbc::connection& con)
{
    nanodbc::statement exec(con);
    constexpr std::string_view textoExec{
        "INSERT INTO decorar_lapidas(id_lapida, nome_motivo_decorativo) "
        "VALUES (?, ?)"
    };

    exec.prepare(textoExec.data());

    auto idLapida = elemento.getId();

    for (auto&& i: elemento.getMotivosDecorativos())
    {
        unsigned short posLigar = 0;
        exec.prepare(textoExec.data());

        auto nomeMotivoDecorativo = i.getNome();

        ligarParametro(idLapida, exec, posLigar);
        ligarParametro(nomeMotivoDecorativo, exec, posLigar);

        exec.execute();
    }
}

void MotivoDecorativoDAO::modificarComponentesElemento(const BenPatrimonial& inicial, const BenPatrimonial& final, nanodbc::connection& con)
{
    // TODO: optimizar para que non corte a machada todos os motivos e os repoña
    nanodbc::statement exec(con);
    constexpr std::string_view textoExec{
        "DELETE FROM decorar_mobles dm "
        "WHERE id_ben_moble = ?"
    };

    exec.prepare(textoExec.data());

    unsigned short posLigar = 0;
    auto idBenPatrimonialInicial = inicial.getId();
    ligarParametro(idBenPatrimonialInicial, exec, posLigar);

    exec.execute();

    asociarComponentesElemento(final, con);
}

void MotivoDecorativoDAO::modificarComponentesElemento(const Escultura& inicial, const Escultura& final, nanodbc::connection& con)
{
    modificarComponentesElemento(static_cast<BenPatrimonial>(inicial), static_cast<BenPatrimonial>(final), con);
}

void MotivoDecorativoDAO::modificarComponentesElemento(const Lapida& inicial, const Lapida& final, nanodbc::connection& con)
{
    // TODO: optimizar para que non corte a machada todos os motivos e os repoña
    nanodbc::statement exec(con);
    constexpr std::string_view textoExec{
        "DELETE FROM decorar_lapidas dl "
        "WHERE id_lapida = ?"
    };

    exec.prepare(textoExec.data());

    unsigned short posLigar = 0;
    auto idLapidaInicial = inicial.getId();
    ligarParametro(idLapidaInicial, exec, posLigar);

    exec.execute();

    asociarComponentesElemento(final, con);
}

std::vector<MotivoDecorativo> MotivoDecorativoDAO::obterComponentesElemento(const BenPatrimonial& elemento, nanodbc::connection& con)
{
    nanodbc::statement exec(con);
    constexpr std::string_view textoExec {
        "SELECT m.* "
        "FROM decorar_mobles dm JOIN motivos_decorativos m ON dm.nome_motivo_decorativo = m.nome "
        "WHERE dm.id_ben_moble = ?"};

    exec.prepare(textoExec.data());
    const unsigned int id = elemento.getId().value();
    exec.bind(0, &id);

    auto resultado = exec.execute();

    std::vector<MotivoDecorativo> obtidoExecucion{};

    while (resultado.next())
        obtidoExecucion.push_back(MotivoDecorativo(resultado.get<std::string>(0)));

    return obtidoExecucion;
}

std::vector<MotivoDecorativo> MotivoDecorativoDAO::obterComponentesElemento(const Escultura& elemento, nanodbc::connection& con)
{
    return obterComponentesElemento(static_cast<BenPatrimonial>(elemento), con);
}

std::vector<MotivoDecorativo> MotivoDecorativoDAO::obterComponentesElemento(const Lapida& elemento, nanodbc::connection& con)
{
    nanodbc::statement exec(con);
    constexpr std::string_view textoExec {
        "SELECT m.* "
        "FROM decorar_lapidas dl JOIN motivos_decorativos m ON dl.nome_motivo_decorativo = m.nome "
        "WHERE dl.id_lapida = ?"};

    exec.prepare(textoExec.data());
    const unsigned int id = elemento.getId().value();
    exec.bind(0, &id);

    auto resultado = exec.execute();

    std::vector<MotivoDecorativo> obtidoExecucion{};

    while (resultado.next())
        obtidoExecucion.push_back(MotivoDecorativo(resultado.get<std::string>(0)));

    return obtidoExecucion;
}
