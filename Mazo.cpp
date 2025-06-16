#include<iostream>
#include "Mazo.h"
#include<cstdlib>
#include<ctime>
#include<stack>
using namespace std;

// --- FUNCIONES AUXILIARES PRIVADAS ---
vector<Carta> Mazo::inicializarMazoOriginal() {
    return CartasMazo();
}

void Mazo::mezclarMazo(vector<Carta>& iniciales) {
    srand(time(nullptr));
    while (!iniciales.empty()) {
        int indice = rand() % iniciales.size();
        pilaCartas.push(iniciales[indice]);
        iniciales.erase(iniciales.begin() + indice);
    }
}

void Mazo::cargarPilaCartas(vector<Carta>& mezcladas) {
    pilaCartas = stack<Carta>();
    for (auto it = mezcladas.rbegin(); it != mezcladas.rend(); ++it)
        pilaCartas.push(*it);
}

// --- FUNCIONES ORIGINALES ---

Mazo::Mazo() {
    vector<Carta> iniciales = inicializarMazoOriginal();
    mazoOriginal = iniciales;
    cantidadCartasDisponibles = 40;
    mezclarMazo(iniciales);
}

bool Mazo::repartirCartas() {
    if (pilaCartas.size() < 5) {
        cout << "No hay mas cartas para repartir." << endl;
        return false;
    }
    cartasJugador.clear();
    for (int x = 0; x < 5; x++) {
        cartasJugador.push_back(pilaCartas.top());
        pilaCartas.pop();
        cantidadCartasDisponibles--;
    }
    return true;
}

bool Mazo::darCartas(int cantidad, vector<Carta>& nuevasCartas) {
    nuevasCartas.clear();
    if (pilaCartas.size() < cantidad) return false;
    for (int x = 0; x < cantidad; x++) {
        nuevasCartas.push_back(pilaCartas.top());
        pilaCartas.pop();
        cantidadCartasDisponibles--;
    }
    return true;
}

void Mazo::mostrarCartasJugador() const {
    cout << "==================================" << endl;
    cout << "Tus cartas son: " << endl << endl;
    for (const Carta& c : cartasJugador)
        c.mostrar();
}

void Mazo::mostrarCartasDisponibles() const {
    cout << "Cartas restantes en el mazo: " << pilaCartas.size() << endl;
    stack<Carta> copia = pilaCartas;
    while (!copia.empty()) {
        copia.top().mostrar();
        copia.pop();
    }
}

void Mazo::mostrarMazoOriginal() const {
    cout << "Mazo original: " << endl;
    for (const Carta& c : mazoOriginal)
        c.mostrar();
}

const vector<Carta>& Mazo::getMazoOriginal() const {
    return mazoOriginal;
}
const Carta* Mazo::getCartasJugador() const {
    return cartasJugador.data();
}
int Mazo::getCantidadCartasJugador() const {
    return cartasJugador.size();
}
int Mazo::getCantidadCartasDisponibles() const {
    return cantidadCartasDisponibles;
}

vector<Carta> Mazo::CartasMazo() {
    vector<Carta> cartas = {
        Carta(1, "espada", 1, 50),   Carta(1, "basto", 2, 35),   Carta(7, "espada", 3, 30),
        Carta(7, "oro", 4, 25),      Carta(3, "espada", 5, 20),  Carta(3, "basto", 6, 20),
        Carta(3, "oro", 7, 20),      Carta(3, "copa", 8, 20),    Carta(2, "espada", 9, 15),
        Carta(2, "basto", 10, 15),   Carta(2, "oro", 11, 15),    Carta(2, "copa", 12, 15),
        Carta(1, "oro", 13, 11),     Carta(1, "copa", 14, 11),   Carta(12, "espada", 15, 10),
        Carta(12, "basto", 16, 10),  Carta(12, "oro", 17, 10),   Carta(12, "copa", 18, 10),
        Carta(11, "espada", 19, 9),  Carta(11, "basto", 20, 9),  Carta(11, "oro", 21, 9),
        Carta(11, "copa", 22, 9),    Carta(10, "espada", 23, 8), Carta(10, "basto", 24, 8),
        Carta(10, "oro", 25, 8),     Carta(10, "copa", 26, 8),   Carta(7, "basto", 27, 7),
        Carta(7, "copa", 28, 7),     Carta(6, "espada", 29, 6),  Carta(6, "basto", 30, 6),
        Carta(6, "oro", 31, 6),      Carta(6, "copa", 32, 6),    Carta(5, "espada", 33, 5),
        Carta(5, "basto", 34, 5),    Carta(5, "oro", 35, 5),     Carta(5, "copa", 36, 5),
        Carta(4, "espada", 37, 4),   Carta(4, "basto", 38, 4),   Carta(4, "oro", 39, 4),
        Carta(4, "copa", 40, 4)
    };
    return cartas;
}