#pragma once
#include <SFML/Graphics.hpp>
#include "Carta.h"
#include "Jugador.h"
#include "Comodin.h"


void seleccionarCartasJugador(sf::RenderWindow& ventana,
                              const Carta* cartas, int cantidad,
                              int ronda, int objetivo, int puntajeActual,
                              int& c1, int& c2, int& c3, int& c4,
                              int jugadas, int descartes, int cartasEnMazo,
                              int& jugadasRestantes, int& descartesRestantes,
                              int& accion,
                              const Jugador& jugador,
                              const std::string& jugadaActualTexto,
                              const std::vector<Comodin>& comodinesActivos,
                              int rondasGanadas);


void mostrarSeleccion(sf::RenderWindow& ventana, sf::Sprite* sprites, bool* seleccionadas, int cantidad);

void cargarTexturasCartas(const Carta* cartas, int cantidad, sf::Texture* texturas, sf::Sprite* sprites);
