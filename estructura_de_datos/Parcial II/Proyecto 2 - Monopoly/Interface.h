#ifndef INTERFACE_H
#define INTERFACE_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <windows.h>
#include <conio.h>
#include "lists.h"

class Interface {
public:
	int nJugadores;
	
	bool menu();
	void imprimirReglas();
	std::vector<std::string> pedirDatos();
	void imprimirTablero(lists::Nodo* acceso, std::vector<std::string> nombres, int* pagoMovil);
	void pausarPantalla();
	void imprimirEnPosicion(COORD posicion, int textColor, int backgroundColor, const std::string texto);
	void imprimirEnPosicion(int x, int y, int textColor, int backgroundColor, const std::string texto);
	void actualizarTablero(int dado, std::string jugador);
	void actualizarTablero(lists::Nodo *acceso, int* pagoMovil);
	char* preguntarJugador(lists::Nodo *acceso, const std::string& pregunta);
	void propiedadAdquirida(lists::Nodo* acceso, int tipo, std::string nombre);
	void casillaEspecial(lists::Nodo* acceso);
	void imprimirTarjeta(const char *locations);
	void eliminarJugador(int jugador, std::string nombre);
	void ganadorPartida(std::string nombre);
};

#endif
