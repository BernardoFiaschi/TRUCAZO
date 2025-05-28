#pragma once
#include <vector>
#include "Carta.h"
using namespace std;

class Mazo {
private:
    vector<Carta> cartas;                       // Almacena las 40 cartas del mazo //
    vector<Carta> cartasJugador;                // Almacena las 5 cartas que se le reparten al jugador //
    vector<Carta> mazoOriginal;                 // Para mostrar el mazo en orden //

public:
    Mazo();                                     // Constructor que carga las 40 cartas y reparte 5 aleatorias //
    void mostrarCartasJugador() const;          // Muestra las 5 cartas repartidas //
    bool repartirCartas();                      // Reparte las cartas //
    void mostrarCartasDisponibles() const;
    void mostrarMazoOriginal() const;
};


