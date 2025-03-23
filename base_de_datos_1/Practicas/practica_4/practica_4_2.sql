-- Parte 1

-- 1
SELECT codart, precio * 2 AS doble_precio
FROM articulos
WHERE precio < 1;

-- 2
SELECT codfac, codart
FROM lineas_fac
WHERE cant < 2
AND dto >= 50;

-- 3
SELECT descrip, stock, stock_min
FROM articulos
WHERE stock < stock_min;

-- 4
SELECT descrip, stock, stock_min, (stock_min - stock) AS cantidad_necesaria
FROM articulos
WHERE stock < stock_min;

-- 5
SELECT DISTINCT codart
FROM lineas_fac
WHERE codfac BETWEEN 8 AND 10;

-- 6
SELECT codart, 
       CASE 
           WHEN stock > stock_min THEN 'STOCK SUFICIENTE'
           WHEN stock = stock_min THEN 'STOCK AJUSTADO'
           ELSE 'STOCK INSUFICIENTE' 
       END AS estado_stock
FROM articulos
WHERE precio < 1;

-- 7
SELECT nombre
FROM provincias
WHERE LOWER(SUBSTR(nombre, 2, 1)) = 'o'
AND LOWER(SUBSTR(nombre, -1, 1)) = 'a';

-- Parte 2

-- 1
SELECT c.nombre AS cliente, p.nombre AS pueblo
FROM clientes c
JOIN pueblos p ON c.codpue = p.codpue
JOIN provincias prov ON p.codpro = prov.codpro
WHERE prov.nombre = 'Soria';

-- 2
SELECT f.codfac AS codigo_factura, c.nombre AS cliente, p.nombre AS pueblo
FROM facturas f
JOIN clientes c ON f.codcli = c.codcli
JOIN pueblos p ON c.codpue = p.codpue
JOIN provincias prov ON p.codpro = prov.codpro
WHERE EXTRACT(YEAR FROM f.fecha) = 1996
AND prov.nombre = 'Castellón';

--3
SELECT COUNT(*) AS num_pueblos
FROM pueblos p
JOIN provincias prov ON p.codpro = prov.codpro
WHERE prov.nombre = 'Soria';

-- 4

-- 5
SELECT c.nombre AS cliente, f.codfac AS codigo_factura, f.fecha AS fecha_factura,
       lf.linea, lf.cant AS cantidad, lf.precio, lf.dto AS descuento
FROM facturas f
JOIN clientes c ON f.codcli = c.codcli
JOIN lineas_fac lf ON f.codfac = lf.codfac
WHERE EXTRACT(MONTH FROM f.fecha) = 12
AND EXTRACT(YEAR FROM f.fecha) = 1998
AND lf.dto IS NULL;

-- 6
SELECT f.codfac AS codigo_factura, f.fecha, c.nombre AS cliente,
       p.nombre AS pueblo, prov.nombre AS provincia,
       CASE 
           WHEN f.iva = 16 THEN 'Normal (16)'
           WHEN f.iva = 7 THEN 'Reducido (7)'
           ELSE 'Otros'
       END AS tipo_iva
FROM facturas f
JOIN clientes c ON f.codcli = c.codcli
JOIN pueblos p ON c.codpue = p.codpue
JOIN provincias prov ON p.codpro = prov.codpro
WHERE EXTRACT(MONTH FROM f.fecha) = 12
AND EXTRACT(YEAR FROM f.fecha) = 1997;

-- 7
SELECT a.descrip AS nombre_articulo, a.stock_min, a.stock, c.nombre AS cliente,
       f.codfac AS codigo_factura, f.fecha AS fecha_factura
FROM articulos a
JOIN lineas_fac lf ON a.codart = lf.codart
JOIN facturas f ON lf.codfac = f.codfac
JOIN clientes c ON f.codcli = c.codcli
JOIN pueblos p ON c.codpue = p.codpue
WHERE a.stock < a.stock_min
AND (p.nombre = 'ARAYA' OR p.nombre = 'BUGARRA');
