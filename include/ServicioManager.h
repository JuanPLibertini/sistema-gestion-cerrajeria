#pragma once

#include "ServicioArchivo.h"

class ServicioManager {
private:
    ServicioArchivo _repo;

public:
    ServicioManager();

    void altaServicio();
    bool listarServicios();
    bool bajaServicio(int id);
    bool existeServicio(int id);
    bool reactivarServicio(int id);
    void modificarServicio();
    bool listarServiciosEliminados();
    bool existeServicioIncluyendoEliminados(int id);

    // LISTADO DE SERVICIOS
    void listarOrdenadoPorDescripcion();
    void listarOrdenadoPorTipo();
    void listarOrdenadoPorPrecio();

    // CONSULTA DE SERVICIOS
    bool buscarServicioPorTipo();
    bool buscarServicioPorRangoPrecio();

};
