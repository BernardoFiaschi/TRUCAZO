#include "Jugadas.h"
using namespace std;

int evaluarJugada(const Carta seleccionadas[], int cantidad, bool esPrimeraMano, string& nombreJugada) {
    nombreJugada = "";
    int puntos = 0;
    int suma = 0;
    int usados[4] = {0, 0, 0, 0};

    for (int i = 0; i < cantidad; i++)
    {
        suma += seleccionadas[i].getValor();
    }

    // Verificar FLOR DE TRUCO (4 iguales n£mero y palo)
    bool mismoNum = true, mismoPalo = true;
    for (int i = 1; i < cantidad; i++)
    {
        if (seleccionadas[i].getNumero() != seleccionadas[0].getNumero()) mismoNum = false;
        if (seleccionadas[i].getPalo() != seleccionadas[0].getPalo()) mismoPalo = false;
    }
    if (cantidad == 4 && mismoNum && mismoPalo)
    {
        nombreJugada = "FLOR DE TRUCO";
        return suma * 150;
    }

    // Combinaciones por n£mero (TRUCO, RETRUCO, VALE CUATRO)
    for (int i = 0; i < cantidad; i++)
        {
        if (usados[i]) continue;
        int iguales = 1;
        int subtotal = seleccionadas[i].getValor();
        for (int j = i + 1; j < cantidad; j++)
        {
            if (!usados[j] && seleccionadas[j].getNumero() == seleccionadas[i].getNumero())
            {
                iguales++;
                subtotal += seleccionadas[j].getValor();
                usados[j] = 1;
            }
        }
        usados[i] = 1;

        if (iguales == 2)
        {
            puntos += subtotal * 2;
            if (nombreJugada != "") nombreJugada += " + ";
            nombreJugada += "TRUCO";
        }
        else if (iguales == 3)
        {
            puntos += subtotal * 4;
            if (nombreJugada != "") nombreJugada += " + ";
            nombreJugada += "RETRUCO";
        }
        else if (iguales == 4)
        {
            puntos += subtotal * 16;
            if (nombreJugada != "") nombreJugada += " + ";
            nombreJugada += "VALE CUATRO";
        }
    }

    // Combinaciones por palo (ENVIDO, etc) solo en primera mano
    if (esPrimeraMano)
    {
        for (int i = 0; i < cantidad; i++) usados[i] = 0;
        for (int i = 0; i < cantidad; i++)
        {
            if (usados[i]) continue;
            int iguales = 1;
            int subtotal = seleccionadas[i].getValor();
            for (int j = i + 1; j < cantidad; j++)
            {
                if (!usados[j] && seleccionadas[j].getPalo() == seleccionadas[i].getPalo())
                {
                    iguales++;
                    subtotal += seleccionadas[j].getValor();
                    usados[j] = 1;
                }
            }
            usados[i] = 1;

            if (iguales == 2)
            {
                puntos += subtotal * 5;
                if (nombreJugada != "") nombreJugada += " + ";
                nombreJugada += "ENVIDO";
            }
            else if (iguales == 3)
            {
                puntos += subtotal * 15;
                if (nombreJugada != "") nombreJugada += " + ";
                nombreJugada += "REAL ENVIDO";
            }
            else if (iguales == 4)
            {
                puntos += subtotal * 30;
                if (nombreJugada != "") nombreJugada += " + ";
                nombreJugada += "FALTA ENVIDO";
            }
        }
    }

    // Si no hubo combinaciones, sumar directo el total
    if (puntos == 0)
    {
        nombreJugada = "";
        return suma;
    }

    return puntos;
}
