#include "Partida.h"
#include "Imagenes.h"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

                                                                                        // Constructor de la clase Partida //
                                                                                        // Inicializa el estado de la partida y carga los puntajes objetivo por ronda //
Partida::Partida()
{
    rondaActual = 0;
    puntajeTotal = 0;
    for (int i = 0; i < 15; i++)
    {
        puntajesObjetivo[i] = 50 * (i + 1);
    }
}

                                                                                        // Iniciamos la partida completa //
                                                                                        // Crea una ventana grafica y ejecuta 15 rondas mientras la ventana esta abierta //
void Partida::iniciar() {
    sf::RenderWindow ventana(sf::VideoMode(900, 600), "Juego - TRUCAZO");
    ventana.setFramerateLimit(60);

    for (rondaActual = 0; rondaActual < 15 && ventana.isOpen(); rondaActual++)
    {
        iniciarRonda(ventana);
    }


    if (ventana.isOpen())
    {
        mostrarMensaje(ventana, "Fin de la partida. Puntaje total: " + to_string(puntajeTotal));
    }

    ventana.close();
}

                                                                                        // Ejecuta la logica de una ronda //
                                                                                        // Reparte cartas iniciales //
                                                                                        // Permite al jugador jugar o descartar cartas //
                                                                                        // Evalua si se alcanza el puntaje objetivo //
                                                                                        // Muestra el resultado de la ronda //
void Partida::iniciarRonda(sf::RenderWindow& ventana)
{
    mazo = Mazo();
    jugadasRestantes = 3;
    descartesRestantes = 2;
    puntajeRonda = 0;
    mano.clear();

    if (mazo.repartirCartas())
    {
        const Carta* iniciales = mazo.getCartasJugador();
        for (int i = 0; i < mazo.getCantidadCartasJugador(); i++)
        {
            mano.push_back(iniciales[i]);
        }
    }

    bool victoria = false;

    while ((jugadasRestantes > 0 || descartesRestantes > 0) && ventana.isOpen())
    {
        int c1 = -1, c2 = -1, c3 = -1, c4 = -1, accion = 0;

        seleccionarCartasJugador(
            ventana,
            mano.data(), mano.size(),
            rondaActual + 1,
            puntajesObjetivo[rondaActual],
            puntajeRonda,
            c1, c2, c3, c4,
            jugadasRestantes,
            descartesRestantes,
            mazo.getCantidadCartasDisponibles(),
            accion
        );

        vector<int> seleccion = { c1, c2, c3, c4 };

        if (accion == 1 && jugadasRestantes > 0) {
            jugarCartas(seleccion);
            if (verificarVictoria()) {
                victoria = true;
                break;
            }
        } else if (accion == -1 && descartesRestantes > 0) {
            descartarCartas(seleccion);
        }
    }

    finalizarRonda(ventana, victoria);
}

                                                                                        // Suma los valores de las cartas seleccionadas (juego) al puntaje actual de ronda //
                                                                                        // Las cartas jugadas se eliminan de la mano y luego se repone la mano //
void Partida::jugarCartas(const vector<int>& seleccion) {
    for (int idx : seleccion) {
        if (idx >= 0 && idx < mano.size()) {
            puntajeRonda += mano[idx].getValor();
            mano[idx] = Carta();
        }
    }
    jugadasRestantes--;
    rellenarMano();
}

                                                                                        // Descarta las cartas seleccionadas y luego rellena la mano con nuevas del mazo //
void Partida::descartarCartas(const vector<int>& seleccion) {
    for (int idx : seleccion) {
        if (idx >= 0 && idx < mano.size()) {
            mano[idx] = Carta();
        }
    }
    descartesRestantes--;
    rellenarMano();
}
                                                                                        // Reemplaza solo las cartas vacias de la mano con nuevas cartas del mazo //
                                                                                        // Se asegura de no modificar las cartas que el jugador conserva //
void Partida::rellenarMano() {
    vector<int> vacios;
    for (int i = 0; i < mano.size(); i++) {
        if (mano[i].getValor() == 0) {
            vacios.push_back(i);
        }
    }

    vector<Carta> nuevas;
    if (mazo.darCartas(vacios.size(), nuevas)) {
        for (int i = 0; i < vacios.size(); i++) {
            mano[vacios[i]] = nuevas[i];
        }
    }
}

                                                                                        // Devuelve true si el puntaje actual de ronda alcanza o supera el objetivo //
bool Partida::verificarVictoria() {
    return puntajeRonda >= puntajesObjetivo[rondaActual];
}

                                                                                        // Muestra un mensaje en pantalla con SFML //
                                                                                        // Espera a que el jugador presione ENTER para continuar //
void Partida::mostrarMensaje(sf::RenderWindow& ventana, const string& mensaje) {
    sf::Font fuente;
    fuente.loadFromFile("C:/Windows/Fonts/arial.ttf");

    sf::Text texto;
    texto.setFont(fuente);
    texto.setCharacterSize(26);
    texto.setFillColor(sf::Color::Yellow);
    texto.setString(mensaje + "Presione ENTER para continuar...");
    texto.setPosition(100, 250);

    while (ventana.isOpen()) {
        sf::Event event;
        while (ventana.pollEvent(event)) {
            if (event.type == sf::Event::Closed) ventana.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) return;
        }
        ventana.clear();
        ventana.draw(texto);
        ventana.display();
    }
}

                                                                                        // Muestra si la ronda fue ganada o perdida //
                                                                                        // Si se gana, suma el puntaje al total y muestra un mensaje de felicitacion //
void Partida::finalizarRonda(sf::RenderWindow& ventana, bool victoria) {
    if (victoria) {
        puntajeTotal += puntajesObjetivo[rondaActual];
        mostrarMensaje(ventana, "RONDA " + to_string(rondaActual + 1) + " COMPLETADA.");
    } else {
        mostrarMensaje(ventana, "RONDA " + to_string(rondaActual + 1) + " PERDIDA.");
    }
}
