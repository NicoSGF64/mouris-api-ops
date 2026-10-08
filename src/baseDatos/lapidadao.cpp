#include "lapidadao.h"
#include <imaxe/fabricaimaxe.h>

LapidaDAO::LapidaDAO()
{
    alias = 'l';
}

LapidaDAO::LapidaDAO(const MaterialDAO &materialDao, const MotivoDecorativoDAO &motivoDecorativoDao) : materialDao(materialDao),
    motivoDecorativoDao(motivoDecorativoDao)
{
    alias = 'l';
}

void LapidaDAO::construirParametrosConsulta(const Lapida& parametro, std::string& texto)
{
    construirParametroConsulta(parametro.getId(), texto, "id");
    construirParametroConsulta(parametro.getXenealoxia(), texto, "xeanoloxia");
    construirParametroConsulta(parametro.getEpigrafia(), texto, "epigrafia");
    std::optional<nanodbc::date> data{};
    if (parametro.getDatacion())
        data = nanodbc::date{.year = static_cast<int16_t>(parametro.getDatacion().value().ano),
                             .month = static_cast<int16_t>(parametro.getDatacion().value().mes),
                             .day = static_cast<int16_t>(parametro.getDatacion().value().dia)};
    construirParametroConsulta(data, texto, "datacion");
    construirParametroConsulta(parametro.getProxectoArquitectonico(), texto, "paq");
    construirParametroConsulta(parametro.getEstadoConservacionBioloxico(), texto, "ecb");
    construirParametroConsulta(parametro.getEstadoConservacionAtmosferico(), texto, "eca");

    // Limpar o "AND " que sobra
    if (!texto.empty())
        texto.erase(texto.length() - 5);
}


void LapidaDAO::construirParametrosActualizacion(const Lapida& inicial, Lapida& final, std::string& texto)
{
    construirParametroActualizacion(final.getXenealoxia(), texto, "xeanoloxia");
    construirParametroActualizacion(final.getEpigrafia(), texto, "epigrafia");
    std::optional<nanodbc::date> data{};
    if (final.getDatacion())
        data = nanodbc::date{.year = static_cast<int16_t>(final.getDatacion()->ano),
                             .month = static_cast<int16_t>(final.getDatacion()->mes),
                             .day = static_cast<int16_t>(final.getDatacion()->dia)};
    construirParametroActualizacion(data, texto, "datacion");
    construirParametroActualizacion(final.getProxectoArquitectonico(), texto, "paq");

    const std::optional<estadoConservacion> ecb = final.getEstadoConservacionBioloxico();
    if (ecb)
    {
        construirParametroActualizacion(ecb.value().marca, texto, "ecb_marca");
        construirParametroActualizacion(ecb.value().razonamento, texto, "ecb_razonamento");
    }

    const std::optional<estadoConservacion> eca = final.getEstadoConservacionAtmosferico();
    if (eca)
    {
        construirParametroActualizacion(eca.value().marca, texto, "eca_marca");
        construirParametroActualizacion(eca.value().razonamento, texto, "eca_razonamento");
    }

    // Quitar a coma extra que sobra ao realizar construirParametroActualizacion e poñer un espazo para o WHERE
    if (!texto.empty())
        texto.back() = ' ';
}

nanodbc::result LapidaDAO::ligarParametros(const Lapida& parametro, nanodbc::statement& consulta, const bool insercion)
{
    unsigned short posLigar = 0;
    const auto id = parametro.getId();
    const auto xenealoxia = parametro.getXenealoxia();
    const auto epigrafia = parametro.getEpigrafia();
    const std::optional<nanodbc::date> datacion = parametro.getDatacion() ?
        nanodbc::date{.year = static_cast<int16_t>(parametro.getDatacion()->ano),
                      .month = static_cast<int16_t>(parametro.getDatacion()->mes),
                      .day = static_cast<int16_t>(parametro.getDatacion()->dia)} :
        std::optional<nanodbc::date>{};
    const auto proxectoArquitectonico = parametro.getProxectoArquitectonico();
    const auto ecb = parametro.getEstadoConservacionBioloxico();
    const auto eca = parametro.getEstadoConservacionAtmosferico();

    if (!insercion)
        ligarParametro(id, consulta, posLigar, false);
    ligarParametro(xenealoxia, consulta, posLigar, insercion);
    ligarParametro(epigrafia, consulta, posLigar, insercion);
    ligarParametro(datacion, consulta, posLigar, insercion);
    ligarParametro(proxectoArquitectonico, consulta, posLigar, insercion);
    ligarParametro(ecb, consulta, posLigar, insercion);
    ligarParametro(eca, consulta, posLigar, insercion);

    return consulta.execute();
}

void LapidaDAO::ligarParametros(const Lapida& inicial, const Lapida& final, nanodbc::statement& consulta)
{
    unsigned short posLigar = 0;
    const auto xenealoxiaFinal = final.getXenealoxia();
    const auto epigrafiaFinal = final.getEpigrafia();
    const std::optional<nanodbc::date> datacionFinal = final.getDatacion() ?
                                                      nanodbc::date{.year = static_cast<int16_t>(final.getDatacion()->ano),
                                                                    .month = static_cast<int16_t>(final.getDatacion()->mes),
                                                                    .day = static_cast<int16_t>(final.getDatacion()->dia)} :
                                                      std::optional<nanodbc::date>{};
    const auto proxectoArquitectonicoFinal = final.getProxectoArquitectonico();
    const auto ecbFinal = final.getEstadoConservacionBioloxico();
    const auto ecaFinal = final.getEstadoConservacionAtmosferico();

    ligarParametro(xenealoxiaFinal, consulta, posLigar, false);
    ligarParametro(epigrafiaFinal, consulta, posLigar, false);
    ligarParametro(datacionFinal, consulta, posLigar, false);
    ligarParametro(proxectoArquitectonicoFinal, consulta, posLigar, false);

    if (ecbFinal)
    {
        ligarParametro(ecbFinal.value().marca, consulta, posLigar);
        ligarParametro(ecbFinal.value().razonamento, consulta, posLigar);
    }

    if (ecaFinal)
    {
        ligarParametro(ecaFinal.value().marca, consulta, posLigar);
        ligarParametro(ecaFinal.value().razonamento, consulta, posLigar);
    }

    const auto idInicial = inicial.getId();
    ligarParametro(idInicial, consulta, posLigar, false);

    consulta.execute();
}

std::vector<Lapida> LapidaDAO::listarInventario(nanodbc::connection& con)
{
    nanodbc::statement exec(con);
    constexpr std::string_view textoExec {
            "SELECT * "
            "FROM lapidas l"};

    exec.prepare(textoExec.data());
    auto resultado = exec.execute();

    std::vector<Lapida> obtidoExecucion{};

    while (resultado.next())
    {
        int id = resultado.get<int>("id");
        std::optional<nanodbc::date> data = obterAtributo<nanodbc::date>(resultado, "datacion");

        obtidoExecucion.push_back(Lapida(id,
                                         obterAtributo<std::string>(resultado, "xeanoloxia"),
                                         obterAtributo<std::string>(resultado, "epigrafia"),
                                         data ? Data{static_cast<unsigned short>(data.value().day), static_cast<unsigned short>(data.value().month), data.value().year} : std::optional<Data>{},
                                         obterAtributo<std::string>(resultado, "paq"),
                                         estadoConservacion{.marca = obterAtributo<std::string>(resultado, "ecb_marca").value_or(""), .razonamento = obterAtributo<std::string>(resultado, "ecb_razonamento").value_or("")},
                                         estadoConservacion{.marca = obterAtributo<std::string>(resultado, "eca_marca").value_or(""), .razonamento = obterAtributo<std::string>(resultado, "eca_razonamento").value_or("")},
                                         materialDao.obterComponentesElemento(Lapida(id), con),
                                         motivoDecorativoDao.obterComponentesElemento(Lapida(id), con)));
    }

    return obtidoExecucion;
}

std::vector<Lapida> LapidaDAO::buscarInventario(const Lapida& parametros, nanodbc::connection& con)
{
    nanodbc::statement exec(con);
    std::string textoExec {
        "SELECT * "
        "FROM lapidas l "
        "WHERE "};

    construirParametrosConsulta(parametros, textoExec);

    exec.prepare(textoExec.data());

    auto resultado = ligarParametros(parametros, exec);

    std::vector<Lapida> obtidoExecucion{};

    while (resultado.next())
    {
        int id = resultado.get<int>("id");
        nanodbc::date data = resultado.get<nanodbc::date>("datacion");

        obtidoExecucion.push_back(Lapida(id,
                                         obterAtributo<std::string>(resultado, "xeanoloxia"),
                                         obterAtributo<std::string>(resultado, "epigrafia"),
                                         Data{static_cast<unsigned short>(data.day), static_cast<unsigned short>(data.month), data.year},
                                         obterAtributo<std::string>(resultado, "paq"),
                                         estadoConservacion{.marca = obterAtributo<std::string>(resultado, "ecb_marca").value_or(""), .razonamento = obterAtributo<std::string>(resultado, "ecb_razonamento").value_or("")},
                                         estadoConservacion{.marca = obterAtributo<std::string>(resultado, "eca_marca").value_or(""), .razonamento = obterAtributo<std::string>(resultado, "eca_razonamento").value_or("")},
                                         materialDao.obterComponentesElemento(Lapida(id), con),
                                         motivoDecorativoDao.obterComponentesElemento(Lapida(id), con)));
    }

    return obtidoExecucion;
}

void LapidaDAO::engadirInventario(Lapida& parametros, nanodbc::connection& con)
{
    nanodbc::transaction trans(con);

    nanodbc::statement exec(con);

    constexpr std::string_view textoExec {
        "INSERT INTO lapidas(epigrafia, xeanoloxia, datacion, paq, ecb_marca, ecb_razonamento, eca_marca, eca_razonamento) "
        "VALUES(?, ?, ?, ?, ?, ?, ?, ?)"};

    exec.prepare(textoExec.data());

    ligarParametros(parametros, exec, true);

    // Obter o último ID que vemos de inserir
    // Ao estarnos dentro dunha transacción, non hai que ter medo de que haia outra superior
    // (teoricamente)
    exec = nanodbc::statement(con);
    exec.prepare("SELECT MAX(l.id) AS max_id "
                 "FROM lapidas l");

    auto resultados = exec.execute();

    resultados.next();

    parametros.setId(resultados.get<unsigned int>("max_id"));

    materialDao.asociarComponentesElemento(parametros, con);
    motivoDecorativoDao.asociarComponentesElemento(parametros, con);

    trans.commit();
}

void LapidaDAO::modificarInventario(const Lapida& inicial, Lapida& final, nanodbc::connection& con)
{
    nanodbc::transaction trans(con);

    nanodbc::statement exec(con);
    std::string textoExec {
        "UPDATE lapidas l "
        "SET"};

    construirParametrosActualizacion(inicial, final, textoExec);
    textoExec += "WHERE id = ?";

    exec.prepare(textoExec.data());

    ligarParametros(inicial, final, exec);

    if (!final.getMateriais().empty())
        materialDao.modificarComponentesElemento(inicial, final, con);

    if (!final.getMotivosDecorativos().empty())
        motivoDecorativoDao.modificarComponentesElemento(inicial, final, con);

    trans.commit();
}

void LapidaDAO::eliminarInventario(const Lapida& parametros, nanodbc::connection& con)
{
    nanodbc::statement exec(con);
    constexpr std::string_view textoExec {
        "DELETE FROM lapidas l "
        "WHERE id = ?"
    };

    exec.prepare(textoExec.data());

    unsigned short pos = 0;
    const auto id = parametros.getId();
    ligarParametro(id, exec, pos);

    exec.execute();
}

std::unique_ptr<Imaxe> LapidaDAO::obterImaxe(const Lapida& parametros, nanodbc::connection &con)
{
    nanodbc::statement exec(con);
    constexpr std::string_view textoExec {
    "SELECT fotografia_mime, encode(fotografia_datos, 'hex') AS fotografia_datos "
    "FROM  lapidas l "
    "WHERE l.id = ?"};

    exec.prepare(textoExec.data());

    unsigned short pos = 0;
    const auto id = parametros.getId();
    ligarParametro(id, exec, pos);

    auto resultado = exec.execute();

    if(!resultado.next())
        return nullptr;

    FabricaImaxe fi;

    std::optional<std::string> mime = obterAtributo<std::string>(resultado, "fotografia_mime");

    if (!mime)
        return nullptr;

    std::string v = resultado.get<std::string>("fotografia_datos");

    return fi.fabricar(mime.value(), from_hex(v));
}

void LapidaDAO::rexistrarImaxe(const Lapida& parametros, const Imaxe &imaxe, nanodbc::connection &con)
{
    nanodbc::statement exec(con);
    constexpr std::string_view textoExec {
        "UPDATE lapidas l "
        "SET fotografia_mime = ?, fotografia_datos = decode(?, 'hex') "
        "WHERE l.id = ?"
    };

    exec.prepare(textoExec.data());

    unsigned short pos = 0;
    const std::string mime = imaxe.getMIME();
    ligarParametro(mime, exec, pos);
    std::string datos = to_hex(imaxe.getDatos());
    ligarParametro(datos, exec, pos);

    const auto id = parametros.getId();
    ligarParametro(id, exec, pos);

    exec.execute();
}

void LapidaDAO::eliminarImaxe(const Lapida& parametros, nanodbc::connection &con)
{
    nanodbc::statement exec(con);
    constexpr std::string_view textoExec {
        "UPDATE lapidas l "
        "SET fotografia_mime = NULL, fotografia_datos = NULL "
        "WHERE l.id = ?"
    };

    exec.prepare(textoExec.data());

    unsigned short pos = 0;
    const auto id = parametros.getId();
    ligarParametro(id, exec, pos);

    exec.execute();
}
