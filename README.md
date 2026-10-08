# mourisAPIos - Unha API REST para a xestión do patrimonio da contorna de Mouriscados

mourisAPIos é unha API REST básica para o almacenamento de bens culturais eclesiásticos da contorna de Mouriscados. Foi escrita en C++17 como parte do programa [Campus Rural](https://www.miteco.gob.es/es/reto-demografico/campus_rural.html) do ano 2026 realizada para a Comunidade de Montes Veciñais en Man Común de Mouriscados.

## Capacidades

mourisAPIos fornece soporte para o rexistro dixitalizado de bens inmobles tales coma pilas bautismais, altares, campás, etc., toda clase de esculturas e información sobre lápidas, podendo recoller en detalle moitos dos aspectos destes. En adición ao previo, a API permite xestionar usuarios de varios tipos.

## Documentación

A documentación está dispoñible [nesta ligazón](https://example.com).

## Deseño

A API segue o paradigma [REST](https://es.wikipedia.org/wiki/REST) e permite chamadas aos *endpoint* con obxectos escritos en [JSON](https://es.wikipedia.org/wiki/JSON). A información destes obxectos, xunto cas imaxes asociadas, son gardadas nunha base de datos baseada en PostgreSQL estruturada tal coma indicado no *script* de creación.

O programa usa extensivamente as librarías [nanodbc](https://nanodbc.github.io/nanodbc/) para poder facer a conectividade á base de datos e [cpp-httplib](https://yhirose.github.io/cpp-httplib/en/) para xestionar as conexións e o manexo de datos a través de  HTTPS.

## Uso

Os xeitos de acceder e manipular cada obxecto está recollido na súa páxina correspondente. Para toda consulta, é necesario [iniciar sesión](sesion.md) e mandar no campo HTTP de `Authorization` de tipo `Basic` o nome de usuario e contrasinal.
