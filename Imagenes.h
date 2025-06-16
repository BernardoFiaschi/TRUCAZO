#pragma once
#include <SFML/Graphics.hpp>
#include "Carta.h"
using namespace std;

// No hay helpers expuestos aquí, los auxiliares se dejan en el cpp

void seleccionarCartasJugador(sf::RenderWindow& ventana,
                              const Carta* cartas, int cantidad,
                              int ronda, int objetivo, int puntajeActual,
                              int& c1, int& c2, int& c3, int& c4,
                              int jugadas, int descartes, int cartasEnMazo,
                              int& jugadasRestantes, int& descartesRestantes,
                              int& accion,
                              const string& jugadaActualTexto);