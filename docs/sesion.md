# Xestión de Sesións

Tódalas peticións dirixidas ao servidor que conten a base de datos deben estar asignadas a unha sesión que fora creada previamente a esta, que debe ser pechada cando non se van facer máis peticións ao servidor. A xestión de sesións faise sobre a URI `/autenticar`.

As sesións por defecto teñen unha validez de media hora, que é renovada ao facer calquera operación sobre o servidor. Se caduca unha sesión, esta debe volver a iniciarse.

Toda petición feita sobre o servidor, incluída estas, debe levar na cabeceira unha autenticación de tipo `Basic` co nome e contrasinal do usuario codificado en base 64 en formato `nome:contrasinal`. O nome non debe conter dous puntos.

## Iniciar sesión

### Petición HTTP

- Método: `POST /autenticar`.
- Parámetros: Ningún, salvo o valor da cabeceira `Authorization` posto correctamente.
- Devolve: Código HTTP 200 se a modificación fíxose correctamente.

### Erros

Esta operación devolve os [erros comúns](./erros.md) xunto cun erro HTTP 403 de contido

```json
{
  "error": "Erro de autenticación"
}
```

en caso de que xa exista a sesión e un erro HTTP 401 de contido 

```json
{
  "error": "Nome de usuario ou contrasinal incorrectas"
}
```

en caso de que o usuario ou contrasinal non sexan correctas.

## Pechar sesión

### Petición HTTP

- Método: `DELETE /autenticar`.
- Parámetros: Ningún, salvo o valor da cabeceira `Authorization` posto correctamente.
- Devolve: Código HTTP 200 se o borrado foi completado correctamente.

### Erros

Esta operación devolve os [erros comúns](./erros.md) xunto cun erro HTTP 403 de contido

```json
{
  "error": "Erro de autenticación"
}
```

en caso de que non exista a sesión a borrar ou o usuario ou contrasinal estean incorrectos.