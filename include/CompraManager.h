#pragma once

#include "CompraArchivo.h"
#include "CompraDetalleArchivo.h"
#include "Fecha.h"

class CompraManager {
private:
    CompraArchivo        _repo;
    CompraDetalleArchivo  _repoDetalle;

public:
    CompraManager();

    void altaCompra();
    bool bajaCompra(int id);
    bool existeCompra(int id);
    void modificarCompra();
    bool reactivarCompra(int id);

    // LISTADO DE COMPRAS
    bool listarCompras();
    bool listarCompraPorEmpleado();
    bool listarCompraPorFecha();
    bool listarCompraPorProveedor();
    bool listarCompraEliminada();

    // CONSULTA DE COMPRADETALLE
    bool listarDetalles();
    bool listarDetallesPorCompra(int idCompra);
    bool listarDetallesPorProducto(int idProducto);

    // CONSULTA DE COMPRAS
    bool listarComprasPorRangoFechas(Fecha desde, Fecha hasta);
    bool listarComprasPorMarca(const char* marca);
    bool listarComprasPorProveedor(int idProveedor);
    bool listarComprasPorEmpleado(int idEmpleado);
};
