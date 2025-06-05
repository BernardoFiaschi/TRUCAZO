#include <iostream>
#include "Mazo.h"
#include "Imagenes.h"
#include "Partida.h"
using namespace std;

int main()
{
    int opcion;

    do
    {
        cout << endl << "---------------------------------" << endl;
        cout << "1. Mostrar mazo original" << endl;
        cout << "2. Mostrar cartas disponibles" << endl;
        cout << "3. Jugar partida completa (15 rondas)" << endl;
        cout << "0. Salir del programa" << endl;
        cout << "---------------------------------" << endl;
        cout << "Ingrese una opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1: {
            Mazo mazo;
            mazo.mostrarMazoOriginal();
            break;
        }

        case 2: {
            Mazo mazo;
            mazo.mostrarCartasDisponibles();
            break;
        }

        case 3: {
            Partida partida;
            partida.iniciar();
            break;
        }

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
