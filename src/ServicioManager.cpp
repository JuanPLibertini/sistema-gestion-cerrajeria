#include <iostream>
#include <cstring>
#include "ServicioManager.h"
#include "rlutil.h"
#include "MenuServicio.h"

#include "Utilidades.h"
#include <algorithm>
#include "ServicioManager.h"
#include "rlutil.h"



using namespace std;

ServicioManager::ServicioManager() {}
void pausa();
void limpiarEntrada();

void ServicioManager::altaServicio() {
    Servicio reg;
    int nuevoId = _repo.obtenerProximoId();

    cout << "\nALTA DE SERVICIO\n";
    cout << "---------------------------\n";
    rlutil::setColor(rlutil::YELLOW);
    cout << "Para cancelar, escribe 'salir' en cualquier momento.\n\n";
    rlutil::setColor(rlutil::WHITE);
    cout << "ID del servicio a dar de alta: " << nuevoId << "\n";
    reg.setIdServicio(nuevoId);

    if (!reg.Cargar()) {
        rlutil::setColor(rlutil::RED);
        cout << "Operacion cancelada. Volviendo al menu anterior...\n";
        rlutil::setColor(rlutil::WHITE);
        return;
    }

    if (_repo.guardar(reg)) {
        rlutil::setColor(rlutil::GREEN);
        cout << "\nSERVICIO GUARDADO EN ARCHIVO!!!\n";
        rlutil::setColor(rlutil::WHITE);
    } else {
        rlutil::setColor(rlutil::RED);
        cout << "Error de apertura.\n";
        rlutil::setColor(rlutil::WHITE);
    }
}

bool ServicioManager::listarServicios() {
    int cantidad = _repo.getCantidadRegistros();
    bool hayActivos = false;
    for (int i=0; i<cantidad; i++) {
        Servicio reg = _repo.leer(i);
        if (!reg.getEliminado()) {
            if (!hayActivos) {
                cout << "LISTADO DE SERVICIOS:\n";
                hayActivos = true;
            }
            reg.Mostrar();
        }
    }
    if (!hayActivos) {
        rlutil::setColor(rlutil::RED);
        cout << "NO HAY SERVICIOS CARGADOS.\n";
        rlutil::setColor(rlutil::WHITE);
        return false;
    }
    return true;
}


bool ServicioManager::bajaServicio(int id) {
    int pos = _repo.buscarPorId(id);
    if (pos == -1) return false;

    Servicio reg = _repo.leer(pos);
    reg.setEliminado(true);
    return _repo.modificar(reg, pos);
}

bool ServicioManager::existeServicio(int id) {
    int pos = _repo.buscarPorId(id);
    return pos != -1;
}


bool ServicioManager::existeServicioIncluyendoEliminados(int id) {
    int pos = _repo.buscarPorId(id, true);
    return pos != -1;
}


bool ServicioManager::reactivarServicio(int id) {
    int pos = _repo.buscarPorId(id, true);
    if (pos == -1) return false;

    Servicio reg = _repo.leer(pos);
    if (!reg.getEliminado()) return false;

    reg.setEliminado(false);
    return _repo.modificar(reg, pos);
}

void ServicioManager::modificarServicio() {
    if (!listarServicios()) return;

    int id, pos;
    while (true) {
        cout << "\nIngrese ID del servicio a modificar (0 para salir): ";
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
            cout << "Error: Servicio no encontrado.\n";
            rlutil::setColor(rlutil::WHITE);
            continue;
        }
        break;
    }

    Servicio reg = _repo.leer(pos);
    int opcion;
    string entrada;

    do {
        rlutil::cls();
        cout << "\n--- MODIFICAR SERVICIO ID " << id << " ---\n";

        cout << "1) Descripcion   [" << reg.getDescripcion() << "]\n";
        cout << "2) Tipo          [" << reg.getTipo() << " - "
             << (reg.getTipo() == 1 ? "Local" : "Calle") << "]\n";
        cout << "3) Precio        [$" << reg.getPrecio() << "]\n";
        cout << "4) Guardar cambios\n";
        cout << "0) Cancelar\n";
        cout << "Opcion: ";
        opcion = leerOpcion();

        switch (opcion) {
            case 1: {
                cout << "Nueva descripcion: ";
                getline(cin, entrada);
                if (entrada == "salir") return;

                if (entrada.empty()) {
                    rlutil::setColor(rlutil::RED);
                    cout << "Error: la descripcion no puede estar vacia.\n";
                    rlutil::setColor(rlutil::WHITE);
                    break;
                }

                reg.setDescripcion(entrada.c_str());
                break;
            }
            case 2: {
                while (true) {
                    cout << "Nuevo tipo (1=Local, 2=Calle): ";
                    getline(cin, entrada);

                    if (entrada == "1" || entrada == "2") {
                        int nuevoTipo = stoi(entrada);
                        reg.setTipo(nuevoTipo);
                        break;
                    } else {
                        rlutil::setColor(rlutil::RED);
                        cout << "Error: solo se acepta 1 (Local) o 2 (Calle).\n";
                        rlutil::setColor(rlutil::WHITE);
                    }
                }
                break;
            }
            case 3: {
                while (true) {
                    cout << "Nuevo precio: ";
                    getline(cin, entrada);
                    if (entrada == "salir") return;

                    int nuevoPrecio;
                    try {
                        nuevoPrecio = stoi(entrada);
                    } catch (...) {
                        rlutil::setColor(rlutil::RED);
                        cout << "Error: ingrese un numero valido.\n";
                        rlutil::setColor(rlutil::WHITE);
                        continue;
                    }

                    if (nuevoPrecio <= 0) {
                        rlutil::setColor(rlutil::RED);
                        cout << "Error: el precio debe ser mayor a 0.\n";
                        rlutil::setColor(rlutil::WHITE);
                        continue;
                    }

                    reg.setPrecio(nuevoPrecio);
                    break;
                }
                break;
            }
            case 4:
                if (_repo.modificar(reg, pos)) {
                    rlutil::setColor(rlutil::GREEN);
                    cout << "SERVICIO MODIFICADO CORRECTAMENTE.\n";
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


bool ServicioManager::listarServiciosEliminados() {
    rlutil::cls();
    int cantidad = _repo.getCantidadRegistros();
    bool hayEliminados = false;

    for (int i = 0; i < cantidad; i++) {
        Servicio reg = _repo.leer(i);
        if (reg.getEliminado()) {
            if (!hayEliminados) {
                cout << "LISTADO DE SERVICIOS ELIMINADOS:\n";
                hayEliminados = true;
            }
            reg.Mostrar(true);
        }
    }

    if (!hayEliminados) {
        rlutil::setColor(rlutil::RED);
        cout << "NO HAY SERVICIOS ELIMINADOS.\n";
        rlutil::setColor(rlutil::WHITE);
        return false;
    }
    return true;
}

// CONSULTA DE SERVICIOS
bool ServicioManager::buscarServicioPorTipo() {
    int tipo;
    cout << "Ingrese tipo de servicio (1=Local, 2=Calle, 0=Cancelar): ";
    cin >> tipo;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        rlutil::setColor(rlutil::RED);
        cout << "Entrada inválida.\n";
        rlutil::setColor(rlutil::WHITE);
        return false;
    }

    if (tipo == 0) {
        rlutil::setColor(rlutil::RED);
        cout << "OPERACION CANCELADA.\n";
        rlutil::setColor(rlutil::WHITE);
         pausa();
        return false;
    }

    if (tipo != 1 && tipo != 2) {
        rlutil::setColor(rlutil::RED);
        cout << "Error: solo se acepta 1 (Local) o 2 (Calle).\n";
        rlutil::setColor(rlutil::WHITE);
        return false;
    }

    int cantidad = _repo.getCantidadRegistros();
    bool hay = false;

    for (int i = 0; i < cantidad; i++) {
        Servicio reg = _repo.leer(i);
        if (!reg.getEliminado() && reg.getTipo() == tipo) {
            if (!hay) {
                hay = true;
            }
            reg.Mostrar();
        }
    }

    if (!hay) {
        rlutil::setColor(rlutil::RED);
        cout << "NO HAY SERVICIOS DE ESE TIPO.\n";
        rlutil::setColor(rlutil::WHITE);
    }

    pausa();
    return hay;
}

bool ServicioManager::buscarServicioPorRangoPrecio() {
    float precioMin, precioMax;
    string entrada;

    while (true) {
        cout << "Ingrese precio minimo (0 para cancelar): ";
        getline(cin, entrada);

        try {
            precioMin = stof(entrada);
        } catch (...) {
            rlutil::setColor(rlutil::RED);
            cout << "Error: ingrese un numero valido.\n";
            rlutil::setColor(rlutil::WHITE);
            continue;
        }

        if (precioMin == 0) {
            rlutil::setColor(rlutil::RED);
            cout << "OPERACION CANCELADA.\n";
            rlutil::setColor(rlutil::WHITE);
            pausa();
            return false;
        }

        if (precioMin < 0) {
            rlutil::setColor(rlutil::RED);
            cout << "Error: el precio minimo debe ser mayor a 0.\n";
            rlutil::setColor(rlutil::WHITE);
            continue;
        }
        break;
    }


    while (true) {
        cout << "Ingrese precio maximo (0 para cancelar): ";
        getline(cin, entrada);

        try {
            precioMax = stof(entrada);
        } catch (...) {
            rlutil::setColor(rlutil::RED);
            cout << "Error: ingrese un numero valido.\n";
            rlutil::setColor(rlutil::WHITE);
            continue;
        }

        if (precioMax == 0) {
            rlutil::setColor(rlutil::RED);
            cout << "OPERACION CANCELADA.\n";
            rlutil::setColor(rlutil::WHITE);
            pausa();
            return false;
        }

        if (precioMax < precioMin) {
            rlutil::setColor(rlutil::RED);
            cout << "Error: el precio maximo debe ser mayor o igual al minimo.\n";
            rlutil::setColor(rlutil::WHITE);
            continue;
        }
        break;
    }

    int cantidad = _repo.getCantidadRegistros();
    bool hay = false;

    for (int i = 0; i < cantidad; i++) {
        Servicio reg = _repo.leer(i);
        if (!reg.getEliminado() && reg.getPrecio() >= precioMin && reg.getPrecio() <= precioMax) {
            if (!hay) {
                hay = true;
            }
            reg.MostrarPorPrecio();
        }
    }

    if (!hay) {
        rlutil::setColor(rlutil::RED);
        cout << "NO HAY SERVICIOS EN ESE RANGO DE PRECIO.\n";
        rlutil::setColor(rlutil::WHITE);
        pausa();
        return false;
    }

    pausa();
    return hay;
}


// LISTADO DE SERVICIOS

void ServicioManager::listarOrdenadoPorDescripcion() {
    int cantidad = _repo.getCantidadRegistros();
    Servicio temp[500];
    int activos = 0;

    for (int i = 0; i < cantidad; i++) {
        Servicio reg = _repo.leer(i);
        if (!reg.getEliminado()) temp[activos++] = reg;
    }

    if (activos == 0) {
        rlutil::setColor(rlutil::RED);
        cout << "NO HAY SERVICIOS CARGADOS.\n";
        rlutil::setColor(rlutil::WHITE);
        return;
    }

    for (int i = 0; i < activos - 1; i++)
        for (int j = 0; j < activos - i - 1; j++)
            if (strcmp(temp[j].getDescripcion(), temp[j+1].getDescripcion()) > 0) {
                Servicio aux = temp[j];
                temp[j] = temp[j+1];
                temp[j+1] = aux;
            }

    cout << "LISTADO DE SERVICIOS (por descripcion):\n";
    for (int i = 0; i < activos; i++) temp[i].MostrarPorDescripcion();
}

void ServicioManager::listarOrdenadoPorTipo() {
    int cantidad = _repo.getCantidadRegistros();
    Servicio temp[500];
    int activos = 0;

    for (int i = 0; i < cantidad; i++) {
        Servicio reg = _repo.leer(i);
        if (!reg.getEliminado()) temp[activos++] = reg;
    }

    if (activos == 0) {
        rlutil::setColor(rlutil::RED);
        cout << "NO HAY SERVICIOS CARGADOS.\n";
        rlutil::setColor(rlutil::WHITE);
        return;
    }

    for (int i = 0; i < activos - 1; i++)
        for (int j = 0; j < activos - i - 1; j++)
            if (temp[j].getTipo() > temp[j+1].getTipo()) {
                Servicio aux = temp[j];
                temp[j] = temp[j+1];
                temp[j+1] = aux;
            }

    cout << "LISTADO DE SERVICIOS (por tipo):\n";
    for (int i = 0; i < activos; i++) temp[i].MostrarPorTipo();
}

void ServicioManager::listarOrdenadoPorPrecio() {
    int cantidad = _repo.getCantidadRegistros();
    Servicio temp[500];
    int activos = 0;

    for (int i = 0; i < cantidad; i++) {
        Servicio reg = _repo.leer(i);
        if (!reg.getEliminado()) temp[activos++] = reg;
    }

    if (activos == 0) {
        rlutil::setColor(rlutil::RED);
        cout << "NO HAY SERVICIOS CARGADOS.\n";
        rlutil::setColor(rlutil::WHITE);
        return;
    }

    for (int i = 0; i < activos - 1; i++)
        for (int j = 0; j < activos - i - 1; j++)
            if (temp[j].getPrecio() > temp[j+1].getPrecio()) {
                Servicio aux = temp[j];
                temp[j] = temp[j+1];
                temp[j+1] = aux;
            }

    cout << "LISTADO DE SERVICIOS (por precio):\n";
    for (int i = 0; i < activos; i++) temp[i].MostrarPorPrecio();
}
