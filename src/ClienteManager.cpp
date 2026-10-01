#include <iostream>
#include <cstring>
#include "ClienteManager.h"
#include "rlutil.h"
#include "MenuCliente.h"
#include "Utilidades.h"

using namespace std;

ClienteManager::ClienteManager() {}
void pausa();
void limpiarEntrada();

void ClienteManager::altaCliente() {
    Cliente reg;
    int nuevoId = _repo.obtenerProximoId();

    cout << "\nALTA DE CLIENTE\n";
    cout << "---------------------------\n";
    rlutil::setColor(rlutil::YELLOW);
    cout << "Para cancelar, escribe 'salir' en cualquier momento.\n\n";
    rlutil::setColor(rlutil::WHITE);
    cout << "ID del cliente a dar de alta: " << nuevoId << "\n";
    reg.setIdCliente(nuevoId);


    if (!reg.Cargar()) {
        rlutil::setColor(rlutil::RED);
        cout << "OPERACION CANCELADA.\n";
        rlutil::setColor(rlutil::WHITE);
        return;

    }

    int cantidad = _repo.getCantidadRegistros();
    for (int i = 0; i < cantidad; i++) {
        Cliente existente = _repo.leer(i);
        if (!existente.getEliminado() &&
            strcmp(existente.getNombre(), reg.getNombre()) == 0 &&
            strcmp(existente.getApellido(), reg.getApellido()) == 0) {
            rlutil::setColor(rlutil::RED);
            cout << "Error: ya existe un cliente con ese nombre y apellido.\n";
            rlutil::setColor(rlutil::WHITE);
            pausa();
            return;
        }
    }

    if (_repo.guardar(reg)) {
        rlutil::setColor(rlutil::GREEN);
        cout << endl;
        cout << "CLIENTE GUARDADO EN ARCHIVO!!!\n";
        rlutil::setColor(rlutil::WHITE);
    }
    else {
        rlutil::setColor(rlutil::RED);
        cout << "Error de apertura.\n";
        rlutil::setColor(rlutil::WHITE);
    }
}

bool ClienteManager::listarClientes() {
    int cantidad = _repo.getCantidadRegistros();
    bool hayActivos = false;

    for (int i = 0; i < cantidad; i++) {
        Cliente reg = _repo.leer(i);

        if (!reg.getEliminado()) {
            if (!hayActivos) {
                cout << "LISTADO DE CLIENTES:\n";
                hayActivos = true;
            }

            reg.Mostrar();
        }
    }

    if (!hayActivos) {
        rlutil::setColor(rlutil::RED);
        cout << "NO HAY CLIENTES CARGADOS.\n";
        rlutil::setColor(rlutil::WHITE);
        return false;
    }

    return true;
}

void ClienteManager::modificarCliente() {
    if (!listarClientes()) return;

    int id, pos;
    while (true) {
        cout << "\nIngrese ID del cliente a modificar (0 para salir): ";
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
            cout << "Error: Cliente no encontrado.\n";
            rlutil::setColor(rlutil::WHITE);
            continue;
        }
        break;
    }

    Cliente reg = _repo.leer(pos);
    int opcion;
    string entrada;

    do {
        rlutil::cls();
        cout << "\n--- MODIFICAR CLIENTE ID " << id << " ---\n";
        cout << "1) Nombre     [" << reg.getNombre()    << "]\n";
        cout << "2) Apellido   [" << reg.getApellido()  << "]\n";
        cout << "3) Telefono   [" << reg.getTelefono()  << "]\n";
        cout << "4) Direccion  [" << reg.getDireccion() << "]\n";
        cout << "5) Email      [" << reg.getEmail()     << "]\n";
        cout << "6) Guardar cambios\n";
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

                    // Valida que nombre y apellido no sean iguales
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
                        Cliente existente = _repo.leer(i);
                        if (!existente.getEliminado() &&
                            existente.getIdCliente() != reg.getIdCliente() &&
                            strcasecmp(existente.getNombre(), reg.getNombre()) == 0 &&
                            strcasecmp(existente.getApellido(), entrada.c_str()) == 0) {
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

                    reg.setApellido(entrada.c_str());
                    break;
                }
                break;
            }
            case 3: {
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
            case 4: {
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
            case 5: {
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
            case 6:
                if (_repo.modificar(reg,pos)) {
                    rlutil::setColor(rlutil::GREEN);
                    cout << "CLIENTE MODIFICADO CORRECTAMENTE.\n";
                    rlutil::setColor(rlutil::WHITE);
                } else {
                    cout << "Error al guardar.\n";
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


bool ClienteManager::bajaCliente(int id) {
    if (id <= 0) return false;
    int pos = _repo.buscarPorId(id);
    if (pos == -1) return false;
    Cliente reg = _repo.leer(pos);
    if (reg.getEliminado()) return false;
    reg.setEliminado(true);
    return _repo.modificar(reg, pos);
}


bool ClienteManager::reactivarCliente(int id) {
    if (id <= 0) return false;
    int pos = _repo.buscarPorId(id, true);
    if (pos == -1) return false;
    Cliente reg = _repo.leer(pos);
    if (!reg.getEliminado()) return false;
    reg.setEliminado(false);
    return _repo.modificar(reg, pos);
}


bool ClienteManager::existeCliente(int id) {
    int pos = _repo.buscarPorId(id);
    return pos != -1;
}

void ClienteManager::listarClientesPorApellido() {
    int cantidad = _repo.getCantidadRegistros();
    Cliente temp[2000];
    int activos = 0;

    for (int i = 0; i < cantidad; i++) {
        Cliente reg = _repo.leer(i);
        if (!reg.getEliminado()) {
            temp[activos++] = reg;
        }
    }

    if (activos == 0) {
        rlutil::setColor(rlutil::RED);
        cout << "NO HAY CLIENTES CARGADOS.\n";
        rlutil::setColor(rlutil::WHITE);
        return;
    }

    for (int i = 0; i < activos - 1; i++) {
        for (int j = 0; j < activos - i - 1; j++) {
            if (strcmp(temp[j].getApellido(), temp[j+1].getApellido()) > 0) {
                Cliente aux = temp[j];
                temp[j] = temp[j+1];
                temp[j+1] = aux;
            }
        }
    }

    cout << "LISTADO DE CLIENTES (por apellido):\n";
    for (int i = 0; i < activos; i++) {
        temp[i].MostrarPorApellido();
    }
}

void ClienteManager::listarClientesPorNombre() {
    int cantidad = _repo.getCantidadRegistros();
    Cliente temp[2000];
    int activos = 0;

    for (int i = 0; i < cantidad; i++) {
        Cliente reg = _repo.leer(i);
        if (!reg.getEliminado()) {
            temp[activos++] = reg;
        }
    }

    if (activos == 0) {
        rlutil::setColor(rlutil::RED);
        cout << "NO HAY CLIENTES CARGADOS.\n";
        rlutil::setColor(rlutil::WHITE);
        return;
    }

    for (int i = 0; i < activos - 1; i++) {
        for (int j = 0; j < activos - i - 1; j++) {
            if (strcmp(temp[j].getNombre(), temp[j+1].getNombre()) > 0) {
                Cliente aux = temp[j];
                temp[j] = temp[j+1];
                temp[j+1] = aux;
            }
        }
    }

    cout << "LISTADO DE CLIENTES (por nombre):\n";
    for (int i = 0; i < activos; i++) {
        temp[i].MostrarPorNombre();
    }
}

bool ClienteManager::listarClientesEliminados() {
    rlutil::cls();
    int cantidad = _repo.getCantidadRegistros();
    bool hayEliminados = false;

    for (int i = 0; i < cantidad; i++) {
        Cliente reg = _repo.leer(i);

        if (reg.getEliminado()) {
            if (!hayEliminados) {
                cout << "LISTADO DE CLIENTES ELIMINADOS:\n";
                hayEliminados = true;
            }
            reg.Mostrar(true);
        }
    }

    if (!hayEliminados) {
        rlutil::setColor(rlutil::RED);
        cout << "NO HAY CLIENTES ELIMINADOS.\n";
        rlutil::setColor(rlutil::WHITE);
        return false;
    }

    return true;
}



bool ClienteManager::buscarClientePorNombre() {
    while (true) {
        char nombreBuscado[30];
        cout << "Ingrese el nombre del cliente a buscar (o 'salir' para cancelar): ";
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
            Cliente c = _repo.leer(i);
            if (!c.getEliminado()) {
                if (strcasecmp(c.getNombre(), nombreBuscado) == 0) {
                    c.Mostrar();
                    encontrado = true;
                }
            }
        }

        if (encontrado) {
            return true;
        } else {
            rlutil::setColor(rlutil::RED);
            cout << "Error: No existe un cliente con el nombre '" << nombreBuscado << "'.\n";
            rlutil::setColor(rlutil::WHITE);
        }
    }
}

bool ClienteManager::buscarClientePorApellido() {
    while (true) {
        char apellidoBuscado[30];
        cout << "Ingrese el apellido del cliente a buscar (o 'salir' para cancelar): ";
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
            Cliente c = _repo.leer(i);
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
            cout << "Error: No existe un cliente con el apellido '" << apellidoBuscado << "'.\n";
            rlutil::setColor(rlutil::WHITE);
        }
    }
}
