#include <iostream>
#include <windows.h>
#include <limits>
#include <sstream>
#include <string>
#include <cstdio>
#include <string>
#include <fstream>
#include "../include/Include.h"

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

void mecanismoSemestral(const char *_archivo);
void imprimirEnPosicion(COORD posicion, const char *texto);
void imprimirNodo(Materia *acceso);
int validarEntrada(int minimo, int maximo);
void manejarIzquierda(Materia *&acceso);
void printArrows();
void printTitle();
void printTitleOption(int i);
bool vacio = false, esperandoEntradaMenu = false, vuelta = false;
HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);

template <typename T>
std::string to_string(T value) {
    std::stringstream ss;
    ss << value;
    return ss.str();
}

struct Nodo
{
    int semestre;
    Nodo *sig;
    Nodo *first;
};

struct Saved
{
    char nombre[40];
    Atributos info;
    Saved() : info() {}
};

void save(const char *nombreArchivo, const void *datos, size_t size)
{
    std::ofstream archivo(nombreArchivo, std::ios::binary | std::ios::app);
    if (!archivo)
    {
        std::cout << "NO SE PUEDO ABRIR EL ARCHIVO.";
        return;
    }
    archivo.write(reinterpret_cast<const char *>(datos), size);
    archivo.close();
}

void read(const char *nombreArchivo, const size_t size, int indice, void *datos)
{
    std::ifstream archivo(nombreArchivo, std::ios::binary);
    if (!archivo)
    {
        std::cerr << "NO SE PUDO ABRIR EL ARCHIVO." << std::endl;
        system("pause");
    }

    size_t posicion = indice * size;
    archivo.seekg(posicion);
    if (!archivo.read(reinterpret_cast<char *>(datos), size))
    {
        std::cerr << "ERROR AL LEER DEL ARCHIVO." << std::endl;
        system("pause");
    }
}

size_t getSize(const char *nombreArchivo, const size_t size)
{
    std::ifstream archivo(nombreArchivo, std::ios::binary | std::ios::ate);
    if (!archivo)
    {
        std::cerr << "No se pudo abrir el archivo." << std::endl;
        return 0;
    }
    size_t tamanoDelArchivo = archivo.tellg();
    return tamanoDelArchivo / size;
}

bool isEmpty(const char *nombreArchivo)
{
    std::ifstream archivo(nombreArchivo, std::ios::binary | std::ios::ate);
    if (!archivo)
    {
        return true;
    }
    return archivo.tellg() == 0;
}

bool deleteInFile(const char *nombreArchivo, const size_t size, int indice)
{
    std::vector<char> buffer;
    std::ifstream archivo(nombreArchivo, std::ios::binary);
    if (!archivo)
    {
        std::cerr << "NO SE PUDO ABRIR EL ARCHIVO." << std::endl;
        return false;
    }
    archivo.seekg(0, std::ios::end);
    size_t tamano = archivo.tellg();
    archivo.seekg(0, std::ios::beg);
    buffer.resize(tamano);
    archivo.read(buffer.data(), tamano);
    archivo.close();

    size_t posicion = indice * size;
    if (posicion + size > tamano)
    {
        std::cerr << "Indice fuera de rango." << std::endl;
        return false;
    }

    buffer.erase(buffer.begin() + posicion, buffer.begin() + posicion + size);

    std::ofstream archivoSalida(nombreArchivo, std::ios::binary | std::ios::trunc);
    if (!archivoSalida)
    {
        std::cerr << "NO SE PUDO ABRIR EL ARCHIVO PARA ESCRIBIR." << std::endl;
        return false;
    }
    archivoSalida.write(buffer.data(), buffer.size());
    archivoSalida.close();

    return true;
}

void newNodo(Nodo *&puntoAcceso, int i)
{
    Nodo *nuevoNodo = new Nodo();
    nuevoNodo->semestre = i;
    nuevoNodo->sig = NULL;

    if (puntoAcceso == NULL)
    {
        puntoAcceso = nuevoNodo;
        puntoAcceso->first = puntoAcceso;
    }
    else
    {
        Nodo *actual = puntoAcceso;
        while (actual->sig != NULL)
        {
            actual = actual->sig;
        }
        nuevoNodo->first = puntoAcceso->first;
        actual->sig = nuevoNodo;
    }
}

void backtToStart(Nodo *&puntoAcceso)
{
    if (puntoAcceso != NULL)
    {
        puntoAcceso = puntoAcceso->first;
    }
}

void newNodo(Materia *&acceso, char *_nombre, int _uc, char *_codigo)
{
    Materia *nuevo_nodo = new Materia();
    strncpy(nuevo_nodo->nombre, _nombre, sizeof(nuevo_nodo->nombre) - 1);
    nuevo_nodo->nombre[sizeof(nuevo_nodo->nombre) - 1] = '\0';
    strncpy(nuevo_nodo->info.codigo, _codigo, sizeof(nuevo_nodo->info.codigo) - 1);
    nuevo_nodo->info.codigo[sizeof(nuevo_nodo->info.codigo) - 1] = '\0';
    nuevo_nodo->info.uc = _uc;

    if (acceso == NULL)
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

void printAll(Materia *acceso)
{
    Materia *actual = acceso;
    do
    {
        std::cout << actual->nombre << "\n";
        actual = actual->sig;
    } while (actual != acceso);
}

void deleteNodo(Materia *&acceso)
{
    if (acceso == NULL)
    {
        return;
    }

    if (acceso->sig == acceso)
    {
        delete acceso;
        acceso = NULL;
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

void save(Materia *&acceso, const char *nombre_archivo)
{
    Saved *auxiliar = new Saved();
    strncpy(auxiliar->nombre, acceso->nombre, sizeof(auxiliar->nombre) - 1);
    auxiliar->nombre[sizeof(auxiliar->nombre) - 1] = '\0';
    auxiliar->info.uc = acceso->info.uc;
    strncpy(auxiliar->info.codigo, acceso->info.codigo, sizeof(auxiliar->info.codigo) - 1);
    auxiliar->info.codigo[sizeof(auxiliar->info.codigo) - 1] = '\0';
    for (int i = 0; i < acceso->info.uc; i++)
    {
        strcpy(auxiliar->info.vectorUc[i], acceso->info.vectorUc[i]);
    }
    save(nombre_archivo, auxiliar, sizeof(Saved));
}

void read(Materia *&acceso, const char *nombre_archivo)
{
    binaryFiles file;
    Saved auxiliar;
    int size = static_cast<int>(getSize(nombre_archivo, sizeof(Saved)));
    if (isEmpty(nombre_archivo))
    {
        return;
    }

    for (int i = 0; i < size; i++)
    {
        read(nombre_archivo, sizeof(Saved), i, &auxiliar);
        newNodo(acceso, auxiliar.nombre, auxiliar.info.uc, auxiliar.info.codigo);
        for (int a = 0; a < auxiliar.info.uc; a++)
        {
            strcpy(acceso->info.vectorUc[a], auxiliar.info.vectorUc[a]);
        }
        strcpy(acceso->info.codigo, auxiliar.info.codigo);
    }
}

void deleteNodoinFile(Materia *&acceso, const char *nombre_archivo)
{
    Saved auxiliar;
    int indice = 0;
    int size = static_cast<int>(getSize(nombre_archivo, sizeof(Saved)));
    if (isEmpty(nombre_archivo))
    {
        return;
    }
    for (int i = 0; i < size; i++)
    {
        read(nombre_archivo, sizeof(Saved), i, &auxiliar);
        if (auxiliar.info.codigo == acceso->info.codigo)
        {
            indice = i;
            break;
        }
    }
    deleteInFile(nombre_archivo, sizeof(Saved), indice);
}

int main()
{
    COORD posicionEspecifica;
    linkedList list;
    char menu;
    Nodo *puntoAcceso = NULL;
    for (int a = 1; a < 11; a++)
    {
        newNodo(puntoAcceso, a);
    }
    do
    {
        system("cls");
        FlushConsoleInputBuffer(hStdin);
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
                    if (puntoAcceso->sig != NULL)
                    {
                        puntoAcceso = puntoAcceso->sig;
                        system("cls");
                        printTitleOption(puntoAcceso->semestre);
                    }
                }
                if (GetKeyState('Q') & 0x8000)
                {
                    backtToStart(puntoAcceso);
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
    Materia *acceso = NULL;
    char nombre[40], codigo[9], c, c1;
    int uc = 0;
    bool flag = true;
    COORD posicionEspecifica;
    read(acceso, _archivo);
    do
    {
        system("cls");
        FlushConsoleInputBuffer(hStdin);
        printTitle();
		posicionEspecifica.X = 10;
		posicionEspecifica.Y = 5;
 //       posicionEspecifica = {10, 5};
        imprimirEnPosicion(posicionEspecifica, "1. Introducir una nueva materia.");
        posicionEspecifica.X = 10;
		posicionEspecifica.Y = 7;
//        posicionEspecifica = {10, 7};
        imprimirEnPosicion(posicionEspecifica, "2. Ver tarjetas de materias.");
        posicionEspecifica.X = 10;
		posicionEspecifica.Y = 9;
//        posicionEspecifica = {10, 9};
        imprimirEnPosicion(posicionEspecifica, "3. Cerrar programa.");
        posicionEspecifica.X = 10;
		posicionEspecifica.Y = 11;
//        posicionEspecifica = {10, 11};
        imprimirEnPosicion(posicionEspecifica, "OPCION: ");
        c = toupper(getchar());
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (c == '1')
        {
            printTitle();
            system("cls");
            posicionEspecifica.X = 10;
			posicionEspecifica.Y = 5;
//            posicionEspecifica = {10, 5};
            imprimirEnPosicion(posicionEspecifica, "Nombre: ");
            std::cin.getline(nombre, 40);
            posicionEspecifica.X = 10;
			posicionEspecifica.Y = 7;
//            posicionEspecifica = {10, 7};
            imprimirEnPosicion(posicionEspecifica, "Codigo de materia: ");
            std::cin.getline(codigo, 9);
            posicionEspecifica.X = 10;
			posicionEspecifica.Y = 9;
//          posicionEspecifica = {10, 9};
            imprimirEnPosicion(posicionEspecifica, "UC: ");
            uc = validarEntrada(1, 4);
            newNodo(acceso, nombre, uc, codigo);
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            SHORT y = 0;
            std::string textoCompleto;
            std::string temario;
            for (int i = 0; i < uc; i++)
            {
                y = 11 + (i * 2);
                posicionEspecifica.X = 10;
                posicionEspecifica.Y = y;
//                posicionEspecifica = {10, y};
                textoCompleto = "Temas del Parcial " + to_string(i + 1) + ": ";
                imprimirEnPosicion(posicionEspecifica, textoCompleto.c_str());
                std::cin.getline(acceso->info.vectorUc[i], 40);
            }
            save(acceso, _archivo);
        }
        else if (c == '2')
        {
            imprimirNodo(acceso);
            printArrows();
            if (vacio)
            {
                system("cls");
                printTitle();
                posicionEspecifica.X = 80;
                posicionEspecifica.Y = 24;
//                posicionEspecifica = {80, 24};
                imprimirEnPosicion(posicionEspecifica, "Presione S para salir de la vista\n\n");
            }
            else
            {
                printTitle();
                posicionEspecifica.X = 80;
                posicionEspecifica.Y = 20;
//                posicionEspecifica = {80, 20};
                imprimirEnPosicion(posicionEspecifica, "Presione C para modificar el registro");
                posicionEspecifica.X = 80;
                posicionEspecifica.Y = 22;
//                posicionEspecifica = {80, 22};
                imprimirEnPosicion(posicionEspecifica, "Presione D para eliminar el registro");
                posicionEspecifica.X = 80;
                posicionEspecifica.Y = 24;
//                posicionEspecifica = {80, 24};
                imprimirEnPosicion(posicionEspecifica, "Presione S para salir de la vista");
            }
            bool esperandoEntrada = false;

            while (true)
            {
                if (!esperandoEntrada)
                {
                    if (GetKeyState(VK_RIGHT) & 0x8000)
                    {
                        if (acceso == NULL)
                        {
                            system("cls");
                            printTitle();
                            posicionEspecifica.X = 80;
                            posicionEspecifica.Y = 24;
//                            posicionEspecifica = {80, 24};
                            imprimirEnPosicion(posicionEspecifica, "Presione S para salir de la vista\n\n");
                        }
                        else
                        {
                            acceso = acceso->sig;
                            imprimirNodo(acceso);
                            posicionEspecifica.X = 80;
                            posicionEspecifica.Y = 20;
//                            posicionEspecifica = {80, 20};
                            imprimirEnPosicion(posicionEspecifica, "Presione C para modificar el registro");
                            posicionEspecifica.X = 80;
                            posicionEspecifica.Y = 22;
//                            posicionEspecifica = {80, 22};
                            imprimirEnPosicion(posicionEspecifica, "Presione D para eliminar el registro");
                            posicionEspecifica.X = 80;
                            posicionEspecifica.Y = 24;
//                            posicionEspecifica = {80, 24};
                            imprimirEnPosicion(posicionEspecifica, "Presione S para salir de la vista");
                            printArrows();
                        }
                    }

                    if (GetKeyState(VK_LEFT) & 0x8000)
                    {
                        if (acceso == NULL)
                        {
                            system("cls");
                            posicionEspecifica.X = 80;
                            posicionEspecifica.Y = 24;
//                            posicionEspecifica = {80, 24};
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
                        posicionEspecifica.X = 40;
                        posicionEspecifica.Y = 19;
//                        posicionEspecifica = {40, 19};
                        imprimirEnPosicion(posicionEspecifica, "Seleccione la propiedad que desea cambiar a continuacion:");
                        posicionEspecifica.X = 40;
                        posicionEspecifica.Y = 21;
//                        posicionEspecifica = {40, 21};
                        imprimirEnPosicion(posicionEspecifica, "N. Nombre.");
                        posicionEspecifica.X = 40;
                        posicionEspecifica.Y = 23;
//                        posicionEspecifica = {40, 23};
                        imprimirEnPosicion(posicionEspecifica, "U. UC.\n");
                    }
                    if (GetKeyState('D') & 0x8000)
                    {
                        deleteNodo(acceso);
                        deleteNodoinFile(acceso, _archivo);
                        if (acceso == NULL)
                        {
                            system("cls");
                            posicionEspecifica.X = 80;
                            posicionEspecifica.Y = 24;
//                            posicionEspecifica = {80, 24};
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
                    posicionEspecifica.X = 40;
                    posicionEspecifica.Y = 7;
//                    posicionEspecifica = {40, 7};
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
                    posicionEspecifica.X = 40;
                    posicionEspecifica.Y = 7;
//                    posicionEspecifica = {40, 7};
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

void imprimirNodo(Materia *acceso)
{
    system("cls");
    printTitle();
    COORD posicionEspecifica = {20, 5};
    vacio = false;
    if (acceso == NULL)
    {
        vacio = true;
        return;
    }
    SHORT y = 0;
    int _uc = acceso->info.uc;
    std::string textoCompleto = "Nombre: " + std::string(acceso->nombre);
    posicionEspecifica.X = 40;
    posicionEspecifica.Y = 5;
//    posicionEspecifica = {40, 5};
    imprimirEnPosicion(posicionEspecifica, textoCompleto.c_str());
    textoCompleto = "Codigo de materia: " + std::string(acceso->info.codigo);
    posicionEspecifica.X = 40;
    posicionEspecifica.Y = 7;
//    posicionEspecifica = {40, 7};
    imprimirEnPosicion(posicionEspecifica, textoCompleto.c_str());
    textoCompleto = "UC: " + to_string(acceso->info.uc);
    posicionEspecifica.X = 40;
    posicionEspecifica.Y = 9;
//    posicionEspecifica = {40, 9};
    imprimirEnPosicion(posicionEspecifica, textoCompleto.c_str());

    for (int i = 0; i < _uc; i++)
    {
        y = 11 + (i * 2);
        posicionEspecifica.X = 40;
    	posicionEspecifica.Y = y;
//        posicionEspecifica = {40, y};
        textoCompleto = "Parcial " + to_string(i + 1) + ": " + acceso->info.vectorUc[i];
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

void manejarIzquierda(Materia *&acceso)
{
    acceso = acceso->ant;
    imprimirNodo(acceso);
    COORD posicionEspecifica = {80, 20};
    imprimirEnPosicion(posicionEspecifica, "Presione C para modificar el registro");
    posicionEspecifica.X = 80;
    posicionEspecifica.Y = 22;
//    posicionEspecifica = {80, 22};
    imprimirEnPosicion(posicionEspecifica, "Presione D para eliminar el registro");
    posicionEspecifica.X = 80;
    posicionEspecifica.Y = 24;
//    posicionEspecifica = {80, 24};
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
    posicionEspecifica.X = 70;
    posicionEspecifica.Y = 22;
//    posicionEspecifica = {70, 22};
    imprimirEnPosicion(posicionEspecifica, "Presione A para ver la informacion correspondiente");
    posicionEspecifica.X = 70;
    posicionEspecifica.Y = 24;
//    posicionEspecifica = {70, 24};
    imprimirEnPosicion(posicionEspecifica, "Presione Q para volver al inicio de la lista");
    posicionEspecifica.X = 70;
    posicionEspecifica.Y = 26;
//    posicionEspecifica = {70, 26};
    imprimirEnPosicion(posicionEspecifica, "Presione S para terminar la ejecucion\n\n");
    posicionEspecifica.X = 110;
    posicionEspecifica.Y = 28;
//    posicionEspecifica = {110, 28};
    imprimirEnPosicion(posicionEspecifica, "->");
}
