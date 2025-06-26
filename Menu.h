#pragma once
#include "Sonidos.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <vector>


class Manager;

class Menu
{
private:
    sf::RenderWindow& ventana;
    sf::Font fuente;
    std::vector<sf::Text> opciones;
    sf::Text titulo;
    sf::Texture texturaFondo;
    sf::Sprite spriteFondo;
    int opcionSeleccionada;
    void dibujarMenu();
    void gestionarEventos(Manager& cargar);

public:
    Menu(sf::RenderWindow& v);
    void ejecutar();
};
