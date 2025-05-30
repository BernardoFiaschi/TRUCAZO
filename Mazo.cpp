#include "Mazo.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

Mazo::Mazo()
{
    cartas = listarCartasMazo();                                        // Cargamos las 40 cartas iniciales //

    srand(time(NULL));                                                  // Semilla para aleatoriedad con rand() //

    vector<Carta> mazoTemporal = cartas;
    vector<Carta> mazoMezclado;
    cartas = listarCartasMazo();
    mazoOriginal = cartas;                                              // guardamos una copia antes de mezclar //


    while (mazoTemporal.size() > 0)                                     // El bucle se repite mientras haya cartas para mezclar //
    {
        int indice = rand() % mazoTemporal.size();                      // Reducimos el numero generado por rand y seleccionamos una carta aleatoria del mazo temp //
        mazoMezclado.push_back(mazoTemporal[indice]);                   // Agregamos esta carta al mazoMezclado y la insertamos al final del vector //
        mazoTemporal.erase(mazoTemporal.begin() + indice);              // La eliminamos del mazo temporal para no volver a elegirla //
    }

    cartas = mazoMezclado;                                              // Guardamos el mazo mezclado en 'cartas' //
}

bool Mazo::repartirCartas()
{
    if (cartas.size() <= 0)
    {
        cout << "No hay mas cartas disponibles" << endl;
        return false;
    }

    cartasJugador.clear();                                              // Vaciamos la mano anterior //
    for (int i = 0; i < 5; i++)                                         // EN ESTA LINEA REEMPLAZAR 5 POR CUANTAS CARTAS TE FALTAN PARA LLEGAR A 5 EN TU MANO //
    {
        cartasJugador.push_back(cartas[i]);                             // Repartimos las primeras 5 cartas disponibles //
    }

    cartas.erase(cartas.begin(), cartas.begin() + 5);                   // Eliminamos esas 5 cartas del mazo //
    return true;
}

void Mazo::mostrarCartasDisponibles() const
{
    cout << endl << "Cartas disponibles en el mazo: " << endl << endl;
    cout << "Total de cartas restantes: " << cartas.size() << endl << endl;

    for (int id = 1; id <= 40; id++)
    {
        for (int i = 0; i < cartas.size(); i++)
        {
            if (cartas[i].getIdCarta() == id)
            {
                cartas[i].mostrar();
                break;
            }
        }
    }
}

void Mazo::mostrarMazoOriginal() const
{
    cout << endl << "Mazo original:" << endl << endl;
    cout << "Total de cartas: " << mazoOriginal.size() << endl << endl;

    for (const Carta& c : mazoOriginal)
    {
        c.mostrar();
    }
}

void Mazo::mostrarCartasJugador() const
{
    cout << "---------------------------------" << endl;
    cout << "Tus cartas son:" << endl << endl;
    for (const Carta& c : cartasJugador)
    {
        c.mostrar();
    }
}
