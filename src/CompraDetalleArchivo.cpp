#include "CompraDetalleArchivo.h"
#include <cstdio>

CompraDetalleArchivo::CompraDetalleArchivo(std::string nombreArchivo) {
    _nombreArchivo = nombreArchivo;
}

bool CompraDetalleArchivo::guardar(CompraDetalle reg) {
    FILE* p = fopen(_nombreArchivo.c_str(), "ab");
    if (p == NULL) return false;

    bool ok = fwrite(&reg, sizeof(CompraDetalle), 1, p) == 1;
    fclose(p);
    return ok;
}

bool CompraDetalleArchivo::modificar(CompraDetalle reg, int pos) {
    FILE* p = fopen(_nombreArchivo.c_str(), "rb+");
    if (p == NULL) return false;

    fseek(p, pos * sizeof(CompraDetalle), SEEK_SET);
    bool ok = fwrite(&reg, sizeof(CompraDetalle), 1, p) == 1;
    fclose(p);
    return ok;
}

CompraDetalle CompraDetalleArchivo::leer(int pos) const {
    FILE* p = fopen(_nombreArchivo.c_str(), "rb");
    CompraDetalle reg;
    if (p == NULL) return reg;

    fseek(p, pos * sizeof(CompraDetalle), SEEK_SET);
    fread(&reg, sizeof(CompraDetalle), 1, p);
    fclose(p);
    return reg;
}

int CompraDetalleArchivo::getCantidadRegistros() const {
    FILE* p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) return 0;

    fseek(p, 0, SEEK_END);
    int cant = ftell(p) / sizeof(CompraDetalle);
    fclose(p);
    return cant;
}
