#pragma once

#include <string>
#include "Servicio.h"

class ServicioArchivo {
private:
    std::string _nombreArchivo;

public:
    ServicioArchivo(std::string nombreArchivo = "servicios.dat");

    bool guardar(Servicio reg);
    int buscarPorId(int id, bool incluirEliminados = false) const;
    bool modificar(Servicio reg, int pos);
    Servicio leer(int pos) const;

    int obtenerProximoId() const;
    int getCantidadRegistros() const;
};
