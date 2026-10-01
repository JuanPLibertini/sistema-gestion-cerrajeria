#pragma once

#include <string>
#include "Empleado.h"

class EmpleadoArchivo {
private:
    std::string _nombreArchivo;

public:
    EmpleadoArchivo(std::string nombreArchivo = "empleados.dat");

    bool guardar(Empleado reg);
    bool modificar(Empleado reg, int pos);
    Empleado leer(int pos)const;

    int getCantidadRegistros()const;
    int buscarPorId(int id, bool incluirEliminados = false);
    int obtenerProximoId();
};


