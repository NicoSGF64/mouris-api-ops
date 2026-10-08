#ifndef OPTIONALJSON_HPP
#define OPTIONALJSON_HPP
#include "tipousuario.h"
#include <nlohmann/json.hpp>
#include <optional>

// Especialización manual de std::optional para from_json
// Ver https://github.com/nlohmann/json/issues/5246, https://github.com/nlohmann/json/issues/4864
// (Arreglo do Issue 4864 en https://github.com/nlohmann/json/pull/4742 pero inda non sacado ate release)
// TODO: Cando saia soporte real para std::optional, usar eso
namespace nlohmann
{
    template <typename T>
    struct adl_serializer<std::optional<T>> {
        static void to_json(json& j, const std::optional<T>& opt)
        {
            if (opt)
                j = opt.value();
            else
                j = nullptr;
        }

        static void from_json(const json& j, std::optional<T>& opt)
        {
            if (j.is_null())
                opt = std::nullopt;
            else
                opt = j.get<T>();
        }
    };

    // "tipo":{"tipo":0}} é unha abominación así que poñemos algo máis bonito
    template<>
    struct adl_serializer<std::optional<TipoUsuario>> {
        static void to_json(json& j, const std::optional<TipoUsuario>& opt)
        {
            if (opt)
                j = opt.value().getNomeTipo();
            else
                j = nullptr;
        }

        static void from_json(const json& j, std::optional<TipoUsuario>& opt)
        {
            if (j.is_null())
                opt = std::nullopt;
            else
                opt = TipoUsuario(j.get<std::string>());
        }
    };
}

#endif // OPTIONALJSON_HPP
