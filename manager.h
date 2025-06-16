#pragma once
#include "menu.h"
#include "Partida.h"
#include "Jugador.h"
#include <SFML/Audio.hpp>
class Manager
{
    Jugador jugador;
    Partida partida;
    Mazo mazo;
public:
    Manager();
    void mostrarMenu(sf::RenderWindow& ventana);
    void mostrarMazo(sf::RenderWindow& ventana);
    void iniciarPartida(sf::RenderWindow& ventana);
    void mostrarMensaje(sf::RenderWindow& ventana,const std::string& mensaje);
    void finalizarRonda(sf::RenderWindow& ventana,bool victoria,Partida& partida);
    void mostrarCreditos(sf::RenderWindow& ventana);
};
