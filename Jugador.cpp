#include<iostream>
#include<cstring>
#include "Jugador.h"
#include "Carta.h"
using namespace std;

/*
   Constructor por defecto del jugador
   Para que: inicializar un jugador vacio con valores en cero
   Como: asigna ID 0, nombre vacio, puntaje 0, sin partidas jugadas y sin puntaje maximo
*/
Jugador::Jugador() : _id(0), _nombre(""), _puntajeTotal(0), _partidasJugadas(0), _puntajeMaximo(0) {}

/*
   Constructor con parametros
   Para que: crear un jugador nuevo con nombre y datos iniciales
   Como: recibe ID, nombre, puntaje total y cantidad de partidas jugadas
*/
Jugador::Jugador(int id, string nombre, int puntaje, int partidas)
{
    _id = id;
    strncpy(_nombre, nombre.c_str(), sizeof(_nombre) - 1); // Copia el string al array char
    _nombre[sizeof(_nombre) - 1] = '\0'; // Asegura terminacion
    _puntajeTotal = puntaje;
    _partidasJugadas = partidas;
    _puntajeMaximo = 0; // Por defecto se arranca sin puntaje maximo
}

/*
   Suma puntos al puntaje total del jugador
   Para que: acumular el total a lo largo de todas las partidas
*/
void Jugador::sumarPuntos(int puntos)
{
    _puntajeTotal += puntos;
}

/*
   Verifica si el puntaje actual supera al puntaje maximo anterior
   Para que: registrar la mejor puntuacion obtenida en una sola partida
*/
void Jugador::actualizarPuntajeMaximo(int puntajePartida)
{
    if (puntajePartida > _puntajeMaximo)
        _puntajeMaximo = puntajePartida;
}

/* Getter del ID del jugador */
int Jugador::getId() const { return _id; }

/* Devuelve el nombre del jugador */
string Jugador::getNombre() const { return _nombre; }

/* Devuelve cuantas partidas jugo este jugador */
int Jugador::getPartidasJugadas() const { return _partidasJugadas; }

/* Devuelve el puntaje acumulado de todas las partidas */
int Jugador::getPuntajeTotal() const { return _puntajeTotal; }

/* Devuelve el mayor puntaje obtenido en una sola partida */
int Jugador::getPuntajeMaximo() const { return _puntajeMaximo; }

/*
   Suma 1 al contador de partidas jugadas
   Para que: llevar registro de cuantas veces jugo el jugador
*/
void Jugador::aumentarPartidas()
{
    _partidasJugadas++;
}

