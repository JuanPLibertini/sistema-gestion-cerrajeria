#include "ProveedorArchivo.h"
#include <cstdio>

ProveedorArchivo::ProveedorArchivo(std::string nombreArchivo) {
    _nombreArchivo = nombreArchivo;
}

bool ProveedorArchivo::guardar(Proveedor reg) {
    FILE* p = fopen(_nombreArchivo.c_str(), "ab");
    if (p == NULL) return false;
    bool ok = fwrite(&reg, sizeof(Proveedor), 1, p) == 1;
    fclose(p);
    return ok;
}

bool ProveedorArchivo::modificar(Proveedor reg, int pos) {
    FILE* p = fopen(_nombreArchivo.c_str(), "rb+");
    if (p == NULL) return false;
    fseek(p, pos * sizeof(Proveedor), SEEK_SET);
    bool ok = fwrite(&reg, sizeof(Proveedor), 1, p) == 1;
    fclose(p);
    return ok;
}

Proveedor ProveedorArchivo::leer(int pos) {
    FILE* p = fopen(_nombreArchivo.c_str(), "rb");
    Proveedor reg;
    if (p == NULL) return reg;
    fseek(p, pos * sizeof(Proveedor), SEEK_SET);
    fread(&reg, sizeof(Proveedor), 1, p);
    fclose(p);
    return reg;
}

int ProveedorArchivo::getCantidadRegistros() {
    FILE* p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) return 0;
    fseek(p, 0, SEEK_END);
    int cant = ftell(p) / sizeof(Proveedor);
    fclose(p);
    return cant;
}

int ProveedorArchivo::buscarPorId(int id, bool incluirEliminados) {
    int cantidad = getCantidadRegistros();
    for (int i = 0; i < cantidad; i++) {
        Proveedor reg = leer(i);
        if (reg.getIdProveedor() == id && (incluirEliminados || !reg.getEliminado())) {
            return i;
        }
    }
    return -1;
}

int ProveedorArchivo::obtenerProximoId() {
    int cantidad = getCantidadRegistros();
    int mayorId = 0;
    for (int i = 0; i < cantidad; i++) {
        Proveedor reg = leer(i);
        if (reg.getIdProveedor() > mayorId) {
            mayorId = reg.getIdProveedor();
        }
    }
    return mayorId + 1;
}
