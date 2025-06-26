#pragma once
#include "Carta.h"
#include "Comodin.h"
#include <vector>
#include <string>

/*
    Esta funcion evalua la jugada realizada por el jugador,
    detecta combinaciones validas y calcula el puntaje total.

    Parametros:
    - seleccionadas: arreglo de cartas jugadas en el turno.
    - cantidad: cantidad de cartas seleccionadas (max 4).
    - esPrimeraMano: true si es la primera jugada de la ronda.
    - nombreJugada: se devuelve una descripcion textual de las combinaciones detectadas.
    - comodinesActivos: lista de comodines seleccionados que modifican el puntaje.
    - rondasGanadas: cantidad de rondas ganadas hasta ahora (para aplicar efectos como Dolar o Sube).

    Devuelve:
    - Puntaje total calculado segun la combinacion y los comodines aplicados.
*/
int evaluarJugada(const Carta seleccionadas[], int cantidad, bool esPrimeraMano,
                  std::string& nombreJugada, const std::vector<Comodin>& comodinesActivos,
                  int rondasGanadas);
