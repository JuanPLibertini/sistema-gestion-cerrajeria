#include "Servicio.h"
#include "ProductoArchivo.h"
#include "EmpleadoArchivo.h"
#include "rlutil.h"

#include <sstream>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

void Servicio::copiarCadena(char* destino, const char* origen, int tamanio) {
    if (origen == NULL) { destino[0] = '\0'; return; }
    strncpy(destino, origen, tamanio - 1);
    destino[tamanio - 1] = '\0';
}

Servicio::Servicio() {
    idServicio = 0;
    idProducto = 0;
    fecha = Fecha(1,1,2000);
    descripcion[0] = '\0';
    tipo = 0;
    precio = 0;
    eliminado = false;
}

bool Servicio::Cargar() {
    ProductoArchivo repoProd;
    string entrada;
    int idProd;

        while (true) {
            cout << "\n--- LISTADO DE PRODUCTOS ---\n";
            int cantProd = repoProd.getCantidadRegistros();
            for (int i = 0; i < cantProd; i++) {
                Producto p = repoProd.leer(i);
                if (!p.getEliminado()) {
                    cout << "ID: " << p.getIdProducto()
                         << " - " << p.getDescripcion()
                         << " - " << p.getMarca()
                         << " - " << p.getTipo() << endl;
                }
            }
            cout << "-----------------------------\n";

            cout << "Ingrese ID producto (0=No Aplica, ej: Apertura de Caja fuerte): ";
            string entrada;
            getline(cin, entrada);

            if (entrada == "salir"){
                rlutil::setColor(rlutil::RED);
                cout << "OPERACION CANCELADA.\n";
                rlutil::setColor(rlutil::WHITE);
                return false;
            }

            if (entrada == "0") {
                idProducto = 0;
                break;
            }

            // Valida que sea un número
            bool esNum = all_of(entrada.begin(), entrada.end(), ::isdigit);
            if (!esNum) {
                rlutil::setColor(rlutil::RED);
                cout << "Error: debe ingresar un numero valido.\n";
                rlutil::setColor(rlutil::WHITE);
                continue;
            }

            int idProd = stoi(entrada);
            int posProd = repoProd.buscarPorId(idProd);
            if (posProd == -1) {
                rlutil::setColor(rlutil::RED);
                cout << "Error: producto inexistente.\n";
                rlutil::setColor(rlutil::WHITE);
                continue;
            }

            Producto p = repoProd.leer(posProd);
            if (p.getEliminado()) {
                rlutil::setColor(rlutil::RED);
                cout << "Error: producto dado de baja.\n";
                rlutil::setColor(rlutil::WHITE);
                continue;
            }

            idProducto = idProd;
            break;
        }


    cout << "Fecha del servicio:\n";
    if (!fecha.Cargar()) return false;


    cout << "Descripcion breve: ";
    cin.getline(descripcion, 100);
    if (strcmp(descripcion, "salir") == 0) return false;


    while (true) {
    cout << "Ingrese tipo (1=Local,2=Calle,0=Cancelar): ";
    int t;
    if (!(cin >> t)) {
        cin.clear();
        cin.ignore(1000,'\n');
        rlutil::setColor(rlutil::RED);
        cout << "Error: debe ingresar un numero.\n";
        rlutil::setColor(rlutil::WHITE);
        continue;
    }
    cin.ignore(1000,'\n');

    if (t == 0) return false;
    if (t != 1 && t != 2) {
        rlutil::setColor(rlutil::RED);
        cout << "Error: solo se acepta 1 (Local) o 2 (Calle).\n";
        rlutil::setColor(rlutil::WHITE);
        continue;
    }

    // Se asigna el atributo de la clase
    this->tipo = t;
    break;
}


    while (true) {
        char buffer[50];
        cout << "Precio (sin punto ni coma): ";
        cin.getline(buffer, 50);

        if (strcmp(buffer, "salir") == 0)
            return false;

        stringstream ss(buffer);

        if (!(ss >> precio) || !ss.eof()) {
            rlutil::setColor(rlutil::RED);
            cout << "Error: el precio debe ser un numero.\n";
            rlutil::setColor(rlutil::WHITE);
            continue;
        }

        if (precio <= 0) {
            rlutil::setColor(rlutil::RED);
            cout << "Error: el precio debe ser mayor a 0.\n";
            rlutil::setColor(rlutil::WHITE);
            continue;
        }

        break;
    }

    eliminado = false;
    return true;
}

void Servicio::Mostrar(bool mostrarEliminados) const {
    if (eliminado && !mostrarEliminados) return;
    ProductoArchivo  archivoProd;
    int posProd = archivoProd.buscarPorId(idProducto);




    cout << "---------------------------\n";
    cout << "ID Servicio: " << idServicio << "\n";
    if (idProducto == 0) {
        cout << "Producto: NULL\n";
    }

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



    cout << "Fecha: ";
    fecha.Mostrar();
    cout << "\n";
    cout << "Descripcion: " << descripcion << "\n";

    cout << "Tipo: " << tipo;
    switch (tipo) {
        case 1: cout << " - Local\n"; break;
        case 2: cout << " - Calle\n"; break;
        default: cout << " - Desconocido\n"; break;
    }

    cout << "Precio: $" << precio << "\n";
}


void Servicio::MostrarPorDescripcion() const {
    ProductoArchivo  archivoProd;
    int posProd = archivoProd.buscarPorId(idProducto);
    cout << "---------------------------\n";
    cout << "ID Servicio: " << idServicio << "\n";
    cout << "Descripcion: " << descripcion << "\n";
    if (idProducto == 0) {
        cout << "Producto: NULL\n";
    }
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

    cout << "Fecha: ";
    fecha.Mostrar();
    cout << "\n";
    cout << "Tipo: " << tipo;
    switch (tipo) {
        case 1: cout << " - Local\n"; break;
        case 2: cout << " - Calle\n"; break;
        default: cout << " - Desconocido\n"; break;
    }

    cout << "Precio: $" << precio << "\n";
}



void Servicio::MostrarPorTipo() const {
    ProductoArchivo  archivoProd;
    int posProd = archivoProd.buscarPorId(idProducto);
        cout << "---------------------------\n";
    cout << "ID Servicio: " << idServicio << "\n";
    cout << "Tipo: " << tipo;
    switch (tipo) {
        case 1: cout << " - Local\n"; break;
        case 2: cout << " - Calle\n"; break;
        default: cout << " - Desconocido\n"; break;
    }
        if (idProducto == 0) {
        cout << "Producto: NULL\n";
    }
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
    cout << "Fecha: ";
    fecha.Mostrar();
    cout << "\n";
    cout << "Descripcion: " << descripcion << "\n";
    cout << "Precio: $" << precio << "\n";
}

void Servicio::MostrarPorPrecio() const {
    ProductoArchivo  archivoProd;
    int posProd = archivoProd.buscarPorId(idProducto);
    cout << "---------------------------\n";
    cout << "ID Servicio: " << idServicio << "\n";
    cout << "Precio: $" << precio << "\n";
        if (idProducto == 0) {
        cout << "Producto: NULL\n";
    }
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
    cout << "Fecha: ";
    fecha.Mostrar();
    cout << "\n";
    cout << "Descripcion: " << descripcion << "\n";
    cout << "Tipo: " << tipo;
    switch (tipo) {
        case 1: cout << " - Local\n"; break;
        case 2: cout << " - Calle\n"; break;
        default: cout << " - Desconocido\n"; break;
    }
}


int Servicio::getIdServicio() const { return idServicio; }
int Servicio::getIdProducto() const { return idProducto; }
Fecha Servicio::getFecha() const { return fecha; }
const char* Servicio::getDescripcion() const { return descripcion; }
int Servicio::getTipo() const { return tipo; }
int Servicio::getPrecio() const { return precio; }
bool Servicio::getEliminado() const { return eliminado; }


void Servicio::setIdServicio(int id) { idServicio = id; }
void Servicio::setIdProducto(int id) { idProducto = id; }
void Servicio::setFecha(const Fecha& f) { fecha = f; }
void Servicio::setDescripcion(const char* d) { copiarCadena(descripcion, d, 100); }
void Servicio::setTipo(int t) { tipo = t; }
void Servicio::setPrecio(int p) { precio = p; }
void Servicio::setEliminado(bool e) { eliminado = e; }
