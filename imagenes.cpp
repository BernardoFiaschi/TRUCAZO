#include "Imagenes.h"
#include "Jugadas.h"
#include "Partida.h"
#include "Sonidos.h"
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Renderiza la pantalla de selecci¢n de cartas usando SFML.
// Muestra fondo, cartas, puntajes, jugada actual y permite seleccionar hasta 4 cartas para jugar o descartar.
void seleccionarCartasJugador(sf::RenderWindow& ventana,
                               const Carta* cartas, int cantidad,
                               int ronda, int objetivo, int puntajeActual,
                               int& c1, int& c2, int& c3, int& c4,
                               int jugadas, int descartes, int cartasEnMazo,
                               int& jugadasRestantes, int& descartesRestantes,
                               int& accion,
                               const string& jugadaActualTexto)
{
    // Cargar imagen de fondo
    sf::Texture fondoTextura;
    if (!fondoTextura.loadFromFile("fondos/FONDOTRUCAZO.png")) {
        cerr << "No se pudo cargar la imagen de fondo." << endl;
    }
    sf::Sprite fondoSprite(fondoTextura);

    // Fuente
    sf::Font fuente;
    fuente.loadFromFile("C:/Windows/Fonts/arial.ttf");

    // Mazo
    sf::Texture texturaMazo;
    if (!texturaMazo.loadFromFile("cartas/atrascarta.png"))
    {
        cerr << "No se pudo cargar la imagen del mazo." << endl;
    }
    sf::Sprite spriteMazo(texturaMazo);
    spriteMazo.setScale(0.125f, 0.125f); // Escalado opcional
    spriteMazo.setPosition(25, 425); // Ajust  posici¢n seg£n tu necesidad

    // Textos
    sf::Text texto, info;
    texto.setFont(fuente);
    texto.setCharacterSize(20);
    texto.setFillColor(sf::Color::White);
    texto.setPosition(20, 20);

    info.setFont(fuente);
    info.setCharacterSize(22);
    info.setFillColor(sf::Color::Cyan);
    info.setPosition(20, 60);

    // Cartas y selecci¢n
    sf::Texture texturas[5];
    sf::Sprite sprites[5];
    bool seleccionadas[5] = { false, false, false, false, false };
    int seleccion[4] = { -1, -1, -1, -1 };

    for (int i = 0; i < cantidad; i++) {
        string ruta = "cartas/" + to_string(cartas[i].getIdCarta()) + ".png";
        texturas[i].loadFromFile(ruta);
        sprites[i].setTexture(texturas[i]);
        sprites[i].setScale(1.35f, 1.35f);
        sprites[i].setPosition(212 + i * 100, 460); // Posici¢n centrada
    }

    bool terminar = false;
    while (!terminar && ventana.isOpen())
    {
        sf::Event event;
        while (ventana.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) ventana.close();

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code >= sf::Keyboard::Num1 && event.key.code <= sf::Keyboard::Num5)
                {
                    int idx = event.key.code - sf::Keyboard::Num1;
                    if (seleccionadas[idx]) {
                        seleccionadas[idx] = false;
                        Sonidos::get().reproducirSeleccionar();
                        for (int i = 0; i < 4; i++) if (seleccion[i] == idx) seleccion[i] = -1;
                    }
                    else {
                        for (int i = 0; i < 4; i++) {
                            if (seleccion[i] == -1) {
                                seleccion[i] = idx;
                                seleccionadas[idx] = true;
                                Sonidos::get().reproducirSeleccionar();
                                break;
                            }
                        }
                    }
                }

                if (event.key.code == sf::Keyboard::Enter) {
                    accion = 1;
                    tie(c1, c2, c3, c4) = make_tuple(seleccion[0], seleccion[1], seleccion[2], seleccion[3]);
                    terminar = true;
                }

                if (event.key.code == sf::Keyboard::BackSpace) {
                    accion = -1;
                    tie(c1, c2, c3, c4) = make_tuple(seleccion[0], seleccion[1], seleccion[2], seleccion[3]);
                    terminar = true;
                }
            }
        }

        ventana.clear();
        ventana.draw(fondoSprite);
        ventana.draw(spriteMazo);

        texto.setString("Selecciona con 1-5 (max 4). ENTER = jugar | BACKSPACE = descartar");
        info.setString("Ronda " + to_string(ronda) + " | Objetivo: " + to_string(objetivo) +
                       " | Jugadas: " + to_string(jugadasRestantes) +
                       " | Desc: " + to_string(descartesRestantes) +
                       " | Mazo: " + to_string(cartasEnMazo) +
                       " | Puntaje: " + to_string(puntajeActual));
        ventana.draw(texto);
        ventana.draw(info);

        for (int i = 0; i < cantidad; i++)
        {
            sprites[i].setPosition(212 + i * 100, seleccionadas[i] ? 445 : 460);
            ventana.draw(sprites[i]);

            if (seleccionadas[i])
            {
                sf::RectangleShape marco(sf::Vector2f(sprites[i].getGlobalBounds().width, sprites[i].getGlobalBounds().height));
                marco.setPosition(sprites[i].getPosition());
                marco.setFillColor(sf::Color::Transparent);
                marco.setOutlineThickness(3);
                marco.setOutlineColor(sf::Color::Red);
                ventana.draw(marco);
            }
        }

        // Evaluar jugada seleccionada
        Carta seleccionadasArray[4];
        int cantidadSeleccionadas = 0;
        for (int i = 0; i < 5 && cantidadSeleccionadas < 4; i++) {
            if (seleccionadas[i]) {
                seleccionadasArray[cantidadSeleccionadas++] = cartas[i];
            }
        }

        string jugadaActual;
        bool esPrimeraMano = (jugadasRestantes == 3);
        evaluarJugada(seleccionadasArray, cantidadSeleccionadas, esPrimeraMano, jugadaActual);

        if (!jugadaActual.empty())
        {

            sf::RectangleShape globo(sf::Vector2f(250, 50));
            globo.setFillColor(sf::Color(255, 255, 255, 140));
            globo.setOutlineColor(sf::Color::Black);
            globo.setOutlineThickness(2);
            globo.setPosition(350, 290);


            sf::Text textoGlobo;
            textoGlobo.setFont(fuente);
            textoGlobo.setCharacterSize(14);
            textoGlobo.setFillColor(sf::Color::Black);
            textoGlobo.setString(jugadaActual);

            sf::FloatRect textoBounds = textoGlobo.getLocalBounds();
            textoGlobo.setOrigin(textoBounds.left + textoBounds.width / 2.f, textoBounds.top + textoBounds.height / 2.f);
            textoGlobo.setPosition(globo.getPosition().x + globo.getSize().x / 2.f, globo.getPosition().y + globo.getSize().y / 2.f);


            sf::ConvexShape punta;
            punta.setPointCount(3);
            punta.setPoint(0, sf::Vector2f(globo.getPosition().x + globo.getSize().x, globo.getPosition().y + 30));
            punta.setPoint(1, sf::Vector2f(globo.getPosition().x + globo.getSize().x + 15, globo.getPosition().y + 40));
            punta.setPoint(2, sf::Vector2f(globo.getPosition().x + globo.getSize().x, globo.getPosition().y + 50));
            punta.setFillColor(sf::Color(255, 255, 255, 140));
            punta.setOutlineColor(sf::Color::Black);
            punta.setOutlineThickness(2);

            ventana.draw(globo);
            ventana.draw(punta);
            ventana.draw(textoGlobo);
        }
        ventana.display();
    }
}
