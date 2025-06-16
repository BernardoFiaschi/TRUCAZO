#pragma once
#include "Jugador.h"
#include "Mazo.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
using namespace std;

class Partida
{
private:
    Jugador _jugador;
    int rondaActual;
    int puntajesObjetivo[15];
    int puntajeTotal;
    int puntajeRonda;
    int jugadasRestantes;
    int descartesRestantes;
    string jugadaActualTexto;
    vector<Carta> mano;
    Mazo mazo;

    // --- FUNCIONES AUXILIARES PRIVADAS ---
    void inicializarRonda();
    bool procesarTurno(sf::RenderWindow& ventana, bool& victoria);
    void finalizarRonda(sf::RenderWindow& ventana, bool victoria);
    vector<Carta> obtenerCartasSeleccionadas(const vector<int>& seleccion);
    void limpiarCartasUsadas(const vector<int>& seleccion);
    void limpiarCartasDescartadas(const vector<int>& seleccion);
    vector<int> obtenerIndicesHuecosMano();
    vector<Carta> obtenerCartasParaHuecos(int cantidad);
    void rellenarHuecos(const vector<int>& vacios, const vector<Carta>& nuevas);

public:
    Partida();
    Partida(Jugador jugador);

    void iniciar(sf::RenderWindow& ventana);
    void iniciarRonda(sf::RenderWindow& ventana);
    void jugarCartas(const vector<int>& seleccion);
    void descartarCartas(const vector<int>& seleccion);
    void rellenarMano();

    int getPuntajeTotal() const { return puntajeTotal; }
    bool verificarVictoria();
    int getPuntajeRonda() const;
    int getRondaActual() const;
    string getJugadaActualTexto() const { return jugadaActualTexto; }
};