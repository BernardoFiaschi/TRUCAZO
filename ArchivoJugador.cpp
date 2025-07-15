#include "ArchivoJugador.h"
#include <cstdio>
using namespace std;

ArchivoJugador::ArchivoJugador() {
    _nombreArchivo = "Jugadores.dat";
}

bool ArchivoJugador::guardarJugador(const Jugador& jugador) {
    FILE* pFile = fopen(_nombreArchivo.c_str(), "ab");
    if (pFile == nullptr) {
        cerr << "Error al abrir el archivo para escribir!" << endl;
        return false;
    }

    bool resultado = fwrite(&jugador, sizeof(Jugador), 1, pFile);
    fclose(pFile);

    if (!resultado) {
        cerr << "Error al guardar el jugador." << endl;
    }

    return resultado;
}

bool ArchivoJugador::guardarJugador(const Jugador& jugador, int posicion) {
    FILE* pFile = fopen(_nombreArchivo.c_str(), "rb+");
    if (pFile == nullptr) return false;

    fseek(pFile, posicion * sizeof(Jugador), SEEK_SET);
    bool resultado = fwrite(&jugador, sizeof(Jugador), 1, pFile);
    fclose(pFile);

    return resultado;
}

int ArchivoJugador::getCantidadJugadores() {
    FILE* pFile = fopen(_nombreArchivo.c_str(), "rb");
    if (pFile == nullptr) return 0;

    fseek(pFile, 0, SEEK_END);
    int totalBytes = ftell(pFile);
    fclose(pFile);

    return totalBytes / sizeof(Jugador);
}

Jugador ArchivoJugador::leer(int posicion) {
    Jugador jugador;
    FILE* pFile = fopen(_nombreArchivo.c_str(), "rb");
    if (pFile == nullptr) return jugador;

    fseek(pFile, posicion * sizeof(Jugador), SEEK_SET);
    fread(&jugador, sizeof(Jugador), 1, pFile);
    fclose(pFile);

    return jugador;
}

int ArchivoJugador::buscarJugadorPorId(int id) {
    FILE* pFile = fopen(_nombreArchivo.c_str(), "rb");
    if (pFile == nullptr) return -1;

    Jugador aux;
    int pos = 0;

    while (fread(&aux, sizeof(Jugador), 1, pFile)) {
        if (aux.getId() == id) {
            fclose(pFile);
            return pos;
        }
        pos++;
    }

    fclose(pFile);
    return -1;
}

Jugador ArchivoJugador::buscarJugador(const string& nombre) {
    Jugador aux;
    FILE* pFile = fopen(_nombreArchivo.c_str(), "rb");
    if (pFile == nullptr) return aux;

    while (fread(&aux, sizeof(Jugador), 1, pFile)) {
        if (aux.getNombre() == nombre) {
            fclose(pFile);
            return aux;
        }
    }

    fclose(pFile);
    return Jugador();
}
