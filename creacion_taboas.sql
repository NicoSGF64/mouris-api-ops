DROP TABLE IF EXISTS lapidas CASCADE;
DROP TABLE IF EXISTS motivos_decorativos CASCADE;
DROP TABLE IF EXISTS lapidas CASCADE;
DROP TABLE IF EXISTS materiais CASCADE;
DROP TABLE IF EXISTS bens_mobles CASCADE;
DROP TABLE IF EXISTS esculturas CASCADE;
DROP TABLE IF EXISTS decorar_lapidas CASCADE;
DROP TABLE IF EXISTS decorar_mobles CASCADE;
DROP TABLE IF EXISTS componer_lapidas CASCADE;
DROP TABLE IF EXISTS componer_mobles CASCADE;
DROP TABLE IF EXISTS usuarios CASCADE;

DROP DOMAIN IF EXISTS marcas;
DROP DOMAIN IF EXISTS segmento;
DROP DOMAIN IF EXISTS tipo_usuario;

create domain marcas as varchar(8)
 constraint checkMarcas
     check(value in ('Moi Bo', 'Bo', 'Medio', 'Malo', 'Moi Malo'));

create domain segmento as varchar(16)
 constraint checkSegmento
     check(value in ('Primeira metade', 'Segunda metade', 'Terceira metade', 'Primeiro terzo', 'Segundo Terzo', 'Terceiro terzo', 'Primeiro cuarto', 'Segundo cuarto', 'Terceiro cuarto', 'Cuarto cuarto'));

create domain tipo_usuario as varchar(32)
 constraint checkTipo
     check(value in ('usuario_consultorio', 'usuario_tecnico', 'administrador_sistema'));

-- TÁBOAS PRINCIPAIS

CREATE TABLE lapidas(
    id                 SERIAL             PRIMARY KEY,
    xeanoloxia        VARCHAR(4096),    
    epigrafia        VARCHAR(4096),    
    datacion        DATE             DEFAULT CURRENT_DATE,
    paq                VARCHAR(1024),
    fotografia_mime   VARCHAR(16),
    fotografia_datos  bytea,
    ecb_Marca        marcas,
    ecb_Razonamento    VARCHAR(512),
    eca_Marca        marcas,
    eca_Razonamento    VARCHAR(512),
     CONSTRAINT fotografia_ambas_ou_ningunha
        CHECK ((fotografia_mime IS NULL) = (fotografia_datos IS NULL))
);

CREATE TABLE motivos_Decorativos(
    nome    VARCHAR(32)    PRIMARY KEY
);

CREATE TABLE materiais(
    nome    VARCHAR(32)    PRIMARY KEY
);

CREATE TABLE bens_Mobles(
    id                SERIAL            PRIMARY KEY,
    nome            VARCHAR(256)        NOT NULL,
    descripcion     VARCHAR(4096)    NOT NULL,
    altura            FLOAT(3),
    anchura            FLOAT(3),
    datacion        DATE,
    seculo            VARCHAR(5)        CHECK (seculo SIMILAR TO '[IVX]+'),
    segmento_seculo    segmento,
    estilo            VARCHAR(32)        NOT NULL,
    taller            VARCHAR(64),
    fotografia_mime   VARCHAR(16),
    fotografia_datos  bytea,
     CONSTRAINT fotografia_ambas_ou_ningunha
        CHECK ((fotografia_mime IS NULL) = (fotografia_datos IS NULL))
);

CREATE TABLE esculturas(
    id_ben_Moble            INT    PRIMARY KEY,
    santo_Representado   VARCHAR(32) NOT NULL,
    FOREIGN KEY (id_Ben_Moble) REFERENCES bens_Mobles(id)
        ON UPDATE CASCADE
        ON DELETE CASCADE
);

-- TÁBOAS DE RELACIÓNS
CREATE TABLE decorar_Lapidas(
    id_Lapida                INT, 
    nome_Motivo_Decorativo    VARCHAR(32),
    PRIMARY KEY (id_Lapida, nome_Motivo_Decorativo),
    FOREIGN KEY (id_Lapida) REFERENCES lapidas(id)
        ON UPDATE CASCADE
        ON DELETE CASCADE,
    FOREIGN KEY (nome_Motivo_Decorativo) REFERENCES motivos_Decorativos(nome)
        ON UPDATE CASCADE
        ON DELETE CASCADE
);

CREATE TABLE decorar_Mobles(
    id_ben_Moble                INT,
    nome_Motivo_Decorativo    VARCHAR(32),
    PRIMARY KEY (id_ben_Moble, nome_Motivo_Decorativo),
    FOREIGN KEY (id_ben_Moble) REFERENCES bens_Mobles(id)
        ON UPDATE CASCADE
        ON DELETE CASCADE,
    FOREIGN KEY (nome_Motivo_Decorativo) REFERENCES motivos_Decorativos(nome)
        ON UPDATE CASCADE
        ON DELETE CASCADE
);

CREATE TABLE componer_Lapidas(
    id_Lapida        INT,
    nome_Material    VARCHAR(32),
    PRIMARY KEY (id_Lapida, nome_Material),
    FOREIGN KEY (id_Lapida) REFERENCES lapidas(id)
        ON UPDATE CASCADE
        ON DELETE CASCADE,
    FOREIGN KEY (nome_Material) REFERENCES materiais(nome)
        ON UPDATE CASCADE
        ON DELETE CASCADE
);

CREATE TABLE componer_Mobles(	
    id_ben_Moble        INT,
    nome_Material    VARCHAR(32),
    PRIMARY KEY (id_ben_Moble, nome_Material),
    FOREIGN KEY (id_ben_Moble) REFERENCES bens_mobles(id)
        ON UPDATE CASCADE
        ON DELETE CASCADE,
    FOREIGN KEY (nome_Material) REFERENCES materiais(nome)
        ON UPDATE CASCADE
        ON DELETE CASCADE
);

CREATE TABLE usuarios(
    nome_usuario    VARCHAR(32)    PRIMARY KEY,
    tipo_usuario    tipo_usuario    NOT NULL
);

CREATE ROLE usuario_consultorio;
GRANT SELECT ON bens_mobles, componer_lapidas, componer_mobles, decorar_lapidas, decorar_mobles, esculturas, lapidas, materiais, motivos_decorativos TO usuario_consultorio;

CREATE ROLE usuario_tecnico;
GRANT SELECT, INSERT, UPDATE, DELETE ON bens_mobles, componer_lapidas, componer_mobles, decorar_lapidas, decorar_mobles, esculturas, lapidas, materiais, motivos_decorativos TO usuario_tecnico;

CREATE ROLE administrador_sistema CREATEROLE;
GRANT SELECT, INSERT, UPDATE, DELETE ON usuarios TO administrador_sistema;
GRANT usuario_consultorio TO administrador_sistema WITH ADMIN OPTION, INHERIT FALSE;
GRANT usuario_tecnico     TO administrador_sistema WITH ADMIN OPTION, INHERIT FALSE;

GRANT USAGE, SELECT ON ALL SEQUENCES IN SCHEMA public TO usuario_consultorio, usuario_tecnico, administrador_sistema;