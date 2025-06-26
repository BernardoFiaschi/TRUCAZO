#include "Partida.h"
#include "Manager.h"
#include "Imagenes.h"
#include "Jugadas.h"
#include "Sonidos.h"
#include "EntreRondas.h"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

/*
   Constructor de Partida
   Para que: inicializamos todos los valores por defecto para empezar una nueva partida.
   Por qu‚: necesitamos tener definidos los objetivos de cada ronda y dejar todo limpio.
   C¢mo: recibimos el jugador por referencia y cargamos los objetivos por ronda.
*/
Partida::Partida(Jugador& jugador) : _jugador(jugador)
{
    rondaActual = 0;
    puntajeTotal = 0;
    rondasGanadas = 0;

    int objetivos[15] = {150, 350, 500, 1000, 1500, 2000, 2500, 3000, 4000, 5000, 6000, 7000, 8500, 10000, 15000};
    for (int i = 0; i < 15; i++)
        puntajesObjetivo[i] = objetivos[i];
}

/*
   Inicializa los valores de la ronda actual
   Para qu‚: comenzar una nueva ronda limpia con mazo reiniciado y mano nueva.
   C¢mo: reinicia mazo, cantidad de jugadas y descartes, y reparte las cartas al jugador.
*/
void Partida::inicializarRonda()
{
    mazo = Mazo(); // se reinicia el mazo original mezclado
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

    // Agrega las cartas extra obtenidas en rondas anteriores
    for (const Carta& c : cartasExtra)
    {
        mazo.agregarCartaExtra(c);
    }

    // APLICAR EFECTO DE COMODINES MATE y CAFE
    for (const Comodin& comodin : comodinesActivos)
    {
        string nombre = comodin.getNombre();
        if (nombre == "Mate") jugadasRestantes += 2;
        if (nombre == "Cafe") descartesRestantes += 2;
    }
}

/*
   Inicia la partida completa (todas las rondas)
   Para qu‚: ejecutar una secuencia de hasta 15 rondas hasta ganar o perder.
   C¢mo: por cada ronda se llama a iniciarRonda(), y se corta si no se cumple el objetivo.
*/
void Partida::iniciar(sf::RenderWindow& ventana)
{

    for (rondaActual = 0; rondaActual < 15 && ventana.isOpen(); rondaActual++)
    {
        iniciarRonda(ventana);

        if (puntajeRonda < puntajesObjetivo[rondaActual]) return; // se pierde
    }
}

/*
   Inicia una ronda individual dentro de la partida
   Para qu‚: preparar y ejecutar la logica de una sola ronda
   C¢mo: se inicializa la ronda y se repiten turnos hasta ganar o quedarse sin jugadas.
*/
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

/*
   Procesa un turno del jugador
   Para qu‚: manejar la seleccion de cartas y decidir si se juega o descarta
   C¢mo: llama a seleccionarCartasJugador y seg£n la accion elegida actua.
*/
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

/*
   Juega las cartas seleccionadas
   Para qu‚: evaluar jugada, sumar puntos y actualizar mano
   C¢mo: se arma un array de hasta 4 cartas, se evalua la jugada, se suman puntos y se repone la mano
*/
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

/*
   Descarta las cartas seleccionadas
   Para qu‚: permite al jugador reemplazar cartas que no quiere
   C¢mo: limpia las cartas seleccionadas y repone con nuevas del mazo
*/
void Partida::descartarCartas(const vector<int>& seleccion)
{
    Sonidos::get().reproducirDescartar();
    limpiarCartas(seleccion);
    descartesRestantes--;
    rellenarMano();
}

/* Extrae las cartas seleccionadas segun indices */
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

/* Limpia (borra) las cartas seleccionadas en la mano */
void Partida::limpiarCartas(const vector<int>& seleccion)
{
    for (int i : seleccion)
    {
        if (i >= 0 && i < mano.size())
            mano[i] = Carta(); // carta vacia
    }
}

/* Devuelve los indices donde hay huecos vacios en la mano */
vector<int> Partida::obtenerIndicesHuecosMano()
{
    vector<int> vacios;
    for (int i = 0; i < mano.size(); i++)
        if (mano[i].getValor() == 0)
            vacios.push_back(i);
    return vacios;
}

/* Pide al mazo cartas nuevas para los huecos */
vector<Carta> Partida::obtenerCartasParaHuecos(int cantidad)
{
    vector<Carta> nuevas;
    mazo.darCartas(cantidad, nuevas);
    return nuevas;
}

/* Asigna las cartas nuevas en los huecos detectados */
void Partida::rellenarHuecos(const vector<int>& vacios, const vector<Carta>& nuevas)
{
    for (int i = 0; i < vacios.size(); i++)
        mano[vacios[i]] = nuevas[i];
}

/* Rellena la mano completa con cartas nuevas en los huecos */
void Partida::rellenarMano()
{
    auto vacios = obtenerIndicesHuecosMano();
    auto nuevas = obtenerCartasParaHuecos(vacios.size());
    rellenarHuecos(vacios, nuevas);
}

/* Verifica si el puntaje actual alcanza el objetivo */
bool Partida::verificarVictoria()
{
    return puntajeRonda >= puntajesObjetivo[rondaActual];
}

/* Devuelve el puntaje de la ronda actual */
int Partida::getPuntajeRonda() const
{
    return puntajeRonda;
}

/* Devuelve el numero de ronda actual */
int Partida::getRondaActual() const
{
    return rondaActual;
}
