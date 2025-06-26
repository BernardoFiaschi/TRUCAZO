#include "Sonidos.h"
#include <iostream>
using namespace std;

/*
   Constructor de la clase Sonidos
   Carga todos los efectos de sonido y la m£sica de fondo desde los archivos.
   Esto se hace una sola vez al iniciar el juego, y queda en memoria.
*/
Sonidos::Sonidos()
{
    // Carga de la m£sica de fondo
    if (!musicaFondo.openFromFile("sonidos/musicadefondo.wav"))
    {
        cerr << "Error al cargar musicadefondo.wav" << endl;
    }
    musicaFondo.setLoop(true);    // La m£sica se repite en bucle
    musicaFondo.setVolume(20);

    // Efecto al seleccionar una carta
    if (bufferSeleccionar.loadFromFile("sonidos/seleccionar.wav"))
    {
        sonidoSeleccionar.setBuffer(bufferSeleccionar);
        sonidoSeleccionar.setVolume(100);
    }

    // Efecto al descartar carta
    if (bufferDescartar.loadFromFile("sonidos/descartar.wav"))
    {
        sonidoDescartar.setBuffer(bufferDescartar);
        sonidoDescartar.setVolume(100);
    }

    // Efecto cuando se realiza una jugada (TRUCO, ENVIDO, etc.)
    if (bufferJugada.loadFromFile("sonidos/jugada.wav"))
    {
        sonidoJugada.setBuffer(bufferJugada);
        sonidoJugada.setVolume(100);
    }

    // Efecto de victoria
    if (bufferVictoria.loadFromFile("sonidos/victoria.wav"))
    {
        sonidoVictoria.setBuffer(bufferVictoria);
        sonidoVictoria.setVolume(40);
    }

    // Efecto de derrota
    if (bufferDerrota.loadFromFile("sonidos/derrota.wav"))
    {
        sonidoDerrota.setBuffer(bufferDerrota);
        sonidoDerrota.setVolume(30);
    }
}

/* Efecto de sonido al seleccionar una carta */
void Sonidos::reproducirSeleccionar() {
    sonidoSeleccionar.play();
}

/* Efecto al descartar una carta */
void Sonidos::reproducirDescartar() {
    sonidoDescartar.play();
}

/* Efecto cuando se hace una jugada (como TRUCO o ENVIDO) */
void Sonidos::reproducirJugada() {
    sonidoJugada.play();
}

/* Sonido que suena si se gana una ronda */
void Sonidos::reproducirVictoria() {
    sonidoVictoria.play();
}

/* Detiene el sonido de victoria si estaba sonando */
void Sonidos::detenerVictoria() {
    sonidoVictoria.stop();
}

/* Sonido que suena si se pierde una ronda */
void Sonidos::reproducirDerrota() {
    sonidoDerrota.play();
}

/* Detiene el sonido de derrota si estaba sonando */
void Sonidos::detenerDerrota() {
    sonidoDerrota.stop();
}

/* Reproduce la m£sica de fondo, si no est  ya sonando */
void Sonidos::reproducirMusicaFondo() {
    if (musicaFondo.getStatus() != sf::SoundSource::Playing)
        musicaFondo.play();
}

/* Detiene la m£sica de fondo */
void Sonidos::detenerMusicaFondo() {
    musicaFondo.stop();
}

/*
   Devuelve la instancia £nica de esta clase
   Se usa un singleton para que toda la l¢gica de sonido pase por un solo lugar.
   As¡ evitamos cargar sonidos m£ltiples veces o tener bugs de audio.
*/
Sonidos& Sonidos::get() {
    static Sonidos instancia;
    return instancia;
}

