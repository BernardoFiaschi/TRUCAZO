#include "imagenes.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
using namespace std;

                                                                            // Funci¢n que abre una ventana con SFML y muestra las cartas gr ficamente //
void mostrarCartasJugadorVisual(const Carta cartasJugador[], int cantidad)
{
                                                                            // Creamos una ventana de 800x600 p¡xeles //
    sf::RenderWindow ventana(sf::VideoMode(900, 600), "Cartas del Jugador");

    sf::Texture texturas[5];                                                // Hasta 5 texturas para 5 cartas //
    sf::Sprite sprites[5];                                                  // Sprites para representar visualmente las texturas //

    for (int i = 0; i < cantidad; i++)
    {
                                                                            // Obtenemos los datos de la carta //
        int numero = cartasJugador[i].getNumero();
        string palo = cartasJugador[i].getPalo();

                                                                            // Armamos el nombre de carpeta: "Espada", "Oro", etc. //
        string nombreCarpeta = string(1, toupper(palo[0])) + palo.substr(1);

                                                                            // Armamos la ruta al archivo de imagen correspondiente //
        stringstream ruta;
        ruta << "C:/Users/berna/OneDrive/Desktop/PROYECTO FINAL TRUCAZO/pixelDeck/"
             << nombreCarpeta << "/" << palo << numero << ".png";

                                                                            // Cargamos la textura desde archivo //
        if (!texturas[i].loadFromFile(ruta.str()))
        {
            cout << "Falta " << ruta.str() << endl;                         // Avisamos si no se encuentra la imagen //
        }

                                                                            // Asignamos la textura al sprite y lo posicionamos horizontalmente //
        sprites[i].setTexture(texturas[i]);
        sprites[i].setScale(1.5f, 1.5f);                                    // Aumentamos el tama¤o de la carta un 50% //
        sprites[i].setPosition(85 + i * 160, 425);                          // Separamos las cartas para que quede mas prolijo //
    }

                                                                            // Loop principal de la ventana //
    while (ventana.isOpen())
    {
        sf::Event e;
        while (ventana.pollEvent(e))
            if (e.type == sf::Event::Closed) ventana.close();

        ventana.clear();                                                    // Limpiamos la pantalla //
        for (int i = 0; i < cantidad; i++)                                  // Dibujamos las cartas una por una //
            ventana.draw(sprites[i]);
        ventana.display();                                                  // Mostramos el contenido final //
    }
}
