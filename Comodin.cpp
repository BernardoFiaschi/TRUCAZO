#include "Comodin.h"
using namespace std;

Comodin::Comodin() : _id(0), _nombre(""), _descripcion("") {}

Comodin::Comodin(int id, std::string nombre, std::string descripcion) {
    setId(id);
    setNombre(nombre);
    setDescripcion(descripcion);
}

int Comodin::getId() const {
    return _id;
}

string Comodin::getNombre() const {
    return _nombre;
}

string Comodin::getDescripcion() const {
    return _descripcion;
}

void Comodin::setId(int id) {
    _id = id;
}

void Comodin::setNombre(string nombre) {
    _nombre = nombre;
}

void Comodin::setDescripcion(string descripcion) {
    _descripcion = descripcion;
}
