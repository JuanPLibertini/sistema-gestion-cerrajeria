#include <iostream>
#include "MenuCompra.h"
#include "rlutil.h"
#include "Utilidades.h"

using namespace std;

void MenuCompra::mostrar() {
    int opcion;

    do {
        rlutil::cls();
        cout << "\n--- MENU COMPRAS ---\n";
        cout << "1) Alta Compra\n";
        cout << "2) Listar Compras\n";
        cout << "3) Baja de Compra\n";
        cout << "4) Modificacion de Compra\n";
        cout << "5) Reactivar Compra\n";
        cout << "6) Consultas de Compras\n";
        cout << "7) Detalles de compra (productos)\n";
        cout << "0) Volver\n";
        cout << "===========================\n";
        cout << "Opcion: ";

        opcion = leerOpcion();
        switch (opcion) {
            case 1:
                rlutil::cls();
                _manager.altaCompra();
                pausa();
                break;

            case 2:
                rlutil::cls();
                mostrarListadoCompras();
                pausa();
                break;

            case 3: {
                rlutil::cls();
                if (!_manager.listarCompras()) {
                    pausa();
                    break;
                }

                int id;
                char confirmacion;

                cout << "\nIngrese ID del Compra a dar de baja: ";
                cin >> id;
                limpiarEntrada();

                if (!_manager.existeCompra(id)) {
                    rlutil::setColor(rlutil::RED);
                    cout << "Compra no encontrado.\n";
                    rlutil::setColor(rlutil::WHITE);
                    pausa();
                    break;
                }

                cout << "\nSeguro que desea eliminar el Compra? (s/n): ";
                cin >> confirmacion;
                limpiarEntrada();

                if (confirmacion == 's' || confirmacion == 'S') {
                    if (_manager.bajaCompra(id)) {
                        rlutil::setColor(rlutil::GREEN);
                        cout << "Compra dado de baja correctamente.\n";
                        rlutil::setColor(rlutil::WHITE);
                    } else {
                        rlutil::setColor(rlutil::RED);
                        cout << "Compra no encontrado o ya eliminado.\n";
                        rlutil::setColor(rlutil::WHITE);
                    }
                } else {
                    cout << "Operacion cancelada\n";
                }

                pausa();
                break;
            }

            case 4:
                rlutil::cls();
                _manager.modificarCompra();
                pausa();
                break;

            case 5: {
                rlutil::cls();
                if (!_manager.listarCompraEliminada()) {
                    pausa();
                    break;
                }

                int id;
                cout << "\nIngrese ID del Compra a reactivar: ";
                cin >> id;
                limpiarEntrada();

                if (_manager.reactivarCompra(id)) {
                    rlutil::setColor(rlutil::GREEN);
                    cout << "Compra reactivado correctamente.\n";
                    rlutil::setColor(rlutil::WHITE);
                } else {
                    rlutil::setColor(rlutil::RED);
                    cout << "ID invalido o el Compra ya estaba activo.\n";
                    rlutil::setColor(rlutil::WHITE);
                }
                pausa();
                break;
            }

            case 6:
                rlutil::cls();
                mostrarConsultasCompras();
                break;

            case 7:
                rlutil::cls();
                mostrarDetallesCompra();
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

void MenuCompra::mostrarListadoCompras() {
    int opcion;
    do {
        rlutil::cls();
        cout << "\n--- LISTADO DE COMPRAS ---\n";
        cout << "1) Todas los Compras\n";
        cout << "2) Ordenado por empleado\n";
        cout << "3) Ordenado por proveedor\n";
        cout << "4) Ordenado por fecha\n";
        cout << "0) Volver\n";
        cout << "===========================\n";
        cout << "Opcion: ";

        opcion = leerOpcion();
        switch (opcion) {
            case 1: rlutil::cls(); _manager.listarCompras();           pausa(); break;
            case 2: rlutil::cls(); _manager.listarCompraPorEmpleado(); pausa(); break;
            case 3: rlutil::cls(); _manager.listarCompraPorProveedor();pausa(); break;
            case 4: rlutil::cls(); _manager.listarCompraPorFecha();    pausa(); break;
            case 0: break;
            default:
                rlutil::setColor(rlutil::RED);
                cout << "OPCION INVALIDA. INTENTE NUEVAMENTE.\n";
                rlutil::setColor(rlutil::WHITE);
                pausa();
                break;
        }
    } while (opcion != 0);
}

void MenuCompra::mostrarConsultasCompras() {
    int opcion;

    do {
        rlutil::cls();
        cout << "\n--- CONSULTA DE COMPRAS ---\n";
        cout << "1) Por rango de fechas\n";
        cout << "2) Por marca\n";
        cout << "3) Por proveedor\n";
        cout << "4) Por empleado\n";
        cout << "0) Volver\n";
        cout << "===========================\n";
        cout << "Opcion: ";

        opcion = leerOpcion();
        switch (opcion) {
            case 1: {
                rlutil::cls();
                Fecha desde, hasta;

                cout << "Fecha desde:\n";
                if (!desde.Cargar()) {
                    rlutil::setColor(rlutil::RED);
                    cout << "Operacion cancelada.\n";
                    rlutil::setColor(rlutil::WHITE);
                    pausa();
                    break;
                }

                cout << "Fecha hasta:\n";
                if (!hasta.Cargar()) {
                    rlutil::setColor(rlutil::RED);
                    cout << "Operacion cancelada.\n";
                    rlutil::setColor(rlutil::WHITE);
                    pausa();
                    break;
                }
            }
            case 2: {
                char marca[50];
                cout << "Ingrese marca: ";
                cin.getline(marca, 50);
                _manager.listarComprasPorMarca(marca);
                pausa();
                break;
            }
            case 3: {
                int idProveedor;
                cout << "Ingrese ID de proveedor: ";
                cin >> idProveedor;
                limpiarEntrada();
                _manager.listarComprasPorProveedor(idProveedor);
                pausa();
                break;
            }
            case 4: {
                int idEmpleado;
                cout << "Ingrese ID de empleado: ";
                cin >> idEmpleado;
                limpiarEntrada();
                _manager.listarComprasPorEmpleado(idEmpleado);
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

void MenuCompra::mostrarDetallesCompra() {
    int opcion;

    do {
        rlutil::cls();
        cout << "\n--- DETALLES DE COMPRA (PRODUCTOS) ---\n";
        cout << "1) Listar todos los detalles\n";
        cout << "2) Por ID de compra\n";
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
                int idCompra;
                cout << "Ingrese ID de compra: ";
                cin >> idCompra;
                rlutil::cls();
                limpiarEntrada();
                _manager.listarDetallesPorCompra(idCompra);
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
