#include <iostream>
#include <stdlib.h>
#include <limits>
#include <locale.h>
#include <fstream>
#include <cstring>
#include "registro.h"

class compras : public registro
{

public:
   void listarCompras()
   {
      std::fstream archivo("database/Compra.bin", std::ios::binary | std::ios::in | std::ios::out);
      if (archivo.fail())
      {
         cerr << "No se pudo abrir el archivo.\n";
         system("pause");
         return;
      }
      Compra compra;
      while (archivo.read((char *)&compra, sizeof(Compra)))
      {
         std::cout << "" << '\n';
         std::cout << "ID--------------------: " << compra.id << "\n";
         std::cout << "PRODUCTO--------------: " << compra.id_producto << "\n";
         std::cout << "CANTIDAD--------------: " << compra.cantidad << "\n";
         std::cout << "____________________________________________________" << '\n';
         std::cout << "" << '\n';
      }
      archivo.close();
   }

   void imprimirCompra(Compra compra)
   {
      std::cout << "ID--------------: " << compra.id << '\n';
      std::cout << "ID_PRODUCTO-----: " << compra.id_producto << '\n';
      std::cout << "CANTIDAD--------: " << compra.cantidad << '\n';
      std::cout << "ID_FACTURA------: " << compra.id_factura << '\n';
      std::cout << "______________________________________________ " << '\n';
      std::cout << '\n';
   }

   void registrarCompra()
   {
      int auxId = 0, generadorId = 0;
      string linea = "";
      Compra modelo;
      ofstream archivo("database/Compra.bin", ios::app | ios::binary);
      std::cout << "\nPor favor introduzca el ID de la compra: ";
      auxId = helper.validarIntSinLimite();
      modelo = getCompra(auxId);
      if (modelo.id != -1)
      {
         system("cls");
         std::cout << "\nYa existe una compra con el ID especificado\n\n";
         system("pause");
         return;
      }
      system("cls");
      std::cout << "***** Datos compra *****\n\n";
      std::cout << "Por favor introduzca la informacion solicitada a continuacion:\n\n";
      modelo.id = auxId;
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      std::cout << "Id del producto: ";
      modelo.id_producto = helper.validarIntSinLimite();
      std::cout << "Id de la factura: ";
      modelo.id_factura = helper.validarIntSinLimite();
      std::cout << "Cantidad: ";
      modelo.cantidad = helper.validarIntSinLimite();
      if (archivo.fail())
      {
         system("cls");
         cerr << "\nNo se pudo abrir el archivo.\n\n";
         system("pause");
         return;
      }
      else
      {
         archivo.write((char *)&modelo, sizeof(Compra));
         archivo.close();
         std::cout << "\nCompra registrada exitosamente\n\n";
         system("pause");
      }
   }

   void modificarCompra()
   {
      string linea = "";
      Compra modelo;
      Producto modeloProducto, modeloProductoCambio;
      int auxId = 0, generadorId = 0, cambioPropiedad = 0, aux_id_producto = 0;
      fstream archivo("database/Compra.bin", ios::out | ios::in | ios::binary);
      std::cout << "\nPor favor introduzca el ID de la compra: ";
      auxId = helper.validarIntSinLimite();
      modelo = getCompra(auxId);
      if (modelo.id == -1)
      {
         system("cls");
         std::cout << "\nNo existe una compra con el ID especificado\n\n";
         system("pause");
         return;
      }
      do
      {
         system("cls");
         std::cout << "***** Modificacion de Compra *****\n\n";
         imprimirCompra(modelo);
         std::cout << "Seleccione la opcion que desee cambiar:\n\n";
         std::cout << "1. ID del producto asociado\n";
         std::cout << "2. ID de la factura asociada\n";
         std::cout << "3. Cantidad\n";
         std::cout << "4. Salir\n\n";
         std::cout << "Respuesta: ";
         cambioPropiedad = helper.validarInt(4);
         std::cout << '\n';
         if (cambioPropiedad == 1)
         {
            std::cout << "ID del producto asociado: ";
            aux_id_producto = helper.validarIntSinLimite();
            modeloProducto = getProducto(aux_id_producto);
            if (modeloProducto.id == -1)
            {
               system("cls");
               std::cout << "\nNo existe un producto con el ID indicado.\n\n";
               system("pause");
            }
            else
            {
               modeloProductoCambio = getProducto(modelo.id_producto);
               modeloProductoCambio.stock += modelo.cantidad;
               modeloProducto.stock -= modelo.cantidad;
               modelo.id_producto = aux_id_producto;
            }
         }
         else if (cambioPropiedad == 2)
         {
            std::cout << "Id de la factura asociada: ";
            modelo.id_factura = helper.validarIntSinLimite();
            std::cout << "\nId de la factura editado extisoamente\n\n";
            system("pause");
         }
         else if (cambioPropiedad == 3)
         {
            std::cout << "Cantidad: ";
            modelo.cantidad = helper.validarIntSinLimite();
            std::cout << "\nCantidad de la factura editado exitosamente\n\n";
            system("pause");
         }
      } while (cambioPropiedad != 4);
      if (archivo.fail())
      {
         system("cls");
         cerr << "\nNo se pudo abrir el archivo.\n\n";
         system("pause");
         return;
      }

      {
         archivo.seekg(auxPosicionCompra * sizeof(Compra));
         archivo.write((char *)&modelo, sizeof(Compra));
         archivo.close();
      }
   }

   void eliminarRegistro()
   {
      int auxId = 0;
      Compra modelo;
      Compra reemplazo;
      fstream archivoOriginal("database/Compra.bin", ios::out | ios::in | ios::binary);
      fstream archivoTemporal("database/CompraTemp.bin", ios::out);
      archivoTemporal.close();
      archivoTemporal.open("database/CompraTemp.bin", ios::in | ios::out | ios::binary);
      std::cout << "\nPor favor introduzca el ID de la compra: ";
      auxId = helper.validarIntSinLimite();
      modelo = getCompra(auxId);
      if (modelo.id == -1)
      {
         system("cls");
         std::cout << "\nNo existe una compra con el ID especificado\n\n";
         system("pause");
         return;
      }
      if (archivoOriginal.fail())
      {
         system("cls");
         cerr << "\nNo se pudo abrir el archivo.\n\n";
         system("pause");
         return;
      }
      if (archivoTemporal.fail())
      {
         system("cls");
         cerr << "\nNo se pudo abrir el archivo.\n\n";
         system("pause");
         return;
      }
      while (archivoOriginal.read((char *)&reemplazo, sizeof(Compra)))
      {
         if (reemplazo.id != modelo.id)
         {
            archivoTemporal.write((char *)&reemplazo, sizeof(Compra));
         }
      }

      archivoOriginal.close();
      archivoTemporal.close();
      remove("database/Compra.bin");
      rename("database/CompraTemp.bin", "database/Compra.bin");
   std:
      cout << "\nArchivo eliminado exitosamente.\n\n";
      system("pause");
   }

   void registrarCompraCaja(int id_factura, int id_compra)
   {
      Compra modelo;
      ofstream archivo("database/Compra.bin", ios::app | ios::binary);
      modelo.id = id_compra;
      modelo.id_factura = id_factura;
      int id_producto_aux = 0, cantidad_producto_aux = 0, confirmarCompra = 0;
      Producto modeloProducto;
      do
      {
         std::cout << "\nPor favor introduzca el Id del producto: ";
         id_producto_aux = helper.validarIntSinLimite();
         modeloProducto = getProducto(id_producto_aux);
         if (modeloProducto.id == -1)
         {
            system("cls");
            std::cout << "\nEl producto indicado no existe en la base de datos\n";
            std::cout << "Eche un vistazo a los productos disponibles\n\n";
            listarProductos("database/Producto.bin");
            system("pause");
         }
         if ((modeloProducto.stock_min > modeloProducto.stock) && modeloProducto.id != -1)
         {
            system("cls");
            std::cout << "Producto no disponible para la venta por escasez de inventario.\n\n";
            system("pause");
         }
      } while (modeloProducto.id == -1 || modeloProducto.stock_min > modeloProducto.stock);
      do
      {
         std::cout << "Cantidad del producto a facturar: ";
         cantidad_producto_aux = helper.validarIntSinLimite();

         if (modeloProducto.stock < cantidad_producto_aux)
         {
            system("cls");
            std::cout << "\nNo hay suficiente producto en existencia\n\n";
            system("pause");
         }
      } while (modeloProducto.stock < cantidad_producto_aux);
      std::cout << "Por favor confirme la compra (Una vez confirmada se ejecutaran cambios irreversibles en la base de datos)\n";
      std::cout << "1. Si" << '\n';
      std::cout << "2. No" << '\n';
      confirmarCompra = helper.validarInt(2);
      if (confirmarCompra == 1)
      {
         if (archivo.fail())
         {
            system("cls");
            cerr << "No se pudo abrir el archivo.\n\n";
            system("pause");
            return;
         }
         else
         {
            modelo.id = id_compra;
            modelo.cantidad = cantidad_producto_aux;
            modelo.id_factura = id_factura;
            modelo.id_producto = id_producto_aux;
            modificarCantidadProducto(modeloProducto.id, cantidad_producto_aux);
            archivo.write((char *)&modelo, sizeof(Compra));
            archivo.close();
         }
      }
      else
      {
         system("cls");
         std::cout << "\nCompra cancelada\n\n";
         system("pause");
      }
   }

   void listarComprasUnicas(int id_factura)
   {
      ifstream archivo("database/Compra.bin", ios::binary);
      if (archivo.fail())
      {
         system("cls");
         cerr << "\nNo se pudo abrir el archivo.\n\n";
         system("pause");
         return;
      }
      Compra compra;
      while (archivo.read((char *)&compra, sizeof(Compra)))
      {
         if (archivo.fail())
         {
            system("cls");
            cerr << "\nError al leer del archivo.\n\n";
            system("pause");
            return;
         }
         if (compra.id_factura == id_factura)
         {
            std::cout << "" << '\n';
            std::cout << "ID--------------------: " << compra.id << "\n";
            std::cout << "PRODUCTO--------------: " << compra.id_producto << "\n";
            std::cout << "CANTIDAD--------------: " << compra.cantidad << "\n";
            std::cout << "____________________________________________________________" << '\n';
            std::cout << '\n';
         }
      }
      archivo.close();
   }

   void eliminarComprasPorFactura(int id_factura, std::vector<int> &v_id, std::vector<int> &v_cant)
   {
      int auxId = 0;
      Compra reemplazo;
      fstream archivoOriginal("database/Compra.bin", ios::out | ios::in | ios::binary);
      fstream archivoTemporal("database/CompraTemp.bin", ios::out);
      archivoTemporal.close();
      archivoTemporal.open("database/CompraTemp.bin", ios::in | ios::out | ios::binary);

      if (archivoOriginal.fail())
      {
         cerr << "No se pudo abrir el archivo.\n";
         system("pause");
         return;
      }
      if (archivoTemporal.fail())
      {
         cerr << "No se pudo abrir el archivo.\n";
         system("pause");
         return;
      }
      while (archivoOriginal.read((char *)&reemplazo, sizeof(Compra)))
      {
         if (reemplazo.id_factura != id_factura)
         {
            archivoTemporal.write((char *)&reemplazo, sizeof(Compra));
         }
         else if (reemplazo.id_factura == id_factura)
         {
            v_cant.push_back(reemplazo.cantidad);
            v_id.push_back(reemplazo.id_producto);
            system("pause");
         }
      }
      archivoOriginal.close();
      archivoTemporal.close();
      remove("database/Compra.bin");
      rename("database/CompraTemp.bin", "database/Compra.bin");
   }
};