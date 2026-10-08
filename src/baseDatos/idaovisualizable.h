#ifndef IDAOVISUALIZABLE_H
#define IDAOVISUALIZABLE_H
#include <imaxe/imaxe.h>
#include "idao.h"

template <typename T>
class IDAOVisualizable : public IDAO<T>
{
public:
    using IDAO<T>::ligarParametro;

    virtual std::unique_ptr<Imaxe> obterImaxe(const T& parametros, nanodbc::connection& con) = 0;

    virtual void rexistrarImaxe(const T& parametros, const Imaxe& imaxe, nanodbc::connection& con) = 0;

    virtual void eliminarImaxe(const T& parametros, nanodbc::connection& con) = 0;

protected:
    static constexpr void ligarParametro(const std::vector<std::vector<std::uint8_t>>& ligadura, nanodbc::statement& consulta, unsigned short& pos)
    {
        consulta.bind(pos, ligadura);
        pos++;
    }

    // Código tomado de https://github.com/nanodbc/nanodbc/blob/fd9b4f551b0f03780168c4b2ba880dcb5777aad4/test/base_test_fixture.h
    static std::vector<std::uint8_t> from_hex(const std::string& hex)
    {
        if (hex.empty() || 0 != hex.size() % 2)
            throw std::runtime_error("invalid lenght of hex string");

        std::string::size_type const nchars = 2;
        std::string::size_type const nbytes = hex.size() / nchars;
        std::vector<std::uint8_t> bytes(nbytes);
        for (std::string::size_type i = 0; i < nbytes; ++i)
        {
            std::istringstream iss(hex.substr(i * nchars, nchars));
            unsigned int n(0);
            if (!(iss >> std::hex >> n))
                throw std::runtime_error("hex to binary failed");
            bytes[i] = static_cast<std::uint8_t>(n);
        }
        return bytes;
    }

    static std::string to_hex(const std::vector<std::uint8_t>& bytes)
    {
        std::ostringstream ss;
        ss << std::hex << std::setfill('0') << std::uppercase;
        for (auto const& b : bytes)
            ss << std::setw(2) << static_cast<int>(b);
        return ss.str();
    }
};

#endif // IDAOVISUALIZABLE_H
