#include <iostream>
#include "MenuProducto.h"
#include "rlutil.h"
#include "Utilidades.h"

using namespace std;

void MenuProducto::mostrar() {
    int opcion;

    do {
        rlutil::cls();
        cout << "\n--- MENU PRODUCTOS ---\n";
        cout << "1) Alta producto\n";
        cout << "2) Listar productos\n";
        cout << "3) Baja de producto\n";
        cout << "4) Modificacion de producto\n";
        cout << "5) Reactivar producto\n";
        cout << "6) Consultas de productos\n";
        cout << "0) Volver\n";
        cout << "===========================\n";
        cout << "Opcion: ";

        opcion = leerOpcion();
        switch (opcion) {
            case 1:
                rlutil::cls();
                _manager.altaProducto();
                pausa();
                break;

            case 2:
                rlutil::cls();
                mostrarListadoProductos();
                pausa();
                break;

           case 3: {
            rlutil::cls();
            if (!_manager.listarProductos()) {
                pausa();
                break;
            }

            int id;
            char confirmacion;
            while (true) {
                cout << "\nIngrese ID del producto a dar de baja (0 para cancelar): ";
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

                if (!_manager.existeProducto(id)) {
                    rlutil::setColor(rlutil::RED);
                    cout << "Error: Producto no encontrado.\n ";
                    rlutil::setColor(rlutil::WHITE);
                    continue;
                }

                cout << "\nSeguro que desea eliminar el producto? (s/n): ";
                cin >> confirmacion;
                limpiarEntrada();

                if (confirmacion == 's' || confirmacion == 'S') {
                    if (_manager.bajaProducto(id)) {
                        rlutil::setColor(rlutil::GREEN);
                        cout << "Producto dado de baja correctamente.\n";
                        rlutil::setColor(rlutil::WHITE);
                    } else {
                        rlutil::setColor(rlutil::RED);
                        cout << "No se pudo eliminar el producto.\n";
                        rlutil::setColor(rlutil::WHITE);
                    }
                } else {
                    rlutil::setColor(rlutil::RED);
                    cout << "OPCION INVALIDA. INTENTE NUEVAMENTE.\n";
                    rlutil::setColor(rlutil::WHITE);
                }

                pausa();
                break;
            }
            break;
        }

            case 4:
                rlutil::cls();
                _manager.modificarProducto();
                pausa();
                break;

            case 5: {
                rlutil::cls();
                if (!_manager.listarProductoEliminados()) {
                    pausa();
                    break;
                }

                int id;
                while (true) {
                    cout << "\nIngrese ID del producto a reactivar (0 para cancelar): ";
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

                    if (_manager.reactivarProducto(id)) {
                        rlutil::setColor(rlutil::GREEN);
                        cout << "Producto reactivado correctamente.\n";
                        rlutil::setColor(rlutil::WHITE);
                        pausa();
                        break;
                    } else {
                        rlutil::setColor(rlutil::RED);
                        cout << "Error: ID invalido o el producto ya estaba activo.\n";
                        rlutil::setColor(rlutil::WHITE);
                        continue;
                    }
                }
                break;
            }
            case 6:
                mostrarConsultasProductos();
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

void MenuProducto::mostrarListadoProductos() {
    int opcion;
    do {
        rlutil::cls();
        cout << "\n--- LISTADO DE PRODUCTOS ---\n";
        cout << "1) Todos los productos\n";
        cout << "2) Ordenado por nombre\n";
        cout << "3) Ordenado por marca\n";
        cout << "4) Ordenado por precio\n";
        cout << "5) Ordenado por stock\n";
        cout << "0) Volver\n";
        cout << "===========================\n";
        cout << "Opcion: ";

        opcion = leerOpcion();
        switch (opcion) {
            case 1: rlutil::cls(); _manager.listarProductos();        pausa(); break;
            case 2: rlutil::cls(); _manager.listarProductoPorNombre();pausa(); break;
            case 3: rlutil::cls(); _manager.listarProductoPorMarca(); pausa(); break;
            case 4: rlutil::cls(); _manager.listarProductoPorPrecio();pausa(); break;
            case 5: rlutil::cls(); _manager.listarProductoPorStock(); pausa(); break;
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

void MenuProducto::mostrarConsultasProductos() {
    int opcion;

    do {
        rlutil::cls();
        cout << "\n--- CONSULTAS DE PRODUCTOS ---\n";
        cout << "1) Consultar por nombre\n";
        cout << "2) Consultar por modelo\n";
        cout << "3) Consultar por rango de precio\n";
        cout << "4) Consultar por proveedor\n";
        cout << "0) Volver\n";
        cout << "===========================\n";
        cout << "Opcion: ";

        opcion = leerOpcion();
        switch (opcion) {
            case 1:
                rlutil::cls();
                _manager.buscarProductoPorNombre();
                pausa();
                break;

            case 2:
                rlutil::cls();
                _manager.buscarProductoPorTipo();
                pausa();
                break;

            case 3:
                rlutil::cls();
                _manager.buscarProductoPorRangoPrecio();
                pausa();
                break;

            case 4:
                rlutil::cls();
                _manager.buscarProductoPorProveedor();
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
