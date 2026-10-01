#pragma once

#include <string>
#include "Compra.h"

class CompraArchivo {
private:
    std::string _nombreArchivo;

public:
    CompraArchivo(std::string nombreArchivo = "compra.dat");

    bool guardar(Compra reg);
    int buscarPorId(int id, bool incluirEliminados = false) const;
    bool modificar(Compra reg, int pos);
    Compra leer(int pos) const;

    int obtenerProximoId() const;
    int getCantidadRegistros() const;
};
