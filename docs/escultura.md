# Esculturas

Unha escultura é calquera tallado que represente un ídolo, humano ou polo contrario, de interese para rexistro. Ten o URI de `/escultura`

## Atributos
  
| Nome | Descripción | Tipo (JSON) | Opcional na inserción | 
| :---: | :---: | :---: | :---: |
| `id` | Número identificador único do obxecto dentro da base de datos, compartido coa lista de bens patrimoniais | `interger` | N/A | 
| `nome` | Nome non necesariamente único da escultura | `string` | Non | 
| `descripción` | Descripción textual da escultura | `string` | Non | 
| `altura` | Altura da escultura en metros | `number` | Si | 
| `anchura` | Anchura da escultura en metros | `number` | Si | 
| `datacion` | Ano de creación da escultura | `integer` | Si | 
| `seculo` | Século de creación da escultura, en letras romanas maiúsculas | `string` | Si | 
| `segmento` | Sección do século ao que pertence a escultura | `string` | Si |
| `estilo` | Estilo artístico ao que pertence a escultura | `string` | Non |
| `taller` | Taller de creación da escultura | `string` | Si |
| `materiais` | Materiais dos que está composto a escultura | `array` de [materiais](./material.md) | Si |
| `motivosDecorativos` | Motivos decorativos presentes na escultura | `array` de [motivos decorativos](./motivodecorativo.md) | Si |
| `santoRepresentado` | Santo ou ídolo representado da escultura | `string` | Non |
| `imaxe` | Imaxe PNG ou JPEG da escultura | N/A | Si ([inserido a posteriori](./imaxe.md)) |

## Notas

- O valor de `segmento` só pode ser un dos seguintes: "Primeira metade", "Segunda metade", "Terceira metade", "Primeiro terzo", "Segundo Terzo", "Terceiro terzo", "Primeiro cuarto", "Segundo cuarto", "Terceiro cuarto", "Cuarto cuarto"
- `segmento` e `seculo` deben estar ou ambos establecidos ou ambos en nulo ao inserir os datos
- As imaxes son manipuladas no seu propio URI, `/imaxes/escultura`

## Listar o inventario

### Descrición

Lista todos as esculturas existentes na base de datos.

### Petición HTTP

- Método: `GET /escultura`.
- Parámetros: N/A.
- Devolve: Código HTTP 200 cun *array* de esculturas en JSON se hai inventario do valor, código 204 en caso contrario.

### Acceso

O acceso está permitido aos usuarios consultorios e aos usuarios técnicos.

### Erros

Esta operación devolve os [erros comúns](./erros.md).


### Exemplos

Listar o inventario cun catálogo baldeiro.

`GET /escultura`

```
HTTP/1.1 204 No Content
Keep-Alive: timeout=5, max=100
Content-Length: 0
```

---

Listar o inventario cun catálogo con dous obxectos.

`GET /escultura`

```json
HTTP/1.1 200 OK
Content-Type: application/json
Content-Length: 888
Keep-Alive: timeout=5, max=100

[
  {
    "altura": 110.0,
    "anchura": 40.0,
    "descripcion": "Escultura en madeira policromada",
    "estilo": "Barroco",
    "id": 2,
    "materiais": [
      {
        "nome": "Madeira de carballo"
      }
    ],
    "motivosDecorativos": [
      {
        "nome": "Cruz latina"
      }
    ],
    "nome": "Talla de San Roque",
    "santoRepresentado": "San Roque",
    "seculo": "XVII",
    "segmento": "Terceiro terzo",
    "taller": "Obradoiro de Ourense"
  },
  {
    "altura": 95.0,
    "anchura": 45.0,
    "descripcion": "Escultura en madeira con manto de tea encolada",
    "estilo": "Barroco",
    "id": 4,
    "materiais": [
      {
        "nome": "Madeira de carballo"
      }
    ],
    "motivosDecorativos": [
      {
        "nome": "Vieira"
      }
    ],
    "nome": "Talla da Virxe do Carme",
    "santoRepresentado": "Nosa Señora do Carme",
    "seculo": "XVIII",
    "segmento": "Primeiro terzo",
    "taller": "Obradoiro de Pontevedra"
  }
]
```

## Buscar o inventario

### Descrición

Busca unha escultura segundo os atributos que se especifiquen. Non se permite buscar por motivos decorativos ou materiais.

As buscas son exactas (buscar un `nome` de valor "Peza" devolve todos os bens patrimoniais que se chamen exactamente "Peza", diferenciando maiúsculas e minúsculas).

### Petición HTTP

- Método: `GET /escultura`.
- Parámetros: JSON cos atributos dunha escultura.
- Devolve: Código HTTP 200 cun *array* de bens patrimoniais en JSON se hai inventario do valor, código 204 en caso contrario

### Acceso

O acceso está permitido aos usuarios consultorios e aos usuarios técnicos.

### Erros

Esta operación devolve os [erros comúns](./erros.md).


### Exemplos

Buscar todas as esculturas cuxo taller sexa o Obradoiro de Madrid (non hai ningún).

```json
GET /escultura
{
  "altura": null,
  "anchura": null,
  "descripcion": null,
  "estilo": null,
  "id": null,
  "materiais": [],
  "motivosDecorativos": [],
  "nome": null,
  "santoRepresentado": null,
  "seculo": null,
  "segmento": null,
  "taller": "Obradoiro de Madrid",
  "santoRepresentado": null
}
```

```
HTTP/1.1 204 No Content
Keep-Alive: timeout=5, max=100
Content-Length: 0
```
---

Buscar todas esculturas de que ilustran a Virxe do Carme.

```json
GET /escultura
{
  "altura": null,
  "anchura": null,
  "descripcion": null,
  "estilo": null,
  "id": null,
  "materiais": [],
  "motivosDecorativos": [],
  "nome": null,
  "seculo": null,
  "segmento": null,
  "taller": null,
  "santoRepresentado": "Nosa Señora do Carme"
}
```

```json
HTTP/1.1 200 OK
Content-Type: application/json
Content-Length: 888
Keep-Alive: timeout=5, max=100

[
  {
    "altura": 95.0,
    "anchura": 45.0,
    "descripcion": "Escultura en madeira con manto de tea encolada",
    "estilo": "Barroco",
    "id": 4,
    "materiais": [
      {
        "nome": "Madeira de carballo"
      }
    ],
    "motivosDecorativos": [
      {
        "nome": "Vieira"
      }
    ],
    "nome": "Talla da Virxe do Carme",
    "santoRepresentado": "Nosa Señora do Carme",
    "seculo": "XVIII",
    "segmento": "Primeiro terzo",
    "taller": "Obradoiro de Pontevedra"
  }
]
```

## Modificar un inventario

### Descrición

Modifica unha escultura existente, cambiando os parámetros indicados.

Se un inventario está composto de materiais ou foron definidos motivos decorativos para este, non é posible modificalo para desasociar os materiais ou motivos decorativos deste.

### Petición HTTP

- Método: `POST /escultura`.
- Parámetros: Lista en JSON con dúas esculturas, sendo a primeira o inventario a modificar e a segunda unha que contén os valores a modificar.
  - Só é inspeccionado no primeira escultura o valor `id`. O resto de valores deberían ser postos a `null`, ou é posible que se produzan erros HTTP 404.
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

en caso de que non exista a escultura a modificar.

### Exemplos

Modificar a escultura de `id` 4 para que sexa de estilo "Renacentista".

```json
POST /escultura
[
  {
    "altura": null,
    "anchura": null,
    "descripcion": null,
    "estilo": null,
    "id": 4,
    "materiais": [],
    "motivosDecorativos": [],
    "nome": null,
    "seculo": null,
    "segmento": null,
    "taller": null,
    "santoRepresentado": null
  }
  ,{
    "altura": null,
    "anchura": null,
    "descripcion": null,
    "estilo": "Renacentista",
    "id": null,
    "materiais": [],
    "motivosDecorativos": [],
    "nome": null,
    "seculo": null,
    "segmento": null,
    "taller": null,
    "santoRepresentado": null
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

Rexistra unha escultura novo na base de datos.

Os materiais e motivos decorativos que compoñen a escultura deben existir previamente na base de datos.

### Petición HTTP

- Método: `PUT /escultura`
- Parámetros: JSON cos atributos dunha escultura, necesariamente co parámetros indicados como "opcional na inserción" co valor "non" enchidos.
- Devolve: Código HTTP 201 se a inserción é completada correctamente xunto ca escultura de datos idénticos co valor `id` asignado internamente.

### Acceso

O acceso está permitido aos usuarios técnicos.

### Erros

Esta operación devolve os [erros comúns](./erros.md).

### Exemplos

Inserir unha escultura cos valores dados no exemplo.

```json
PUT /escultura
{
  "altura": 2.0,
  "anchura": 10.0,
  "descripcion": "Escultura policromada recentemente repintada que represente a San Benito",
  "estilo": "Contemporáneo",
  "id": null,
  "materiais": [
    {
      "nome": "Madeira de carballo"
    }
  ],
  "motivosDecorativos": [],
  "nome": "Estatua de San Benito",
  "santoRepresentado": "San Benito",
  "seculo": "XX",
  "segmento": "Primeiro terzo",
  "taller": null,
  "santoRepresentado": null
}
```

```json
HTTP/1.1 201 Created
Keep-Alive: timeout=5, max=100
Content-Length: 0

{
  "altura": 2.0,
  "anchura": 10.0,
  "descripcion": "Escultura policromada recentemente repintada que represente a San Benito",
  "estilo": "Contemporáneo",
  "id": 7,
  "materiais": [
    {
      "nome": "Madeira de carballo"
    }
  ],
  "motivosDecorativos": [],
  "nome": "Estatua de San Benito",
  "santoRepresentado": "San Benito",
  "seculo": "XX",
  "segmento": "Primeiro terzo",
  "taller": null,
  "santoRepresentado": null
}
```

## Eliminar un inventario

### Descrición

Elimina unha escultura existente na base de datos.

### Petición HTTP

- Método: `DELETE /escultura`.
- Parámetros: JSON cos atributos dunha escultura, necesariamente co parámetro `id` indicado.
  - Só é inspeccionado o valor `id`. O resto de valores deberían ser postos a `null`, ou é posible que se produzan erros HTTP 404.
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

en caso de que non exista a escultura a eliminar.

### Exemplos

Eliminar a escultura de chave `id` de valor 7.

```json
DELETE /escultura
{
  "altura": null,
  "anchura": null,
  "descripcion": null,
  "estilo": null,
  "id": 7,
  "materiais": [],
  "motivosDecorativos": [],
  "nome": null,
  "seculo": null,
  "segmento": null,
  "taller": null,
  "santoRepresentado": null
}
```

```json
HTTP/1.1 200 OK
Keep-Alive: timeout=5, max=100
Content-Length: 0
```