#include <cstring>
#include <iostream>
#include <limits>
#include "Producto.h"
#include "ProveedorArchivo.h"
#include "rlutil.h"

#include <iomanip>
#include <sstream>

using namespace std;

void Producto::copiarCadena(char* destino, const char* origen, int tamanio) {
    if (origen == NULL) {
        destino[0] = '\0';
        return;
    }

    strncpy(destino, origen, tamanio - 1);
    destino[tamanio - 1] = '\0';
}

Producto::Producto() {
    idProducto = 0;
    nombre[0] = '\0';
    descripcion[0] = '\0';
    tipo[0] = '\0';
    marca[0] = '\0';
    precio = 0;
    stock = 0;
    idProveedor = 0;
    eliminado = false;
}

bool Producto::Cargar() {

    ProveedorArchivo repoProv;
    int cantProv = repoProv.getCantidadRegistros();
    bool hayProveedores = false;

    for (int i = 0; i < cantProv; i++) {
        Proveedor p = repoProv.leer(i);
        if (!p.getEliminado()) {
            hayProveedores = true;
            break;
        }
    }

    if (!hayProveedores) {
        rlutil::setColor(rlutil::RED);
        cout << "No hay proveedores cargados. Debe registrar al menos un proveedor antes de cargar un producto.\n";
        rlutil::setColor(rlutil::WHITE);
        return false;
    }

    while (true) {
        cout << "Nombre: ";
        cin.getline(nombre, 30);
        if (strcmp(nombre, "salir") == 0) return false;

        bool ok = (nombre[0] != '\0');
        for (int i = 0; ok && nombre[i] != '\0'; ++i) {
            if (!((nombre[i] >= 'A' && nombre[i] <= 'Z') ||
                  (nombre[i] >= 'a' && nombre[i] <= 'z') ||
                  nombre[i] == ' ')) {
                ok = false;
            }
        }

        if (ok) break;

        rlutil::setColor(rlutil::RED);
        cout << "Error: el nombre debe contener solo letras.\n";
        rlutil::setColor(rlutil::WHITE);
    }

    cout << "Descripcion breve: ";
    cin.getline(descripcion, 100);
    if (strcmp(descripcion, "salir") == 0) return false;

    cout << "Marca: ";
    cin.getline(marca, 50);
    if (strcmp(marca, "salir") == 0) return false;

    while (true) {
            string modelo;
            cout << "Modelo (max. 5 caracteres): ";
            getline(cin, modelo);

            if (modelo == "salir") return false;

            bool valido = (!modelo.empty() && modelo.size() <= 5);
            for (char c : modelo) {
                if (!isalnum(c)) {
                    valido = false;
                    break;
                }
            }

            if (valido) {
                setTipo(modelo.c_str());
                break;
            }

            rlutil::setColor(rlutil::RED);
            cout << "Error: el modelo debe tener hasta 5 caracteres, solo letras o numeros.\n";
            rlutil::setColor(rlutil::WHITE);
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

    while (true) {
        char buffer[50];
        cout << "Stock : ";
        cin.getline(buffer, 50);
        if (strcmp(buffer, "salir") == 0) return false;

        stringstream ss(buffer);
        if (ss >> stock && stock > 0) break;

        rlutil::setColor(rlutil::RED);
        cout << "Error: el precio maximo debe ser mayor a 0.\n";
        rlutil::setColor(rlutil::WHITE);
    }


    while (true) {
        char buffer[50];

        cout << "\nLISTADO DE PROVEEDORES:\n";
        cout << "---------------------------\n";
        for (int i = 0; i < cantProv; i++) {
            Proveedor p = repoProv.leer(i);
            if (!p.getEliminado()) {
                cout << "ID: " << p.getIdProveedor() << " - " << p.getNombre() << "\n";
            }
        }
        cout << "---------------------------\n";

        cout << "ID proveedor (o 'salir'): ";
        cin.getline(buffer, 50);
        if (strcmp(buffer, "salir") == 0) return false;

        stringstream ss(buffer);
        if (!(ss >> idProveedor) || idProveedor <= 0) {
            rlutil::setColor(rlutil::RED);
            cout << "Error: el ID de proveedor debe ser numerico y mayor a 0.\n";
            rlutil::setColor(rlutil::WHITE);
            continue;
        }

        if (repoProv.buscarPorId(idProveedor) == -1) {
            rlutil::setColor(rlutil::RED);
            cout << "Error: no existe un proveedor activo con ese ID.\n";
            rlutil::setColor(rlutil::WHITE);
            continue;
        }

        break;
    }

    eliminado = false;
    return true;
}

void Producto::Mostrar(bool mostrarEliminados) const {
    if (eliminado && !mostrarEliminados) return;

    cout << "---------------------------\n";
    cout << "ID: " << idProducto << "\n";
    cout << "Nombre: " << nombre << "\n";
    cout << "Descripcion: " << descripcion << "\n";
    cout << "Marca: " << marca << "\n";
    cout << "Modelo: " << tipo << "\n";
    cout << "Precio: $" << fixed << setprecision(2) << precio << "\n";
    cout << "Stock: " << stock << "\n";
    cout << "ID Proveedor: " << idProveedor << "\n";
}

void Producto::MostrarProductoPorMarca (bool mostrarEliminados) const {
    if (eliminado && !mostrarEliminados) return;

    cout << "---------------------------\n";
    cout << "ID: " << idProducto << "\n";
    cout << "Marca: " << marca << "\n";
    cout << "Nombre: " << nombre << "\n";
    cout << "Descripcion: " << descripcion << "\n";
    cout << "Modelo: " << tipo << "\n";
    cout << "Precio: $" << fixed << setprecision(2) << precio << "\n";
    cout << "Stock: " << stock << "\n";
    cout << "ID Proveedor: " << idProveedor << "\n";
}



void Producto::MostrarProductoPorPrecio (bool mostrarEliminados) const {
    if (eliminado && !mostrarEliminados) return;

    cout << "---------------------------\n";
    cout << "ID: " << idProducto << "\n";
    cout << "Precio: $" << fixed << setprecision(2) << precio << "\n";
    cout << "Nombre: " << nombre << "\n";
    cout << "Descripcion: " << descripcion << "\n";
    cout << "Marca: " << marca << "\n";
    cout << "Modelo: " << tipo << "\n";
    cout << "Stock: " << stock << "\n";
    cout << "ID Proveedor: " << idProveedor << "\n";
}

void Producto::MostrarProductoPorStock(bool mostrarEliminados) const {
    if (eliminado && !mostrarEliminados) return;

    cout << "---------------------------\n";
    cout << "ID: " << idProducto << "\n";
    cout << "Stock: " << stock << "\n";
    cout << "Nombre: " << nombre << "\n";
    cout << "Descripcion: " << descripcion << "\n";
    cout << "Marca: " << marca << "\n";
    cout << "Modelo: " << tipo << "\n";
    cout << "Precio: $" << fixed << setprecision(2) << precio << "\n";
    cout << "ID Proveedor: " << idProveedor << "\n";
}


void Producto::setIdProducto(int id) { idProducto = id; }
void Producto::setNombre(const char* nuevoNombre) { copiarCadena(nombre, nuevoNombre, 50); }
void Producto::setDescripcion(const char* nuevaDescripcion) { copiarCadena(descripcion, nuevaDescripcion, 100); }
void Producto::setTipo(const char* nuevoTipo) { copiarCadena(tipo, nuevoTipo, 6); }
void Producto::setPrecio(float nuevoPrecio) { precio = nuevoPrecio; }
void Producto::setStock(int nuevoStock) { stock = nuevoStock; }
void Producto::setIdProveedor(int id) { idProveedor = id; }
void Producto::setEliminado(bool e) { eliminado = e; }
void Producto::setMarca(const char* nuevaMarca){copiarCadena(marca, nuevaMarca, 50); }

int Producto::getIdProducto() const { return idProducto; }
const char* Producto::getNombre() const { return nombre; }
const char* Producto::getDescripcion() const { return descripcion; }
const char* Producto::getTipo() const { return tipo; }
const char* Producto::getMarca() const { return marca; }
float Producto::getPrecio() const { return precio; }
int Producto::getStock() const { return stock; }
int Producto::getIdProveedor() const { return idProveedor; }
bool Producto::getEliminado() const { return eliminado; }
