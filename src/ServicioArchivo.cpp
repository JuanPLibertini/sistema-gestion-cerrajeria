#include "ServicioArchivo.h"
#include <cstdio>

ServicioArchivo::ServicioArchivo(std::string nombreArchivo) {
    _nombreArchivo = nombreArchivo;
}

bool ServicioArchivo::guardar(Servicio reg) {
    FILE* p = fopen(_nombreArchivo.c_str(), "ab");
    if (p == NULL) return false;

    bool ok = fwrite(&reg, sizeof(Servicio), 1, p) == 1;
    fclose(p);
    return ok;
}

int ServicioArchivo::buscarPorId(int id, bool incluirEliminados) const {
    int cantidad = getCantidadRegistros();

    for (int i = 0; i < cantidad; i++) {
        Servicio reg = leer(i);
        if (reg.getIdServicio() == id && (incluirEliminados || !reg.getEliminado())) {
            return i;
        }
    }

    return -1;
}

bool ServicioArchivo::modificar(Servicio reg, int pos) {
    FILE* p = fopen(_nombreArchivo.c_str(), "rb+");
    if (p == NULL) return false;

    fseek(p, pos * sizeof(Servicio), SEEK_SET);
    bool ok = fwrite(&reg, sizeof(Servicio), 1, p) == 1;
    fclose(p);
    return ok;
}

Servicio ServicioArchivo::leer(int pos) const {
    FILE* p = fopen(_nombreArchivo.c_str(), "rb");
    Servicio reg;
    if (p == NULL) return reg;

    fseek(p, pos * sizeof(Servicio), SEEK_SET);
    fread(&reg, sizeof(Servicio), 1, p);
    fclose(p);
    return reg;
}

int ServicioArchivo::obtenerProximoId() const {
    int cantidad = getCantidadRegistros();
    int mayorId = 0;

    for (int i = 0; i < cantidad; i++) {
        Servicio reg = leer(i);
        if (reg.getIdServicio() > mayorId) {
            mayorId = reg.getIdServicio();
        }
    }

    return mayorId + 1;
}

int ServicioArchivo::getCantidadRegistros() const {
    FILE* p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) return 0;

    fseek(p, 0, SEEK_END);
    int cant = ftell(p) / sizeof(Servicio);
    fclose(p);
    return cant;
}
