#pragma once
#include <vector>
#include "Carta.h"
#include "Mazo.h"
#include "Jugador.h"
#include "Sonidos.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace std;

class Partida
{
private:
    Jugador _jugador;
    int rondaActual;
    int puntajesObjetivo[15];
    int puntajeTotal;
    int puntajeRonda;
    int jugadasRestantes;
    int descartesRestantes;
    string jugadaActualTexto;
    vector<Carta> mano;
    Mazo mazo;

public:

Partida();
Partida(Jugador jugador);

void iniciar(sf::RenderWindow& ventana);

void iniciarRonda(sf::RenderWindow& ventana);

void jugarCartas(const vector<int>& seleccion);

void descartarCartas(const vector<int>& seleccion);

void rellenarMano();

int getPuntajeTotal() const { return puntajeTotal; }

bool verificarVictoria();
int getPuntajeRonda() const;
int getRondaActual() const;
string getJugadaActualTexto() const { return jugadaActualTexto; }


};
