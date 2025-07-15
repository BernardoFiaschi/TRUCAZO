#include "Partida.h"
#include "Manager.h"
#include "Imagenes.h"
#include "Jugadas.h"
#include "Sonidos.h"
#include "EntreRondas.h"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

Partida::Partida(Jugador& jugador) : _jugador(jugador)
{
    rondaActual = 0;
    puntajeTotal = 0;
    rondasGanadas = 0;

    int objetivos[15] = {150, 350, 500, 1000, 1500, 2000, 2500, 3000, 4000, 5000, 6000, 7000, 8500, 10000, 15000};
    for (int i = 0; i < 15; i++)
        puntajesObjetivo[i] = objetivos[i];
}


void Partida::inicializarRonda()
{
    mazo = Mazo();
    jugadasRestantes = 3;
    descartesRestantes = 3;
    puntajeRonda = 0;
    mano.clear();

    if (mazo.repartirCartas())
    {
        const Carta* iniciales = mazo.getCartasJugador();
        for (int i = 0; i < mazo.getCantidadCartasJugador(); i++)
            mano.push_back(iniciales[i]);
    }

    for (const Carta& c : cartasExtra)
    {
        mazo.agregarCartaExtra(c);
    }

    for (const Comodin& comodin : comodinesActivos)
    {
        string nombre = comodin.getNombre();
        if (nombre == "Mate") jugadasRestantes += 2;
        if (nombre == "Cafe") descartesRestantes += 2;
    }
}

void Partida::iniciar(sf::RenderWindow& ventana)
{

    for (rondaActual = 0; rondaActual < 15 && ventana.isOpen(); rondaActual++)
    {
        iniciarRonda(ventana);

        if (puntajeRonda < puntajesObjetivo[rondaActual]) return;
    }
}

void Partida::iniciarRonda(sf::RenderWindow& ventana)
{
    inicializarRonda();
    bool victoria = false;

    while ((jugadasRestantes > 0 || descartesRestantes > 0) &&
            puntajeRonda < puntajesObjetivo[rondaActual] &&
            ventana.isOpen())
    {

        if (jugadasRestantes == 0 && puntajeRonda < puntajesObjetivo[rondaActual]) break;

        if (procesarTurno(ventana, victoria)) break;
    }

    Manager manager;
    manager.finalizarRonda(ventana, victoria, *this);

    if (victoria && rondaActual < 14 && ventana.isOpen())
    {
        vector<Carta> ganadas = EntreRondas::seleccionarCartasEntreRondas(ventana, mazo.getMazoOriginal());
        for (const Carta& c : ganadas)
        {
            cartasExtra.push_back(c);
        }
    }

    if (victoria)
    {
        rondasGanadas++;
        if (rondasGanadas % 4 == 0 && ventana.isOpen())
        {
            Comodin elegido = EntreRondas::seleccionarComodin(ventana, mazo.getMazoComodines());
            comodinesSeleccionados.push_back(elegido);
            comodinesActivos.push_back(elegido);

        }
    }
}

bool Partida::procesarTurno(sf::RenderWindow& ventana, bool& victoria)
{
    int c1 = -1, c2 = -1, c3 = -1, c4 = -1, accion = 0;

    seleccionarCartasJugador
    (
        ventana, mano.data(), mano.size(),
        rondaActual + 1, puntajesObjetivo[rondaActual], puntajeRonda,
        c1, c2, c3, c4,
        jugadasRestantes, descartesRestantes, mazo.getCantidadCartasDisponibles(),
        jugadasRestantes, descartesRestantes, accion, _jugador,
        getJugadaActualTexto(),
        comodinesSeleccionados,
        rondasGanadas
    );

    vector<int> seleccion = {c1, c2, c3, c4};

    if (accion == 1 && jugadasRestantes > 0)
    {
        jugarCartas(seleccion);
        if (verificarVictoria())
        {
            victoria = true;
            return true;
        }
    }
    else if (accion == -1 && descartesRestantes > 0)
    {
        descartarCartas(seleccion);
    }

    return false;
}

void Partida::jugarCartas(const vector<int>& seleccion)
{
    auto seleccionadas = obtenerCartasSeleccionadas(seleccion);
    Carta seleccionadasCartas[4];
    int cantidad = seleccionadas.size();

    for (int i = 0; i < cantidad; i++)
        seleccionadasCartas[i] = seleccionadas[i];

    string jugadaActual;
    bool esPrimeraMano = (jugadasRestantes == 3);
    int puntos = evaluarJugada(seleccionadasCartas, cantidad, esPrimeraMano, jugadaActual, comodinesActivos, rondasGanadas);

    Sonidos::get().reproducirJugada();
    puntajeRonda += puntos;
    puntajeTotal += puntos;
    jugadaActualTexto = jugadaActual;

    limpiarCartas(seleccion);
    jugadasRestantes--;
    rellenarMano();
}


void Partida::descartarCartas(const vector<int>& seleccion)
{
    Sonidos::get().reproducirDescartar();
    limpiarCartas(seleccion);
    descartesRestantes--;
    rellenarMano();
}

vector<Carta> Partida::obtenerCartasSeleccionadas(const vector<int>& seleccion)
{
    vector<Carta> seleccionadas;
    for (int i : seleccion)
    {
        if (i >= 0 && i < mano.size() && mano[i].getValor() != 0 && seleccionadas.size() < 4)
            seleccionadas.push_back(mano[i]);
    }
    return seleccionadas;
}

void Partida::limpiarCartas(const vector<int>& seleccion)
{
    for (int i : seleccion)
    {
        if (i >= 0 && i < mano.size())
            mano[i] = Carta();
    }
}

vector<int> Partida::obtenerIndicesHuecosMano()
{
    vector<int> vacios;
    for (int i = 0; i < mano.size(); i++)
        if (mano[i].getValor() == 0)
            vacios.push_back(i);
    return vacios;
}

vector<Carta> Partida::obtenerCartasParaHuecos(int cantidad)
{
    vector<Carta> nuevas;
    mazo.darCartas(cantidad, nuevas);
    return nuevas;
}


void Partida::rellenarHuecos(const vector<int>& vacios, const vector<Carta>& nuevas)
{
    for (int i = 0; i < vacios.size(); i++)
        mano[vacios[i]] = nuevas[i];
}

void Partida::rellenarMano()
{
    auto vacios = obtenerIndicesHuecosMano();
    auto nuevas = obtenerCartasParaHuecos(vacios.size());
    rellenarHuecos(vacios, nuevas);
}

bool Partida::verificarVictoria()
{
    return puntajeRonda >= puntajesObjetivo[rondaActual];
}

int Partida::getPuntajeRonda() const
{
    return puntajeRonda;
}

int Partida::getRondaActual() const
{
    return rondaActual;
}
