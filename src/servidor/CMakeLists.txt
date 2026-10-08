cmake_minimum_required(VERSION 3.19)
project(servidorMourisapios VERSION 0.8 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options (-Wpedantic)

add_library(servidorMourisapios OBJECT
    fachadaservidor.h
    fachadaservidor.cpp
    sesion.h
    sesion.cpp
    errosautentificacion.h
    iservidor.h
    configurador/ixestionadorpeticions.h
    configurador/ixestionadorpeticions.cpp
    configurador/xestionadorpeticionsobxetoestudo.h
    configurador/xestionadorpeticionsobxetoestudo.cpp
    configurador/xestionadorpeticionsautenticar.h
    configurador/xestionadorpeticionsautenticar.cpp
    configurador/xestionadorpeticionsimaxe.h
    configurador/xestionadorpeticionsimaxe.cpp
)

target_include_directories(servidorMourisapios
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(servidorMourisapios
    PUBLIC
    ponte)
