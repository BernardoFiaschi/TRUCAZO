#include "Carta.h"
#include <iostream>
using namespace std;

int main()
    {
    vector<Carta> cartas = listarCartasMazo();

    for (const Carta& c : cartas) {
        c.mostrar();
    }

    return 0;
}
