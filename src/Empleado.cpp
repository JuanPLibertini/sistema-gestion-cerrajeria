#include <cstdio>
#include <cstring>
#include <iostream>
#include "Empleado.h"
#include "EmpleadoArchivo.h"
#include "rlutil.h"

using namespace std;

void Empleado::copiarCadena(char* destino, const char* origen, int tamanio) {
    if (origen == NULL) { destino[0] = '\0'; return; }
    strncpy(destino, origen, tamanio - 1);
    destino[tamanio - 1] = '\0';
}

Empleado::Empleado() {
    idEmpleado = 0;
    nombre[0] = '\0';
    apellido[0] = '\0';
    cargo[0] = '\0';
    sueldo = 0;
    fechaIngreso = Fecha(1, 1, 2000);
    eliminado = false;
}

bool Empleado::Cargar() {
     EmpleadoArchivo repo("empleados.dat");
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

        // Valida que nombre y apellido no sean iguales
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
            Empleado existente = repo.leer(i);
            if (!existente.getEliminado() &&
                strcasecmp(existente.getNombre(), nombre) == 0 &&
                strcasecmp(existente.getApellido(), apellido) == 0) {
                existe = true;
                break;
            }
        }

        if (existe) {
            rlutil::setColor(rlutil::RED);
            cout << "Error: ya existe un empleado con el mismo nombre y apellido.\n";
            rlutil::setColor(rlutil::WHITE);
            continue;
        }

        break;
    }

    while (true) {
                cout << "Cargo: ";
                cin.getline(cargo, 30);
                if (strcmp(cargo, "salir") == 0) return false;

                bool ok = (cargo[0] != '\0');
                for (int i = 0; ok && cargo[i] != '\0'; ++i) {
                    if (!((cargo[i] >= 'A' && cargo[i] <= 'Z') ||
                          (cargo[i] >= 'a' && cargo[i] <= 'z') ||
                          cargo[i] == ' ')) {
                        ok = false;
                    }
                }

                if (ok) break;

                rlutil::setColor(rlutil::RED);
                cout << "Error: el cargo debe contener solo letras.\n";
                rlutil::setColor(rlutil::WHITE);
            }

    while (true) {
        cout << "Sueldo (sin puntos): ";
        string entrada;
        getline(cin, entrada);

        if (entrada == "salir") return false;
     try {
            sueldo = stof(entrada);
        } catch (...) {
            rlutil::setColor(rlutil::RED);
            cout << "Error: ingrese un numero.\n";
            rlutil::setColor(rlutil::WHITE);
            continue;
        }

        if (sueldo <= 0) {
            rlutil::setColor(rlutil::RED);
            cout << "Error: el sueldo debe ser mayor a 0.\n";
            rlutil::setColor(rlutil::WHITE);
            continue;
        }
        break;
    }

    while (true) {
        cout << "Fecha de ingreso:\n";
        if (!fechaIngreso.Cargar()) return false;

        Fecha hoy;
        hoy.setCurrentDate();

        if (fechaIngreso > hoy) {
            rlutil::setColor(rlutil::RED);
            cout << "Error: la fecha de ingreso no puede ser futura.\n";
            rlutil::setColor(rlutil::WHITE);
            continue;
        }

        break;
    }



    eliminado = false;
    return true;
}

void Empleado::Mostrar(bool mostrarEliminados) const {
    if (eliminado && !mostrarEliminados) return;
    cout << "---------------------------\n";
    cout << "ID: " << idEmpleado << "\n";
    cout << "Nombre: " << nombre << "\n";
    cout << "Apellido: " << apellido << "\n";
    cout << "Cargo: " << cargo << "\n";
    cout << "Sueldo: $" << sueldo << "\n";
    cout << "Fecha ingreso: ";
    fechaIngreso.Mostrar();
    cout << "\n";
}


void Empleado::MostrarPorCargo() const {
    if (eliminado) return;
    cout << "---------------------------\n";
    cout << "ID: "       << idEmpleado << "\n";
    cout << "Cargo: "    << cargo      << "\n";
    cout << "Nombre: " << nombre   << "\n";
    cout << "Apellido: "   << apellido     << "\n";
    cout << "Sueldo: $"  << sueldo     << "\n";
    cout << "Fecha ingreso: ";
    fechaIngreso.Mostrar();
    cout << "\n";
}


void Empleado::MostrarPorApellido() const {
    if (eliminado) return;
    cout << "---------------------------\n";
    cout << "ID: "       << idEmpleado << "\n";
    cout << "Apellido: "   << apellido     << "\n";
    cout << "Nombre: " << nombre   << "\n";
    cout << "Cargo: "    << cargo      << "\n";
    cout << "Sueldo: $"  << sueldo     << "\n";
    cout << "Fecha ingreso: ";
    fechaIngreso.Mostrar();
    cout << "\n";
}



int Empleado::getIdEmpleado() const { return idEmpleado; }
const char* Empleado::getNombre() const { return nombre; }
const char* Empleado::getApellido() const { return apellido; }
const char* Empleado::getCargo() const { return cargo; }
float Empleado::getSueldo() const { return sueldo; }
Fecha Empleado::getFechaIngreso() const { return fechaIngreso; }
bool Empleado::getEliminado() const { return eliminado; }

void Empleado::setIdEmpleado(int id) { idEmpleado = id; }
void Empleado::setNombre(const char* n) { copiarCadena(nombre, n, 30); }
void Empleado::setApellido(const char* a) { copiarCadena(apellido, a, 30); }
void Empleado::setCargo(const char* c) { copiarCadena(cargo, c, 30); }
void Empleado::setSueldo(float s) { sueldo = s; }
void Empleado::setFechaIngreso(const Fecha& f) { fechaIngreso = f; }
void Empleado::setEliminado(bool e) { eliminado = e; }
