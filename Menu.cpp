#include "Menu.h"
#include "Mazo.h"
#include "Manager.h"
#include "Sonidos.h"
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <cstring>
using namespace std;

/*
   Dibuja el menu en pantalla
   Para que: el jugador vea el titulo y las opciones disponibles
   Como: limpia la ventana, dibuja el fondo, titulo y las opciones.
          Resalta la opcion seleccionada en color amarillo.
*/
void Menu::dibujarMenu()
{
    ventana.clear();
    ventana.draw(spriteFondo);
    ventana.draw(titulo);
    for (int x = 0; x < 5; x++)
    {
        if (x == opcionSeleccionada)
            opciones[x].setFillColor(sf::Color::Yellow);  // Resalta la seleccion
        else
            opciones[x].setFillColor(sf::Color::White);
        ventana.draw(opciones[x]);
    }
    ventana.display();
}

/*
    Captura eventos del teclado y ejecuta la opcion correspondiente
   Para que: el jugador pueda moverse con flechas y elegir con ENTER
   Como: al presionar arriba o abajo cambia la seleccion.
          ENTER ejecuta la funcion segun la opcion actual.
*/
void Menu::gestionarEventos(Manager& cargar)
{
    sf::Event evento;
    while (ventana.pollEvent(evento))
    {
        if (evento.type == sf::Event::Closed)
            ventana.close();

        if (evento.type == sf::Event::KeyPressed)
        {
            if (evento.key.code == sf::Keyboard::Up)
                opcionSeleccionada = (opcionSeleccionada - 1 + 5) % 5;

            if (evento.key.code == sf::Keyboard::Down)
                opcionSeleccionada = (opcionSeleccionada + 1) % 5;

            if (evento.key.code == sf::Keyboard::Enter)
            {
                cout << "Opcion seleccionada: " << opcionSeleccionada + 1 << endl;

                if (opcionSeleccionada == 0)  // INICIAR PARTIDA
                {
                    cargar.iniciarPartida(ventana);
                    cargar.actualizarJugador();  // Actualiza los datos del jugador
                }
                else if (opcionSeleccionada == 1)  // LISTAR JUGADORES
                {
                    cargar.listarJugadores(ventana);
                }
                else if (opcionSeleccionada == 2)  // MAZO DE CARTAS
                {
                    cargar.mostrarMazo(ventana);
                    cargar.mostrarMazoComodines(ventana);
                }
                else if (opcionSeleccionada == 3)  // CREDITOS
                {
                    cargar.mostrarCreditos(ventana);
                }
                else if (opcionSeleccionada == 4)  // SALIR
                {
                    ventana.close();
                }
            }
        }
    }
}

/* Constructor del Menu
   Para que: cargar todos los recursos visuales del menu principal
   Como: carga fuente, fondo, crea el texto del titulo y las 5 opciones
*/
Menu::Menu(sf::RenderWindow& v) : ventana(v), opcionSeleccionada(0)
{
    if (!fuente.loadFromFile("fuentes/Poppins-Regular.ttf"))
    {
        cerr << "Error cargando la fuente!" << endl;
    }

    if (!texturaFondo.loadFromFile("fondos/FONDOTRUCAZO.png"))
    {
        cerr << "Error al cargar fondo de menu." << endl;
    }

    spriteFondo.setTexture(texturaFondo);

    titulo.setFont(fuente);
    titulo.setStyle(sf::Text::Bold);
    titulo.setString("TRUCAZO");
    titulo.setCharacterSize(60);
    titulo.setFillColor(sf::Color::Cyan);
    titulo.setPosition(60, 50);

    // Lista de textos de las opciones del menu
    string textos[] = {
        "INICIAR PARTIDA",
        "LISTAR JUGADORES",
        "MAZO DE CARTAS",
        "CREDITOS",
        "SALIR"
    };

    for (int x = 0; x < 5; x++)
    {
        sf::Text texto;
        texto.setFont(fuente);
        texto.setString(textos[x]);
        texto.setCharacterSize(30);
        texto.setPosition(85, 150 + x * 50);  // Distribucion vertical
        opciones.push_back(texto);
    }
}

/* Ejecuta el bucle principal del menu
   Para que: mantener el menu activo hasta que se cierre la ventana
   Como: inicia la musica de fondo, y repite continuamente gestionando eventos y dibujando
*/
void Menu::ejecutar()
{
    Manager cargar;
    Sonidos::get().reproducirMusicaFondo();
    while (ventana.isOpen())
    {
        gestionarEventos(cargar);
        dibujarMenu();             // Refresca pantalla con nueva seleccion
    }
}
