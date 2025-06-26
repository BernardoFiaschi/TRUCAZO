#include "Mazo.h"
#include <cstdlib>
#include <ctime>
#include <stack>
#include <iostream>
using namespace std;

/*
   Esta funcion genera el mazo base con las 40 cartas originales.
   Para que: tengamos un mazo inicial bien definido para el juego.
   Como: simplemente llama a CartasMazo() que arma el vector de cartas.
*/
vector<Carta> Mazo::inicializarMazoOriginal() {
    return CartasMazo();
}

/*
   Mezcla el mazo de forma aleatoria y lo guarda como pila.
   Para que: las cartas salgan en orden distinto cada vez.
   Como: elige una carta al azar del vector y la mete en la pila,
          repitiendo hasta vaciar el vector.
*/
void Mazo::mezclarMazo(vector<Carta>& iniciales) {
   // Inicializa el random con la hora actual
    while (!iniciales.empty()) {
        int indice = rand() % iniciales.size();
        pilaCartas.push(iniciales[indice]);             // Mete carta aleatoria en la pila
        iniciales.erase(iniciales.begin() + indice);    // La saca del vector
    }
}

/*
   Constructor del mazo
   Para que: preparar todo desde cero cada vez que arranca una partida.
   Como: genera el mazo original, lo guarda y lo mezcla para jugar.
*/
Mazo::Mazo() {
    vector<Carta> iniciales = inicializarMazoOriginal();
    mazoOriginal = iniciales;
    cantidadCartasDisponibles = 40;
    mezclarMazo(iniciales);

    vector<Comodin> especiales =inicializarMazoComodin();
    mazoDeComodines=especiales;
    cantidadComodinesDisponibles = mazoDeComodines.size();
}
/*
   Reparte las 5 cartas iniciales al jugador desde la pila.
   Para que: el jugador arranque con una mano completa.
   Como: saca 5 cartas del tope de la pila y las guarda.
*/
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

/*
   Da nuevas cartas al jugador (por ejemplo, si descarto o jugo).
   Para que: el jugador pueda tener siempre una mano completa.
   Como: saca X cartas de la pila y las guarda en el vector recibido.
*/
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

/*
   Devuelve el mazo original completo (sin mezclar)
   Para que: se pueda mostrar o consultar desde otros lados.
*/
const vector<Carta>& Mazo::getMazoOriginal() const {
    return mazoOriginal;
}

/*
   Devuelve las cartas que tiene actualmente el jugador en mano.
   Como puntero constante al arreglo de cartas.
*/
const Carta* Mazo::getCartasJugador() const {
    return cartasJugador.data();
}

/*
   Devuelve cuantas cartas tiene actualmente el jugador.
   El tama¤o del vector cartasJugador.
*/
int Mazo::getCantidadCartasJugador() const {
    return cartasJugador.size();
}

/*
   Devuelve cuantas cartas quedan en la pila del mazo.
   Esto sirve para verificar si quedan cartas.
*/
int Mazo::getCantidadCartasDisponibles() const {
    return cantidadCartasDisponibles;
}

void Mazo::agregarCartaExtra(const Carta& c) {
    pilaCartas.push(c);
    cantidadCartasDisponibles++;
}

/*
   Define el contenido fijo del mazo del juego.
   Para que: haya cartas bien definidas con sus valores, nombres, palos y puntaje.
   Como: se arma un vector con todas las 40 cartas manualmente.
*/
vector<Carta> Mazo::CartasMazo() {
    vector<Carta> cartas = {
        Carta(1, "espada", 1, 100),   Carta(1, "basto", 2, 50),   Carta(7, "espada", 3, 30),
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

vector<Comodin> Mazo::ComodinMazo()
{
    vector<Comodin> comodines = {
        Comodin(1, "Cafe", "Da 2 descartes extra"),
        Comodin(2, "Amanecer", "Permite usar Envido, RealEnvido y FaltaEnvido en la ultima jugada"),
        Comodin(3, "Anochecer", "Si no hay jugada valida, multiplica por 25 el total"),
        Comodin(4, "Arbol", "Todas las cartas de basto reciben por 4 al ser jugadas"),
        Comodin(5, "Figuras", "Las cartas 10, 11 y 12 reciben x5 a sus valor"),
        Comodin(6, "Mate", "+2 jugadas adicionales"),
        Comodin(7, "Sable de San Martin", "El ancho de espada vale 500. Otras cartas de espada suman +35 a su valor"),
        Comodin(8, "Dolar", "Todas las cartas de oro se multiplican por (5 + rondas ganadas)"),
        Comodin(9, "Sube", "+500 puntos antes de multiplicar. Pierde 50 por ronda ganada"),
        Comodin(10, "Copa del Mundo", "Todas las cartas de copa se multiplican por 3 al ser jugadas")
    };

    return comodines;
}


vector<Comodin> Mazo::inicializarMazoComodin()
{
    return ComodinMazo();
}

void Mazo::mezclarComodines(vector<Comodin>& especiales)
{
    while (!especiales.empty()) {
        int indice = rand() % especiales.size();
        pilaComodines.push(especiales[indice]);             // Mete carta aleatoria en la pila
        especiales.erase(especiales.begin() + indice);    // La saca del vector
    }

}

const vector<Comodin>& Mazo::getMazoComodines() const
{
    return mazoDeComodines;
}
