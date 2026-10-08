# Lápidas

## Descrición
A sección de lápidas recolle calquera xacemento de interese. Ten o URI de `/lápida`

## Atributos

  
| Nome | Descripción | Tipo (JSON) | Opcional na inserción | 
| :---: | :---: | :---: | :---: |
| `id` | Número identifAuraicador único do obxecto dentro da base de datos | `integer` | N/A | 
| `xenealoxia` | Descrición da xenealoxía da persoa enterrada | `string` | Si | 
| `epigrafia` | Texto que figura na inscripción da lápida | `string` | Si | 
| `datación` | Data que figura na lápida | `object` (ver notas) | Si (ver notas) | 
| `paq` | <b>P</b>roxecto <b>A</b>r<b>q</b>uitectónico da lápida, é dicir, localización | `string` | Si | 
| `estadoConservacionBioloxico` | Estado de conservación biolóxico da lápida | `object` (ver notas) | Si (ver notas) | 
| `estadoConservacionAtmosferico` | Estado de conservación atmosférico da lápida | `object` (ver notas) | Si (ver notas) |
| `materiais` | Materiais dos que está composto a lápida | `array` de [materiais](./material.md) | Si |
| `motivosDecorativos` | Motivos decorativos presentes na lápida | `array` de [motivos decorativos](./motivodecorativo.md) | Si
| `imaxe` | Imaxe PNG ou JPEG da lápida | N/A | Si ([inserido a posteriori](./imaxe.md)) |

## Notas

- `datacion` ten o seguinte formato de `object`:

```json
"datacion":
{
  "ano": integer,
  "dia": integer,
  "mes": integer
},
```

- `datacion`, en caso de non ser establecido na inserción, é posto por defecto ao día actual. Por este motivo, é aconsellable establecer os valores correctos na inserción.

- Ambos `estadoConservacion` teñen o seguinte formato de `object`:

```json
"estadoConservacion<TIPO>":
{
  "marca": marca,
  "razonamento": string
}
```

onde `marca` é un tipo JSON `string` cun dos seguintes valores sensibles a maiúsculas: "Moi Bo", "Bo", "Medio", "Malo" ou "Moi Malo".

- Se en algunha operación salvo a modificación son manipulados os valores de `datacion` ou `estadoConservacion<TIPO>`, tódolos campos deben ter o valor indicado

- As imaxes son manipuladas no seu propio URI, `/imaxes/lápida`

## Listar o inventario

### Descrición

Lista todos as lápidas existentes na base de datos.

### Petición HTTP

- Método: `GET /lápida`.
- Parámetros: N/A.
- Devolve: Código HTTP 200 cun *array* de lápidas en JSON se hai inventario do valor, código 204 en caso contrario.

### Acceso

O acceso está permitido aos usuarios consultorios e aos usuarios técnicos.

### Erros

Esta operación devolve os [erros comúns](./erros.md).


### Exemplos

Listar o inventario cun catálogo baldeiro.

`GET /lápida`

```
HTTP/1.1 204 No Content
Keep-Alive: timeout=5, max=100
Content-Length: 0
```

---

Listar o inventario cun catálogo con cinco obxectos.

`GET /lápida`

```json
HTTP/1.1 200 OK
Content-Type: application/json
Content-Length: 888
Keep-Alive: timeout=5, max=100

[
  {
    "datacion": {
      "ano": 1850,
      "dia": 12,
      "mes": 4
    },
    "epigrafia": "HIC IACET IOANNES",
    "estadoConservacionAtmosferico": {
      "marca": "Medio",
      "razonamento": "Erosión leve no bordo inferior"
    },
    "estadoConservacionBioloxico": {
      "marca": "Bo",
      "razonamento": "Lectura completa e clara"
    },
    "id": 1,
    "materiais": [
      {
        "nome": "Granito"
      }
    ],
    "motivosDecorativos": [
      {
        "nome": "Cruz latina"
      }
    ],
    "proxectoArquitectonico": "Localizado no oitavo andamio do primeiro bloque do cemiterio",
    "xenealoxia": null
  },
  {
    "datacion": {
      "ano": 1902,
      "dia": 3,
      "mes": 11
    },
    "epigrafia": "D.O.M. MARIA GÓMEZ",
    "estadoConservacionAtmosferico": {
      "marca": "Malo",
      "razonamento": "Fragmentación avanzada"
    },
    "estadoConservacionBioloxico": {
      "marca": "Medio",
      "razonamento": "Fenda vertical central"
    },
    "id": 2,
    "materiais": [
      {
        "nome": "Granito"
      }
    ],
    "motivosDecorativos": [
      {
        "nome": "Roseta"
      }
    ],
    "proxectoArquitectonico": "Localizado no bloque primeiro do cemiterio",
    "xenealoxia": "Filla de Ana Gómez Forján e do alcalde de Pás do Norte Pérez Gómez"
  },
  {
    "datacion": {
      "ano": 1780,
      "dia": 20,
      "mes": 6
    },
    "epigrafia": "D.E.P JOSEFINA DE LOS DOLORES ÁLBAREZ",
    "estadoConservacionAtmosferico": {
      "marca": "Bo",
      "razonamento": "Lixeira pátina biolóxica"
    },
    "estadoConservacionBioloxico": {
      "marca": "Moi Bo",
      "razonamento": "Sen sinais de deterioro"
    },
    "id": 3,
    "materiais": [
      {
        "nome": "Pedra calcaria"
      }
    ],
    "motivosDecorativos": [
      {
        "nome": "Escudo heráldico"
      }
    ],
    "proxectoArquitectonico": "Enterrado na esquerda da porta principal da igrexa de Mouriscados",
    "xenealoxia": "Neta de Nerea Álvarez"
  },
  {
    "datacion": {
      "ano": 1865,
      "dia": 15,
      "mes": 9
    },
    "epigrafia": "AQUI DESCANSA PEDRO ALVAREZ",
    "estadoConservacionAtmosferico": {
      "marca": "Moi Malo",
      "razonamento": "Fenda irreversible, risco de colapso"
    },
    "estadoConservacionBioloxico": {
      "marca": "Malo",
      "razonamento": "Perda de material no ángulo superior"
    },
    "id": 4,
    "materiais": [
      {
        "nome": "Mármore"
      }
    ],
    "motivosDecorativos": [
      {
        "nome": "Flor de lis"
      }
    ],
    "proxectoArquitectonico": "PAQ-004",
    "xenealoxia": null
  },
  {
    "datacion": {
      "ano": 1910,
      "dia": 28,
      "mes": 2
    },
    "epigrafia": "D.E.P",
    "estadoConservacionAtmosferico": {
      "marca": "Bo",
      "razonamento": "Estable dende a última revisión"
    },
    "estadoConservacionBioloxico": {
      "marca": "Medio",
      "razonamento": "Inscrición parcialmente lexible"
    },
    "id": 5,
    "materiais": [
      {
        "nome": "Granito"
      }
    ],
    "motivosDecorativos": [
      {
        "nome": "Cruz latina"
      },
      {
        "nome": "Vieira"
      }
    ],
    "proxectoArquitectonico": "Enterrado na entrada do cemiterio novo nunha lápida moi ornamentada",
    "xenealoxia": null
  }
]
```

## Buscar o inventario

### Descrición

Busca unha lápida segundo os atributos que se especifiquen. Non se permite buscar por motivos decorativos ou materiais. A busca por estado de conservación (sexa biolóxico ou atmosférico) ou data debe ser feita con tódolos valores enchidos (é dicir, non hai `null` en ningún valor).

As buscas son exactas (buscar por `epigrafia` de valor "D.E.P" devolve todos as lápidas que conteñan exactamente "D.E.P", diferenciando maiúsculas e minúsculas).

### Petición HTTP

- Método: `GET /lápida`.
- Parámetros: JSON cos atributos dunha lápida.
- Devolve: Código HTTP 200 cun *array* de bens patrimoniais en JSON se hai inventario do valor, código 204 en caso contrario

### Acceso

O acceso está permitido aos usuarios consultorios e aos usuarios técnicos.

### Erros

Esta operación devolve os [erros comúns](./erros.md).


### Exemplos

Buscar todas as lápidas cuxa epigrafía sexa "D.E.P FRANCISCO FERNÁNDEZ RIVERA" (non hai ningunha).

```json
GET /lápida
{
  "datacion": null,
  "epigrafia": "D.E.P FRANCISCO FERNÁNDEZ RIVERA",
  "estadoConservacionAtmosferico": null,
  "estadoConservacionBioloxico": null,
  "id": null,
  "materiais": [],
  "motivosDecorativos": [],
  "proxectoArquitectonico": null,
  "xenealoxia": null
}
```

```
HTTP/1.1 204 No Content
Keep-Alive: timeout=5, max=100
Content-Length: 0
```
---

Buscar a lápida de ID 1.

```json
GET /lápida
{
  "datacion": null,
  "epigrafia": null,
  "estadoConservacionAtmosferico": null,
  "estadoConservacionBioloxico": null,
  "id": 1,
  "materiais": [],
  "motivosDecorativos": [],
  "proxectoArquitectonico": null,
  "xenealoxia": null
}
```

```json
HTTP/1.1 200 OK
Content-Type: application/json
Content-Length: 888
Keep-Alive: timeout=5, max=100

[
  {
    "datacion": {
      "ano": 1850,
      "dia": 12,
      "mes": 4
    },
    "epigrafia": "HIC IACET IOANNES",
    "estadoConservacionAtmosferico": {
      "marca": "Medio",
      "razonamento": "Erosión leve no bordo inferior"
    },
    "estadoConservacionBioloxico": {
      "marca": "Bo",
      "razonamento": "Lectura completa e clara"
    },
    "id": 1,
    "materiais": [
      {
        "nome": "Granito"
      }
    ],
    "motivosDecorativos": [
      {
        "nome": "Cruz latina"
      }
    ],
    "proxectoArquitectonico": "Localizado no oitavo andamio do primeiro bloque do cemiterio",
    "xenealoxia": null
  }
]
```

## Modificar un inventario

### Descrición

Modifica unha lápida existente, cambiando os parámetros indicados.

Se un inventario está composto de materiais ou foron definidos motivos decorativos para este, non é posible modificalo para desasociar os materiais ou motivos decorativos deste.

### Petición HTTP

- Método: `POST /lápida`
- Parámetros: Lista en JSON con dúas lápidas, sendo a primeira o inventario a modificar e a segunda unha que contén os valores a modificar.
  - Só é inspeccionado no primeira lápida o valor `id`. O resto de valores deberían ser postos a `null`, ou é posible que se produzan erros HTTP 404.
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

en caso de que non exista a lápida a modificar.

### Exemplos

Modificar a lápida de `id` 5 para cambiar a data de enterro ao 28/02/1911 e cambiar o rexistro de conservación biolóxico.

```json
POST /lápida
[
  {
    "datacion": null,
    "epigrafia": null,
    "estadoConservacionAtmosferico": null,
    "estadoConservacionBioloxico": null,
    "id": 5,
    "materiais": [],
    "motivosDecorativos": [],
    "proxectoArquitectonico": null,
    "xenealoxia": null
  },
  {
    "datacion": {
      "ano": 1911,
      "dia": 28,
      "mes": 2
    },
    "epigrafia": null,
    "estadoConservacionAtmosferico": null,
    "estadoConservacionBioloxico": {
      "marca": "Medio",
      "razonamento": "Inscrición degradada parcialmente"
    },
    "id": null,
    "materiais": [],
    "motivosDecorativos": [],
    "proxectoArquitectonico": null,
    "xenealoxia": null
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

Rexistra unha lápida novo na base de datos.

Os materiais e motivos decorativos que compoñen a lápida deben existir previamente na base de datos.

### Petición HTTP

- Método: `PUT /lápida`.
- Parámetros: JSON cos atributos dunha lápida, necesariamente co parámetros indicados como "opcional na inserción" co valor "non" enchidos.
- Devolve: Código HTTP 201 se a inserción é completada correctamente xunto ca lápida de datos idénticos co valor `id` asignado internamente.

### Acceso

O acceso está permitido aos usuarios técnicos.

### Erros

Esta operación devolve os [erros comúns](./erros.md).

### Exemplos

Inserir unha lápida cos valores dados no exemplo.

```json
PUT /lápida
{
  "datacion": {
    "ano": 2020,
    "dia": 12,
    "mes": 6
  },
  "epigrafia": "D.E.P José Luís Verdante Facero",
  "estadoConservacionAtmosferico": null,
  "estadoConservacionBioloxico": {
    "marca": "Moi Bo",
    "razonamento": "En conservación pristina"
  },
  "id": null,
  "materiais": [
    {
      "nome": "Granito"
    }
  ],
  "motivosDecorativos": [],
  "proxectoArquitectonico": "Localizado no séptimo andamio do terceiro bloque do cemiterio",
  "xenealoxia": null
}
```

```json
HTTP/1.1 201 Created
Keep-Alive: timeout=5, max=100
Content-Length: 0

{
  "datacion": {
    "ano": 2020,
    "dia": 12,
    "mes": 6
  },
  "epigrafia": "D.E.P José Luís Verdante Facero",
  "estadoConservacionAtmosferico": null,
  "estadoConservacionBioloxico": {
    "marca": "Moi Bo",
    "razonamento": "En conservación pristina"
  },
  "id": 6,
  "materiais": [
    {
      "nome": "Granito"
    }
  ],
  "motivosDecorativos": [],
  "proxectoArquitectonico": "Localizado no séptimo andamio do terceiro bloque do cemiterio",
  "xenealoxia": null
}
```

## Eliminar un inventario

### Descrición

Elimina unha lápida existente na base de datos.

### Petición HTTP

- Método: `DELETE /lápida`
- Parámetros: JSON cos atributos dunha lápida, necesariamente co parámetro `id` indicado.
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

en caso de que non exista a lápida a eliminar.

### Exemplos

Eliminar a lápida de chave `id` de valor 6.

```json
DELETE /lápida
{
  "datacion": null,
  "epigrafia": null,
  "estadoConservacionAtmosferico": null,
  "estadoConservacionBioloxico": null,
  "id": 6,
  "materiais": [],
  "motivosDecorativos": [],
  "proxectoArquitectonico": null,
  "xenealoxia": null
}
```

```json
HTTP/1.1 200 OK
Keep-Alive: timeout=5, max=100
Content-Length: 0
```