#include "ClienteArchivo.h"
#include <cstdio>

ClienteArchivo::ClienteArchivo(std::string nombreArchivo) {
    _nombreArchivo = nombreArchivo;
}

bool ClienteArchivo::guardar(Cliente reg) {
    FILE* p = fopen(_nombreArchivo.c_str(), "ab");
    if (p == NULL) return false;

    bool ok = fwrite(&reg, sizeof(Cliente), 1, p) == 1;
    fclose(p);
    return ok;
}

int ClienteArchivo::buscarPorId(int id, bool incluirEliminados) const {
    int cantidad = getCantidadRegistros();

    for (int i = 0; i < cantidad; i++) {
        Cliente reg = leer(i);
        if (reg.getIdCliente() == id && (incluirEliminados || !reg.getEliminado())) {
            return i;
        }
    }

    return -1;
}

bool ClienteArchivo::modificar(Cliente reg, int pos) {
    FILE* p = fopen(_nombreArchivo.c_str(), "rb+");
    if (p == NULL) return false;

    fseek(p, pos * sizeof(Cliente), SEEK_SET);
    bool ok = fwrite(&reg, sizeof(Cliente), 1, p) == 1;
    fclose(p);
    return ok;
}

Cliente ClienteArchivo::leer(int pos) const {
    FILE* p = fopen(_nombreArchivo.c_str(), "rb");
    Cliente reg;
    if (p == NULL) return reg;

    fseek(p, pos * sizeof(Cliente), SEEK_SET);
    fread(&reg, sizeof(Cliente), 1, p);
    fclose(p);
    return reg;
}

int ClienteArchivo::obtenerProximoId() const {
    int cantidad = getCantidadRegistros();
    int mayorId = 0;

    for (int i = 0; i < cantidad; i++) {
        Cliente reg = leer(i);
        if (reg.getIdCliente() > mayorId) {
            mayorId = reg.getIdCliente();
        }
    }

    return mayorId + 1;
}

int ClienteArchivo::getCantidadRegistros() const {
    FILE* p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) return 0;

    fseek(p, 0, SEEK_END);
    int cant = ftell(p) / sizeof(Cliente);
    fclose(p);
    return cant;
}
