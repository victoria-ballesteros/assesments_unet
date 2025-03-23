-- DROP TABLE secciones;
-- DROP TABLE materias;
-- DROP TABLE docentes;
-- DROP TABLE aulas;

CREATE TABLE materias (
    cod         INTEGER NOT NULL,
    nombre      VARCHAR2(50) NOT NULL CHECK (nombre = UPPER(nombre)),
    horteo      INTEGER NOT NULL,
    horlab      INTEGER,
    estado      CHAR(1) DEFAULT 'A' CHECK (estado IN ('A', 'I')),
    CONSTRAINT materias_pk PRIMARY KEY (cod)
);

CREATE TABLE docentes (
    cedula      VARCHAR2(11),
    nombre      VARCHAR2(50) NOT NULL,
    telf        VARCHAR2(20),
    CONSTRAINT docentes_pk PRIMARY KEY (cedula)
);

CREATE TABLE aulas (
    idAula      INTEGER NOT NULL,
    numero      INTEGER NOT NULL,
    edificio    CHAR(1) CHECK (edificio IN ('A', 'B', 'C')),
    capacidad   INTEGER NOT NULL, 
    CONSTRAINT aula_pk PRIMARY KEY (idAula),
    CONSTRAINT aulas_unique UNIQUE (numero, edificio),
    CONSTRAINT aulas_capacidad_check CHECK (capacidad <= 50)
);

CREATE TABLE secciones (    
    idSec       INTEGER NOT NULL,
    numero      INTEGER NOT NULL,
    canalu      INTEGER NOT NULL,
    cedula      VARCHAR2(11),
    cod         INTEGER NOT NULL,
    idAula      INTEGER NOT NULL,
    estado      CHAR(1) DEFAULT 'A' CHECK (estado IN ('A', 'I')),
    CONSTRAINT secciones_pk PRIMARY KEY (idSec),
    CONSTRAINT secciones_cedula_fk FOREIGN KEY (cedula) REFERENCES docentes (cedula) ON DELETE CASCADE,
    CONSTRAINT secciones_cod_fk FOREIGN KEY (cod) REFERENCES materias (cod) ON DELETE CASCADE,
    CONSTRAINT secciones_idAula_fk FOREIGN KEY (idAula) REFERENCES aulas (idAula) ON DELETE CASCADE,
    CONSTRAINT secciones_unique_materia_num UNIQUE (cod, numero),
    CONSTRAINT secciones_unique_profesor UNIQUE (cedula, cod, numero),
    CONSTRAINT secciones_estado_activa CHECK (
        (estado = 'A' AND canalu BETWEEN 20 AND 40) OR (estado = 'I' AND canalu = 0)
    )
);

ALTER TABLE docentes
ADD direccion VARCHAR2(255) NULL;

ALTER TABLE aulas
DROP CONSTRAINT aulas_capacidad_check;

ALTER TABLE secciones
ADD CONSTRAINT chk_canalu CHECK (canalu BETWEEN 20 AND 40);

ALTER TABLE aulas
ADD CONSTRAINT chk_capacidad_edificio CHECK (
    (edificio = 'B' AND capacidad <= 50) OR
    (edificio = 'A' AND capacidad <= 40) OR
    (edificio = 'C' AND capacidad <= 30)
);

SELECT constraint_name, constraint_type
FROM user_constraints
WHERE table_name = 'horarios';

-- Correcto
INSERT INTO materias (cod, nombre, horteo, horlab, estado) 
VALUES (1, 'PROGRAMACION', 10, 5, 'A');

-- Incorrecto (nombre con caracteres no permitidos)
INSERT INTO materias (cod, nombre, horteo, horlab, estado) 
VALUES (2, 'Matematica Avanzada', 8, 4, 'A');

-- Correcto
INSERT INTO docentes (cedula, nombre, telf) 
VALUES ('V12345678', 'Juan Pérez', '0424123456');

-- Incorrecto (duplicar cédula)
INSERT INTO docentes (cedula, nombre, telf) 
VALUES ('V12345678', 'Ana Gómez', '0424765432');

-- Correcto
INSERT INTO aulas (idAula, numero, edificio, capacidad) 
VALUES (1, 101, 'A', 40);

-- Incorrecto (capacidad mayor a la permitida para 'A')
INSERT INTO aulas (idAula, numero, edificio, capacidad) 
VALUES (2, 102, 'A', 45);

-- Correcto (sección activa con 30 alumnos)
INSERT INTO secciones (idSec, numero, canalu, cedula, cod, idAula, estado) 
VALUES (1, 1, 30, 'V12345678', 1, 1, 'A');

-- Incorrecto (sección activa con menos de 20 alumnos)
INSERT INTO secciones (idSec, numero, canalu, cedula, cod, idAula, estado) 
VALUES (2, 2, 15, 'V12345678', 1, 1, 'A');

-- Incorrecto (sección inactiva con más de 0 alumnos)
INSERT INTO secciones (idSec, numero, canalu, cedula, cod, idAula, estado) 
VALUES (3, 3, 5, 'V12345678', 2, 2, 'I');

