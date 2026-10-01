#pragma once
#include "CompraManager.h"
#include "Fecha.h"

class MenuCompra {
private:
    CompraManager _manager;

    void mostrarListadoCompras();
    void mostrarConsultasCompras();
    void mostrarDetallesCompra();

public:
    void mostrar();
};
