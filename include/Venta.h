#pragma once

#include "Fecha.h"

class Venta {
private:
    int   idVenta;
    int   idCliente;
    int   idEmpleado;
    Fecha fecha;
    float total;
    bool  eliminado;

public:
    Venta();

    bool Cargar();
    void Mostrar(bool mostrarEliminados = false) const;
    void MostrarPorFecha(bool mostrarEliminados = false) const;
    void MostrarPorCliente(bool mostrarEliminados = false) const;

    void setIdVenta(int id);
    void setIdCliente(int id);
    void setIdEmpleado(int id);
    void setFecha(const Fecha& f);
    void setTotal(float t);
    void setEliminado(bool e);

    int getIdVenta() const;
    int getIdCliente() const;
    int getIdEmpleado() const;
    Fecha getFecha() const;
    float getTotal() const;
    bool getEliminado() const;
};
