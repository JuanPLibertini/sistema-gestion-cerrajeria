#include <cstring>
#include <iostream>
#include <string>
#include "VentaDetalle.h"
#include "ProductoArchivo.h"
#include "rlutil.h"

using namespace std;

VentaDetalle::VentaDetalle() {
    idVenta = 0;
    idProducto = 0;
    cantidad = 0;
    precioUnitario = 0;
    eliminado = false;
}

bool VentaDetalle::Cargar() {
    ProductoArchivo repoProducto;
    string entrada;
    int pos = -1;

    while (true) {
        cout << "\nLISTADO DE PRODUCTOS:\n";
        int cant = repoProducto.getCantidadRegistros();
        for (int i = 0; i < cant; i++) {
            Producto p = repoProducto.leer(i);
            if (!p.getEliminado()) {
                cout << "ID: " << p.getIdProducto() << " - " << p.getNombre()
                     << " (" << p.getMarca() << ") - Stock: " << p.getStock()
                     << " - $" << p.getPrecio() << "\n";
            }
        }
        cout << "---------------------------\n";
        cout << "Ingrese ID producto ('salir' para cancelar): ";
        getline(cin, entrada);
        if (entrada == "salir") return false;

        try {
            idProducto = stoi(entrada);
        } catch (...) {
            rlutil::setColor(rlutil::RED);
            cout << "Error: ingrese un numero valido.\n";
            rlutil::setColor(rlutil::WHITE);
            continue;
        }

        pos = repoProducto.buscarPorId(idProducto);
        if (pos == -1) {
            rlutil::setColor(rlutil::RED);
            cout << "Error: producto inexistente.\n";
            rlutil::setColor(rlutil::WHITE);
            continue;
        }
        break;
    }

    Producto prod = repoProducto.leer(pos);
    precioUnitario = prod.getPrecio();

    while (true) {
        cout << "Cantidad (stock disponible " << prod.getStock() << "): ";
        getline(cin, entrada);
        if (entrada == "salir") return false;

        try {
            cantidad = stoi(entrada);
        } catch (...) {
            rlutil::setColor(rlutil::RED);
            cout << "Error: ingrese un numero valido.\n";
            rlutil::setColor(rlutil::WHITE);
            continue;
        }

        if (cantidad <= 0 || cantidad > prod.getStock()) {
            rlutil::setColor(rlutil::RED);
            cout << "Error: cantidad invalida o supera el stock disponible.\n";
            rlutil::setColor(rlutil::WHITE);
            continue;
        }
        break;
    }

    eliminado = false;
    return true;
}

void VentaDetalle::Mostrar() const {
    if (eliminado) return;

    ProductoArchivo  archivoProd;

    int posProd = archivoProd.buscarPorId(idProducto);

    cout << "---------------------------\n";
    cout << "ID Venta: " << idVenta << "\n";

    if (posProd != -1) {
        Producto prod = archivoProd.leer(posProd);
        cout << "Producto ID: " << idProducto
              << " - " << prod.getNombre()
              << " - " << prod.getMarca()
              << " - " << prod.getTipo()
              << endl;
    } else {
        cout << "Producto ID: " << idProducto
             << " - No encontrado" << endl;
    }

    cout << "Cantidad: " << cantidad << "\n";
    cout << "Precio Unitario: $" << precioUnitario << "\n";
    cout << "Subtotal: $" << (precioUnitario * cantidad) << "\n";
}

int VentaDetalle::getIdVenta() const { return idVenta; }
int VentaDetalle::getIdProducto() const { return idProducto; }
int VentaDetalle::getCantidad() const { return cantidad; }
float VentaDetalle::getPrecioUnitario() const { return precioUnitario; }
bool VentaDetalle::getEliminado() const { return eliminado; }

void VentaDetalle::setIdVenta(int id) { idVenta = id; }
void VentaDetalle::setIdProducto(int id) { idProducto = id; }
void VentaDetalle::setCantidad(int c) { cantidad = c; }
void VentaDetalle::setPrecioUnitario(float p) { precioUnitario = p; }
void VentaDetalle::setEliminado(bool e) { eliminado = e; }
