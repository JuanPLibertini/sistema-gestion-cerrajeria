#include <iostream>
#include "MenuInforme.h"
#include "EmpleadoArchivo.h"
#include "ClienteArchivo.h"
#include "ProveedorArchivo.h"
#include "rlutil.h"
#include "Utilidades.h"

using namespace std;

void MenuInforme::mostrar() {
    int opcion;

    do {
        rlutil::cls();
        cout << "\n--- MENU INFORMES ---\n";
        cout << "1) Informes de compras\n";
        cout << "2) Informes de ventas\n";
        cout << "3) Informes de servicios\n";
        cout << "0) Volver\n";
        cout << "===========================\n";
        cout << "Opcion: ";

        opcion = leerOpcion();
        switch (opcion) {
            case 1:
                rlutil::cls();
                mostrarInformesCompras();
                break;

            case 2:
                rlutil::cls();
                mostrarInformesVentas();
                break;

            case 3:
                rlutil::cls();
                mostrarInformesServicios();
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

void MenuInforme::mostrarInformesCompras() {
    int opcion;

    do {
        rlutil::cls();
        cout << "\n--- INFORMES DE COMPRAS ---\n";
        cout << "1) Facturacion de compras en un periodo\n";
        cout << "2) Facturacion de un proveedor en un periodo\n";
        cout << "3) Facturacion total de compras\n";
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

                _manager.informeFacturacionComprasPeriodo(desde, hasta);
                pausa();
                break;
            }
            case 2: {
                rlutil::cls();
                ProveedorArchivo archivoProv;

                cout << "LISTADO DE PROVEEDORES:\n";
                cout << "---------------------------\n";
                int cantProv = archivoProv.getCantidadRegistros();
                bool hayProveedores = false;

                for (int i = 0; i < cantProv; i++) {
                    Proveedor p = archivoProv.leer(i);
                    if (!p.getEliminado()) {
                        cout << "ID: " << p.getIdProveedor()
                             << " - " << p.getNombre() << endl;
                        hayProveedores = true;
                    }
                }

                if (!hayProveedores) {
                    rlutil::setColor(rlutil::RED);
                    cout << "NO HAY PROVEEDORES CARGADOS.\n";
                    rlutil::setColor(rlutil::WHITE);
                    pausa();
                    break;
                }

                cout << "---------------------------\n";
                int idProveedor;
                int posProv;

                while (true) {
                    cout << "Ingrese ID de proveedor (0 para cancelar): ";
                    cin >> idProveedor;

                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(1000, '\n');
                        rlutil::setColor(rlutil::RED);
                        cout << "Entrada invalida. Debe ingresar un numero.\n";
                        rlutil::setColor(rlutil::WHITE);
                        continue;
                    }
                    cin.ignore(1000, '\n');

                    if (idProveedor == 0) {
                        rlutil::setColor(rlutil::RED);
                        cout << "Operacion cancelada.\n";
                        rlutil::setColor(rlutil::WHITE);
                        pausa();
                        break;
                    }

                    posProv = archivoProv.buscarPorId(idProveedor);
                    if (posProv == -1) {
                        rlutil::setColor(rlutil::RED);
                        cout << "Proveedor inexistente.\n";
                        rlutil::setColor(rlutil::WHITE);
                        continue;
                    }
                    break;
                }

                if (posProv == -1) break;

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


                _manager.informeFacturacionProveedorPeriodo(idProveedor, desde, hasta);
                pausa();
                break;
            }
            case 3:
                _manager.informeFacturacionComprasTotal();
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

void MenuInforme::mostrarInformesVentas() {
    int opcion;

    do {
        rlutil::cls();
        cout << "\n--- INFORMES DE VENTAS ---\n";
        cout << "1) Facturacion de ventas en un periodo\n";
        cout << "2) Facturacion de un cliente en un periodo\n";
        cout << "3) Facturacion total de ventas\n";
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

                _manager.informeFacturacionVentasPeriodo(desde, hasta);
                pausa();
                break;
            }
            case 2: {
                rlutil::cls();
                ClienteArchivo archivoCli;

                cout << "LISTADO DE CLIENTES:\n";
                cout << "---------------------------\n";
                int cantCli = archivoCli.getCantidadRegistros();
                bool hayClientes = false;

                for (int i = 0; i < cantCli; i++) {
                    Cliente c = archivoCli.leer(i);
                    if (!c.getEliminado()) {
                        cout << "ID: " << c.getIdCliente()
                             << " - " << c.getNombre()
                             << " " << c.getApellido() << endl;
                        hayClientes = true;
                    }
                }

                if (!hayClientes) {
                    rlutil::setColor(rlutil::RED);
                    cout << "NO HAY CLIENTES CARGADOS.\n";
                    rlutil::setColor(rlutil::WHITE);
                    pausa();
                    break;
                }

                cout << "---------------------------\n";
                int idCliente;
                int posCli;

                while (true) {
                    cout << "Ingrese ID de cliente (0 para cancelar): ";
                    cin >> idCliente;

                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(1000, '\n');
                        rlutil::setColor(rlutil::RED);
                        cout << "Entrada invalida. Debe ingresar un numero.\n";
                        rlutil::setColor(rlutil::WHITE);
                        continue;
                    }
                    cin.ignore(1000, '\n');

                    if (idCliente == 0) {
                        rlutil::setColor(rlutil::RED);
                        cout << "Operacion cancelada.\n";
                        rlutil::setColor(rlutil::WHITE);
                        pausa();
                        break;
                    }

                    posCli = archivoCli.buscarPorId(idCliente);
                    if (posCli == -1) {
                        rlutil::setColor(rlutil::RED);
                        cout << "Cliente inexistente.\n";
                        rlutil::setColor(rlutil::WHITE);
                        continue;
                    }
                    break;
                }

                if (posCli == -1) break;

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

                _manager.informeFacturacionClientePeriodo(idCliente, desde, hasta);
                pausa();
                break;
            }
            case 3:
                _manager.informeFacturacionVentasTotal();
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

void MenuInforme::mostrarInformesServicios() {
    int opcion;

    do {
        rlutil::cls();
        cout << "\n--- INFORMES DE SERVICIOS ---\n";
        cout << "1) Facturacion de servicios en un periodo\n";
        cout << "2) Servicios realizados por empleado\n";
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

                _manager.informeFacturacionServiciosPeriodo(desde, hasta);
                pausa();
                break;
            }
            case 2: {
                rlutil::cls();
                EmpleadoArchivo archivoEmp;

                cout << "LISTADO DE EMPLEADOS:\n";
                cout << "---------------------------\n";
                int cantEmp = archivoEmp.getCantidadRegistros();
                bool hayEmpleados = false;

                for (int i = 0; i < cantEmp; i++) {
                    Empleado e = archivoEmp.leer(i);
                    if (!e.getEliminado()) {
                        cout << "ID: " << e.getIdEmpleado()
                             << " - " << e.getNombre()
                             << " " << e.getApellido() << endl;
                        hayEmpleados = true;
                    }
                }

                if (!hayEmpleados) {
                    rlutil::setColor(rlutil::RED);
                    cout << "NO HAY EMPLEADOS CARGADOS.\n";
                    rlutil::setColor(rlutil::WHITE);
                    pausa();
                    break;
                }

                cout << "---------------------------\n";
                int idEmpleado;
                int posEmp;

                while (true) {
                    cout << "Ingrese ID de empleado (0 para cancelar): ";
                    cin >> idEmpleado;

                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(1000, '\n');
                        rlutil::setColor(rlutil::RED);
                        cout << "Entrada invalida. Debe ingresar un numero.\n";
                        rlutil::setColor(rlutil::WHITE);
                        continue;
                    }
                    cin.ignore(1000, '\n');

                    if (idEmpleado == 0) {
                        rlutil::setColor(rlutil::RED);
                        cout << "Operacion cancelada.\n";
                        rlutil::setColor(rlutil::WHITE);
                        pausa();
                        break;
                    }

                    posEmp = archivoEmp.buscarPorId(idEmpleado);
                    if (posEmp == -1) {
                        rlutil::setColor(rlutil::RED);
                        cout << "Empleado inexistente.\n";
                        rlutil::setColor(rlutil::WHITE);
                        continue;
                    }
                    break;
                }

                if (posEmp == -1) break;

                rlutil::cls();
                _manager.informeServiciosPorEmpleado(idEmpleado);
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
