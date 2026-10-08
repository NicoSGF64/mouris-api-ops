# Motivos Decorativos

Un motivo decorativo representa unha característica artística asociada a un [ben patrimonial](./benpatrimonial.md), unha [escultura](./escultura.md) ou unha [lápida](./lapida.md). Ten o URI de `/motivodecorativo`

## Atributos
  
| Nome | Descrición | Tipo (JSON) | Opcional na inserción | 
| :---: | :---: | :---: | :---: |
| `nome` | Nome do motivo decorativo | `string` | Non | 

## Notas

Sen notas relevantes.

## Listar o inventario

### Descrición

Lista todos os motivos decorativos existentes na base de datos.

### Petición HTTP

- Método: `GET /motivodecorativo`.
- Parámetros: N/A.
- Devolve: Código HTTP 200 cun *array* de motivos decorativos en JSON se hai inventario do valor, código 204 en caso contrario.

### Acceso

O acceso está permitido aos usuarios consultorios e aos usuarios técnicos.

### Erros

Esta operación devolve os [erros comúns](./erros.md).


### Exemplos

Listar o inventario cun catálogo baldeiro.

`GET /motivodecorativo`

```
HTTP/1.1 204 No Content
Keep-Alive: timeout=5, max=100
Content-Length: 0
```

---

Listar o inventario cun catálogo con cinco motivos decorativos.

`GET /motivodecorativo`

```json
HTTP/1.1 200 OK
Content-Type: application/json
Content-Length: 888
Keep-Alive: timeout=5, max=100

[
  {
    "nome": "Cruz latina"
  },
  {
    "nome": "Roseta"
  },
  {
    "nome": "Vieira"
  },
  {
    "nome": "Escudo heráldico"
  },
  {
    "nome": "Flor de lis"
  }
]
```

## Buscar o inventario

### Descrición

Busca un motivo decorativo segundo nome exacto.

### Petición HTTP

- Método: `GET /motivodecorativo`.
- Parámetros: JSON cos atributos dun motivo decorativo.
- Devolve: Código HTTP 200 cun *array* de motivos decorativos en JSON se hai inventario do valor, código 204 en caso contrario

### Acceso

O acceso está permitido aos usuarios consultorios e aos usuarios técnicos.

### Erros

Esta operación devolve os [erros comúns](./erros.md).


### Exemplos

Buscar todos os motivos decorativos de nome exacto "Sfumatto" (non hai ningún).

```json
GET /motivodecorativo
{
  "nome": "Sfumatto"
}
```

```
HTTP/1.1 204 No Content
Keep-Alive: timeout=5, max=100
Content-Length: 0
```
---

Buscar todos os motivos decorativos de nome exacto "Roseta".

```json
GET /motivodecorativo
{
  "nome": "Roseta"
}
```

```json
HTTP/1.1 200 OK
Content-Type: application/json
Content-Length: 888
Keep-Alive: timeout=5, max=100

[
  {
    "nome": "Roseta"
  }
]
```

## Modificar un inventario

### Descrición

Modifica un motivo decorativo existente, cambiando os parámetros indicados. Automaticamente, tódolos obxectos rexistrados que estean compostos polo motivo decorativo estarán compostos polo novo modificado.

### Petición HTTP

- Método: `POST /motivodecorativo`.
- Parámetros: Lista en JSON con dous motivos decorativos, sendo o primeiro o inventario a modificar e de segundo un que contén os valores a modificar.
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

en caso de que non exista o motivo decorativo a modificar.

### Exemplos

Modificar o material de `nome` = "Roseta" para que sexa chamado "Broche floral".

```json
POST /motivodecorativo
[
  {
    "nome": "Roseta"
  },
  {
    "nome": "Broche floral"
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

Rexistra un motivo decorativo novo na base de datos.

### Petición HTTP

- Método: `PUT /motivo decorativo`.
- Parámetros: JSON cos atributos dun motivo decorativo, necesariamente co parámetros indicados como "opcional na inserción" co valor "non" enchidos.
- Devolve: Código HTTP 201 se a inserción é completada correctamente xunto co motivo decorativo de datos idénticos.

### Acceso

O acceso está permitido aos usuarios técnicos.

### Erros

Esta operación devolve os [erros comúns](./erros.md).

### Exemplos

Inserir un motivo decorativo cos valores dados no exemplo.

```json
PUT /motivodecorativo
{
  "nome": "Ménsula"
}
```

```json
HTTP/1.1 201 Created
Keep-Alive: timeout=5, max=100
Content-Length: 0

{
  "nome": "Ménsula"
}
```

## Eliminar un inventario

### Descrición

Elimina un motivo decorativo existente na base de datos.

### Petición HTTP

- Método: `DELETE /motivodecorativo`.
- Parámetros: JSON cos atributos dun motivo decorativo, necesariamente co parámetro `nome` indicado.
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

en caso de que non exista o motivo decorativo a eliminar.

### Exemplos

Eliminar o motivo decorativo de chave `nome` de valor "Ménsula".

```json
DELETE /motivodecorativo
{
  "nome": "Ménsula"
}
```

```json
HTTP/1.1 200 OK
Keep-Alive: timeout=5, max=100
Content-Length: 0
```