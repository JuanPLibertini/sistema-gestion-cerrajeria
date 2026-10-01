#pragma once

#include "VentaArchivo.h"
#include "VentaDetalleArchivo.h"
#include "VentaServicioArchivo.h"
#include "Fecha.h"

class VentaManager {
private:
    VentaArchivo         _repo;
    VentaDetalleArchivo  _repoDetalle;
    VentaServicioArchivo _repoServicio;

public:
    VentaManager();

    void altaVenta();
    bool listarVenta();
    bool bajaVenta(int id);
    bool existeVenta(int id);
    bool reactivarVenta(int id);
    void modificarVenta();

    bool listarDetalles();
    bool listarServicios();
    bool listarVentaEliminada();

    // LISTADO DE VENTAS
    void listarOrdenadoPorFecha();
    void listarOrdenadoPorCliente();

    // CONSULTA DE VENTAS
    bool listarVentasPorRangoFechas(Fecha desde, Fecha hasta);
    bool listarVentasPorMarca(const char* marca);
    bool listarVentasPorCliente(int idCliente);
    bool listarVentasPorEmpleado(int idEmpleado);

    // CONSULTA DE VENTADETALLE
    bool listarDetallesPorVenta(int idVenta);
    bool listarDetallesPorProducto(int idProducto);

    // CONSULTA DE VENTASERVICIO
    bool listarServiciosVentaPorCliente(int idCliente);
    bool listarServiciosVentaPorServicio(int idServicio);
    bool listarServiciosVentaPorRangoFechas(Fecha desde, Fecha hasta);
};
