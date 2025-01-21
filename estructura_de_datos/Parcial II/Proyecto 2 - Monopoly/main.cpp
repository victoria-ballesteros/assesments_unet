#include <iostream>
#include <windows.h>
#include <ctime>
#include <vector>
#include "lists.h"
#include "Interface.h"
#define MAXMONEY 500

lists lista;
lists::Nodo *acceso = NULL;
Interface interfaz;
int pagoMovil[4];
bool gameOver = false;
void start(int _nPlayers);
void init(int _nPlayers);
std::vector<std::string> nombres;
std::vector<lists::Nodo*> accesoJugador;
int random();
void eliminarJugador(int, lists::Nodo *&);
const char* datos[] = {
        "GO TO JAIL",
        "GO TO THE START",
        "GO TO PAY THE ELECTRICITY BILL",
        "GO TO THE RAILWAY",
        "GO TO THE HARBOR",
        "GO TO THE AIRPORT"
};

int main(int argc, char** argv) {
	bool menu = false;
	lista.modificarPrecio();
	do{
		menu = interfaz.menu();
		if (menu){
			acceso = NULL;
			gameOver = false;
			nombres = interfaz.pedirDatos();
			int nPlayers = nombres.size();
			lista.readLoop(acceso, "tablero.txt");
			acceso = acceso->ant;
			init(nPlayers);
		}
	} while(menu); 
}

void init(int _nPlayers)
{
	accesoJugador.resize(_nPlayers);

	for(int i = 0; i < _nPlayers; i++)
	{
		acceso->isHere[i] = true;
		pagoMovil[i] = MAXMONEY;
		accesoJugador[i] = acceso;
	}
	
	start(_nPlayers);
}

void start(int _nPlayers)
{
	int dado, tarjeta, iterador = 0, retirados = 0, diasCarcel[_nPlayers];
	bool seVende = true, ubicacionEncontrada = false, rondaTerminada = false;
	char compra[2], carcel[2];
	
	for (int i=0; i<_nPlayers; i++)
		diasCarcel[i] = 0;
		
	interfaz.imprimirTablero(acceso, nombres, pagoMovil);
	
	// Do while que define las rondas
	do
	{
		// For para cada jugador en la ronda
		for(int i = 0; i < _nPlayers; i++)
		{
			if (pagoMovil[i] < 0) 
				continue;
				
			//Saltarse 
			if((diasCarcel[i] == 0 || diasCarcel[i] == 4) && accesoJugador[i] != NULL) {
				// El jugador no est� en la c�rcel o reci�n sali� de la c�rcel
				diasCarcel[i] = 0;
				seVende = true;
				rondaTerminada = false;
				// Primero tiramos el dado
				dado = random();
				interfaz.actualizarTablero(dado, nombres[i]); //Imprimir numero del dado, turno actual.
				// Quitamos al jugador de la casilla original
				accesoJugador[i]->isHere[i] = false;
				// Movemos al jugador tantas casillas lo indique el dado
				for(int a= 0; a<dado; a++){
					accesoJugador[i] = accesoJugador[i]->ant;
					if(strcmpi(accesoJugador[i]->name, "HOME") == 0)
						pagoMovil[i] += 200;
				}
				// Ubicamos al jugador en la nueva casilla
				accesoJugador[i]->isHere[i] = true;
				
				interfaz.actualizarTablero(acceso, pagoMovil); //Imprimir movimiento, actualiza precio.
				
				// If para verificar ??, cayendo en una de las casillas principales
				if (strcmpi(accesoJugador[i]->name, "??") == 0) {
					ubicacionEncontrada = false;
					iterador = 0;
				    tarjeta = random();
				    const char *locations[] = {"JAIL", "HOME", "ELECTRICITY", "RAILWAY", "HARBOR", "AIRPORT"};
				    accesoJugador[i]->isHere[i] = false;
				    do {
				    	iterador++;
				        accesoJugador[i] = accesoJugador[i]->ant;
				        if (strcmpi(accesoJugador[i]->name, locations[tarjeta - 1]) == 0) {
				            accesoJugador[i]->isHere[i] = true;
				            ubicacionEncontrada = true;
				        }
				    } while (!ubicacionEncontrada && iterador < 28);
					interfaz.imprimirTarjeta(locations[tarjeta-1]);
					interfaz.actualizarTablero(acceso, pagoMovil); 
				}
				
				if(!rondaTerminada){
					// Revisamos si el jugador est� en una de las casillas especiales para que pague
					const char* casillasEspeciales[] = { "HARBOR", "RAILWAY", "AIRPORT", "ELECTRICITY" };
					for (int j=0; j<4; j++){
						if(strcmpi(accesoJugador[i]->name, casillasEspeciales[j]) == 0){
							interfaz.casillaEspecial(accesoJugador[i]);
							if(!(pagoMovil[i] >= accesoJugador[i]->price)){
									accesoJugador[i] == NULL;
									retirados++;
									eliminarJugador(i, accesoJugador[i]);
							}
							pagoMovil[i] -= accesoJugador[i]->price;
							rondaTerminada = true;
						}
					}
					
					if(strcmpi(accesoJugador[i]->name, "JAIL") == 0){
						
						if (pagoMovil[i] >= accesoJugador[i]->price){
							std::string respuestaStr = interfaz.preguntarJugador(accesoJugador[i], "Desea pagar $150 para salir? (S/N)");
							strcpy(compra, respuestaStr.c_str());
							
							if(strcmpi(compra, "S") == 0){
								pagoMovil[i] -= accesoJugador[i]->price;
							}else {
								diasCarcel[i] ++;
							}
							
						}else {
							diasCarcel[i] ++;
						}
						rondaTerminada = true;
					}
					
					if(strcmpi(accesoJugador[i]->name, "HOME") == 0){
						pagoMovil[i]+=200;
						rondaTerminada = true;
					}
				}
				
				if(!rondaTerminada){
					// For para ver si alg�n jugador s tiene una casa en la posici�n
					for(int s = 0; s < _nPlayers; s++){
						if(accesoJugador[i]->houseHere[s]){
							seVende = false;
							if(s == i){
								interfaz.propiedadAdquirida(accesoJugador[i], 0, nombres[s]);
								break;
							}else{
								interfaz.propiedadAdquirida(accesoJugador[i], 1, nombres[s]);
								int montoFinal = accesoJugador[i]->price * 0.20;
								if(pagoMovil[i] >= montoFinal){
									pagoMovil[s] += montoFinal;
									pagoMovil[i] -= montoFinal;
									break;
								}else{
									accesoJugador[i] == NULL;
									retirados++;
									eliminarJugador(i, accesoJugador[i]);
								}
							}
						}
					}
					
					if(seVende){
						// Preguntamos si quiere comprar la propiedad
						if (pagoMovil[i] >= accesoJugador[i]->price){
							std::string respuestaStr = interfaz.preguntarJugador(accesoJugador[i], "Desea comprar esta propiedad? (S/N)");
							strcpy(compra, respuestaStr.c_str());
							if((strcmpi(compra, "S") == 0)){
								// El jugador adquiere la casa
								pagoMovil[i] -= accesoJugador[i]->price;
								accesoJugador[i]->houseHere[i] = true;
							}
						}
					}
				}
			}else if(accesoJugador[i] == NULL){
				// EL JUGADOR NO EXISTE
				
			}else if(diasCarcel[i] > 0 && diasCarcel[i] < 4 && accesoJugador[i] != NULL){ // Jugador en la carcel
				diasCarcel[i]++;
			}
			
			interfaz.actualizarTablero(acceso, pagoMovil);
			
			if(_nPlayers - retirados == 1 || pagoMovil[i] > 5000){
				gameOver = true;
				if(pagoMovil[i] > 5000){
					interfaz.ganadorPartida(nombres[i]);
				}else{
					int maximo = 0;
					for(int a = 0; a < _nPlayers; a++){
						if (pagoMovil[a] > maximo) {
				            maximo = a;
				        }
					}
					interfaz.ganadorPartida(nombres[maximo]);
				}
				break;
			}
		} // Aqu� termina el turno de un jugador
	}
	while(!gameOver);
	// Juego terminado
}

int random()
{
	std::srand(std::time(0));
	return std::rand()%6+1;
}

void eliminarJugador(int jugador, lists::Nodo *&acceso){
	acceso->isHere[jugador] = false;
	for (int i = 0; i < 28; i++){
		if (acceso->houseHere[jugador])
			acceso->houseHere[jugador] = false;
		acceso = acceso->ant;
	}
	interfaz.eliminarJugador(jugador, nombres[jugador]);
}

