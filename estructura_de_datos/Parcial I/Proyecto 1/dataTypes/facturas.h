#include <iostream>
#include <stdlib.h>
#include <limits>
#include <locale.h>
#include <fstream>
#include <cstring>
#include "registro.h"

class facturas : public registro
{

public:
   void listarFacturas()
   {
      std::fstream archivo("database/Factura.bin", std::ios::binary | std::ios::in | std::ios::out);
      if (archivo.fail())
      {
         cerr << "No se pudo abrir el archivo.\n";
         system("pause");
         return;
      }
      Factura factura;
      while (archivo.read((char *)&factura, sizeof(Factura)))
      {
         std::cout << "" << '\n';
         std::cout << "ID--------------------: " << factura.id << "\n";
         std::cout << "FECHA-----------------: " << factura.fecha << "\n";
         std::cout << "CLIENTE---------------: " << factura.id_cliente << "\n";
         std::cout << "____________________________________________________________" << '\n';
         std::cout << '\n';
      }
      archivo.close();
   }

   void imprimirFactura(Factura factura)
   {
      std::cout << "ID--------------: " << factura.id << '\n';
      std::cout << "FECHA-----------: " << factura.fecha << "\n";
      std::cout << "CLIENTE---------: " << factura.id_cliente << "\n";
      std::cout << "____________________________________________________________" << '\n';
      std::cout << '\n';
   }

   void registrarFactura()
   {
      int auxId = 0, generadorId = 0;
      string linea = "";
      Factura modelo;
      ofstream archivo("database/Factura.bin", ios::app | ios::binary);
      std::cout << "\nPor favor introduzca el ID de la factura: ";
      auxId = helper.validarIntSinLimite();
      modelo = getFactura(auxId);

      if (modelo.id != -1)
      {
         std::cout << "\nYa existe una factura con el ID especificado\n\n";
         system("pause");
         return;
      }
      system("cls");
      std::cout << "***** Registro de Nueva Factura *****\n\n";
      std::cout << "Por favor introduzca la informacion solicitada a continuacion:\n\n";
      modelo.id = auxId;
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      std::cout << "Id del cliente: ";
      modelo.id_cliente = helper.validarIntSinLimite();

      if (archivo.fail())
      {
         cerr << "\nNo se pudo abrir el archivo para escritura.\n\n";
         system("pause");
         return;
      }
      else
      {
         archivo.write((char *)&modelo, sizeof(Factura));
         archivo.close();
      }

      cout << "\nFactura creada exitosamente\n\n";
      system("pause");
   }

   void modificarFactura()
   {
      string linea = "";
      Factura modelo;
      int auxId = 0, generadorId = 0, cambioPropiedad = 0;
      int aux_id_cliente = 0;
      Cliente modeloCliente;
      fstream archivo("database/Factura.bin", ios::out | ios::in | ios::binary);
      std::cout << "Por favor introduzca el ID de la factura: ";
      auxId = helper.validarIntSinLimite();
      modelo = getFactura(auxId);
      if (modelo.id == -1)
      {
         std::cout << "\nNo existe una factura con el ID especificado\n\n";
         system("pause");
         return;
      }
      do
      {
         system("cls");
         std::cout << "***** Modificacion de Factura *****\n\n";
         imprimirFactura(modelo);
         std::cout << "1. ID del cliente asociado" << '\n';
         std::cout << "2. Salir" << '\n';
         std::cout << "\nSeleccione la opcion que desee cambiar: ";
         cambioPropiedad = helper.validarInt(2);

         if (cambioPropiedad == 1)
         {
            std::cout << "\nId del cliente asociado: ";
            aux_id_cliente = helper.validarIntSinLimite();
            modeloCliente = getCliente(aux_id_cliente);

            if (modeloCliente.id == -1)
            {
               system("cls");
               std::cout << "\nEl cliente indicado no existe en la base de datos, por favor, registrelo.\n\n";
               system("pause");
            }
            else
            {
               modelo.id_cliente = aux_id_cliente;
               std::cout << "\nFactura modificada exitosamente.";
            }
         }
         
      } while (cambioPropiedad != 2);
      
      if (archivo.fail())
      {
         system("cls");
         cerr << "No se pudo abrir el archivo para escritura.\n";
         system("pause");
         return;
      }
      else
      {
         archivo.seekg(auxPosicionFactura * sizeof(Factura));
         archivo.write((char *)&modelo, sizeof(Factura));
         archivo.close();
      }
   }

   int eliminarRegistro()
   {
      int auxId = 0;
      Factura modelo;
      Factura reemplazo;
      Compra modeloCompra;
      fstream archivoOriginal("database/Factura.bin", ios::out | ios::in | ios::binary);
      fstream archivoTemporal("database/FacturaTemp.bin", ios::out);
      archivoTemporal.close();
      archivoTemporal.open("database/FacturaTemp.bin", ios::in | ios::out | ios::binary);
      system("cls");
      std::cout << "***** Eliminar Factura *****\n\n";
      std::cout << "Por favor introduzca el ID de la factura: ";
      auxId = helper.validarIntSinLimite();
      modelo = getFactura(auxId);
      if (modelo.id == -1)
      {
         system("cls");
         std::cout << "\nNo existe una factura con el ID especificado\n\n";
         system("pause");
         return -1;
      }
      if (archivoOriginal.fail())
      {
         system("cls");
         cout << "\nNo se pudo abrir el archivo original.\n\n";
         system("pause");
         return -1;
      }
      if (archivoTemporal.fail())
      {
         system("cls");
         cout << "\nNo se pudo abrir el archivo temporal.\n\n";
         system("pause");
         return -1;
      }
      while (archivoOriginal.read((char *)&reemplazo, sizeof(Factura)))
      {
         if (reemplazo.id != modelo.id)
         {
            archivoTemporal.write((char *)&reemplazo, sizeof(Factura));
         }
      }

      archivoOriginal.close();
      archivoTemporal.close();
      remove("database/Factura.bin");
      rename("database/FacturaTemp.bin", "database/Factura.bin");
      cout << "\nFactura eliminada exitosamente.\n\n";
      system("pause");
      return auxId;
   }

   void registrarFacturaDirecta(Factura factura)
   {
      ofstream archivo("database/Factura.bin", ios::app | ios::binary);
      if (archivo.fail())
      {
         cerr << "No se pudo abrir el archivo para escritura.\n";
         system("pause");
         return;
      }
      else
      {
         archivo.write((char *)&factura, sizeof(Factura));
         archivo.close();
      }
   }
};