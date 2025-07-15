#pragma once
#include "Carta.h"
#include "Comodin.h"
#include <SFML/Graphics.hpp>
#include <vector>

class EntreRondas {
public:
    static std::vector<Carta> seleccionarCartasEntreRondas(sf::RenderWindow& ventana, const std::vector<Carta>& mazoOriginal);
    static Comodin seleccionarComodin(sf::RenderWindow& ventana, const std::vector<Comodin>& mazoComodines);
};
