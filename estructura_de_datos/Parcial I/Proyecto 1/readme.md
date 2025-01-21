# Primer Proyecto: Sistema transaccional de venta y control de inventario
## Por Javier Chacon (29.185.050) y Maria Ballesteros (31.060.745)
## Claves de usuario
```
Administrador: 11235
Personal de almacen: 81321
Personal de caja: 34558
```
## Guia de instalacion del programa
El presente codigo fue escrito en VS Code, debido a ciertos problemas internos de compilacion que impidieron el correcto funcionamiento de Dev C++ (Situacion que no volvera a repetirse). En vista de estos infortunios, el procedimiento de ejecucion es el siguiente (En caso de no poder compilarse en los IDE's de su equipo):
1. Ejecutar en terminal los comandos `g++ --version`, `gcc --version` y `gdb --version`. En caso de no tenerlos (o tener una version desactualizada), se recomienda su pertinente instalacion con la ayuda de minGW.
2. Abrir la terminal en la carpeta del proyecto y ejecutar `g++ main.cpp -o main`, posteriormente ejecutar el archivo .exe generado.
NOTA: Se incluye un .exe con la ultima compilacion del programa para su ejecucion directa.
## Guia de Usuario Administrador
Una vez introducida su clave de acceso, se le permitira acceder a un menu donde se desplegaran todos los posibles archivos a los que puede acceder; una vez ha seleccionado uno de ellos, se le permitira registrar, modificar o eliminar ua entrada en ese archivo. Claro que, segun las indicaciones proporcionadas, estas acciones se veran limitadas por las condiciones relacionales de la base de datos, es decir, se deberan respetar las siguientes conexiones estrictamente:
---
1. Una factura debe estar asociada al ID de un cliente existente en la base de datos.
2. Toda compra debe estar asociada al ID de un cliente y de un producto existentes en la base de datos.
3. Todo producto debe estar asociado a un proveedor cuyo ID este registrado en la base de datos.
Respetando estas reglas, puede modificar a su gusto todos los campos del archivo que desee.
---
Adicional a esto, de existir un archivo auxiliar con actualizaciones respectivas a la informacion de los productos manejados por el Personal de Almacen, debera aprobar o eliminar dicho archivo.
## Guia de Personal de Almacen
Inmediatamente despues de introducir la clave de acceso correspondiente, debera introducir un nombre para el archivo auxiliar (copia del archivo original de Productos), sobre el cual estara trabajando. Podra modificar el precio y cantidad en stock de todo producto que sea necesario. Posteriormente, y al finalizar su labor, unicamente debera cerrar sesion. La aprobacion del archivo auxiliar y su respectiva incorporacion a la base de datos quedara en manos del personal administrativo.
## Guia de Personal de Caja
Como vendedor puede procesar compras mediante el ID del cliente (de no existir en la base de datos se le solicitara que llene un formulario corto). Una vez registradas las compras con sus ID's pertinentes y sus cantidades, y de ser aprobadas estas compras una vez validadas las cantidades en stock; posteriormente se imprime la factura y se concluye la transaccion, asi toda la jornada hasta cerrar la caja.