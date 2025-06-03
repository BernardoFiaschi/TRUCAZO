#pragma once
#include <vector>
#include <stack>
#include "Carta.h"
using namespace std;

class Mazo {
private:
    stack<Carta> pilaCartas;
    vector<Carta> cartasJugador;
    vector<Carta> mazoOriginal;

public:
    Mazo();
    bool repartirCartas();
    void mostrarCartasJugador() const;
    void mostrarCartasDisponibles() const;
    void mostrarMazoOriginal() const;

    // para hacer funcionar las funciones de mostrar imagenes //

    const Carta* getCartasJugador() const;
    int getCantidadCartasJugador() const;


};
