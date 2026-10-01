#pragma once

#include "EmpleadoManager.h"

class MenuEmpleado {
private:
    EmpleadoManager _manager;

    void mostrarListadoEmpleados();
    void mostrarConsultasEmpleados();

public:
    void mostrar();
};
