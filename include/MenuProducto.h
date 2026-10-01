#pragma once

#include "ProductoManager.h"

class MenuProducto {
private:
    ProductoManager _manager;

    void mostrarListadoProductos();
    void mostrarConsultasProductos();

public:
    void mostrar();
};
