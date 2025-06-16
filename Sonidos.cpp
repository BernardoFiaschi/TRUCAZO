#include "Sonidos.h"
#include <iostream>
using namespace std;

Sonidos::Sonidos()
{
    // M£sica de fondo
    if (!musicaFondo.openFromFile("sonidos/musicadefondo.wav"))
    {
        std::cerr << "Error al cargar musicadefondo.wav" << std::endl;
    }
    musicaFondo.setLoop(true);
    musicaFondo.setVolume(30);

    // Seleccionar carta
    if (bufferSeleccionar.loadFromFile("sonidos/seleccionar.wav"))
    {
        sonidoSeleccionar.setBuffer(bufferSeleccionar);
        sonidoSeleccionar.setVolume(100);
    }

    // Descartar
    if (bufferDescartar.loadFromFile("sonidos/descartar.wav"))
    {
        sonidoDescartar.setBuffer(bufferDescartar);
        sonidoDescartar.setVolume(100);
    }

    // Jugar
    if (bufferJugada.loadFromFile("sonidos/jugada.wav"))
    {
        sonidoJugada.setBuffer(bufferJugada);
        sonidoJugada.setVolume(100);
    }

    // Victoria
    if (bufferVictoria.loadFromFile("sonidos/victoria.wav"))
    {
        sonidoVictoria.setBuffer(bufferVictoria);
        sonidoVictoria.setVolume(50);
    }

    // Derrota
    if (bufferDerrota.loadFromFile("sonidos/derrota.wav"))
    {
        sonidoDerrota.setBuffer(bufferDerrota);
        sonidoDerrota.setVolume(30);
    }

}

void Sonidos::reproducirSeleccionar() {
    sonidoSeleccionar.play();
}

void Sonidos::reproducirDescartar() {
    sonidoDescartar.play();
}

void Sonidos::reproducirJugada() {
    sonidoJugada.play();
}

void Sonidos::reproducirVictoria() {
    sonidoVictoria.play();
}

void Sonidos::detenerVictoria() {
    sonidoVictoria.stop();
}

void Sonidos::reproducirDerrota() {
    sonidoDerrota.play();
}

void Sonidos::detenerDerrota() {
    sonidoDerrota.stop();
}

void Sonidos::reproducirMusicaFondo() {
    if (musicaFondo.getStatus() != sf::SoundSource::Playing)
        musicaFondo.play();
}

void Sonidos::detenerMusicaFondo() {
    musicaFondo.stop();
}

Sonidos& Sonidos::get() {
    static Sonidos instancia;
    return instancia;
}
