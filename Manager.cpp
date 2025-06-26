#include "Manager.h"
#include "ArchivoJugador.h"
#include "Menu.h"
#include "Mazo.h"
#include "Partida.h"
#include "Jugador.h"
#include "Sonidos.h"
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
using namespace std;

/*
   Constructor del manager
   Para que: inicializar el jugador actual como vacio por defecto.
   Como: se crea un jugador con ID 1, nombre vacio y 0 en partidas y puntos.
*/
Manager::Manager() : jugador(1, "", 0, 0) {}

/*
   Dibuja todas las cartas del mazo original en pantalla
   Para que: el jugador pueda ver el mazo completo
   Como: recorre el vector de cartas originales y las dibuja una por una
*/
void Manager::dibujarMazoCartas(sf::RenderWindow& ventana) {
    ventana.clear();

    sf::Texture fondoTexture;
    if (!fondoTexture.loadFromFile("fondos/MOSTRARCARTAS.png")) {
        cerr << "No se pudo cargar el fondo MOSTRARCARTAS.png" << endl;
        return;
    }

    sf::Sprite fondoSprite(fondoTexture);
    ventana.draw(fondoSprite);

    int x = 50, y = 50, cartasEnFila = 0;

    for (const Carta& carta : mazo.getMazoOriginal()) {
        int id = carta.getIdCarta();
        sf::Texture texturaCarta;
        if (!texturaCarta.loadFromFile("cartas/" + to_string(id) + ".png")) {
            cerr << "Error cargando carta ID: " << id << endl;
            continue;
        }

        sf::Sprite sprite(texturaCarta);
        sprite.setPosition(x, y);
        sprite.setScale(1.2f, 1.2f);
        ventana.draw(sprite);

        x += 75;
        if (++cartasEnFila == 10) {
            x = 50;
            y += 130;
            cartasEnFila = 0;
        }
    }

    ventana.display();
}

void Manager::dibujarComodines(sf::RenderWindow& ventana)
{
    ventana.clear();

    sf::Texture fondoPantalla;
    if (!fondoPantalla.loadFromFile("fondos/MOSTRARCARTAS.png"))
    {
        cerr << "No se pudo cargar el fondo Mostrar cartas" << endl;
        return;
    }

    sf::Sprite spriteFondo(fondoPantalla);
    ventana.draw(spriteFondo);

    // Dimensiones
    float escala = 1.5f; // reducida para que entren m s
    float anchoCarta = 90 * escala;
    float altoCarta = 140 * escala;
    float espacioX = 20;
    float espacioY = 30;

    int cartasPorFila = (ventana.getSize().x - 100) / (anchoCarta + espacioX);
    float x = 50;
    float y = 50;
    int cartasEnFila = 0;

    for (const Comodin& comodin : mazo.getMazoComodines())
    {
        int id = comodin.getId();
        sf::Texture texturaComodin;
        if (!texturaComodin.loadFromFile("comodines/" + to_string(id) + ".png"))
        {
            cerr << "Error cargando carta ID: " << id << endl;
            continue;
        }

        sf::Sprite sprite(texturaComodin);
        sprite.setScale(escala, escala);
        sprite.setPosition(x, y);
        ventana.draw(sprite);

        x += anchoCarta + espacioX;
        cartasEnFila++;

        if (cartasEnFila >= cartasPorFila)
        {
            x = 50;
            y += altoCarta + espacioY;
            cartasEnFila = 0;
        }
    }

    ventana.display();
}


void Manager::mostrarMazoComodines(sf::RenderWindow& ventana)
{
    dibujarComodines(ventana);
    esperarTecla(ventana);
}

/*
   Espera a que el jugador presione cualquier tecla
   Para que: pausar la pantalla hasta que el jugador quiera seguir
*/
void Manager::esperarTecla(sf::RenderWindow& ventana) {
    bool esperando = true;
    while (esperando && ventana.isOpen()) {
        sf::Event ev;
        while (ventana.pollEvent(ev)) {
            if (ev.type == sf::Event::Closed) ventana.close();
            if (ev.type == sf::Event::KeyPressed) esperando = false;
        }
    }
}

/*
   Muestra el menu principal
   Para que: iniciar la interfaz principal del juego
   Como: se crea el objeto Menu y se ejecuta su metodo
*/
void Manager::mostrarMenu(sf::RenderWindow& ventana) {
    Menu menu(ventana);
    menu.ejecutar();
}

/*
   Muestra visualmente el mazo completo y espera una tecla
   Para que: mostrar al jugador las 40 cartas que hay
*/
void Manager::mostrarMazo(sf::RenderWindow& ventana) {
    dibujarMazoCartas(ventana);
    esperarTecla(ventana);
}

/*
   Pide el nombre del jugador por pantalla (ingreso tipo consola)
   Para que: registrar o recuperar al jugador que va a jugar
   Como: usa una ventana con texto en vivo y espera ENTER
*/
string Manager::pedirNombre(sf::RenderWindow& ventana) {
    sf::Font fuente;
    fuente.loadFromFile("fuentes/Poppins-Regular.ttf");

    sf::Texture fondoTexture;
    if (!fondoTexture.loadFromFile("fondos/MOSTRARCARTAS.png")) return "";

    sf::Sprite fondo(fondoTexture);
    sf::Text titulo("Ingresa tu nombre y presiona ENTER: ", fuente, 30);
    titulo.setFillColor(sf::Color::White);
    titulo.setPosition(50, 180);

    sf::Text texto("", fuente, 30);
    texto.setFillColor(sf::Color::White);
    texto.setPosition(150, 280);

    string nombre;

    while (ventana.isOpen()) {
        sf::Event evento;
        while (ventana.pollEvent(evento)) {
            if (evento.type == sf::Event::Closed) ventana.close();

            if (evento.type == sf::Event::TextEntered) {
                char tecla = static_cast<char>(evento.text.unicode);
                if (tecla == '\b' && !nombre.empty()) nombre.pop_back();
                else if ((tecla == '\r' || tecla == '\n') && !nombre.empty()) {
                    Sonidos::get().reproducirDescartar();
                    return nombre;
                }
                else if (nombre.size() < 19 && isprint(tecla)) nombre += tecla;

            }
        }
        if (!nombre.empty())
        nombre[0] = toupper(nombre[0]);



        texto.setString(nombre);
        ventana.clear();
        ventana.draw(fondo);
        ventana.draw(titulo);
        ventana.draw(texto);
        ventana.display();
    }

    return "";
}

/*
   Inicia una nueva partida para el jugador
   Para que: cargar un jugador existente o crear uno nuevo
   Como: se pide el nombre, se busca en archivo y luego se inicia la partida
*/
void Manager::iniciarPartida(sf::RenderWindow& ventana) {
    ArchivoJugador archivo;
    string nombre = pedirNombre(ventana);
    Jugador existente = archivo.buscarJugador(nombre);

    if (existente.getNombre() != "") jugador = existente;
    else {
        int nuevoId = archivo.getCantidadJugadores() + 1;
        jugador = Jugador(nuevoId, nombre, 0, 0);
        archivo.guardarJugador(jugador);
    }

    Partida partida(jugador);
    partida.iniciar(ventana);

    jugador.sumarPuntos(partida.getPuntajeTotal());
    jugador.aumentarPartidas();
    jugador.actualizarPuntajeMaximo(partida.getPuntajeTotal());

    int pos = archivo.buscarJugadorPorId(jugador.getId());
    if (pos >= 0) archivo.guardarJugador(jugador, pos);
}

/*
   Muestra una pantalla de fin de ronda (ganada o perdida)
   Para que: dar feedback visual y sonoro al jugador
   Como: muestra fondo, texto, puntaje, y espera ENTER
*/
void Manager::finalizarRonda(sf::RenderWindow& ventana, bool victoria, Partida& partida)
{

    if (victoria && partida.getRondaActual() == 14)  // rondaActual arranca en 0
    {
        sf::Texture fondoTexture;
        if (!fondoTexture.loadFromFile("fondos/CREDITOS.png")) {
            cerr << "No se pudo cargar la imagen de fondo CREDITOS." << endl;
            return;
        }
        sf::Sprite fondoSprite(fondoTexture);

        sf::Font fuente;
        fuente.loadFromFile("fuentes/Poppins-Regular.ttf");

        sf::Text titulo("FELICITACIONES POR GANAR!", fuente, 34);
        titulo.setStyle(sf::Text::Bold);
        titulo.setFillColor(sf::Color::White);
        titulo.setPosition(100, 100);

        sf::Text instruccion("Presione ENTER para volver al menu principal", fuente, 24);
        instruccion.setFillColor(sf::Color::White);
        instruccion.setPosition(120, 180);

        Sonidos::get().detenerMusicaFondo();
        Sonidos::get().reproducirVictoria();

        ventana.clear();
        ventana.draw(fondoSprite);
        ventana.draw(titulo);
        ventana.draw(instruccion);
        ventana.display();

        bool esperando = true;
        while (esperando && ventana.isOpen())
        {
            sf::Event evento;
            while (ventana.pollEvent(evento))
            {
                if (evento.type == sf::Event::Closed) ventana.close();
                if (evento.type == sf::Event::KeyPressed && evento.key.code == sf::Keyboard::Enter)
                    esperando = false;
            }
        }

        Sonidos::get().detenerVictoria();
        Sonidos::get().reproducirMusicaFondo();
        return;
    }

    sf::Texture fondo;
    if (victoria) {
        fondo.loadFromFile("fondos/RONDAGANADA.png");
        Sonidos::get().detenerMusicaFondo();
        Sonidos::get().reproducirVictoria();
    } else {
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
    texto.setFillColor(sf::Color::White);
    texto.setStyle(sf::Text::Bold);
    texto.setPosition(ventana.getSize().x / 2.f - 360, 480);

    int puntajeRonda = partida.getPuntajeRonda();
    sf::Text textoPuntaje;
    textoPuntaje.setFont(fuente);
    textoPuntaje.setString("Puntaje obtenido: " + to_string(puntajeRonda));
    textoPuntaje.setCharacterSize(25);
    textoPuntaje.setFillColor(sf::Color::White);
    textoPuntaje.setPosition(ventana.getSize().x / 2.f - 340, 520);

    sf::Text instruccion;
    instruccion.setFont(fuente);
    instruccion.setString("Presione ENTER para continuar");
    instruccion.setCharacterSize(20);
    instruccion.setFillColor(sf::Color(255, 255, 255, 160));
    instruccion.setPosition(ventana.getSize().x / 2.f - 340, 560);

    ventana.clear();
    ventana.draw(spriteFondo);
    ventana.draw(texto);
    ventana.draw(textoPuntaje);
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

    // Restaurar musica
    if (ventana.isOpen()) {
        Sonidos::get().detenerVictoria();
        Sonidos::get().detenerDerrota();
        Sonidos::get().reproducirMusicaFondo();
    }
}

/*
   Muestra una pantalla con los creditos del juego
   Para que: reconocer a los desarrolladores
   Como: se dibuja una imagen de fondo y texto en pantalla
*/
void Manager::mostrarCreditos(sf::RenderWindow& ventana) {
    sf::Texture fondoTexture;
    if (!fondoTexture.loadFromFile("fondos/CREDITOS.png")) return;
    sf::Sprite fondoSprite(fondoTexture);

    sf::Font fuente;
    fuente.loadFromFile("fuentes/Poppins-Regular.ttf");

    string textoCreditos =
        "*     TRUCAZO    *\n"
        "Desarrollado por:\n"
        "Bernardo Fiaschi\n"
        "Raul Luppini\n"
        "C++ con SFML - 2025\n"
        "Gracias por jugar!\n";

    sf::Text creditos(textoCreditos, fuente, 32);
    creditos.setFillColor(sf::Color::Black);
    creditos.setStyle(sf::Text::Bold);

    sf::FloatRect bounds = creditos.getLocalBounds();
    creditos.setOrigin(bounds.width / 2, bounds.height / 2);
    creditos.setPosition(ventana.getSize().x / 3.5f, ventana.getSize().y / 2.f);

    ventana.clear();
    ventana.draw(fondoSprite);
    ventana.draw(creditos);
    ventana.display();

    esperarTecla(ventana);
}

/*
   Devuelve una referencia al jugador actual
   Para que: otras clases puedan acceder a sus datos sin duplicarlos
*/

Jugador& Manager::getJugador() {
    return jugador;
}

/*
   Muestra la lista de jugadores registrados y sus datos
   Para que: visualizar todos los jugadores guardados en archivo
   Como: se lee el archivo binario y se dibuja cada jugador en pantalla
*/
void Manager::listarJugadores(sf::RenderWindow& ventana) {
    ArchivoJugador archivo;
    int cantidad = archivo.getCantidadJugadores();

    sf::Font fuente;
    fuente.loadFromFile("fuentes/Poppins-Regular.ttf");

    sf::Texture fondoTexture;
    fondoTexture.loadFromFile("fondos/MOSTRARCARTAS.png");
    sf::Sprite fondo(fondoTexture);

    vector<sf::Text> textos;

    sf::Text titulo("=== LISTADO DE JUGADORES ===", fuente, 30);
    titulo.setFillColor(sf::Color::White);
    titulo.setPosition(60, 40);
    textos.push_back(titulo);

    for (int i = 0; i < cantidad; i++) {
        Jugador j = archivo.leer(i);
        stringstream ss;
        ss << "ID: " << j.getId()
           << " | Nombre: " << j.getNombre()
           << " | Puntaje Maximo: " << j.getPuntajeMaximo()
           << " | Partidas Jugadas: " << j.getPartidasJugadas();

        sf::Text linea(ss.str(), fuente, 22);
        linea.setFillColor(sf::Color::White);
        linea.setPosition(60, 90 + i * 30);
        textos.push_back(linea);
    }

    sf::Text instruccion("Presione una tecla para volver", fuente, 20);
    instruccion.setFillColor(sf::Color(255, 255, 255, 160));
    instruccion.setPosition(60, 100 + cantidad * 30 + 20);
    textos.push_back(instruccion);

    ventana.clear();
    ventana.draw(fondo);
    for (auto& t : textos) ventana.draw(t);
    ventana.display();

    esperarTecla(ventana);
}

/*
   Guarda los datos actualizados del jugador en archivo
   Para que: se conserven los cambios de partidas y puntajes
*/
void Manager::actualizarJugador() {
    ArchivoJugador archivo;
    int pos = archivo.buscarJugadorPorId(jugador.getId());
    if (pos >= 0) archivo.guardarJugador(jugador, pos);
}
