#include <cstdio>
#include <cstring>
#include <iostream>

#include "Compra.h"
#include "ProveedorArchivo.h"
#include "ProveedorManager.h"
#include "EmpleadoArchivo.h"
#include "rlutil.h"

using namespace std;

void Compra::copiarCadena(char* destino, const char* origen, int tamanio) {
     if (origen == NULL) {
        destino[0] = '\0';
        return;
        }

    strncpy(destino, origen, tamanio - 1);
    destino[tamanio - 1] = '\0';
}

Compra::Compra() {
    idProveedor = 0;
    idEmpleado = 0;
    fechaCompra = Fecha(1, 1, 2000);
    totalCompra = 0;
    eliminado = false;
}

bool Compra::Cargar() {
    ProveedorArchivo repoProv;
    EmpleadoArchivo repoEmp;
    string entrada;

    // Verificacion de proveedores ANTES de pedir cualquier dato
    int cantProvTotal = repoProv.getCantidadRegistros();
    bool hayProveedores = false;
    for (int i = 0; i < cantProvTotal; i++) {
        Proveedor p = repoProv.leer(i);
        if (!p.getEliminado()) {
            hayProveedores = true;
            break;
        }
    }

    if (!hayProveedores) {
        rlutil::setColor(rlutil::RED);
        cout << "No hay proveedores cargados. Debe registrar al menos un proveedor antes de cargar una compra.\n";
        rlutil::setColor(rlutil::WHITE);
        return false;
    }

    // Verificacion de empleados ANTES de pedir cualquier dato
    int cantEmpTotal = repoEmp.getCantidadRegistros();
    bool hayEmpleados = false;
    for (int i = 0; i < cantEmpTotal; i++) {
        Empleado e = repoEmp.leer(i);
        if (!e.getEliminado()) {
            hayEmpleados = true;
            break;
        }
    }

    if (!hayEmpleados) {
        rlutil::setColor(rlutil::RED);
        cout << "No hay empleados cargados. Debe registrar al menos un empleado antes de cargar una compra.\n";
        rlutil::setColor(rlutil::WHITE);
        return false;
    }

    while (true) {
        cout << "\nLISTADO DE PROVEEDORES:\n";
        int cantProv = repoProv.getCantidadRegistros();
        for (int i = 0; i < cantProv; i++) {
            Proveedor p = repoProv.leer(i);
            if (!p.getEliminado()) {
                cout << "ID: " << p.getIdProveedor()
                     << " - " << p.getNombre() << " " << endl;
            }
        }
        cout << "---------------------------\n" << endl;
        cout << "Ingrese ID proveedor: ";
        cin >> entrada;
        cin.ignore();

        if (entrada == "salir") return false;
        try {
            idProveedor = stoi(entrada);
        } catch (...) {
            rlutil::setColor(rlutil::RED);
            cout << "Error: ingrese un numero valido.\n";
            rlutil::setColor(rlutil::WHITE);
            continue;
        }

        if (repoProv.buscarPorId(idProveedor) == -1) {
            rlutil::setColor(rlutil::RED);
            cout << "Error: proveedor inexistente.\n";
            rlutil::setColor(rlutil::WHITE);
            continue;
        }
        break;
    }

    while (true) {
        cout << "\nID del empleado:\n";
        int cantEmp = repoEmp.getCantidadRegistros();
        for (int i = 0; i < cantEmp; i++) {
            Empleado e = repoEmp.leer(i);
            if (!e.getEliminado()) {
                cout << "ID: " << e.getIdEmpleado()
                     << " - " << e.getNombre() << " " << e.getApellido() << endl;
            }
        }
        cout << "---------------------------\n" << endl;
        cout << "Ingrese ID empleado (o 'salir'): ";
        cin >> entrada;
        cin.ignore();

        if (entrada == "salir") return false;
        try {
            idEmpleado = stoi(entrada);
        } catch (...) {
            rlutil::setColor(rlutil::RED);
            cout << "Error: ingrese un numero valido.\n";
            rlutil::setColor(rlutil::WHITE);
            continue;
        }

        if (repoEmp.buscarPorId(idEmpleado) == -1) {
            rlutil::setColor(rlutil::RED);
            cout << "Error: empleado inexistente.\n";
            rlutil::setColor(rlutil::WHITE);
            continue;
        }
        break;
    }

    cout << "Fecha de compra:\n";
    if (!fechaCompra.Cargar()) return false;

    eliminado = false;
    return true;
}

void Compra::Mostrar(bool mostrarEliminados) const {
    if (eliminado && !mostrarEliminados) return;

    ProveedorArchivo archivoProv;
    EmpleadoArchivo  archivoEmp;

    int posEmp = archivoEmp.buscarPorId(idEmpleado);
    int posProv = archivoProv.buscarPorId(idProveedor);

    cout << "---------------------------\n";
    cout << "ID Compra: " << idCompra << endl;

    if (posProv != -1) {
        Proveedor prov = archivoProv.leer(posProv);
        cout << "Proveedor ID: " << idProveedor
             << " - " << prov.getNombre() << endl;
    } else {
        cout << "Proveedor ID: " << idProveedor
             << " - No encontrado" << endl;
    }

    if (posEmp != -1) {
        Empleado emp = archivoEmp.leer(posEmp);
        cout << "Empleado ID: " << idEmpleado
             << " - " << emp.getNombre()
              << " " << emp.getApellido()<< endl;
    } else {
        cout << "Empleado ID: " << idEmpleado
             << " - No encontrado" << endl;
    }
    cout << "Fecha de compra: ";
    fechaCompra.Mostrar();
    cout << "\n";
    cout << "Total: $" << totalCompra << endl;
}

void Compra::MostrarPorEmpleado(bool mostrarEliminados) const {
    if (eliminado && !mostrarEliminados) return;

    ProveedorArchivo archivoProv;
    EmpleadoArchivo  archivoEmp;

    int posProv = archivoProv.buscarPorId(idProveedor);
    int posEmp = archivoEmp.buscarPorId(idEmpleado);

    cout << "---------------------------\n";
    cout << "ID Compra: " << idCompra << endl;

    if (posEmp != -1) {
        Empleado emp = archivoEmp.leer(posEmp);
        cout << "Empleado ID: " << idEmpleado
             << " - " << emp.getNombre()
              << " " << emp.getApellido()<< endl;
    } else {
        cout << "Empleado ID: " << idEmpleado
             << " - No encontrado" << endl;
    }

    if (posProv != -1) {
        Proveedor prov = archivoProv.leer(posProv);
        cout << "Proveedor ID: " << idProveedor
             << " - " << prov.getNombre() << endl;
    } else {
        cout << "Proveedor ID: " << idProveedor
             << " - No encontrado" << endl;
    }

    cout << "Fecha de compra: ";
    fechaCompra.Mostrar();
    cout << "\n";
    cout << "Total: $" << totalCompra << endl;
}

void Compra::MostrarPorProveedor(bool mostrarEliminados) const {
    if (eliminado && !mostrarEliminados) return;

    ProveedorArchivo archivoProv;
    EmpleadoArchivo  archivoEmp;

    int posProv = archivoProv.buscarPorId(idProveedor);
    int posEmp = archivoEmp.buscarPorId(idEmpleado);

    cout << "---------------------------\n";
    cout << "ID Compra: " << idCompra << endl;

    if (posProv != -1) {
        Proveedor prov = archivoProv.leer(posProv);
        cout << "Proveedor ID: " << idProveedor
             << " - " << prov.getNombre() << endl;
    } else {
        cout << "Proveedor ID: " << idProveedor
             << " - No encontrado" << endl;
    }

    if (posEmp != -1) {
        Empleado emp = archivoEmp.leer(posEmp);
        cout << "Empleado ID: " << idEmpleado
             << " - " << emp.getNombre()
              << " " << emp.getApellido()<< endl;
    } else {
        cout << "Empleado ID: " << idEmpleado
             << " - No encontrado" << endl;
    }
    cout << "Fecha de compra: ";
    fechaCompra.Mostrar();
    cout << "\n";
    cout << "Total: $" << totalCompra << endl;
}

void Compra::MostrarPorFecha(bool mostrarEliminados) const {
    if (eliminado && !mostrarEliminados) return;

    ProveedorArchivo archivoProv;
    EmpleadoArchivo  archivoEmp;

    int posProv = archivoProv.buscarPorId(idProveedor);
    int posEmp = archivoEmp.buscarPorId(idEmpleado);

    cout << "---------------------------\n";
    cout << "ID Compra: " << idCompra << endl;

    cout << "Fecha de compra: ";
    fechaCompra.Mostrar();
    cout << "\n";

    if (posProv != -1) {
        Proveedor prov = archivoProv.leer(posProv);
        cout << "Proveedor ID: " << idProveedor
             << " - " << prov.getNombre() << endl;
    } else {
        cout << "Proveedor ID: " << idProveedor
             << " - No encontrado" << endl;
    }

    if (posEmp != -1) {
        Empleado emp = archivoEmp.leer(posEmp);
        cout << "Empleado ID: " << idEmpleado
             << " - " << emp.getNombre()
              << " " << emp.getApellido()<< endl;
    } else {
        cout << "Empleado ID: " << idEmpleado
             << " - No encontrado" << endl;
    }
    cout << "Total: $" << totalCompra << endl;
}

int Compra::getIdCompra() const { return idCompra; }
int Compra::getIdProveedor() const { return idProveedor; }
int Compra::getIdEmpleado() const { return idEmpleado; }
Fecha Compra::getFechaCompra() const { return fechaCompra; }
float Compra::getTotalCompra() const { return totalCompra; }
bool Compra::getEliminado() const { return eliminado; }


void Compra::setIdCompra(int id) { idCompra = id; }
void Compra::setIdProveedor(int id) { idProveedor = id; }
void Compra::setIdEmpleado(int id) { idEmpleado = id; }
void Compra::setFechaCompra(const Fecha& f) { fechaCompra = f; }
void Compra::setTotalCompra(float t) { totalCompra = t; }
void Compra::setEliminado(bool e) { eliminado = e; }
