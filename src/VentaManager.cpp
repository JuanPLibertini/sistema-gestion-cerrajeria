#include <iostream>
#include <cstring>
#include "VentaManager.h"
#include "ProductoArchivo.h"
#include "ClienteArchivo.h"
#include "EmpleadoArchivo.h"
#include "rlutil.h"
#include "MenuVenta.h"
#include "utilidades.h"

using namespace std;

// Helper local para comparar fechas como entero (AAAAMMDD)
static int fechaToInt(const Fecha& f) {
    return f.getAnio() * 10000 + f.getMes() * 100 + f.getDia();
}

VentaManager::VentaManager() {}

void VentaManager::altaVenta() {
    Venta venta;
    int nuevoId = _repo.obtenerProximoId();
    venta.setIdVenta(nuevoId);

    rlutil::cls();
    cout << "\nALTA DE VENTA\n";
    cout << "---------------------------\n";
    cout << "ID de la venta: " << nuevoId << "\n";

    if (!venta.Cargar()) {
        rlutil::setColor(rlutil::RED);
        cout << "OPERACION CANCELADA.\n";
        rlutil::setColor(rlutil::WHITE);
        return;
    }

    const int MAX_ITEMS = 100;
    VentaDetalle detalles[MAX_ITEMS];
    int cantDetalles = 0;
    VentaServicio servicios[MAX_ITEMS];
    int cantServicios = 0;

    float totalAcumulado = 0;
    int opcion;

    do {
        rlutil::cls();
        cout << "\n--- VENTA ID " << nuevoId << " (total actual: $" << totalAcumulado << ") ---\n\n";

        if (cantDetalles + cantServicios == 0) {
            cout << "(Sin items agregados aun)\n";
        } else {
            cout << "Items agregados:\n";
            int n = 1;
            for (int i = 0; i < cantDetalles; i++) {
                cout << "  " << n++ << ") Producto ID " << detalles[i].getIdProducto()
                     << " x" << detalles[i].getCantidad()
                     << " = $" << (detalles[i].getCantidad() * detalles[i].getPrecioUnitario()) << "\n";
            }
            for (int i = 0; i < cantServicios; i++) {
                cout << "  " << n++ << ") Servicio ID " << servicios[i].getIdServicio()
                     << " = $" << servicios[i].getTotal() << "\n";
            }
        }

        cout << "\n1) Agregar producto\n";
        cout << "2) Agregar servicio\n";
        cout << "3) Quitar un item agregado\n";
        cout << "4) Finalizar venta\n";
        cout << "0) Cancelar venta\n";
        cout << "Opcion: ";
        opcion = leerOpcion();

        switch (opcion) {
            case 1: {
                if (cantDetalles >= MAX_ITEMS) {
                    rlutil::setColor(rlutil::RED);
                    cout << "Limite de items alcanzado.\n";
                    rlutil::setColor(rlutil::WHITE);
                } else {
                    VentaDetalle det;
                    if (det.Cargar()) {
                        det.setIdVenta(nuevoId);
                        detalles[cantDetalles++] = det;
                        totalAcumulado += det.getPrecioUnitario() * det.getCantidad();
                        rlutil::setColor(rlutil::GREEN);
                        cout << "Producto agregado a la venta.\n";
                        rlutil::setColor(rlutil::WHITE);
                    }
                }
                cout << "\nPresione ENTER para continuar...";
                cin.ignore();
                break;
            }
            case 2: {
                if (cantServicios >= MAX_ITEMS) {
                    rlutil::setColor(rlutil::RED);
                    cout << "Limite de items alcanzado.\n";
                    rlutil::setColor(rlutil::WHITE);
                } else {
                    VentaServicio vs;
                    if (vs.Cargar()) {
                        vs.setIdVenta(nuevoId);
                        vs.setIdCliente(venta.getIdCliente());
                        vs.setFecha(venta.getFecha());
                        servicios[cantServicios++] = vs;
                        totalAcumulado += vs.getTotal();
                        rlutil::setColor(rlutil::GREEN);
                        cout << "Servicio agregado a la venta.\n";
                        rlutil::setColor(rlutil::WHITE);
                    }
                }
                cout << "\nPresione ENTER para continuar...";
                cin.ignore();
                break;
            }
            case 3: {
                int totalItems = cantDetalles + cantServicios;
                if (totalItems == 0) {
                    rlutil::setColor(rlutil::RED);
                    cout << "No HAY items para quitar.\n";
                    rlutil::setColor(rlutil::WHITE);
                } else {
                    cout << "Ingrese el numero del item a quitar (0 para cancelar): ";
                    int idx = leerOpcion();
                    if (idx == 0) {

                    } else if (idx >= 1 && idx <= totalItems) {
                        if (idx <= cantDetalles) {
                            int i = idx - 1;
                            totalAcumulado -= detalles[i].getPrecioUnitario() * detalles[i].getCantidad();
                            for (int j = i; j < cantDetalles - 1; j++) detalles[j] = detalles[j+1];
                            cantDetalles--;
                        } else {
                            int i = idx - 1 - cantDetalles;
                            totalAcumulado -= servicios[i].getTotal();
                            for (int j = i; j < cantServicios - 1; j++) servicios[j] = servicios[j+1];
                            cantServicios--;
                        }
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
            case 4:
                break;
            case 0:
                rlutil::setColor(rlutil::RED);
                cout << "OPERACION CANCELADA.\n";
                rlutil::setColor(rlutil::WHITE);
                return;
            default:
                rlutil::setColor(rlutil::RED);
                cout << "Opcion invalida.\n";
                rlutil::setColor(rlutil::WHITE);
                cout << "\nPresione ENTER para continuar...";
                cin.ignore();
                break;
        }
    } while (opcion != 4);

    venta.setTotal(totalAcumulado);

    if (!_repo.guardar(venta)) {
        rlutil::setColor(rlutil::RED);
        cout << "Error al guardar la venta.\n";
        rlutil::setColor(rlutil::WHITE);
        return;
    }

    ProductoArchivo repoProd;
    for (int i = 0; i < cantDetalles; i++) {
        _repoDetalle.guardar(detalles[i]);
        int pos = repoProd.buscarPorId(detalles[i].getIdProducto());
        if (pos != -1) {
            Producto p = repoProd.leer(pos);
            p.setStock(p.getStock() - detalles[i].getCantidad());
            repoProd.modificar(p, pos);
        }
    }
    for (int i = 0; i < cantServicios; i++) {
        _repoServicio.guardar(servicios[i]);
    }

    rlutil::setColor(rlutil::GREEN);
    cout << "\nVENTA GUARDADA EN ARCHIVO!!! Total: $" << totalAcumulado << "\n";
    rlutil::setColor(rlutil::WHITE);
}

bool VentaManager::listarVenta() {
    int cantidad = _repo.getCantidadRegistros();
    bool hayActivosActivos = false;

    for (int i = 0; i < cantidad; i++) {
        Venta reg = _repo.leer(i);
        if (!reg.getEliminado()) {
            if (!hayActivosActivos) {
                cout << "LISTADO DE VENTAS:\n";
                hayActivosActivos = true;
            }
            reg.Mostrar();
        }
    }

    if (!hayActivosActivos) {
        rlutil::setColor(rlutil::RED);
        cout << "NO HAY VENTAS CARGADAS.\n";
        rlutil::setColor(rlutil::WHITE);
        return false;
    }
    return true;
}

bool VentaManager::bajaVenta(int id) {
    int pos = _repo.buscarPorId(id);
    if (pos == -1) return false;

    Venta reg = _repo.leer(pos);
    reg.setEliminado(true);
    return _repo.modificar(reg, pos);
}

bool VentaManager::existeVenta(int id) {
    return _repo.buscarPorId(id) != -1;
}

bool VentaManager::reactivarVenta(int id) {
    if (id <= 0) return false;
    int pos = _repo.buscarPorId(id, true);
    if (pos == -1) return false;

    Venta reg = _repo.leer(pos);
    if (!reg.getEliminado()) return false;

    reg.setEliminado(false);
    return _repo.modificar(reg, pos);
}

bool VentaManager::listarVentaEliminada() {
    rlutil::cls();
    int cantidad = _repo.getCantidadRegistros();
    bool hayEliminados = false;

    for (int i = 0; i < cantidad; i++) {
        Venta reg = _repo.leer(i);

        if (reg.getEliminado()) {
            if (!hayEliminados) {
                cout << "LISTADO DE VENTAS ELIMINADAS:\n";
                hayEliminados = true;
            }
            reg.Mostrar(true);
        }
    }

    if (!hayEliminados) {
        rlutil::setColor(rlutil::RED);
        cout << "NO HAY VENTAS ELIMINADAS.\n";
        rlutil::setColor(rlutil::WHITE);
        return false;
    }

    return true;
}

void VentaManager::modificarVenta() {
    if (!listarVenta()) return;

    int id, pos;
    while (true) {
        cout << "\nIngrese ID de la venta a modificar (0 para salir): ";
        cin >> id;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            rlutil::setColor(rlutil::RED);
            cout << "Entrada invalida. Debe ingresar un numero.\n";
            rlutil::setColor(rlutil::WHITE);
            continue;
        }
        cin.ignore(1000, '\n');

        if (id == 0) {
            rlutil::setColor(rlutil::RED);
            cout << "OPERACION CANCELADA\n";
            rlutil::setColor(rlutil::WHITE);
            return;
        }

        pos = _repo.buscarPorId(id);
        if (pos == -1) {
            rlutil::setColor(rlutil::RED);
            cout << "Venta no encontrada.\n";
            rlutil::setColor(rlutil::WHITE);
            continue;
        }
        break;
    }

    Venta reg = _repo.leer(pos);
    int opcion;
    do {
        rlutil::cls();
        cout << "\n--- MODIFICAR VENTA ID " << id << " ---\n";
        cout << "1) ID Cliente  [" << reg.getIdCliente() << "]\n";
        cout << "2) ID Empleado [" << reg.getIdEmpleado() << "]\n";
        cout << "3) Fecha       "; reg.getFecha().Mostrar(); cout << "\n";
        cout << "4) Guardar cambios\n";
        cout << "0) Cancelar\n";
        cout << "Opcion: ";
        opcion = leerOpcion();

        switch (opcion) {
            case 1: {
            ClienteArchivo repoClie;

            cout << "\nLISTADO DE CLIENTES\n";
            cout << "----------------------\n";

            for (int i = 0; i < repoClie.getCantidadRegistros(); i++) {
                Cliente c = repoClie.leer(i);

                if (!c.getEliminado()) {
                    cout << "ID: " << c.getIdCliente()
                            << " - " << c.getNombre() << " " << c.getApellido() << endl;
                }
            }

            int idClie;
            cout << "\nNuevo ID cliente: ";
            cin >> idClie;
            limpiarEntrada();

            if (repoClie.buscarPorId(idClie) != -1) {
                reg.setIdCliente(idClie);
            }
            else {
                rlutil::setColor(rlutil::RED);
                cout << "Cliente inexistente.\n";
                rlutil::setColor(rlutil::WHITE);
                pausa();
            }
        }
        break;

            case 2: {
            EmpleadoArchivo repoEmp;

            cout << "\nLISTADO DE EMPLEADOS\n";
            cout << "----------------------\n";

            for (int i = 0; i < repoEmp.getCantidadRegistros(); i++) {
                Empleado e = repoEmp.leer(i);

                if (!e.getEliminado()) {
                    cout << "ID: " << e.getIdEmpleado()
                            << " - " << e.getNombre() << " " << e.getApellido() << endl;
                }
            }

            int idEmp;
            cout << "\nNuevo ID empleado: ";
            cin >> idEmp;
            cin.ignore();

            if (repoEmp.buscarPorId(idEmp) != -1) {
                reg.setIdEmpleado(idEmp);
            }
            else {
                rlutil::setColor(rlutil::RED);
                cout << "Empleado inexistente.\n";
                rlutil::setColor(rlutil::WHITE);
                pausa();
            }
        }
        break;

            case 3: {
                int d, m, a;
                cout << "Nueva fecha (dd mm aaaa): ";
                cin >> d >> m >> a;
                cin.ignore(1000, '\n');
                reg.setFecha(Fecha(d, m, a));
                break;
            }
            case 4:
                if (_repo.modificar(reg, pos)) {
                    rlutil::setColor(rlutil::GREEN);
                    cout << "VENTA MODIFICADA CORRECTAMENTE.\n";
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

bool VentaManager::listarDetalles() {
    int cantidad = _repoDetalle.getCantidadRegistros();
    bool hayActivos = false;

    for (int i = 0; i < cantidad; i++) {
        VentaDetalle reg = _repoDetalle.leer(i);
        if (!reg.getEliminado()) {
            if (!hayActivos) { cout << "LISTADO DE DETALLES DE VENTA:\n"; hayActivos = true; }
            reg.Mostrar();
        }
    }

    if (!hayActivos) {
        rlutil::setColor(rlutil::RED);
        cout << "NO HAY DETALLES DE VENTA CARGADOS.\n";
        rlutil::setColor(rlutil::WHITE);
    }
    return hayActivos;
}

bool VentaManager::listarServicios() {
    int cantidad = _repoServicio.getCantidadRegistros();
    bool hayActivos = false;

    for (int i = 0; i < cantidad; i++) {
        VentaServicio reg = _repoServicio.leer(i);
        if (!reg.getEliminado()) {
            if (!hayActivos) { cout << "LISTADO DE SERVICIOS VENDIDOS:\n"; hayActivos = true; }
            reg.Mostrar();
        }
    }

    if (!hayActivos) {
        rlutil::setColor(rlutil::RED);
        cout << "NO HAY SERVICIOS VENDIDOS CARGADOS.\n";
        rlutil::setColor(rlutil::WHITE);
    }
    return hayActivos;
}

// ---------------------- CONSULTA DE VENTAS ----------------------

bool VentaManager::listarVentasPorRangoFechas(Fecha desde, Fecha hasta) {
    int cantidad = _repo.getCantidadRegistros();
    int ini = fechaToInt(desde);
    int fin = fechaToInt(hasta);
    bool hayActivos = false;

    for (int i = 0; i < cantidad; i++) {
        Venta reg = _repo.leer(i);
        if (reg.getEliminado()) continue;

        int f = fechaToInt(reg.getFecha());
        if (f >= ini && f <= fin) {
            if (!hayActivos) { cout << "LISTADO DE VENTAS (por rango de fechas):\n"; hayActivos = true; }
            reg.Mostrar();
        }
    }

    if (!hayActivos) {
        rlutil::setColor(rlutil::RED);
        cout << "NO HAY VENTAS EN ESE RANGO DE FECHAS.\n";
        rlutil::setColor(rlutil::WHITE);
    }
    return hayActivos;
}

bool VentaManager::listarVentasPorMarca(const char* marca) {
    ProductoArchivo repoProd;
    int cantVenta = _repo.getCantidadRegistros();
    int cantDet = _repoDetalle.getCantidadRegistros();
    bool hayActivos = false;

    for (int i = 0; i < cantVenta; i++) {
        Venta v = _repo.leer(i);
        if (v.getEliminado()) continue;

        bool coincide = false;
        for (int j = 0; j < cantDet && !coincide; j++) {
            VentaDetalle d = _repoDetalle.leer(j);
            if (d.getEliminado() || d.getIdVenta() != v.getIdVenta()) continue;

            int posProd = repoProd.buscarPorId(d.getIdProducto(), true);
            if (posProd == -1) continue;

            Producto p = repoProd.leer(posProd);
            if (strcmp(p.getMarca(), marca) == 0) coincide = true;
        }

        if (coincide) {
            if (!hayActivos) { cout << "LISTADO DE VENTAS (marca: " << marca << "):\n"; hayActivos = true; }
            v.Mostrar();
        }
    }

    if (!hayActivos) {
        rlutil::setColor(rlutil::RED);
        cout << "NO HAY VENTAS PARA ESA MARCA.\n";
        rlutil::setColor(rlutil::WHITE);
    }
    return hayActivos;
}

bool VentaManager::listarVentasPorCliente(int idCliente) {
    int cantidad = _repo.getCantidadRegistros();
    bool hayActivos = false;

    for (int i = 0; i < cantidad; i++) {
        Venta reg = _repo.leer(i);
        if (!reg.getEliminado() && reg.getIdCliente() == idCliente) {
            if (!hayActivos) { cout << "LISTADO DE VENTAS (cliente ID " << idCliente << "):\n"; hayActivos = true; }
            reg.Mostrar();
        }
    }

    if (!hayActivos) {
        rlutil::setColor(rlutil::RED);
        cout << "NO HAY VENTAS PARA ESE CLIENTE.\n";
        rlutil::setColor(rlutil::WHITE);
    }
    return hayActivos;
}

bool VentaManager::listarVentasPorEmpleado(int idEmpleado) {
    int cantidad = _repo.getCantidadRegistros();
    bool hayActivos = false;

    for (int i = 0; i < cantidad; i++) {
        Venta reg = _repo.leer(i);
        if (!reg.getEliminado() && reg.getIdEmpleado() == idEmpleado) {
            if (!hayActivos) { cout << "LISTADO DE VENTAS (empleado ID " << idEmpleado << "):\n"; hayActivos = true; }
            reg.Mostrar();
        }
    }

    if (!hayActivos) {
        rlutil::setColor(rlutil::RED);
        cout << "NO HAY VENTAS PARA ESE EMPLEADO.\n";
        rlutil::setColor(rlutil::WHITE);
    }
    return hayActivos;
}

// ---------------------- LISTADO DE VENTAS ----------------------

void VentaManager::listarOrdenadoPorFecha() {
    int cantidad = _repo.getCantidadRegistros();
    Venta temp[500];
    int activos = 0;

    for (int i = 0; i < cantidad; i++) {
        Venta reg = _repo.leer(i);
        if (!reg.getEliminado()) temp[activos++] = reg;
    }

    if (activos == 0) {
        rlutil::setColor(rlutil::RED);
        cout << "NO HAY VENTAS CARGADAS.\n";
        rlutil::setColor(rlutil::WHITE);
        return;
    }

    for (int i = 0; i < activos - 1; i++)
        for (int j = 0; j < activos - i - 1; j++)
            if (fechaToInt(temp[j].getFecha()) > fechaToInt(temp[j+1].getFecha())) {
                Venta aux = temp[j];
                temp[j] = temp[j+1];
                temp[j+1] = aux;
            }

    cout << "LISTADO DE VENTAS (por fecha):\n";
    for (int i = 0; i < activos; i++) temp[i].MostrarPorFecha();
}

void VentaManager::listarOrdenadoPorCliente() {
    int cantidad = _repo.getCantidadRegistros();
    Venta temp[500];
    int activos = 0;

    for (int i = 0; i < cantidad; i++) {
        Venta reg = _repo.leer(i);
        if (!reg.getEliminado()) temp[activos++] = reg;
    }

    if (activos == 0) {
        rlutil::setColor(rlutil::RED);
        cout << "NO HAY VENTAS CARGADAS.\n";
        rlutil::setColor(rlutil::WHITE);
        return;
    }

    for (int i = 0; i < activos - 1; i++)
        for (int j = 0; j < activos - i - 1; j++)
            if (temp[j].getIdCliente() > temp[j+1].getIdCliente()) {
                Venta aux = temp[j];
                temp[j] = temp[j+1];
                temp[j+1] = aux;
            }

    cout << "LISTADO DE VENTAS (por cliente):\n";
    for (int i = 0; i < activos; i++) temp[i].MostrarPorCliente();
}

// ---------------------- CONSULTA DE VENTADETALLE ----------------------

bool VentaManager::listarDetallesPorVenta(int idVenta) {
    int cantidad = _repoDetalle.getCantidadRegistros();
    bool hayActivos = false;

    for (int i = 0; i < cantidad; i++) {
        VentaDetalle reg = _repoDetalle.leer(i);
        if (!reg.getEliminado() && reg.getIdVenta() == idVenta) {
            if (!hayActivos) { cout << "LISTADO DE DETALLES (venta ID " << idVenta << "):\n"; hayActivos = true; }
            reg.Mostrar();
        }
    }

    if (!hayActivos) {
        rlutil::setColor(rlutil::RED);
        cout << "NO HAY DETALLES PARA ESA VENTA.\n";
        rlutil::setColor(rlutil::WHITE);
    }
    return hayActivos;
}

bool VentaManager::listarDetallesPorProducto(int idProducto) {
    int cantidad = _repoDetalle.getCantidadRegistros();
    bool hayActivos = false;

    for (int i = 0; i < cantidad; i++) {
        VentaDetalle reg = _repoDetalle.leer(i);
        if (!reg.getEliminado() && reg.getIdProducto() == idProducto) {
            if (!hayActivos) { cout << "LISTADO DE DETALLES (producto ID " << idProducto << "):\n"; hayActivos = true; }
            reg.Mostrar();
        }
    }

    if (!hayActivos) {
        rlutil::setColor(rlutil::RED);
        cout << "NO HAY DETALLES PARA ESE PRODUCTO.\n";
        rlutil::setColor(rlutil::WHITE);
    }
    return hayActivos;
}

// ---------------------- CONSULTA DE VENTASERVICIO ----------------------

bool VentaManager::listarServiciosVentaPorCliente(int idCliente) {
    int cantidad = _repoServicio.getCantidadRegistros();
    bool hayActivos = false;

    for (int i = 0; i < cantidad; i++) {
        VentaServicio reg = _repoServicio.leer(i);
        if (!reg.getEliminado() && reg.getIdCliente() == idCliente) {
            if (!hayActivos) { cout << "LISTADO DE SERVICIOS VENDIDOS (cliente ID " << idCliente << "):\n"; hayActivos = true; }
            reg.Mostrar();
        }
    }

    if (!hayActivos) {
        rlutil::setColor(rlutil::RED);
        cout << "NO HAY SERVICIOS VENDIDOS PARA ESE CLIENTE.\n";
        rlutil::setColor(rlutil::WHITE);
    }
    return hayActivos;
}

bool VentaManager::listarServiciosVentaPorServicio(int idServicio) {
    int cantidad = _repoServicio.getCantidadRegistros();
    bool hayActivos = false;

    for (int i = 0; i < cantidad; i++) {
        VentaServicio reg = _repoServicio.leer(i);
        if (!reg.getEliminado() && reg.getIdServicio() == idServicio) {
            if (!hayActivos) { cout << "LISTADO DE SERVICIOS VENDIDOS (servicio ID " << idServicio << "):\n"; hayActivos = true; }
            reg.Mostrar();
        }
    }

    if (!hayActivos) {
        rlutil::setColor(rlutil::RED);
        cout << "NO HAY VENTAS PARA ESE SERVICIO.\n";
        rlutil::setColor(rlutil::WHITE);
    }
    return hayActivos;
}

bool VentaManager::listarServiciosVentaPorRangoFechas(Fecha desde, Fecha hasta) {
    int cantidad = _repoServicio.getCantidadRegistros();
    int ini = fechaToInt(desde);
    int fin = fechaToInt(hasta);
    bool hayActivos = false;

    for (int i = 0; i < cantidad; i++) {
        VentaServicio reg = _repoServicio.leer(i);
        if (reg.getEliminado()) continue;

        int f = fechaToInt(reg.getFecha());
        if (f >= ini && f <= fin) {
            if (!hayActivos) { cout << "LISTADO DE SERVICIOS VENDIDOS (por rango de fechas):\n"; hayActivos = true; }
            reg.Mostrar();
        }
    }

    if (!hayActivos) {
        rlutil::setColor(rlutil::RED);
        cout << "NO HAY SERVICIOS VENDIDOS EN ESE RANGO DE FECHAS.\n";
        rlutil::setColor(rlutil::WHITE);
    }
    return hayActivos;
}
