#ifndef IDAOCOMPONEDOR_H
#define IDAOCOMPONEDOR_H
#include "idao.h"
#include <benpatrimonial.h>
#include <escultura.h>
#include <motivodecorativo.h>
#include <lapida.h>
#include <nanodbc/nanodbc.h>

template <typename T>
class IDAOComponedor : public IDAO<T>
{
public:
    virtual void asociarComponentesElemento(const BenPatrimonial& elemento, nanodbc::connection& con) = 0;
    virtual void asociarComponentesElemento(const Escultura& elemento, nanodbc::connection& con) = 0;
    virtual void asociarComponentesElemento(const Lapida& elemento, nanodbc::connection& con) = 0;

    virtual void modificarComponentesElemento(const BenPatrimonial& inicial, const BenPatrimonial& final, nanodbc::connection& con) = 0;
    virtual void modificarComponentesElemento(const Escultura& inicial, const Escultura& final, nanodbc::connection& con) = 0;
    virtual void modificarComponentesElemento(const Lapida& inicial, const Lapida& final, nanodbc::connection& con) = 0;

    virtual std::vector<T> obterComponentesElemento(const BenPatrimonial& elemento, nanodbc::connection& con) = 0;
    virtual std::vector<T> obterComponentesElemento(const Escultura& elemento, nanodbc::connection& con) = 0;
    virtual std::vector<T> obterComponentesElemento(const Lapida& elemento, nanodbc::connection& con) = 0;
};

#endif // IDAOCOMPONEDOR_H
