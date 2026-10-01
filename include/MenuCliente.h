#pragma once

#include "ClienteManager.h"

class MenuCliente {
private:
    ClienteManager _manager;

    void mostrarListadoClientes();
    void mostrarConsultasClientes();

public:
    void mostrar();
};
