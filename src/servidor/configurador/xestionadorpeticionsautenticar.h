#ifndef XESTIONADORPETICIONSAUTENTICAR_H
#define XESTIONADORPETICIONSAUTENTICAR_H
#include "ixestionadorpeticions.h"

class XestionadorPeticionsAutenticar: public IXestionadorPeticions
{
public:
    XestionadorPeticionsAutenticar() = delete;
    explicit XestionadorPeticionsAutenticar(IServidor &fs, const std::string& dsn);

    void configurarPeticions(std::string_view uri) override;

private:
    void login(const httplib::Request& req, httplib::Response& res);
    void logout(const httplib::Request& req, httplib::Response& res);

    std::string dsn;
};

#endif // XESTIONADORPETICIONSAUTENTICAR_H
