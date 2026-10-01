#pragma once

#include <string>
#include "CompraDetalle.h"

class CompraDetalleArchivo {
private:
    std::string _nombreArchivo;

public:
    CompraDetalleArchivo(std::string nombreArchivo = "compraDetalle.dat");

    bool guardar(CompraDetalle reg);
    bool modificar(CompraDetalle reg, int pos);
    CompraDetalle leer(int pos) const;

    int getCantidadRegistros() const;
};
