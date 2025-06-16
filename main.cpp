#include "Carta.h"
#include "manager.h"
#include "Mazo.h"
#include <iostream>
#include "menu.h"
#include "Sonidos.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace std;

int main()
{
    sf::RenderWindow ventana(sf::VideoMode(900, 600), "TRUCAZO");
    ventana.setFramerateLimit(60);
    Menu menu(ventana);
    menu.ejecutar();
    return 0;
}

