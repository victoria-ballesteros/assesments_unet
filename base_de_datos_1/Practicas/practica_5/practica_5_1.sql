-- TABLA EMPLE Y DEPART

-- 1. Departamentos con salario medio mayor o igual a la media de todos los salarios
SELECT d.dept_no, d.dnombre
FROM DEPART d
JOIN EMPLE e ON d.dept_no = e.dept_no
GROUP BY d.dept_no, d.dnombre
HAVING AVG(e.salario) >= (SELECT AVG(salario) FROM EMPLE);

-- 2. Número de vendedores en el departamento “VENTAS”
SELECT COUNT(*) AS num_vendedores
FROM EMPLE
WHERE dept_no = (SELECT dept_no FROM DEPART WHERE dnombre = 'VENTAS')
AND oficio = 'VENDEDOR';

-- 3. Apellidos cuyo salario sea igual a la media del salario en su departamento
SELECT apellido
FROM EMPLE e1
WHERE salario = (SELECT AVG(e2.salario) 
                 FROM EMPLE e2 
                 WHERE e1.dept_no = e2.dept_no);

-- 4. Número de empleados por departamento cuyo oficio sea “EMPLEADO”
SELECT dept_no, COUNT(*) AS num_empleados
FROM EMPLE
WHERE oficio = 'EMPLEADO'
GROUP BY dept_no;

-- 5. Departamento con más empleados cuyo oficio sea “EMPLEADO”
SELECT dept_no
FROM EMPLE
WHERE oficio = 'EMPLEADO'
GROUP BY dept_no
ORDER BY COUNT(*) DESC
FETCH FIRST 1 ROWS ONLY;

-- 6. Número y nombre del departamento con más empleados cuyo oficio sea “EMPLEADO”
SELECT d.dept_no, d.dnombre
FROM DEPART d
JOIN EMPLE e ON d.dept_no = e.dept_no
WHERE e.oficio = 'EMPLEADO'
GROUP BY d.dept_no, d.dnombre
ORDER BY COUNT(*) DESC
FETCH FIRST 1 ROWS ONLY;

-- 7. Suma de salarios por oficio en el departamento "VENTAS"
SELECT oficio, SUM(salario) AS suma_salarios
FROM EMPLE
WHERE dept_no = (SELECT dept_no FROM DEPART WHERE dnombre = 'VENTAS')
GROUP BY oficio;

-- TABLA LIBRERÍA

-- 1. Suma de ejemplares por estante
SELECT estante, SUM(ejemplares) AS total_ejemplares
FROM LIBRERIA
GROUP BY estante;

-- 2. Estante con más ejemplares
SELECT estante
FROM (
    SELECT estante, SUM(ejemplares) AS total_ejemplares
    FROM LIBRERIA
    GROUP BY estante
    ORDER BY total_ejemplares DESC
) WHERE ROWNUM = 1;

-- TABLA ALUM, ANTIGUOS Y NUEVOS

-- 1. Nombres de alumnos en alguna de las tablas NUEVOS o ANTIGUOS
SELECT nombre 
FROM ALUM 
WHERE nombre IN (SELECT nombre FROM NUEVOS)
   OR nombre IN (SELECT nombre FROM ANTIGUOS);

-- 2. Alternativas de la consulta anterior
SELECT nombre FROM ALUM 
INTERSECT 
(SELECT nombre FROM NUEVOS UNION SELECT nombre FROM ANTIGUOS);

SELECT nombre 
FROM ALUM 
WHERE nombre IN (SELECT nombre FROM NUEVOS UNION SELECT nombre FROM ANTIGUOS);

-- 3. Nombres de alumnos que están en ambas tablas, NUEVOS y ANTIGUOS
SELECT nombre
FROM ALUM
WHERE nombre IN (SELECT nombre FROM NUEVOS)
AND nombre IN (SELECT nombre FROM ANTIGUOS);

-- 4. Alternativas de la consulta anterior
SELECT nombre 
FROM NUEVOS 
INTERSECT 
SELECT nombre FROM ANTIGUOS;

SELECT n.nombre 
FROM NUEVOS n
JOIN ANTIGUOS a ON n.nombre = a.nombre;

-- 5. Nombres de alumnos que no están en ANTIGUOS ni en NUEVOS
SELECT nombre 
FROM ALUM 
WHERE nombre NOT IN (SELECT nombre FROM NUEVOS)
AND nombre NOT IN (SELECT nombre FROM ANTIGUOS);

-- TABLA PERSONAL, PROFESORES Y CENTROS

-- 1. Número de profesores por centro y especialidad (incluyendo centros sin profesores)
SELECT c.cod_centro, p.especialidad, COALESCE(COUNT(p.dni), 0) AS num_profesores
FROM CENTROS c
LEFT JOIN PROFESORES p ON c.cod_centro = p.cod_centro
GROUP BY c.cod_centro, p.especialidad;

-- 2. Número de empleados por centro (incluyendo centros sin empleados)
SELECT c.cod_centro, COALESCE(COUNT(p.dni), 0) AS num_empleados
FROM CENTROS c
LEFT JOIN PERSONAL p ON c.cod_centro = p.cod_centro
GROUP BY c.cod_centro;

-- 3. Especialidad con menos empleados
SELECT funcion
FROM PERSONAL
GROUP BY funcion
ORDER BY COUNT(*) ASC
FETCH FIRST 1 ROWS ONLY;




