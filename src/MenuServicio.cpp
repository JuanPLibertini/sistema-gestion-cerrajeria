#include <iostream>
#include "MenuServicio.h"
#include "rlutil.h"
#include "Utilidades.h"

using namespace std;

void pausa();
void limpiarEntrada();

void MenuServicio::mostrar() {
    int opcion;

    do {
        rlutil::cls();
        cout << "\n--- MENU SERVICIOS ---\n";
        cout << "1) Alta servicio\n";
        cout << "2) Listar servicios\n";
        cout << "3) Baja de servicio\n";
        cout << "4) Modificacion de servicio\n";
        cout << "5) Reactivar servicio\n";
        cout << "6) Consultas de servicios\n";
        cout << "0) Volver\n";
        cout << "===========================\n";
        cout << "Opcion: ";

        opcion = leerOpcion();
        switch (opcion) {
            case 1:
                rlutil::cls();
                _manager.altaServicio();
                pausa();
                break;

            case 2:
                rlutil::cls();
                mostrarListadoServicios();
                break;

            case 3: {
            rlutil::cls();
            if (!_manager.listarServicios()) {
                pausa();
                break;
            }

            int id;
            while (true) {
                cout << "\nIngrese ID del servicio a dar de baja (0=Cancelar): ";
                if (!(cin >> id)) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    rlutil::setColor(rlutil::RED);
                    cout << "Error: debe ingresar un numero.\n";
                    rlutil::setColor(rlutil::WHITE);
                    continue;
                }
                cin.ignore(1000, '\n');

                if (id == 0) {
                    rlutil::setColor(rlutil::RED);
                    cout << "OPERACION CANCELADA.\n";
                    rlutil::setColor(rlutil::WHITE);
                    pausa();
                    break; //
                }

                if (!_manager.existeServicio(id)) {
                    rlutil::setColor(rlutil::RED);
                    cout << "Error: servicio inexistente.\n";
                    rlutil::setColor(rlutil::WHITE);
                    continue; // vuelve a pedir
                }

                char confirmacion;
                cout << "\nSeguro que desea eliminar el servicio? (s/n): ";
                cin >> confirmacion;
                cin.ignore(1000, '\n');

                if (confirmacion == 's' || confirmacion == 'S') {
                    if (_manager.bajaServicio(id)) {
                        rlutil::setColor(rlutil::GREEN);
                        cout << "Servicio dado de baja correctamente.\n";
                        rlutil::setColor(rlutil::WHITE);
                    } else {
                        rlutil::setColor(rlutil::RED);
                        cout << "Error: servicio no encontrado o ya eliminado.\n";
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
                _manager.modificarServicio();
                pausa();
                break;

            case 5: {
                rlutil::cls();
                if (!_manager.listarServiciosEliminados()) {
                    pausa();
                    break;
                }

                int id;
                while (true) {
                    cout << "\nIngrese ID del servicio a reactivar (0=Cancelar): ";
                    if (!(cin >> id)) {
                        cin.clear();
                        cin.ignore(1000, '\n');
                        rlutil::setColor(rlutil::RED);
                        cout << "Error: debe ingresar un numero.\n";
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

                    if (!_manager.existeServicioIncluyendoEliminados(id)) {
                        rlutil::setColor(rlutil::RED);
                        cout << "Error: servicio inexistente.\n";
                        rlutil::setColor(rlutil::WHITE);
                        continue;
                    }

                    if (_manager.reactivarServicio(id)) {
                        rlutil::setColor(rlutil::GREEN);
                        cout << "Servicio reactivado correctamente.\n";
                        rlutil::setColor(rlutil::WHITE);
                        pausa();
                        break;
                    } else {
                        rlutil::setColor(rlutil::RED);
                        cout << "Error: ID invalido o el servicio ya estaba activo.\n";
                        rlutil::setColor(rlutil::WHITE);
                        continue;
                        }
                    }
                    break;
                }

            case 6:
                rlutil::cls();
                mostrarConsultaServicios();
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

void MenuServicio::mostrarConsultaServicios() {
    int opcion;

    do {
        rlutil::cls();
        cout << "\n--- CONSULTA DE SERVICIOS ---\n";
        cout << "1) Por tipo (1=Local, 2=Calle)\n";
        cout << "2) Por rango de precio\n";
        cout << "0) Volver\n";
        cout << "===========================\n";
        cout << "Opcion: ";

        opcion = leerOpcion();
        switch (opcion) {
            case 1: {
                rlutil::cls();
                _manager.buscarServicioPorTipo();
                limpiarEntrada();
                break;}
            case 2: {
                    rlutil::cls();
                    _manager.buscarServicioPorRangoPrecio();
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
        }while (opcion != 0);
    }

void MenuServicio::mostrarListadoServicios() {
    int opcion;

    do {
        rlutil::cls();
        cout << "\n--- LISTADO DE SERVICIOS ---\n";
        cout << "1) Todos los servicios\n";
        cout << "2) Ordenado por descripcion\n";
        cout << "3) Ordenado por tipo\n";
        cout << "4) Ordenado por precio\n";
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
            case 2:
                rlutil::cls();
                _manager.listarOrdenadoPorDescripcion();
                pausa();
                break;
            case 3:
                rlutil::cls();
                _manager.listarOrdenadoPorTipo();
                pausa();
                break;
            case 4:
                rlutil::cls();
                _manager.listarOrdenadoPorPrecio();
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
