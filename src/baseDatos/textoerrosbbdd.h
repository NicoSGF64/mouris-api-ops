#ifndef TEXTOERROSBBDD_H
#define TEXTOERROSBBDD_H
#include <string_view>

// Textos de erros para discernir os erros da base de datos, debido a que os códigos SQL son deficientes

constexpr std::string_view baseNonFuncional = "Is the server running";
constexpr std::string_view credenciaisIncorrectas = "password authentication";
constexpr std::string_view parametroInvalidamenteNulo = "violates not-null constraint";
constexpr std::string_view permisoDenegado = "permission denied for table";
constexpr std::string_view lonxitudeLonga = "value too long for type";
constexpr std::string_view nbindeadoMal = "The # of binded parameters < the # of parameter markers";

#endif // TEXTOERROSBBDD_H
