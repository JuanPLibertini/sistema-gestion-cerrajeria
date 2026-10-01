#pragma once

#include "Fecha.h"

class Empleado {
private:
    int   idEmpleado;
    char  nombre[30];
    char  apellido[30];
    char  cargo[30];
    float sueldo;
    Fecha fechaIngreso;
    bool  eliminado;

    void copiarCadena(char* destino, const char* origen, int tamanio);

public:
    Empleado();
    bool Cargar();
    void Mostrar(bool mostrarEliminados = false) const;
    void MostrarPorCargo() const;
    void MostrarPorApellido()const;

    void setIdEmpleado(int id);
    void setNombre(const char* n);
    void setApellido(const char* a);
    void setCargo(const char* c);
    void setSueldo(float s);
    void setFechaIngreso(const Fecha& f);
    void setEliminado(bool e);

    int getIdEmpleado() const;
    const char* getNombre() const;
    const char* getApellido() const;
    const char* getCargo() const;
    float getSueldo() const;
    Fecha getFechaIngreso() const;
    bool getEliminado() const;
};


