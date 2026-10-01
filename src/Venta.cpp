#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include "Venta.h"
#include "ClienteArchivo.h"
#include "EmpleadoArchivo.h"
#include "rlutil.h"

using namespace std;

Venta::Venta() {
    idVenta = 0;
    idCliente = 0;
    idEmpleado = 0;
    fecha = Fecha(1, 1, 2000);
    total = 0;
    eliminado = false;
}

bool Venta::Cargar() {
    ClienteArchivo repoCliente;
    EmpleadoArchivo repoEmpleado;
    string entrada;

    cout << "Para cancelar, escribe 'salir' en cualquier momento.\n\n";

    while (true) {
        cout << "\nLISTADO DE CLIENTES:\n";
        int cantCli = repoCliente.getCantidadRegistros();
        for (int i = 0; i < cantCli; i++) {
            Cliente c = repoCliente.leer(i);
            if (!c.getEliminado()) {
                cout << "ID: " << c.getIdCliente() << " - "
                     << c.getNombre() << " " << c.getApellido() << "\n";
            }
        }
        cout << "---------------------------\n";
        cout << "Ingrese ID cliente: ";
        getline(cin, entrada);
        if (entrada == "salir") return false;

        try {
            idCliente = stoi(entrada);
        } catch (...) {
            rlutil::setColor(rlutil::RED);
            cout << "Error: ingrese un numero valido.\n";
            rlutil::setColor(rlutil::WHITE);
            continue;
        }

        if (repoCliente.buscarPorId(idCliente) == -1) {
            rlutil::setColor(rlutil::RED);
            cout << "Error: cliente inexistente.\n";
            rlutil::setColor(rlutil::WHITE);
            continue;
        }
        break;
    }

    while (true) {
        cout << "\nLISTADO DE EMPLEADOS:\n";
        int cantEmp = repoEmpleado.getCantidadRegistros();
        for (int i = 0; i < cantEmp; i++) {
            Empleado e = repoEmpleado.leer(i);
            if (!e.getEliminado()) {
                cout << "ID: " << e.getIdEmpleado() << " - "
                     << e.getNombre() << " " << e.getApellido() << "\n";
            }
        }
        cout << "---------------------------\n";
        cout << "Ingrese ID empleado: ";
        getline(cin, entrada);
        if (entrada == "salir") return false;

        try {
            idEmpleado = stoi(entrada);
        } catch (...) {
            rlutil::setColor(rlutil::RED);
            cout << "Error: ingrese un numero valido.\n";
            rlutil::setColor(rlutil::WHITE);
            continue;
        }

        if (repoEmpleado.buscarPorId(idEmpleado) == -1) {
            rlutil::setColor(rlutil::RED);
            cout << "Error: empleado inexistente.\n";
            rlutil::setColor(rlutil::WHITE);
            continue;
        }
        break;
    }

    cout << "\nFecha de la venta:\n";
    fecha.Cargar();

    total = 0;
    eliminado = false;
    return true;
}


void Venta::Mostrar(bool mostrarEliminados) const {
    if (eliminado && !mostrarEliminados) return;

    ClienteArchivo  archivoCli;
    EmpleadoArchivo  archivoEmp;

    int posCli = archivoCli.buscarPorId(idCliente);
    int posEmp = archivoEmp.buscarPorId(idEmpleado);

    cout << "---------------------------\n";
    cout << "ID Venta: " << idVenta << "\n";

     if (posCli != -1) {
        Cliente cli = archivoCli.leer(posCli);
        cout << "Cliente ID: " << idCliente
             << " - " << cli.getNombre()
             << " - " << cli.getApellido()
              << endl;
    } else {
        cout << "Cliente ID: " << idCliente
             << " - No encontrado" << endl;
    }

     if (posEmp != -1) {
        Empleado emp = archivoEmp.leer(posEmp);
        cout << "Empleado ID: " << idEmpleado
             << " - " << emp.getNombre()
             << " - " << emp.getApellido()
             << endl;
    } else {
        cout << "Empleado ID: " << idEmpleado
             << " - No encontrado" << endl;
    }

    cout << "Fecha: ";
    fecha.Mostrar();
    cout << "\n";
    cout << "Total: $" << total << "\n";
}

void Venta::MostrarPorFecha(bool mostrarEliminados) const {
    if (eliminado && !mostrarEliminados) return;

    ClienteArchivo  archivoCli;
    EmpleadoArchivo  archivoEmp;

    int posCli = archivoCli.buscarPorId(idCliente);
    int posEmp = archivoEmp.buscarPorId(idEmpleado);

    cout << "---------------------------\n";
    cout << "ID Venta: " << idVenta << "\n";

    cout << "Fecha: ";
    fecha.Mostrar();
    cout << "\n";

     if (posCli != -1) {
        Cliente cli = archivoCli.leer(posCli);
        cout << "Cliente ID: " << idCliente
             << " - " << cli.getNombre()
             << " - " << cli.getApellido()
             << endl;
    } else {
        cout << "Cliente ID: " << idCliente
             << " - No encontrado" << endl;
    }

     if (posEmp != -1) {
        Empleado emp = archivoEmp.leer(posEmp);
        cout << "Empleado ID: " << idEmpleado
             << " - " << emp.getNombre()
             << " - " << emp.getApellido()
             << endl;
    } else {
        cout << "Empleado ID: " << idEmpleado
             << " - No encontrado" << endl;
    }
    cout << "Total: $" << total << "\n";
}

void Venta::MostrarPorCliente(bool mostrarEliminados) const {
    if (eliminado && !mostrarEliminados) return;

    ClienteArchivo  archivoCli;
    EmpleadoArchivo  archivoEmp;

    int posCli = archivoCli.buscarPorId(idCliente);
    int posEmp = archivoEmp.buscarPorId(idEmpleado);

    cout << "---------------------------\n";
    cout << "ID Venta: " << idVenta << "\n";

     if (posCli != -1) {
        Cliente cli = archivoCli.leer(posCli);
        cout << "Cliente ID: " << idCliente
             << " - " << cli.getNombre()
             << " - " << cli.getApellido()
             << endl;
    } else {
        cout << "Cliente ID: " << idCliente
             << " - No encontrado" << endl;
    }

     if (posEmp != -1) {
        Empleado emp = archivoEmp.leer(posEmp);
        cout << "Empleado ID: " << idEmpleado
             << " - " << emp.getNombre()
             << " - " << emp.getApellido()
             << endl;
    } else {
        cout << "Empleado ID: " << idEmpleado
             << " - No encontrado" << endl;
    }
    cout << "Fecha: ";
    fecha.Mostrar();
    cout << "\n";
    cout << "Total: $" << total << "\n";
}

int Venta::getIdVenta() const { return idVenta; }
int Venta::getIdCliente() const { return idCliente; }
int Venta::getIdEmpleado() const { return idEmpleado; }
Fecha Venta::getFecha() const { return fecha; }
float Venta::getTotal() const { return total; }
bool Venta::getEliminado() const { return eliminado; }

void Venta::setIdVenta(int id) { idVenta = id; }
void Venta::setIdCliente(int id) { idCliente = id; }
void Venta::setIdEmpleado(int id) { idEmpleado = id; }
void Venta::setFecha(const Fecha& f) { fecha = f; }
void Venta::setTotal(float t) { total = t; }
void Venta::setEliminado(bool e) { eliminado = e; }
