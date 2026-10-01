#include <iostream>
#include <cstring>
#include "ProveedorManager.h"
#include "rlutil.h"
#include "MenuProveedor.h"
#include "Utilidades.h"

using namespace std;

ProveedorManager::ProveedorManager() {}

void ProveedorManager::altaProveedor() {
    Proveedor reg;
    int nuevoId = _repo.obtenerProximoId();

    cout << "\nALTA DE PROVEEDOR\n";
    cout << "---------------------------\n";
    rlutil::setColor(rlutil::YELLOW);
    cout << "Para cancelar, escribe 'salir' en cualquier momento.\n\n";
    rlutil::setColor(rlutil::WHITE);
    cout << "ID del proveedor: " << nuevoId << "\n";

    reg.setIdProveedor(nuevoId);
    if (!reg.Cargar()) {
        rlutil::setColor(rlutil::RED);
        cout << "Operacion cancelada. Volviendo al menu anterior...\n";
        rlutil::setColor(rlutil::WHITE);
        return;
    }

    if (_repo.guardar(reg)) {
        rlutil::setColor(rlutil::GREEN);
        cout << "\nPROVEEDOR GUARDADO EN ARCHIVO!!!\n";
        rlutil::setColor(rlutil::WHITE);
    } else {
        rlutil::setColor(rlutil::RED);
        cout << "Error al guardar.\n";
        rlutil::setColor(rlutil::WHITE);
    }
}

bool ProveedorManager::listarProveedores() {
    int cantidad = _repo.getCantidadRegistros();
    bool hayActivos = false;

    for (int i = 0; i < cantidad; i++) {
        Proveedor reg = _repo.leer(i);
        if (!reg.getEliminado()) {
            if (!hayActivos) {
                cout << "LISTADO DE PROVEEDORES:\n";
                hayActivos = true;
            }
            reg.Mostrar();
        }
    }

    if (!hayActivos) {
        rlutil::setColor(rlutil::RED);
        cout << "NO HAY PROVEEDORES CARGADOS.\n";
        rlutil::setColor(rlutil::WHITE);
        return false;
    }
    return true;
}

bool ProveedorManager::listarProveedoresPorNombre() {
    int cantidad = _repo.getCantidadRegistros();
    Proveedor temp[500];
    int activos = 0;

    for (int i = 0; i < cantidad; i++) {
        Proveedor reg = _repo.leer(i);
        if (!reg.getEliminado()) {
            temp[activos++] = reg;
        }
    }

    if (activos == 0) {
        rlutil::setColor(rlutil::RED);
        cout << "NO HAY PROVEEDORES CARGADOS.\n";
        rlutil::setColor(rlutil::WHITE);
        return false;
    }

    for (int i = 0; i < activos - 1; i++) {
        for (int j = 0; j < activos - i - 1; j++) {
            if (strcmp(temp[j].getNombre(), temp[j+1].getNombre()) > 0) {
                Proveedor aux = temp[j];
                temp[j] = temp[j+1];
                temp[j+1] = aux;
            }
        }
    }

    cout << "LISTADO DE PROVEEDORES (por nombre):\n";
    for (int i = 0; i < activos; i++) {
        temp[i].Mostrar();
    }
    return true;
}

bool ProveedorManager::bajaProveedor(int id) {
    if (id <= 0) return false;
    int pos = _repo.buscarPorId(id);
    if (pos == -1) return false;
    Proveedor reg = _repo.leer(pos);
    if (reg.getEliminado()) return false;
    reg.setEliminado(true);
    return _repo.modificar(reg, pos);
}

bool ProveedorManager::reactivarProveedor(int id) {
    if (id <= 0) return false;
    int pos = _repo.buscarPorId(id, true);
    if (pos == -1) return false;
    Proveedor reg = _repo.leer(pos);
    if (!reg.getEliminado()) return false;
    reg.setEliminado(false);
    return _repo.modificar(reg, pos);
}

bool ProveedorManager::existeProveedor(int id) {
    int pos = _repo.buscarPorId(id);
    return pos != -1;
}

void ProveedorManager::modificarProveedor() {
    if (!listarProveedores()) return;

    int id, pos;
    while (true) {
        cout << "\nIngrese ID del proveedor a modificar (0 para salir): ";
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
            cout << "Error: Proveedor no encontrado.\n";
            rlutil::setColor(rlutil::WHITE);
            continue;
        }
        break;
    }

    Proveedor reg = _repo.leer(pos);
    int opcion;
    string entrada;

    do {
        rlutil::cls();
        cout << "\n--- MODIFICAR PROVEEDOR ID " << id << " ---\n";
        cout << "1) Nombre     [" << reg.getNombre()    << "]\n";
        cout << "2) Telefono   [" << reg.getTelefono()  << "]\n";
        cout << "3) Direccion  [" << reg.getDireccion() << "]\n";
        cout << "4) Email      [" << reg.getEmail()     << "]\n";
        cout << "5) Guardar cambios\n";
        cout << "0) Cancelar\n";
        cout << "Opcion: ";
        opcion = leerOpcion();

        switch (opcion) {
            case 1: {
                while (true) {
                    cout << "Nuevo nombre: ";
                    getline(cin, entrada);

                    bool ok = !entrada.empty();
                    for (char c : entrada) {
                        if (!isalpha(c) && c != ' ') { ok = false; break; }
                    }

                    bool existe = false;
                    int cantidad = _repo.getCantidadRegistros();
                    for (int i = 0; i < cantidad; i++) {
                        Proveedor existente = _repo.leer(i);
                        if (!existente.getEliminado() &&
                            existente.getIdProveedor() != reg.getIdProveedor() &&
                            strcasecmp(existente.getNombre(), entrada.c_str()) == 0) {
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
                    reg.setNombre(entrada.c_str());
                    break;
                }
                break;
            }
            case 2: {
                while (true) {
                    cout << "Nuevo telefono (8 a 10 digitos): ";
                    getline(cin, entrada);

                    bool ok = entrada.size() >= 8 && entrada.size() <= 10;
                    for (char c : entrada) {
                        if (!isdigit(c)) { ok = false; break; }
                    }

                    if (!ok) {
                        rlutil::setColor(rlutil::RED);
                        cout << "Error: el telefono debe contener solo numeros (8 a 10 digitos).\n";
                        rlutil::setColor(rlutil::WHITE);
                        continue;
                    }

                    reg.setTelefono(entrada.c_str());
                    break;
                }
                break;
            }
            case 3: {
                while (true) {
                    cout << "Nueva direccion (ej: Av. San Martin 456): ";
                    getline(cin, entrada);

                    bool ok = false;
                    size_t posEspacio = entrada.find_last_of(' ');
                    if (posEspacio != string::npos && posEspacio < entrada.size()-1) {
                        ok = true;
                        for (size_t i = posEspacio+1; i < entrada.size(); i++) {
                            if (!isdigit(entrada[i])) { ok = false; break; }
                        }
                    }

                    if (!ok) {
                        rlutil::setColor(rlutil::RED);
                        cout << "Error: la direccion debe terminar con un numero separado por espacio.\n";
                        rlutil::setColor(rlutil::WHITE);
                        continue;
                    }

                    reg.setDireccion(entrada.c_str());
                    break;
                }
                break;
            }
            case 4: {
                while (true) {
                    cout << "Nuevo email (ej: usuario@dominio.com): ";
                    getline(cin, entrada);

                    if (entrada.find('@') == string::npos) {
                        rlutil::setColor(rlutil::RED);
                        cout << "Error: el email debe contener un @.\n";
                        rlutil::setColor(rlutil::WHITE);
                        continue;
                    }

                    reg.setEmail(entrada.c_str());
                    break;
                }
                break;
            }
            case 5:
                if (_repo.modificar(reg, pos)) {
                    rlutil::setColor(rlutil::GREEN);
                    cout << "PROVEEDOR MODIFICADO CORRECTAMENTE.\n";
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

bool ProveedorManager::listarProveedorEliminados() {
    rlutil::cls();
    int cantidad = _repo.getCantidadRegistros();
    bool hayEliminados = false;

    for (int i = 0; i < cantidad; i++) {
        Proveedor reg = _repo.leer(i);

        if (reg.getEliminado()) {
            if (!hayEliminados) {
                cout << "LISTADO DE PROVEEDORES  ELIMINADOS:\n";
                hayEliminados = true;
            }
            reg.Mostrar(true);
        }
    }

    if (!hayEliminados) {
        rlutil::setColor(rlutil::RED);
        cout << "NO HAY PROVEEDORES ELIMINADOS.\n";
        rlutil::setColor(rlutil::WHITE);
        return false;
    }

    return true;
}


bool ProveedorManager::buscarProveedorPorNombre() {
    while (true) {
        char nombreBuscado[30];
        cout << "Ingrese el nombre del proveedor a buscar (o 'salir' para cancelar): ";
        cin.getline(nombreBuscado, 30);

        if (strcmp(nombreBuscado, "salir") == 0) {
            rlutil::setColor(rlutil::RED);
            cout << "OPERACION CANCELADA.\n";
            rlutil::setColor(rlutil::WHITE);
            return false;
        }

        int cantidad = _repo.getCantidadRegistros();
        bool encontrado = false;

        for (int i = 0; i < cantidad; i++) {
            Proveedor p = _repo.leer(i);
            if (!p.getEliminado()) {
                if (strcmp(p.getNombre(), nombreBuscado) == 0) {
                    p.Mostrar();
                    encontrado = true;
                }
            }
        }
        if (encontrado)  return true;
        else {
            rlutil::setColor(rlutil::RED);
            cout << "No existe un proveedor con el nombre '" << nombreBuscado << "'. Intente nuevamente.\n";
            rlutil::setColor(rlutil::WHITE);
        }
    }
}
