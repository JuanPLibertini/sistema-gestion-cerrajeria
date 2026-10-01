#pragma once

#include "EmpleadoArchivo.h"

class EmpleadoManager {
private:
    EmpleadoArchivo _repo;

public:
    EmpleadoManager();
    void altaEmpleado();
    bool listarEmpleados();
    bool bajaEmpleado(int id);
    bool reactivarEmpleado(int id);
    bool existeEmpleado(int id);
    void modificarEmpleado();

    // LISTADO DE EMPLEADOS
    void listarEmpleadoPorApellido();
    void listarEmpleadoPorCargo();
    bool listarEmpleadosEliminados();

    // CONSULTA DE EMPLEADOS
    bool buscarEmpleadoPorApellido();
    bool buscarEmpleadoPorCargo();
};


