#include "VentaArchivo.h"
#include <cstdio>

VentaArchivo::VentaArchivo(std::string nombreArchivo) {
    _nombreArchivo = nombreArchivo;
}

bool VentaArchivo::guardar(Venta reg) {
    FILE* p = fopen(_nombreArchivo.c_str(), "ab");
    if (p == NULL) return false;

    bool ok = fwrite(&reg, sizeof(Venta), 1, p) == 1;
    fclose(p);
    return ok;
}

int VentaArchivo::buscarPorId(int id, bool incluirEliminados) const {
    int cantidad = getCantidadRegistros();

    for (int i = 0; i < cantidad; i++) {
        Venta reg = leer(i);
        if (reg.getIdVenta() == id && (incluirEliminados || !reg.getEliminado())) {
            return i;
        }
    }

    return -1;
}

bool VentaArchivo::modificar(Venta reg, int pos) {
    FILE* p = fopen(_nombreArchivo.c_str(), "rb+");
    if (p == NULL) return false;

    fseek(p, pos * sizeof(Venta), SEEK_SET);
    bool ok = fwrite(&reg, sizeof(Venta), 1, p) == 1;
    fclose(p);
    return ok;
}

Venta VentaArchivo::leer(int pos) const {
    FILE* p = fopen(_nombreArchivo.c_str(), "rb");
    Venta reg;
    if (p == NULL) return reg;

    fseek(p, pos * sizeof(Venta), SEEK_SET);
    fread(&reg, sizeof(Venta), 1, p);
    fclose(p);
    return reg;
}

int VentaArchivo::obtenerProximoId() const {
    int cantidad = getCantidadRegistros();
    int mayorId = 0;

    for (int i = 0; i < cantidad; i++) {
        Venta reg = leer(i);
        if (reg.getIdVenta() > mayorId) {
            mayorId = reg.getIdVenta();
        }
    }

    return mayorId + 1;
}

int VentaArchivo::getCantidadRegistros() const {
    FILE* p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) return 0;

    fseek(p, 0, SEEK_END);
    int cant = ftell(p) / sizeof(Venta);
    fclose(p);
    return cant;
}
