#include "ArchivoJugador.h"
#include <cstdio>
using namespace std;

/*
    Constructor de la clase ArchivoJugador
    Para que: establecer el nombre del archivo donde se van a guardar los datos.
    Como: simplemente define que se trabajar  con "Jugadores.dat".
*/
ArchivoJugador::ArchivoJugador() {
    _nombreArchivo = "Jugadores.dat";
}

/*
    Guarda un jugador al final del archivo (modo append)
    Para que: registrar un nuevo jugador en el archivo binario.
    Como: abre el archivo en modo "ab" (append binary) y escribe el struct.
*/
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

/*
    Guarda un jugador en una posicion espec¡fica del archivo
    Para que: actualizar un jugador ya existente (por ejemplo al finalizar una partida).
    Como: abre el archivo en modo "rb+" (lectura/escritura) y lo posiciona en la ubicacion deseada.
*/
bool ArchivoJugador::guardarJugador(const Jugador& jugador, int posicion) {
    FILE* pFile = fopen(_nombreArchivo.c_str(), "rb+");
    if (pFile == nullptr) return false;

    fseek(pFile, posicion * sizeof(Jugador), SEEK_SET);
    bool resultado = fwrite(&jugador, sizeof(Jugador), 1, pFile);
    fclose(pFile);

    return resultado;
}

/*
    Devuelve cu ntos jugadores hay guardados en total
    Para que: saber la cantidad de registros en el archivo binario.
    Como: se mueve al final del archivo y divide el tama¤o total por el tama¤o de un registro.
*/
int ArchivoJugador::getCantidadJugadores() {
    FILE* pFile = fopen(_nombreArchivo.c_str(), "rb");
    if (pFile == nullptr) return 0;

    fseek(pFile, 0, SEEK_END);
    int totalBytes = ftell(pFile);
    fclose(pFile);

    return totalBytes / sizeof(Jugador);
}

/*
    Lee un jugador en una posicion espec¡fica
    Para que: obtener los datos de un jugador por su posici¢n en el archivo.
    Como: se posiciona con `fseek` y lee un struct de tipo Jugador.
*/
Jugador ArchivoJugador::leer(int posicion) {
    Jugador jugador;
    FILE* pFile = fopen(_nombreArchivo.c_str(), "rb");
    if (pFile == nullptr) return jugador;

    fseek(pFile, posicion * sizeof(Jugador), SEEK_SET);
    fread(&jugador, sizeof(Jugador), 1, pFile);
    fclose(pFile);

    return jugador;
}

/*
    Busca a un jugador por su ID y devuelve la posici¢n
    Para que: saber en qu‚ posici¢n del archivo se encuentra un jugador espec¡fico.
    Como: recorre el archivo leyendo uno por uno hasta encontrar el ID buscado.
*/
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

/*
    Busca un jugador por su nombre
    Para que: recuperar los datos de un jugador si ya existe.
    Como: recorre el archivo hasta encontrar un nombre que coincida con el buscado.
          Si no lo encuentra, devuelve un jugador vac¡o.
*/
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
    return Jugador(); // Devuelve un jugador vac¡o si no se encontr¢
}
