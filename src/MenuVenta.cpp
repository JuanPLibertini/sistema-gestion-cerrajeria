#include <iostream>
#include "MenuVenta.h"
#include "rlutil.h"
#include "Utilidades.h"

using namespace std;

void pausa();
void limpiarEntrada();

void MenuVenta::mostrar() {
    int opcion;

    do {
        rlutil::cls();
        cout << "\n--- MENU VENTAS ---\n";
        cout << "1) Alta venta\n";
        cout << "2) Listar ventas\n";
        cout << "3) Baja de venta\n";
        cout << "4) Modificacion de venta\n";
        cout << "5) Reactivar venta\n";
        cout << "6) Consultas de ventas\n";
        cout << "7) Detalles de venta (productos)\n";
        cout << "8) Servicios vendidos\n";
        cout << "0) Volver\n";
        cout << "===========================\n";
        cout << "Opcion: ";

        opcion = leerOpcion();
        switch (opcion) {
            case 1:
                rlutil::cls();
                _manager.altaVenta();
                pausa();
                break;

            case 2:
                rlutil::cls();
                mostrarListadoVentas();
                break;

            case 3: {
                rlutil::cls();
                if (!_manager.listarVenta()) {
                    pausa();
                    break;
                }

                int id;
                char confirmacion;

                cout << "\nIngrese ID de la venta a dar de baja: ";
                cin >> id;
                limpiarEntrada();

                if (!_manager.existeVenta(id)) {
                    rlutil::setColor(rlutil::RED);
                    cout << "Venta no encontrada.\n";
                    rlutil::setColor(rlutil::WHITE);
                    pausa();
                    break;
                }

                cout << "\nSeguro que desea eliminar la venta? (s/n): ";
                cin >> confirmacion;
                limpiarEntrada();

                if (confirmacion == 's' || confirmacion == 'S') {
                    if (_manager.bajaVenta(id)) {
                        rlutil::setColor(rlutil::GREEN);
                        cout << "Venta dada de baja correctamente.\n";
                        rlutil::setColor(rlutil::WHITE);
                    } else {
                        rlutil::setColor(rlutil::RED);
                        cout << "Venta no encontrada o ya eliminada.\n";
                        rlutil::setColor(rlutil::WHITE);
                    }
                } else {
                    rlutil::setColor(rlutil::RED);
                    cout << "OPERACION CANCELADA\n";
                    rlutil::setColor(rlutil::WHITE);
                }

                pausa();
                break;
            }

            case 4:
                rlutil::cls();
                _manager.modificarVenta();
                pausa();
                break;

            case 5: {
                rlutil::cls();
                if (!_manager.listarVentaEliminada()) {
                    pausa();
                    break;
                }

                int id;
                while (true) {
                    cout << "\nIngrese ID de la venta a reactivar (0 para cancelar): ";
                    cin >> id;

                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(1000, '\n');
                        rlutil::setColor(rlutil::RED);
                        cout << "Entrada invalida. Debe ingresar un numero entero positivo.\n";
                        rlutil::setColor(rlutil::WHITE);
                        continue;
                    }

                    cin.ignore(1000, '\n');

                    if (id == 0) {
                        rlutil::setColor(rlutil::RED);
                        cout << "OPERACION CANCELADA.\n";
                        rlutil::setColor(rlutil::WHITE);
                        pausa();
                        break;
                    }

                    if (id < 0) {
                        rlutil::setColor(rlutil::RED);
                        cout << "El ID no puede ser negativo.\n";
                        rlutil::setColor(rlutil::WHITE);
                        continue;
                    }

                    if (_manager.reactivarVenta(id)) {
                        rlutil::setColor(rlutil::GREEN);
                        cout << "Venta reactivada correctamente.\n";
                        rlutil::setColor(rlutil::WHITE);
                        pausa();
                        break;
                    } else {
                        rlutil::setColor(rlutil::RED);
                        cout << "ID invalido o la venta ya estaba activo.\n";
                        rlutil::setColor(rlutil::WHITE);
                        continue;
                    }
                }
                break;
            }

            case 6:
                rlutil::cls();
                mostrarConsultaVentas();
                break;

            case 7:
                rlutil::cls();
                mostrarDetallesVenta();
                break;

            case 8:
                rlutil::cls();
                mostrarServiciosVenta();
                break;

            case 0:
                break;

            default:
                rlutil::setColor(rlutil::RED);
                cout << "OPCION INVALIDA. INTENTE NUEVAMENTE.\n";
                rlutil::setColor(rlutil::WHITE);
                pausa();
                break;
        }
    } while (opcion != 0);
}

void MenuVenta::mostrarConsultaVentas() {
    int opcion;

    do {
        rlutil::cls();
        cout << "\n--- CONSULTA DE VENTAS ---\n";
        cout << "1) Por rango de fechas\n";
        cout << "2) Por marca\n";
        cout << "3) Por cliente\n";
        cout << "4) Por empleado\n";
        cout << "0) Volver\n";
        cout << "===========================\n";
        cout << "Opcion: ";

        opcion = leerOpcion();
        switch (opcion) {
            case 1: {
                Fecha desde, hasta;
                cout << "Fecha desde:\n";
                desde.Cargar();
                cout << "Fecha hasta:\n";
                hasta.Cargar();
                rlutil::cls();
                _manager.listarVentasPorRangoFechas(desde, hasta);
                pausa();
                break;
            }
            case 2: {
                char marca[50];
                cout << "Ingrese marca: ";
                cin.getline(marca, 50);
                rlutil::cls();
                _manager.listarVentasPorMarca(marca);
                pausa();
                break;
            }
            case 3: {
                int idCliente;
                cout << "Ingrese ID de cliente: ";
                cin >> idCliente;
                rlutil::cls();
                _manager.listarVentasPorCliente(idCliente);
                pausa();
                break;
            }
            case 4: {
                int idEmpleado;
                cout << "Ingrese ID de empleado: ";
                cin >> idEmpleado;
                rlutil::cls();
                _manager.listarVentasPorEmpleado(idEmpleado);
                pausa();
                break;
            }
            case 0:
                break;
            default:
                rlutil::setColor(rlutil::RED);
                cout << "OPCION INVALIDA. INTENTE NUEVAMENTE.\n";
                rlutil::setColor(rlutil::WHITE);
                pausa();
                break;
        }
    } while (opcion != 0);
}

void MenuVenta::mostrarListadoVentas() {
    int opcion;

    do {
        rlutil::cls();
        cout << "\n--- LISTADO DE VENTAS ---\n";
        cout << "1) Todas las ventas\n";
        cout << "2) Ordenado por fecha\n";
        cout << "3) Ordenado por cliente\n";
        cout << "0) Volver\n";
        cout << "===========================\n";
        cout << "Opcion: ";

        opcion = leerOpcion();
        switch (opcion) {
            case 1:
                rlutil::cls();
                _manager.listarVenta();
                pausa();
                break;
            case 2:
                rlutil::cls();
                _manager.listarOrdenadoPorFecha();
                pausa();
                break;
            case 3:
                rlutil::cls();
                _manager.listarOrdenadoPorCliente();
                pausa();
                break;
            case 0:
                break;
            default:
                rlutil::setColor(rlutil::RED);
                cout << "OPCION INVALIDA. INTENTE NUEVAMENTE.\n";
                rlutil::setColor(rlutil::WHITE);
                pausa();
                break;
        }
    } while (opcion != 0);
}

void MenuVenta::mostrarDetallesVenta() {
    int opcion;

    do {
        rlutil::cls();
        cout << "\n--- DETALLES DE VENTA (PRODUCTOS) ---\n";
        cout << "1) Listar todos los detalles\n";
        cout << "2) Por ID de venta\n";
        cout << "3) Por producto\n";
        cout << "0) Volver\n";
        cout << "===========================\n";
        cout << "Opcion: ";

        opcion = leerOpcion();
        switch (opcion) {
            case 1:
                 rlutil::cls();
                _manager.listarDetalles();
                pausa();
                break;
            case 2: {
                int idVenta;
                cout << "Ingrese ID de venta: ";
                cin >> idVenta;
                rlutil::cls();
                limpiarEntrada();
                _manager.listarDetallesPorVenta(idVenta);
                pausa();
                break;
            }
            case 3: {
                int idProducto;
                cout << "Ingrese ID de producto: ";
                cin >> idProducto;
                rlutil::cls();
                limpiarEntrada();
                _manager.listarDetallesPorProducto(idProducto);
                pausa();
                break;
            }
            case 0:
                break;
            default:
                rlutil::setColor(rlutil::RED);
                cout << "OPCION INVALIDA. INTENTE NUEVAMENTE.\n";
                rlutil::setColor(rlutil::WHITE);
                pausa();
                break;
        }
    } while (opcion != 0);
}

void MenuVenta::mostrarServiciosVenta() {
    int opcion;

    do {
        rlutil::cls();
        cout << "\n--- SERVICIOS VENDIDOS ---\n";
        cout << "1) Listar todos los servicios vendidos\n";
        cout << "2) Por cliente\n";
        cout << "3) Por servicio\n";
        cout << "4) Por rango de fechas\n";
        cout << "0) Volver\n";
        cout << "===========================\n";
        cout << "Opcion: ";

        opcion = leerOpcion();
        switch (opcion) {
            case 1:
                rlutil::cls();
                _manager.listarServicios();
                pausa();
                break;
            case 2: {
                int idCliente;
                cout << "Ingrese ID de cliente: ";
                cin >> idCliente;
                limpiarEntrada();
                _manager.listarServiciosVentaPorCliente(idCliente);
                pausa();
                break;
            }
            case 3: {
                int idServicio;
                cout << "Ingrese ID de servicio: ";
                cin >> idServicio;
                limpiarEntrada();
                _manager.listarServiciosVentaPorServicio(idServicio);
                pausa();
                break;
            }
            case 4: {
                Fecha desde, hasta;
                cout << "Fecha desde:\n";
                desde.Cargar();
                cout << "Fecha hasta:\n";
                hasta.Cargar();
                _manager.listarServiciosVentaPorRangoFechas(desde, hasta);
                pausa();
                break;
            }
            case 0:
                break;
            default:
                rlutil::setColor(rlutil::RED);
                cout << "OPCION INVALIDA. INTENTE NUEVAMENTE.\n";
                rlutil::setColor(rlutil::WHITE);
                pausa();
                break;
        }
    } while (opcion != 0);
}
