cmake_minimum_required(VERSION 3.19)
project(comunMourisapios VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options (-Wpedantic)

add_library(comunMourisapios OBJECT
    benpatrimonial.h
    benpatrimonial.cpp
    datacion.h
    escultura.cpp
    escultura.h
    estadoConservacion.h
    lapida.h
    lapida.cpp
    material.h
    material.cpp
    motivodecorativo.cpp
    motivodecorativo.h
    tipousuario.cpp
    tipousuario.h
    usuario.h
    usuario.cpp
    obxetoestudo.h
    optionaljson.hpp
    imaxe/imaxe.h
    imaxe/imaxe.cpp
    imaxe/imaxepng.h
    imaxe/imaxepng.cpp
    imaxe/imaxejpeg.h
    imaxe/imaxejpeg.cpp
    imaxe/fabricaimaxe.h
    imaxe/fabricaimaxe.cpp
    imaxe/errosimaxe.h
    parseadorlineacomandos.h
    parseadorlineacomandos.cpp
)

target_include_directories(comunMourisapios
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(comunMourisapios
    PUBLIC
    ponte)
