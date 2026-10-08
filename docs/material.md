# Materiais

Un material é calquera substancia da que poda estar conformada un [ben patrimonial](./benpatrimonial.md), unha [escultura](./escultura.md) ou unha [lápida](./lapida.md). Pode ser tan xenérico ou específico como sexa desexado. Ten o URI de `/material`

## Atributos
  
| Nome | Descrición | Tipo (JSON) | Opcional na inserción | 
| :---: | :---: | :---: | :---: |
| `nome` | Nome do material | `string` | Non |

## Notas

Sen notas relevantes.

## Listar o inventario

### Descrición

Lista todos os materiais existentes na base de datos.

### Petición HTTP

- Método: `GET /material`.
- Parámetros: N/A.
- Devolve: Código HTTP 200 cun *array* de materiais en JSON se hai inventario do valor, código 204 en caso contrario.

### Acceso

O acceso está permitido aos usuarios consultorios e aos usuarios técnicos.

### Erros

Esta operación devolve os [erros comúns](./erros.md).


### Exemplos

Listar o inventario cun catálogo baldeiro.

`GET /material`

```
HTTP/1.1 204 No Content
Keep-Alive: timeout=5, max=100
Content-Length: 0
```

---

Listar o inventario cun catálogo con cinco materiais.

`GET /material`

```json
HTTP/1.1 200 OK
Content-Type: application/json
Content-Length: 888
Keep-Alive: timeout=5, max=100

[
  {
    "nome": "Granito"
  },
  {
    "nome": "Mármore"
  },
  {
    "nome": "Madeira de carballo"
  },
  {
    "nome": "Bronce"
  },
  {
    "nome": "Pedra calcaria"
  }
]
```

## Buscar o inventario

### Descrición

Busca un material segundo nome exacto.

### Petición HTTP

- Método: `GET /material`.
- Parámetros: JSON cos atributos dun material.
- Devolve: Código HTTP 200 cun *array* de materiais en JSON se hai inventario do valor, código 204 en caso contrario.

### Acceso

O acceso está permitido aos usuarios consultorios e aos usuarios técnicos.

### Erros

Esta operación devolve os [erros comúns](./erros.md).


### Exemplos

Buscar todos os materiais de nome exacto "Aluminio" (non hai ningún).

```json
GET /material
{
  "nome": "Aluminio"
}
```

```
HTTP/1.1 204 No Content
Keep-Alive: timeout=5, max=100
Content-Length: 0
```
---

Buscar todos os materiais de nome exacto "Granito".

```json
GET /material
{
  "nome": "Granito"
}
```

```json
HTTP/1.1 200 OK
Content-Type: application/json
Content-Length: 888
Keep-Alive: timeout=5, max=100

[
  {
    "nome": "Granito"
  }
]
```

## Modificar un inventario

### Descrición

Modifica un material existente, cambiando os parámetros indicados. Automaticamente, tódolos obxectos rexistrados que estean compostos polo material estarán compostos polo novo modificado.

### Petición HTTP

- Método: `POST /material`.
- Parámetros: Lista en JSON con dous materiais, sendo o primeiro o inventario a modificar e de segundo un que contén os valores a modificar.
- Devolve: Código HTTP 200 se a modificación fíxose correctamente.

### Acceso

O acceso está permitido aos usuarios técnicos.

### Erros

Esta operación devolve os [erros comúns](./erros.md) xunto cun erro HTTP 404 de contido

```json
{
  "error": "Obxecto a modificar non existente"
}
```

en caso de que non exista o material a modificar.

### Exemplos

Modificar o material de `nome` = "Madeira de carballo" para que sexa chamado "Madeira de pino".

```json
POST /material
[
  {
    "nome": "Madeira de carballo"
  },
  {
    "nome": "Madeira de pino"
  }
]
```

```
HTTP/1.1 200 OK
Keep-Alive: timeout=5, max=100
Content-Length: 0
```

## Engadir un inventario

### Descrición

Rexistra un material novo na base de datos.

### Petición HTTP

- Método: `PUT /material`.
- Parámetros: JSON cos atributos dun material, necesariamente co parámetros indicados como "opcional na inserción" co valor "non" enchidos.
- Devolve: Código HTTP 201 se a inserción é completada correctamente xunto co material de datos idénticos.

### Acceso

O acceso está permitido aos usuarios técnicos.

### Erros

Esta operación devolve os [erros comúns](./erros.md).

### Exemplos

Inserir un material cos valores dados no exemplo.

```json
PUT /material
{
  "nome": "Bismuto"
}
```

```json
HTTP/1.1 201 Created
Keep-Alive: timeout=5, max=100
Content-Length: 0

{
  "nome": "Bismuto"
}
```

## Eliminar un inventario

### Descrición

Elimina un material existente na base de datos.

### Petición HTTP

- Método: `DELETE /material`.
- Parámetros: JSON cos atributos dun material, necesariamente co parámetro `nome` indicado.
- Devolve: Código HTTP 200 se o borrado foi completado correctamente.

### Acceso

O acceso está permitido aos usuarios técnicos.

### Erros

Esta operación devolve os [erros comúns](./erros.md) xunto cun erro HTTP 404 de contido

```json
{
  "error": "Obxecto a eliminar non existente"
}
```

en caso de que non exista o material a eliminar.

### Exemplos

Eliminar o material de chave `nome` de valor "Bismuto".

```json
DELETE /material
{
  "nome": "Bismuto"
}
```

```json
HTTP/1.1 200 OK
Keep-Alive: timeout=5, max=100
Content-Length: 0
```