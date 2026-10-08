#include "esculturadao.h"

EsculturaDAO::EsculturaDAO()
{
    alias = 'e';
}

void EsculturaDAO::construirParametrosConsulta(const Escultura& parametro, std::string& texto)
{
    benPatrimonialDao.construirParametrosConsulta(parametro, texto);
    // Poñer un AND extra ao sair de benPatrimonialdao
    texto += " AND ";
    construirParametroConsulta(parametro.getId(), texto, "id_ben_moble");
    construirParametroConsulta(parametro.getSantoRepresentado(), texto, "santo_representado");

    // Limpar o "AND " que sobra
    if (!texto.empty())
        texto.erase(texto.length() - 5);
}

void EsculturaDAO::construirParametrosActualizacion(const Escultura& inicial, Escultura& final, std::string& texto)
{
    construirParametroActualizacion(final.getSantoRepresentado(), texto, "santo_representado");

    // Quitar a coma extra que sobra ao realizar construirParametroActualizacion e poñer un espazo para o WHERE
    if (!texto.empty())
        texto.back() = ' ';
}

nanodbc::result EsculturaDAO::ligarParametros(const Escultura& parametro, nanodbc::statement& consulta, const bool actualizacion)
{
    unsigned short posLigar = 0;
    const auto id = parametro.getId();
    const auto SantoRepresentado = parametro.getSantoRepresentado();

    ligarParametro(id, consulta, posLigar, false);
    ligarParametro(SantoRepresentado, consulta, posLigar, actualizacion);

    return consulta.execute();
}

void EsculturaDAO::ligarParametros(const Escultura& inicial, const Escultura& final, nanodbc::statement& consulta)
{
    unsigned short posLigar = 0;
    const auto SantoRepresentadoFinal = final.getSantoRepresentado();


    ligarParametro(SantoRepresentadoFinal, consulta, posLigar, false);

    const auto idInicial = inicial.getId();

    ligarParametro(idInicial, consulta, posLigar, false);

    consulta.execute();
}

std::vector<Escultura> EsculturaDAO::listarInventario(nanodbc::connection& con)
{
    nanodbc::statement exec(con);
    constexpr std::string_view textoExec {
        "SELECT * "
        "FROM  bens_mobles bm "
        "JOIN esculturas e ON bm.id = e.id_ben_moble"};

    exec.prepare(textoExec.data());
    auto resultado = exec.execute();

    std::vector<Escultura> obtidoExecucion{};

    while (resultado.next())
    {
        int id = resultado.get<int>("id");
        auto datacion = obterAtributo<nanodbc::date>(resultado, "datacion");
        obtidoExecucion.push_back(Escultura(obterAtributo<std::string>(resultado, "santo_representado"),
                                            id,
                                            obterAtributo<std::string>(resultado, "nome"),
                                            obterAtributo<std::string>(resultado, "descripcion"),
                                            obterAtributo<float>(resultado, "altura"),
                                            obterAtributo<float>(resultado, "anchura"),
                                            (datacion ? static_cast<unsigned short>(datacion.value().year) : std::optional<unsigned short>{}),
                                            obterAtributo<std::string>(resultado, "seculo"),
                                            obterAtributo<std::string>(resultado, "segmento_seculo"),
                                            obterAtributo<std::string>(resultado, "estilo"),
                                            obterAtributo<std::string>(resultado, "taller"),
                                            materialDao.obterComponentesElemento(Escultura(id), con),
                                            motivoDecorativoDao.obterComponentesElemento(Escultura(id), con)));
    }

    return obtidoExecucion;
}

std::vector<Escultura> EsculturaDAO::buscarInventario(const Escultura& parametros, nanodbc::connection& con)
{
    nanodbc::statement exec(con);
    std::string textoExec {
        "SELECT * "
        "FROM bens_mobles bm "
        "JOIN esculturas e ON bm.id = e.id_ben_moble "
        "WHERE "};

    benPatrimonialDao.construirParametrosConsulta(parametros, textoExec);

    exec.prepare(textoExec.data());

    auto resultado = benPatrimonialDao.ligarParametros(parametros, exec);

    std::vector<Escultura> obtidoExecucion{};

    while (resultado.next())
    {
        int id = resultado.get<int>("id");
        std::optional<nanodbc::date> datacion = obterAtributo<nanodbc::date>(resultado, "datacion");
        obtidoExecucion.push_back(Escultura(obterAtributo<std::string>(resultado, "santo_representado"),
                                            id,
                                            obterAtributo<std::string>(resultado, "nome"),
                                            obterAtributo<std::string>(resultado, "descripcion"),
                                            obterAtributo<float>(resultado, "altura"),
                                            obterAtributo<float>(resultado, "anchura"),
                                            datacion ? datacion.value().year : std::optional<unsigned short>{},
                                            obterAtributo<std::string>(resultado, "seculo"),
                                            obterAtributo<std::string>(resultado, "segmento_seculo"),
                                            obterAtributo<std::string>(resultado, "estilo"),
                                            obterAtributo<std::string>(resultado, "taller"),
                                            materialDao.obterComponentesElemento(Escultura(id), con),
                                            motivoDecorativoDao.obterComponentesElemento(Escultura(id), con)));
    }

    return obtidoExecucion;
}

void EsculturaDAO::engadirInventario(Escultura& parametros, nanodbc::connection& con)
{
    // Faise unha transación por comodidade para poder coller o ID do novo valor inserido sen que haia
    nanodbc::transaction trans(con);

    benPatrimonialDao.engadirInventario(parametros, con);

    // Meter o valor na táboa correspondente adicional segundo o MER

    constexpr std::string_view textoExec =
        "INSERT INTO Esculturas(id_ben_moble, santo_representado) "
        "VALUES(?, ?)";

    nanodbc::statement exec = nanodbc::statement(con);

    exec.prepare(textoExec.data());

    ligarParametros(parametros, exec, true);

    trans.commit();
}

void EsculturaDAO::modificarInventario(const Escultura& inicial, Escultura& final, nanodbc::connection& con)
{
    nanodbc::transaction trans(con);
    benPatrimonialDao.modificarInventario(inicial, final, con);

    if(final.getSantoRepresentado())
    {
        nanodbc::statement exec(con);

        std::string textoExec =
            "UPDATE Esculturas "
            "SET";

        construirParametrosActualizacion(inicial, final, textoExec);
        textoExec += "WHERE id_ben_moble = ?";

        exec.prepare(textoExec.data());

        ligarParametros(inicial, final, exec);
    }

    trans.commit();
}

void EsculturaDAO::eliminarInventario(const Escultura& parametros, nanodbc::connection& con)
{
    benPatrimonialDao.eliminarInventario(parametros, con);
}

std::unique_ptr<Imaxe> EsculturaDAO::obterImaxe(const Escultura& parametros, nanodbc::connection &con)
{
    return benPatrimonialDao.obterImaxe(parametros, con);
}

void EsculturaDAO::rexistrarImaxe(const Escultura& parametros, const Imaxe &imaxe, nanodbc::connection &con)
{
    benPatrimonialDao.rexistrarImaxe(parametros, imaxe, con);
}

void EsculturaDAO::eliminarImaxe(const Escultura& parametros, nanodbc::connection &con)
{
    benPatrimonialDao.eliminarImaxe(parametros, con);
}
