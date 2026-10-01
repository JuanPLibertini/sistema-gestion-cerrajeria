#include "EmpleadoArchivo.h"
#include <cstdio>

EmpleadoArchivo::EmpleadoArchivo(std::string nombreArchivo) {
    _nombreArchivo = nombreArchivo;
}

bool EmpleadoArchivo::guardar(Empleado reg) {
    FILE* p = fopen(_nombreArchivo.c_str(), "ab");
    if (p == NULL) return false;
    bool ok = fwrite(&reg, sizeof(Empleado), 1, p) == 1;
    fclose(p);
    return ok;
}

bool EmpleadoArchivo::modificar(Empleado reg, int pos) {
    FILE* p = fopen(_nombreArchivo.c_str(), "rb+");
    if (p == NULL) return false;
    fseek(p, pos * sizeof(Empleado), SEEK_SET);
    bool ok = fwrite(&reg, sizeof(Empleado), 1, p) == 1;
    fclose(p);
    return ok;
}

Empleado EmpleadoArchivo::leer(int pos)  const{
    FILE* p = fopen(_nombreArchivo.c_str(), "rb");
    Empleado reg;
    if (p == NULL) return reg;
    fseek(p, pos * sizeof(Empleado), SEEK_SET);
    fread(&reg, sizeof(Empleado), 1, p);
    fclose(p);
    return reg;
}

int EmpleadoArchivo::getCantidadRegistros() const {
    FILE* p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) return 0;
    fseek(p, 0, SEEK_END);
    int cant = ftell(p) / sizeof(Empleado);
    fclose(p);
    return cant;
}

int EmpleadoArchivo::buscarPorId(int id, bool incluirEliminados) {
    int cantidad = getCantidadRegistros();
    for (int i = 0; i < cantidad; i++) {
        Empleado reg = leer(i);
        if (reg.getIdEmpleado() == id && (incluirEliminados || !reg.getEliminado())) {
            return i;
        }
    }
    return -1;
}

int EmpleadoArchivo::obtenerProximoId() {
    int cantidad = getCantidadRegistros();
    int mayorId = 0;
    for (int i = 0; i < cantidad; i++) {
        Empleado reg = leer(i);
        if (reg.getIdEmpleado() > mayorId) {
            mayorId = reg.getIdEmpleado();
        }
    }
    return mayorId + 1;
}
