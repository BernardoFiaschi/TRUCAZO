#include "Jugadas.h"
using namespace std;

int evaluarJugada(const Carta seleccionadas[], int cantidad, bool esPrimeraMano, string& nombreJugada, const vector<Comodin>& comodinesActivos, int rondasGanadas)
{
    nombreJugada = "";
    int puntos = 0;
    int suma = 0;
    int usados[4] = {0, 0, 0, 0};

    for (int i = 0; i < cantidad; i++)
    {
        suma += seleccionadas[i].getValor();
    }

    for (int i = 0; i < cantidad; i++)
    {
        for (const Comodin& comodin : comodinesActivos)
        {
            if (comodin.getNombre() == "Figuras")
            {
                int num = seleccionadas[i].getNumero();
                if (num == 10 || num == 11 || num == 12)
                {
                    suma += seleccionadas[i].getValor() * 4;
                }
            }
        }
    }

    for (int i = 0; i < cantidad; i++)
    {
        for (const Comodin& comodin : comodinesActivos)
        {
            if (comodin.getNombre() == "Sable de San Martin")
            {
                if (seleccionadas[i].getNumero() == 1 && seleccionadas[i].getPalo() == "espada")
                {
                    suma += 500 - seleccionadas[i].getValor();
                }
                else if (seleccionadas[i].getPalo() == "espada")
                {
                    suma += 35;
                }
            }
        }
    }


    for (int i = 0; i < cantidad; i++)
    {
        for (const Comodin& comodin : comodinesActivos)
        {
            if (comodin.getNombre() == "Dolar" && seleccionadas[i].getPalo() == "oro")
            {
                suma += seleccionadas[i].getValor() * ((5 + rondasGanadas) - 1);
            }
        }
    }

    for (int i = 0; i < cantidad; i++)
    {
        for (const Comodin& comodin : comodinesActivos)
        {
            if (comodin.getNombre() == "Copa del Mundo" && seleccionadas[i].getPalo() == "copa")
            {
                suma += seleccionadas[i].getValor() * 2;
            }
        }
    }


    for (int i = 0; i < cantidad; i++)
    {
        for (const Comodin& comodin : comodinesActivos)
        {
            if (comodin.getNombre() == "Arbol" && seleccionadas[i].getPalo() == "basto")
            {
                suma += seleccionadas[i].getValor() * 3;
            }
        }
    }

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
            puntos += subtotal * 4;
            if (nombreJugada != "") nombreJugada += " + ";
            nombreJugada += "TRUCO";
        }
        else if (iguales == 3)
        {
            puntos += subtotal * 12;
            if (nombreJugada != "") nombreJugada += " + ";
            nombreJugada += "RETRUCO";
        }
        else if (iguales == 4)
        {
            puntos += subtotal * 24;
            if (nombreJugada != "") nombreJugada += " + ";
            nombreJugada += "VALE CUATRO";
        }
    }

    bool permitirEnvido = esPrimeraMano;
    for (const Comodin& c : comodinesActivos)
    {
        if (c.getNombre() == "Amanecer")
        {
            permitirEnvido = true;
            break;
        }
    }

    if (permitirEnvido)
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

    for (const Comodin& c : comodinesActivos)
    {
        if (c.getNombre() == "Sube")
        {
            puntos += 500 - (50 * rondasGanadas);
        }
    }

    if (puntos == 0)
    {
        for (const Comodin& c : comodinesActivos)
        {
            if (c.getNombre() == "Anochecer")
            {
                nombreJugada = "ANOCHECER";
                return suma * 25;
            }
        }
        nombreJugada = "";
        return suma;
    }

    return puntos;
}

