#ifndef IMAXE_H
#define IMAXE_H
#include <cstdint>
#include <string>
#include <vector>

class Imaxe
{
public:
    Imaxe() = default;
    virtual ~Imaxe();

    virtual std::vector<uint8_t> getDatos() const = 0;
    virtual void setDatos(const std::vector<uint8_t> &newDatos) = 0;

    virtual std::string getMIME() const = 0;

    virtual bool serValida() const = 0;
};

#endif // IMAXE_H
