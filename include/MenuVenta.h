#pragma once

#include "VentaManager.h"

class MenuVenta {
private:
    VentaManager _manager;
    void mostrarListadoVentas();
    void mostrarConsultaVentas();
    void mostrarDetallesVenta();
    void mostrarServiciosVenta();

public:
    void mostrar();
};
