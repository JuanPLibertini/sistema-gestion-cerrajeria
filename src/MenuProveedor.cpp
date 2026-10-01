#include <iostream>
#include "MenuProveedor.h"
#include "rlutil.h"
#include "Utilidades.h"

using namespace std;

void MenuProveedor::mostrar() {
    int opcion;

    do {
        rlutil::cls();
        cout << "\n--- MENU PROVEEDORES ---\n";
        cout << "1) Alta Proveedor\n";
        cout << "2) Listar Proveedores\n";
        cout << "3) Baja de Proveedor\n";
        cout << "4) Modificacion de Proveedor\n";
        cout << "5) Reactivar Proveedor\n";
        cout << "6) Consultas de proveedores\n";
        cout << "0) Volver\n";
        cout << "===========================\n";
        cout << "Opcion: ";

        opcion = leerOpcion();
        switch (opcion) {
            case 1:
                rlutil::cls();
                _manager.altaProveedor();
                pausa();
                break;

            case 2:
                rlutil::cls();
                mostrarListadoProveedores();
                pausa();
                break;

            case 3: {
                rlutil::cls();
                if (!_manager.listarProveedores()) {
                    pausa();
                    break;
                }
                int id;
                char confirmacion;

                while (true) {
                    cout << "\nIngrese ID del Proveedor a dar de baja (0 para cancelar): ";
                    cin >> id;

                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(1000, '\n');
                        rlutil::setColor(rlutil::RED);
                        cout << "Error: Entrada invalida. Debe ingresar un numero entero positivo.\n";
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
                        cout << "Error: El ID no puede ser negativo.\n";
                        rlutil::setColor(rlutil::WHITE);
                        continue;
                    }
                    if (!_manager.existeProveedor(id)) {
                        rlutil::setColor(rlutil::RED);
                        cout << "Error: Proveedor no encontrado.\n";
                        rlutil::setColor(rlutil::WHITE);
                        continue;
                    }

                    cout << "\nSeguro que desea eliminar el Proveedor? (s/n): ";
                    cin >> confirmacion;
                    limpiarEntrada();

                    if (confirmacion == 's' || confirmacion == 'S') {
                        if (_manager.bajaProveedor(id)) {
                            rlutil::setColor(rlutil::GREEN);
                            cout << "Proveedor dado de baja correctamente.\n";
                            rlutil::setColor(rlutil::WHITE);
                        } else {
                            rlutil::setColor(rlutil::RED);
                            cout << "Error: No se pudo eliminar el proveedor.\n";
                            rlutil::setColor(rlutil::WHITE);
                        }
                    } else {
                        rlutil::setColor(rlutil::RED);
                        cout << "OPERACION CANCELADA.\n";
                        rlutil::setColor(rlutil::WHITE);
                    }

                    pausa();
                    break;
                }
                break;
            }
            case 4:
                rlutil::cls();
                _manager.modificarProveedor();
                pausa();
                break;

            case 5: {
                rlutil::cls();
                if (!_manager.listarProveedorEliminados()) {
                    pausa();
                    break;
                }

                int id;
                while (true) {
                    cout << "\nIngrese ID del Proveedor a reactivar (0 para cancelar): ";
                    cin >> id;

                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(1000, '\n');
                        rlutil::setColor(rlutil::RED);
                        cout << "Error: Entrada invalida. Debe ingresar un numero entero positivo.\n";
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
                        cout << "Error: El ID no puede ser negativo.\n";
                        rlutil::setColor(rlutil::WHITE);
                        continue;
                    }

                    if (_manager.reactivarProveedor(id)) {
                        rlutil::setColor(rlutil::GREEN);
                        cout << "Proveedor reactivado correctamente.\n";
                        rlutil::setColor(rlutil::WHITE);
                        pausa();
                        break;
                    } else {
                        rlutil::setColor(rlutil::RED);
                        cout << "Error: ID invalido o el proveedor ya estaba activo.\n";
                        rlutil::setColor(rlutil::WHITE);
                        continue;
                    }
                }
                break;
            }

            case 6:
                mostrarConsultasProveedores();
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

void MenuProveedor::mostrarListadoProveedores() {
    int opcion;
    do {
        rlutil::cls();
        cout << "\n--- LISTADO DE PROVEEDORES ---\n";
        cout << "1) Todos los Proveedors\n";
        cout << "2) Ordenado por nombre\n";
        cout << "0) Volver\n";
        cout << "===========================\n";
        cout << "Opcion: ";

        opcion = leerOpcion();
        switch (opcion) {
            case 1: rlutil::cls(); _manager.listarProveedores();      pausa(); break;
            case 2: rlutil::cls(); _manager.listarProveedoresPorNombre();pausa(); break;
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

void MenuProveedor::mostrarConsultasProveedores() {
    int opcion;

    do {
        rlutil::cls();
        cout << "\n--- CONSULTAS DE PROVEEDORES ---\n";
        cout << "1) Consultar por nombre\n";
        cout << "0) Volver\n";
        cout << "===========================\n";
        cout << "Opcion: ";

        opcion = leerOpcion();
        switch (opcion) {
            case 1:
                rlutil::cls();
                _manager.buscarProveedorPorNombre();
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
