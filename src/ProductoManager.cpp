#include <iostream>
#include "ProductoManager.h"
#include "ProveedorArchivo.h"
#include "rlutil.h"
#include "Utilidades.h"

using namespace std;

ProductoManager::ProductoManager() {}
void pausa();
void limpiarEntrada();

void ProductoManager::altaProducto() {
    Producto reg;
    int nuevoId = _repo.obtenerProximoId();

    cout << "\nALTA DE PRODUCTO\n";
    cout << "---------------------------\n";
    rlutil::setColor(rlutil::YELLOW);
    cout << "Para cancelar, escribe 'salir' en cualquier momento.\n\n";
    rlutil::setColor(rlutil::WHITE);
    cout << "ID del producto a dar de alta: " << nuevoId << "\n";
    reg.setIdProducto(nuevoId);

    if (!reg.Cargar()) {
        rlutil::setColor(rlutil::RED);
        cout << "Operacion cancelada. Volviendo al menu anterior...\n";
        rlutil::setColor(rlutil::WHITE);
        return;
    }


    int cantidad = _repo.getCantidadRegistros();
    for (int i = 0; i < cantidad; i++) {
        Producto existente = _repo.leer(i);
        if (!existente.getEliminado() &&
            strcmp(existente.getNombre(), reg.getNombre()) == 0 &&
            strcmp(existente.getMarca(), reg.getMarca()) == 0) {
            rlutil::setColor(rlutil::RED);
            cout << "Error: ya existe un producto con ese nombre para la misma marca.\n";
            rlutil::setColor(rlutil::WHITE);
            pausa();
            return;
        }
    }

    if (_repo.guardar(reg)) {
        rlutil::setColor(rlutil::GREEN);
        cout << "\nPRODUCTO GUARDADO EN ARCHIVO!!!\n";
        rlutil::setColor(rlutil::WHITE);
    } else {
        rlutil::setColor(rlutil::RED);
        cout << "Error de apertura.\n";
        rlutil::setColor(rlutil::WHITE);
    }
}

bool ProductoManager::listarProductos() {
    int cantidad = _repo.getCantidadRegistros();
    bool hayActivos = false;

    for (int i = 0; i < cantidad; i++) {
        Producto reg = _repo.leer(i);

        if (!reg.getEliminado()) {
            if (!hayActivos) {
                cout << "LISTADO DE PRODUCTOS:\n";
                hayActivos = true;
            }

            reg.Mostrar();
        }
    }

    if (!hayActivos) {
        rlutil::setColor(rlutil::RED);
        cout << "NO HAY PRODUCTOS CARGADOS.\n";
        rlutil::setColor(rlutil::WHITE);
        return false;
    }

    return true;
}


void ProductoManager::modificarProducto() {
    if (!listarProductos()) return;

    int id, pos;
    while (true) {
        cout << "\nIngrese ID del producto a modificar (0 para salir): ";
        cin >> id;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            rlutil::setColor(rlutil::RED);
            cout << "Entrada invalida. Debe ingresar un numero entero positivo.\n";
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
            cout << "El ID no puede ser negativo.\n";
            rlutil::setColor(rlutil::WHITE);
            continue;
        }

        pos = _repo.buscarPorId(id);
        if (pos == -1) {
            rlutil::setColor(rlutil::RED);
            cout << "Producto no encontrado.\n";
            rlutil::setColor(rlutil::WHITE);
            continue;
        }
        break;
    }

    Producto reg = _repo.leer(pos);
    int opcion;
    string entrada;

    do {
        rlutil::cls();
        cout << "\n--- MODIFICAR PRODUCTO ID " << id << " ---\n";
        cout << "1) Nombre       [" << reg.getNombre()      << "]\n";
        cout << "2) Descripcion  [" << reg.getDescripcion() << "]\n";
        cout << "3) Modelo       [" << reg.getTipo()        << "]\n";
        cout << "4) Precio       [" << reg.getPrecio()      << "]\n";
        cout << "5) Stock        [" << reg.getStock()       << "]\n";
        cout << "6) ID Proveedor [" << reg.getIdProveedor() << "]\n";
        cout << "7) Guardar cambios\n";
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
                cout << "Nueva descripcion: ";
                getline(cin, entrada);
                if (entrada == "salir") return;
                reg.setDescripcion(entrada.c_str());
                break;
            }
            case 3: {
                while (true) {
                    cout << "Nuevo modelo (máx. 5 caracteres): ";
                    getline(cin, entrada);
                    if (entrada == "salir") return;

                    bool ok = (!entrada.empty() && entrada.size() <= 5);
                    for (char c : entrada) {
                        if (!isalnum(c)) { ok = false; break; }
                    }

                    if (!ok) {
                        rlutil::setColor(rlutil::RED);
                        cout << "Error: el modelo debe tener hasta 5 caracteres, solo letras o numeros.\n";
                        rlutil::setColor(rlutil::WHITE);
                        continue;
                    }

                    reg.setTipo(entrada.c_str());
                    break;
                }
                break;
            }
            case 4: {
                while (true) {
                    cout << "Nuevo precio: ";
                    getline(cin, entrada);
                    if (entrada == "salir") return;

                    float nuevoPrecio;
                    try {
                        nuevoPrecio = stof(entrada);
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
            case 5: {
                while (true) {
                    cout << "Nuevo stock: ";
                    getline(cin, entrada);
                    if (entrada == "salir") return;

                    int nuevoStock;
                    try {
                        nuevoStock = stoi(entrada);
                    } catch (...) {
                        rlutil::setColor(rlutil::RED);
                        cout << "Error: ingrese un numero valido.\n";
                        rlutil::setColor(rlutil::WHITE);
                        continue;
                    }

                    if (nuevoStock < 0) {
                        rlutil::setColor(rlutil::RED);
                        cout << "Error: el stock debe ser no negativo.\n";
                        rlutil::setColor(rlutil::WHITE);
                        continue;
                    }

                    reg.setStock(nuevoStock);
                    break;
                }
                break;
            }
            case 6: {
                ProveedorArchivo repoProv;

                while (true) {
                    cout << "\nLISTADO DE PROVEEDORES:\n";
                    cout << "---------------------------\n";
                    for (int i = 0; i < repoProv.getCantidadRegistros(); i++) {
                        Proveedor p = repoProv.leer(i);
                        if (!p.getEliminado()) {
                            cout << "ID: " << p.getIdProveedor()
                                 << " - " << p.getNombre() << "\n";
                        }
                    }
                    cout << "---------------------------\n";

                    cout << "Nuevo ID proveedor (o 'salir'): ";
                    getline(cin, entrada);
                    if (entrada == "salir") return;

                    int nuevoId;
                    try {
                        nuevoId = stoi(entrada);
                    } catch (...) {
                        rlutil::setColor(rlutil::RED);
                        cout << "Error: ingrese un numero valido.\n";
                        rlutil::setColor(rlutil::WHITE);
                        continue;
                    }

                    if (repoProv.buscarPorId(nuevoId) == -1) {
                        rlutil::setColor(rlutil::RED);
                        cout << "Error: proveedor inexistente.\n";
                        rlutil::setColor(rlutil::WHITE);
                        continue;
                    }

                    reg.setIdProveedor(nuevoId);
                    break;
                }
                break;
            }
            case 7:
                if (_repo.modificar(reg, pos)) {
                    rlutil::setColor(rlutil::GREEN);
                    cout << "PRODUCTO MODIFICADO CORRECTAMENTE.\n";
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

bool ProductoManager::bajaProducto(int id) {
    if (id <= 0) return false;

    int pos = _repo.buscarPorId(id);
    if (pos == -1) {
        return false;
    }
    Producto reg = _repo.leer(pos);
    if (reg.getEliminado()) {
        return false; }
    reg.setEliminado(true);
    return _repo.modificar(reg, pos);
}


void ProductoManager::listarProductoPorNombre() {
    int cantidad = _repo.getCantidadRegistros();
    Producto temp[500];
    int activos = 0;

    for (int i = 0; i < cantidad; i++) {
        Producto reg = _repo.leer(i);
        if (!reg.getEliminado()) {
            temp[activos++] = reg;
        }
    }

    if (activos == 0) {
        rlutil::setColor(rlutil::RED);
        cout << "NO HAY PRODUCTOS CARGADOS.\n";
        rlutil::setColor(rlutil::WHITE);
        return;
    }

    for (int i = 0; i < activos - 1; i++) {
        for (int j = 0; j < activos - i - 1; j++) {
            if (strcmp(temp[j].getNombre(), temp[j+1].getNombre()) > 0) {
                Producto aux = temp[j];
                temp[j] = temp[j+1];
                temp[j+1] = aux;
            }
        }
    }

    cout << "LISTADO DE PRODUCTOS (por nombre):\n";
    for (int i = 0; i < activos; i++) {
        temp[i].Mostrar();
    }
}

bool ProductoManager::reactivarProducto(int id) {
    if (id <= 0) return false;
    int pos = _repo.buscarPorId(id, true);
    if (pos == -1) {
        return false;
    }
    Producto reg = _repo.leer(pos);
    if (!reg.getEliminado()) {
        return false;
    }
    reg.setEliminado(false);
    return _repo.modificar(reg, pos);
}





void ProductoManager::listarProductoPorMarca() {
    int cantidad = _repo.getCantidadRegistros();
    Producto temp[500];
    int activos = 0;

    for (int i = 0; i < cantidad; i++) {
        Producto reg = _repo.leer(i);
        if (!reg.getEliminado()) temp[activos++] = reg;
    }

    if (activos == 0) {
        rlutil::setColor(rlutil::RED);
        cout << "NO HAY PRODUCTOS CARGADOS.\n";
        rlutil::setColor(rlutil::WHITE);
        return;
    }

    for (int i = 0; i < activos - 1; i++)
        for (int j = 0; j < activos - i - 1; j++)
            if (strcmp(temp[j].getMarca(), temp[j+1].getMarca()) > 0) {
                Producto aux = temp[j];
                temp[j] = temp[j+1];
                temp[j+1] = aux;
            }

    cout << "LISTADO DE PRODUCTOS (por marca):\n";
    for (int i = 0; i < activos; i++) temp[i].MostrarProductoPorMarca();
}

void ProductoManager::listarProductoPorPrecio() {
    int cantidad = _repo.getCantidadRegistros();
    Producto temp[500];
    int activos = 0;

    for (int i = 0; i < cantidad; i++) {
        Producto reg = _repo.leer(i);
        if (!reg.getEliminado()) temp[activos++] = reg;
    }

    if (activos == 0) {
        rlutil::setColor(rlutil::RED);
        cout << "NO HAY PRODUCTOS CARGADOS.\n";
        rlutil::setColor(rlutil::WHITE);
        return;
    }

    for (int i = 0; i < activos - 1; i++)
        for (int j = 0; j < activos - i - 1; j++)
            if (temp[j].getPrecio() > temp[j+1].getPrecio()) {
                Producto aux = temp[j];
                temp[j] = temp[j+1];
                temp[j+1] = aux;
            }

    cout << "LISTADO DE PRODUCTOS (por precio):\n";
    for (int i = 0; i < activos; i++) temp[i].MostrarProductoPorPrecio();
}

void ProductoManager::listarProductoPorStock() {
    int cantidad = _repo.getCantidadRegistros();
    Producto temp[500];
    int activos = 0;

    for (int i = 0; i < cantidad; i++) {
        Producto reg = _repo.leer(i);
        if (!reg.getEliminado()) temp[activos++] = reg;
    }

    if (activos == 0) {
        rlutil::setColor(rlutil::RED);
        cout << "NO HAY PRODUCTOS CARGADOS.\n";
        rlutil::setColor(rlutil::WHITE);
        return;
    }

    for (int i = 0; i < activos - 1; i++)
        for (int j = 0; j < activos - i - 1; j++)
            if (temp[j].getStock() > temp[j+1].getStock()) {
                Producto aux = temp[j];
                temp[j] = temp[j+1];
                temp[j+1] = aux;
            }

    cout << "LISTADO DE PRODUCTOS (por stock):\n";
    for (int i = 0; i < activos; i++) temp[i].MostrarProductoPorStock();
}

bool ProductoManager::existeProducto(int id) {
    int pos = _repo.buscarPorId(id);
    return pos != -1;
}

bool ProductoManager::listarProductoEliminados() {
    rlutil::cls();
    int cantidad = _repo.getCantidadRegistros();
    bool hayEliminados = false;

    for (int i = 0; i < cantidad; i++) {
        Producto reg = _repo.leer(i);

        if (reg.getEliminado()) {
            if (!hayEliminados) {
                cout << "LISTADO DE PRODUCTOS ELIMINADOS:\n";
                hayEliminados = true;
            }
            reg.Mostrar(true);
        }
    }

    if (!hayEliminados) {
        rlutil::setColor(rlutil::RED);
        cout << "NO HAY PRODUCTOS ELIMINADOS.\n";
        rlutil::setColor(rlutil::WHITE);
        return false;
    }

    return true;
}

bool ProductoManager::buscarProductoPorNombre() {
    while (true) {
        char nombreBuscado[30];
        cout << "Ingrese el nombre del producto a buscar (o 'salir' para cancelar): ";
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
            Producto p = _repo.leer(i);
            if (!p.getEliminado()) {
                if (strcasecmp(p.getNombre(), nombreBuscado) == 0) {
                    p.Mostrar();
                    encontrado = true;
                }
            }
        }
        if (encontrado)  return true;
        else {
            rlutil::setColor(rlutil::RED);
            cout << "Error: No existe un producto con el nombre '" << nombreBuscado << "'. Intente nuevamente.\n";
            rlutil::setColor(rlutil::WHITE);
        }
    }
}

bool ProductoManager::buscarProductoPorTipo() {
    while (true) {
        char tipoBuscado[30];
        cout << "Ingrese el tipo de producto a buscar (o 'salir' para cancelar): ";
        cin.getline(tipoBuscado, 30);

        if (strcmp(tipoBuscado, "salir") == 0) {
            rlutil::setColor(rlutil::RED);
            cout << "OPERACION CANCELADA.\n";
            rlutil::setColor(rlutil::WHITE);
            return false;
        }

        int cantidad = _repo.getCantidadRegistros();
        bool encontrado = false;

        for (int i = 0; i < cantidad; i++) {
            Producto p = _repo.leer(i);
            if (!p.getEliminado()) {
                if (strcasecmp(p.getTipo(), tipoBuscado) == 0) {
                    p.Mostrar();
                    encontrado = true;
                }
            }
        }

        if (encontrado) return true;
            else {
            rlutil::setColor(rlutil::RED);
            cout << "Error: No existe un producto con el tipo '" << tipoBuscado << "'. Intente nuevamente.\n";
            rlutil::setColor(rlutil::WHITE);
        }
    }
}


bool ProductoManager::buscarProductoPorRangoPrecio() {
    while (true) {
         float minPrecio, maxPrecio;
        cout << "Ingrese precio minimo (0 para cancelar): ";
        cin >> minPrecio;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            rlutil::setColor(rlutil::RED);
            cout << "Error: Entrada invalida. Debe ingresar un numero.\n";
            rlutil::setColor(rlutil::WHITE);
            continue;
        }
        cin.ignore(1000, '\n');

        if (minPrecio == 0) {
            rlutil::setColor(rlutil::RED);
            cout << "OPERACION CANCELADA.\n";
            rlutil::setColor(rlutil::WHITE);
            return false;
        }

        if (minPrecio < 0) {
            rlutil::setColor(rlutil::RED);
            cout << "Error: El precio minimo no puede ser negativo.\n";
            rlutil::setColor(rlutil::WHITE);
            continue;
        }
        while (true) {
            cout << "Ingrese precio maximo (0 para cancelar): ";
            cin >> maxPrecio;

            if (maxPrecio == 0) {
            rlutil::setColor(rlutil::RED);
            cout << "OPERACION CANCELADA.\n";
            rlutil::setColor(rlutil::WHITE);
            limpiarEntrada();
            return false;
        }

            if (cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
                rlutil::setColor(rlutil::RED);
                cout << "Error: Entrada invalida. Debe ingresar un numero.\n";
                rlutil::setColor(rlutil::WHITE);
                continue;
            }
            cin.ignore(1000, '\n');

            if (maxPrecio < 0) {
                rlutil::setColor(rlutil::RED);
                cout << "Error: El precio maximo no puede ser negativo.\n";
                rlutil::setColor(rlutil::WHITE);
                continue;
            }

            if (maxPrecio < minPrecio) {
                rlutil::setColor(rlutil::RED);
                cout << "Error: El precio maximo debe ser mayor o igual al minimo.\n";
                rlutil::setColor(rlutil::WHITE);
                continue;
            }
            break;
        }
        int cantidad = _repo.getCantidadRegistros();
        bool encontrado = false;

        for (int i = 0; i < cantidad; i++) {
            Producto p = _repo.leer(i);
            if (!p.getEliminado() && p.getPrecio() >= minPrecio && p.getPrecio() <= maxPrecio) {
                p.Mostrar();
                encontrado = true;
            }
        }
        if (encontrado)return true;
        else {
            rlutil::setColor(rlutil::RED);
            cout << "No existen productos en el rango de precio ingresado. Intente nuevamente.\n";
            rlutil::setColor(rlutil::WHITE);
        }
    }
}

bool ProductoManager::buscarProductoPorProveedor() {
    while (true) {
        int idProveedor;
        cout << "Ingrese ID del proveedor (0 para cancelar): ";
        cin >> idProveedor;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            rlutil::setColor(rlutil::RED);
            cout << "Error: Entrada invalida. Debe ingresar un numero.\n";
            rlutil::setColor(rlutil::WHITE);
            continue;
        }
        cin.ignore(1000, '\n');

        if (idProveedor == 0) {
            rlutil::setColor(rlutil::RED);
            cout << "OPERACION CANCELADA.\n";
            rlutil::setColor(rlutil::WHITE);
            return false;
        }

        int cantidad = _repo.getCantidadRegistros();
        bool encontrado = false;

        for (int i = 0; i < cantidad; i++) {
            Producto p = _repo.leer(i);
            if (!p.getEliminado() && p.getIdProveedor() == idProveedor) {
                p.Mostrar();
                encontrado = true;
            }
        }

        if (encontrado) {
            return true;
        } else {
            rlutil::setColor(rlutil::RED);
            cout << "Error: No existen productos asociados al proveedor con ID "
                 << idProveedor << ". Intente nuevamente.\n";
            rlutil::setColor(rlutil::WHITE);
        }
    }
}



