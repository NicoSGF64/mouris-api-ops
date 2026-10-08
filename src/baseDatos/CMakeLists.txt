cmake_minimum_required(VERSION 3.19)
project(backendMourisapios VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options (-Wpedantic)

add_library(backendMourisapios OBJECT
    benpatrimonialdao.cpp
    benpatrimonialdao.h
    esculturadao.cpp
    esculturadao.h
    fachadabasedatos.cpp
    fachadabasedatos.h
    idao.h
    lapidadao.cpp
    lapidadao.h
    materialdao.cpp
    materialdao.h
    motivodecorativodao.cpp
    motivodecorativodao.h
    usuariodao.cpp
    usuariodao.h
    fabricadao.h
    idaovisualizable.h
    idaocomponedor.h
    imaxedao.h
    imaxedao.cpp
    textoerrosbbdd.h
)

target_include_directories(backendMourisapios
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(backendMourisapios
    PUBLIC
    ponte
    nanodbc
)
