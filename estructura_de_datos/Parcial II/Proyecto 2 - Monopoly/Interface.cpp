#include "interface.h"

using namespace std;

void Interface::imprimirEnPosicion(COORD posicion, int textColor, int backgroundColor, const string texto){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsole, posicion);
    int colorAttribute = (backgroundColor << 4) | textColor;
    SetConsoleTextAttribute(hConsole, colorAttribute);
    std::cout << texto << endl;;
}

void Interface::imprimirEnPosicion(int x, int y, int textColor, int backgroundColor, const string texto){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD posicion;
    posicion.X = x;
    posicion.Y = y;
    SetConsoleCursorPosition(hConsole, posicion);
    int colorAttribute = (backgroundColor << 4) | textColor;
    SetConsoleTextAttribute(hConsole, colorAttribute);
    std::cout << texto;
}

void Interface::pausarPantalla() {
	imprimirEnPosicion(10, 28, 15, 0, "");
    system("PAUSE");
    imprimirEnPosicion(10, 28, 15, 0, "                                        ");
}

bool Interface::menu(){
	while(true){
		system("cls");
		char tecla = '\0';
		cout << endl << endl;
		cout << "    =========================================================" << endl;
		cout << "    |                 M  O  N  O  P  O  L  Y                |" << endl;
		cout << "    =========================================================" << endl;
		cout << "    |------                                  ---------------|" << endl;
		cout << "    |-----------             1. JUGAR           ------------|" << endl;
		cout << "    |--------------                                     ----|" << endl;
		cout << "    |-----------             2. REGLAS          ------------|" << endl;
		cout << "    |------------                           ----------------|" << endl;
		cout << "    |-----------             3. SALIR           ------------|" << endl;
		cout << "    |-------                                          ------|" << endl;
		cout << "    |-------           Selecciona el numero           ------|" << endl;
		cout << "    =========================================================" << endl;
		
		do{
			tecla = _getch();
		} while(tecla != '1' && tecla != '2' && tecla != '3');
		
		switch(tecla){
			case '1':
				return true;
			case '2':
				imprimirReglas();
				break;
			case '3':
				cout << "     Muchas gracias por jugar :)" << endl;
				return false;
			default:
				cout << "Debe haber algún error" << endl;
		}
	}
}

void Interface::imprimirReglas(){
	system("cls");
	cout << "Normas del Juego - Monopoly Simplificado" << endl << endl;
	cout << "Objetivo del Juego:" << endl;
	cout << "Ser el ultimo jugador en pie, evitando la bancarrota y adquiriendo la mayor cantidad de propiedades y dinero posible." << endl << endl;
	cout << "Preparacion del Juego:" << endl;
	cout << "Selecciona el numero de jugadores, con un maximo de 4 participantes." << endl;
	cout << "Cada jugador elige un nombre para identificarse en el juego." << endl;
	cout << "El tablero se compone de 28 casillas, cada una representando una propiedad o una accion especial." << endl << endl;
	cout << "Desarrollo del Juego:" << endl;
	cout << "Los jugadores se turnan para lanzar un dado y moverse por el tablero." << endl;
	cout << "Dependiendo de la casilla en la que caigan, los jugadores pueden:" << endl;
	cout << "- Adquirir una propiedad si está disponible y tienen suficiente dinero." << endl;
	cout << "- Pagar peajes si caen en una casilla especial como 'Puerto', 'Ferrocarril', 'Aeropuerto' o 'Electricidad'." << endl;
	cout << "- Ir a la carcel, pagar una fianza para salir o esperar varios turnos para ser liberados." << endl;
	cout << "- Recibir bonificaciones al pasar por la casilla 'Inicio'." << endl;
	cout << "- Recoger tarjetas que pueden requerir que vayan a una casilla especifica." << endl<< endl;
	cout << "Si otro jugador cae en una casilla propiedad de otro, debe pagar un alquiler al propietario." << endl;
	cout << "El juego continua hasta que solo quede un jugador sin declararse en bancarrota o un jugador llegue a $5000" << endl<<endl;
	cout << "Fin del Juego:" << endl;
	cout << "El juego termina cuando solo queda un jugador en pie o cuando un jugador alcanza un cierto nivel de riqueza." << endl;
	cout << "El jugador restante o el mas rico se declara ganador del juego." << endl;
	system("PAUSE");
}

vector<string> Interface::pedirDatos(){
	vector<string> jugadores;
	string nombre;
	int nPlayers;
	
	system("cls");
	cout << endl << endl;
	cout << "    =========================================================" << endl;
	do{
	cout << "    | Digite numero de jugadores (MAX 4): ";
	cin >> nPlayers;
	}while(nPlayers<2 || nPlayers>4);
	nJugadores = nPlayers;
	cin.ignore();
	for (int i = 0; i < nPlayers; i++){
		cout << "    | Nombre del Jugador " << (i+1) << ": ";
		getline(cin, nombre);
		jugadores.push_back(nombre);
	}
	return jugadores;
}

void Interface::imprimirTablero(lists::Nodo* acceso, vector<string> nombres, int* pagoMovil){
	system("cls");
	//Impresion de bordes
	cout << endl << endl;
	cout << "    ---------------------------------------------------------" << endl;
	cout << "    |      |      |      |      |      |      |      |      |" << endl;
	cout << "    |      |      |      |      |      |      |      |      |" << endl;
	cout << "    ---------------------------------------------------------" << endl;
	cout << "    |      |                                         |      |" << endl;
	cout << "    |      |  Turno de:                              |      |" << endl;
	cout << "    --------                                         --------" << endl;
	cout << "    |      |                                         |      |" << endl;
	cout << "    |      |                                         |      |" << endl;
	cout << "    --------                                         --------" << endl;
	cout << "    |      |                                         |      |" << endl;
	cout << "    |      |                                         |      |" << endl;
	cout << "    --------                                         --------" << endl;
	cout << "    |      |                                         |      |" << endl;
	cout << "    |      |                                         |      |" << endl;
	cout << "    --------                                         --------" << endl;
	cout << "    |      |                                         |      |" << endl;
	cout << "    |      |                                         |      |" << endl;
	cout << "    --------                                         --------" << endl;
	cout << "    |      |                                         |      |" << endl;
	cout << "    |      |                                         |      |" << endl;
	cout << "    ---------------------------------------------------------" << endl;
	cout << "    |      |      |      |      |      |      |      |      |" << endl;
	cout << "    |      |      |      |      |      |      |      |      |" << endl;
	cout << "    ---------------------------------------------------------" << endl;
	
	// Impresion de casillas del tablero
	for (int i = 0; i < 28; i++){
		stringstream ss;
		if(i == 0){
			ss << " HOME ";
		} else if (i == 7 || i == 21){
			ss << "  ??  ";
		} else if (i == 14){
			ss << " JAIL ";
		} else if (i == 4 || i == 11 || i == 18 || i == 25){
			ss << " $" << acceso->price << "  ";
		}else{
			ss << " $" << acceso->price << " ";
		}
		imprimirEnPosicion(acceso->position, 0, acceso->color, ss.str());
		acceso->position.Y++;
		imprimirEnPosicion(acceso->position, 0, 15, "      ");
		acceso = acceso->ant;
	}
	
	// Impresion de nombre jugadores
	for (int i = 0; i < nombres.size(); i++){
		stringstream ss;
		ss << "'*' " << nombres[i];
		imprimirEnPosicion(67, 3+(2*i), i+3, 0, ss.str());
	}
	
	actualizarTablero(acceso, pagoMovil);
}

void Interface::actualizarTablero(int dado, string jugador){
	imprimirEnPosicion(24, 7, 15, 0, "                    ");
	imprimirEnPosicion(24, 7, 15, 0, jugador);
	stringstream ss;
	ss << "Le ha tocado un " << dado << " en el dado!";
	imprimirEnPosicion(18, 9, 15, 0, ss.str());
	pausarPantalla();
}


void Interface::actualizarTablero(lists::Nodo *acceso, int* pagoMovil){
	for (int i =0; i < 28; i++){
		COORD casilla;
		casilla.Y = acceso->position.Y;
		for (int j = 0; j < 4; j++){
			casilla.X = acceso->position.X+1+j;
			if (acceso->isHere[j]){
				imprimirEnPosicion(casilla, j+3, 15, "*");
			} else {
				imprimirEnPosicion(casilla, j+3, 15, " ");
			}
		}
		acceso = acceso->ant;
	}
	
	
	for (int i = 0; i < nJugadores; i++){
		imprimirEnPosicion(62, 3+(2*i), i+3, 0, "    ");
		stringstream ss;
		if (pagoMovil[i] >= 0){
			ss << "$" << pagoMovil[i];
			imprimirEnPosicion(62, 3+(2*i), i+3, 0, ss.str());
		}
	}
}

char* Interface::preguntarJugador(lists::Nodo* acceso, const string& pregunta) {
    static char respuesta[2];
    char tecla = '\0';
    stringstream ss;
    
    ss << "Estas en " << acceso->name;
    imprimirEnPosicion(15,11, 15, 0, ss.str());
    while (true) {
    	imprimirEnPosicion(15, 13, 15, 0, pregunta);
        tecla = _getch(); // Espera a que el usuario presione una tecla

        if (tecla == 'S' || tecla == 's') {
            respuesta[0] = 'S';
            break;
        } else if (tecla == 'N' || tecla == 'n') {
            respuesta[0] = 'N';
            break;
        }
    }
    imprimirEnPosicion(15, 13, 15, 0, "                                   ");
    imprimirEnPosicion(15, 11, 15, 0, "                                   ");
    return respuesta;
}

void Interface::propiedadAdquirida(lists::Nodo* acceso, int tipo, string nombre){
    stringstream ss;
    ss << "Estas en " << acceso->name;
    imprimirEnPosicion(15,11, 15, 0, ss.str());
    
    if (tipo == 0){
    	imprimirEnPosicion(15, 13, 15, 0, "Estas en tu propiedad");
	} else if (tipo == 1){
		ss.str("");
		ss << "Estas en propiedad de: " << nombre;
		imprimirEnPosicion(15 , 13, 15, 0, ss.str());
		ss.str("");
		ss << "Te corresponde pagarle " << "$" << (acceso->price*0.20);
		imprimirEnPosicion(15, 14, 15, 0, ss.str());
	}
	
	pausarPantalla();
    imprimirEnPosicion(15, 13, 15, 0, "                                   ");
    imprimirEnPosicion(15, 11, 15, 0, "                                   ");
    imprimirEnPosicion(15, 14, 15, 0, "                                   ");
}

void Interface::casillaEspecial(lists::Nodo* acceso){
    stringstream ss;
    ss << "Estas en " << acceso->name;
    imprimirEnPosicion(15,11, 15, 0, ss.str());
    
    ss.str("");
    ss << "Te corresponde pagar " << "$" << acceso->price << " de peaje";
    imprimirEnPosicion(15,13,15,0, ss.str());
	pausarPantalla();
    imprimirEnPosicion(15, 13, 15, 0, "                                   ");
    imprimirEnPosicion(15, 11, 15, 0, "                                   ");
}

void Interface::imprimirTarjeta(const char *locations){
	imprimirEnPosicion(15,11, 15, 0, "Has caido en ??");
	imprimirEnPosicion(15,13, 15, 0, "Agarras una tarjeta y...");
	stringstream ss;
	ss << "Te toca moverte hacia " << locations << "!";
	imprimirEnPosicion(15,14, 15, 0, ss.str());
	
	pausarPantalla();
    imprimirEnPosicion(15, 13, 15, 0, "                                   ");
    imprimirEnPosicion(15, 11, 15, 0, "                                   ");
    imprimirEnPosicion(15, 14, 15, 0, "                                   ");
}

void Interface::eliminarJugador(int jugador, string nombre){
	
	stringstream ss;
	ss << "'*' " << nombre << "-> ELIMINADO";
	imprimirEnPosicion(67, 3+(2*jugador), 8, 0, ss.str());
	Sleep(2000);
}

void Interface::ganadorPartida(string nombre){
	imprimirEnPosicion(0,0, 15, 0, "");
	system("cls");
	//Impresion de bordes
	cout << endl << endl;
	cout << "    ---------------------------------------------------------" << endl;
	cout << "    |      |      |      |      |      |      |      |      |" << endl;
	cout << "    |                                                       |" << endl;
	cout << "    |      |      |      |      |      |      |      |      |" << endl;
	cout << "    ---------------------------------------------------------" << endl;
	
	stringstream ss;
	ss << "Ganador: " << nombre; 
	imprimirEnPosicion(25,4, 10, 0, ss.str());
	imprimirEnPosicion(15,7, 15, 0, "");
	system("PAUSE");
}

