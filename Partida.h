#pragma once
#include "Jugador.h"
#include "Mazo.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>


class Partida
{
private:
    Jugador& _jugador;
    int rondaActual;
    int puntajesObjetivo[15];
    int puntajeTotal;
    int puntajeRonda;
    int jugadasRestantes;
    int descartesRestantes;
    std::string jugadaActualTexto;
    std::vector<Carta> mano;
    std::vector<Carta> cartasExtra;
    Mazo mazo;
    std::vector<Comodin> comodinesSeleccionados;
    int rondasGanadas;
    std::vector<Comodin> comodinesActivos;
    void inicializarRonda();
    bool procesarTurno(sf::RenderWindow& ventana, bool& victoria);
    std::vector<Carta> obtenerCartasSeleccionadas(const std::vector<int>& seleccion);
    void limpiarCartas(const std::vector<int>& seleccion);
    std::vector<int> obtenerIndicesHuecosMano();
    std::vector<Carta> obtenerCartasParaHuecos(int cantidad);
    void rellenarHuecos(const std::vector<int>& vacios, const std::vector<Carta>& nuevas);

public:
    Partida(Jugador& jugador);
    void iniciar(sf::RenderWindow& ventana);
    void iniciarRonda(sf::RenderWindow& ventana);
    void jugarCartas(const std::vector<int>& seleccion);
    void descartarCartas(const std::vector<int>& seleccion);
    void rellenarMano();
    int getPuntajeTotal() const
    {
        return puntajeTotal;
    }
    int getPuntajeRonda() const;
    int getRondaActual() const;
    bool verificarVictoria();
    std::string getJugadaActualTexto() const
    {
        return jugadaActualTexto;
    }
};
