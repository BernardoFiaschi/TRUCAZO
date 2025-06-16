#include "menu.h"
#include "Mazo.h"
#include "manager.h"
#include "Sonidos.h"
#include <SFML/Audio.hpp>
#include<iostream>
#include<string>
#include<cstring>
using namespace std;

// --- FUNCIONES AUXILIARES PRIVADAS ---
void Menu::dibujarMenu() {
    ventana.clear();
    ventana.draw(spriteFondo);
    ventana.draw(titulo);
    for(int x=0;x<5;x++) {
        if(x == opcionSeleccionada) opciones[x].setFillColor(sf::Color::Yellow);
        else opciones[x].setFillColor(sf::Color::White);
        ventana.draw(opciones[x]);
    }
    ventana.display();
}
void Menu::gestionarEventos(Manager& cargar, bool& terminar) {
    sf::Event evento;
    while(ventana.pollEvent(evento)) {
        if(evento.type==sf::Event::Closed) ventana.close();
        if(evento.type==sf::Event::KeyPressed) {
            if(evento.key.code == sf::Keyboard::Up) opcionSeleccionada= (opcionSeleccionada - 1 + 5)%5;
            if(evento.key.code == sf::Keyboard::Down) opcionSeleccionada= (opcionSeleccionada + 1)%5;
            if(evento.key.code == sf::Keyboard::Enter) {
                cout<<"Opcion seleccionada: "<<opcionSeleccionada + 1 <<endl;
                if(opcionSeleccionada == 0) cargar.iniciarPartida(ventana);
                if(opcionSeleccionada == 2) cargar.mostrarMazo(ventana);
                if(opcionSeleccionada == 3) cargar.mostrarCreditos(ventana);
                if(opcionSeleccionada == 4) ventana.close();
            }
        }
    }
}

// --- FUNCIONES ORIGINALES ---
Menu::Menu(sf::RenderWindow& v) : ventana(v), opcionSeleccionada(0) {
    if(!fuente.loadFromFile("fuentes/Poppins-Regular.ttf")) {
        cerr<<"Error cargando la fuente!"<<endl;
    }
    if (!texturaFondo.loadFromFile("fondos/FONDOTRUCAZO.png")) {
        cerr << "Error al cargar fondo de men£." << endl;
    }
    spriteFondo.setTexture(texturaFondo);

    titulo.setFont(fuente);
    titulo.setStyle(sf::Text::Bold);
    titulo.setString("TRUCAZO");
    titulo.setCharacterSize(60);
    titulo.setFillColor(sf::Color::Cyan);
    titulo.setPosition(60,50);

    string textos[]={"INICIAR PARTIDA","LISTAR JUGADORES","MAZO DE CARTAS","CREDITOS","SALIR"};
    for(int x=0;x<5;x++) {
        sf::Text texto;
        texto.setFont(fuente);
        texto.setString(textos[x]);
        texto.setCharacterSize(30);
        texto.setPosition(85,150 + x *50);
        opciones.push_back(texto);
    }
}

void Menu::ejecutar() {
    Manager cargar;
    Sonidos::get().reproducirMusicaFondo();
    while(ventana.isOpen()) {
        bool terminar = false;
        gestionarEventos(cargar, terminar);
        dibujarMenu();
    }
}