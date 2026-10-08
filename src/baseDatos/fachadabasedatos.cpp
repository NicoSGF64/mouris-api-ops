#include "fachadabasedatos.h"

FachadaBaseDatos::FachadaBaseDatos(const std::string& dsn, const Usuario &u) : dsnBBDD(dsn)
{
    // Por motivos fora do meu coñecemento, nanodbc::conection(dns, user, password) non funciona así que hai que facer esta chapuza
    dsnBBDD += ";Uid=" + u.getNomeUsuario().value_or("consulta") + ";";
    dsnBBDD += "Pwd=" + u.getContrasinal().value_or("consulta") + ";";

    con = nanodbc::connection(dsnBBDD);
}