#include "Carta.h"
#include "Manager.h"
#include "Mazo.h"
#include "Menu.h"
#include "Sonidos.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
using namespace std;


int main()
{
    srand(time(nullptr));
    sf::RenderWindow ventana(sf::VideoMode(900, 600), "TRUCAZO");
    ventana.setFramerateLimit(60);

    sf::Image icono;
    if (!icono.loadFromFile("iconos/icono.png"))
    {
        cerr << "No se pudo cargar el icono de la ventana." << endl;
    }
    else
    {
        ventana.setIcon(icono.getSize().x, icono.getSize().y, icono.getPixelsPtr());
    }
    Menu menu(ventana);
    menu.ejecutar();

    return 0;
}

