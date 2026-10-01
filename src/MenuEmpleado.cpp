#include <iostream>
#include "MenuEmpleado.h"
#include "rlutil.h"
#include "Utilidades.h"

using namespace std;

void MenuEmpleado::mostrar() {
    int opcion;

    do {
        rlutil::cls();
        cout << "\n--- MENU EMPLEADOS ---\n";
        cout << "1) Alta empleado\n";
        cout << "2) Listar empleados\n";
        cout << "3) Baja de empleado\n";
        cout << "4) Modificacion de empleado\n";
        cout << "5) Reactivar empleado\n";
        cout << "6) Consultas de empleados\n";
        cout << "0) Volver\n";
        cout << "===========================\n";
        cout << "Opcion: ";

        opcion = leerOpcion();
        switch (opcion) {
            case 1:
                rlutil::cls();
                _manager.altaEmpleado();
                pausa();
                break;

            case 2:
                rlutil::cls();
                mostrarListadoEmpleados();
                pausa();
                break;
            case 3: {
                rlutil::cls();
                if (!_manager.listarEmpleados()) {
                    pausa();
                    break;
                }
                int id;
                char confirmacion;

                while (true) {
                    cout << "\nIngrese ID del empleado a dar de baja (0 para cancelar): ";
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
                    if (!_manager.existeEmpleado(id)) {
                        rlutil::setColor(rlutil::RED);
                        cout << "Error: Empleado no encontrado.\n";
                        rlutil::setColor(rlutil::WHITE);
                        continue;
                    }

                    cout << "\nSeguro que desea eliminar el empleado? (s/n): ";
                    cin >> confirmacion;
                    limpiarEntrada();

                    if (confirmacion == 's' || confirmacion == 'S') {
                        if (_manager.bajaEmpleado(id)) {
                            rlutil::setColor(rlutil::GREEN);
                            cout << "Empleado dado de baja correctamente.\n";
                            rlutil::setColor(rlutil::WHITE);
                        } else {
                            rlutil::setColor(rlutil::RED);
                            cout << "Error: No se pudo eliminar el empleado.\n";
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
                _manager.modificarEmpleado();
                pausa();
                break;

            case 5: {
                    rlutil::cls();
                    if (!_manager.listarEmpleadosEliminados()) {
                        pausa();
                        break;
                    }
                    int id;
                    while (true) {
                        cout << "\nIngrese ID del empleado a reactivar (0 para cancelar): ";
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
                            cout << "OPERACION CANCELADA\n";
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

                        if (_manager.reactivarEmpleado(id)) {
                            rlutil::setColor(rlutil::GREEN);
                            cout << "Empleado reactivado correctamente.\n";
                            rlutil::setColor(rlutil::WHITE);
                            pausa();
                            break;
                        } else {
                            rlutil::setColor(rlutil::RED);
                            cout << "Error: ID invalido o el empleado ya estaba activo.\n";
                            rlutil::setColor(rlutil::WHITE);
                            continue;
                        }
                    }
                    break;
                }


            case 6:
                mostrarConsultasEmpleados();
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

void MenuEmpleado::mostrarListadoEmpleados() {
    int opcion;
    do {
        rlutil::cls();
        cout << "\n--- LISTADO DE EMPLEADOS ---\n";
        cout << "1) Todos los empleados\n";
        cout << "2) Ordenado por apellido\n";
        cout << "3) Ordenado por cargo\n";
        cout << "0) Volver\n";
        cout << "===========================\n";
        cout << "Opcion: ";

        opcion = leerOpcion();
        switch (opcion) {
            case 1:
                rlutil::cls();
                _manager.listarEmpleados();
                pausa();
                break;

            case 2:
                 rlutil::cls();
                 _manager.listarEmpleadoPorApellido();
                 pausa();
                 break;

            case 3:
                rlutil::cls();
                 _manager.listarEmpleadoPorCargo();
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

void MenuEmpleado::mostrarConsultasEmpleados() {
    int opcion;

    do {
        rlutil::cls();
        cout << "\n--- CONSULTAS DE EMPLEADOS ---\n";
        cout << "1) Consultar por apellido\n";
        cout << "2) Consultar por cargo\n";
        cout << "0) Volver\n";
        cout << "===========================\n";
        cout << "Opcion: ";

        opcion = leerOpcion();
        switch (opcion) {
            case 1:
                rlutil::cls();
                _manager.buscarEmpleadoPorApellido();
                pausa();
                break;

            case 2:
                rlutil::cls();
                _manager.buscarEmpleadoPorCargo();
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
