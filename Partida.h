#pragma once
#include <vector>
#include "Carta.h"
#include "Mazo.h"
#include <SFML/Graphics.hpp>
using namespace std;

class Partida
{
private:
    int rondaActual;
    int puntajesObjetivo[15];
    int puntajeTotal;
    int puntajeRonda;
    int jugadasRestantes;
    int descartesRestantes;
    std::vector<Carta> mano;
    Mazo mazo;

public:

Partida();

void iniciar();

void iniciarRonda(sf::RenderWindow& ventana);

void jugarCartas(const std::vector<int>& seleccion);

void descartarCartas(const std::vector<int>& seleccion);

void rellenarMano();

bool verificarVictoria();

void mostrarMensaje(sf::RenderWindow& ventana, const std::string& mensaje);

void finalizarRonda(sf::RenderWindow& ventana, bool victoria);
};
