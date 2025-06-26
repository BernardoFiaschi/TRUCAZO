#pragma once
#include "Carta.h"
#include "Comodin.h"
#include <SFML/Graphics.hpp>
#include <vector>


/*
    Clase EntreRondas

    Para que: mostrar una pantalla especial entre rondas ganadas
              donde el jugador puede elegir hasta 2 cartas nuevas
              para agregar a su mazo por el resto de la partida.

    Por que: agrega una mecanica de progresion y estrategia visual,
             recompensando al jugador con nuevas cartas al ganar.

    Como: se muestran 4 cartas aleatorias del mazo original, el
          jugador puede elegir 1 o 2 usando el teclado numerico,
          y se devuelven esas cartas como vector.
*/
class EntreRondas {
public:
    static std::vector<Carta> seleccionarCartasEntreRondas(sf::RenderWindow& ventana, const std::vector<Carta>& mazoOriginal);
    static Comodin seleccionarComodin(sf::RenderWindow& ventana, const std::vector<Comodin>& mazoComodines);
};
