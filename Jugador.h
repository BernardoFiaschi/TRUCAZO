#pragma once
#include<string>
#include<vector>
#include "Carta.h"


class Jugador
{
private:
    int _id;
    char _nombre[20];
    int _puntajeTotal;
    int _partidasJugadas;
    int _puntajeMaximo;
    std::vector<Carta> _mano;

public:
    Jugador();
    Jugador(int id,std::string nombre,int puntaje,int partidas);
    void sumarPuntos(int puntos);
    void actualizarPuntajeMaximo(int puntajePartida);
    int getId()const;
    std::string getNombre() const;
    int getPartidasJugadas() const;
    void aumentarPartidas();
    int getPuntajeTotal() const;
    int getPuntajeMaximo() const;
};
