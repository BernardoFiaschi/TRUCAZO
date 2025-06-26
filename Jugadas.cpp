#include "Jugadas.h"
using namespace std;

/*
    Esta funcion analiza una seleccion de cartas y devuelve el puntaje
    obtenido segun las combinaciones validas del juego y los comodines activos.

    Para que:
        Calcular cuantos puntos suma una jugada segun si hay pares, jugadas especiales
        como ENVIDO, RETRUCO o FLOR DE TRUCO, y aplicar efectos de los comodines.

    Por que:
        Es la funcion central de la logica de juego, que determina si la jugada fue buena
        y cuantos puntos aporta al objetivo.

    Como:
        - Analiza combinaciones por numero y por palo.
        - Aplica multiplicadores segun el tipo de jugada.
        - Aplica modificadores adicionales si hay comodines activos.
*/
int evaluarJugada(const Carta seleccionadas[], int cantidad, bool esPrimeraMano, string& nombreJugada, const vector<Comodin>& comodinesActivos, int rondasGanadas)
{
    nombreJugada = "";
    int puntos = 0;
    int suma = 0;
    int usados[4] = {0, 0, 0, 0}; // Marca las cartas que ya se usaron en una combinacion

    // Suma inicial de las cartas jugadas
    for (int i = 0; i < cantidad; i++) {
        suma += seleccionadas[i].getValor();
    }

    // Comodin: MATE (+2 jugadas adicionales) --> se implementa fuera, en logica de rondas

    // Comodin: FIGURAS (x5 a 10, 11, 12)
    for (int i = 0; i < cantidad; i++) {
        for (const Comodin& comodin : comodinesActivos) {
            if (comodin.getNombre() == "Figuras") {
                int num = seleccionadas[i].getNumero();
                if (num == 10 || num == 11 || num == 12) {
                    suma += seleccionadas[i].getValor() * 4; // valor extra para lograr x5 en total
                }
            }
        }
    }

    // Comodin: ESPADA CEREMONIAL (ancho de espada = 500, resto de espadas +30)
    for (int i = 0; i < cantidad; i++) {
        for (const Comodin& comodin : comodinesActivos) {
            if (comodin.getNombre() == "Sable de San Martin") {
                if (seleccionadas[i].getNumero() == 1 && seleccionadas[i].getPalo() == "espada") {
                    suma += 500 - seleccionadas[i].getValor(); // sobreescribe su valor
                }
                else if (seleccionadas[i].getPalo() == "espada") {
                    suma += 35;
                }
            }
        }
    }

    // Comodin: DOLAR (cartas de oro multiplican por (5 + rondasGanadas))
    for (int i = 0; i < cantidad; i++) {
        for (const Comodin& comodin : comodinesActivos) {
            if (comodin.getNombre() == "Dolar" && seleccionadas[i].getPalo() == "oro") {
                suma += seleccionadas[i].getValor() * ((5 + rondasGanadas) - 1); // -1 porque ya fue sumado
            }
        }
    }

    // Comodin: COPA DEL MUNDO (cartas de copa x3)
    for (int i = 0; i < cantidad; i++) {
        for (const Comodin& comodin : comodinesActivos) {
            if (comodin.getNombre() == "Copa del Mundo" && seleccionadas[i].getPalo() == "copa") {
                suma += seleccionadas[i].getValor() * 2; // x3 total
            }
        }
    }

    // Comodin: ARBOL (cartas de basto x4)
    bool tieneArbol = false;
   for (int i = 0; i < cantidad; i++) {
        for (const Comodin& comodin : comodinesActivos) {
            if (comodin.getNombre() == "Arbol" && seleccionadas[i].getPalo() == "basto") {
                suma += seleccionadas[i].getValor() * 3; // x4 total
            }
        }
    }
    /*
        Coincidencias por numero:
        2 iguales: TRUCO
        3 iguales: RETRUCO
        4 iguales: VALE CUATRO
    */
    for (int i = 0; i < cantidad; i++) {
        if (usados[i]) continue;

        int iguales = 1;
        int subtotal = seleccionadas[i].getValor();

        for (int j = i + 1; j < cantidad; j++) {
            if (!usados[j] && seleccionadas[j].getNumero() == seleccionadas[i].getNumero()) {
                iguales++;
                subtotal += seleccionadas[j].getValor();
                usados[j] = 1;
            }
        }

        usados[i] = 1;

        if (iguales == 2) {
            puntos += subtotal * 4;
            if (nombreJugada != "") nombreJugada += " + ";
            nombreJugada += "TRUCO";
        }
        else if (iguales == 3) {
            puntos += subtotal * 12;
            if (nombreJugada != "") nombreJugada += " + ";
            nombreJugada += "RETRUCO";
        }
        else if (iguales == 4) {
            puntos += subtotal * 24;
            if (nombreJugada != "") nombreJugada += " + ";
            nombreJugada += "VALE CUATRO";
        }
    }

    /*
        Coincidencias por palo (solo en primera mano o si se tiene "Amanecer")
    */
    bool permitirEnvido = esPrimeraMano;
    for (const Comodin& c : comodinesActivos) {
        if (c.getNombre() == "Amanecer") {
            permitirEnvido = true;
            break;
        }
    }

    if (permitirEnvido) {
        for (int i = 0; i < cantidad; i++) usados[i] = 0;

        for (int i = 0; i < cantidad; i++) {
            if (usados[i]) continue;

            int iguales = 1;
            int subtotal = seleccionadas[i].getValor();

            for (int j = i + 1; j < cantidad; j++) {
                if (!usados[j] && seleccionadas[j].getPalo() == seleccionadas[i].getPalo()) {
                    iguales++;
                    subtotal += seleccionadas[j].getValor();
                    usados[j] = 1;
                }
            }

            usados[i] = 1;

            if (iguales == 2) {
                puntos += subtotal * 5;
                if (nombreJugada != "") nombreJugada += " + ";
                nombreJugada += "ENVIDO";
            }
            else if (iguales == 3) {
                puntos += subtotal * 15;
                if (nombreJugada != "") nombreJugada += " + ";
                nombreJugada += "REAL ENVIDO";
            }
            else if (iguales == 4) {
                puntos += subtotal * 30;
                if (nombreJugada != "") nombreJugada += " + ";
                nombreJugada += "FALTA ENVIDO";
            }
        }
    }

    // Comodin: SUBE (+500, pero -50 por ronda)
    for (const Comodin& c : comodinesActivos) {
        if (c.getNombre() == "Sube") {
            puntos += 500 - (50 * rondasGanadas);
        }
    }

    // Si no hubo ninguna jugada, pero tenemos "Anochecer", se multiplica el total por 20
    if (puntos == 0) {
        for (const Comodin& c : comodinesActivos) {
            if (c.getNombre() == "Anochecer") {
                nombreJugada = "ANOCHECER";
                return suma * 25;
            }
        }
        nombreJugada = "";
        return suma;
    }

    return puntos;
}

