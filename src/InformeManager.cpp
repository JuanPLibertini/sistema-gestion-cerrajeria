#include <iostream>
#include "InformeManager.h"
#include "rlutil.h"

using namespace std;

// para comparar fechas como entero (AAAAMMDD)
static int fechaToInt(const Fecha& f) {
    return f.getAnio() * 10000 + f.getMes() * 100 + f.getDia();
}

InformeManager::InformeManager() {}

// INFORMES DE COMPRAS

bool InformeManager::informeFacturacionComprasPeriodo(Fecha desde, Fecha hasta) {
    int cantidad = _repoCompra.getCantidadRegistros();
    int ini = fechaToInt(desde);
    int fin = fechaToInt(hasta);
    float totalFacturado = 0;
    bool hay = false;

    for (int i = 0; i < cantidad; i++) {
        Compra reg = _repoCompra.leer(i);
        if (reg.getEliminado()) continue;

        int f = fechaToInt(reg.getFechaCompra());
        if (f >= ini && f <= fin) {
            if (!hay) { cout << "INFORME DE FACTURACION DE COMPRAS (por periodo):\n"; hay = true; }
            reg.Mostrar();
            totalFacturado += reg.getTotalCompra();
        }
    }

    if (!hay) {
        rlutil::setColor(rlutil::RED);
        cout << "NO HAY COMPRAS EN ESE RANGO DE FECHAS.\n";
        rlutil::setColor(rlutil::WHITE);
        return false;
    }

    rlutil::setColor(rlutil::GREEN);
    cout << "\nTOTAL FACTURADO EN COMPRAS: $" << totalFacturado << "\n";
    rlutil::setColor(rlutil::WHITE);
    return true;
}

bool InformeManager::informeFacturacionProveedorPeriodo(int idProveedor, Fecha desde, Fecha hasta) {
    int cantidad = _repoCompra.getCantidadRegistros();
    int ini = fechaToInt(desde);
    int fin = fechaToInt(hasta);
    float totalFacturado = 0;
    bool hay = false;

    for (int i = 0; i < cantidad; i++) {
        Compra reg = _repoCompra.leer(i);
        if (reg.getEliminado() || reg.getIdProveedor() != idProveedor) continue;

        int f = fechaToInt(reg.getFechaCompra());
        if (f >= ini && f <= fin) {
            if (!hay) {
                cout << "INFORME DE FACTURACION DEL PROVEEDOR ID " << idProveedor << " (por periodo):\n";
                hay = true;
            }
            reg.Mostrar();
            totalFacturado += reg.getTotalCompra();
        }
    }

    if (!hay) {
        rlutil::setColor(rlutil::RED);
        cout << "NO HAY COMPRAS PARA ESE PROVEEDOR EN ESE RANGO DE FECHAS.\n";
        rlutil::setColor(rlutil::WHITE);
        return false;
    }

    rlutil::setColor(rlutil::GREEN);
    cout << "\nTOTAL FACTURADO AL PROVEEDOR: $" << totalFacturado << "\n";
    rlutil::setColor(rlutil::WHITE);
    return true;
}

float InformeManager::informeFacturacionComprasTotal() {
    int cantidad = _repoCompra.getCantidadRegistros();
    float total = 0;

    for (int i = 0; i < cantidad; i++) {
        Compra reg = _repoCompra.leer(i);
        if (!reg.getEliminado()) total += reg.getTotalCompra();
    }

    rlutil::setColor(rlutil::GREEN);
    cout << "FACTURACION TOTAL DE COMPRAS: $" << total << "\n";
    rlutil::setColor(rlutil::WHITE);
    return total;
}

// INFORMES DE VENTAS

bool InformeManager::informeFacturacionVentasPeriodo(Fecha desde, Fecha hasta) {
    int cantidad = _repoVenta.getCantidadRegistros();
    int ini = fechaToInt(desde);
    int fin = fechaToInt(hasta);
    float totalFacturado = 0;
    bool hay = false;

    for (int i = 0; i < cantidad; i++) {
        Venta reg = _repoVenta.leer(i);
        if (reg.getEliminado()) continue;

        int f = fechaToInt(reg.getFecha());
        if (f >= ini && f <= fin) {
            if (!hay) { cout << "INFORME DE FACTURACION DE VENTAS (por periodo):\n"; hay = true; }
            reg.Mostrar();
            totalFacturado += reg.getTotal();
        }
    }

    if (!hay) {
        rlutil::setColor(rlutil::RED);
        cout << "NO HAY VENTAS EN ESE RANGO DE FECHAS.\n";
        rlutil::setColor(rlutil::WHITE);
        return false;
    }

    rlutil::setColor(rlutil::GREEN);
    cout << "\nTOTAL FACTURADO EN VENTAS: $" << totalFacturado << "\n";
    rlutil::setColor(rlutil::WHITE);
    return true;
}

bool InformeManager::informeFacturacionClientePeriodo(int idCliente, Fecha desde, Fecha hasta) {
    int cantidad = _repoVenta.getCantidadRegistros();
    int ini = fechaToInt(desde);
    int fin = fechaToInt(hasta);
    float totalFacturado = 0;
    bool hay = false;

    for (int i = 0; i < cantidad; i++) {
        Venta reg = _repoVenta.leer(i);
        if (reg.getEliminado() || reg.getIdCliente() != idCliente) continue;

        int f = fechaToInt(reg.getFecha());
        if (f >= ini && f <= fin) {
            if (!hay) {
                cout << "INFORME DE FACTURACION DEL CLIENTE ID " << idCliente << " (por periodo):\n";
                hay = true;
            }
            reg.Mostrar();
            totalFacturado += reg.getTotal();
        }
    }

    if (!hay) {
        rlutil::setColor(rlutil::RED);
        cout << "NO HAY VENTAS PARA ESE CLIENTE EN ESE RANGO DE FECHAS.\n";
        rlutil::setColor(rlutil::WHITE);
        return false;
    }

    rlutil::setColor(rlutil::GREEN);
    cout << "\nTOTAL FACTURADO AL CLIENTE: $" << totalFacturado << "\n";
    rlutil::setColor(rlutil::WHITE);
    return true;
}

float InformeManager::informeFacturacionVentasTotal() {
    int cantidad = _repoVenta.getCantidadRegistros();
    float total = 0;

    for (int i = 0; i < cantidad; i++) {
        Venta reg = _repoVenta.leer(i);
        if (!reg.getEliminado()) total += reg.getTotal();
    }

    rlutil::setColor(rlutil::GREEN);
    cout << "FACTURACION TOTAL DE VENTAS: $" << total << "\n";
    rlutil::setColor(rlutil::WHITE);
    return total;
}

// INFORMES DE SERVICIOS

bool InformeManager::informeFacturacionServiciosPeriodo(Fecha desde, Fecha hasta) {
    int cantidad = _repoServicio.getCantidadRegistros();
    int ini = fechaToInt(desde);
    int fin = fechaToInt(hasta);
    float totalFacturado = 0;
    bool hay = false;

    for (int i = 0; i < cantidad; i++) {
        Servicio reg = _repoServicio.leer(i);
        if (reg.getEliminado()) continue;

        int f = fechaToInt(reg.getFecha());
        if (f >= ini && f <= fin) {
            if (!hay) { cout << "INFORME DE FACTURACION DE SERVICIOS (por periodo):\n"; hay = true; }
            reg.Mostrar();
            totalFacturado += reg.getPrecio();
        }
    }

    if (!hay) {
        rlutil::setColor(rlutil::RED);
        cout << "NO HAY SERVICIOS EN ESE RANGO DE FECHAS.\n";
        rlutil::setColor(rlutil::WHITE);
        return false;
    }

    rlutil::setColor(rlutil::GREEN);
    cout << "\nTOTAL FACTURADO EN SERVICIOS: $" << totalFacturado << "\n";
    rlutil::setColor(rlutil::WHITE);
    return true;
}

bool InformeManager::informeServiciosPorEmpleado(int idEmpleado) {
    int cantVenta = _repoVenta.getCantidadRegistros();
    int cantVS = _repoVentaServicio.getCantidadRegistros();
    float totalFacturado = 0;
    bool hay = false;

    for (int i = 0; i < cantVenta; i++) {
        Venta v = _repoVenta.leer(i);
        if (v.getEliminado() || v.getIdEmpleado() != idEmpleado) continue;

        for (int j = 0; j < cantVS; j++) {
            VentaServicio vs = _repoVentaServicio.leer(j);
            if (vs.getEliminado() || vs.getIdVenta() != v.getIdVenta()) continue;

            if (!hay) {
                cout << "INFORME DE SERVICIOS REALIZADOS POR EL EMPLEADO ID " << idEmpleado << ":\n";
                hay = true;
            }
            vs.Mostrar();
            totalFacturado += vs.getTotal();
        }
    }

    if (!hay) {
        rlutil::setColor(rlutil::RED);
        cout << "ESE EMPLEADO NO TIENE SERVICIOS REALIZADOS.\n";
        rlutil::setColor(rlutil::WHITE);
        return false;
    }

    rlutil::setColor(rlutil::GREEN);
    cout << "\nTOTAL FACTURADO EN SERVICIOS POR EL EMPLEADO: $" << totalFacturado << "\n";
    rlutil::setColor(rlutil::WHITE);
    return true;
}
