#ifndef ARCHIVOMAZO_H_INCLUDED
#define ARCHIVOMAZO_H_INCLUDED
#include "MAZO.h"

class ArchivoMazo {
private:
    char _nombre[30];

public:
    ArchivoMazo(const char* nombre = "mazo.dat") {
        strcpy(_nombre, nombre);
    }

    MAZO leer(int pos);
    bool guardar(MAZO reg);
    int contarRegistros();
    bool guardar(MAZO reg, int pos);
};

#endif // ARCHIVOMAZO_H_INCLUDED
