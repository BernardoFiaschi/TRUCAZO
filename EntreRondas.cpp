#include "EntreRondas.h"
#include "Sonidos.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

vector<Carta> EntreRondas::seleccionarCartasEntreRondas(sf::RenderWindow& ventana, const vector<Carta>& mazoOriginal)
{
    vector<Carta> seleccionadas;
    vector<int> indicesUsados;

    while (indicesUsados.size() < 4) {
        int idx = rand() % mazoOriginal.size();
        indicesUsados.push_back(idx);
    }

    sf::Texture texturas[4];
    sf::Sprite sprites[4];
    bool elegidas[4] = { false, false, false, false };

    for (int i = 0; i < 4; i++) {
        int id = mazoOriginal[indicesUsados[i]].getIdCarta();
        texturas[i].loadFromFile("cartas/" + to_string(id) + ".png");
        sprites[i].setTexture(texturas[i]);
        sprites[i].setScale(1.5f, 1.5f);
        sprites[i].setPosition(150 + i * 150, 250);
    }

    sf::Font fuente;
    fuente.loadFromFile("fuentes/Poppins-Regular.ttf");

    sf::Text titulo("Elige hasta 2 cartas para agregar a tu mazo", fuente, 26);
    titulo.setFillColor(sf::Color::White);
    titulo.setPosition(120, 100);

    while (ventana.isOpen())
    {
        sf::Event evento;
        while (ventana.pollEvent(evento))
        {
            if (evento.type == sf::Event::Closed) ventana.close();

            if (evento.type == sf::Event::KeyPressed)
            {
                if (evento.key.code >= sf::Keyboard::Num1 && evento.key.code <= sf::Keyboard::Num4)
                {
                    int idx = evento.key.code - sf::Keyboard::Num1;
                    if (!elegidas[idx] && seleccionadas.size() < 2) {
                        elegidas[idx] = true;
                        seleccionadas.push_back(mazoOriginal[indicesUsados[idx]]);
                        Sonidos::get().reproducirSeleccionar();
                    }
                    else if (elegidas[idx]) {
                        elegidas[idx] = false;
                        // eliminacion manual sin operator==
                        for (int i = 0; i < seleccionadas.size(); i++) {
                            if (seleccionadas[i].getIdCarta() == mazoOriginal[indicesUsados[idx]].getIdCarta()) {
                                seleccionadas.erase(seleccionadas.begin() + i);
                                break;
                            }
                        }
                        Sonidos::get().reproducirSeleccionar();
                    }
                }

                if (evento.key.code == sf::Keyboard::Enter && !seleccionadas.empty()) {
                    return seleccionadas;
                }
            }
        }

        ventana.clear();
        sf::Texture fondo;
        fondo.loadFromFile("fondos/MOSTRARCARTAS.png");
        sf::Sprite fondoSprite(fondo);
        ventana.draw(fondoSprite);

        ventana.draw(titulo);
        for (int i = 0; i < 4; i++) {
            ventana.draw(sprites[i]);
            if (elegidas[i]) {
                sf::RectangleShape marco(sf::Vector2f(sprites[i].getGlobalBounds().width, sprites[i].getGlobalBounds().height));
                marco.setPosition(sprites[i].getPosition());
                marco.setFillColor(sf::Color::Transparent);
                marco.setOutlineThickness(4);
                marco.setOutlineColor(sf::Color::Green);
                ventana.draw(marco);
            }
        }

        ventana.display();
    }

    return seleccionadas;
}

/* Permite elegir 1 comodin entre 2 aleatorios.
   Para que: el jugador obtenga efectos especiales durante la partida.
   Como: muestra los nombres y deja elegir con tecla 1 o 2.
*/
Comodin EntreRondas::seleccionarComodin(sf::RenderWindow& ventana, const vector<Comodin>& mazoComodines)
{
    // Elige 2 comodines al azar
    srand(time(nullptr));
    vector<Comodin> seleccionados;
    vector<int> usados;

    while (seleccionados.size() < 2) {
        int idx = rand() % mazoComodines.size();
        if (find(usados.begin(), usados.end(), idx) == usados.end()) {
            seleccionados.push_back(mazoComodines[idx]);
            usados.push_back(idx);
        }
    }

    // Carga de recursos
    sf::Font fuente;
    fuente.loadFromFile("fuentes/Poppins-Regular.ttf");

    sf::Texture fondo;
    fondo.loadFromFile("fondos/MOSTRARCARTAS.png");
    sf::Sprite fondoSprite(fondo);

    sf::Texture texturas[2];
    sf::Sprite sprites[2];
    for (int i = 0; i < 2; i++) {
        texturas[i].loadFromFile("comodines/" + to_string(seleccionados[i].getId()) + ".png");
        sprites[i].setTexture(texturas[i]);
        sprites[i].setScale(2.0f, 2.0f);
        sprites[i].setPosition(150 + i * 300, 200);
    }

    // Textos de descripci¢n
    sf::Text nombre, descripcion;
    nombre.setFont(fuente);
    nombre.setCharacterSize(24);
    nombre.setFillColor(sf::Color::White);
    nombre.setPosition(40, 470);

    descripcion.setFont(fuente);
    descripcion.setCharacterSize(18);
    descripcion.setFillColor(sf::Color(230, 230, 230));
    descripcion.setPosition(40, 510);

    // Titulo
    sf::Text titulo("Elige un Comodin (1 o 2)", fuente, 30);
    titulo.setFillColor(sf::Color::White);
    titulo.setPosition(200, 100);

    // Recuadros de selecci¢n
    sf::RectangleShape recuadro(sf::Vector2f(100, 140));
    recuadro.setFillColor(sf::Color::Transparent);
    recuadro.setOutlineColor(sf::Color::White);
    recuadro.setOutlineThickness(4);

    int seleccionado = -1;

    while (ventana.isOpen()) {
        sf::Event evento;
        while (ventana.pollEvent(evento)) {
            if (evento.type == sf::Event::Closed)
                ventana.close();

            if (evento.type == sf::Event::KeyPressed) {
                if (evento.key.code == sf::Keyboard::Num1)
                    seleccionado = 0;
                if (evento.key.code == sf::Keyboard::Num2)
                    seleccionado = 1;
                if (evento.key.code == sf::Keyboard::Enter && seleccionado != -1)
                    return seleccionados[seleccionado];
            }
        }

        ventana.clear();
        ventana.draw(fondoSprite);
        ventana.draw(titulo);

        for (int i = 0; i < 2; i++) {
            ventana.draw(sprites[i]);
        }

        if (seleccionado != -1) {
            nombre.setString(seleccionados[seleccionado].getNombre());
            descripcion.setString(seleccionados[seleccionado].getDescripcion());

            recuadro.setPosition(sprites[seleccionado].getPosition().x - 10,
                                 sprites[seleccionado].getPosition().y - 10);
            recuadro.setSize(sf::Vector2f(sprites[seleccionado].getGlobalBounds().width + 20,
                                          sprites[seleccionado].getGlobalBounds().height + 20));
            ventana.draw(recuadro);
            ventana.draw(nombre);
            ventana.draw(descripcion);
        }

        ventana.display();
    }

    return seleccionados[0]; // fallback
}

