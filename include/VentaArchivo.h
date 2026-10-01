#pragma once

#include <string>
#include "Venta.h"

class VentaArchivo {
private:
    std::string _nombreArchivo;

public:
    VentaArchivo(std::string nombreArchivo = "ventas.dat");

    bool guardar(Venta reg);
    int buscarPorId(int id, bool incluirEliminados = false) const;
    bool modificar(Venta reg, int pos);
    Venta leer(int pos) const;

    int obtenerProximoId() const;
    int getCantidadRegistros() const;
};
