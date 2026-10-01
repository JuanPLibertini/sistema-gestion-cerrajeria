#include <iostream>
#include <cstring>
#include <cstdio>
#include "Proveedor.h"
#include "ProveedorArchivo.h"
#include "rlutil.h"

using namespace std;

void Proveedor::copiarCadena(char* destino, const char* origen, int tamanio) {
      if (origen == NULL) {
        destino[0] = '\0';
        return;
    }
    strncpy(destino, origen, tamanio - 1);
    destino[tamanio - 1] = '\0';
}

Proveedor::Proveedor() {
    idProveedor = 0;
    nombre[0] = '\0';
    telefono[0] = '\0';
    direccion[0] = '\0';
    email[0] = '\0';
    eliminado = false;
}

bool Proveedor::Cargar() {
    ProveedorArchivo repo("proveedores.dat");

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

        int cantidad = repo.getCantidadRegistros();
        bool existe = false;
        for (int i = 0; i < cantidad; i++) {
            Proveedor existente = repo.leer(i);
            if (!existente.getEliminado() &&
                strcasecmp(existente.getNombre(), nombre) == 0) {
                existe = true;
                break;
            }
        }

        if (!ok) {
            rlutil::setColor(rlutil::RED);
            cout << "Error: el nombre debe contener solo letras.\n";
            rlutil::setColor(rlutil::WHITE);
            continue;
        }

        if (existe) {
            rlutil::setColor(rlutil::RED);
            cout << "Error: ya existe un proveedor con ese nombre. Ingrese otro.\n";
            rlutil::setColor(rlutil::WHITE);
            continue;
        }

        break;
    }


while (true) {
    cout << "Telefono (entre 8 a 10 digitos): ";
    cin.getline(telefono, 20);
    if (strcmp(telefono, "salir") == 0) return false;

    bool ok = strlen(telefono) >= 8 && strlen(telefono) <= 10;
    for (int i = 0; ok && telefono[i] != '\0'; ++i) {
        if (!isdigit(telefono[i])) ok = false;
    }

    if (ok) break;

    rlutil::setColor(rlutil::RED);
    cout << "Error: el telefono debe contener solo numeros (8 a 10 digitos).\n";
    rlutil::setColor(rlutil::WHITE);
    }

    while (true) {
    cout << "Direccion (ej: Av. Cabildo 123): ";
    cin.getline(direccion, 100);
    if (strcmp(direccion, "salir") == 0) return false;

    bool ok = false;
    int len = strlen(direccion);

    char* espacio = strrchr(direccion, ' ');
    if (espacio != NULL && *(espacio + 1) != '\0') {
        ok = true;
        for (char* p = espacio + 1; *p != '\0'; ++p) {
            if (!isdigit(*p)) {
                ok = false;
                break;
                }
            }
        }

    if (ok) break;

    rlutil::setColor(rlutil::RED);
    cout << "Error: la direccion debe terminar con un numero separado por espacio (ej: Av. San Martin 456).\n";
    rlutil::setColor(rlutil::WHITE);
    }

   while (true) {
        cout << "Email (ej: usuario@dominio.com): ";
        cin.getline(email, 50);
        if (strcmp(email, "salir") == 0) return false;

        bool tieneArroba = false;
        for (int i = 0; email[i] != '\0'; ++i) {
            if (email[i] == '@') {
                tieneArroba = true;
                break;
            }
        }

        if (tieneArroba) break;

        rlutil::setColor(rlutil::RED);
        cout << "Error: el email debe contener un @ (ej: usuario@dominio.com).\n";
        rlutil::setColor(rlutil::WHITE);
    }

    eliminado = false;
    return true;
}

void Proveedor::Mostrar(bool mostrarEliminados) const {
    if (eliminado && !mostrarEliminados) return;
    cout << "---------------------------\n";
    cout << "ID: " << idProveedor << "\n";
    cout << "Nombre: " << nombre << "\n";
    cout << "Telefono: " << telefono << "\n";
    cout << "Direccion: " << direccion << "\n";
    cout << "Email: " << email << "\n";
}

int Proveedor::getIdProveedor() const { return idProveedor; }
const char* Proveedor::getNombre() const { return nombre; }
const char* Proveedor::getTelefono() const { return telefono; }
const char* Proveedor::getDireccion() const { return direccion; }
const char* Proveedor::getEmail() const { return email; }
bool Proveedor::getEliminado() const { return eliminado; }

void Proveedor::setIdProveedor(int id) { idProveedor = id; }
void Proveedor::setNombre(const char* n) { copiarCadena(nombre, n, 50); }
void Proveedor::setTelefono(const char* t) { copiarCadena(telefono, t, 20); }
void Proveedor::setDireccion(const char* d) { copiarCadena(direccion, d, 100); }
void Proveedor::setEmail(const char* e) { copiarCadena(email, e, 50); }
void Proveedor::setEliminado(bool estado) { eliminado = estado; }
