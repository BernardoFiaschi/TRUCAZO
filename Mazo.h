#pragma once
#include <vector>
#include <stack>
#include "Carta.h"
using namespace std;


class Mazo
{
private:
    stack<Carta> pilaCartas;
    vector<Carta> cartasJugador;
    vector<Carta> mazoOriginal;
    int cantidadCartasDisponibles;

public:
    Mazo();


bool repartirCartas();

bool darCartas(int cantidad, vector<Carta>& nuevasCartas);

void mostrarCartasJugador() const;

void mostrarCartasDisponibles() const;

void mostrarMazoOriginal() const;

const Carta* getCartasJugador() const;

int getCantidadCartasJugador() const;

int getCantidadCartasDisponibles() const;
};
