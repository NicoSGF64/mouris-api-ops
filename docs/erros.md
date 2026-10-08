# Erros comúns

Esta páxina cubre a lista de erros HTTP que moitas operacións poden producir. Certos métodos poden producir erros adicionais, e, en tal caso, será indicada na sección relevante.

Os erros son devolvidos en formato JSON co seguinte aspecto:

```json
{"error": razón}
```

onde `razon` é un texto explicativo do sucedido, de tipo JSON `string`.

## Listaxe de erros

A categoría de erros 400 está reservada para erros do usuario, mentres que a categoría 500 para erros internos.

| Nome | Código HTTP | `razon` | Información adicional
| :---: | :---: | :---: | :---: |
| Sesión xa existente | 401 | "Sesión xa existente" |  |
| Sen sesión | 403 | "Requírese iniciar sesión" | Fíxose unha petición sen a cabeceira co valor `Authorization` especificado ou cunha dun usuario sen sesión |
| Permisos insuficientes | 403 | "Permiso denegado para manipular as táboas necesarias" | O usuario que fixo a petición non ten permiso para acceder as táboas necesarias na base de datos |
| Sesión caducada | 403 | "Sesión caducada" | A sesión leva máis de trinta minutos de inactividade |
| JSON mal formado | 422 | "O JSON fornecido está mal formado" | Cómpre asegurarse de que está ben escrito todos os valores JSON |
| Nulo en inserción | 422 | "Estableceuse un campo non candidato a ser nulo como nulo" | Un parámetro marcado coma "non" na columna "nulo na inserción" da táboa do obxecto a manipular non foi posto |
| Lonxitude demasiado longa | 422 | "A lonxitude dos parámetros é demasiado longa" |  |
| Erro de conexión interna | 500 | "A API non puido establecer unha conexión coa base de datos" | A base de datos está inaccesible ou a configuración dada ao servidor é incorrecta |
| Erro da base de datos | 500 | "Erro interno da base de datos" | A base de datos non puido realizar a cabo a operación pedida. En ocasións pode ser devolto este erro en lugar dun erro de categoría 400 apropiado. |
| Erro interno do servidor | 500 | "Erro interno do servidor" | O servidor sufriu un erro de programación interna. Este erro non debería ser devolto |
| Erro de ligado de parámetros | 500 | "Erro de programación interna do servidor (nº parámetros ligados erróneo)" | O servidor sufriu un erro de programación interna. Este erro non debería ser devolto. |
