#include "helpers.h"

long helpers::validarLong(){
   long numero = 0;
      while(!(cin >> numero)) {
         cin.clear();
         cin.ignore(numeric_limits<streamsize>::max(), '\n');
         cout << "Entrada inválida. Por favor, ingresa un número: ";
      }
      return numero;
 }

 int helpers::validarInt(int maximo){
   int numero;
   do{
      while(!(cin >> numero)) {
         cin.clear();
         cin.ignore(numeric_limits<streamsize>::max(), '\n');
         cout << "Entrada inválida. Por favor, ingresa un número: ";
      }
   }while(numero <= 0 || numero > maximo);
   return numero;
 }

 int helpers::validarIntSinLimite(){
   int numero;
      while(!(cin >> numero)) {
         cin.clear();
         cin.ignore(numeric_limits<streamsize>::max(), '\n');
         cout << "Entrada inválida. Por favor, ingresa un número: ";
      }
   return numero;
 }

 float validarFloat(){
   float numero = 0.0;
   while (!(std::cin >> numero))
   {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Entrada invalida. Por favor, ingresa un numero (punto para la coma flotante): ";
   }
   return numero;
 }
