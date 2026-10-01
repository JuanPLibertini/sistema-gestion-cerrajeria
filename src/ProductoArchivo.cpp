#include "ProductoArchivo.h"
#include <cstdio>

ProductoArchivo::ProductoArchivo(std::string nombreArchivo) {
    _nombreArchivo = nombreArchivo;
}

bool ProductoArchivo::guardar(Producto reg) {
    FILE* p = fopen(_nombreArchivo.c_str(), "ab");
    if (p == NULL) return false;

    bool ok = fwrite(&reg, sizeof(Producto), 1, p) == 1;
    fclose(p);
    return ok;
}

int ProductoArchivo::buscarPorId(int id, bool incluirEliminados) const {
    int cantidad = getCantidadRegistros();

    for (int i = 0; i < cantidad; i++) {
        Producto reg = leer(i);
        if (reg.getIdProducto() == id && (incluirEliminados || !reg.getEliminado())) {
            return i;
        }
    }

    return -1;
}

bool ProductoArchivo::modificar(Producto reg, int pos) {
    FILE* p = fopen(_nombreArchivo.c_str(), "rb+");
    if (p == NULL) return false;

    fseek(p, pos * sizeof(Producto), SEEK_SET);
    bool ok = fwrite(&reg, sizeof(Producto), 1, p) == 1;
    fclose(p);
    return ok;
}

Producto ProductoArchivo::leer(int pos) const {
    FILE* p = fopen(_nombreArchivo.c_str(), "rb");
    Producto reg;
    if (p == NULL) return reg;

    fseek(p, pos * sizeof(Producto), SEEK_SET);
    fread(&reg, sizeof(Producto), 1, p);
    fclose(p);
    return reg;
}

int ProductoArchivo::obtenerProximoId() const {
    int cantidad = getCantidadRegistros();
    int mayorId = 0;

    for (int i = 0; i < cantidad; i++) {
        Producto reg = leer(i);
        if (reg.getIdProducto() > mayorId) {
            mayorId = reg.getIdProducto();
        }
    }

    return mayorId + 1;
}

int ProductoArchivo::getCantidadRegistros() const {
    FILE* p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) return 0;

    fseek(p, 0, SEEK_END);
    int cant = ftell(p) / sizeof(Producto);
    fclose(p);
    return cant;
}
