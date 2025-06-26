#pragma once
#include <SFML/Audio.hpp>
#include <string>

class Sonidos {
private:
    sf::Music musicaFondo;
    sf::SoundBuffer bufferSeleccionar;
    sf::SoundBuffer bufferDescartar;
    sf::SoundBuffer bufferJugada;
    sf::SoundBuffer bufferVictoria;
    sf::SoundBuffer bufferDerrota;
    sf::Sound sonidoSeleccionar;
    sf::Sound sonidoDescartar;
    sf::Sound sonidoJugada;
    sf::Sound sonidoVictoria;
    sf::Sound sonidoDerrota;
    Sonidos();

public:

    void reproducirSeleccionar();
    void reproducirDescartar();
    void reproducirJugada();
    void reproducirVictoria();
    void detenerVictoria();
    void reproducirDerrota();
    void detenerDerrota();
    void reproducirMusicaFondo();
    void detenerMusicaFondo();
    static Sonidos& get();
};

