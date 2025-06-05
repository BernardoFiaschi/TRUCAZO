#pragma once
#include <SFML/Graphics.hpp>
#include "Carta.h"
using namespace std;

void seleccionarCartasJugador(sf::RenderWindow& ventana,
                               const Carta cartas[], int cantidad,
                               int ronda, int objetivo, int puntajeActual,
                               int& c1, int& c2, int& c3, int& c4,
                               int jugadasRestantes, int descartesRestantes, int cartasEnMazo, int& accion);
