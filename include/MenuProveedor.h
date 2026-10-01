#pragma once

#include "ProveedorManager.h"

class MenuProveedor {
private:
    ProveedorManager _manager;

    void mostrarListadoProveedores();
    void mostrarConsultasProveedores();

public:
    void mostrar();
};
