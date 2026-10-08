# Bens Patrimoniais

Un ben patrimonial refírese a calquera obxecto de interese patrimonial tal coma unha pila bautismal, unha campá, un reloxo, un cadro, etc. Dentro desta sección non son consideradas as esculturas, ao teren o seu [propio obxeto](./escultura.md). Ten o URI de `/benpatrimonial`

## Atributos
  
| Nome | Descripción | Tipo (JSON) | Opcional na inserción | 
| :---: | :---: | :---: | :---: |
| `id` | Número identificador único do obxecto dentro da base de datos, compartido coa lista de esculturas | `interger` | N/A | 
| `nome` | Nome non necesariamente único do ben patrimonial | `string` | Non | 
| `descripción` | Descripción textual do ben patrimonial | `string` | Non | 
| `altura` | Altura do ben patrimonial en metros | `number` | Si | 
| `anchura` | Anchura do ben patrimonial en metros | `number` | Si | 
| `datacion` | Ano de creación do ben patrimonial | `integer` | Si | 
| `seculo` | Século de creación do ben patrimonial, en letras romanas maiúsculas | `string` | Si | 
| `segmento` | Sección do século ao que pertence o ben patrimonial | `string` | Si |
| `estilo` | Estilo artístico ao que pertence o ben patrimonial | `string` | Non |
| `taller` | Taller de creación do ben patrimonial | `string` | Si |
| `materiais` | Materiais dos que está composto o ben patrimonial | `array` de [materiais](./material.md) | Si |
| `motivosDecorativos` | Motivos decorativos presentes no ben patrimonial | `array` de [motivos decorativos](./motivodecorativo.md) | Si |
| `imaxe` | Imaxe PNG ou JPEG do ben patrimonial | N/A | Si ([inserido a posteriori](./imaxe.md)) |

## Notas

- O valor de `segmento` só pode ser un dos seguintes: "Primeira metade", "Segunda metade", "Terceira metade", "Primeiro terzo", "Segundo Terzo", "Terceiro terzo", "Primeiro cuarto", "Segundo cuarto", "Terceiro cuarto", "Cuarto cuarto"
- `segmento` e `seculo` deben estar ou ambos establecidos ou ambos en nulo ao inserir os datos
- As imaxes son manipuladas no seu propio URI, `/imaxes/benpatrimonial`

## Listar o inventario

### Descrición

Lista todos os bens patrimoniais existentes na base de datos.

### Petición HTTP

- Método: `GET /benpatrimonial`.
- Parámetros: N/A.
- Devolve: Código HTTP 200 cun *array* de bens patrimoniais en JSON se hai inventario do valor, código 204 en caso contrario.

### Acceso

O acceso está permitido aos usuarios consultorios e aos usuarios técnicos.

### Erros

Esta operación devolve os [erros comúns](./erros.md).


### Exemplos

Listar o inventario cun catálogo baldeiro.

`GET /benpatrimonial`

```
HTTP/1.1 204 No Content
Keep-Alive: timeout=5, max=100
Content-Length: 0
```

---

Listar o inventario cun catálogo con tres obxectos.

`GET /benpatrimonial`

```json
HTTP/1.1 200 OK
Content-Type: application/json
Content-Length: 888
Keep-Alive: timeout=5, max=100

[
  {
    "altura": 25.5,
    "anchura": 12.0,
    "descripcion": "Cáliz litúrxico con decoración vexetal repuxada",
    "estilo": "Barroco",
    "id": 1,
    "materiais": [
      {
        "nome": "Bronce"
      }
    ],
    "motivosDecorativos": [
      {
        "nome": "Flor de lis"
      }
    ],
    "nome": "Cáliz de prata",
    "seculo": "XVIII",
    "segmento": "Primeiro terzo",
    "taller": "Obradoiro de Compostela"
  },
  {
    "altura": 85.0,
    "anchura": 30.0,
    "descripcion": "Custodia de bronce dourado",
    "estilo": "Neoclásico",
    "id": 3,
    "materiais": [
      {
        "nome": "Bronce"
      }
    ],
    "motivosDecorativos": [
      {
        "nome": "Roseta"
      }
    ],
    "nome": "Custodia procesional",
    "seculo": "XIX",
    "segmento": "Primeira metade",
    "taller": "Obradoiro de Lugo"
  },
  {
    "altura": 30.0,
    "anchura": 15.0,
    "descripcion": "Relicario de prata cicelada",
    "estilo": "Renacentista",
    "id": 5,
    "materiais": [
      {
        "nome": "Bronce"
      }
    ],
    "motivosDecorativos": [
      {
        "nome": "Escudo heráldico"
      }
    ],
    "nome": "Relicario de San Bieito",
    "seculo": "XVII",
    "segmento": "Primeiro terzo",
    "taller": "Obradoiro de Santiago"
  }
]
```

## Buscar o inventario

### Descrición

Busca un ben patrimonial segundo os atributos que se especifiquen. Non se permite buscar por motivos decorativos ou materiais.

As buscas son exactas (buscar un `nome` de valor "Peza" devolve todos os bens patrimoniais que se chamen exactamente "Peza", diferenciando maiúsculas e minúsculas).

### Petición HTTP

- Método: `GET /benpatrimonial`.
- Parámetros: JSON cos atributos dun ben patrimonial.
- Devolve: Código HTTP 200 cun *array* de bens patrimoniais en JSON se hai inventario do valor, código 204 en caso contrario.

### Acceso

O acceso está permitido aos usuarios consultorios e aos usuarios técnicos.

### Erros

Esta operación devolve os [erros comúns](./erros.md).


### Exemplos

Buscar todos os bens patrimoniais cuxo taller sexa o Obradoiro de Madrid (non hai ningún).

```json
GET /benpatrimonial
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
  "taller": "Obradoiro de Madrid"
}
```

```
HTTP/1.1 204 No Content
Keep-Alive: timeout=5, max=100
Content-Length: 0
```
---

Buscar todos os bens patrimoniais de trinta metros de altura cuxo taller sexa o Obradoiro de Santiago.

```json
GET /benpatrimonial
{
  "altura": 30.0,
  "anchura": null,
  "descripcion": null,
  "estilo": null,
  "id": null,
  "materiais": [],
  "motivosDecorativos": [],
  "nome": null,
  "seculo": null,
  "segmento": null,
  "taller": "Obradoiro de Santiago"
}
```

```json
HTTP/1.1 200 OK
Content-Type: application/json
Content-Length: 888
Keep-Alive: timeout=5, max=100

[
  {
    "altura": 30.0,
    "anchura": 15.0,
    "descripcion": "Relicario de prata cicelada",
    "estilo": "Renacentista",
    "id": 5,
    "materiais": [
      {
        "nome": "Bronce"
      }
    ],
    "motivosDecorativos": [
      {
        "nome": "Escudo heráldico"
      }
    ],
    "nome": "Relicario de San Bieito",
    "seculo": "XVII",
    "segmento": "Primeiro terzo",
    "taller": "Obradoiro de Santiago"
  }
]
```

## Modificar un inventario

### Descrición

Modifica un ben patrimonial existente, cambiando os parámetros indicados.

Se un inventario está composto de materiais ou foron definidos motivos decorativos para este, non é posible modificalo para desasociar os materiais ou motivos decorativos deste.

### Petición HTTP

- Método: `POST /benpatrimonial`.
- Parámetros: Lista en JSON con dous bens patrimoniais, sendo o primeiro o inventario a modificar e de segundo un que contén os valores a modificar.
  - Só é inspeccionado no primeiro ben patrimonial o valor `id`. O resto de valores deberían ser postos a `null`, ou é posible que se produzan erros HTTP 404.
- Devolve: Código HTTP 200 se a modificación fíxose correctamente.

### Acceso

O acceso está permitido aos usuarios técnicos.

### Erros

Esta operación devolve os [erros comúns](./erros.md) xunto cun erro HTTP 404 de contido

```json
{
  "error": "Obxeto a modificar non existente"
}
```

en caso de que non exista o ben patrimonial a modificar.

### Exemplos

Modificar o ben patrimonial de id = 5 para que teña unha altura de 50m e unha altura de 20,25m.

```json
POST /benpatrimonial
[
  {
    "altura": null,
    "anchura": null,
    "descripcion": null,
    "estilo": null,
    "id": 5,
    "materiais": [],
    "motivosDecorativos": [],
    "nome": null,
    "seculo": null,
    "segmento": null,
    "taller": null
  }
  ,{
    "altura": 50.0,
    "anchura": 20.25,
    "descripcion": null,
    "estilo": null,
    "id": null,
    "materiais": [],
    "motivosDecorativos": [],
    "nome": null,
    "seculo": null,
    "segmento": null,
    "taller": null
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

Rexistra un ben patrimonial novo na base de datos.

Os materiais e motivos decorativos que compoñen o ben patrimonial deben existir previamente na base de datos.

### Petición HTTP

- Método: `PUT /benpatrimonial`
- Parámetros: JSON cos atributos dun ben patrimonial, necesariamente co parámetros indicados como "opcional na inserción" co valor "non" enchidos.
- Devolve: Código HTTP 201 se a inserción é completada correctamente xunto co ben patrimonial de datos idénticos co valor `id` asignado internamente.

### Acceso

O acceso está permitido aos usuarios técnicos.

### Erros

Esta operación devolve os [erros comúns](./erros.md).

### Exemplos

Inserir un ben patrimonial cos valores dados no exemplo.

```json
PUT /benpatrimonial
{
  "altura": 5.0,
  "anchura": 7.23,
  "descripcion": "Pila bautismal de pedra en boa condición, de orixe descoñecido.",
  "estilo": "Neoclásico",
  "id": null,
  "materiais": [
    {
      "nome": "Pedra calcaria"
    }
  ],
  "motivosDecorativos": [],
  "nome": "Pila bautismal da igrexa de Mondariz",
  "seculo": "XIX",
  "segmento": "Primeiro terzo",
  "taller": null
}
```

```json
HTTP/1.1 201 Created
Keep-Alive: timeout=5, max=100
Content-Length: 0

{
  "altura": 5.0,
  "anchura": 7.23,
  "descripcion": "Pila bautismal de pedra en boa condición, de orixe descoñecido.",
  "estilo": "Neoclásico",
  "id": 6,
  "materiais": [
    {
      "nome": "Pedra calcaria"
    }
  ],
  "motivosDecorativos": [],
  "nome": "Pila bautismal da igrexa de Mondariz",
  "seculo": "XIX",
  "segmento": "Primeiro terzo",
  "taller": null
}
```

## Eliminar un inventario

### Descrición

Elimina un ben patrimonial existente na base de datos.

### Petición HTTP

- Método: `DELETE /benpatrimonial`.
- Parámetros: JSON cos atributos dun ben patrimonial, necesariamente co parámetro `id` indicado.
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

en caso de que non exista o ben patrimonial a eliminar.

### Exemplos

Eliminar o ben patrimonial de chave `id` de valor 6.

```json
DELETE /benpatrimonial
{
  "altura": null,
  "anchura": null,
  "descripcion": null,
  "estilo": null,
  "id": 6,
  "materiais": [],
  "motivosDecorativos": [],
  "nome": null,
  "seculo": null,
  "segmento": null,
  "taller": null
}
```

```json
HTTP/1.1 200 OK
Keep-Alive: timeout=5, max=100
Content-Length: 0
```