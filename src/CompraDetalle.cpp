#include <cstring>
#include <iostream>
#include <string>
#include "CompraDetalle.h"
#include "ProductoArchivo.h"
#include "rlutil.h"

using namespace std;

CompraDetalle::CompraDetalle() {
    idCompra = 0;
    idProducto = 0;
    cantidad = 0;
    precioUnitario = 0;
    eliminado = false;
}

bool CompraDetalle::Cargar() {
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
                     << " (" << p.getMarca() << ") - Stock actual: " << p.getStock()
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
        cout << "Cantidad a comprar ('salir' para cancelar): ";
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

        if (cantidad <= 0) {
            rlutil::setColor(rlutil::RED);
            cout << "Error: la cantidad debe ser mayor a 0.\n";
            rlutil::setColor(rlutil::WHITE);
            continue;
        }
        break;
    }

    eliminado = false;
    return true;
}

void CompraDetalle::Mostrar() const {
    if (eliminado) return;

    ProductoArchivo  archivoProd;
    int posProd = archivoProd.buscarPorId(idProducto);

    cout << "============================\n";
    cout << "ID Compra: " << idCompra << "\n";

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


int CompraDetalle::getIdCompra() const { return idCompra; }
int CompraDetalle::getIdProducto() const { return idProducto; }
int CompraDetalle::getCantidad() const { return cantidad; }
float CompraDetalle::getPrecioUnitario() const { return precioUnitario; }
bool CompraDetalle::getEliminado() const { return eliminado; }

void CompraDetalle::setIdCompra(int id) { idCompra = id; }
void CompraDetalle::setIdProducto(int id) { idProducto = id; }
void CompraDetalle::setCantidad(int c) { cantidad = c; }
void CompraDetalle::setPrecioUnitario(float p) { precioUnitario = p; }
void CompraDetalle::setEliminado(bool e) { eliminado = e; }
