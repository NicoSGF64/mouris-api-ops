cmake_minimum_required(VERSION 3.19)
project(mourisapios VERSION 0.1 LANGUAGES CXX)

add_compile_definitions(DEBUG)

add_library(ponte INTERFACE)

find_package(OpenSSL REQUIRED)

add_compile_options (-Wall -O2)

add_executable(mourisapios src/main.cpp)

target_include_directories(ponte INTERFACE
    ${CMAKE_SOURCE_DIR}/src/comun
    ${CMAKE_SOURCE_DIR}/src/baseDatos
    ${CMAKE_SOURCE_DIR}/src/servidor
    ${CMAKE_SOURCE_DIR}/src/lib/nanodbc
)

add_subdirectory(src/lib/nanodbc)
add_subdirectory(src/comun)
add_subdirectory(src/baseDatos)
add_subdirectory(src/servidor)

target_link_libraries(mourisapios
    PRIVATE
    comunMourisapios
    backendMourisapios
    servidorMourisapios
    nanodbc
    OpenSSL::SSL
    OpenSSL::Crypto)

option(BUILD_DOC "Facer a documentación" ON)

find_package(Doxygen)
if (DOXYGEN_FOUND)
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

    add_custom_target(doc_doxygen ALL
	COMMENT "Xerando a documentación con DOxygen"
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        VERBATIM )
else (DOXYGEN_FOUND)
  message("Falta a instalación de DOxygen")
endif (DOXYGEN_FOUND)
