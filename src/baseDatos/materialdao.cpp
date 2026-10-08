#include "materialdao.h"
#include <benpatrimonial.h>
#include <escultura.h>
#include <lapida.h>

MaterialDAO::MaterialDAO()
{
    alias = 'm';
}

void MaterialDAO::construirParametrosConsulta(const Material& parametro, std::string& texto)
{
    construirParametroConsulta(parametro.getNome(), texto, "nome", true);

    // Limpar o "AND " que sobra
    if (!texto.empty())
        texto.erase(texto.length() - 5);
}


void MaterialDAO::construirParametrosActualizacion(const Material& inicial, Material& final, std::string& texto)
{
    construirParametroActualizacion(std::optional<std::string>(final.getNome()), texto, "nome");

    if (!texto.empty())
        texto.pop_back();
}

nanodbc::result MaterialDAO::ligarParametros(const Material& parametro, nanodbc::statement& consulta, const bool actualizacion)
{
    unsigned short posLigar = 0;
    const auto nome = parametro.getNome();

    ligarParametro(nome, consulta, posLigar);

    return consulta.execute();
}

void MaterialDAO::ligarParametros(const Material& inicial, const Material& final, nanodbc::statement& consulta)
{
    unsigned short posLigar = 0;

    const auto nomeFinal = final.getNome();

    ligarParametro(nomeFinal, consulta, posLigar);

    const auto nomeInicial = inicial.getNome();
    ligarParametro(nomeInicial, consulta, posLigar);

    consulta.execute();
}

std::vector<Material> MaterialDAO::listarInventario(nanodbc::connection& con)
{
    nanodbc::statement exec(con);
    constexpr std::string_view textoExec {
            "SELECT * "
            "FROM materiais m"};

    exec.prepare(textoExec.data());
    auto resultado = exec.execute();

    std::vector<Material> obtidoExecucion{};

    while (resultado.next())
        obtidoExecucion.push_back(Material(resultado.get<std::string>("nome")));

    return obtidoExecucion;
}

std::vector<Material> MaterialDAO::buscarInventario(const Material& parametros, nanodbc::connection& con)
{
    nanodbc::statement exec(con);
    std::string textoExec {
        "SELECT * "
        "FROM materiais m "
        "WHERE "};

    construirParametrosConsulta(parametros, textoExec);

    exec.prepare(textoExec.data());

    auto resultado = ligarParametros(parametros, exec);

    std::vector<Material> obtidoExecucion{};

    while (resultado.next())
        obtidoExecucion.push_back(Material(resultado.get<std::string>("nome")));

    return obtidoExecucion;
}

void MaterialDAO::engadirInventario(Material& parametros, nanodbc::connection& con)
{
    nanodbc::statement exec(con);
    std::string textoExec {
        "INSERT INTO materiais(nome) \
        VALUES(?)"};

    exec.prepare(textoExec.data());

    ligarParametros(parametros, exec, true);
}

void MaterialDAO::modificarInventario(const Material& inicial, Material& final, nanodbc::connection& con)
{
    nanodbc::statement exec(con);
    std::string textoExec {
        "UPDATE materiais m \
        SET"};

    construirParametrosActualizacion(inicial, final, textoExec);

    // Quitar a coma extra que sobra ao realizar construirParametroActualizacion e poñer un espazo para o WHERE
    textoExec.back() = ' ';
    textoExec += "WHERE nome = ?";

    exec.prepare(textoExec.data());

    ligarParametros(inicial, final, exec);
}

void MaterialDAO::eliminarInventario(const Material& parametros, nanodbc::connection& con)
{
    nanodbc::statement exec(con);
    std::string textoExec {
        "DELETE FROM bens_mobles bp \
        WHERE nome = ?"
    };

    exec.prepare(textoExec.data());

    unsigned short pos = 0;
    const auto nome = parametros.getNome();
    ligarParametro(nome, exec, pos);
}

void MaterialDAO::asociarComponentesElemento(const BenPatrimonial& elemento, nanodbc::connection& con)
{
    nanodbc::statement exec(con);
    constexpr std::string_view textoExec{
        "INSERT INTO componer_mobles(id_ben_moble, nome_material) "
        "VALUES (?, ?)"
    };

    exec.prepare(textoExec.data());

    auto idBenMoble = elemento.getId().value();

    for (auto&& i: elemento.getMateriais())
    {
        unsigned short posLigar = 0;
        exec.prepare(textoExec.data());

        auto nomeMaterial = i.getNome();

        ligarParametro(idBenMoble, exec, posLigar);
        ligarParametro(nomeMaterial, exec, posLigar);

        exec.execute();
    }
}

void MaterialDAO::asociarComponentesElemento(const Escultura& elemento, nanodbc::connection& con)
{
    asociarComponentesElemento(static_cast<BenPatrimonial>(elemento), con);
}

void MaterialDAO:: asociarComponentesElemento(const Lapida& elemento, nanodbc::connection& con)
{
    nanodbc::statement exec(con);
    constexpr std::string_view textoExec{
        "INSERT INTO componer_lapidas(id_lapida, nome_material) "
        "VALUES (?, ?)"
    };

    exec.prepare(textoExec.data());

    auto idLapida = elemento.getId();

    for (auto&& i: elemento.getMateriais())
    {
        unsigned short posLigar = 0;
        exec.prepare(textoExec.data());

        auto nomeMaterial = i.getNome();

        ligarParametro(idLapida, exec, posLigar);
        ligarParametro(nomeMaterial, exec, posLigar);

        exec.execute();
    }
}

void MaterialDAO::modificarComponentesElemento(const BenPatrimonial& inicial, const BenPatrimonial& final, nanodbc::connection& con)
{
    // TODO: optimizar para que non corte a machada todos os motivos e os repoña
    nanodbc::statement exec(con);
    constexpr std::string_view textoExec{
        "DELETE FROM componer_mobles cm "
        "WHERE id_ben_moble = ?"
    };

    exec.prepare(textoExec.data());

    unsigned short posLigar = 0;
    auto idBenPatrimonialInicial = inicial.getId();
    ligarParametro(idBenPatrimonialInicial, exec, posLigar);

    exec.execute();

    asociarComponentesElemento(final, con);
}

void MaterialDAO::modificarComponentesElemento(const Escultura& inicial, const Escultura& final, nanodbc::connection& con)
{
    modificarComponentesElemento(static_cast<BenPatrimonial>(inicial), static_cast<BenPatrimonial>(final), con);
}

void MaterialDAO::modificarComponentesElemento(const Lapida& inicial, const Lapida& final, nanodbc::connection& con)
{
    // TODO: optimizar para que non corte a machada todos os motivos e os repoña
    nanodbc::statement exec(con);
    constexpr std::string_view textoExec{
        "DELETE FROM componer_lapidas cl "
        "WHERE id_lapida = ?"
    };

    exec.prepare(textoExec.data());

    unsigned short posLigar = 0;
    auto idLapidaInicial = inicial.getId();
    ligarParametro(idLapidaInicial, exec, posLigar);

    exec.execute();

    asociarComponentesElemento(final, con);
}

std::vector<Material> MaterialDAO::obterComponentesElemento(const BenPatrimonial& elemento, nanodbc::connection& con)
{
    nanodbc::statement exec(con);
    constexpr std::string_view textoExec {
            "SELECT m.* \
            FROM componer_mobles cp JOIN materiais m ON cp.nome_material = m.nome \
            WHERE cp.id_ben_moble = ?"};

    exec.prepare(textoExec.data());
    const unsigned int id = elemento.getId().value();
    exec.bind(0, &id);

    auto resultado = exec.execute();

    std::vector<Material> obtidoExecucion{};

    while (resultado.next())
        obtidoExecucion.push_back(Material(resultado.get<std::string>(0)));

    return obtidoExecucion;
}


std::vector<Material> MaterialDAO::obterComponentesElemento(const Escultura& elemento, nanodbc::connection& con)
{
    return obterComponentesElemento(static_cast<const BenPatrimonial>(elemento), con);
}


std::vector<Material> MaterialDAO::obterComponentesElemento(const Lapida& elemento, nanodbc::connection& con)
{
    nanodbc::statement exec(con);
    constexpr std::string_view textoExec {
            "SELECT m.* \
            FROM componer_lapidas cl JOIN materiais m ON cl.nome_material = m.nome \
            WHERE cl.id_lapida = ?"};

    exec.prepare(textoExec.data());
    const unsigned int id = elemento.getId().value();
    exec.bind(0, &id);

    auto resultado = exec.execute();

    std::vector<Material> obtidoExecucion{};

    while (resultado.next())
        obtidoExecucion.push_back(Material(resultado.get<std::string>(0)));

    return obtidoExecucion;
}