#include "Partida.h"
#include "Imagenes.h"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

Partida::Partida() {
    rondaActual = 0;
    puntajeTotal = 0;
    for (int i = 0; i < 15; i++) {
        puntajesObjetivo[i] = 50 * (i + 1);
    }
}

void Partida::iniciar() {
    sf::RenderWindow ventana(sf::VideoMode(900, 600), "Juego - TRUCAZO");

    for (rondaActual = 0; rondaActual < 15 && ventana.isOpen(); rondaActual++) {
        iniciarRonda(ventana);
    }

    if (ventana.isOpen()) {
        mostrarMensaje(ventana, "Fin de la partida. Puntaje total: " + to_string(puntajeTotal));
    }

    ventana.close();
}

void Partida::iniciarRonda(sf::RenderWindow& ventana) {
    mazo = Mazo();
    jugadasRestantes = 3;
    descartesRestantes = 2;
    puntajeRonda = 0;
    mano.clear();

    if (mazo.repartirCartas()) {
        const Carta* iniciales = mazo.getCartasJugador();
        for (int i = 0; i < mazo.getCantidadCartasJugador(); i++) {
            mano.push_back(iniciales[i]);
        }
    }

    bool victoria = false;

    while ((jugadasRestantes > 0 || descartesRestantes > 0) && ventana.isOpen()) {
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

void Partida::descartarCartas(const vector<int>& seleccion) {
    for (int idx : seleccion) {
        if (idx >= 0 && idx < mano.size()) {
            mano[idx] = Carta();
        }
    }
    descartesRestantes--;
    rellenarMano();
}

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

bool Partida::verificarVictoria() {
    return puntajeRonda >= puntajesObjetivo[rondaActual];
}

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

void Partida::finalizarRonda(sf::RenderWindow& ventana, bool victoria) {
    if (victoria) {
        puntajeTotal += puntajesObjetivo[rondaActual];
        mostrarMensaje(ventana, "RONDA " + to_string(rondaActual + 1) + " COMPLETADA.");
    } else {
        mostrarMensaje(ventana, "RONDA " + to_string(rondaActual + 1) + " PERDIDA.");
    }
}
