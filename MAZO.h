#ifndef MAZO_H_INCLUDED
#define MAZO_H_INCLUDED

class MAZO {
private:
    int _idCarta;
    char _nombre[30];
    int _numeroCarta;
    char _palo[10];
    int _valor;

public:
    void cargar();
    void mostrar();

    // Getters
    int getIdCarta();
    const char* getNombre();
    int getNumeroCarta();
    const char* getPalo();
    int getValor();

    // Setters
    void setIdCarta(int);
    void setNombre(const char*);
    void setNumeroCarta(int);
    void setPalo(const char*);
    void setValor(int);
};

#endif // MAZO_H_INCLUDED
