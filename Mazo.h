#pragma once
#include<vector>
#include<stack>
#include "Carta.h"
#include "Comodin.h"
using namespace std;

class Mazo
{
private:
    std::stack<Carta> pilaCartas;
    std::vector<Carta> cartasJugador;
    std::vector<Carta> mazoOriginal;
    int cantidadCartasDisponibles;
    std::vector<Carta> inicializarMazoOriginal();
    void mezclarMazo(std::vector<Carta>& iniciales);
    std::stack<Comodin> pilaComodines;
    std::vector<Comodin> mazoDeComodines;
    std::vector<Comodin> comodinesJugador;
    int cantidadComodinesDisponibles;
    std::vector<Comodin> inicializarMazoComodin();
    void mezclarComodines(std::vector<Comodin>& especiales);

public:
    Mazo();
    bool repartirCartas();
    bool darCartas(int cantidad,std::vector<Carta>& nuevasCartas);
    const std::vector<Carta>& getMazoOriginal() const;
    const Carta* getCartasJugador() const;
    int getCantidadCartasJugador() const;
    int getCantidadCartasDisponibles() const;
    static std::vector<Carta> CartasMazo();
    void generarCartasOpcionales(int cantidad,std::vector<Carta>& destino);
    void agregarCartaExtra(const Carta& c);
    static std::vector<Comodin> ComodinMazo();
    const std::vector<Comodin>& getMazoComodines() const;
};
