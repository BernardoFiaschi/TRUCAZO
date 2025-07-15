#pragma once
#include "Carta.h"
#include "Comodin.h"
#include <vector>
#include <string>

int evaluarJugada(const Carta seleccionadas[], int cantidad, bool esPrimeraMano,
                  std::string& nombreJugada, const std::vector<Comodin>& comodinesActivos,
                  int rondasGanadas);
