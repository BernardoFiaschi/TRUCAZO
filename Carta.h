#pragma once
#include <string>


class Carta
{
private:
    int numero;
    std::string palo;
    int idCarta;
    int valor;

public:
    Carta();
    Carta(int num, std::string p, int id, int pts);
    int getNumero() const;
    std::string getPalo() const;
    int getIdCarta() const;
    int getValor() const;
};

