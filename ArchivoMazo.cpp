#include <fstream>
#include "ArchivoMazo.h"

MAZO ArchivoMazo::leer(int pos) {
    MAZO reg;
    std::ifstream archivo(_nombre, std::ios::binary);
    if (!archivo) return reg;

    archivo.seekg(pos * sizeof(MAZO));
    archivo.read(reinterpret_cast<char*>(&reg), sizeof(MAZO));
    archivo.close();

    return reg;
}

bool ArchivoMazo::guardar(MAZO reg) {
    std::ofstream archivo(_nombre, std::ios::app | std::ios::binary);
    if (!archivo) return false;

    archivo.write(reinterpret_cast<const char*>(&reg), sizeof(MAZO));
    archivo.close();

    return true;
}

bool ArchivoMazo::guardar(MAZO reg, int pos) {
    std::fstream archivo(_nombre, std::ios::in | std::ios::out | std::ios::binary);
    if (!archivo) return false;

    archivo.seekp(pos * sizeof(MAZO));
    archivo.write(reinterpret_cast<const char*>(&reg), sizeof(MAZO));
    archivo.close();

    return true;
}

int ArchivoMazo::contarRegistros() {
    std::ifstream archivo(_nombre, std::ios::binary);
    if (!archivo) return 0;

    archivo.seekg(0, std::ios::end);
    int tam = archivo.tellg();
    archivo.close();

    return tam / sizeof(MAZO);
}
