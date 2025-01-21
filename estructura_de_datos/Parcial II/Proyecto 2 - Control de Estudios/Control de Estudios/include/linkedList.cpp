#include "linkedList.h"

void linkedList::newNodo(Nodo *&puntoAcceso, int i)
{
    Nodo *nuevoNodo = new Nodo();
    nuevoNodo->semestre = i;
    nuevoNodo->sig = nullptr;

    if (puntoAcceso == nullptr)
    {
        puntoAcceso = nuevoNodo;
        puntoAcceso->first = puntoAcceso;
    }
    else
    {
        Nodo *actual = puntoAcceso;
        while (actual->sig != nullptr)
        {
            actual = actual->sig;
        }
        nuevoNodo->first = puntoAcceso->first;
        actual->sig = nuevoNodo;
    }
}

void linkedList::backtToStart(Nodo *&puntoAcceso)
{
    if (puntoAcceso != nullptr)
    {
        puntoAcceso = puntoAcceso->first;
    }
}