#pragma once

#include <string>
#include "VentaDetalle.h"

class VentaDetalleArchivo {
private:
    std::string _nombreArchivo;

public:
    VentaDetalleArchivo(std::string nombreArchivo = "ventaDetalle.dat");

    bool guardar(VentaDetalle reg);
    bool modificar(VentaDetalle reg, int pos);
    VentaDetalle leer(int pos) const;

    int getCantidadRegistros() const;
};
