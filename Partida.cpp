#include "Partida.h"
#include "manager.h"
#include "Jugador.h"
#include "Imagenes.h"
#include "Jugadas.h"
#include "Sonidos.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

// --- FUNCIONES AUXILIARES PRIVADAS ---
void Partida::inicializarRonda() {
    mazo = Mazo();
    jugadasRestantes = 3;
    descartesRestantes = 2;
    puntajeRonda = 0;
    mano.clear();
    if (mazo.repartirCartas()) {
        const Carta* iniciales = mazo.getCartasJugador();
        for (int i = 0; i < mazo.getCantidadCartasJugador(); i++)
            mano.push_back(iniciales[i]);
    }
}

bool Partida::procesarTurno(sf::RenderWindow& ventana, bool& victoria) {
    int c1 = -1, c2 = -1, c3 = -1, c4 = -1, accion = 0;
    seleccionarCartasJugador(
        ventana, mano.data(), mano.size(),
        rondaActual + 1, puntajesObjetivo[rondaActual], puntajeRonda,
        c1, c2, c3, c4,
        jugadasRestantes, descartesRestantes, mazo.getCantidadCartasDisponibles(),
        jugadasRestantes, descartesRestantes, accion,
        getJugadaActualTexto()
    );
    vector<int> seleccion = {c1, c2, c3, c4};
    if (accion == 1 && jugadasRestantes > 0) {
        jugarCartas(seleccion);
        if (verificarVictoria()) {
            victoria = true;
            return true;
        }
    } else if (accion == -1 && descartesRestantes > 0) {
        descartarCartas(seleccion);
    }
    return false;
}

void Partida::finalizarRonda(sf::RenderWindow& ventana, bool victoria) {
    cout << "Fin de la ronda. Jugadas restantes: " << jugadasRestantes << " | Puntaje actual: " << puntajeRonda << endl;
    Manager ronda;
    ronda.finalizarRonda(ventana, victoria, *this);
}

vector<Carta> Partida::obtenerCartasSeleccionadas(const vector<int>& seleccion) {
    vector<Carta> seleccionadas;
    for (int i : seleccion) {
        if (i >= 0 && i < mano.size() && mano[i].getValor() != 0 && seleccionadas.size() < 4)
            seleccionadas.push_back(mano[i]);
    }
    return seleccionadas;
}

void Partida::limpiarCartasUsadas(const vector<int>& seleccion) {
    for (int i : seleccion) {
        if (i >= 0 && i < mano.size())
            mano[i] = Carta();
    }
}

void Partida::limpiarCartasDescartadas(const vector<int>& seleccion) {
    for (int i : seleccion) {
        if (i >= 0 && i < mano.size())
            mano[i] = Carta();
    }
}

vector<int> Partida::obtenerIndicesHuecosMano() {
    vector<int> vacios;
    for (int i = 0; i < mano.size(); i++)
        if (mano[i].getValor() == 0)
            vacios.push_back(i);
    return vacios;
}

vector<Carta> Partida::obtenerCartasParaHuecos(int cantidad) {
    vector<Carta> nuevas;
    mazo.darCartas(cantidad, nuevas);
    return nuevas;
}

void Partida::rellenarHuecos(const vector<int>& vacios, const vector<Carta>& nuevas) {
    for (int i = 0; i < vacios.size(); i++)
        mano[vacios[i]] = nuevas[i];
}

// --- FUNCIONES ORIGINALES ---

Partida::Partida() {
    rondaActual = 0;
    puntajeTotal = 0;
    int objetivos[15] = {100, 150, 300, 500, 1000, 1500, 3000, 5000, 7500, 10000, 15000, 30000, 50000, 75000, 150000};
    for (int i = 0; i < 15; i++)
        puntajesObjetivo[i] = objetivos[i];
}

Partida::Partida(Jugador jugador) : Partida() {
    _jugador = jugador;
}

void Partida::iniciar(sf::RenderWindow& ventana) {
    ventana.setTitle("TRUCAZO");
    ventana.setFramerateLimit(60);
    for (rondaActual = 0; rondaActual < 15 && ventana.isOpen(); rondaActual++) {
        iniciarRonda(ventana);
        if (puntajeRonda < puntajesObjetivo[rondaActual])
            return;
    }
}

void Partida::iniciarRonda(sf::RenderWindow& ventana) {
    inicializarRonda();
    bool victoria = false;
    while ((jugadasRestantes > 0 || descartesRestantes > 0) && puntajeRonda < puntajesObjetivo[rondaActual] && ventana.isOpen()) {
        if (jugadasRestantes == 0 && puntajeRonda < puntajesObjetivo[rondaActual]) {
            std::cout << "No quedan jugadas. Perdiste la partida." << std::endl;
            break;
        }
        if (procesarTurno(ventana, victoria))
            break;
    }
    finalizarRonda(ventana, victoria);
}

void Partida::jugarCartas(const vector<int>& seleccion) {
    auto seleccionadas = obtenerCartasSeleccionadas(seleccion);
    Carta seleccionadasCartas[4];
    int cantidadSeleccionadas = seleccionadas.size();
    for (int i = 0; i < cantidadSeleccionadas; ++i)
        seleccionadasCartas[i] = seleccionadas[i];
    string jugadaActual;
    bool esPrimeraMano = (jugadasRestantes == 3);
    int puntos = evaluarJugada(seleccionadasCartas, cantidadSeleccionadas, esPrimeraMano, jugadaActual);
    Sonidos::get().reproducirJugada();
    puntajeRonda += puntos;
    this->jugadaActualTexto = jugadaActual;
    limpiarCartasUsadas(seleccion);
    jugadasRestantes--;
    rellenarMano();
}

void Partida::descartarCartas(const vector<int>& seleccion) {
    Sonidos::get().reproducirDescartar();
    limpiarCartasDescartadas(seleccion);
    descartesRestantes--;
    rellenarMano();
}

void Partida::rellenarMano() {
    auto vacios = obtenerIndicesHuecosMano();
    auto nuevas = obtenerCartasParaHuecos(vacios.size());
    rellenarHuecos(vacios, nuevas);
}

bool Partida::verificarVictoria() {
    return puntajeRonda >= puntajesObjetivo[rondaActual];
}

int Partida::getPuntajeRonda() const {
    return puntajeRonda;
}

int Partida::getRondaActual() const {
    return rondaActual;
}