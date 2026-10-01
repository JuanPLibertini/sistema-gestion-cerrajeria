#pragma once

#include <string>
#include "Cliente.h"

class ClienteArchivo {
private:
    std::string _nombreArchivo;

public:
    ClienteArchivo(std::string nombreArchivo = "clientes.dat");

    bool guardar(Cliente reg);
    int buscarPorId(int id, bool incluirEliminados = false) const;
    bool modificar(Cliente reg, int pos);
    Cliente leer(int pos) const;

    int obtenerProximoId() const;
    int getCantidadRegistros() const;
};
