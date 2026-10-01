#include <iostream>
#include <cstring>
#include "CompraManager.h"
#include "rlutil.h"
#include "Utilidades.h"

#include "ProveedorArchivo.h"
#include "EmpleadoArchivo.h"
#include "ProductoArchivo.h"
#include "Proveedor.h"
#include "Empleado.h"

using namespace std;

// Compara fechas como entero (AAAAMMDD)
static int fechaToInt(const Fecha& f) {
    return f.getAnio() * 10000 + f.getMes() * 100 + f.getDia();
}

CompraManager::CompraManager() {}


void CompraManager::altaCompra() {
    Compra reg;
    int nuevoId = _repo.obtenerProximoId();
    reg.setIdCompra(nuevoId);

    rlutil::cls();
    cout << "\nALTA DE COMPRA\n";
    cout << "---------------------------\n";
    rlutil::setColor(rlutil::YELLOW);
    cout << "Para cancelar, escribe 'salir' en cualquier momento.\n\n";
    rlutil::setColor(rlutil::WHITE);
    cout << "ID de la compra: " << nuevoId << "\n";

    if (!reg.Cargar()) {
        rlutil::setColor(rlutil::RED);
        cout << "OPERACION CANCELADA.\n";
        rlutil::setColor(rlutil::WHITE);
        return;
    }

    const int MAX_ITEMS = 100;
    CompraDetalle detalles[MAX_ITEMS];
    int cantDetalles = 0;
    float totalAcumulado = 0;
    int opcion;

    do {
        rlutil::cls();
        cout << "\n--- COMPRA ID " << nuevoId << " (total actual: $" << totalAcumulado << ") ---\n\n";

        if (cantDetalles == 0) {
            cout << "(Sin productos agregados aun)\n";
        } else {
            cout << "Productos agregados:\n";
            for (int i = 0; i < cantDetalles; i++) {
                cout << "  " << (i + 1) << ") Producto ID " << detalles[i].getIdProducto()
                     << " x" << detalles[i].getCantidad()
                     << " = $" << (detalles[i].getCantidad() * detalles[i].getPrecioUnitario()) << "\n";
            }
        }

        cout << "\n1) Agregar producto\n";
        cout << "2) Quitar un producto agregado\n";
        cout << "3) Finalizar compra\n";
        cout << "0) Cancelar compra\n";
        cout << "Opcion: ";
        opcion = leerOpcion();

        switch (opcion) {
            case 1: {
                if (cantDetalles >= MAX_ITEMS) {
                    rlutil::setColor(rlutil::RED);
                    cout << "Limite de items alcanzado.\n";
                    rlutil::setColor(rlutil::WHITE);
                } else {
                    CompraDetalle det;
                    if (det.Cargar()) {
                        det.setIdCompra(nuevoId);
                        detalles[cantDetalles++] = det;
                        totalAcumulado += det.getPrecioUnitario() * det.getCantidad();
                        rlutil::setColor(rlutil::GREEN);
                        cout << "Producto agregado a la compra.\n";
                        rlutil::setColor(rlutil::WHITE);
                    }
                }
                cout << "\nPresione ENTER para continuar...";
                cin.ignore();
                break;
            }
            case 2: {
                if (cantDetalles == 0) {
                    rlutil::setColor(rlutil::RED);
                    cout << "No hay productos para quitar.\n";
                    rlutil::setColor(rlutil::WHITE);
                } else {
                    cout << "Ingrese el numero del item a quitar (0 para cancelar): ";
                    int idx = leerOpcion();
                    if (idx == 0) {
                        // no hace nada
                    } else if (idx >= 1 && idx <= cantDetalles) {
                        int i = idx - 1;
                        totalAcumulado -= detalles[i].getPrecioUnitario() * detalles[i].getCantidad();
                        for (int j = i; j < cantDetalles - 1; j++) detalles[j] = detalles[j + 1];
                        cantDetalles--;
                        rlutil::setColor(rlutil::GREEN);
                        cout << "Item eliminado.\n";
                        rlutil::setColor(rlutil::WHITE);
                    } else {
                        rlutil::setColor(rlutil::RED);
                        cout << "Numero invalido.\n";
                        rlutil::setColor(rlutil::WHITE);
                    }
                }
                cout << "\nPresione ENTER para continuar...";
                cin.ignore();
                break;
            }
            case 3:
                break;
            case 0:
                rlutil::setColor(rlutil::RED);
                cout << "Operacion cancelada.\n";
                rlutil::setColor(rlutil::WHITE);
                return;
            default:
                rlutil::setColor(rlutil::RED);
                cout << "OPCION INVALIDA.\n";
                rlutil::setColor(rlutil::WHITE);
                cout << "\nPresione ENTER para continuar...";
                cin.ignore();
                break;
        }
    } while (opcion != 3);

    if (cantDetalles == 0) {
        rlutil::setColor(rlutil::RED);
        cout << "No se agrego ningun producto. OPERACION CANCELADA.\n";
        rlutil::setColor(rlutil::WHITE);
        return;
    }

    reg.setTotalCompra(totalAcumulado);

    if (!_repo.guardar(reg)) {
        rlutil::setColor(rlutil::RED);
        cout << "Error al guardar la compra.\n";
        rlutil::setColor(rlutil::WHITE);
        return;
    }

    ProductoArchivo repoProd;
    for (int i = 0; i < cantDetalles; i++) {
        _repoDetalle.guardar(detalles[i]);
        int pos = repoProd.buscarPorId(detalles[i].getIdProducto(), true);
        if (pos != -1) {
            Producto p = repoProd.leer(pos);
            p.setStock(p.getStock() + detalles[i].getCantidad());
            repoProd.modificar(p, pos);
        }
    }

    rlutil::setColor(rlutil::GREEN);
    cout << "\nCOMPRA GUARDADA EN ARCHIVO!!! Total: $" << totalAcumulado << "\n";
    rlutil::setColor(rlutil::WHITE);
}

bool CompraManager::listarCompras() {
    int cantidad = _repo.getCantidadRegistros();
    bool hay = false;

    for (int i=0; i<cantidad; i++) {
        Compra reg = _repo.leer(i);
        if (!reg.getEliminado()) {
            if (!hay) {
                cout << "LISTADO DE COMPRAS:\n";
                hay = true;
            }
            reg.Mostrar();
        }
    }

    if (!hay) {
        rlutil::setColor(rlutil::RED);
        cout << "NO HAY COMPRAS CARGADAS.\n";
        rlutil::setColor(rlutil::WHITE);
        return false;
    }
    return true;
}

bool CompraManager::listarCompraPorEmpleado() {
    int cantidad = _repo.getCantidadRegistros();
    Compra temp[500];
    int activos = 0;

    for (int i=0; i<cantidad; i++) {
        Compra reg = _repo.leer(i);
        if (!reg.getEliminado()) temp[activos++] = reg;
    }

    if (activos == 0) {
        rlutil::setColor(rlutil::RED);
        cout << "NO HAY COMPRAS CARGADAS.\n";
        rlutil::setColor(rlutil::WHITE);
        return false;
    }

    for (int i=0; i<activos-1; i++) {
        for (int j=0; j<activos-i-1; j++) {
            if (temp[j].getIdEmpleado() > temp[j+1].getIdEmpleado()) {
                Compra aux = temp[j];
                temp[j] = temp[j+1];
                temp[j+1] = aux;
            }
        }
    }

    cout << "LISTADO DE COMPRAS (por empleado):\n";
    for (int i=0; i<activos; i++) temp[i].MostrarPorEmpleado();
    return true;
}

bool CompraManager::listarCompraPorFecha() {
    int cantidad = _repo.getCantidadRegistros();
    Compra temp[500];
    int activos = 0;

    for (int i=0; i<cantidad; i++) {
        Compra reg = _repo.leer(i);
        if (!reg.getEliminado()) temp[activos++] = reg;
    }

    if (activos == 0) {
        rlutil::setColor(rlutil::RED);
        cout << "NO HAY COMPRAS CARGADAS.\n";
        rlutil::setColor(rlutil::WHITE);
        return false;
    }

    for (int i = 0; i < activos - 1; i++) {
        for (int j = 0; j < activos - i - 1; j++) {
            Fecha f1 = temp[j].getFechaCompra();
            Fecha f2 = temp[j + 1].getFechaCompra();

            if (f1.esMayorQue(f2)) {
                Compra aux = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = aux;
            }
        }
    }

    cout << "LISTADO DE COMPRAS (por fecha):\n";
    for (int i=0; i<activos; i++) temp[i].MostrarPorFecha();
    return true;
}

bool CompraManager::listarCompraPorProveedor() {
    int cantidad = _repo.getCantidadRegistros();
    Compra temp[500];
    int activos = 0;

    for (int i=0; i<cantidad; i++) {
        Compra reg = _repo.leer(i);
        if (!reg.getEliminado()) temp[activos++] = reg;
    }

    if (activos == 0) {
        rlutil::setColor(rlutil::RED);
        cout << "NO HAY COMPRAS CARGADAS.\n";
        rlutil::setColor(rlutil::WHITE);
        return false;
    }

    for (int i=0; i<activos-1; i++) {
        for (int j=0; j<activos-i-1; j++) {
            if (temp[j].getIdProveedor() > temp[j+1].getIdProveedor()) {
                Compra aux = temp[j];
                temp[j] = temp[j+1];
                temp[j+1] = aux;
            }
        }
    }

    cout << "LISTADO DE COMPRAS (por proveedor):\n";
    for (int i=0; i<activos; i++) temp[i].MostrarPorProveedor();
    return true;
}

bool CompraManager::reactivarCompra(int id) {
    int pos = _repo.buscarPorId(id, true);
    if (pos == -1) return false;

    Compra reg = _repo.leer(pos);
    if (!reg.getEliminado()) return false;

    reg.setEliminado(false);
    return _repo.modificar(reg, pos);
}


bool CompraManager::existeCompra(int id) {
    return _repo.buscarPorId(id) != -1;
}

bool CompraManager::bajaCompra(int id) {
    int pos = _repo.buscarPorId(id);
    if (pos == -1) return false;
    Compra reg = _repo.leer(pos);
    reg.setEliminado(true);
    return _repo.modificar(reg, pos);
}

void CompraManager::modificarCompra() {
    if (!listarCompras()) return;

    int id, pos;
    while (true) {
        cout << "\nIngrese ID de la compra a modificar (0 para salir): ";
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
            cout << "Compra no encontrada.\n";
            rlutil::setColor(rlutil::WHITE);
            continue;
        }
        break;
    }

    Compra reg = _repo.leer(pos);
    int opcion;
    string entrada;

    ProveedorArchivo repoProv;
    EmpleadoArchivo repoEmp;

    do {
        rlutil::cls();
        cout << "\n--- MODIFICAR COMPRA ID " << id << " ---\n";
        cout << "1) ID Proveedor  [" << reg.getIdProveedor() << "]\n";
        cout << "2) ID Empleado   [" << reg.getIdEmpleado()  << "]\n";
        cout << "3) Fecha compra  "; reg.getFechaCompra().Mostrar(); cout << "\n";
        cout << "4) Total compra  [$" << reg.getTotalCompra() << "]\n";
        cout << "5) Guardar cambios\n";
        cout << "0) Cancelar\n";
        cout << "Opcion: ";
        opcion = leerOpcion();

        switch (opcion) {
            case 1: {
                while (true) {
                    cout << "\nLISTADO DE PROVEEDORES:\n";
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
            case 2: {
                while (true) {
                    cout << "\nLISTADO DE EMPLEADOS:\n";
                    for (int i = 0; i < repoEmp.getCantidadRegistros(); i++) {
                        Empleado e = repoEmp.leer(i);
                        if (!e.getEliminado()) {
                            cout << "ID: " << e.getIdEmpleado()
                                 << " - " << e.getNombre() << " " << e.getApellido() << "\n";
                        }
                    }
                    cout << "---------------------------\n";
                    cout << "Nuevo ID empleado (o 'salir'): ";
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

                    if (repoEmp.buscarPorId(nuevoId) == -1) {
                        rlutil::setColor(rlutil::RED);
                        cout << "Error: empleado inexistente.\n";
                        rlutil::setColor(rlutil::WHITE);
                        continue;
                    }

                    reg.setIdEmpleado(nuevoId);
                    break;
                }
                break;
            }
            case 3: {
                Fecha nuevaFecha;
                cout << "Nueva fecha de compra:\n";
                if (nuevaFecha.Cargar()) {
                    reg.setFechaCompra(nuevaFecha);
                }
                break;
            }
            case 4: {
                while (true) {
                    cout << "Nuevo total de compra: ";
                    getline(cin, entrada);
                    if (entrada == "salir") return;

                    float nuevoTotal;
                    try {
                        nuevoTotal = stof(entrada);
                    } catch (...) {
                        rlutil::setColor(rlutil::RED);
                        cout << "Error: ingrese un numero valido.\n";
                        rlutil::setColor(rlutil::WHITE);
                        continue;
                    }

                    if (nuevoTotal <= 0) {
                        rlutil::setColor(rlutil::RED);
                        cout << "Error: el total debe ser mayor a 0.\n";
                        rlutil::setColor(rlutil::WHITE);
                        continue;
                    }

                    reg.setTotalCompra(nuevoTotal);
                    break;
                }
                break;
            }
            case 5:
                if (_repo.modificar(reg, pos)) {
                    rlutil::setColor(rlutil::GREEN);
                    cout << "COMPRA MODIFICADA CORRECTAMENTE.\n";
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

bool CompraManager::listarCompraEliminada() {
    rlutil::cls();
    int cantidad = _repo.getCantidadRegistros();
    bool hayEliminados = false;

    for (int i = 0; i < cantidad; i++) {
        Compra reg = _repo.leer(i);

        if (reg.getEliminado()) {
            if (!hayEliminados) {
                cout << "LISTADO DE COMPRAS ELIMINADAS:\n";
                hayEliminados = true;
            }
            reg.Mostrar(true);
        }
    }

    if (!hayEliminados) {
        rlutil::setColor(rlutil::RED);
        cout << "NO HAY COMPRAS ELIMINADAS.\n";
        rlutil::setColor(rlutil::WHITE);
        return false;
    }

    return true;
}

//  CONSULTA DE COMPRADETALLE

bool CompraManager::listarDetalles() {
    int cantidad = _repoDetalle.getCantidadRegistros();
    bool hay = false;

    for (int i = 0; i < cantidad; i++) {
        CompraDetalle reg = _repoDetalle.leer(i);
        if (!reg.getEliminado()) {
            if (!hay) { cout << "LISTADO DE DETALLES DE COMPRA:\n"; hay = true; }
            reg.Mostrar();
        }
    }

    if (!hay) {
        rlutil::setColor(rlutil::RED);
        cout << "NO HAY DETALLES DE COMPRA CARGADOS.\n";
        rlutil::setColor(rlutil::WHITE);
    }
    return hay;
}

bool CompraManager::listarDetallesPorCompra(int idCompra) {
    int cantidad = _repoDetalle.getCantidadRegistros();
    bool hay = false;

    for (int i = 0; i < cantidad; i++) {
        CompraDetalle reg = _repoDetalle.leer(i);
        if (!reg.getEliminado() && reg.getIdCompra() == idCompra) {
            if (!hay) { cout << "LISTADO DE DETALLES (compra ID " << idCompra << "):\n"; hay = true; }
            reg.Mostrar();
        }
    }

    if (!hay) {
        rlutil::setColor(rlutil::RED);
        cout << "NO HAY DETALLES PARA ESA COMPRA.\n";
        rlutil::setColor(rlutil::WHITE);
    }
    return hay;
}

bool CompraManager::listarDetallesPorProducto(int idProducto) {
    int cantidad = _repoDetalle.getCantidadRegistros();
    bool hay = false;

    for (int i = 0; i < cantidad; i++) {
        CompraDetalle reg = _repoDetalle.leer(i);
        if (!reg.getEliminado() && reg.getIdProducto() == idProducto) {
            if (!hay) { cout << "LISTADO DE DETALLES (producto ID " << idProducto << "):\n"; hay = true; }
            reg.Mostrar();
        }
    }

    if (!hay) {
        rlutil::setColor(rlutil::RED);
        cout << "NO HAY DETALLES PARA ESE PRODUCTO.\n";
        rlutil::setColor(rlutil::WHITE);
    }
    return hay;
}

//  CONSULTA DE COMPRAS

bool CompraManager::listarComprasPorRangoFechas(Fecha desde, Fecha hasta) {
    int cantidad = _repo.getCantidadRegistros();
    int ini = fechaToInt(desde);
    int fin = fechaToInt(hasta);
    bool hay = false;

    for (int i = 0; i < cantidad; i++) {
        Compra reg = _repo.leer(i);
        if (reg.getEliminado()) continue;

        int f = fechaToInt(reg.getFechaCompra());
        if (f >= ini && f <= fin) {
            if (!hay) { cout << "LISTADO DE COMPRAS (por rango de fechas):\n"; hay = true; }
            reg.Mostrar();
        }
    }

    if (!hay) {
        rlutil::setColor(rlutil::RED);
        cout << "NO HAY COMPRAS EN ESE RANGO DE FECHAS.\n";
        rlutil::setColor(rlutil::WHITE);
    }
    return hay;
}

bool CompraManager::listarComprasPorMarca(const char* marca) {
    ProductoArchivo repoProd;
    int cantCompra = _repo.getCantidadRegistros();
    int cantDet = _repoDetalle.getCantidadRegistros();
    bool hay = false;

    for (int i = 0; i < cantCompra; i++) {
        Compra c = _repo.leer(i);
        if (c.getEliminado()) continue;

        bool coincide = false;
        for (int j = 0; j < cantDet && !coincide; j++) {
            CompraDetalle d = _repoDetalle.leer(j);
            if (d.getEliminado() || d.getIdCompra() != c.getIdCompra()) continue;

            int posProd = repoProd.buscarPorId(d.getIdProducto(), true);
            if (posProd == -1) continue;

            Producto p = repoProd.leer(posProd);
            if (strcmp(p.getMarca(), marca) == 0) coincide = true;
        }

        if (coincide) {
            if (!hay) { cout << "LISTADO DE COMPRAS (marca: " << marca << "):\n"; hay = true; }
            c.Mostrar();
        }
    }

    if (!hay) {
        rlutil::setColor(rlutil::RED);
        cout << "NO HAY COMPRAS PARA ESA MARCA.\n";
        rlutil::setColor(rlutil::WHITE);
    }
    return hay;
}

bool CompraManager::listarComprasPorProveedor(int idProveedor) {
    int cantidad = _repo.getCantidadRegistros();
    bool hay = false;

    for (int i = 0; i < cantidad; i++) {
        Compra reg = _repo.leer(i);
        if (!reg.getEliminado() && reg.getIdProveedor() == idProveedor) {
            if (!hay) { cout << "LISTADO DE COMPRAS (proveedor ID " << idProveedor << "):\n"; hay = true; }
            reg.Mostrar();
        }
    }

    if (!hay) {
        rlutil::setColor(rlutil::RED);
        cout << "NO HAY COMPRAS PARA ESE PROVEEDOR.\n";
        rlutil::setColor(rlutil::WHITE);
    }
    return hay;
}

bool CompraManager::listarComprasPorEmpleado(int idEmpleado) {
    int cantidad = _repo.getCantidadRegistros();
    bool hay = false;

    for (int i = 0; i < cantidad; i++) {
        Compra reg = _repo.leer(i);
        if (!reg.getEliminado() && reg.getIdEmpleado() == idEmpleado) {
            if (!hay) { cout << "LISTADO DE COMPRAS (empleado ID " << idEmpleado << "):\n"; hay = true; }
            reg.Mostrar();
        }
    }

    if (!hay) {
        rlutil::setColor(rlutil::RED);
        cout << "NO HAY COMPRAS PARA ESE EMPLEADO.\n";
        rlutil::setColor(rlutil::WHITE);
    }
    return hay;
}
