#include <iostream>
#include <stdlib.h>
#include <limits>
#include <locale.h>
#include <fstream>
#include <cstring>
#include "registro.h"

class clientes : public registro
{

public:
#include <fstream>
#include <iostream>

   void listarClientes()
   {
      std::fstream archivo("database/Cliente.bin", std::ios::binary | std::ios::in | std::ios::out);
      if (archivo.fail())
      {
         std::cerr << "No se pudo abrir el archivo.\n";
         system("pause");
         return;
      }
      Cliente cliente;
      while (archivo.read((char *)&cliente, sizeof(Cliente)))
      {
         std::cout << "\n";
         std::cout << "ID--------------------: " << cliente.id << "\n";
         std::cout << "NOMBRE----------------: " << cliente.nombre << "\n";
         std::cout << "__________________________________________________\n";
      }
      archivo.close();
   }

   void imprimirCliente(Cliente cliente)
   {
      std::cout << "ID--------------: " << cliente.id << "\n";
      std::cout << "Nombre----------: " << cliente.nombre << "\n";
      std::cout << "Direccion-------: " << cliente.direccion << "\n";
      std::cout << "Telefono--------: " << cliente.telefono << "\n";
      std::cout << "____________________________________________________________"
                << "\n";
      std::cout << "\n";
   }

   void registrarCliente()
   {
      int auxId = 0, generadorId = 0;
      string linea = "";
      Cliente modelo;
      ofstream archivo("database/Cliente.bin", ios::app | ios::binary);
      std::cout << "\n***** Datos del cliente *****\n";
      std::cout << "\nIntroduzca el ID del cliente: ";
      auxId = helper.validarIntSinLimite();
      modelo = getCliente(auxId);
      if (modelo.id != -1)
      {
         system("cls");
         std::cout << "\nYa existe un cliente con el ID especificado\n\n";
         system("pause");
         return;
      }
      modelo.id = auxId;
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      std::cout << "Nombre: ";
      getline(cin, linea);
      strcpy(modelo.nombre, linea.c_str());
      std::cout << "Direccion: ";
      getline(cin, linea);
      strcpy(modelo.direccion, linea.c_str());
      std::cout << "Telefono: ";
      getline(cin, linea);
      strcpy(modelo.telefono, linea.c_str());

      if (archivo.fail())
      {
         cerr << "No se pudo abrir el archivo.\n";
         system("pause");
         return;
      }
      else
      {
         archivo.write((char *)&modelo, sizeof(Cliente));
         archivo.close();
      }
   }

   void modificarCliente()
   {
      string linea = "";
      Cliente modelo;
      int auxId = 0, generadorId = 0, cambioPropiedad = 0;
      fstream archivo("database/Cliente.bin", ios::out | ios::in | ios::binary);
      std::cout << "\n***** Datos del cliente *****\n";
      std::cout << "\nIntroduzca el ID del cliente: ";
      auxId = helper.validarIntSinLimite();
      modelo = getCliente(auxId);

      if (modelo.id == -1)
      {
         system("cls");
         std::cout << "No existe un cliente con el ID especificado\n\n";
         system("pause");
         return;
      }
      do
      {
         system("cls");
         cout << "***** Datos cliente *****\n\n";
         imprimirCliente(modelo);
         std::cout << "Seleccione la opcion que desee cambiar:\n\n";
         std::cout << "1. Nombre\n";
         std::cout << "2. Direccion\n";
         std::cout << "3. Telefono\n";
         std::cout << "4. Salir\n\n";
         std::cout << "Respuesta: ";
         cambioPropiedad = helper.validarInt(4);
         std::cout << ""
                   << "\n";

         if (cambioPropiedad == 1)
         {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            std::cout << "Nombre: ";
            getline(cin, linea);
            strcpy(modelo.nombre, linea.c_str());
            cout << "\nNombre cambiado exitosamente a "<<modelo.nombre<<"\n\n";
            system("pause");
         }
         else if (cambioPropiedad == 2)
         {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            std::cout << "Direccion: ";
            getline(cin, linea);
            strcpy(modelo.direccion, linea.c_str());
            cout << "\nDireccion cambiada exitosamente a "<<modelo.direccion<<"\n\n";
            system("pause");
         }
         else if (cambioPropiedad == 3)
         {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            std::cout << "Telefono: ";
            getline(cin, linea);
            strcpy(modelo.telefono, linea.c_str());
            cout << "\nTelefono cambiado exitosamente a "<<modelo.telefono<<"\n\n";
            system("pause");
         }

      } while (cambioPropiedad != 4);

      if (archivo.fail())
      {
         cerr << "No se pudo abrir el archivo.\n";
         system("pause");
      }
      else
      {
         archivo.seekg(auxPosicionCliente * sizeof(Cliente));
         archivo.write((char *)&modelo, sizeof(Cliente));
         archivo.close();
      }
   }

   void eliminarRegistro()
   {
      int auxId = 0;
      Cliente modelo;
      Cliente reemplazo;
      fstream archivoOriginal("database/Cliente.bin", ios::out | ios::in | ios::binary);
      fstream archivoTemporal("database/ClienteTemp.bin", ios::out);
      archivoTemporal.close();
      archivoTemporal.open("database/ClienteTemp.bin", ios::in | ios::out | ios::binary);
      std::cout << "\nPor favor introduzca el ID del cliente: ";
      auxId = helper.validarIntSinLimite();
      modelo = getCliente(auxId);

      if (modelo.id == -1)
      {
         system("cls");
         std::cout << "\nNo existe un cliente con el ID especificado\n\n";
         system("pause");
         return;
      }
      if (archivoOriginal.fail())
      {
         system("cls");
         cerr << "\nNo se pudo abrir el archivo original.\n\n";
         system("pause");
         return;
      }
      if (archivoTemporal.fail())
      {
         system("cls");
         cerr << "\nNo se pudo abrir el archivo temporal.\n\n";
         system("pause");
         return;
      }
      while (archivoOriginal.read((char *)&reemplazo, sizeof(Cliente)))
      {
         if (reemplazo.id != modelo.id)
         {
            archivoTemporal.write((char *)&reemplazo, sizeof(Cliente));
         }
      }

      archivoOriginal.close();
      archivoTemporal.close();

      remove("database/Cliente.bin");
      rename("database/ClienteTemp.bin", "database/Cliente.bin");
      std::cout << "\nEliminado exitosamente el cliente " << modelo.nombre << "." << '\n';
      system("pause");
   }

   void registroDirecto(int _id)
   {
      string linea = "";
      Cliente modelo;
      ofstream archivo("database/Cliente.bin", ios::app | ios::binary);
      modelo.id = _id;
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      std::cout << "Nombre: ";
      getline(cin, linea);
      strcpy(modelo.nombre, linea.c_str());
      std::cout << "Direccion: ";
      getline(cin, linea);
      strcpy(modelo.direccion, linea.c_str());
      std::cout << "Telefono: ";
      getline(cin, linea);
      strcpy(modelo.telefono, linea.c_str());

      if (archivo.fail())
      {
         cerr << "No se pudo abrir el archivo.\n";
         system("pause");
         return;
      }
      else
      {
         archivo.write((char *)&modelo, sizeof(Cliente));
         archivo.close();
      }
   }
};