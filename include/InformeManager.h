#pragma once

#include "CompraArchivo.h"
#include "VentaArchivo.h"
#include "VentaServicioArchivo.h"
#include "ServicioArchivo.h"
#include "Fecha.h"

class InformeManager {
private:
    CompraArchivo         _repoCompra;
    VentaArchivo          _repoVenta;
    VentaServicioArchivo  _repoVentaServicio;
    ServicioArchivo       _repoServicio;

public:
    InformeManager();

    // INFORMES DE COMPRAS
    bool informeFacturacionComprasPeriodo(Fecha desde, Fecha hasta);
    bool informeFacturacionProveedorPeriodo(int idProveedor, Fecha desde, Fecha hasta);
    float informeFacturacionComprasTotal();

    // INFORMES DE VENTAS
    bool informeFacturacionVentasPeriodo(Fecha desde, Fecha hasta);
    bool informeFacturacionClientePeriodo(int idCliente, Fecha desde, Fecha hasta);
    float informeFacturacionVentasTotal();

    // INFORME DE SERVICIO
    bool informeFacturacionServiciosPeriodo(Fecha desde, Fecha hasta);
    bool informeServiciosPorEmpleado(int idEmpleado);
};
