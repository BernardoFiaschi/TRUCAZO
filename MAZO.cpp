#include <iostream>
#include <cstring>
#include "MAZO.h"
using namespace std;

void MAZO::cargar() {
    cout << "ID Carta: ";
    cin >> _idCarta;
    cin.ignore();

    cout << "Nombre: ";
    cin.getline(_nombre, 30);

    cout << "Numero de carta: ";
    cin >> _numeroCarta;
    cin.ignore();

    cout << "Palo: ";
    cin.getline(_palo, 10);

    cout << "Valor: ";
    cin >> _valor;
}

void MAZO::mostrar() {
    cout << "ID Carta: " << _idCarta << endl;
    cout << "Nombre: " << _nombre << endl;
    cout << "Numero: " << _numeroCarta << endl;
    cout << "Palo: " << _palo << endl;
    cout << "Valor: " << _valor << endl;
}

// Getters
int MAZO::getIdCarta() { return _idCarta; }
const char* MAZO::getNombre() { return _nombre; }
int MAZO::getNumeroCarta() { return _numeroCarta; }
const char* MAZO::getPalo() { return _palo; }
int MAZO::getValor() { return _valor; }

// Setters
void MAZO::setIdCarta(int id) { _idCarta = id; }
void MAZO::setNombre(const char* nombre) { strcpy(_nombre, nombre); }
void MAZO::setNumeroCarta(int num) { _numeroCarta = num; }
void MAZO::setPalo(const char* palo) { strcpy(_palo, palo); }
void MAZO::setValor(int valor) { _valor = valor; }
