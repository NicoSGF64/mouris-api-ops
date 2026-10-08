# Usuarios

Un usuario é calquera persona que ten acceso ao sistema. Este documento só cubre a manipulación de contas, para ver como iniciar e pechar sesión, ver [o documento correspondente](./sesion.md). Ten o URI de `/usuario`.

## Atributos
  
| Nome | Descrición | Tipo (JSON) | Opcional na inserción | 
| :---: | :---: | :---: | :---: |
| `nome` | Nome do usuario | `string` | Non |
| `contrasinal` | Contrasinal do usuario | `string` | Non | 
| `tipo` | Tipo do usuario | `string` | Non | 

## Notas

O `tipo_usuario` debe ser ou ben `usuario_consultorio`, `usuario_tecnico` ou `administrador_sistema`.

Os primeiros teñen acceso á lectura de información de datos patrimoniais (esculturas, lápidas, etc.), os segundos teñen de lectura, inserción, modificación e borrado destes mesmo, e os últimos de lectura, inserción, modificación e borrado sobre as contas de usuario tal coma descrito neste documento.

## Listar usuarios

### Descrición

Lista todos os usuarios existentes na base de datos.

### Petición HTTP

- Método: `GET /usuario`.
- Parámetros: N/A.
- Devolve: Código HTTP 200 cun *array* de usuarios en JSON se hai inventario do valor, código 204 en caso contrario. Non se amosan as contrasinais dos usuarios na listaxe.

### Acceso

O acceso está permitido aos usuarios administrativos.

### Erros

Esta operación devolve os [erros comúns](./erros.md).


### Exemplos

Listar o inventario cun catálogo baldeiro.

`GET /usuario`

```
HTTP/1.1 204 No Content
Keep-Alive: timeout=5, max=100
Content-Length: 0
```

---

Listar o inventario cun catálogo con cinco usuarios.

`GET /usuario`

```json
HTTP/1.1 200 OK
Content-Type: application/json
Content-Length: 888
Keep-Alive: timeout=5, max=100

[
  {
    "contrasinal": null,
    "nomeUsuario": "jperez",
    "tipo": "usuario_consultorio"
  },
  {
    "contrasinal": null,
    "nomeUsuario": "mrodriguez",
    "tipo": "usuario_tecnico"
  },
  {
    "contrasinal": null,
    "nomeUsuario": "admin1",
    "tipo": "administrador_sistema"
  },
  {
    "contrasinal": null,
    "nomeUsuario": "lgonzalez",
    "tipo": "usuario_consultorio"
  },
  {
    "contrasinal": null,
    "nomeUsuario": "mmartinez",
    "tipo": "usuario_consultorio"
  }
]
```

## Buscar usuarios

### Descrición

Busca un usuario segundo nome exacto.

### Petición HTTP

- Método: `GET /usuario`
- Parámetros: JSON cos atributos dun usuario. Calquera valor introducido en `contrasinal` é ignorado.
- Devolve: Código HTTP 200 cun *array* de usuarios en JSON se hai inventario do valor, código 204 en caso contrario. Non se amosan as contrasinais dos usuarios na listaxe.

### Acceso

O acceso está permitido aos usuarios administrativos.

### Erros

Esta operación devolve os [erros comúns](./erros.md).


### Exemplos

Buscar todos os usuarios de `tipo` "usuario_consultorio".

```json
GET /usuario
{
  "contrasinal": null,
  "nomeUsuario": null,
  "tipo": "usuario_consultorio"
}
```

```
HTTP/1.1 200 OK
Keep-Alive: timeout=5, max=100
Content-Length: 0
[
  {
    "contrasinal": null,
    "nomeUsuario": "jperez",
    "tipo": "usuario_consultorio"
  },
  {
    "contrasinal": null,
    "nomeUsuario": "lgonzalez",
    "tipo": "usuario_consultorio"
  },
  {
    "contrasinal": null,
    "nomeUsuario": "mmartinez",
    "tipo": "usuario_consultorio"
  }
]
```

## Modificar un usuario

### Descrición

Modifica un usuario existente, cambiando os parámetros indicados. Non é posible cambiar o tipo de usuario.

### Petición HTTP

- Método: `POST /usuario`
- Parámetros: Lista en JSON con dous usuarios, sendo o primeiro o usuario  a modificar necesariamente co campo `nomeUsuario` enchido e de segundo un que contén os valores a modificar
  - Ao non ser posible modificar o tipo de usuario, o campo `tipo` debería ser nulo.
- Devolve: Código HTTP 200 se a modificación fíxose correctamente.

### Acceso

O acceso está permitido aos usuarios administrativos.

### Erros

Esta operación devolve os [erros comúns](./erros.md) xunto cun erro HTTP 404 de contido

```json
{
  "error": "Obxecto a modificar non existente"
}
```

en caso de que non exista o usuario a modificar.

### Exemplos

Modificar o usuario de nome de usuario "jperez" para que teña o nome de usuario "lperez" e a contrasinal "1234".

```json
POST /usuario
[
  {
    "contrasinal": null,
    "nomeUsuario": "jperez",
    "tipo": null
  },
  {
    "contrasinal": "1234",
    "nomeUsuario": "lgonzalez",
    "tipo": null
  },
]
```

```
HTTP/1.1 200 OK
Keep-Alive: timeout=5, max=100
Content-Length: 0
```

## Engadir un usuario

### Descrición

Rexistra un usuario novo na base de datos. Non se permite crear usuarios de tipo `usuario_administrativo`.

### Petición HTTP

- Método: `PUT /usuario`.
- Parámetros: JSON cos atributos dun usuario, necesariamente co parámetros indicados como "opcional na inserción" co valor "non" enchidos.
- Devolve: Código HTTP 201 se a inserción é completada correctamente xunto co usuario de datos idénticos.

### Acceso

O acceso está permitido aos usuarios administrativos.

### Erros

Esta operación devolve os [erros comúns](./erros.md).

### Exemplos

Inserir un usuario cos valores dados no exemplo.

```json
PUT /usuario
{
  "contrasinal": "kkkk",
  "nomeUsuario": "mgomez",
  "tipo": "usuario_tecnico"
}
```

```json
HTTP/1.1 201 Created
Keep-Alive: timeout=5, max=100
Content-Length: 0

{
  "contrasinal": "kkkk",
  "nomeUsuario": "mgomez",
  "tipo": "usuario_tecnico"
}
```

## Eliminar un inventario

### Descrición

Elimina un usuario existente na base de datos.

### Petición HTTP

- Método: `DELETE /usuario`.
- Parámetros: JSON cos atributos dun usuario, necesariamente co parámetro `nome` indicado.
- Devolve: Código HTTP 200 se o borrado foi completado correctamente.

### Acceso

O acceso está permitido aos usuarios administrativos.

### Erros

Esta operación devolve os [erros comúns](./erros.md) xunto cun erro HTTP 404 de contido

```json
{
  "error": "Obxecto a eliminar non existente"
}
```

en caso de que non exista o usuario a eliminar.

### Exemplos

Eliminar o usuario de chave `nomeUsuario` de valor "mgomez".

```json
DELETE /usuario
{
  "contrasinal": null,
  "nomeUsuario": "mgomez",
  "tipo": null
}
```

```json
HTTP/1.1 200 OK
Keep-Alive: timeout=5, max=100
Content-Length: 0
```  