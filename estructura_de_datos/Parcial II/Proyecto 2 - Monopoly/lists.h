#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <cstring>
#include <windows.h>
#include <fstream>

class lists
{

public:
    struct Nodo
    {
        int price;
        COORD position;
        int color;
        char name[45];
        bool isHere[4];
        bool houseHere[4];
        Nodo *sig;
        Nodo *ant;
    };
    
    struct Binario
	{
    	int price;
        COORD position;
        char name[45];
        int color;
	};

lists();
void newNodo(Nodo *&acceso, int _price, COORD _position, char* _name, int _color);
void read(const char *nombreArchivo, int indice, Binario* datos);
void readLoop(Nodo *&acceso, const char *nombre_archivo);
size_t getSize(const char *nombreArchivo);
bool isEmpty(const char* nombreArchivo);
void printAll(Nodo *acceso);
void guardarTodo();
void modificarPrecio();
};

#endif
