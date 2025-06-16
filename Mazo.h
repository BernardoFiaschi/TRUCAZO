#pragma once
#include<vector>
#include<stack>
#include "Carta.h"
class Mazo
{
private:
    std::stack<Carta> pilaCartas;
    std::vector<Carta> cartasJugador;
    std::vector<Carta> mazoOriginal;
    int cantidadCartasDisponibles;
public:
    Mazo();
    bool repartirCartas();
    bool darCartas(int cantidad,std::vector<Carta>& nuevasCartas);
    void mostrarCartasJugador() const;
    void mostrarCartasDisponibles() const;
    void mostrarMazoOriginal() const;
    const std::vector<Carta>& getMazoOriginal() const;
    const Carta* getCartasJugador() const;
    int getCantidadCartasJugador() const;
    int getCantidadCartasDisponibles() const;
    static std::vector<Carta> CartasMazo();
};
