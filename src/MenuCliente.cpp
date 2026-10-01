#include <iostream>
#include "MenuCliente.h"
#include "rlutil.h"
#include "Utilidades.h"

using namespace std;

void MenuCliente::mostrar() {
    int opcion;

    do {
        rlutil::cls();
        cout << "\n--- MENU CLIENTES ---\n";
        cout << "1) Alta Cliente\n";
        cout << "2) Listar Clientes\n";
        cout << "3) Baja de Cliente\n";
        cout << "4) Modificacion de Cliente\n";
        cout << "5) Reactivar Cliente\n";
        cout << "6) Consultas de Clientes\n";
        cout << "0) Volver\n";
        cout << "===========================\n";
        cout << "Opcion: ";

        opcion = leerOpcion();
        switch (opcion) {
            case 1:
                rlutil::cls();
                _manager.altaCliente();
                pausa();
                break;

            case 2:
                rlutil::cls();
                mostrarListadoClientes();
                pausa();
                break;

            case 3: {
                rlutil::cls();
                if (!_manager.listarClientes()) {
                    pausa();
                    break;
                }

                int id;
                char confirmacion;

                while (true) {
                    cout << "\nIngrese ID del cliente a dar de baja (0 para cancelar): ";
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
                    if (!_manager.existeCliente(id)) {
                        rlutil::setColor(rlutil::RED);
                        cout << "Error: Cliente no encontrado.\n";
                        rlutil::setColor(rlutil::WHITE);
                        continue;
                    }

                    cout << "\nSeguro que desea eliminar el cliente? (s/n): ";
                    cin >> confirmacion;
                    limpiarEntrada();

                    if (confirmacion == 's' || confirmacion == 'S') {
                        if (_manager.bajaCliente(id)) {
                            rlutil::setColor(rlutil::GREEN);
                            cout << "Cliente dado de baja correctamente.\n";
                            rlutil::setColor(rlutil::WHITE);
                        } else {
                            rlutil::setColor(rlutil::RED);
                            cout << "Error: No se pudo eliminar el cliente.\n";
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
                _manager.modificarCliente();
                pausa();
                break;

            case 5: {
                rlutil::cls();
                if (!_manager.listarClientesEliminados()) {
                    pausa();
                    break;
                }

                int id;
                while (true) {
                    cout << "\nIngrese ID del cliente a reactivar (0 para cancelar): ";
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
                        cout << "Operacion cancelada.\n";
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

                    if (_manager.reactivarCliente(id)) {
                        rlutil::setColor(rlutil::GREEN);
                        cout << "Cliente reactivado correctamente.\n";
                        rlutil::setColor(rlutil::WHITE);
                        pausa();
                        break;
                    } else {
                        rlutil::setColor(rlutil::RED);
                        cout << "Error: ID invalido o el cliente ya estaba activo.\n";
                        rlutil::setColor(rlutil::WHITE);
                        continue;
                    }
                }
                break;
            }

            case 6:
                mostrarConsultasClientes();
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

void MenuCliente::mostrarListadoClientes() {
    int opcion;
    do {
        rlutil::cls();
        cout << "\n--- LISTADO DE CLIENTES ---\n";
        cout << "1) Todos los Clientes\n";
        cout << "2) Ordenado por nombre\n";
        cout << "3) Ordenado por apellido\n";
        cout << "0) Volver\n";
        cout << "===========================\n";
        cout << "Opcion: ";

        opcion = leerOpcion();
        switch (opcion) {
            case 1:
                rlutil::cls();
                _manager.listarClientes();
                pausa();
                break;

            case 2:
                rlutil::cls();
                _manager.listarClientesPorNombre();
                pausa();
                break;

            case 3:
                rlutil::cls();
                 _manager.listarClientesPorApellido();
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

void MenuCliente::mostrarConsultasClientes() {
    int opcion;

    do {
        rlutil::cls();
        cout << "\n--- CONSULTAS DE CLIENTES ---\n";
        cout << "1) Consultar por nombre\n";
        cout << "2) Consultar por apellido\n";
        cout << "0) Volver\n";
        cout << "===========================\n";
        cout << "Opcion: ";

        opcion = leerOpcion();
        switch (opcion) {
            case 1:
                _manager.buscarClientePorNombre();
                pausa();
                break;

            case 2:
                _manager.buscarClientePorApellido();
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
