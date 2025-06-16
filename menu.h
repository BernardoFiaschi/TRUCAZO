#pragma once
#include "Sonidos.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
using namespace std;

class Manager; // Forward declaration para evitar include circular

class Menu
{
private:
    sf::RenderWindow& ventana;
    sf::Font fuente;
    vector<sf::Text> opciones;
    sf::Text titulo;
    sf::Texture texturaFondo;
    sf::Sprite spriteFondo;
    int opcionSeleccionada;

    // --- FUNCIONES AUXILIARES PRIVADAS ---
    void dibujarMenu();
    void gestionarEventos(Manager& cargar, bool& terminar);

public:
    Menu(sf::RenderWindow& v);
    void ejecutar();
};