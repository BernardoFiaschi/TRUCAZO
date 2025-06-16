#include<iostream>
#include<cstring>
#include "Jugador.h"
#include "Carta.h"
using namespace std;

Jugador::Jugador() : _id(0), _nombre(""), _puntajeTotal(0), _partidasJugadas(0),
                     _jugadasRestantes(3), _descartesRestantes(2) {}

Jugador::Jugador(int id,string nombre,int puntaje,int partidas)
{
    _id=id;
    strncpy(_nombre,nombre.c_str(),sizeof(_nombre)-1);
    _nombre[sizeof(_nombre)-1]='\0';
    _puntajeTotal = puntaje;
    _partidasJugadas=partidas;
    _jugadasRestantes = 3;
    _descartesRestantes = 2;

}
void Jugador::agregarCarta(Carta nuevaCarta)
{
    _mano.push_back(nuevaCarta);
}
void Jugador::mostrarMano()const
{
  cout<<""<<_nombre<<"";
  for(const Carta& c : _mano)
  {
      c.mostrar();
  }
}

void Jugador::jugarCarta(int indice)
{
  if(indice>=0 && indice <_mano.size() && _jugadasRestantes > 0)
  {
      _puntajeTotal += _mano[indice].getValor();
      _mano.erase(_mano.begin() + indice);
      _jugadasRestantes--;
  }
}
void Jugador::descartarCarta(int indice)
{
  if(indice>= 0 && indice < _mano.size() && _descartesRestantes > 0)
  {
      _mano.erase(_mano.begin() + indice);
      _descartesRestantes--;
  }
}

void Jugador::sumarPuntos(int puntos)
{
    _puntajeTotal +=puntos;
}
int Jugador::getId()const
{
    return _id;
}
string Jugador::getNombre()const
{
    return _nombre;
}
int Jugador::getPartidasJugadas() const
{
    return _partidasJugadas;
}
void Jugador::aumentarPartidas()
{
    _partidasJugadas++;
}
int Jugador::getPuntajeTotal()const
{
  return _puntajeTotal;
}
