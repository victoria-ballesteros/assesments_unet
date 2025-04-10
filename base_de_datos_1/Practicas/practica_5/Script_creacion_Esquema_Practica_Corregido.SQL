REM ************ TABLAS PRECTICAS


REM ******** TABLA DEPART: ***********

DROP TABLE DEPART cascade constraints; 

CREATE TABLE DEPART (
 DEPT_NO  NUMBER(2) NOT NULL,
 DNOMBRE  VARCHAR2(14), 
 LOC      VARCHAR2(14) ) ;

INSERT INTO DEPART VALUES (10,'CONTABILIDAD','SEVILLA');
INSERT INTO DEPART VALUES (20,'INVESTIGACIÓN','MADRID');
INSERT INTO DEPART VALUES (30,'VENTAS','BARCELONA');
INSERT INTO DEPART VALUES (40,'PRODUCCIÓN','BILBAO');
COMMIT;


REM ******** TABLA EMPLE: *************

ALTER SESSION SET NLS_DATE_FORMAT='DD/MM/YYYY';

DROP TABLE EMPLE cascade constraints; 

CREATE TABLE EMPLE (
 EMP_NO    NUMBER(4) NOT NULL,
 APELLIDO  VARCHAR2(10)  ,
 OFICIO    VARCHAR2(10)  ,
 DIR       NUMBER(4) ,
 FECHA_ALT DATE      ,
 SALARIO   NUMBER(10),
 COMISION  NUMBER(10),
 DEPT_NO   NUMBER(2) NOT NULL) ;

INSERT INTO EMPLE VALUES (7369,'SÁNCHEZ','EMPLEADO',7902,'17/12/1980',
                        104000,NULL,20);
INSERT INTO EMPLE VALUES (7499,'ARROYO','VENDEDOR',7698,'20/02/1980',
                        208000,39000,30);
INSERT INTO EMPLE VALUES (7521,'SALA','VENDEDOR',7698,'22/02/1981',
                        162500,65000,30);
INSERT INTO EMPLE VALUES (7566,'JIMÉNEZ','DIRECTOR',7839,'02/04/1981',
                        386750,NULL,20);
INSERT INTO EMPLE VALUES (7654,'MARTÍN','VENDEDOR',7698,'29/09/1981',
                        162500,182000,30);
INSERT INTO EMPLE VALUES (7698,'NEGRO','DIRECTOR',7839,'01/05/1981',
                        370500,NULL,30);
INSERT INTO EMPLE VALUES (7782,'CEREZO','DIRECTOR',7839,'09/06/1981',
                        318500,NULL,10);
INSERT INTO EMPLE VALUES (7788,'GIL','ANALISTA',7566,'09/11/1981',
                        390000,NULL,20);
INSERT INTO EMPLE VALUES (7839,'REY','PRESIDENTE',NULL,'17/11/1981',
                        650000,NULL,10);
INSERT INTO EMPLE VALUES (7844,'TOVAR','VENDEDOR',7698,'08/09/1981',
                        195000,0,30);
INSERT INTO EMPLE VALUES (7876,'ALONSO','EMPLEADO',7788,'23/09/1981',
                        143000,NULL,20);
INSERT INTO EMPLE VALUES (7900,'JIMENO','EMPLEADO',7698,'03/12/1981',
                        123500,NULL,30);
INSERT INTO EMPLE VALUES (7902,'FERNÁNDEZ','ANALISTA',7566,'03/12/1981',
                        390000,NULL,20);
INSERT INTO EMPLE VALUES (7934,'MUÑOZ','EMPLEADO',7782,'23/01/1982',
                        169000,NULL,10);

COMMIT;

REM ******** TABLA NOTAS_ALUMNOS: ***********

Drop table notas_alumnos cascade constraints;

create table notas_alumnos
 (
   NOMBRE_ALUMNO VARCHAR2(25) NOT NULL ,
   nota1 number(2),
   nota2 number(2),
   nota3 number(2)
 ) ;
 
insert into NOTAS_ALUMNOS VALUES ('Alcalde García, M. Luisa',5,5,5);
insert into NOTAS_ALUMNOS VALUES ('Benito Martín, Luis',7,6,8);
insert into NOTAS_ALUMNOS VALUES ('Casas Martínez, Manuel',7,5,5);
insert into NOTAS_ALUMNOS VALUES ('Corregidor Sánchez, Ana',6,9,8);
insert into NOTAS_ALUMNOS VALUES ('Díaz Sánchez, María',NULL,NULL,7);
COMMIT;

REM ******** TABLA LIBRERIA: *************

Drop table LIBRERIA cascade constraints;

create table LIBRERIA
 (TEMA CHAR(15) NOT NULL ,
  ESTANTE CHAR(1),
  EJEMPLARES NUMBER(2)
 ) ;

INSERT INTO LIBRERIA VALUES ('Informática', 'A',15);
INSERT INTO LIBRERIA VALUES ('Economía',    'A',10);
INSERT INTO LIBRERIA VALUES ('Deportes',    'B',8);
INSERT INTO LIBRERIA VALUES ('Filosofía',   'C',7);
INSERT INTO LIBRERIA VALUES ('Dibujo',      'C',10);
INSERT INTO LIBRERIA VALUES ('Medicina',    'C',16);
INSERT INTO LIBRERIA VALUES ('Biología',    'A',11);
INSERT INTO LIBRERIA VALUES ('Geología',    'D',7);
INSERT INTO LIBRERIA VALUES ('Sociedad',    'D',9);
INSERT INTO LIBRERIA VALUES ('Labores',     'B',20);
INSERT INTO LIBRERIA VALUES ('Jardinería',    'E',6);
COMMIT;

REM ******** TABLAS ALUMNOS, ASIGNATURAS, NOTAS: ***********

DROP TABLE ALUMNOS cascade constraints;

CREATE TABLE ALUMNOS
(
  DNI VARCHAR2(10) NOT NULL,
  APENOM VARCHAR2(30),
  DIREC VARCHAR2(30),
  POBLA  VARCHAR2(15),
  TELEF  VARCHAR2(10)  
) ;

DROP TABLE ASIGNATURAS cascade constraints;

CREATE TABLE ASIGNATURAS
(
  COD NUMBER(2) NOT NULL,
  NOMBRE VARCHAR2(25)
) ;

DROP TABLE NOTAS cascade constraints;

CREATE TABLE NOTAS
(
  DNI VARCHAR2(10) NOT NULL,
  COD NUMBER(2) NOT NULL,
  NOTA NUMBER(2)
) ;

INSERT INTO ASIGNATURAS VALUES (1,'Prog. Leng. Estr.');
INSERT INTO ASIGNATURAS VALUES (2,'Sist. Informáticos');
INSERT INTO ASIGNATURAS VALUES (3,'Análisis');
INSERT INTO ASIGNATURAS VALUES (4,'FOL');
INSERT INTO ASIGNATURAS VALUES (5,'RET');
INSERT INTO ASIGNATURAS VALUES (6,'Entornos Gráficos');
INSERT INTO ASIGNATURAS VALUES (7,'Aplic. Entornos 4ªGen');

INSERT INTO ALUMNOS VALUES
('12344345','Alcalde García, Elena', 'C/Las Matas, 24','Madrid','917766545');

INSERT INTO ALUMNOS VALUES
('4448242','Cerrato Vela, Luis', 'C/Mina 28 - 3A', 'Madrid','916566545');

INSERT INTO ALUMNOS VALUES
('56882942','Díaz Fernández, María', 'C/Luis Vives 25', 'Móstoles','915577545');

INSERT INTO NOTAS VALUES('12344345', 1,6);
INSERT INTO NOTAS VALUES('12344345', 2,5);
INSERT INTO NOTAS VALUES('12344345', 3,6);

INSERT INTO NOTAS VALUES('4448242', 4,6);
INSERT INTO NOTAS VALUES('4448242', 5,8);
INSERT INTO NOTAS VALUES('4448242', 6,4);
INSERT INTO NOTAS VALUES('4448242', 7,5);

INSERT INTO NOTAS VALUES('56882942', 4,8);
INSERT INTO NOTAS VALUES('56882942', 5,7);
INSERT INTO NOTAS VALUES('56882942', 6,8);
INSERT INTO NOTAS VALUES('56882942', 7,9);

COMMIT;

REM ************ TABLAS UNIDAD IV
REM ************ TABLASUNI4.SQL


REM ********** TABLA NOMBRES: ***********

DROP TABLE NOMBRES cascade constraints; 
CREATE TABLE NOMBRES
(
  NOMBRE VARCHAR2(15),
  EDAD NUMBER(2)
) ;

INSERT INTO NOMBRES VALUES('PEDRO', 17);
INSERT INTO NOMBRES VALUES('JUAN', 17);
INSERT INTO NOMBRES VALUES('MARÍA', 16);
INSERT INTO NOMBRES VALUES('CLARA', 14);
INSERT INTO NOMBRES VALUES(NULL, 15);
INSERT INTO NOMBRES VALUES(NULL, 18);
INSERT INTO NOMBRES VALUES('JESÚS', NULL);

COMMIT;

REM ********** TABLA MISTEXTOS: *************

DROP TABLE MISTEXTOS cascade constraints; 

CREATE TABLE MISTEXTOS (
 TITULO  VARCHAR2(32),
 AUTOR   VARCHAR2(22),
 EDITORIAL VARCHAR2(15), 
 PAGINA  NUMBER(3)
 ) ;

INSERT INTO MISTEXTOS VALUES ('METODOLOGÍA PROGRAMACIÓN.', 
'ALCALDE, GARCÍA', 'MCGRAWHILL',140);
INSERT INTO MISTEXTOS VALUES ('"INFORMÁTICA BÁSICA."', 'GARCÍA GARCERÁN', 'PARANINFO',130);
INSERT INTO MISTEXTOS VALUES ('SISTEMAS OPERATIVOS', 'J.F. GARCÍA', 'OBSBORNE',300);
INSERT INTO MISTEXTOS VALUES ('SISTEMAS DIGITALES.', 'M.A. RUÍZ', 
'PRENTICE HALL',190);
INSERT INTO MISTEXTOS VALUES ('"MANUAL DE C."', 'M.A. RUÍZ', 'MCGRAWHILL',340);

COMMIT;


REM ********** TABLA LIBROS: *************

DROP TABLE LIBROS cascade constraints; 

CREATE TABLE LIBROS (
 TITULO  VARCHAR2(32),
 AUTOR   VARCHAR2(22),
 EDITORIAL VARCHAR2(15), 
 PAGINA  NUMBER(3)
 ) ;

INSERT INTO LIBROS VALUES ('LA COLMENA', 'CELA, CAMILO JOSÉ', 'PLANETA',240);
INSERT INTO LIBROS VALUES ('LA HISTORIA DE MI HIJO', 'GORDIMER, NADINE', 'TIEM.MODERNOS',327);
INSERT INTO LIBROS VALUES ('LA MIRADA DEL OTRO', 'G.DELGADO, FERNANDO', 'PLANETA',298);
INSERT INTO LIBROS VALUES ('ÚLTIMAS TARDES CON TERESA','MARSE, JUAN', 'CÍRCULO',350);
INSERT INTO LIBROS VALUES ('LA NOVELA DE P. ANSUREZ', 
'TORRENTE B., GONZALO', 'PLANETA',162);
COMMIT;

REM ********** TABLA NACIMIENTOS:******************

DROP TABLE NACIMIENTOS cascade constraints; 

ALTER SESSION SET NLS_DATE_FORMAT='DD/MM/YYYY';

CREATE TABLE NACIMIENTOS (
 NOMBRE CHAR(15),
 APELLIDO CHAR(15),
 FECHANAC DATE,
 EDAD NUMBER
 ) ;


INSERT INTO NACIMIENTOS VALUES ('PEDRO', 'SÁNCHEZ','12/05/1982', 17);
INSERT INTO NACIMIENTOS VALUES ('JUAN', 'JIMÉNEZ','23/08/1982', 17);
INSERT INTO NACIMIENTOS VALUES ('MARÍA', 'LÓPEZ','02/02/1983', 16);
INSERT INTO NACIMIENTOS VALUES ('CLARA', 'LASECA','20/05/1985', 14);
COMMIT;

REM ************ TABLAS UNIDAD V
REM ************ TABLASUNI5.SQL

REM ************ TABLAS PARALEER Y LEIDOS **************

DROP TABLE PARALEER cascade constraints; 

CREATE  TABLE  PARALEER
(
  COD_LIBRO  NUMBER(3),
  NOMBRE_LIBRO VARCHAR2(40)
) ;

DROP TABLE LEIDOS cascade constraints; 

ALTER SESSION SET NLS_DATE_FORMAT='DD/MM/YYYY';

CREATE  TABLE  LEIDOS
(
  COD_LIBRO  NUMBER(3),
  FECHA  DATE
) ;

INSERT INTO PARALEER values(100,'Cien Años de Soledad');
INSERT INTO PARALEER values (200,'Los Mitos Griegos');
INSERT INTO PARALEER values (300,'El Camino');

INSERT INTO LEIDOS values(300, '20/02/1999');
INSERT INTO LEIDOS values(200, '11/04/1999');

COMMIT;

REM ************ TABLA ALUM, NUEVOS, ANTIGUOS ************

DROP TABLE ALUM cascade constraints;
DROP TABLE NUEVOS cascade constraints;
DROP TABLE ANTIGUOS cascade constraints;

Create TABLE ALUM
(
  NOMBRE VARCHAR2(20),
 EDAD NUMBER(2),
 LOCALIDAD VARCHAR2(15)
) ;

Create TABLE  NUEVOS
(
  NOMBRE  VARCHAR2(20),
 EDAD NUMBER(2),
 LOCALIDAD VARCHAR2(15)
) ;

Create TABLE ANTIGUOS
(
  NOMBRE  VARCHAR2(20),
 EDAD NUMBER(2),
 LOCALIDAD VARCHAR2(15)
) ;

INSERT INTO ALUM VALUES('JUAN',18,'COSLADA');
INSERT INTO ALUM VALUES('PEDRO',19,'COSLADA');
INSERT INTO ALUM VALUES('ANA',17,'ALCALA');
INSERT INTO ALUM VALUES('LUISA',18,'TORREJÓN');
INSERT INTO ALUM VALUES('MARÍA',20,'MADRID');
INSERT INTO ALUM VALUES('ERNESTO',21,'MADRID');
INSERT INTO ALUM VALUES('RAQUEL',19,'TOLEDO');

INSERT INTO NUEVOS VALUES('JUAN',18,'COSLADA');
INSERT INTO NUEVOS VALUES('MAITE',15,'ALCALA');
INSERT INTO NUEVOS VALUES('SOFÍA',14,'ALCALA');
INSERT INTO NUEVOS VALUES('ANA',17,'ALCALA');
INSERT INTO NUEVOS VALUES('ERNESTO',21,'MADRID');

INSERT INTO ANTIGUOS VALUES('MARÍA',20,'MADRID');
INSERT INTO ANTIGUOS VALUES('ERNESTO',21,'MADRID');
INSERT INTO ANTIGUOS VALUES('ANDRÉS',26,'LAS ROZAS');
INSERT INTO ANTIGUOS VALUES('IRENE',24,'LAS ROZAS');

COMMIT;

REM ************ TABLA PERSONAL, PROFESORES, CENTROS ***********

DROP TABLE PERSONAL cascade constraints; 

CREATE TABLE PERSONAL (
 COD_CENTRO   NUMBER(4) NOT NULL,
 DNI NUMBER(10),
 APELLIDOS VARCHAR2(30),
 FUNCION VARCHAR2(15),
 SALARIO NUMBER (10) 
);

INSERT INTO PERSONAL VALUES (10,1112345,'Martínez Salas, Fernando',
'PROFESOR', 220000);
INSERT INTO PERSONAL VALUES (10,4123005,'Bueno Zarco, Elisa', 
'PROFESOR', 220000);
INSERT INTO PERSONAL VALUES (10,4122025,'Montes García, M.Pilar', 
'PROFESOR', 220000);

INSERT INTO PERSONAL VALUES (15,1112345,'Rivera Silvestre, Ana',
'PROFESOR', 205000);
INSERT INTO PERSONAL VALUES (15,9800990, 'Ramos Ruiz, Luis',
'PROFESOR', 205000);
INSERT INTO PERSONAL VALUES (15,8660990, 'De Lucas Fdez, M.Angel',
'PROFESOR', 205000);

INSERT INTO PERSONAL VALUES (22,7650000, 'Ruiz Lafuente, Manuel',
'PROFESOR', 220000);
INSERT INTO PERSONAL VALUES (45,43526789, 'Serrano Laguía, María',
'PROFESOR', 205000);


INSERT INTO PERSONAL VALUES (10,4480099,'Ruano Cerezo, Manuel',
'ADMINISTRATIVO', 180000);
INSERT INTO PERSONAL VALUES (15,1002345,'Albarrán Serrano, Alicia',
'ADMINISTRATIVO', 180000);
INSERT INTO PERSONAL VALUES (15,7002660,'Muñoz Rey, Felicia',
'ADMINISTRATIVO', 180000);
INSERT INTO PERSONAL VALUES (22,5502678,'Marín Marín, Pedro',
'ADMINISTRATIVO', 180000);
INSERT INTO PERSONAL VALUES (22,6600980, 'Peinado Gil, Elena',
'CONSERJE', 175000);
INSERT INTO PERSONAL VALUES (45,4163222, 'Sarro Molina, Carmen',
'CONSERJE', 175000);


DROP TABLE PROFESORES cascade constraints; 

CREATE TABLE PROFESORES (
 COD_CENTRO   NUMBER(4) NOT NULL,
 DNI          NUMBER(10),
 APELLIDOS VARCHAR2(30),
 ESPECIALIDAD VARCHAR2(16) 
) ;


INSERT INTO PROFESORES VALUES (10,1112345,'Martínez Salas, Fernando',
'INFORMÁTICA');
INSERT INTO PROFESORES VALUES (10,4123005,'Bueno Zarco, Elisa', 
'MATEMÁTICAS');
INSERT INTO PROFESORES VALUES (10,4122025,'Montes García, M.Pilar', 
'MATEMÁTICAS');

INSERT INTO PROFESORES VALUES (15,9800990, 'Ramos Ruiz, Luis',
	'LENGUA');
INSERT INTO PROFESORES VALUES (15,1112345,'Rivera Silvestre, Ana',
	'DIBUJO');
INSERT INTO PROFESORES VALUES (15,8660990, 'De Lucas Fdez, M.Angel',
'LENGUA');

INSERT INTO PROFESORES VALUES (22,7650000, 'Ruiz Lafuente, Manuel',
'MATEMÁTICAS');
INSERT INTO PROFESORES VALUES (45,43526789, 'Serrano Laguía, María',
'INFORMÁTICA');

DROP TABLE CENTROS cascade constraints; 

CREATE TABLE CENTROS (
 COD_CENTRO   NUMBER(4) NOT NULL,
 TIPO_CENTRO  CHAR(1),
 NOMBRE VARCHAR2(30),
 DIRECCION VARCHAR2(26),
 TELEFONO VARCHAR2(10),
 NUM_PLAZAS NUMBER(4)
 ) ;


INSERT INTO CENTROS VALUES (10,'S','IES El Quijote', 
'Avda. Los Molinos 25', '965-887654',538);
INSERT INTO CENTROS VALUES (15,'P','CP Los Danzantes', 'C/Las Musas s/n',
'985-112322',250);
INSERT INTO CENTROS VALUES (22,'S', 'IES Planeta Tierra', 'C/Mina 45',
'925-443400',300);
INSERT INTO CENTROS VALUES (45,'P', 'CP Manuel Hidalgo', 'C/Granada 5',
'926-202310',220);
INSERT INTO CENTROS VALUES (50,'S', 'IES Antoñete', 'C/Los Toreros 21',
'989-406090',310);

commit;

REM *************** TABLAS UNIDAD VI ***************
REM *************** TABLASUNI6.SQL *****************

REM *************** TABLA EMPLE30: **************

DROP TABLE EMPLE30 cascade constraints; 

CREATE TABLE EMPLE30 (
 EMP_NO    NUMBER(4) NOT NULL,
 APELLIDO  VARCHAR(10)  ,
 OFICIO    VARCHAR(10)  ,
 DIR       NUMBER(4) ,
 FECHA_ALT DATE      ,
 SALARIO   NUMBER(10),
 COMISION  NUMBER(10),
 DEPT_NO   NUMBER(2) NOT NULL) ;

REM *************** TABLA COCHES: *************

DROP TABLE COCHES cascade constraints; 

CREATE TABLE COCHES (NOMBRE VARCHAR2(15)) ;

INSERT INTO COCHES VALUES('SEAT');

COMMIT;

REM *************** TABLAS ARTICULOS, TIENDAS, FABRICANTES, PEDIDOS y VENTAS:********

DROP TABLE ARTICULOS cascade constraints; 
DROP TABLE TIENDAS cascade constraints; 
DROP TABLE FABRICANTES cascade constraints; 
DROP TABLE PEDIDOS cascade constraints; 
DROP TABLE VENTAS cascade constraints; 

CREATE TABLE ARTICULOS(
ARTICULO       VARCHAR2(20)NOT NULL,
COD_FABRICANTE NUMBER(3) NOT NULL,
PESO           NUMBER(3) NOT NULL ,
CATEGORIA      VARCHAR2(10) NOT NULL,
PRECIO_VENTA   NUMBER (4),
PRECIO_COSTO   NUMBER (4),
EXISTENCIAS    NUMBER (5) ) ;

INSERT INTO ARTICULOS VALUES ('Macarrones',20, 1, 'Primera',100,98,120);
INSERT INTO ARTICULOS VALUES ('Tallarines',20, 2, 'Primera',120,100,100);
INSERT INTO ARTICULOS VALUES ('Tallarines',20, 1, 'Segunda',99,50,100);
INSERT INTO ARTICULOS VALUES ('Macarrones',20, 1, 'Tercera',80,50,100);

INSERT INTO ARTICULOS VALUES ('Atún',10, 3, 'Primera',200,150,220);
INSERT INTO ARTICULOS VALUES ('Atún',10, 3, 'Segunda',150,100,220);
INSERT INTO ARTICULOS VALUES ('Atún',10, 3, 'Tercera',100,50,220);
INSERT INTO ARTICULOS VALUES ('Sardinillas',10, 1,
 'Primera',250,200,200);
INSERT INTO ARTICULOS VALUES ('Sardinillas',10, 1,
 'Segunda',200,160,200);
INSERT INTO ARTICULOS VALUES ('Sardinillas',10, 1, 
'Tercera',100,150,220);
INSERT INTO ARTICULOS VALUES ('Mejillones',10, 1, 
'Tercera',90,50,200);
INSERT INTO ARTICULOS VALUES ('Mejillones',10, 1, 
'Primera',200,150,300);



INSERT INTO ARTICULOS VALUES ('Macarrones',25, 1, 'Primera',90,68,150);
INSERT INTO ARTICULOS VALUES ('Tallarines',25, 1, 'Primera',100,90,100);
INSERT INTO ARTICULOS VALUES ('Fideos',25, 1, 'Segunda',75,50,100);
INSERT INTO ARTICULOS VALUES ('Fideos',25, 1, 'Primera',100,80,100);


INSERT INTO ARTICULOS VALUES ('Galletas Cuadradas',
15, 1, 'Primera',100,80,100);
INSERT INTO ARTICULOS VALUES ('Galletas Cuadradas',
15, 1, 'Segunda',70,50,100);
INSERT INTO ARTICULOS VALUES ('Galletas Cuadradas',
15, 1, 'Tercera',50,40,100);
INSERT INTO ARTICULOS VALUES ('Barquillos',15, 1, 'Primera',100,80,100);
INSERT INTO ARTICULOS VALUES ('Barquillos',15, 1, 'Segunda',100,80,100);
INSERT INTO ARTICULOS VALUES ('Canutillos',15, 2, 'Primera',170,150,110);
INSERT INTO ARTICULOS VALUES ('Canutillos',15, 2, 'Segunda',120,150,110);

INSERT INTO ARTICULOS VALUES ('Leche entera',30, 1, 
'Primera',110,100,300);
INSERT INTO ARTICULOS VALUES ('Leche desnat.',30, 1, 
'Primera',120,100,300);
INSERT INTO ARTICULOS VALUES ('Leche semi.',30, 1, 
'Primera',130,110,300);
INSERT INTO ARTICULOS VALUES ('Leche entera',30, 2, 
'Primera',210,200,300);
INSERT INTO ARTICULOS VALUES ('Leche desnat.',30, 2, 
'Primera',220,200,300);
INSERT INTO ARTICULOS VALUES ('Leche semi.',30, 2, 
'Primera',230,210,300);
INSERT INTO ARTICULOS VALUES ('Mantequilla',30, 1, 
'Primera',510,400,200);
INSERT INTO ARTICULOS VALUES ('Mantequilla',30, 1, 
'Segunda',450,340,200);


CREATE TABLE FABRICANTES(
COD_FABRICANTE NUMBER(3) NOT NULL,
NOMBRE         VARCHAR2(15), 
PAIS           VARCHAR2(15)) ;

INSERT INTO FABRICANTES VALUES(10,'CALVO', 'ESPAÑA');
INSERT INTO FABRICANTES VALUES(15,'LU', 'BELGICA');
INSERT INTO FABRICANTES VALUES(20,'BARILLA', 'ITALIA');
INSERT INTO FABRICANTES VALUES(25,'GALLO', 'ESPAÑA');
INSERT INTO FABRICANTES VALUES(30,'PRESIDENT', 'FRANCIA');

CREATE TABLE TIENDAS(
NIF       VARCHAR2(10) NOT NULL,
NOMBRE    VARCHAR2(20),
DIRECCIÓN VARCHAR2(20),
POBLACIÓN VARCHAR2(20),
PROVINCIA VARCHAR2(20),
CODPOSTAL NUMBER(5) ) ;

INSERT INTO TIENDAS VALUES('1111-A','Almacenes Pérez', 'C/Toledo, 20',
 'Siguenza','GUADALAJARA',19104); 
INSERT INTO TIENDAS VALUES('5555-B','La gacela', 'C/Santander Rios, 45',
 'Azuqueca','GUADALAJARA', 19209);
INSERT INTO TIENDAS VALUES('2222-A','Comestibles Rodolfo', 
'C/ del Val s/n', 'Alcalá de Henares','MADRID',28804);
INSERT INTO TIENDAS VALUES('4444-A','La Pasta Gansa', 'C/Alcalá, 2',
 'Ajalvir','MADRID', 28765);
 INSERT INTO TIENDAS VALUES('3333-N','Ultramarinos Montse',
  'Avda. Pio 10', 'Toledo','TOLEDO',45100);
INSERT INTO TIENDAS VALUES('4141-B','Todo Toledo',
 'C/Avila 24', 'Talavera','TOLEDO',45199);


CREATE TABLE PEDIDOS(
NIF               VARCHAR2(10) NOT NULL,
ARTICULO          VARCHAR2(20) NOT NULL,
COD_FABRICANTE    NUMBER(3) NOT NULL,
PESO              NUMBER(3) NOT NULL,
CATEGORIA         VARCHAR2(10) NOT NULL,
FECHA_PEDIDO      DATE NOT NULL,
UNIDADES_PEDIDAS  NUMBER(4)
) ;

ALTER SESSION SET NLS_DATE_FORMAT='DD/MM/YYYY';

INSERT INTO PEDIDOS VALUES ('5555-B','Macarrones',20, 1, 'Primera',
TO_DATE('18/02/1999'), 30);
INSERT INTO PEDIDOS VALUES ('5555-B','Atún',10, 3, 'Primera',
TO_DATE('21/02/1999'), 10);
INSERT INTO PEDIDOS VALUES ('5555-B','Atún',10, 3, 'Segunda',
TO_DATE('11/03/1999'), 4);
INSERT INTO PEDIDOS VALUES ('5555-B','Sardinillas',10, 1, 'Segunda', 
TO_DATE('11/03/1999'), 10);
INSERT INTO PEDIDOS VALUES ('5555-B','Macarrones',25, 1, 'Primera',
TO_DATE('14/04/1999'), 12);
INSERT INTO PEDIDOS VALUES ('5555-B','Fideos',25, 1, 'Segunda', 
TO_DATE('18/05/1999'), 24);
INSERT INTO PEDIDOS VALUES ('5555-B','Fideos',25, 1, 'Segunda', 
TO_DATE('19/05/1999'), 20);
INSERT INTO PEDIDOS VALUES ('5555-B','Galletas Cuadradas',
15, 1, 'Segunda', TO_DATE('20/06/1999'), 15);

INSERT INTO PEDIDOS VALUES ('1111-A','Barquillos',15, 1, 'Primera',
TO_DATE('20/02/1999'), 10);

INSERT INTO PEDIDOS VALUES ('1111-A','Canutillos',15, 2, 'Segunda',
TO_DATE('10/04/1999'), 12);
INSERT INTO PEDIDOS VALUES ('1111-A','Leche semi.',30, 1, 'Primera',
TO_DATE('24/06/1999'), 5);
INSERT INTO PEDIDOS VALUES ('1111-A','Leche semi.',30, 2, 'Primera',
TO_DATE('04/07/1999'), 11);
INSERT INTO PEDIDOS VALUES ('1111-A','Mantequilla',30, 1, 'Primera', 
TO_DATE('10/07/1999'), 10);

INSERT INTO PEDIDOS VALUES ('4141-B','Macarrones',20, 1, 'Primera',
TO_DATE('16/04/1999'), 30);
INSERT INTO PEDIDOS VALUES ('4141-B','Atún',10, 3, 'Primera',
TO_DATE('21/06/1999'), 10);
INSERT INTO PEDIDOS VALUES ('4141-B','Atún',10, 3, 'Segunda',
TO_DATE('12/08/1999'), 9);


INSERT INTO PEDIDOS VALUES ('2222-A','Sardinillas',10, 1,
 'Segunda', TO_DATE('12/08/1999'),20);
INSERT INTO PEDIDOS VALUES ('2222-A','Sardinillas',10, 1, 
'Tercera', TO_DATE('12/08/1999'),22);
INSERT INTO PEDIDOS VALUES('2222-A','Mejillones',10,1,
 'Primera',SYSDATE,1000);

INSERT INTO PEDIDOS VALUES ('3333-A','Macarrones',25, 1,
 'Primera',TO_DATE('10/11/1999'),8);
INSERT INTO PEDIDOS VALUES ('3333-A','Tallarines',25, 1, 
'Primera', TO_DATE('12/11/1999'),9);
 INSERT INTO PEDIDOS VALUES ('3333-A','Fideos',25, 1, 
'Primera', TO_DATE('15/11/1999'),11);
 INSERT INTO PEDIDOS VALUES ('3333-A','Galletas Cuadradas',
15, 1, 'Primera', TO_DATE('20/11/1999'),6);
INSERT INTO PEDIDOS VALUES ('3333-A','Barquillos',15, 1, 
'Segunda', TO_DATE('20/11/1999'),40);
 INSERT INTO PEDIDOS VALUES ('3333-A','Canutillos',15, 2, 
'Segunda', TO_DATE('20/11/1999'),10);



CREATE TABLE VENTAS(
NIF                VARCHAR2(10) NOT NULL,
ARTICULO           VARCHAR2(20) NOT NULL,
COD_FABRICANTE     NUMBER(3) NOT NULL,
PESO               NUMBER(3) NOT NULL,
CATEGORIA          VARCHAR2(10) NOT NULL,
FECHA_VENTA        DATE NOT NULL,
UNIDADES_VENDIDAS  NUMBER(4)
) ;


INSERT INTO VENTAS VALUES ('5555-B','Macarrones',20, 1, 'Primera',
TO_DATE('19/02/1999'), 5);
INSERT INTO VENTAS VALUES ('5555-B','Atún',10, 3, 'Primera',
TO_DATE('19/02/1999'), 6);
INSERT INTO VENTAS VALUES ('5555-B','Atún',10, 3, 'Segunda',
TO_DATE('20/03/1999'), 15);
INSERT INTO VENTAS VALUES ('5555-B','Sardinillas',10, 1, 'Segunda', 
TO_DATE('20/03/1999'), 8);
INSERT INTO VENTAS VALUES ('5555-B','Macarrones',25, 1, 'Primera',
TO_DATE('17/04/1999'), 2);
INSERT INTO VENTAS VALUES ('5555-B','Fideos',25, 1, 'Segunda', 
TO_DATE('18/05/1999'), 14);
INSERT INTO VENTAS VALUES ('5555-B','Leche semi.',30, 1, 'Primera',
TO_DATE('24/06/1999'), 5);

INSERT INTO VENTAS VALUES ('2222-A','Galletas Cuadradas',
15, 1, 'Segunda', TO_DATE('20/06/1999'), 5);
INSERT INTO VENTAS VALUES ('2222-A','Barquillos',15, 1, 'Primera',
TO_DATE('20/02/1999'), 6);
INSERT INTO VENTAS VALUES ('2222-A','Canutillos',15, 2, 'Segunda',
TO_DATE('10/06/1999'), 2);
INSERT INTO VENTAS VALUES ('2222-A','Sardinillas',10, 1,
 'Segunda', TO_DATE('15/08/1999'),5);
INSERT INTO VENTAS VALUES ('2222-A','Sardinillas',10, 1, 
'Tercera', TO_DATE('15/08/1999'),5);


INSERT INTO VENTAS VALUES ('3333-A','Leche semi.',30, 2, 'Primera',
TO_DATE('06/07/1999'), 11);
INSERT INTO VENTAS VALUES ('3333-A','Mantequilla',30, 1, 'Primera', 
TO_DATE('16/07/1999'), 10);
INSERT INTO VENTAS VALUES ('3333-A','Macarrones',20, 1, 'Primera',
TO_DATE('26/04/1999'), 30);
INSERT INTO VENTAS VALUES ('3333-A','Atún',10, 3, 'Primera',
TO_DATE('26/04/1999'), 10);
INSERT INTO VENTAS VALUES ('3333-A','Barquillos',15, 1, 
'Segunda', TO_DATE('25/11/1999'),4);
 INSERT INTO VENTAS VALUES ('3333-A','Canutillos',15, 2, 
'Segunda', TO_DATE('25/11/1999'),4);

INSERT INTO VENTAS VALUES ('4141-B','Atún',10, 3, 'Segunda',
TO_DATE('12/08/1999'), 2);

INSERT INTO VENTAS VALUES ('4141-B','Macarrones',25, 1,
 'Primera',TO_DATE('10/11/1999'),2);
INSERT INTO VENTAS VALUES ('4141-B','Tallarines',25, 1, 
'Primera', TO_DATE('11/11/1999'),3);
INSERT INTO VENTAS VALUES ('4141-B','Canutillos',15, 2, 
'Segunda', TO_DATE('11/11/1999'),8);

commit;

REM ****************** TABLAS UNIDAD VIII ************
REM ****************** TABLASUNI8.SQL ************

REM ****************** TABLAS TVENTAS Y TARTICULOS:

DROP TABLE TARTICULOS CASCADE CONSTRAINTS;
DROP TABLE TVENTAS CASCADE CONSTRAINTS;

Create table TARTICULOS
(
  CODIGO NUMBER(3)   PRIMARY KEY,
  DENOM VARCHAR2(18) NOT NULL,
  EXIS NUMBER(5),
  PVP NUMBER(4)       
) ;

Create table TVENTAS
(
  CODIGO NUMBER(3)  REFERENCES TARTICULOS,
  FECHA_VENTA DATE ,
  UNI_VEND NUMBER(4),
  PRIMARY KEY (CODIGO, FECHA_VENTA) 
) ;


INSERT INTO TARTICULOS VALUES(100,'NARANJAS', 100,90);
INSERT INTO TARTICULOS VALUES(101,'PATATAS', 200,40);
INSERT INTO TARTICULOS VALUES(102,'CEBOLLAS', 50,92);
INSERT INTO TARTICULOS VALUES(103,'SANDÍAS', 200,120);
INSERT INTO TARTICULOS VALUES(104,'NUECES', 300,190);
INSERT INTO TARTICULOS VALUES(105,'PERAS', 50,110);
INSERT INTO TARTICULOS VALUES(106,'MANZANAS', 55,50);
INSERT INTO TARTICULOS VALUES(107,'JUDÍAS VERDES', 600,145);
INSERT INTO TARTICULOS VALUES(108,'GARBANZOS', 300,220);
INSERT INTO TARTICULOS VALUES(109,'LENTEJAS', 250,197);
INSERT INTO TARTICULOS VALUES(110,'JUDÍAS BLANCAS',178,92);

ALTER SESSION SET NLS_DATE_FORMAT='DD/MM/YYYY';

INSERT INTO TVENTAS VALUES(100,TO_DATE('14/04/1999'),5);
INSERT INTO TVENTAS VALUES(100,TO_DATE('18/04/1999'),6);
INSERT INTO TVENTAS VALUES(100,TO_DATE('19/05/1999'),10);
INSERT INTO TVENTAS VALUES(100,TO_DATE('26/05/1999'),10);

INSERT INTO TVENTAS VALUES(101,TO_DATE('22/04/1999'),20);
INSERT INTO TVENTAS VALUES(101,TO_DATE('25/05/1999'),15);
INSERT INTO TVENTAS VALUES(101,TO_DATE('27/05/1999'),16);

INSERT INTO TVENTAS VALUES(102,TO_DATE('07/04/1999'),10);
INSERT INTO TVENTAS VALUES(102,TO_DATE('09/04/1999'),11);
INSERT INTO TVENTAS VALUES(102,TO_DATE('10/05/1999'),5);
INSERT INTO TVENTAS VALUES(102,TO_DATE('28/05/1999'),6);
INSERT INTO TVENTAS VALUES(102,TO_DATE('30/05/1999'),14);

INSERT INTO TVENTAS VALUES(108,TO_DATE('06/04/1999'),10);
INSERT INTO TVENTAS VALUES(108,TO_DATE('07/05/1999'),11);
INSERT INTO TVENTAS VALUES(108,TO_DATE('10/05/1999'),5);

INSERT INTO TVENTAS VALUES(109,TO_DATE('06/04/1999'),10);
INSERT INTO TVENTAS VALUES(109,TO_DATE('28/05/1999'),6);
INSERT INTO TVENTAS VALUES(109,TO_DATE('29/05/1999'),18);
INSERT INTO TVENTAS VALUES(109,TO_DATE('30/05/1999'),14);
INSERT INTO TVENTAS VALUES(109,TO_DATE('31/05/1999'),18);

INSERT INTO TVENTAS VALUES(110,TO_DATE('21/05/1999'),20);
INSERT INTO TVENTAS VALUES(110,TO_DATE('31/05/1999'),54);

Commit;







