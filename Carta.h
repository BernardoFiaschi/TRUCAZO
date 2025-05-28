#pragma once
#include <string>
#include <vector>
using namespace std;

class Carta {
private:
    int numero;
    string palo;
    int idCarta;
    int valor;

public:
    Carta();
    Carta(int num, string p, int id, int pts);

    int getNumero() const;
    string getPalo() const;
    int getIdCarta() const;
    int getValor() const;

    void mostrar() const;
};

vector<Carta> listarCartasMazo();
