#include "Mazo.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stack>
using namespace std;


Mazo::Mazo()
{
    vector<Carta> iniciales = CartasMazo();
    mazoOriginal = iniciales;
    srand(time(NULL));
    cantidadCartasDisponibles = 40;

    while (!iniciales.empty())
    {
        int indice = rand() % iniciales.size();
        pilaCartas.push(iniciales[indice]);
        iniciales.erase(iniciales.begin() + indice);
    }
}


                                                                // Reparte 5 cartas al jugador desde la pila de cartas mezcladas //
bool Mazo::repartirCartas()
{
    if (pilaCartas.size() < 5)
    {
        cout << "No hay mas cartas para repartir." << endl;
        return false;
    }

                                                                // Limpiamos la mano anterior del jugador //
    cartasJugador.clear();

                                                                // Extraemos 5 cartas del tope de la pila y las agregamos al jugador //
    for (int i = 0; i < 5; i++)
    {
        cartasJugador.push_back(pilaCartas.top());
        pilaCartas.pop();
        cantidadCartasDisponibles--;
    }
    return true;
}

                                                                // Mostramos las cartas actuales del jugador por consola //
void Mazo::mostrarCartasJugador() const
{
    cout << "---------------------------------" << endl;
    cout << "Tus cartas son:" << endl << endl;
    for (const Carta& c : cartasJugador)
        c.mostrar();
}

                                                                // Mostramos cu ntas cartas quedan en la pila mezclada //
void Mazo::mostrarCartasDisponibles() const
{
    cout << "Cartas restantes en el mazo: " << pilaCartas.size() << "";

    stack<Carta> copia = pilaCartas;
    while (!copia.empty())
    {
        copia.top().mostrar();
        copia.pop();
    }
}


                                                                // Mostramos el mazo original completo //
void Mazo::mostrarMazoOriginal() const
{
    cout << endl << "Mazo original: " << endl;
    for (const Carta& c : mazoOriginal)
        c.mostrar();
}

                                                                // Devolvemos un puntero al arreglo de cartas del jugador para mostrar graficamente las cartas //
const Carta* Mazo::getCartasJugador() const {
    return cartasJugador.data();
}

                                                                // Devolvemos cuantas cartas tiene actualmente el jugador //
int Mazo::getCantidadCartasJugador() const {
    return cartasJugador.size();
}

int Mazo::getCantidadCartasDisponibles() const {
    return cantidadCartasDisponibles;
}




bool Mazo::darCartas(int cantidad, std::vector<Carta>& nuevasCartas) {
    nuevasCartas.clear();
    if (pilaCartas.size() < cantidad) return false;

    for (int i = 0; i < cantidad; i++) {
        nuevasCartas.push_back(pilaCartas.top());
        pilaCartas.pop();
        cantidadCartasDisponibles--;
    }
    return true;
}
