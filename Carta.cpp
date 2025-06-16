#include "Carta.h"
#include <iostream>
#include <vector>
using namespace std;

Carta::Carta()
{
    numero = 0;
    palo = "";
    idCarta = 0;
    valor = 0;
}

Carta::Carta(int num, string p, int id, int pts)
{
    numero = num;
    palo = p;
    idCarta = id;
    valor = pts;
}

int Carta::getNumero() const { return numero; }
string Carta::getPalo() const { return palo; }
int Carta::getIdCarta() const { return idCarta; }
int Carta::getValor() const { return valor; }

void Carta::mostrar() const
{
    cout << numero << " de " << palo << " | Puntaje: " << valor << " | ID: " << idCarta << endl;
}
