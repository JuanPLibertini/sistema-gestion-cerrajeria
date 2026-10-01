#pragma once
#include "InformeManager.h"

class MenuInforme {
private:
    InformeManager _manager;

    void mostrarInformesCompras();
    void mostrarInformesVentas();
    void mostrarInformesServicios();

public:
    void mostrar();
};
