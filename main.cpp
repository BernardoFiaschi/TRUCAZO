#include <iostream>
#include "Mazo.h"
#include "imagenes.h"
using namespace std;

int main()
{
    Mazo mazo;
    int opcion;

    do
    {
        cout << endl << "---------------------------------" << endl;
        cout << "1. Repartimos 5 cartas, las mostramos graficamente y en consola" << endl;
        cout << "2. Mostrar mazo original" << endl;
        cout << "3. Mostrar cartas disponibles" << endl;
        cout << "0. Salir del programa" << endl;
        cout << "---------------------------------" << endl;
        cout << "Ingrese una opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            // Reparte y muestra las cartas tanto en texto como gr ficamente //
            if (mazo.repartirCartas())
                mazo.mostrarCartasJugador();
            mostrarCartasJugadorVisual(mazo.getCartasJugador(), mazo.getCantidadCartasJugador());
            break;

        case 2:
            mazo.mostrarMazoOriginal();
            break;

        case 3:
            mazo.mostrarCartasDisponibles();
            break;

        case 0:
            cout << "Programa terminado." << endl;
            break;

        default:
            cout << "Opcion invalida. Intente nuevamente." << endl;
            break;
        }

    } while (opcion != 0);
    return 0;
}

