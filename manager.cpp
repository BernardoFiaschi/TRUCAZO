#include"manager.h"
#include "menu.h"
#include "Mazo.h"
#include "Partida.h"
#include "Jugador.h"
#include "Sonidos.h"
#include <SFML/Audio.hpp>
#include<iostream>
using namespace std;


Manager::Manager(): jugador(1,"",0,0) {}

void Manager::mostrarMenu(sf::RenderWindow& ventana)
{
    Menu menu(ventana);
    menu.ejecutar();
}

void Manager::mostrarMazo(sf::RenderWindow& ventana)
{

    ventana.clear();
    int cartasEnFila=0;
    int x=50,y=50;
    for(const Carta& carta : mazo.getMazoOriginal())
    {
        int id=carta.getIdCarta();

        sf::Texture texturaCarta;
        if(!texturaCarta.loadFromFile("cartas/" + to_string(id) + ".png"))
        {
            cout<<"Error cargando la textura de cartas!"<<id<<endl;
            continue;
        }
        sf::Sprite cartaSprite;
        cartaSprite.setTexture(texturaCarta);
        cartaSprite.setPosition(x,y);
        ventana.draw(cartaSprite);

        x +=65;
        cartasEnFila++;
        if(cartasEnFila==10)
        {
            cartasEnFila=0;
            x =50;
            y +=110;
        }
    }
    ventana.display();

    bool esperando=true;
    while(esperando && ventana.isOpen())
    {
        sf::Event ev;
        while(ventana.pollEvent(ev))
        {
            if(ev.type == sf::Event::Closed)ventana.close();
            if(ev.type == sf::Event::KeyPressed)esperando= false;
        }
    }
}

void Manager::iniciarPartida(sf::RenderWindow& ventana)
{
    Jugador jugador;
    Partida partida(jugador);

    partida.iniciar(ventana);
}

void Manager::mostrarMensaje(sf::RenderWindow& ventana,const string& mensaje)
{
    sf::Font fuente;
    fuente.loadFromFile("fuentes/Poppins-Regular.ttf");

    sf::Text texto;
    texto.setFont(fuente);
    texto.setCharacterSize(26);
    texto.setFillColor(sf::Color::Yellow);
    texto.setString(mensaje + " ENTER para continuar...");
    texto.setPosition(100,250);

    while(ventana.isOpen())
    {
        sf::Event event;
        while(ventana.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)ventana.close();
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)return;
        }
        ventana.clear();
        ventana.draw(texto);
        ventana.display();
    }
}

void Manager::finalizarRonda(sf::RenderWindow& ventana, bool victoria, Partida& partida)
{
    int numeroRonda = partida.getRondaActual();
    if (numeroRonda >= 15) numeroRonda = 14;

    sf::Texture fondo;
    if (victoria)
    {
        fondo.loadFromFile("fondos/RONDAGANADA.png");
        jugador.sumarPuntos(partida.getPuntajeRonda());
        jugador.aumentarPartidas();
        Sonidos::get().detenerMusicaFondo();
        Sonidos::get().reproducirVictoria();
    }
    else
    {
        fondo.loadFromFile("fondos/DERROTA.png");
        Sonidos::get().detenerMusicaFondo();
        Sonidos::get().reproducirDerrota();
    }

    sf::Sprite spriteFondo(fondo);

    sf::Font fuente;
    fuente.loadFromFile("fuentes/Poppins-Regular.ttf");

    sf::Text texto;
    texto.setFont(fuente);
    texto.setString(victoria ? "RONDA GANADA" : "DERROTA");
    texto.setCharacterSize(40);
    texto.setFillColor(sf::Color(255, 255, 255, 200));
    texto.setStyle(sf::Text::Bold);
    texto.setPosition(ventana.getSize().x / 2.f - 360, 500);

    sf::Text instruccion;
    instruccion.setFont(fuente);
    instruccion.setString("Presione ENTER para continuar");
    instruccion.setCharacterSize(20);
    instruccion.setFillColor(sf::Color(255, 255, 255, 160));
    instruccion.setPosition(ventana.getSize().x / 2.f - 340, 550);

    ventana.clear();
    ventana.draw(spriteFondo);
    ventana.draw(texto);
    ventana.draw(instruccion);
    ventana.display();

    // Esperar ENTER
    bool esperando = true;
    while (esperando && ventana.isOpen())
    {
        sf::Event event;
        while (ventana.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) ventana.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
                esperando = false;
        }
    }

    // Restaurar m£sica si sigue el juego
    if (victoria && ventana.isOpen())
    {
        Sonidos::get().detenerVictoria();
        Sonidos::get().reproducirMusicaFondo();
    }
      else
    {
        Sonidos::get().detenerDerrota();
        Sonidos::get().reproducirMusicaFondo(); // Detener sonido de derrota al volver al men£
    }
}

void Manager::mostrarCreditos(sf::RenderWindow& ventana)
{
    sf::Font fuente;
    if(!fuente.loadFromFile("fuentes/Poppins-Regular.ttf"))
    {
        cout<<"No se pudo cargar la fuente de los creditos."<<endl;
        return;
    }

    sf::Text creditos;
    creditos.setFont(fuente);
    creditos.setString("=================="
                       "*     TRUCAZO    *"
                       "=================="
                       "Desarrollado por:"
                       "Angeles Albornoz-"
                       "Bernardo Fiaschi-"
                       "Raul Luppini"
                       "C++ con SFML -2025"
                       "Gracias por jugar!"
                       "==================");
    creditos.setCharacterSize(28);
    creditos.setFillColor(sf::Color::White);
    creditos.setPosition(100,100);

    ventana.clear(sf::Color::Black);
    ventana.draw(creditos);
    ventana.display();

    bool esperando=true;
    while(esperando && ventana.isOpen())
    {
        sf::Event evento;
        while(ventana.pollEvent(evento))
        {
            if(evento.type == sf::Event::Closed)ventana.close();
            if(evento.type == sf::Event::KeyPressed)esperando=false;
        }
    }

}
