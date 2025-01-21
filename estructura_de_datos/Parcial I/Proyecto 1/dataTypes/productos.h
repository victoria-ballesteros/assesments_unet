#include <iostream>
#include <stdlib.h>
#include <limits>
#include <locale.h>
#include <fstream>
#include <cstring>
#include "registro.h"

class productos : public registro
{

public:
   void imprimirProducto(Producto producto)
   {
      std::cout << "ID---------------: " << producto.id << '\n';
      std::cout << "ID proveedor-----: " << producto.id_proveedor << '\n';
      std::cout << "Stock------------: " << producto.stock << '\n';
      std::cout << "Precio-----------: " << producto.precio << '\n';
      std::cout << "Descripcion------: " << producto.description << '\n';
      std::cout << "Stock minimo-----: " << producto.stock_min << '\n';
      std::cout << "____________________________________________________________" << '\n';
      std::cout << '\n';
   }

   void registrarProducto()
   {
      int auxId = 0, generadorId = 0, aux_id_proveedor = 0;
      string linea = "";
      Producto modelo;
      Proveedor modeloProveedor;
      ofstream archivo("database/Producto.bin", ios::app | ios::binary);
      std::cout << "Por favor introduzca el ID del producto:" << '\n';
      auxId = helper.validarInt(99999);
      modelo = getProducto(auxId);
      if (modelo.id != -1)
      {
         std::cout << "Ya existe un producto con el ID especificado" << '\n';
         system("pause");
         return;
      }
      std::cout << "Por favor introduzca la informacion solicitada a continuacion:" << '\n';
      modelo.id = auxId;
      std::cout << "ID del proveedor: ";
      aux_id_proveedor = helper.validarIntSinLimite();
      modeloProveedor = getProveedor(aux_id_proveedor);
      if (modeloProveedor.id == -1)
      {
         std::cout << "No existe un proveedor con el ID especificado, por favor registrelo primero." << '\n';
         system("pause");
         return;
      }
      modelo.id_proveedor = aux_id_proveedor;
      std::cout << "Cantidad en stock: ";
      modelo.stock = helper.validarIntSinLimite();
      std::cout << "Precio: ";
      modelo.precio = helper.validarFloat();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      std::cout << "Descripcion: ";
      getline(cin, linea);
      strcpy(modelo.description, linea.c_str());
      std::cout << "Cantidad minima de stock necesaria: ";
      modelo.stock_min = helper.validarIntSinLimite();
      if (archivo.fail())
      {
         cerr << "No se pudo abrir el archivo.\n";
         system("pause");
         return;
      }
      else
      {
         archivo.seekp((cantidadRegistro("database/Producto.bin", sizeof(Producto))) * sizeof(Producto));
         archivo.write((char *)&modelo, sizeof(Producto));
         archivo.close();
      }
   }

   void modificarProducto(string dir)
   {
      string linea = "";
      Producto modelo;
      Proveedor modeloProveedor;
      int auxId = 0, generadorId = 0, cambioPropiedad = 0;
      int aux_id_proveedor = 0;
      fstream archivo(dir, ios::out | ios::in | ios::binary);
      std::cout << "Por favor introduzca el ID del producto:" << '\n';
      auxId = helper.validarIntSinLimite();
      modelo = getProducto(auxId);
      if (modelo.id == -1)
      {
         std::cout << "No existe un producto con el ID especificado" << '\n';
         system("pause");
         return;
      }
      do
      {
         imprimirProducto(modelo);
         std::cout << "Seleccione la opcion que desee cambiar:" << '\n';
         std::cout << "1. ID proveedor" << '\n';
         std::cout << "2. Stock" << '\n';
         std::cout << "3. Precio" << '\n';
         std::cout << "4. Descripcion" << '\n';
         std::cout << "5. Stock minimo" << '\n';
         std::cout << "6. Terminar proceso" << '\n';
         std::cout << "Respuesta: ";
         cin >> cambioPropiedad;
         std::cout << "" << '\n';

         if (cambioPropiedad == 1)
         {
            std::cout << "ID del proveedor: ";
            aux_id_proveedor = helper.validarIntSinLimite();
            modeloProveedor = getProveedor(aux_id_proveedor);
            if (modeloProveedor.id == -1)
            {
               cout << "El proveedor indicado no existe, por favor registrelo primero." << '\n';
            }
            else
            {
               modelo.id_proveedor = aux_id_proveedor;
            }
         }
         else if (cambioPropiedad == 2)
         {
            std::cout << "Stock: ";
            modelo.stock = helper.validarIntSinLimite();
         }
         else if (cambioPropiedad == 3)
         {
            std::cout << "Precio: ";
            modelo.precio = helper.validarFloat();
         }
         else if (cambioPropiedad == 4)
         {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            std::cout << "Descripcion: ";
            getline(cin, linea);
            strcpy(modelo.description, linea.c_str());
         }
         else if (cambioPropiedad == 5)
         {
            std::cout << "Stock minimo: ";
            modelo.stock_min = helper.validarIntSinLimite();
         }
      } while (cambioPropiedad != 6);
      if (archivo.fail())
      {
         cerr << "No se pudo abrir el archivo.\n";
         system("pause");
         return;
      }
      else
      {
         archivo.seekg(auxPosicionProducto * sizeof(Producto));
         archivo.write((char *)&modelo, sizeof(Producto));
         archivo.close();
      }
   }

   void eliminarRegistro()
   {
      int auxId = 0;
      Producto modelo;
      Producto reemplazo;
      fstream archivoOriginal("database/Producto.bin", ios::out | ios::in | ios::binary);
      fstream archivoTemporal("database/ProductoTemp.bin", ios::out);
      archivoTemporal.close();
      archivoTemporal.open("database/ProductoTemp.bin", ios::in | ios::out | ios::binary);
      std::cout << "Por favor introduzca el ID del producto:" << '\n';
      auxId = helper.validarIntSinLimite();
      modelo = getProducto(auxId);
      if (modelo.id == -1)
      {
         std::cout << "No existe un producto con el ID especificado" << '\n';
         system("pause");
         return;
      }
      if (archivoOriginal.fail())
      {
         std::cout << "No se pudo abrir el archivo original." << strerror(errno);
         system("pause");
         return;
      }

      if (archivoTemporal.fail())
      {
         std::cout << "No se pudo abrir el archivo temporal." << strerror(errno);
         system("pause");
         return;
      }

      while (archivoOriginal.read((char *)&reemplazo, sizeof(Producto)))
      {
         if (reemplazo.id != modelo.id)
         {
            archivoTemporal.write((char *)&reemplazo, sizeof(Producto));
         }
      }
      archivoOriginal.close();
      archivoTemporal.close();
      remove("database/Producto.bin");
      rename("database/ProductoTemp.bin", "database/Producto.bin");
   }

   void escribirNuevoArchivo(string newDir)
   {
      ifstream archivoOriginal("database/Producto.bin", std::ios::binary);
      ofstream archivoCopia("database/" + newDir + ".bin", std::ios::binary);
      if (archivoOriginal.fail())
      {
         cerr << "No se pudo abrir el archivo original.\n";
         system("pause");
         return;
      }
      if (archivoCopia.fail())
      {
         cerr << "No se pudo abrir el archivo.\n";
         system("pause");
         return;
      }
      archivoCopia << archivoOriginal.rdbuf();
   }

   void modificacionesAlmacen(string dir, int id_producto)
   {
      string linea = "";
      Producto modelo = getProducto(id_producto);
      int auxId = 0, generadorId = 0, cambioPropiedad = 0;
      fstream archivo(dir, ios::out | ios::in | ios::binary);
      do
      {
         imprimirProducto(modelo);
         std::cout << "Seleccione la opcion que desee cambiar:" << '\n';
         std::cout << "1. Stock" << '\n';
         std::cout << "2. Precio" << '\n';
         std::cout << "3. Terminar proceso" << '\n';
         std::cout << "Respuesta: ";
         cambioPropiedad = helper.validarInt(3);
         std::cout << '\n';
         if (cambioPropiedad == 1)
         {
            std::cout << "Stock: ";
            modelo.stock = helper.validarIntSinLimite();
         }
         else if (cambioPropiedad == 2)
         {
            std::cout << "Precio: ";
            modelo.precio = helper.validarFloat();
         }
      } while (cambioPropiedad != 3);
      if (archivo.fail())
      {
         cerr << "No se pudo abrir el archivo.\n";
         system("pause");
         return;
      }
      else
      {
         archivo.seekg(auxPosicionProducto * sizeof(Producto));
         archivo.write((char *)&modelo, sizeof(Producto));
         archivo.close();
      }
   }

   void modificacionesStock(std::vector<int>& v_id, std::vector<int>& v_cant)
   {
      fstream archivo("database/Producto.bin", ios::out | ios::in | ios::binary);
      Producto modelo;
      int cont = 0;
      if (archivo.fail())
      {
         system("cls");
         std::cout << "No se pudo abrir el archivo.\n\n";
         return;
      }

      for (int i = 0; i < v_id.size(); i++) {
         modelo = getProducto(v_id[i]);
         
         if (modelo.id != -1)
         {
            modelo.stock += v_cant[i];
         }
         archivo.seekg(auxPosicionProducto * sizeof(Producto));
         archivo.write((char *)&modelo, sizeof(Producto));
      }
      archivo.close();
   }
};