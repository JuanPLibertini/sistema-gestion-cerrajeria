#pragma once

#include <string>
#include "Producto.h"

class ProductoArchivo {
private:
    std::string _nombreArchivo;

public:
    ProductoArchivo(std::string nombreArchivo = "productos.dat");

    bool guardar(Producto reg);
    int buscarPorId(int id, bool incluirEliminados = false) const;
    bool modificar(Producto reg, int pos);
    Producto leer(int pos) const;

    int obtenerProximoId() const;
    int getCantidadRegistros() const;
};
