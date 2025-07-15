#include "Imagenes.h"
#include "Jugadas.h"
#include "Partida.h"
#include "Sonidos.h"
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

void cargarTexturasCartas(const Carta* cartas, int cantidad, sf::Texture* texturas, sf::Sprite* sprites)
{
    for (int i = 0; i < cantidad; i++)
    {
        string ruta = "cartas/" + to_string(cartas[i].getIdCarta()) + ".png";
        texturas[i].loadFromFile(ruta);
        sprites[i].setTexture(texturas[i]);
        sprites[i].setScale(1.35f, 1.35f);
        sprites[i].setPosition(212 + i * 100, 460);
    }
}

void mostrarSeleccion(sf::RenderWindow& ventana, sf::Sprite* sprites, bool* seleccionadas, int cantidad)
{
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
}

void seleccionarCartasJugador(sf::RenderWindow& ventana,
                              const Carta* cartas, int cantidad,
                              int ronda, int objetivo, int puntajeActual,
                              int& c1, int& c2, int& c3, int& c4,
                              int jugadas, int descartes, int cartasEnMazo,
                              int& jugadasRestantes, int& descartesRestantes,
                              int& accion,
                              const Jugador& jugador,
                              const string& jugadaActualTexto,
                              const vector<Comodin>& comodinesActivos,
                              int rondasGanadas)
{
    sf::Texture fondoTextura;
    if (!fondoTextura.loadFromFile("fondos/FONDOTRUCAZO.png"))
    {
        cerr << "No se pudo cargar la imagen de fondo." << endl;
    }
    sf::Sprite fondoSprite(fondoTextura);

    sf::Font fuente;
    fuente.loadFromFile("C:/Windows/Fonts/arial.ttf");

    sf::Texture texturaMazo;
    if (!texturaMazo.loadFromFile("cartas/atrascarta.png"))
    {
        cerr << "No se pudo cargar la imagen del mazo." << endl;
    }
    sf::Sprite spriteMazo(texturaMazo);
    spriteMazo.setScale(0.125f, 0.125f);
    spriteMazo.setPosition(780, 425);

    sf::Text texto, info;
    texto.setFont(fuente);
    texto.setCharacterSize(20);
    texto.setFillColor(sf::Color::White);
    texto.setPosition(20, 20);

    info.setFont(fuente);
    info.setCharacterSize(22);
    info.setFillColor(sf::Color::Cyan);
    info.setPosition(20, 60);

    sf::Texture texturas[5];
    sf::Sprite sprites[5];
    bool seleccionadas[5] = { false, false, false, false, false };
    int seleccion[4] = { -1, -1, -1, -1 };

    cargarTexturasCartas(cartas, cantidad, texturas, sprites);

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
                        Sonidos::get().reproducirSeleccionar();
                        for (int i = 0; i < 4; i++) if (seleccion[i] == idx) seleccion[i] = -1;
                    }
                    else
                    {
                        for (int i = 0; i < 4; i++)
                        {
                            if (seleccion[i] == -1)
                            {
                                seleccion[i] = idx;
                                seleccionadas[idx] = true;
                                Sonidos::get().reproducirSeleccionar();
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

        ventana.clear();
        ventana.draw(fondoSprite);
        ventana.draw(spriteMazo);

        texto.setString("Selecciona con 1-5 (max 4). ENTER = jugar | BACKSPACE = descartar");
        info.setString("Jugador: " + jugador.getNombre() + " | Ronda " + to_string(ronda) + " | Objetivo: " + to_string(objetivo) +
                       " | Jugadas: " + to_string(jugadasRestantes) +
                       " | Desc: " + to_string(descartesRestantes) +
                       " | Mazo: " + to_string(cartasEnMazo) +
                       " | \n \nPuntaje: " + to_string(puntajeActual));
        ventana.draw(texto);
        ventana.draw(info);

        sf::Text tituloComodines;
        tituloComodines.setFont(fuente);
        tituloComodines.setCharacterSize(20);
        tituloComodines.setFillColor(sf::Color::White);
        tituloComodines.setString("Comodines:");
        tituloComodines.setPosition(20.f, 180.f);
        ventana.draw(tituloComodines);

        vector<sf::Texture> texturasComodines(comodinesActivos.size());
        for (size_t i = 0; i < comodinesActivos.size(); ++i)
        {
            if (texturasComodines[i].loadFromFile("comodines/" + to_string(comodinesActivos[i].getId()) + ".png"))
            {
                sf::Sprite sprite(texturasComodines[i]);
                sprite.setScale(0.9f, 0.9f);
                sprite.setPosition(20.f, 210.f + i * 100.f);
                ventana.draw(sprite);
            }
        }

        mostrarSeleccion(ventana, sprites, seleccionadas, cantidad);

        Carta seleccionadasArray[4];
        int cantidadSeleccionadas = 0;
        for (int i = 0; i < 5 && cantidadSeleccionadas < 4; i++)
        {
            if (seleccionadas[i])
            {
                seleccionadasArray[cantidadSeleccionadas++] = cartas[i];
            }
        }

        string jugadaActual;
        bool esPrimeraMano = (jugadasRestantes == 3);
        evaluarJugada(seleccionadasArray, cantidadSeleccionadas, esPrimeraMano, jugadaActual, comodinesActivos, rondasGanadas);

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

