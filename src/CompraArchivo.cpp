#include "CompraArchivo.h"
#include <cstdio>

CompraArchivo::CompraArchivo(std::string nombreArchivo) {
    _nombreArchivo = nombreArchivo;
}

bool CompraArchivo::guardar(Compra reg) {
    FILE* p = fopen(_nombreArchivo.c_str(), "ab");
    if (p == NULL) return false;

    bool ok = fwrite(&reg, sizeof(Compra), 1, p) == 1;
    fclose(p);
    return ok;
}

int CompraArchivo::buscarPorId(int id, bool incluirEliminados) const {
    int cantidad = getCantidadRegistros();

    for (int i = 0; i < cantidad; i++) {
        Compra reg = leer(i);
        if (reg.getIdCompra() == id && (incluirEliminados || !reg.getEliminado())) {
            return i;
        }
    }

    return -1;
}

bool CompraArchivo::modificar(Compra reg, int pos) {
    FILE* p = fopen(_nombreArchivo.c_str(), "rb+");
    if (p == NULL) return false;

    fseek(p, pos * sizeof(Compra), SEEK_SET);
    bool ok = fwrite(&reg, sizeof(Compra), 1, p) == 1;
    fclose(p);
    return ok;
}

Compra CompraArchivo::leer(int pos) const {
    FILE* p = fopen(_nombreArchivo.c_str(), "rb");
    Compra reg;
    if (p == NULL) return reg;

    fseek(p, pos * sizeof(Compra), SEEK_SET);
    fread(&reg, sizeof(Compra), 1, p);
    fclose(p);
    return reg;
}

int CompraArchivo::obtenerProximoId() const {
    int cantidad = getCantidadRegistros();
    int mayorId = 0;

    for (int i = 0; i < cantidad; i++) {
        Compra reg = leer(i);
        if (reg.getIdCompra() > mayorId) {
            mayorId = reg.getIdCompra();
        }
    }

    return mayorId + 1;
}

int CompraArchivo::getCantidadRegistros() const {
    FILE* p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) return 0;

    fseek(p, 0, SEEK_END);
    int cant = ftell(p) / sizeof(Compra);
    fclose(p);
    return cant;
}
