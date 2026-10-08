#ifndef IXESTIONADORPETICIONS_H
#define IXESTIONADORPETICIONS_H
#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <httplib.h>
#include "iservidor.h"

class IXestionadorPeticions
{
public:
    IXestionadorPeticions() = delete;

    IXestionadorPeticions(IServidor &fs);

    virtual void configurarPeticions(std::string_view uri) = 0;

protected:
    IServidor& fs;
};

#endif // IXESTIONADORPETICIONS_H
