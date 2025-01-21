//============================================================================
// Name        : Grafos.cpp
// Authors     : Javier Chacon y Maria Ballesteros
//============================================================================

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <vector>
#include <windows.h>
#include <sstream>
#include <algorithm>
#include <limits>
#include <cctype>
#include <queue>
#include <map>
#include <set>

using namespace std;

struct Arista
{
	int peso;
	char padre;
	char hijo;
};

struct Vertice
{
	char id;
	vector<Arista> entrantes;
	vector<Arista> salientes;
};

vector<Vertice> vertices;

void imprimirHeader();
void imprimirMatriz(int **matriz, int cantVertices);
void customSplit(string str, vector<string> &strings);
void gotoxy(int x, int y);
void inicializarMatrizAdyacencia(int **matrizAdyacente, int cantVertices, int instruccion);
int obtenerCantidadVertices();
bool esConexo(int **matrizAdyacente, int cantVertices);
int** recursionWarshall(int **matrizAdyacente, int recursion, int cantVertices);
void determinarNodosFuentePozo();
int validarEntrada(int min, int max);
void imprimirGrafo();
int eliminarNodo(char nodo);
void dijkstra(char inicio, char final);
static bool costoMinimo(const pair<Vertice*, int>& a, const pair<Vertice*, int>& b);

int main()
{
	int totalVertices = obtenerCantidadVertices(), seleccionUsuario = 0, instruccion = 0, continuarEliminacion = 0, indiceAEliminar = 0;
	int nodosEliminados = 0;
	bool conexo = false, nodoEncontrado = false;
	char nodoToDelete;
	
	do
	{
	// INICIALIZACION
		system("cls");
		if(instruccion != 0)
		{
			totalVertices = vertices.size();
		}
		
		int** matrizAdyacente = new int*[totalVertices];
		for (int i = 0; i < totalVertices; ++i) {
		    matrizAdyacente[i] = new int[totalVertices];
		}
		imprimirHeader();
		cout << "\n\nSE ESTA CARGANDO SU GRAFO";
		for (int i = 0; i < 2; i++)
		{
			cout << " .";
			Sleep(500);
		}
		cout << "\n\n";
		system("cls");
		inicializarMatrizAdyacencia(matrizAdyacente, totalVertices, instruccion);
		imprimirGrafo();
		gotoxy(20, 4);
		cout << "MATRIZ DE ADYACENCIA GENERADA:\n\n";
		imprimirMatriz(matrizAdyacente, totalVertices);
		system("cls");
		
		// PARTE A Y B: MATRIZ CONEXA
		conexo = esConexo(matrizAdyacente, totalVertices);
		system("cls");
		imprimirHeader();
		if(conexo)
		{
			cout << "\n\nEL GRAFO ES FUERTEMENTE CONEXO.\n\n";
		}
		else
		{
			cout << "\n\nEL GRAFO NO ES FUERTEMENTE CONEXO.\n\n";
			determinarNodosFuentePozo();
		}
		
		system("pause");
		
		do
		{
			// PARTE C Y D: Eliminar vertice y aplicar algoritmo de Djikstra
			system("cls");
			imprimirHeader();
			cout << "\n\nSeleccione una de las siguientes opciones:\n\n"; 
			cout << "1. Para eliminar un nodo.\n\n";
			cout << "2. Para encontrar la ruta minima entre dos vertices.\n\n";
			cout << "3. Para salir.\n\n";
			
			seleccionUsuario = validarEntrada(1, 3);
			if(seleccionUsuario == 1)
			{
				do
				{
					continuarEliminacion = 0;
					nodoEncontrado = false;	
					indiceAEliminar = 0;
					system("cls");
					imprimirHeader();
					cout << "\n\nIntroduzca el ID del vertice a eliminar: ";
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					nodoToDelete = getchar();
					if (isalpha(nodoToDelete))
					{
						for (int i = 0; i < vertices.size(); i++)
						{
							if(vertices[i].id == toupper(nodoToDelete))
							{
								nodoEncontrado = true;
								indiceAEliminar = i;
							}
						}
						if (nodoEncontrado)
						{
							cout << "\n\nVertice encontrado.\n\n";
							vertices.erase(vertices.begin() + indiceAEliminar);
							nodosEliminados++;
							nodosEliminados += eliminarNodo(toupper(nodoToDelete));
							cout << "1. Para buscar otro nodo.\n\n";
							cout << "2. Para salir del menu de eliminacion\n\n";
							continuarEliminacion = validarEntrada(1,2);
						}
						else
						{
							cout << "\n\nVertice no encontrado.\n\n";
							cout << "1. Para buscar otro nodo.\n\n";
							cout << "2. Para salir del menu de eliminacion\n\n";
							continuarEliminacion = validarEntrada(1,2);
						}
			  		} 
					else 
					{
			       		cout << "\n\nEl caracter introducido no es de tipo Alpha.\n\n";
			       		cout << "1. Para buscar otro nodo.\n\n";
						cout << "2. Para salir del menu de eliminacion\n\n";
						continuarEliminacion = validarEntrada(1,2);
			    	}
			    	
			    	imprimirGrafo();
				}while(continuarEliminacion != 2);
			}
			else if (seleccionUsuario == 2)
			{
				char inicio, final;
				system("cls");
				imprimirHeader();
				cout << "\n\nIntroduzca el nodo de inicio: ";
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				inicio = getchar();
				cout << "\nIntroduzca el nodo final: ";
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				final = getchar();
				dijkstra(toupper(inicio), toupper(final));
			}
			else if (seleccionUsuario == 3)
			{
				system("cls");
				imprimirHeader();
				cout << "\n\nHasta luego.\n\n";
			}
		}while(seleccionUsuario != 3);
		instruccion++;
	}while (seleccionUsuario != 3);
	return 0;
}

void imprimirHeader()
{
	ifstream header("ascii-header.txt");
	string linea;
	while(getline(header, linea))
	{
		cout << linea << "\n";
	}
	header.close();
}

void imprimirMatriz(int **matriz, int cantVertices)
{
	for (int i = 0; i < cantVertices; ++i) {
        for (int j = 0; j < cantVertices; ++j) {
            gotoxy((j+10) * 5, (i+4) * 2);
            cout << matriz[i][j];
        }
    }
	cout << "\n\n";
	system("pause");
}

void customSplit(string str, vector<string>& strings) 
{
    int startIndex = 0, endIndex = 0;
    for (int i = 0; i <= str.size(); i++) 
	{
        if (str[i] == '-' || str[i] == ' ' || i == str.size()) 
		{
            endIndex = i;
            string temp;
            temp.append(str, startIndex, endIndex - startIndex);
            strings.push_back(temp); 
            if(str[i] == '-')
			{
           		startIndex = endIndex + 2;
			}
			else if(str[i] == ' ')
			{
				startIndex = endIndex+1;
			}
        }
    }
}

void gotoxy(int x, int y)
{
    COORD coordinate;
    coordinate.X = x;
    coordinate.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinate);
}

void inicializarArchivo(int **matrizAdyacente, int cantVertices, vector<string>& abecedario)
{
	ifstream arista("arista.txt");
	string linea;
		
	for(int i = 0; i < cantVertices; i++)
	{
		for (int a = 0; a < cantVertices; a++)
		{
			matrizAdyacente[i][a] = 0;
		}
	}
	getline(arista, linea);
	while(getline(arista, linea))
	{
		// Declaracion de variables
		vector<string> strings;
		customSplit(linea, strings);
		Arista arista;
		Vertice verticePadre, verticeHijo;
		bool padre = false, hijo = false;
		int padrePos = 0, hijoPos = 0;
		
		// Si el grafo no esta vacio
		if(!vertices.empty())
		{
			// Comprobamos si hay algun vertice ya registrado en el grafo
			for(int i=0; i<vertices.size(); i++)
			{
				if(vertices[i].id == strings[0][0])
				{
					padre = true;
					padrePos = i;
				}
				if(vertices[i].id == strings[1][0])
				{
					hijo = true;
					hijoPos = i;
				}
			}
			// Si los vertices leidos son iguales
			if(strings[0] == strings[1])
			{
				if(!padre) // Si el padre no existe, no existe el hijo, son el mismo
				{
					abecedario.push_back(strings[0]);
				}
				
				arista.peso = strings[2][0]- '0';
				arista.padre = strings[0][0];
				arista.hijo = strings[1][0];
				
				if(padre)
				{
					vertices[padrePos].salientes.push_back(arista);
					arista.padre = strings[1][0];
					arista.hijo = strings[0][0];
					vertices[padrePos].entrantes.push_back(arista);
				}
				else
				{
					verticePadre.id = strings[0][0];
					verticePadre.salientes.push_back(arista);
					arista.padre = strings[1][0];
					arista.hijo = strings[0][0];
					verticePadre.entrantes.push_back(arista);
					vertices.push_back(verticePadre);
				}
			} // Si los vertices leidos no son iguales
			else
			{
				if(!padre){
					abecedario.push_back(strings[0]);
				}
				if(!hijo)
				{
					abecedario.push_back(strings[1]);
				}
				// Creamos el camino entre ambos
				arista.padre = strings[0][0];
				arista.hijo = strings[1][0];
				arista.peso = strings[2][0]- '0';
				
				if(padre)
				{
					vertices[padrePos].salientes.push_back(arista);
				}
				if(hijo)
				{
					vertices[hijoPos].entrantes.push_back(arista);
				}
				if(!padre)
				{
					verticePadre.id = strings[0][0];
					verticePadre.salientes.push_back(arista);
					vertices.push_back(verticePadre);
				}
				if(!hijo)
				{
					verticeHijo.id = strings[1][0];
					verticeHijo.entrantes.push_back(arista);
					vertices.push_back(verticeHijo);
				}
			}	
		}
		else // Si el grafo esta vacio
		{
			// Creo el camino
			arista.padre = strings[0][0];
			arista.hijo = strings[1][0];
			arista.peso = strings[2][0]- '0';
			
			if(strings[0] != strings[1])
			{
				// Guardo ambas letras, porque no existen todavia
				abecedario.push_back(strings[0]);	
				abecedario.push_back(strings[1]);
				// Creo al vertice padre
				verticePadre.id = strings[0][0];
				verticePadre.salientes.push_back(arista);
				// Creo al vertice hijo
				verticeHijo.id = strings[1][0];
				verticeHijo.entrantes.push_back(arista);
				// Los guardo a ambos en el vector de vertices
				vertices.push_back(verticePadre);
				vertices.push_back(verticeHijo);
			}
			else
			{
				// Guardo solo una de las letras
				abecedario.push_back(strings[0]);
				// Creo al padre, que tambien es el hijo
				verticePadre.id = strings[0][0];
				verticePadre.salientes.push_back(arista);
				verticePadre.entrantes.push_back(arista);
			}
		}
	}
	arista.close();
}

void inicializarMatrizAdyacencia(int **matrizAdyacente, int cantVertices, int instruccion)
{	
	vector<string> abecedario;
	
	if (instruccion == 0)
	{
		ifstream arista("arista.txt");
		string linea;
		
		inicializarArchivo(matrizAdyacente, cantVertices, abecedario);
		
		sort(abecedario.begin(), abecedario.end());
	
		getline(arista, linea);
		while(getline(arista, linea))
		{
			vector<string> strings;
			vector<int> posicion;
			customSplit(linea, strings);
			for (int i = 0; i < strings.size()-1; i ++)
			{
				for(int a = 0; a < cantVertices; a++)
				{
					if(strings[i] == abecedario[a])
						posicion.push_back(a);
				} 	
			}
			matrizAdyacente[posicion[0]][posicion[1]] = 1;
		}
		arista.close();
	}
	else
	{
		for(int i= 0; i< vertices.size(); i++)
		{
			abecedario.push_back(string(1,vertices[i].id));
		}
		for(int i = 0; i < cantVertices; i++)
		{
			for (int a = 0; a < cantVertices; a++)
			{
				matrizAdyacente[i][a] = 0;
			}
		}
		sort(abecedario.begin(), abecedario.end());
		// Genero la matriz de adyacencia
		for(int i = 0; i< vertices.size(); i++)
		{
			if(!vertices[i].salientes.empty())
			{
				for(int a = 0; a < vertices[i].salientes.size(); a++)
				{
					vector<int> posicion;
					for(int v = 0; v<abecedario.size(); v++)
					{
						if(vertices[i].salientes[a].padre == abecedario[v][0])
						{
							posicion.push_back(v);
						}
					}
					for(int v = 0; v<abecedario.size(); v++)
					{
						if(vertices[i].salientes[a].hijo == abecedario[v][0])
						{
							posicion.push_back(v);
						}
					}
					matrizAdyacente[posicion[0]][posicion[1]] = 1;
				}
			}
			if(!vertices[i].entrantes.empty())
			{
				for(int a = 0; a < vertices[i].entrantes.size(); a++)
				{
					vector<int> posicion;
					for(int v = 0; v<abecedario.size(); v++)
					{
						if(vertices[i].entrantes[a].padre == abecedario[v][0])
						{
							posicion.push_back(v);
						}
					}
					for(int v = 0; v<abecedario.size(); v++)
					{
						if(vertices[i].entrantes[a].hijo == abecedario[v][0])
						{
							posicion.push_back(v);
						}
					}
					matrizAdyacente[posicion[0]][posicion[1]] = 1;
				}
			}
		}	
	}
}

int obtenerCantidadVertices()
{
	ifstream arista("arista.txt");
	int cantVertices;
	string linea;
	getline(arista, linea);
	if(sscanf(linea.c_str(), "%d", &cantVertices) != 1)
	{
		cout << "Error while reading the text file. No possible convertion from string to int." << "\n\n";
		return -1;
	}
	arista.close();
	return cantVertices;
}

bool esConexo(int **matrizAdyacente, int cantVertices)
{
	int** matrizAuxiliar = recursionWarshall(matrizAdyacente, cantVertices, cantVertices);
    for (int i = 0; i < cantVertices; ++i) {
        for (int j = 0; j < cantVertices; ++j) {
            if (i != j && matrizAuxiliar[i][j] != 1) {
                return false;
            }
        }
    }
 	for (int i = 0; i < cantVertices; ++i) {
        delete[] matrizAuxiliar[i];
    }
    delete[] matrizAuxiliar;
	return true;
}

int** recursionWarshall(int **matrizAdyacente, int recursion, int cantVertices)
{
	if(recursion == 0)
	{
		return matrizAdyacente;
	}
	else
	{
		recursionWarshall(matrizAdyacente, recursion-1, cantVertices);
		for(int i = 0; i < cantVertices; i++)
		{
			if(matrizAdyacente[i][recursion-1] == 1)
			{
				for (int a = 0; a < cantVertices; a++)
				{
					if(matrizAdyacente[recursion-1][a] == 1)
					{
						matrizAdyacente[i][a] = 1;
					}
				}
			}
		} 
		system("cls");
		if(recursion == cantVertices)
		{
			gotoxy(20, 4);
	    	string title = "MATRIZ DE CIERRE TRANSITIVO:";
			cout << title << "\n\n";
			imprimirMatriz(matrizAdyacente, cantVertices);
		}
		else
		{
			gotoxy(20, 4);
			ostringstream out;
	    	out << recursion;
	    	string numStr = out.str();
	    	string title = "MATRIZ DE WARSHALL " + numStr + ":";
			cout << title << "\n\n";
			imprimirMatriz(matrizAdyacente, cantVertices);
		}
		return matrizAdyacente;
	}
}

void determinarNodosFuentePozo()
{
	for(int i=0; i<vertices.size(); i++)
	{
		if(vertices[i].entrantes.empty())
			cout << "El vertice " << vertices[i].id << " es un nodo fuente.\n\n";
			
		if(vertices[i].salientes.empty())
			cout << "El vertice " << vertices[i].id << " es un nodo pozo.\n\n";
	}
}

int validarEntrada(int min, int max) 
{
    int numero;
    while (true) 
	{
        cout << "RESPUESTA: ";
        cin >> numero;
        if (cin.fail()) 
		{
            cout << "\nEntrada invalida. Por favor ingrese un numero entero.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        if (numero >= min && numero <= max) 
		{
            break;
        } else 
		{
            cout << "El numero debe estar entre " << min << " y " << max << ".\n";
        }
    }
    return numero;
}

void imprimirGrafo()
{
	system("cls");
	imprimirHeader();
	cout << "\n\n";
	for(int i = 0; i< vertices.size(); i++)
	{
		cout << "Nodo: " << vertices[i].id << "\n";
		if(!vertices[i].salientes.empty())
		{
			for (int a = 0; a < vertices[i].salientes.size(); a++)
			{
				cout << "Nodo hijo " << a+1 << ": " << vertices[i].salientes[a].hijo << "\n";
			}	
		}
		if(!vertices[i].entrantes.empty())
		{
			for (int a = 0; a < vertices[i].entrantes.size(); a++)
			{
				cout << "Nodo padre " << a+1 << ": " << vertices[i].entrantes[a].padre << "\n";
			}	
		}
		cout << "\n\n";
	}
	system("pause");
	system("cls");
}

int eliminarNodo(char nodo)
{
	int nodosEliminados = 0;
	for (int i = 0; i< vertices.size(); i++)
	{
		if(!vertices[i].entrantes.empty())
		{
			for(int a = 0; a < vertices[i].entrantes.size(); a++)
			{
				if(vertices[i].entrantes[a].padre == nodo || vertices[i].entrantes[a].hijo == nodo)
					vertices[i].entrantes.erase(vertices[i].entrantes.begin() + a);
			}
		}
		if(!vertices[i].salientes.empty())
		{
			for(int a = 0; a < vertices[i].salientes.size(); a++)
			{
				if(vertices[i].salientes[a].padre == nodo || vertices[i].salientes[a].hijo == nodo)
					vertices[i].salientes.erase(vertices[i].salientes.begin() + a);
			}
		}
	}
	
	for (int i = 0; i< vertices.size(); i++)
	{
		if(vertices[i].salientes.empty() && vertices[i].entrantes.empty())
		{
			cout << "\nEl nodo " << vertices[i].id << " queda desconectado del grafo.\n\n";
			vertices.erase(vertices.begin() + i);
			nodosEliminados++;
		}
	}
	return nodosEliminados;
}

void dijkstra(char inicio, char final) {
    // Check if start and end vertices exist
    bool existeInicio = false, existeFinal = false;
    Vertice* verticeInicio = NULL;
    Vertice* verticeFinal = NULL;
    
    for (size_t i = 0; i < vertices.size(); ++i) {
        if (vertices[i].id == inicio) {
            existeInicio = true;
            verticeInicio = &vertices[i];
        }
        if (vertices[i].id == final) {
            existeFinal = true;
            verticeFinal = &vertices[i];
        }
    }
    
    if (!existeInicio || !existeFinal) {
        cout << "\n\nUno o ambos vertices no existen.\n\n";
        system("pause");
        return;
    }
    
    // Initialize data structures
    map<Vertice*, int> distancias;
    set<pair<int, Vertice*> > cola;
    map<Vertice*, Vertice*> rutas;
    
    // Initialize distances and visited status
    for (size_t i = 0; i < vertices.size(); ++i) {
        distancias[&vertices[i]] = numeric_limits<int>::max();
        rutas[&vertices[i]] = NULL;
        if (vertices[i].id == inicio) {
            distancias[&vertices[i]] = 0;
            cola.insert(make_pair(0, &vertices[i]));
        }
    }
    
    // Process vertices
    while (!cola.empty()) {
        Vertice* currentVertice = cola.begin()->second;
        cola.erase(cola.begin());
        
        // Si hemos llegado al vértice final, podemos detenernos
        if (currentVertice == verticeFinal) {
            break;
        }

        for (size_t j = 0; j < currentVertice->salientes.size(); ++j) {
            Arista& arista = currentVertice->salientes[j];
            Vertice* neighbor = NULL;
            
            // Encuentra el puntero al vértice vecino
            for (size_t k = 0; k < vertices.size(); ++k) {
                if (vertices[k].id == arista.hijo) {
                    neighbor = &vertices[k];
                    break;
                }
            }
            
            if (neighbor) {
                int newDist = distancias[currentVertice] + arista.peso;
                if (newDist < distancias[neighbor]) {
                    cola.erase(make_pair(distancias[neighbor], neighbor));
                    distancias[neighbor] = newDist;
                    rutas[neighbor] = currentVertice;
					cola.insert(make_pair(newDist, neighbor));
                }
            }
        }
    }
    
    if (rutas[verticeFinal] == NULL) {
        cout << "\n\nNo hay un camino valido entre los vertices " << inicio << " y " << final << ".\n";
        system("pause");
        return;
    }

    // Reconstruir y mostrar el camino mas corto desde inicio hasta final
    vector<char> camino;
    
    for (Vertice* v = verticeFinal; v != NULL; v = rutas[v]) {
        camino.push_back(v->id);
    }
    
    reverse(camino.begin(), camino.end());
    
    cout << "Camino mas corto: ";
    
    for (size_t i = 0; i < camino.size(); ++i) {
    	if (i==camino.size()-1){
    		cout << camino[i];
		}
		else
		{
			cout << camino[i] << "->";
		}
    }
    
    cout << "\nDistancia total: " << distancias[verticeFinal] << "\n\n";

    system("pause");
}

static bool costoMinimo(const pair<Vertice*, int>& a, const pair<Vertice*, int>& b)
{
	return a.second < b.second;
}
