#pragma once

#include <string>
#include "Proveedor.h"

class ProveedorArchivo {
private:
    std::string _nombreArchivo;

public:
    ProveedorArchivo(std::string nombreArchivo = "proveedores.dat");

    bool guardar(Proveedor reg);
    bool modificar(Proveedor reg, int pos);
    Proveedor leer(int pos);

    int getCantidadRegistros();
    int buscarPorId(int id, bool incluirEliminados = false);
    int obtenerProximoId();
};


