#include "VentaDetalleArchivo.h"
#include <cstdio>

VentaDetalleArchivo::VentaDetalleArchivo(std::string nombreArchivo) {
    _nombreArchivo = nombreArchivo;
}

bool VentaDetalleArchivo::guardar(VentaDetalle reg) {
    FILE* p = fopen(_nombreArchivo.c_str(), "ab");
    if (p == NULL) return false;

    bool ok = fwrite(&reg, sizeof(VentaDetalle), 1, p) == 1;
    fclose(p);
    return ok;
}

bool VentaDetalleArchivo::modificar(VentaDetalle reg, int pos) {
    FILE* p = fopen(_nombreArchivo.c_str(), "rb+");
    if (p == NULL) return false;

    fseek(p, pos * sizeof(VentaDetalle), SEEK_SET);
    bool ok = fwrite(&reg, sizeof(VentaDetalle), 1, p) == 1;
    fclose(p);
    return ok;
}

VentaDetalle VentaDetalleArchivo::leer(int pos) const {
    FILE* p = fopen(_nombreArchivo.c_str(), "rb");
    VentaDetalle reg;
    if (p == NULL) return reg;

    fseek(p, pos * sizeof(VentaDetalle), SEEK_SET);
    fread(&reg, sizeof(VentaDetalle), 1, p);
    fclose(p);
    return reg;
}

int VentaDetalleArchivo::getCantidadRegistros() const {
    FILE* p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) return 0;

    fseek(p, 0, SEEK_END);
    int cant = ftell(p) / sizeof(VentaDetalle);
    fclose(p);
    return cant;
}
