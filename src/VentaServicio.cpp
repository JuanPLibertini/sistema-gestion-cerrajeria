#include <cstring>
#include <iostream>
#include <string>
#include "VentaServicio.h"
#include "ServicioArchivo.h"
#include "ClienteArchivo.h"
#include "rlutil.h"

using namespace std;

VentaServicio::VentaServicio() {
    idVenta = 0;
    idCliente = 0;
    idServicio = 0;
    fecha = Fecha(1, 1, 2000);
    total = 0;
    eliminado = false;
}

bool VentaServicio::Cargar() {
    ServicioArchivo repoServicio;
    string entrada;
    int pos = -1;

    rlutil::cls();

    while (true) {
        cout << "\nLISTADO DE SERVICIOS:\n";
        int cant = repoServicio.getCantidadRegistros();
        for (int i = 0; i < cant; i++) {
            Servicio s = repoServicio.leer(i);
            if (!s.getEliminado()) {
                cout << "ID: " << s.getIdServicio()
                     << " - " << s.getDescripcion() << " " << endl;
            }
        }
        cout << "---------------------------\n";

        cout << "Ingrese ID servicio ('salir' para cancelar): ";
        getline(cin, entrada);
        if (entrada == "salir") return false;

        try {
            idServicio = stoi(entrada);
        } catch (...) {
            rlutil::setColor(rlutil::RED);
            cout << "Error: ingrese un numero valido.\n";
            rlutil::setColor(rlutil::WHITE);
            continue;
        }

        pos = repoServicio.buscarPorId(idServicio);
        if (pos == -1) {
            rlutil::setColor(rlutil::RED);
            cout << "Error: servicio inexistente.\n";
            rlutil::setColor(rlutil::WHITE);
            continue;
        }
        break;
    }

    Servicio serv = repoServicio.leer(pos);
    total = serv.getPrecio();

    eliminado = false;
    return true;
}

void VentaServicio::Mostrar() const {
    if (eliminado) return;
    ClienteArchivo  archivoCli;
    int posCli = archivoCli.buscarPorId(idCliente);

    ServicioArchivo  archivoServ;
    int posServ = archivoServ.buscarPorId(idServicio);


    cout << "---------------------------\n";
    cout << "ID Venta: " << idVenta << "\n";

     if (posCli != -1) {
        Cliente cli = archivoCli.leer(posCli);
        cout << "Cliente ID: " << idCliente
             << " - " << cli.getNombre()
             << " " << cli.getApellido()
             << endl;
    } else {
        cout << "Cliente ID: " << idCliente
             << " - No encontrado" << endl;
    }
    if (posServ != -1) {
        Servicio Serv = archivoServ.leer(posServ);
        cout << "Servicio ID: " << idServicio
             << " - " << Serv.getDescripcion()
             << endl;
    } else {
        cout << "Servicio ID: " << idCliente
             << " - No encontrado" << endl;
    }
    cout << "Fecha: ";
    fecha.Mostrar();
    cout << "\n";
    cout << "Total: $" << total << "\n";
}

int VentaServicio::getIdVenta() const { return idVenta; }
int VentaServicio::getIdCliente() const { return idCliente; }
int VentaServicio::getIdServicio() const { return idServicio; }
Fecha VentaServicio::getFecha() const { return fecha; }
float VentaServicio::getTotal() const { return total; }
bool VentaServicio::getEliminado() const { return eliminado; }

void VentaServicio::setIdVenta(int id) { idVenta = id; }
void VentaServicio::setIdCliente(int id) { idCliente = id; }
void VentaServicio::setIdServicio(int id) { idServicio = id; }
void VentaServicio::setFecha(const Fecha& f) { fecha = f; }
void VentaServicio::setTotal(float t) { total = t; }
void VentaServicio::setEliminado(bool e) { eliminado = e; }

