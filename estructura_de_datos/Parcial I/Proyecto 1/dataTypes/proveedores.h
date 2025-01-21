#include <iostream>
#include <stdlib.h>
#include <limits>
#include <locale.h>
#include <fstream>
#include <cstring>
#include "registro.h"

class proveedores : public registro
{

public:
   void listarProveedores()
   {
      std::fstream archivo("database/Proveedor.bin", std::ios::binary | std::ios::in | std::ios::out);
      if (archivo.fail())
      {
         cerr << "No se pudo abrir el archivo.\n";
         system("pause");
         return;
      }
      Proveedor proveedor;
      while (archivo.read((char *)&proveedor, sizeof(Proveedor)))
      {
         std::cout << "" << '\n';
         std::cout << "ID--------------------: " << proveedor.id << "\n";
         std::cout << "NOMBRE----------------: " << proveedor.nombre << "\n";
         std::cout << "TELEFONO--------------: " << proveedor.telefono << "\n";
         std::cout << "____________________________________________________________" << '\n';
         std::cout << '\n';
      }
      archivo.close();
   }

   void imprimirProveedor(Proveedor proveedor)
   {
      std::cout << "ID--------------: " << proveedor.id << '\n';
      std::cout << "NOMBRE----------: " << proveedor.nombre << "\n";
      std::cout << "TELEFONO--------: " << proveedor.telefono << "\n";
      std::cout << "____________________________________________________________" << '\n';
      std::cout << "" << '\n';
   }

   void registrarProveedor()
   {
      int auxId = 0, generadorId = 0;
      string linea = "";
      Proveedor modelo;
      ofstream archivo("database/Proveedor.bin", ios::app | ios::binary);
      std::cout << "Por favor introduzca el ID del proveedor:" << '\n';
      auxId = helper.validarIntSinLimite();
      modelo = getProveedor(auxId);
      if (modelo.id != -1)
      {
         std::cout << "Ya existe un proveedor con el ID especificado" << '\n';
         system("pause");
         return;
      }
      std::cout << "Por favor introduzca la informacion solicitada a continuacion:" << '\n';
      modelo.id = auxId;
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      std::cout << "Nombre: ";
      getline(cin, linea);
      strcpy(modelo.nombre, linea.c_str());
      std::cout << "Telefono: ";
      getline(cin, linea);
      strcpy(modelo.telefono, linea.c_str());
      if (archivo.fail())
      {
         cerr << "No se pudo abrir el archivo para escritura.\n";
         system("pause");
         return;
      }
      else
      {
         archivo.write((char *)&modelo, sizeof(Proveedor));
         archivo.close();
      }
   }

   void modificarProveedor()
   {
      string linea = "";
      Proveedor modelo;
      int auxId = 0, generadorId = 0, cambioPropiedad = 0;
      fstream archivo("database/Proveedor.bin", ios::out | ios::in | ios::binary);
      std::cout << "Por favor introduzca el ID del proveedor:" << '\n';
      auxId = helper.validarIntSinLimite();
      modelo = getProveedor(auxId);
      if (modelo.id == -1)
      {
         std::cout << "No existe un proveedor con el ID especificado" << '\n';
         system("pause");
         return;
      }
      do
      {
         imprimirProveedor(modelo);
         std::cout << "Seleccione la opcion que desee cambiar:" << '\n';
         std::cout << "1. Nombre" << '\n';
         std::cout << "2. Telefono" << '\n';
         std::cout << "3. Salir" << '\n';
         std::cout << "Respuesta: ";
         cambioPropiedad = helper.validarInt(3);
         std::cout << '\n';

         if (cambioPropiedad == 1)
         {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            std::cout << "Nombre: ";
            getline(cin, linea);
            strcpy(modelo.telefono, linea.c_str());
         }
         else if (cambioPropiedad == 2)
         {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            std::cout << "Telefono: ";
            getline(cin, linea);
            strcpy(modelo.telefono, linea.c_str());
         }

      } while (cambioPropiedad != 3);
      if (archivo.fail())
      {
         cerr << "No se pudo abrir el archivo para escritura.\n";
         system("pause");
         return;
      }
      else
      {
         archivo.seekg(auxPosicionProveedor * sizeof(Proveedor));
         archivo.write((char *)&modelo, sizeof(Proveedor));
         archivo.close();
      }
   }

   void eliminarRegistro()
   {
      int auxId = 0;
      Proveedor modelo;
      Proveedor reemplazo;
      fstream archivoOriginal("database/Proveedor.bin", ios::out | ios::in | ios::binary);
      fstream archivoTemporal("database/ProveedorTemp.bin", ios::out);
      archivoTemporal.close();
      archivoTemporal.open("database/ProveedorTemp.bin", ios::in | ios::out | ios::binary);
      std::cout << "Por favor introduzca el ID del proveedor:" << '\n';
      auxId = helper.validarIntSinLimite();
      modelo = getProveedor(auxId);
      if (modelo.id == -1)
      {
         std::cout << "No existe un proveedor con el ID especificado" << '\n';
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
      while (archivoOriginal.read((char *)&reemplazo, sizeof(Proveedor)))
      {
         if (reemplazo.id != modelo.id)
         {
            archivoTemporal.write((char *)&reemplazo, sizeof(Proveedor));
         }
      }

      archivoOriginal.close();
      archivoTemporal.close();

      remove("database/Proveedor.bin");
      rename("database/ProveedorTemp.bin", "database/Proveedor.bin");
   }
};