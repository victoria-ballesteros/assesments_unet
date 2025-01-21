#ifndef CDLLSEMESTER_H
#define CDLLSEMESTER_H

#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <cstring>
#include <vector>
#include "binaryFiles.h"

class cdllSemester
{
public:
    struct Atributos
    {
        int uc;
        char codigo[9];
        char vectorUc[4][40];
        Atributos() : uc(0)
        {
            for (int i = 0; i < 4; ++i)
            {
                vectorUc[i][0] = '\0';
            }
            codigo[0] = '\0';
        }
    };

    struct Materia
    {
        char nombre[40];
        Atributos info;
        Materia *sig;
        Materia *ant;
        Materia() : info() {}
    };

    struct Saved
    {
        char nombre[40];
        Atributos info;
        Saved() : info() {}
    };

public:
    void newNodo(Materia *&acceso, char *_nombre, int _uc, char *_codigo);
    void printAll(Materia *acceso);
    void deleteNodo(Materia *&acceso);
    void save(Materia *&acceso, const char *nombre_archivo);
    void read(Materia *&acceso, const char *nombre_archivo);
    void deleteNodoinFile(Materia *&acceso, const char *nombre_archivo);
};

#endif