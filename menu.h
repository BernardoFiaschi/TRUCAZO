#pragma once
#include "Sonidos.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include<vector>
using namespace std;

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
public:
    Menu(sf::RenderWindow& v);
    void ejecutar();
};
