#include "VentaServicioArchivo.h"
#include <cstdio>

VentaServicioArchivo::VentaServicioArchivo(std::string nombreArchivo) {
    _nombreArchivo = nombreArchivo;
}

bool VentaServicioArchivo::guardar(VentaServicio reg) {
    FILE* p = fopen(_nombreArchivo.c_str(), "ab");
    if (p == NULL) return false;

    bool ok = fwrite(&reg, sizeof(VentaServicio), 1, p) == 1;
    fclose(p);
    return ok;
}

bool VentaServicioArchivo::modificar(VentaServicio reg, int pos) {
    FILE* p = fopen(_nombreArchivo.c_str(), "rb+");
    if (p == NULL) return false;

    fseek(p, pos * sizeof(VentaServicio), SEEK_SET);
    bool ok = fwrite(&reg, sizeof(VentaServicio), 1, p) == 1;
    fclose(p);
    return ok;
}

VentaServicio VentaServicioArchivo::leer(int pos) const {
    FILE* p = fopen(_nombreArchivo.c_str(), "rb");
    VentaServicio reg;
    if (p == NULL) return reg;

    fseek(p, pos * sizeof(VentaServicio), SEEK_SET);
    fread(&reg, sizeof(VentaServicio), 1, p);
    fclose(p);
    return reg;
}

int VentaServicioArchivo::getCantidadRegistros() const {
    FILE* p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) return 0;

    fseek(p, 0, SEEK_END);
    int cant = ftell(p) / sizeof(VentaServicio);
    fclose(p);
    return cant;
}
