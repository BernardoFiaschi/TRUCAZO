#pragma once
#include <iostream>
#include <string>
#include "Jugador.h"

class ArchivoJugador {
private:
    std::string _nombreArchivo = "Jugadores.dat";

public:
    ArchivoJugador();
    bool guardarJugador(const Jugador& jugador);
    bool guardarJugador(const Jugador& jugador, int posicion);
    int getCantidadJugadores();
    Jugador leer(int posicion);
    int buscarJugadorPorId(int id);
    Jugador buscarJugador(const std::string& nombre);
};
