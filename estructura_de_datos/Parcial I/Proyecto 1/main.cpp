#include <iostream>
#include <stdlib.h>
#include <limits>
#include <fstream>
#include <cstring>
#include <random>
#include <ctime>
#include <windows.h>
#include "helpers.h"
#include "dataTypes\dataTypes.h"

registro registros;
clientes cliente;
compras compra;
facturas factura;
productos producto;
proveedores proveedor;
std::vector<int> reponerStock_cantidad;
std::vector<int> reponerStock_id;

long key[4] = {11235, 81321, 34558, 0};
int eleccionMenu = 0, keyNumber = 0, terminarEjecucion = 0;
bool aprobarAlmacen = false;
std::string directorio = "";

random_device rd;
mt19937 gen(rd());

void generarFechaActual(facturas::Factura &factura);
void agregarRegistro(int eleccionMenu);
void modificarRegistro(int eleccionMenu);
void eliminarRegistro(int eleccionMenu);
void mecanismoCaja();
void mecanismoAlmacen();
int subMenuAdministrador();
int generarRandom();
int validarClave();
void menu(int clave);


bool compararStock(const productos::Producto& a, const productos::Producto& b) {
    return a.stock < b.stock;
}


void ordenamiento(std::vector<productos::Producto>& productos){
   int n = productos.size();
   for (int i = 0; i < n-1; i++) {
      for (int j = 0; j < n-i-1; j++) {
         if (compararStock(productos[j+1], productos[j])) {
               std::swap(productos[j], productos[j+1]);
         }
      }
   }
}

int main()
{
   /*HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
   SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);*/
   do
   {
      std::cout << "\033[38;5;213m";
      keyNumber = validarClave();
      menu(keyNumber);
      system("cls");
      if (aprobarAlmacen == true)
      {
         menu(0);
      }
      else
      {
         std::cout << "***INDIQUE SI DESEA INTRODUCIR UNA CLAVE DIFERENTE***" << '\n';
         std::cout << "1. Si" << '\n';
         std::cout << "2. No" << '\n';
         terminarEjecucion = helper.validarInt(2);
      }
   } while (terminarEjecucion != 2);
   std::ifstream archivoBinario("database/Producto.bin", std::ios::binary);
   std::vector<productos::Producto> productos;
   std::vector<productos::Producto> productosAgotados;
   std::vector<productos::ProductosAgotados> impresionProductos;
   productos::Producto producto;
   productos::ProductosAgotados auxImpresion;
   while (archivoBinario.read(reinterpret_cast<char*>(&producto), sizeof(productos::Producto))) {
      productos.push_back(producto);
   }
   archivoBinario.close();
   ordenamiento(productos);
   for (int i = 0; i < productos.size(); i++) {
      if(productos[i].stock < productos[i].stock_min){
         productosAgotados.push_back(productos[i]);
         auxImpresion.stock = productos[i].stock;
         auxImpresion.stock_min = productos[i].stock_min;
         auxImpresion.id_proveedor = productos[i].id_proveedor;
         impresionProductos.push_back(auxImpresion);
      }
   }
   std::ofstream archivoTexto("database/reposicionesAlmacen.txt");
   for (const auto& producto : impresionProductos) {
      archivoTexto << "ID DEL PROVEEDOR: " << producto.id_proveedor << ", CANTIDAD ACTUAL EN STOCK: "<< producto.stock << ", CANTIDAD MINIMA DE STOCK: "<< producto.stock_min << '\n';
      std::cout << "ID DEL PROVEEDOR: " << producto.id_proveedor << ", CANTIDAD ACTUAL EN STOCK: "<< producto.stock << ", CANTIDAD MINIMA DE STOCK: "<< producto.stock_min << '\n';
   }
   archivoTexto.close();
   std:cout << "\nEl archivo de texto con las indicaciones de reposiciones de productos ha sido actualizado correctamente\n";
   system("pause");
   system("cls");
   return 0;
}



long helpers::validarLong()
{
   long numero = 0;
   while (!(cin >> numero))
   {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      std::cout << "Entrada invalida. Por favor, ingresa un numero: ";
   }
   return numero;
}

int helpers::validarInt(int maximo)
{
   int numero;
   do
   {
      while (!(cin >> numero))
      {
         cin.clear();
         cin.ignore(numeric_limits<streamsize>::max(), '\n');
         std::cout << "Entrada invalida. Por favor, ingresa un numero: ";
      }
   } while (numero <= 0 || numero > maximo);
   return numero;
}

int helpers::validarIntSinLimite()
{
   int numero;
   while (!(cin >> numero))
   {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      std::cout << "Entrada invalida. Por favor, ingresa un numero: ";
   }
   return numero;
}

float helpers::validarFloat()
{
   float numero = 0.0;
   while (!(std::cin >> numero))
   {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Entrada invalida. Por favor, ingresa un numero (punto para la coma flotante): ";
   }
   return numero;
}

void generarFechaActual(facturas::Factura &factura)
{
   time_t time = std::time(0);
   std::tm *now = std::localtime(&time);
   std::strftime(factura.fecha, sizeof(factura.fecha), "%d-%m-%Y", now);
}

int generarRandom()
{
   uniform_int_distribution<> distrib(10, 99);
   int numeroAleatorio = distrib(gen);
   return numeroAleatorio;
}

int validarClave()
{
   int i = 0, puesto = 0;
   bool flag = false;
   long claveIntroducida = 0;

   do
   {
      system("cls");
      std::cout << "Introduzca una clave de acceso: ";
      claveIntroducida = helper.validarLong();
      for (i = 0; i < 3; i++)
      {
         if (key[i] == claveIntroducida)
         {
            flag = true;
            puesto = i;
            break;
         }
      }
      if (flag == false)
      {
         std::cout << "La clave de acceso introducida no es valida." << '\n';
         system("pause");
      }
   } while (flag != true);
   return puesto;
}

void agregarRegistro(int eleccionMenu)
{
   switch (eleccionMenu)
   {
   case 1:
      cliente.registrarCliente();
      break;
   case 2:
      compra.registrarCompra();
      break;
   case 3:
      factura.registrarFactura();
      break;
   case 4:
      producto.registrarProducto();
      break;
   case 5:
      proveedor.registrarProveedor();
      break;
   default:
      break;
   }
}

void modificarRegistro(int eleccionMenu)
{

   switch (eleccionMenu)
   {
   case 1:
      cliente.modificarCliente();
      break;
   case 2:
      compra.modificarCompra();
      break;
   case 3:
      factura.modificarFactura();
      break;
   case 4:
      producto.modificarProducto("database/Producto.bin");
      break;
   case 5:
      proveedor.modificarProveedor();
      break;
   default:
      break;
   }
}

void eliminarRegistro(int eleccionMenu)
{

   switch (eleccionMenu)
   {
   case 1:
      cliente.eliminarRegistro();
      break;
   case 2:
      compra.eliminarRegistro();
      break;
   case 3:
      compra.eliminarComprasPorFactura(factura.eliminarRegistro(), reponerStock_id, reponerStock_cantidad);
      producto.modificacionesStock(reponerStock_id, reponerStock_cantidad);
      break;
   case 4:
      producto.eliminarRegistro();
      break;
   case 5:
      proveedor.eliminarRegistro();
      break;
   default:
      break;
   }
}

int subMenuAdministrador()
{
   int seleccion = 0;
   std::cout << "1. Agregar Registro" << '\n';
   std::cout << "2. Editar Registro" << '\n';
   std::cout << "3. Eliminar Registro" << '\n';
   std::cout << "4. Seleccionar otro tipo de Registro" << '\n';
   std::cout << "\nPor favor seleccione una opcion: ";
   seleccion = helper.validarInt(4);
   return seleccion;
}

void mecanismoCaja()
{
   long auxId = 0, continuarCompra = 0;
   int id_factura = 0, id_compra = 0;
   bool flagIds = false;
   clientes::Cliente modelo;
   facturas::Factura modeloFactura;
   compras::Compra modeloCompra;
   cin.ignore(numeric_limits<streamsize>::max(), '\n');
   std::cout << "Por favor introduzca el ID del cliente: ";
   auxId = helper.validarLong();
   modelo = cliente.getCliente(auxId);

   if (modelo.id == -1)
   {
      std::cout << "Por favor registre al cliente" << '\n';
      cliente.registroDirecto(auxId);
   }
   else
   {
      system("cls");
      std::cout << "EL cliente ya existe en la base de datos:" << '\n';
      std::cout << "" << '\n';
      cliente.imprimirCliente(modelo);
   }
   std::cout << "" << '\n';
   std::cout << "COMPRA:" << '\n';
   do
   {
      id_factura = generarRandom();
      modeloFactura = factura.getFactura(id_factura);
      if (modeloFactura.id == -1)
      {
         flagIds = true;
      }
   } while (flagIds == false);
   flagIds = false;
   do
   {
      do
      {
         id_compra = generarRandom();
         modeloCompra = compra.getCompra(id_compra);
         if (modeloCompra.id == -1)
         {
            flagIds = true;
         }
      } while (flagIds == false);
      flagIds = false;
      compra.registrarCompraCaja(id_factura, id_compra);
      std::cout << "iIndique si hay otro producto por registrar:" << '\n';
      std::cout << "1. Si" << '\n';
      std::cout << "2. No" << '\n';
      continuarCompra = helper.validarInt(2);
   } while (continuarCompra != 2);
   std::cout << "" << '\n';
   modeloFactura.id = id_factura;
   modeloFactura.id_cliente = modelo.id;
   generarFechaActual(modeloFactura);
   factura.registrarFacturaDirecta(modeloFactura);
   std::cout << "" << '\n';
   factura.imprimirFactura(modeloFactura);
   std::cout << "PRODUCTOS FACTURADOS" << '\n';
   compra.listarComprasUnicas(id_factura);
   std::cout << "" << '\n';
}

void mecanismoAlmacen()
{
   string dir = "";
   int aux_id = 0, finJornada = 0;
   bool dirAproval = true;
   productos::Producto modelo;
   cin.ignore(numeric_limits<streamsize>::max(), '\n');
   do
   {
      dirAproval = true;
      std::cout << "Por favor introduzca el nombre del archivo de texto con el cual va a trabajar: ";
      getline(cin, dir);
      if (dir == "Producto" || dir == "ProductoTemp")
      {
         std::cout << "Su archivo no puede tener el nombre indicado" << '\n';
         dirAproval == false;
      }
   } while (dir == "Producto" || dir == "ProductoTemp");
   producto.escribirNuevoArchivo(dir);
   std::cout << "__________________________________" << '\n';
   producto.listarProductos("database/" + dir + ".bin");
   directorio = "database/" + dir + ".bin";

   do
   {
      do
      {
         std::cout << "Por favor indique el ID del producto que desea modificar: ";
         aux_id = helper.validarIntSinLimite();
         modelo = producto.getProducto(aux_id);
         if (modelo.id == -1)
         {
            std::cout << "El ID indicado no corresponde a ningun producto" << '\n';
         }
      } while (modelo.id == -1);
      producto.modificacionesAlmacen("database/" + dir + ".bin", aux_id);
      std::cout << "Fin de jornada?:" << '\n';
      std::cout << "1. Si" << '\n';
      std::cout << "2. No" << '\n';
      finJornada = helper.validarInt(2);
   } while (finJornada == 2);
   std::cout << "Su archivo será aprobado o desechado por un administrador" << '\n';
   aprobarAlmacen = true;
   system("pause");
}

void menu(int clave)
{
   int contOpciones = 6;
   int eleccionOpcion = 0, opcionesCaja = 0, aprobarCambio = 0;
   switch (clave)
   {
   case 0: //  administrador
      do
      {
         system("cls");
         if (aprobarAlmacen == true)
         {
            std::cout << "POR FAVOR ACCEDA A LA OPCION 6" << '\n';
         }
         std::cout <<"***** Menu de Administrador *****\n\n"; 
         std::cout << "1. Cliente" << '\n';
         std::cout << "2. Compra" << '\n';
         std::cout << "3. Factura" << '\n';
         std::cout << "4. Producto" << '\n';
         std::cout << "5. Proveedor" << '\n';
         if (aprobarAlmacen)
         {
            std::cout << "6. Aprobar ediciones de almacen" << '\n';
            contOpciones++;
         }
         std::cout << contOpciones << ". Volver" << '\n';
         std::cout << "\nPor favor seleccione una opcion: ";
         if(aprobarAlmacen){
            eleccionMenu = 6;
         }else{
            eleccionMenu = helper.validarInt(6);
         }
         if (eleccionMenu == 1)
         {
            system("cls");
            std::cout << "" << '\n';
            std::cout << "CLIENTES REGISTRADOS" << '\n';
            cliente.listarClientes();
            std::cout << "" << '\n';
         }
         else if (eleccionMenu == 2)
         {
            system("cls");
            std::cout << "" << '\n';
            std::cout << "COMPRAS REGISTRADAS" << '\n';
            compra.listarCompras();
            std::cout << "" << '\n';
         }
         else if (eleccionMenu == 3)
         {
            system("cls");
            std::cout << "" << '\n';
            std::cout << "FACTURAS REGISTRADAS" << '\n';
            factura.listarFacturas();
            std::cout << "" << '\n';
         }
         else if (eleccionMenu == 4)
         {
            system("cls");
            std::cout << "" << '\n';
            std::cout << "PRODUCTOS REGISTRADOS" << '\n';
            producto.listarProductos("database/Producto.bin");
            std::cout << "" << '\n';
         }
         else if (eleccionMenu == 5)
         {
            system("cls");
            std::cout << "" << '\n';
            std::cout << "PROVEEDORES REGISTRADOS" << '\n';
            proveedor.listarProveedores();
            std::cout << "" << '\n';
         }
         else if (eleccionMenu == 6)
         {
            if (aprobarAlmacen)
            {
               system("cls");
               cout << "ARCHIVO DE ALMACEN" << '\n';
               producto.listarProductos(directorio);
               system("pause");
               cout << "Indique si desea guardar los cambios: " << '\n';
               std::cout << "1. Si" << '\n';
               std::cout << "2. No" << '\n';
               aprobarAlmacen = false;
               aprobarCambio = helper.validarIntSinLimite();
               if (aprobarCambio == 1)
               {
                  remove("database/Producto.bin");
                  if (rename(directorio.c_str(), "database/Producto.bin") != 0)
                  {
                     perror("Error al renombrar el archivo");
                  }
               }
               aprobarAlmacen = false;
               return;
            }else{
               return;
            }
         }
         else if (eleccionMenu == 7)
         {
            return;
         }

         eleccionOpcion = subMenuAdministrador();

         switch (eleccionOpcion)
         {
         case 1:
            agregarRegistro(eleccionMenu);
            break;

         case 2:
            modificarRegistro(eleccionMenu);
            break;

         case 3:
            eliminarRegistro(eleccionMenu);
            break;
         default:
            break;
         }

      } while (eleccionMenu != 7);
      break;
   case 1: //  almacén
      std::cout << "" << '\n';
      std::cout << "APERTURA DE ALMACEN" << '\n';
      std::cout << "" << '\n';
      mecanismoAlmacen();
      break;
   case 2: //  vendedor
      std::cout << "" << '\n';
      std::cout << "APERTURA DE CAJA" << '\n';
      std::cout << "" << '\n';
      do
      {
         mecanismoCaja();
         std::cout << "Por favor indique si ya es momento de cerrar caja:" << '\n';
         std::cout << "1. Si" << '\n';
         std::cout << "2. No" << '\n';
         opcionesCaja = helper.validarInt(2);
         system("cls");
      } while (opcionesCaja != 1);
      std::cout << "JORNADA FINALIZADA";
      break;
   default:
      break;
   }
}
