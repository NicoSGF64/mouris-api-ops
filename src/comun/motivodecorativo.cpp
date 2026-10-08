#include "motivodecorativo.h"

MotivoDecorativo::MotivoDecorativo(const std::string &nome) : nome(nome)
{}

std::string MotivoDecorativo::getNome() const
{
    return nome;
}

void MotivoDecorativo::setNome(const std::string &newNome)
{
    nome = newNome;
}
