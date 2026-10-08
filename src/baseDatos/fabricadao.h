#ifndef FABRICADAO_H
#define FABRICADAO_H
#include <nanodbc/nanodbc.h>
#include "benpatrimonialdao.h"
#include "esculturadao.h"
#include "lapidadao.h"
#include "usuariodao.h"
#include "materialdao.h"
#include "motivodecorativo.h"

template <typename T>
struct FabricaDAO;

template <>
struct FabricaDAO<BenPatrimonial>
{
    using dao = BenPatrimonialDAO;
};

template <>
struct FabricaDAO<Escultura>
{
    using dao = EsculturaDAO;
};

template <>
struct FabricaDAO<Lapida>
{
    using dao = LapidaDAO;
};

template <>
struct FabricaDAO<Material>
{
    using dao = MaterialDAO;
};

template <>
struct FabricaDAO<MotivoDecorativo>
{
    using dao = MotivoDecorativoDAO;
};

template <>
struct FabricaDAO<Usuario>
{
    using dao = UsuarioDAO;
};

#endif // FABRICADAO_H
