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

    // --- FUNCIONES AUXILIARES PRIVADAS ---
    void dibujarMazoCartas(sf::RenderWindow& ventana);
    void esperarTecla(sf::RenderWindow& ventana);

public:
    Manager();
    void mostrarMenu(sf::RenderWindow& ventana);
    void mostrarMazo(sf::RenderWindow& ventana);
    void iniciarPartida(sf::RenderWindow& ventana);
    void mostrarMensaje(sf::RenderWindow& ventana,const std::string& mensaje);
    void finalizarRonda(sf::RenderWindow& ventana,bool victoria,Partida& partida);
    void mostrarCreditos(sf::RenderWindow& ventana);
};