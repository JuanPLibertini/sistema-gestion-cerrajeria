#include <iostream>
#include "EmpleadoManager.h"
#include "rlutil.h"
#include "MenuEmpleado.h"
#include "Utilidades.h"

using namespace std;


EmpleadoManager::EmpleadoManager() {}
void pausa();
void limpiarEntrada();

void EmpleadoManager::altaEmpleado() {
        Empleado reg;
        int nuevoId = _repo.obtenerProximoId();

        cout << "\nALTA DE EMPLEADO\n";
        cout << "---------------------------\n";
        rlutil::setColor(rlutil::YELLOW);
        cout << "Para cancelar, escribe 'salir' en cualquier momento.\n\n";
        rlutil::setColor(rlutil::WHITE);
        cout << "ID del empleado a dar de alta: " << nuevoId << "\n";
        reg.setIdEmpleado(nuevoId);

        if (!reg.Cargar()) {
            rlutil::setColor(rlutil::RED);
            cout << "OPERACION CANCELADA.\n";
            rlutil::setColor(rlutil::WHITE);
            return;
        }

        if (_repo.guardar(reg)) {
            rlutil::setColor(rlutil::GREEN);
            cout << "EMPLEADO GUARDADO EN ARCHIVO!!!\n";;
            rlutil::setColor(rlutil::WHITE);
        } else {
            rlutil::setColor(rlutil::RED);
            cout << "Error al guardar.\n";
            rlutil::setColor(rlutil::WHITE);
        }

}

bool EmpleadoManager::listarEmpleados() {
        int cantidad = _repo.getCantidadRegistros();
        bool hayActivos = false;

        for (int i=0; i<cantidad; i++) {
            Empleado reg = _repo.leer(i);
            if (!reg.getEliminado()) {
                if (!hayActivos) {
                    cout << "LISTADO DE EMPLEADOS:\n";
                    hayActivos = true;
                }
                reg.Mostrar();
            }
        }

        if (!hayActivos) {
            rlutil::setColor(rlutil::RED);
            cout << "NO HAY EMPLEADOS CARGADOS.\n";
            rlutil::setColor(rlutil::WHITE);
            return false;
        }
        return true;
}

bool EmpleadoManager::bajaEmpleado(int id) {
    if (id <= 0) return false;
    int pos = _repo.buscarPorId(id);
    if (pos == -1) return false;
        Empleado reg = _repo.leer(pos);
    if (reg.getEliminado()) return false;
    reg.setEliminado(true);
    return _repo.modificar(reg, pos);
}


bool EmpleadoManager::reactivarEmpleado(int id) {
    if (id <= 0) return false;
    int pos = _repo.buscarPorId(id, true);
    if (pos == -1) return false;
    Empleado reg = _repo.leer(pos);
    if (!reg.getEliminado()) return false;
    reg.setEliminado(false);
    return _repo.modificar(reg, pos);
}

bool EmpleadoManager::existeEmpleado(int id) {
        int pos = _repo.buscarPorId(id);
        return pos != -1;
}

void EmpleadoManager::modificarEmpleado() {
    if (!listarEmpleados()) return;

    int id, pos;
    while (true) {
        cout << "\nIngrese ID del empleado a modificar (0 para salir): ";
        cin >> id;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            rlutil::setColor(rlutil::RED);
            cout << "Error: Entrada invalida. Debe ingresar un numero entero positivo.\n";
            rlutil::setColor(rlutil::WHITE);
            continue;
        }
        cin.ignore(1000, '\n');

        if (id == 0) {
            rlutil::setColor(rlutil::RED);
            cout << "OPERACION CANCELADA.\n";
            rlutil::setColor(rlutil::WHITE);
            return;
        }
        if (id < 0) {
            rlutil::setColor(rlutil::RED);
            cout << "Error: El ID no puede ser negativo.\n";
            rlutil::setColor(rlutil::WHITE);
            continue;
        }

        pos = _repo.buscarPorId(id);
        if (pos == -1) {
            rlutil::setColor(rlutil::RED);
            cout << "Error: Empleado no encontrado.\n";
            rlutil::setColor(rlutil::WHITE);
            continue;
        }
        break;
    }

    Empleado reg = _repo.leer(pos);
    int opcion;
    string entrada;

    do {
        rlutil::cls();
        cout << "\n--- MODIFICAR EMPLEADO ID " << id << " ---\n";
        cout << "1) Nombre     [" << reg.getNombre()  << "]\n";
        cout << "2) Apellido   [" << reg.getApellido() << "]\n";
        cout << "3) Cargo      [" << reg.getCargo()    << "]\n";
        cout << "4) Sueldo     [" << reg.getSueldo()   << "]\n";
        cout << "5) Fecha Ing. [";
        reg.getFechaIngreso().Mostrar();
        cout << "]\n";
        cout << "6) Guardar cambios\n";
        cout << "0) Cancelar\n";
        cout << "Opcion: ";
        opcion = leerOpcion();

        switch (opcion) {
            case 1: {
                while (true) {
                    cout << "Nuevo nombre: ";
                    getline(cin, entrada);
                    if (entrada == "salir") return;

                    bool ok = !entrada.empty();
                    for (char c : entrada) {
                        if (!isalpha(c) && c != ' ') { ok = false; break; }
                    }

                    if (!ok) {
                        rlutil::setColor(rlutil::RED);
                        cout << "Error: el nombre debe contener solo letras.\n";
                        rlutil::setColor(rlutil::WHITE);
                        continue;
                    }

                    reg.setNombre(entrada.c_str());
                    break;
                }
                break;
            }
            case 2: {
                while (true) {
                    cout << "Nuevo apellido: ";
                    getline(cin, entrada);
                    if (entrada == "salir") return;

                    bool ok = !entrada.empty();
                    for (char c : entrada) {
                        if (!isalpha(c) && c != ' ') { ok = false; break; }
                    }

                    if (!ok) {
                        rlutil::setColor(rlutil::RED);
                        cout << "Error: el apellido debe contener solo letras.\n";
                        rlutil::setColor(rlutil::WHITE);
                        continue;
                    }

                     if (strcasecmp(reg.getNombre(), entrada.c_str()) == 0) {
                        rlutil::setColor(rlutil::RED);
                        cout << "Error: el nombre y el apellido no pueden ser iguales.\n";
                        rlutil::setColor(rlutil::WHITE);
                        continue;
                    }

                    // Valida duplicado nombre+apellido
                    int cantidad = _repo.getCantidadRegistros();
                    bool existe = false;
                    for (int i = 0; i < cantidad; i++) {
                        Empleado existente = _repo.leer(i);
                        if (!existente.getEliminado() &&
                            existente.getIdEmpleado() != reg.getIdEmpleado() &&
                            strcasecmp(existente.getNombre(), reg.getNombre()) == 0 &&
                            strcasecmp(existente.getApellido(), entrada.c_str()) == 0) {
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

                    reg.setApellido(entrada.c_str());
                    break;
                }
                break;
            }
            case 3: {
                while (true) {
                    cout << "Nuevo cargo: ";
                    getline(cin, entrada);
                    if (entrada == "salir") return;

                    bool ok = !entrada.empty();
                    for (char c : entrada) {
                        if (!isalpha(c) && c != ' ') { ok = false; break; }
                    }

                    if (!ok) {
                        rlutil::setColor(rlutil::RED);
                        cout << "Error: el cargo debe contener solo letras.\n";
                        rlutil::setColor(rlutil::WHITE);
                        continue;
                    }

                    reg.setCargo(entrada.c_str());
                    break;
                }
                break;
            }
            case 4: {
                while (true) {
                    cout << "Nuevo sueldo (sin puntos): ";
                    getline(cin, entrada);
                    if (entrada == "salir") return;

                    float nuevoSueldo;
                    try {
                        nuevoSueldo = stof(entrada);
                    } catch (...) {
                        rlutil::setColor(rlutil::RED);
                        cout << "Error: ingrese un numero valido.\n";
                        rlutil::setColor(rlutil::WHITE);
                        continue;
                    }

                    if (nuevoSueldo <= 0) {
                        rlutil::setColor(rlutil::RED);
                        cout << "Error: el sueldo debe ser mayor a 0.\n";
                        rlutil::setColor(rlutil::WHITE);
                        continue;
                    }

                    reg.setSueldo(nuevoSueldo);
                    break;
                }
                break;
            }
            case 5: {
                Fecha nuevaFecha;
                cout << "Nueva fecha de ingreso:\n";
                if (nuevaFecha.Cargar()) {
                    reg.setFechaIngreso(nuevaFecha);
                }
                break;
            }
            case 6:
                if (_repo.modificar(reg, pos)) {
                    rlutil::setColor(rlutil::GREEN);
                    cout << "EMPLEADO MODIFICADO CORRECTAMENTE.\n";
                    rlutil::setColor(rlutil::WHITE);
                } else {
                    rlutil::setColor(rlutil::RED);
                    cout << "Error al guardar.\n";
                    rlutil::setColor(rlutil::WHITE);
                }
                return;
            case 0:
                rlutil::setColor(rlutil::RED);
                cout << "MODIFICACION CANCELADA.\n";
                rlutil::setColor(rlutil::WHITE);
                return;
            default:
                rlutil::setColor(rlutil::RED);
                cout << "OPCION INVALIDA. INTENTE NUEVAMENTE.\n";
                rlutil::setColor(rlutil::WHITE);
                pausa();
                break;
        }
    } while (true);
}


void EmpleadoManager::listarEmpleadoPorApellido() {
        int cantidad = _repo.getCantidadRegistros();
        Empleado temp[500];
        int activos=0;

        for (int i=0; i<cantidad; i++) {
            Empleado reg = _repo.leer(i);
            if (!reg.getEliminado()) {
             temp[activos++] = reg;
            }
        }

        if (activos == 0) {
            rlutil::setColor(rlutil::RED);
            cout << "NO HAY EMPLEADOS CARGADOS.\n";
            rlutil::setColor(rlutil::WHITE);
            return;
        }

        for (int i = 0; i < activos - 1; i++) {
            for (int j = 0; j < activos - i - 1; j++) {
                if (strcmp(temp[j].getApellido(), temp[j+1].getApellido()) > 0) {
                    Empleado aux = temp[j];
                    temp[j] = temp[j+1];
                    temp[j+1] = aux;
                }
            }
        }

        cout << "LISTADO DE EMPLEADOS (por apellido):\n";
        for (int i=0; i<activos; i++) {
            temp[i].MostrarPorApellido();
        }
    }

void EmpleadoManager::listarEmpleadoPorCargo() {
        int cantidad = _repo.getCantidadRegistros();
        Empleado temp[500];
        int activos = 0;

        for (int i = 0; i < cantidad; i++) {
            Empleado reg = _repo.leer(i);
            if (!reg.getEliminado()) {
                temp[activos++] = reg;
            }
        }

        if (activos == 0) {
            rlutil::setColor(rlutil::RED);
            cout << "NO HAY EMPLEADOS CARGADOS.\n";
            rlutil::setColor(rlutil::WHITE);
            return;
        }

        for (int i = 0; i < activos-1; i++) {
            for (int j = 0; j < activos-i - 1; j++) {
                if (strcmp(temp[j].getCargo(), temp[j+1].getCargo()) > 0) {
                    Empleado aux = temp[j];
                    temp[j] = temp[j+1];
                    temp[j+1] = aux;
                }
            }
        }

        cout << "LISTADO DE EMPLEADOS (por cargo):\n";
        for (int i = 0; i < activos; i++) {
            temp[i].MostrarPorCargo();
        }
}

bool EmpleadoManager::listarEmpleadosEliminados() {
    rlutil::cls();
    int cantidad = _repo.getCantidadRegistros();
    bool hayEliminados = false;

    for (int i = 0; i < cantidad; i++) {
        Empleado reg = _repo.leer(i);

        if (reg.getEliminado()) {
            if (!hayEliminados) {
                cout << "LISTADO DE EMPLEADOS ELIMINADOS:\n";
                hayEliminados = true;
            }
            reg.Mostrar(true);
        }
    }

    if (!hayEliminados) {
        rlutil::setColor(rlutil::RED);
        cout << "NO HAY EMPLEADOS ELIMINADOS.\n";
        rlutil::setColor(rlutil::WHITE);
        return false;
    }

    return true;
}

bool EmpleadoManager::buscarEmpleadoPorCargo() {
    while (true) {
        char cargoBuscado[30];
        cout << "Ingrese el cargo del empleado a buscar (o 'salir' para cancelar): ";
        cin.getline(cargoBuscado, 30);
        if (strcmp(cargoBuscado, "salir") == 0) {
            rlutil::setColor(rlutil::RED);
            cout << "OPERACION CANCELADA.\n";
            rlutil::setColor(rlutil::WHITE);
            return false;
        }
        int cantidad = _repo.getCantidadRegistros();
        bool encontrado = false;
        for (int i = 0; i < cantidad; i++) {
            Empleado c = _repo.leer(i);
            if (!c.getEliminado()) {
                if (strcasecmp(c.getCargo(), cargoBuscado) == 0) {
                    c.Mostrar(true);
                    encontrado = true;
                }
            }
        }
        if (encontrado) return true;
        else {
            rlutil::setColor(rlutil::RED);
            cout << "No existe un empleado con el cargo '" << cargoBuscado << "'. Intente nuevamente.\n";
            rlutil::setColor(rlutil::WHITE);
        }
    }
}

bool EmpleadoManager::buscarEmpleadoPorApellido() {
    while (true) {
        char apellidoBuscado[30];
        cout << "Ingrese el apellido del empleado a buscar (o 'salir' para cancelar): ";
        cin.getline(apellidoBuscado, 30);

        if (strcmp(apellidoBuscado, "salir") == 0) {
            rlutil::setColor(rlutil::RED);
            cout << "OPERACION CANCELADA.\n";
            rlutil::setColor(rlutil::WHITE);
            return false;
        }

        int cantidad = _repo.getCantidadRegistros();
        bool encontrado = false;

        for (int i = 0; i < cantidad; i++) {
            Empleado c = _repo.leer(i);
            if (!c.getEliminado()) {
                if (strcasecmp(c.getApellido(), apellidoBuscado) == 0) {
                    c.Mostrar(true);
                    encontrado = true;
                }
            }
        }

        if (encontrado)  return true;
        else {
            rlutil::setColor(rlutil::RED);
            cout << "No existe un empleado con el apellido '" << apellidoBuscado << "'. Intente nuevamente.\n";
            rlutil::setColor(rlutil::WHITE);
        }
    }
}
