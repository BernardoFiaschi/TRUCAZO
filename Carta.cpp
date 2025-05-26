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


vector<Carta> listarCartasMazo()
    {
    vector<Carta> cartas =
    {
        Carta(1, "espada", 1, 50),
        Carta(1, "basto", 2, 35),
        Carta(7, "espada", 3, 30),
        Carta(7, "oro", 4, 25),
        Carta(3, "espada", 5, 20),
        Carta(3, "basto", 6, 20),
        Carta(3, "oro", 7, 20),
        Carta(3, "copa", 8, 20),
        Carta(2, "espada", 9, 15),
        Carta(2, "basto", 10, 15),
        Carta(2, "oro", 11, 15),
        Carta(2, "copa", 12, 15),
        Carta(1, "oro", 13, 11),
        Carta(1, "copa", 14, 11),
        Carta(12, "espada", 15, 10),
        Carta(12, "basto", 16, 10),
        Carta(12, "oro", 17, 10),
        Carta(12, "copa", 18, 10),
        Carta(11, "espada", 19, 9),
        Carta(11, "basto", 20, 9),
        Carta(11, "oro", 21, 9),
        Carta(11, "copa", 22, 9),
        Carta(10, "espada", 23, 8),
        Carta(10, "basto", 24, 8),
        Carta(10, "oro", 25, 8),
        Carta(10, "copa", 26, 8),
        Carta(7, "basto", 27, 7),
        Carta(7, "copa", 28, 7),
        Carta(6, "espada", 29, 6),
        Carta(6, "basto", 30, 6),
        Carta(6, "oro", 31, 6),
        Carta(6, "copa", 32, 6),
        Carta(5, "espada", 33, 5),
        Carta(5, "basto", 34, 5),
        Carta(5, "oro", 35, 5),
        Carta(5, "copa", 36, 5),
        Carta(4, "espada", 37, 4),
        Carta(4, "basto", 38, 4),
        Carta(4, "oro", 39, 4),
        Carta(4, "copa", 40, 4)
    };
    return cartas;
    }
