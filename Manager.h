#pragma once
#include "Menu.h"
#include "Partida.h"
#include "Jugador.h"
#include <SFML/Audio.hpp>

class Manager
{
    Jugador jugador;
    Mazo mazo;
    void dibujarMazoCartas(sf::RenderWindow& ventana);
    void esperarTecla(sf::RenderWindow& ventana);
    void dibujarComodines(sf::RenderWindow& ventana);

public:
    Manager();
    void mostrarMenu(sf::RenderWindow& ventana);
    void mostrarMazo(sf::RenderWindow& ventana);
    std::string pedirNombre(sf::RenderWindow& ventana);
    void iniciarPartida(sf::RenderWindow& ventana);
    void finalizarRonda(sf::RenderWindow& ventana,bool victoria,Partida& partida);
    void mostrarCreditos(sf::RenderWindow& ventana);
    void listarJugadores(sf::RenderWindow& ventana);
    void actualizarJugador();
    Jugador& getJugador();
    void mostrarMazoComodines(sf::RenderWindow& ventana);
};
