#include "cdllSemester.h"

void cdllSemester::newNodo(Materia *&acceso, char *_nombre, int _uc, char *_codigo)
{
    Materia *nuevo_nodo = new Materia();
    strncpy(nuevo_nodo->nombre, _nombre, sizeof(nuevo_nodo->nombre) - 1);
    nuevo_nodo->nombre[sizeof(nuevo_nodo->nombre) - 1] = '\0';
    strncpy(nuevo_nodo->info.codigo, _codigo, sizeof(nuevo_nodo->info.codigo) - 1);
    nuevo_nodo->info.codigo[sizeof(nuevo_nodo->info.codigo) - 1] = '\0';
    nuevo_nodo->info.uc = _uc;

    if (acceso == nullptr)
    {
        acceso = nuevo_nodo;
        acceso->sig = acceso;
        acceso->ant = acceso;
    }
    else
    {
        nuevo_nodo->sig = acceso;
        nuevo_nodo->ant = acceso->ant;
        nuevo_nodo->ant->sig = nuevo_nodo;
        acceso->ant = nuevo_nodo;
        acceso = nuevo_nodo;
    }
}

void cdllSemester::printAll(Materia *acceso)
{
    Materia *actual = acceso;
    do
    {
        std::cout << actual->nombre << "\n";
        actual = actual->sig;
    } while (actual != acceso);
}

void cdllSemester::deleteNodo(Materia *&acceso)
{
    if (acceso == nullptr)
    {
        return;
    }

    if (acceso->sig == acceso)
    {
        delete acceso;
        acceso = nullptr;
    }
    else
    {
        Materia *auxiliar = acceso;
        acceso = acceso->ant;
        acceso->sig = auxiliar->sig;
        auxiliar->sig->ant = acceso;
        delete auxiliar;
    }
}

void cdllSemester::save(Materia *&acceso, const char *nombre_archivo)
{
    Saved *auxiliar = new Saved();
    binaryFiles file;
    strncpy(auxiliar->nombre, acceso->nombre, sizeof(auxiliar->nombre) - 1);
    auxiliar->nombre[sizeof(auxiliar->nombre) - 1] = '\0';
    auxiliar->info.uc = acceso->info.uc;
    strncpy(auxiliar->info.codigo, acceso->info.codigo, sizeof(auxiliar->info.codigo) - 1);
    auxiliar->info.codigo[sizeof(auxiliar->info.codigo) - 1] = '\0';
    for (int i = 0; i < acceso->info.uc; i++)
    {
        strcpy(auxiliar->info.vectorUc[i], acceso->info.vectorUc[i]);
    }
    file.save(nombre_archivo, auxiliar, sizeof(Saved));
}

void cdllSemester::read(Materia *&acceso, const char *nombre_archivo)
{
    binaryFiles file;
    Saved auxiliar;
    int size = static_cast<int>(file.getSize(nombre_archivo, sizeof(Saved)));
    if (file.isEmpty(nombre_archivo))
    {
        return;
    }

    for (int i = 0; i < size; i++)
    {
        file.read(nombre_archivo, sizeof(Saved), i, &auxiliar);
        newNodo(acceso, auxiliar.nombre, auxiliar.info.uc, auxiliar.info.codigo);
        for (int a = 0; a < auxiliar.info.uc; a++)
        {
            strcpy(acceso->info.vectorUc[a], auxiliar.info.vectorUc[a]);
        }
        strcpy(acceso->info.codigo, auxiliar.info.codigo);
    }
}

void cdllSemester::deleteNodoinFile(Materia *&acceso, const char *nombre_archivo)
{
    binaryFiles file;
    Saved auxiliar;
    int indice = 0;
    int size = static_cast<int>(file.getSize(nombre_archivo, sizeof(Saved)));
    if (file.isEmpty(nombre_archivo))
    {
        return;
    }
    for (int i = 0; i < size; i++)
    {
        file.read(nombre_archivo, sizeof(Saved), i, &auxiliar);
        if (auxiliar.info.codigo == acceso->info.codigo)
        {
            indice = i;
            break;
        }
    }
    file.deleteInFile(nombre_archivo, sizeof(Saved), indice);
}
