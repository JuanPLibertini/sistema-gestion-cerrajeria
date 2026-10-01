#include <cstdio>
#include <cstring>
#include <iostream>
#include "Cliente.h"
#include "ClienteArchivo.h"

#include "rlutil.h"

using namespace std;

void Cliente::copiarCadena(char* destino, const char* origen, int tamanio) {
    if (origen == NULL) {
        destino[0] = '\0';
        return;
    }

    strncpy(destino, origen, tamanio - 1);
    destino[tamanio - 1] = '\0';
}

Cliente::Cliente() {
    idCliente = 0;
    nombre[0] = '\0';
    apellido[0] = '\0';
    telefono[0] = '\0';
    direccion[0] = '\0';
    email[0] = '\0';
    eliminado = false;
}

bool Cliente::Cargar() {
        ClienteArchivo repo("clientes.dat");

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


   while (true) {
        cout << "Apellido: ";
        cin.getline(apellido, 30);
        if (strcmp(apellido, "salir") == 0) return false;

        bool ok = (apellido[0] != '\0');
        for (int i = 0; ok && apellido[i] != '\0'; ++i) {
            if (!isalpha(apellido[i]) && apellido[i] != ' ') ok = false;
        }

        if (!ok) {
            rlutil::setColor(rlutil::RED);
            cout << "Error: el apellido debe contener solo letras.\n";
            rlutil::setColor(rlutil::WHITE);
            continue;
        }

        //  Valida que nombre y apellido no sean iguales
        if (strcasecmp(nombre, apellido) == 0) {
            rlutil::setColor(rlutil::RED);
            cout << "Error: el nombre y el apellido no pueden ser iguales.\n";
            rlutil::setColor(rlutil::WHITE);
            continue;
        }

        // Valida duplicado nombre+apellido
        int cantidad = repo.getCantidadRegistros();
        bool existe = false;
        for (int i = 0; i < cantidad; i++) {
            Cliente existente = repo.leer(i);
            if (!existente.getEliminado() &&
                strcasecmp(existente.getNombre(), nombre) == 0 &&
                strcasecmp(existente.getApellido(), apellido) == 0) {
                existe = true;
                break;
            }
        }

        if (existe) {
            rlutil::setColor(rlutil::RED);
            cout << "Error: ya existe un cliente con el mismo nombre y apellido.\n";
            rlutil::setColor(rlutil::WHITE);
            continue;
        }
        break;
        }
            while (true) {
            cout << "Telefono (solo numeros entre 8 a 10 digitos): ";
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
            cout << "Direccion (ej: Av. San Martin 456): ";
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

void Cliente::Mostrar(bool mostrarEliminados) const {
    if (eliminado && !mostrarEliminados) return;

    cout << "---------------------------\n";
    cout << "ID: " << idCliente << "\n";
    cout << "Nombre: " << nombre << "\n";
    cout << "Apellido: " << apellido << "\n";
    cout << "Telefono: " << telefono << "\n";
    cout << "Direccion: " << direccion << "\n";
    cout << "Email: " << email << "\n";
}

void Cliente::MostrarPorNombre() const {
    if (eliminado) return;

    cout << "---------------------------\n";
    cout << "ID: " << idCliente << "\n";
    cout << "Nombre: " << nombre << "\n";
    cout << "Apellido: " << apellido << "\n";
    cout << "Telefono: " << telefono << "\n";
    cout << "Direccion: " << direccion << "\n";
    cout << "Email: " << email << "\n";
}

void Cliente::MostrarPorApellido() const {
    if (eliminado) return;

    cout << "---------------------------\n";
    cout << "ID: " << idCliente << "\n";
    cout << "Apellido: " << apellido << "\n";
    cout << "Nombre: " << nombre << "\n";
    cout << "Telefono: " << telefono << "\n";
    cout << "Direccion: " << direccion << "\n";
    cout << "Email: " << email << "\n";
}

void Cliente::setIdCliente(int id) { idCliente = id; }
void Cliente::setNombre(const char* nuevoNombre) { copiarCadena(nombre, nuevoNombre, 30); }
void Cliente::setApellido(const char* nuevoApellido) { copiarCadena(apellido, nuevoApellido, 30); }
void Cliente::setTelefono(const char* nuevoTelefono) { copiarCadena(telefono, nuevoTelefono, 20); }
void Cliente::setDireccion(const char* nuevaDireccion) { copiarCadena(direccion, nuevaDireccion, 100); }
void Cliente::setEmail(const char* nuevoEmail) { copiarCadena(email, nuevoEmail, 50); }
void Cliente::setEliminado(bool e) { eliminado = e; }

int Cliente::getIdCliente() const { return idCliente; }
const char* Cliente::getNombre() const { return nombre; }
const char* Cliente::getApellido() const { return apellido; }
const char* Cliente::getTelefono() const { return telefono; }
const char* Cliente::getDireccion() const { return direccion; }
const char* Cliente::getEmail() const { return email; }
bool Cliente::getEliminado() const { return eliminado; }
