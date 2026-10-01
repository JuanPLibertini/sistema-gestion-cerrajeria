#pragma once

#include <string>
#include "VentaServicio.h"

class VentaServicioArchivo {
private:
    std::string _nombreArchivo;

public:
    VentaServicioArchivo(std::string nombreArchivo = "ventaServicio.dat");

    bool guardar(VentaServicio reg);
    bool modificar(VentaServicio reg, int pos);
    VentaServicio leer(int pos) const;

    int getCantidadRegistros() const;
};
