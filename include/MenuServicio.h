#pragma once

#include "ServicioManager.h"

class MenuServicio {
private:
    ServicioManager _manager;
    void mostrarListadoServicios();
    void mostrarConsultaServicios();

public:
    void mostrar();
};
