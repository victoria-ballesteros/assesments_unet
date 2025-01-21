#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <cstring>

class linkedList
{

public:
    struct Nodo
    {
        int semestre;
        Nodo *sig;
        Nodo *first;
    };

    void newNodo(Nodo *&puntoAcceso, int i);
    void backtToStart(Nodo *&puntoAcceso);
};

#endif