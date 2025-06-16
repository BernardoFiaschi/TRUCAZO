#pragma once
#include<string>
#include "Carta.h"
using namespace std;

class Jugador
{
private:
    int _id;
    char _nombre[20];
    int _puntajeTotal;
    int _partidasJugadas;
    vector<Carta> _mano;
    int _jugadasRestantes;
    int _descartesRestantes;
public:
    Jugador();
    Jugador(int id,string nombre,int puntaje,int partidas);

    void agregarCarta(Carta nuevaCarta);
    void mostrarMano() const;
    void jugarCarta(int indice);
    void descartarCarta(int indice);
    void sumarPuntos(int puntos);
    int getId()const;
    string getNombre() const;
    int getPartidasJugadas() const;
    void aumentarPartidas();
    int getPuntajeTotal() const;
};
