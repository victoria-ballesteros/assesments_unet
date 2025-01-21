#include <iostream>
#include <windows.h>
#include <limits>
#include <cstdio>
#include "../include/Include.h"

void mecanismoSemestral(const char *_archivo);
void imprimirEnPosicion(COORD posicion, const char *texto);
void imprimirNodo(cdllSemester::Materia *acceso);
int validarEntrada(int minimo, int maximo);
void manejarIzquierda(cdllSemester::Materia *&acceso);
void printArrows();
void printTitle();
void printTitleOption(int i);
bool vacio = false, esperandoEntradaMenu = false, vuelta = false;
HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);

int main()
{
    COORD posicionEspecifica;
    linkedList list;
    char menu;
    linkedList::Nodo *puntoAcceso = nullptr;
    for (int a = 1; a < 11; a++)
    {
        list.newNodo(puntoAcceso, a);
    }
    do
    {
        system("cls");


        printTitleOption(puntoAcceso->semestre);

        while (true)
        {
            if (vuelta)
            {
                system("cls");
                printTitleOption(puntoAcceso->semestre);
                vuelta = false;
            }

            if (!esperandoEntradaMenu)
            {
                if (GetKeyState(VK_RIGHT) & 0x8000)
                {
                    if (puntoAcceso->sig != nullptr)
                    {
                        puntoAcceso = puntoAcceso->sig;
                        system("cls");
                        printTitleOption(puntoAcceso->semestre);
                    }
                }
                if (GetKeyState('Q') & 0x8000)
                {
                    list.backtToStart(puntoAcceso);
                    system("cls");
                    printTitleOption(puntoAcceso->semestre);
                }
                if (GetKeyState('S') & 0x8000)
                {
                    FlushConsoleInputBuffer(hStdin);
                    system("cls");
                    return 0;
                }
                if (GetKeyState('A') & 0x8000)
                {
                    FlushConsoleInputBuffer(hStdin);
                    system("cls");
                    if (puntoAcceso->semestre == 1)
                    {
                        mecanismoSemestral("../data/primerSemestre.bin");
                    }
                    else if (puntoAcceso->semestre == 2)
                    {
                        mecanismoSemestral("../data/segundoSemestre.bin");
                    }
                    else if (puntoAcceso->semestre == 3)
                    {
                        mecanismoSemestral("../data/tercerSemestre.bin");
                    }
                    else if (puntoAcceso->semestre == 4)
                    {
                        mecanismoSemestral("../data/cuartoSemestre.bin");
                    }
                    else if (puntoAcceso->semestre == 5)
                    {
                        mecanismoSemestral("../data/quintoSemestre.bin");
                    }
                    else if (puntoAcceso->semestre == 6)
                    {
                        mecanismoSemestral("../data/sextoSemestre.bin");
                    }
                    else if (puntoAcceso->semestre == 7)
                    {
                        mecanismoSemestral("../data/septimoSemestre.bin");
                    }
                    else if (puntoAcceso->semestre == 8)
                    {
                        mecanismoSemestral("../data/octavoSemestre.bin");
                    }
                    else if (puntoAcceso->semestre == 9)
                    {
                        mecanismoSemestral("../data/novenoSemestre.bin");
                    }
                    else
                    {
                        mecanismoSemestral("../data/decimoSemestre.bin");
                    }
                }
            }
            Sleep(50);
        }
    } while (true);
    FlushConsoleInputBuffer(hStdin);
    system("cls");
    return 0;
}

void mecanismoSemestral(const char *_archivo)
{
    esperandoEntradaMenu = true;
    cdllSemester::Materia *acceso = nullptr;
    cdllSemester semestre;
    char nombre[40], codigo[9], c, c1;
    int uc = 0;
    bool flag = true;
    COORD posicionEspecifica;
    semestre.read(acceso, _archivo);
    do
    {
        system("cls");
        FlushConsoleInputBuffer(hStdin);
        printTitle();
        posicionEspecifica = {10, 5};
        imprimirEnPosicion(posicionEspecifica, "1. Introducir una nueva materia.");
        posicionEspecifica = {10, 7};
        imprimirEnPosicion(posicionEspecifica, "2. Ver tarjetas de materias.");
        posicionEspecifica = {10, 9};
        imprimirEnPosicion(posicionEspecifica, "3. Cerrar programa.");
        posicionEspecifica = {10, 11};
        imprimirEnPosicion(posicionEspecifica, "OPCION: ");
        c = toupper(getchar());
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (c == '1')
        {
            printTitle();
            system("cls");
            posicionEspecifica = {10, 5};
            imprimirEnPosicion(posicionEspecifica, "Nombre: ");
            std::cin.getline(nombre, 40);
            posicionEspecifica = {10, 7};
            imprimirEnPosicion(posicionEspecifica, "Codigo de materia: ");
            std::cin.getline(codigo, 9);
            posicionEspecifica = {10, 9};
            imprimirEnPosicion(posicionEspecifica, "UC: ");
            uc = validarEntrada(1, 4);
            semestre.newNodo(acceso, nombre, uc, codigo);
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            SHORT y = 0;
            std::string textoCompleto;
            std::string temario;
            for (int i = 0; i < uc; i++)
            {
                y = 11 + (i * 2);
                posicionEspecifica = {10, y};
                textoCompleto = "Temas del Parcial " + std::to_string(i + 1) + ": ";
                imprimirEnPosicion(posicionEspecifica, textoCompleto.c_str());
                std::cin.getline(acceso->info.vectorUc[i], 40);
            }
            semestre.save(acceso, _archivo);
        }
        else if (c == '2')
        {
            imprimirNodo(acceso);
            printArrows();
            if (vacio)
            {
                system("cls");
                printTitle();
                posicionEspecifica = {80, 24};
                imprimirEnPosicion(posicionEspecifica, "Presione S para salir de la vista\n\n");
            }
            else
            {
                printTitle();
                posicionEspecifica = {80, 20};
                imprimirEnPosicion(posicionEspecifica, "Presione C para modificar el registro");
                posicionEspecifica = {80, 22};
                imprimirEnPosicion(posicionEspecifica, "Presione D para eliminar el registro");
                posicionEspecifica = {80, 24};
                imprimirEnPosicion(posicionEspecifica, "Presione S para salir de la vista");
            }
            bool esperandoEntrada = false;

            while (true)
            {
                if (!esperandoEntrada)
                {
                    if (GetKeyState(VK_RIGHT) & 0x8000)
                    {
                        if (acceso == nullptr)
                        {
                            system("cls");
                            printTitle();
                            posicionEspecifica = {80, 24};
                            imprimirEnPosicion(posicionEspecifica, "Presione S para salir de la vista\n\n");
                        }
                        else
                        {
                            acceso = acceso->sig;
                            imprimirNodo(acceso);
                            posicionEspecifica = {80, 20};
                            imprimirEnPosicion(posicionEspecifica, "Presione C para modificar el registro");
                            posicionEspecifica = {80, 22};
                            imprimirEnPosicion(posicionEspecifica, "Presione D para eliminar el registro");
                            posicionEspecifica = {80, 24};
                            imprimirEnPosicion(posicionEspecifica, "Presione S para salir de la vista");
                            printArrows();
                        }
                    }

                    if (GetKeyState(VK_LEFT) & 0x8000)
                    {
                        if (acceso == nullptr)
                        {
                            system("cls");
                            posicionEspecifica = {80, 24};
                            imprimirEnPosicion(posicionEspecifica, "Presione S para salir de la vista\n\n");
                        }
                        else
                        {
                            manejarIzquierda(acceso);
                        }
                    }
                    if (GetKeyState('C') & 0x8000)
                    {
                        imprimirNodo(acceso);
                        posicionEspecifica = {40, 19};
                        imprimirEnPosicion(posicionEspecifica, "Seleccione la propiedad que desea cambiar a continuacion:");
                        posicionEspecifica = {40, 21};
                        imprimirEnPosicion(posicionEspecifica, "N. Nombre.");
                        posicionEspecifica = {40, 23};
                        imprimirEnPosicion(posicionEspecifica, "U. UC.\n");
                    }
                    if (GetKeyState('D') & 0x8000)
                    {
                        semestre.deleteNodo(acceso);
                        semestre.deleteNodoinFile(acceso, _archivo);
                        if (acceso == nullptr)
                        {
                            system("cls");
                            posicionEspecifica = {80, 24};
                            imprimirEnPosicion(posicionEspecifica, "Presione S para salir de la vista\n\n");
                        }
                        else
                        {
                            manejarIzquierda(acceso);
                        }
                    }
                    if (GetKeyState('S') & 0x8000)
                    {
                        break;
                    }
                }

                if ((GetKeyState('N') & 0x8000) && !esperandoEntrada)
                {
                    FlushConsoleInputBuffer(hStdin);
                    esperandoEntrada = true;
                    system("cls");
                    posicionEspecifica = {40, 7};
                    imprimirEnPosicion(posicionEspecifica, "Nombre: ");
                    std::cin.getline(acceso->nombre, 40);
                    esperandoEntrada = false;
                    manejarIzquierda(acceso);
                }
                if ((GetKeyState('U') & 0x8000) && !esperandoEntrada)
                {
                    FlushConsoleInputBuffer(hStdin);
                    esperandoEntrada = true;
                    system("cls");
                    posicionEspecifica = {40, 7};
                    imprimirEnPosicion(posicionEspecifica, "UC: ");
                    acceso->info.uc = validarEntrada(1, 4);
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    esperandoEntrada = false;
                    FlushConsoleInputBuffer(hStdin);
                    manejarIzquierda(acceso);
                }
                Sleep(50);
            }
            FlushConsoleInputBuffer(hStdin);
        }
    } while (c != '3');

    FlushConsoleInputBuffer(hStdin);
    system("cls");
    esperandoEntradaMenu = false;
    vuelta = true;
    return;
}

void imprimirEnPosicion(COORD posicion, const char *texto)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsole, posicion);
    std::cout << texto;
}

void imprimirNodo(cdllSemester::Materia *acceso)
{
    system("cls");
    printTitle();
    COORD posicionEspecifica = {20, 5};
    vacio = false;
    if (acceso == nullptr)
    {
        vacio = true;
        return;
    }
    SHORT y = 0;
    int _uc = acceso->info.uc;
    std::string textoCompleto = "Nombre: " + std::string(acceso->nombre);
    posicionEspecifica = {40, 5};
    imprimirEnPosicion(posicionEspecifica, textoCompleto.c_str());
    textoCompleto = "Codigo de materia: " + std::string(acceso->info.codigo);
    posicionEspecifica = {40, 7};
    imprimirEnPosicion(posicionEspecifica, textoCompleto.c_str());
    textoCompleto = "UC: " + std::to_string(acceso->info.uc);
    posicionEspecifica = {40, 9};
    imprimirEnPosicion(posicionEspecifica, textoCompleto.c_str());

    for (int i = 0; i < _uc; i++)
    {
        y = 11 + (i * 2);
        posicionEspecifica = {40, y};
        textoCompleto = "Parcial " + std::to_string(i + 1) + ": " + acceso->info.vectorUc[i];
        imprimirEnPosicion(posicionEspecifica, textoCompleto.c_str());
    }
}

int validarEntrada(int minimo, int maximo)
{
    int numero;
    while (true)
    {
        std::cin >> numero;
        if (std::cin.fail() || numero < minimo || numero > maximo)
        {
            COORD posicionEspecifica = {10, 19};
            imprimirEnPosicion(posicionEspecifica, "Entrada invalida. Por favor, intente de nuevo: ");
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else
        {
            break;
        }
    }
    return numero;
}

void manejarIzquierda(cdllSemester::Materia *&acceso)
{
    acceso = acceso->ant;
    imprimirNodo(acceso);
    COORD posicionEspecifica = {80, 20};
    imprimirEnPosicion(posicionEspecifica, "Presione C para modificar el registro");
    posicionEspecifica = {80, 22};
    imprimirEnPosicion(posicionEspecifica, "Presione D para eliminar el registro");
    posicionEspecifica = {80, 24};
    imprimirEnPosicion(posicionEspecifica, "Presione S para salir de la vista");
    printArrows();
}

void printArrows()
{
    COORD posicionEspecifica = {7, 28};
    imprimirEnPosicion(posicionEspecifica, "<-");
    posicionEspecifica.X = 110;
    imprimirEnPosicion(posicionEspecifica, "->");
}

void printTitle()
{
    COORD posicionEspecifica = {90, 2};
    imprimirEnPosicion(posicionEspecifica, "CONTROL DE ESTUDIOS | UNET");
}

void printTitleOption(int i)
{
    printTitle();
    COORD posicionEspecifica = {51, 14};
    if (i == 1)
    {
        imprimirEnPosicion(posicionEspecifica, "PRIMER SEMESTRE");
    }
    else if (i == 2)
    {
        imprimirEnPosicion(posicionEspecifica, "SEGUNDO SEMESTRE");
    }
    else if (i == 3)
    {
        imprimirEnPosicion(posicionEspecifica, "TERCER SEMESTRE");
    }
    else if (i == 4)
    {
        imprimirEnPosicion(posicionEspecifica, "CUARTO SEMESTRE");
    }
    else if (i == 5)
    {
        imprimirEnPosicion(posicionEspecifica, "QUINTO SEMESTRE");
    }
    else if (i == 6)
    {
        imprimirEnPosicion(posicionEspecifica, "SEXTO SEMESTRE");
    }
    else if (i == 7)
    {
        imprimirEnPosicion(posicionEspecifica, "SEPTIMO SEMESTRE");
    }
    else if (i == 8)
    {
        imprimirEnPosicion(posicionEspecifica, "OCTAVO SEMESTRE");
    }
    else if (i == 9)
    {
        imprimirEnPosicion(posicionEspecifica, "NOVENO SEMESTRE");
    }
    else
    {
        imprimirEnPosicion(posicionEspecifica, "DECIMO SEMESTRE");
    }
    posicionEspecifica = {70, 22};
    imprimirEnPosicion(posicionEspecifica, "Presione A para ver la informacion correspondiente");
    posicionEspecifica = {70, 24};
    imprimirEnPosicion(posicionEspecifica, "Presione Q para volver al inicio de la lista");
    posicionEspecifica = {70, 26};
    imprimirEnPosicion(posicionEspecifica, "Presione S para terminar la ejecucion\n\n");
    posicionEspecifica = {110, 28};
    imprimirEnPosicion(posicionEspecifica, "->");
}