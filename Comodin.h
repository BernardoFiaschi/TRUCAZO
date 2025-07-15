#pragma once
#include <string>

class Comodin
{
private:
    int _id;
    std::string _nombre;
    std::string _descripcion;

public:
    Comodin();
    Comodin(int id, std::string nombre, std::string descripcion);
    int getId() const;
    std::string getNombre() const;
    std::string getDescripcion() const;
    void setId(int id);
    void setNombre(std::string nombre);
    void setDescripcion(std::string descripcion);
};
