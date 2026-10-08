#ifndef ERROSAUTENTIFICACION_H
#define ERROSAUTENTIFICACION_H
#include <exception>

class ErroAutentificacion : public std::exception
{};

class ErroSesionCaducada: public std::exception
{};

#endif // ERROSAUTENTIFICACION_H
