#ifndef IMAXEJPEG_H
#define IMAXEJPEG_H

#include "imaxe.h"

class ImaxeJPEG : public Imaxe
{
public:
    explicit ImaxeJPEG(const std::vector<uint8_t>& datos);

    std::vector<uint8_t> getDatos() const override;
    void setDatos(const std::vector<uint8_t> &newDatos) override;

    std::string getMIME() const override;

    bool serValida() const override;

    static bool validarDatos(const std::vector<uint8_t> &datos);

private:
    std::vector<uint8_t> datos;
};

#endif // IMAXEJPEG_H
