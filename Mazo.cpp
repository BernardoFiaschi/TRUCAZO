#include "Mazo.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stack>
using namespace std;

Mazo::Mazo()
{
                                                                // Obtenemos las 40 cartas del mazo inicial fijo //
    vector<Carta> iniciales = CartasMazo();

                                                                // Guardamos una copia sin mezclar para referencia //
    mazoOriginal = iniciales;

                                                                // Inicializamos la semilla aleatoria para mezclar //
    srand(time(NULL));

                                                                // Mezclamos las cartas seleccionando aleatoriamente y cargando en la pila //
    while (!iniciales.empty())
    {
        int indice = rand() % iniciales.size();                 // Selecciona un ¡ndice al azar //
        pilaCartas.push(iniciales[indice]);                     // Agrega la carta a la pila mezclada //
        iniciales.erase(iniciales.begin() + indice);            // La elimina del mazo inicial //
    }
}


                                                                // Reparte 5 cartas al jugador desde la pila de cartas mezcladas //
bool Mazo::repartirCartas()
{
    if (pilaCartas.size() < 5)
    {
        cout << "No hay m s cartas suficientes para repartir." << endl;
        return false;
    }

                                                                // Limpiamos la mano anterior del jugador //
    cartasJugador.clear();

                                                                // Extraemos 5 cartas del tope de la pila y las agregamos al jugador //
    for (int i = 0; i < 5; i++)
    {
        cartasJugador.push_back(pilaCartas.top());
        pilaCartas.pop();
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
    cout << endl << "Cartas restantes en el mazo: " << pilaCartas.size() << endl;
}

                                                                // Mostramos el mazo original (sin mezclar) //
void Mazo::mostrarMazoOriginal() const
{
    cout << endl << "Mazo original (ordenado): " << endl;
    for (const Carta& c : mazoOriginal)
        c.mostrar();
}

                                                                // Devolvemos un puntero al arreglo de cartas del jugador para mostrar graficamente las cartas //
const Carta* Mazo::getCartasJugador() const {
    return cartasJugador.data();
}

                                                                // Devolvemos cu ntas cartas tiene actualmente el jugador //
int Mazo::getCantidadCartasJugador() const {
    return cartasJugador.size();
}

