#include <iostream>
#include "MenuPrincipal.h"
#include "rlutil.h"
#include "Utilidades.h"

using namespace std;

void MenuPrincipal::mostrar() {
    int opcion;
    do {
        rlutil::cls();
        cout << "\n=========== MENU PRINCIPAL ===========\n";
        cout << "1) Productos\n";
        cout << "2) Proveedores\n";
        cout << "3) Clientes\n";
        cout << "4) Empleados\n";
        cout << "5) Servicios\n";
        cout << "6) Compras\n";
        cout << "7) Ventas\n";
        cout << "8) Informes\n";
        cout << "0) Salir\n";
        cout << "===========================\n";
        cout << "Opcion: ";

        opcion = leerOpcion();
        rlutil::cls();

        switch (opcion) {
            case 1: _menuProducto.mostrar();   break;
            case 2: _menuProveedor.mostrar(); break;
            case 3: _menuCliente.mostrar();    break;
            case 4: _menuEmpleado.mostrar();   break;
            case 5: _menuServicio.mostrar();   break;
            case 6: _menuCompra.mostrar();     break;
            case 7: _menuVenta.mostrar();   break;
            case 8: _menuInforme.mostrar();  break;
            case 0: cout << "Saliendo...\n"; break;
            default:
                rlutil::setColor(rlutil::RED);
                cout << "OPCION INVALIDA. INTENTE NUEVAMENTE.\n";
                rlutil::setColor(rlutil::WHITE);
                pausa();
                break;
        }
    } while (opcion != 0);
}
