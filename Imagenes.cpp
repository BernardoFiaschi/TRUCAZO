#include "Imagenes.h"
#include <iostream>
using namespace std;

                                                                                                // Renderiza la pantalla de seleccion de cartas usando SFML //
                                                                                                // Resalta las cartas seleccionadas, muestra informacion de ronda y recibe interaccion del usuario //
void seleccionarCartasJugador(sf::RenderWindow& ventana,
                               const Carta cartas[], int cantidad,
                               int ronda, int objetivo, int puntajeActual,
                               int& c1, int& c2, int& c3, int& c4,
                               int jugadasRestantes, int descartesRestantes, int cartasEnMazo, int& accion)
{
    sf::Font fuente;
    fuente.loadFromFile("C:/Windows/Fonts/arial.ttf");

    sf::Text texto;
    texto.setFont(fuente);
    texto.setCharacterSize(20);
    texto.setFillColor(sf::Color::White);
    texto.setPosition(20, 20);

    sf::Text info;
    info.setFont(fuente);
    info.setCharacterSize(22);
    info.setFillColor(sf::Color::Cyan);
    info.setPosition(20, 60);

    sf::Texture texturas[5];
    sf::Sprite sprites[5];
    bool seleccionadas[5] = { false, false, false, false, false };
    int seleccion[4] = { -1, -1, -1, -1 };

    for (int i = 0; i < cantidad; i++)
    {
        string ruta = "cartas/" + to_string(cartas[i].getIdCarta()) + ".png";
        texturas[i].loadFromFile(ruta);
        sprites[i].setTexture(texturas[i]);
        sprites[i].setScale(1.5f, 1.5f);
        sprites[i].setPosition(85 + i * 160, 300);
    }

    bool terminar = false;
    while (!terminar && ventana.isOpen())
    {
        sf::Event event;
        while (ventana.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                ventana.close();

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code >= sf::Keyboard::Num1 && event.key.code <= sf::Keyboard::Num5)
                {
                    int idx = event.key.code - sf::Keyboard::Num1;
                    if (seleccionadas[idx])
                    {
                        seleccionadas[idx] = false;
                        for (int i = 0; i < 4; i++) if (seleccion[i] == idx) seleccion[i] = -1;
                    } else
                        {
                        for (int i = 0; i < 4; i++)
                            {
                                if (seleccion[i] == -1)
                                {
                                seleccion[i] = idx;
                                seleccionadas[idx] = true;
                                break;
                                }
                            }
                        }
                }
                if (event.key.code == sf::Keyboard::Enter)
                {
                    accion = 1;
                    tie(c1, c2, c3, c4) = make_tuple(seleccion[0], seleccion[1], seleccion[2], seleccion[3]);
                    terminar = true;
                }
                if (event.key.code == sf::Keyboard::BackSpace)
                {
                    accion = -1;
                    tie(c1, c2, c3, c4) = make_tuple(seleccion[0], seleccion[1], seleccion[2], seleccion[3]);
                    terminar = true;
                }
            }
        }

        ventana.clear(sf::Color::Black);

        texto.setString("Selecciona con 1-5 (max 4). ENTER = jugar | BACKSPACE = descartar");
        info.setString("Ronda " + to_string(ronda) + " | Objetivo: " + to_string(objetivo) + " | Jugadas: " + to_string(jugadasRestantes) + " | Desc: " + to_string(descartesRestantes) + " | Mazo: " + to_string(cartasEnMazo) +
                       " | Puntaje actual: " + to_string(puntajeActual));

        ventana.draw(texto);
        ventana.draw(info);

        for (int i = 0; i < cantidad; i++)
        {
            ventana.draw(sprites[i]);
            if (seleccionadas[i])
            {
                sf::FloatRect b = sprites[i].getGlobalBounds();
                sf::RectangleShape marco(sf::Vector2f(b.width, b.height));
                marco.setPosition(b.left, b.top);
                marco.setFillColor(sf::Color::Transparent);
                marco.setOutlineColor(sf::Color::Red);
                marco.setOutlineThickness(5);
                ventana.draw(marco);
            }
        }

        ventana.display();
    }
}
