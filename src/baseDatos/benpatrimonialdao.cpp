#include "benpatrimonialdao.h"
#include <imaxe/fabricaimaxe.h>

BenPatrimonialDAO::BenPatrimonialDAO()
{
    alias = "bm";
}

BenPatrimonialDAO::BenPatrimonialDAO(const MaterialDAO &materialDao, const MotivoDecorativoDAO &motivoDecorativoDao) : materialDao(materialDao),
    motivoDecorativoDao(motivoDecorativoDao)
{
    alias = "bm";
}

void BenPatrimonialDAO::construirParametrosConsulta(const BenPatrimonial& parametro, std::string& texto)
{
    construirParametroConsulta(parametro.getId(), texto, "id");
    construirParametroConsulta(parametro.getNome(), texto, "nome");
    construirParametroConsulta(parametro.getDescripcion(), texto, "descripcion");
    construirParametroConsulta(parametro.getAltura(), texto, "altura");
    construirParametroConsulta(parametro.getAnchura(), texto, "anchura");
    std::optional<nanodbc::date> data{};
    if (parametro.getDatacion())
        data = nanodbc::date{.year = static_cast<int16_t>(parametro.getDatacion().value())};
    construirParametroConsulta(data, texto, "datacion");
    construirParametroConsulta(parametro.getSeculo(), texto, "seculo");
    construirParametroConsulta(parametro.getSegmento(), texto, "segmento_seculo");
    construirParametroConsulta(parametro.getEstilo(), texto, "estilo");
    construirParametroConsulta(parametro.getTaller(), texto, "taller");

    // Limpar o "AND " que sobra
    if (!texto.empty())
        texto.erase(texto.length() - 5);
}


void BenPatrimonialDAO::construirParametrosActualizacion(const BenPatrimonial& inicial, BenPatrimonial& final, std::string& texto)
{
    construirParametroActualizacion(final.getNome(), texto, "nome");
    construirParametroActualizacion(final.getDescripcion(), texto, "descripcion");
    construirParametroActualizacion(final.getAltura(), texto, "altura");
    construirParametroActualizacion(final.getAnchura(), texto, "anchura");
    std::optional<nanodbc::date> data{};
    if (final.getDatacion())
        data = nanodbc::date{.year = static_cast<int16_t>(final.getDatacion().value())};
    construirParametroActualizacion(data, texto, "datacion");
    construirParametroActualizacion(final.getSeculo(), texto, "seculo");
    construirParametroActualizacion(final.getSegmento(), texto, "segmento_seculo");
    construirParametroActualizacion(final.getEstilo(), texto, "estilo");
    construirParametroActualizacion(final.getTaller(), texto, "taller");

    // Quitar a coma extra que sobra ao realizar construirParametroActualizacion e poñer un espazo para o WHERE
    if (!texto.empty())
        texto.back() = ' ';
}

nanodbc::result BenPatrimonialDAO::ligarParametros(const BenPatrimonial& parametro, nanodbc::statement& consulta, const bool insercion)
{
    unsigned short posLigar = 0;


    const auto id = parametro.getId();
    const auto nome = parametro.getNome();
    const auto descripcion = parametro.getDescripcion();
    const auto altura = parametro.getAltura();
    const auto anchura = parametro.getAnchura();
    const std::optional<nanodbc::date> datacion = parametro.getDatacion() ? nanodbc::date{.year = static_cast<int16_t>(parametro.getDatacion().value()), .month = 1, .day = 1} : std::optional<nanodbc::date>{};
    const auto seculo = parametro.getSeculo();
    const auto segmento = parametro.getSegmento();
    const auto estilo = parametro.getEstilo();
    const auto taller = parametro.getTaller();
    const auto materiais = parametro.getMateriais();
    const auto motivosDecorativos = parametro.getMotivosDecorativos();

    if(!insercion)
        ligarParametro(id, consulta, posLigar, false);
    ligarParametro(nome, consulta, posLigar, insercion);
    ligarParametro(descripcion, consulta, posLigar, insercion);
    ligarParametro(altura, consulta, posLigar, insercion);
    ligarParametro(anchura, consulta, posLigar, insercion);
    ligarParametro(datacion, consulta, posLigar, insercion);
    ligarParametro(seculo, consulta, posLigar, insercion);
    ligarParametro(segmento, consulta, posLigar, insercion);
    ligarParametro(estilo, consulta, posLigar, insercion);
    ligarParametro(taller, consulta, posLigar, insercion);

    return consulta.execute();
}

void BenPatrimonialDAO::ligarParametros(const BenPatrimonial& inicial, const BenPatrimonial& final, nanodbc::statement& consulta)
{
    unsigned short posLigar = 0;

    const auto nomeFinal = final.getNome();
    const auto descripcionFinal = final.getDescripcion();
    const auto alturaFinal = final.getAltura();
    const auto anchuraFinal = final.getAnchura();
    const std::optional<nanodbc::date> datacionFinal = final.getDatacion() ? nanodbc::date{.year = static_cast<int16_t>(final.getDatacion().value())} : std::optional<nanodbc::date>{};
    const auto seculoFinal = final.getSeculo();
    const auto segmentoFinal = final.getSegmento();
    const auto estiloFinal = final.getEstilo();
    const auto tallerFinal = final.getTaller();
    const auto materiaisFinal = final.getMateriais();
    const auto motivosDecorativosFinal = final.getMotivosDecorativos();

    ligarParametro(nomeFinal, consulta, posLigar, false);
    ligarParametro(descripcionFinal, consulta, posLigar, false);
    ligarParametro(alturaFinal, consulta, posLigar, false);
    ligarParametro(anchuraFinal, consulta, posLigar, false);
    ligarParametro(datacionFinal, consulta, posLigar, false);
    ligarParametro(seculoFinal, consulta, posLigar, false);
    ligarParametro(segmentoFinal, consulta, posLigar, false);
    ligarParametro(estiloFinal, consulta, posLigar, false);
    ligarParametro(tallerFinal, consulta, posLigar, false);

    const auto idInicial = inicial.getId();
    ligarParametro(idInicial, consulta, posLigar, false);

    consulta.execute();
}

std::vector<BenPatrimonial> BenPatrimonialDAO::listarInventario(nanodbc::connection& con)
{
    nanodbc::statement exec(con);
    constexpr std::string_view textoExec {
            "SELECT * \
            FROM  bens_mobles bm \
            WHERE bm.id NOT IN ( \
                SELECT e.id_ben_moble \
                FROM esculturas e)"};

    exec.prepare(textoExec.data());
    auto resultado = exec.execute();

    std::vector<BenPatrimonial> obtidoExecucion{};

    while (resultado.next())
    {
        int id = resultado.get<int>("id");
        auto datacion = obterAtributo<nanodbc::date>(resultado, "datacion");
        obtidoExecucion.push_back(BenPatrimonial(id,
                                                 obterAtributo<std::string>(resultado, "nome"),
                                                 obterAtributo<std::string>(resultado, "descripcion"),
                                                 obterAtributo<float>(resultado, "altura"),
                                                 obterAtributo<float>(resultado, "anchura"),
                                                 (datacion ? static_cast<unsigned short>(datacion.value().year) : std::optional<unsigned short>{}),
                                                 obterAtributo<std::string>(resultado, "seculo"),
                                                 obterAtributo<std::string>(resultado, "segmento_seculo"),
                                                 obterAtributo<std::string>(resultado, "estilo"),
                                                 obterAtributo<std::string>(resultado, "taller"),
                                                 materialDao.obterComponentesElemento(BenPatrimonial(id), con),
                                                 motivoDecorativoDao.obterComponentesElemento(BenPatrimonial(id), con)));
    }

    return obtidoExecucion;
}

std::vector<BenPatrimonial> BenPatrimonialDAO::buscarInventario(const BenPatrimonial& parametros, nanodbc::connection& con)
{
    nanodbc::statement exec(con);
    std::string textoExec {
        "SELECT * \
        FROM  bens_mobles bm \
        WHERE bm.id NOT IN ( \
            SELECT e.id_ben_moble \
            FROM esculturas e) AND "};

    construirParametrosConsulta(parametros, textoExec);

    exec.prepare(textoExec.data());

    auto resultado = ligarParametros(parametros, exec);

    std::vector<BenPatrimonial> obtidoExecucion{};

    while (resultado.next())
    {
        int id = resultado.get<int>("id");
        auto datacion = obterAtributo<nanodbc::date>(resultado, "datacion");
        obtidoExecucion.push_back(BenPatrimonial(id,
                                                 obterAtributo<std::string>(resultado, "nome"),
                                                 obterAtributo<std::string>(resultado, "descripcion"),
                                                 obterAtributo<float>(resultado, "altura"),
                                                 obterAtributo<float>(resultado, "anchura"),
                                                 (datacion ? static_cast<unsigned short>(datacion.value().year) : std::optional<unsigned short>{}),
                                                 obterAtributo<std::string>(resultado, "seculo"),
                                                 obterAtributo<std::string>(resultado, "segmento_seculo"),
                                                 obterAtributo<std::string>(resultado, "estilo"),
                                                 obterAtributo<std::string>(resultado, "taller"),
                                                 materialDao.obterComponentesElemento(BenPatrimonial(id), con),
                                                 motivoDecorativoDao.obterComponentesElemento(BenPatrimonial(id), con)));
    }

    return obtidoExecucion;
}

void BenPatrimonialDAO::engadirInventario(BenPatrimonial& parametros, nanodbc::connection& con)
{
    nanodbc::transaction trans(con);

    nanodbc::statement exec(con);
    constexpr std::string_view textoExec {
        "INSERT INTO bens_mobles(nome, descripcion, altura, anchura, datacion, seculo, segmento_seculo, estilo, taller) "
        "VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?)"};

    exec.prepare(textoExec.data());

    ligarParametros(parametros, exec, true);

    // Obter o último ID que vemos de inserir
    // Ao estarnos dentro dunha transacción, non hai que ter medo de que haia outra superior
    // (teoricamente)
    exec = nanodbc::statement(con);
    exec.prepare("SELECT MAX(bm.id) AS max_id "
                 "FROM bens_mobles bm");

    auto resultados = exec.execute();

    resultados.next();

    parametros.setId(resultados.get<unsigned int>("max_id"));

    materialDao.asociarComponentesElemento(parametros, con);
    motivoDecorativoDao.asociarComponentesElemento(parametros, con);

    trans.commit();
}

void BenPatrimonialDAO::modificarInventario(const BenPatrimonial& inicial, BenPatrimonial& final, nanodbc::connection& con)
{
    nanodbc::transaction trans(con);

    nanodbc::statement exec(con);
    std::string textoExec {
        "UPDATE bens_mobles bm "
        "SET"};

    construirParametrosActualizacion(inicial, final, textoExec);
    textoExec += "WHERE id = ?";

    exec.prepare(textoExec.data());

    ligarParametros(inicial, final, exec);

    // TODO: Permitir que se poda baldeirar de xeito seguro os motivos decorativos
    if (!final.getMateriais().empty())
        materialDao.modificarComponentesElemento(inicial, final, con);

    // TODO: Permitir que se poda baldeirar de xeito seguro os motivos decorativos
    if (!final.getMotivosDecorativos().empty())
        motivoDecorativoDao.modificarComponentesElemento(inicial, final, con);

    trans.commit();
}

void BenPatrimonialDAO::eliminarInventario(const BenPatrimonial& parametros, nanodbc::connection& con)
{
    nanodbc::statement exec(con);
    constexpr std::string_view textoExec {
        "DELETE FROM bens_mobles bm "
        "WHERE id = ?"
    };

    exec.prepare(textoExec.data());

    unsigned short pos = 0;
    const auto id = parametros.getId();
    ligarParametro(id, exec, pos);

    exec.execute();
}

std::unique_ptr<Imaxe> BenPatrimonialDAO::obterImaxe(const BenPatrimonial& parametros, nanodbc::connection &con)
{
    nanodbc::statement exec(con);
    constexpr std::string_view textoExec {
        "SELECT fotografia_mime, encode(fotografia_datos, 'hex') AS fotografia_datos "
        "FROM  bens_mobles bm "
        "WHERE bm.id = ?"};

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

void BenPatrimonialDAO::rexistrarImaxe(const BenPatrimonial& parametros, const Imaxe& imaxe, nanodbc::connection& con)
{
    nanodbc::statement exec(con);
    constexpr std::string_view textoExec {
        "UPDATE bens_mobles bm "
        "SET fotografia_mime = ?, fotografia_datos = decode(?, 'hex') "
        "WHERE id = ?"
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

void BenPatrimonialDAO::eliminarImaxe(const BenPatrimonial& parametros, nanodbc::connection &con)
{
    nanodbc::statement exec(con);
    constexpr std::string_view textoExec {
        "UPDATE bens_mobles bm "
        "SET fotografia_mime = NULL, fotografia_datos = NULL "
        "WHERE id = ?"
    };

    exec.prepare(textoExec.data());

    unsigned short pos = 0;
    const auto id = parametros.getId();
    ligarParametro(id, exec, pos);

    exec.execute();
}
