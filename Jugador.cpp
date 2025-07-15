#include<iostream>
#include<cstring>
#include "Jugador.h"
#include "Carta.h"
using namespace std;

Jugador::Jugador() : _id(0), _nombre(""), _puntajeTotal(0), _partidasJugadas(0), _puntajeMaximo(0) {}

Jugador::Jugador(int id, string nombre, int puntaje, int partidas)
{
    _id = id;
    strncpy(_nombre, nombre.c_str(), sizeof(_nombre) - 1);
    _nombre[sizeof(_nombre) - 1] = '\0';
    _puntajeTotal = puntaje;
    _partidasJugadas = partidas;
    _puntajeMaximo = 0;
}

void Jugador::sumarPuntos(int puntos)
{
    _puntajeTotal += puntos;
}

void Jugador::actualizarPuntajeMaximo(int puntajePartida)
{
    if (puntajePartida > _puntajeMaximo)
        _puntajeMaximo = puntajePartida;
}

int Jugador::getId() const { return _id; }

string Jugador::getNombre() const { return _nombre; }

int Jugador::getPartidasJugadas() const { return _partidasJugadas; }

int Jugador::getPuntajeTotal() const { return _puntajeTotal; }

int Jugador::getPuntajeMaximo() const { return _puntajeMaximo; }

void Jugador::aumentarPartidas()
{
    _partidasJugadas++;
}

