#include <iostream>
#include "Carta.h"

using namespace std;

/*
    Constructor por defecto de Carta
    Para que: poder crear una carta vac¡a (por ejemplo al limpiar la mano).
    Como: inicializa todos los atributos con valores neutros (0 o string vac¡o).
*/
Carta::Carta()
{
    numero = 0;
    palo = "";
    idCarta = 0;
    valor = 0;
}

/*
    Constructor con par metros
    Para que: crear una carta con datos concretos (por ejemplo al armar el mazo original).
    Como: recibe el n£mero (1 a 12), el palo (espada, basto, etc.),
          un ID de imagen (para graficarla), y el valor de juego que se usar  en las jugadas.
*/
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

