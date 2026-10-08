# Xestión e suba de imaxes

A xestión e suba de imaxes por aspectos técnicos de [separación de intereses](https://es.wikipedia.org/wiki/Separaci%C3%B3n_de_intereses) é tratada separadamente. Dentro do inventario que permite a suba de imaxes, a manipulación destas pode ser realizada no URI `/imaxes/<tipo>`, onde `<tipo>` é o URI do inventario en cuestión.

## Buscar unha imaxe

### Descrición

Devolve a imaxe correspondente a un inventario que soporte.

### Petición HTTP

- Método: `GET /imaxes/URI`.
- Parámetros: JSON correspondente ao obxecto a buscar co valor `id` establecido.
- Devolve: Código HTTP 200 xunto ca imaxe de ou ben de formato MIME `image/png` ou `image/jpeg`.

### Acceso

O acceso está permitido aos usuarios consultorios e aos usuarios técnicos.

### Erros

Esta operación devolve os [erros comúns](./erros.md), xunto cun código HTTP 422 de contido

```json
{
  "error": "Falta o obxecto necesario para recuperar a imaxe"
}
```

se non se da o JSON requirido para a busca.

### Exemplos

Buscar a imaxe correspondente ao ben patrimonial de `ìd` 4 (sen fotografía).

```json
GET /imaxes/benpatrimonial`
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
  "taller": null
}
```


```
HTTP/1.1 204 No Content
Keep-Alive: timeout=5, max=100
Content-Length: 0

```

---

Buscar a imaxe correspondente á lápida de `ìd` 2.

```json
GET /imaxes/lapida
{
  "datacion": null,
  "epigrafia": null,
  "estadoConservacionAtmosferico": null,
  "estadoConservacionBioloxico": null,
  "id": 2,
  "materiais": [],
  "motivosDecorativos": [],
  "proxectoArquitectonico": null,
  "xenealoxia": null
}
```

```json
HTTP/1.1 200 OK
Content-Type: image/jpeg
Content-Length: 308142
Keep-Alive: timeout=5, max=100
```

<img src="./hume.jpg" width="500" alt="Lápida de David Hume">

*(imaxe crédito de User:Jonathan Oldenbuck, [CC-BY-3.0](https://creativecommons.org/licenses/by/3.0), via Wikimedia Commons)*

## Modificar unha imaxe

### Descrición

Modifica a imaxe asociada a un inventario, sobrescribindo os datos gardados da previa.

### Petición HTTP

- Método: `POST /imaxes/URI`
- Parámetros: Un `multipart/form-data` (tal coma o xerado por un formulario HTML coa suba de arquivos) que consiste dunha imaxe PNG ou JPEG co tipo MIME correcto co nome de campo `imaxe` e o JSON enviado como `application/octet-stream` ou `application/json`.
  - O valor JSON debe ser enviado nun só bloque do `multipart/form-data`
- Devolve: Código HTTP 200 se a modificación fíxose correctamente.

### Acceso

O acceso está permitido aos usuarios técnicos.

### Erros

Esta operación devolve os [erros comúns](./erros.md) xunto con varios outros erros:  

```json
{
  "error": "Requírese un tipo de contido de formulario multipart con JSON do obxeto e imaxe"
}
```

co código HTTP 422 se é mandado calquera formato diferente de `multipart/form-data`,

```json
{
  "error": "Obxecto descoñecido (JSON inválido)"
}
```

co código HTTP 422 se o JSON mandado é erróneo,

```json
{
  "error": "Imaxe inválida"
}
```

co código HTTP 422 se a imaxe non contén os números máxicos correspondente ao seu tipo e

```json
{
  "error": "Formato de imaxe inválido (só se permite PNG ou JPEG)"
}
```

co código HTTP 422 se a imaxe é dun tipo distinto de PNG ou JPEG.

## Rexistrar unha imaxe

### Descrición

Rexistra a imaxe asociada a un inventario, sobrescribindo os datos gardados da previa se houbese.

### Petición HTTP

- Método: `POST /imaxes/URI`
- Parámetros: Un `multipart/form-data` (tal coma o xerado por un formulario HTML coa suba de arquivos) que consiste dunha imaxe PNG ou JPEG co tipo MIME correcto co nome de campo `imaxe` e o JSON enviado como `application/octet-stream` ou `application/json`.
  - O valor JSON debe ser enviado nun só bloque do `multipart/form-data`
- Devolve: Código HTTP 200 se a modificación fíxose correctamente.

### Acceso

O acceso está permitido aos usuarios técnicos.

### Erros

Esta operación devolve os [erros comúns](./erros.md) xunto con varios outros erros:  

```json
{
  "error": "Requírese un tipo de contido de formulario multipart con JSON do obxeto e imaxe"
}
```

co código HTTP 422 se é mandado calquera formato diferente de `multipart/form-data`,

```json
{
  "error": "Obxecto descoñecido (JSON inválido)"
}
```

co código HTTP 422 se o JSON mandado é erróneo,

```json
{
  "error": "Imaxe inválida"
}
```

co código HTTP 422 se a imaxe non contén os números máxicos correspondente ao seu tipo e

```json
{
  "error": "Formato de imaxe inválido (só se permite PNG ou JPEG)"
}
```

co código HTTP 422 se a imaxe é dun tipo distinto de PNG ou JPEG.

## Eliminar unha imaxe

### Descrición

Elimina permanentemente a imaxe asociada a un inventario.

### Petición HTTP

- Método: `DELETE /imaxes/URI`
- Parámetros: JSON correspondente ao obxecto a buscar co valor `id` establecido.
- Devolve: Código HTTP 200 en caso de que o borrado sexa realizado correctamente.

### Acceso

O acceso está permitido aos usuarios técnicos.

### Erros

Esta operación devolve os [erros comúns](./erros.md).

### Exemplos

Eliminar a imaxe asociada coa lápida de `id` 2.

```json
DELETE/imaxes/lapida
{
  "datacion": null,
  "epigrafia": null,
  "estadoConservacionAtmosferico": null,
  "estadoConservacionBioloxico": null,
  "id": 2,
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