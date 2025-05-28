#include "Carta.h"
#include <iostream>
#include "Mazo.h"
using namespace std;

int main()
{
    Mazo mazo;
    int opcion;

    do
    {
        cout << endl << "---------------------------------" << endl;
        cout << "1. Repartir 5 cartas" << endl;
        cout << "2. Mostrar mazo entero" << endl;
        cout << "3. Mostrar cartas restantes" << endl;
        cout << "0. Salir del programa" << endl;
        cout << "---------------------------------" << endl;
        cout << "Ingrese una opcion: " << endl;
        cout << "---------------------------------" << endl;
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            if (mazo.repartirCartas())
            {
                mazo.mostrarCartasJugador();
            }
            break;

        case 2:
        {
            mazo.mostrarMazoOriginal();
            break;
        }

         case 3:
        {
            mazo.mostrarCartasDisponibles();
            break;
        }

        case 0:
            cout << "Programa terminado" << endl;
            break;

        default:
            cout << "Opcion invalida. Intente nuevamente." << endl;
            break;
        }

    } while (opcion != 0);

    return 0;
}
