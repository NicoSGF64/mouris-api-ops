#include "material.h"

Material::Material(const std::string &nome) : nome(nome)
{}

std::string Material::getNome() const
{
    return nome;
}

void Material::setNome(const std::string &newNome)
{
    nome = newNome;
}
