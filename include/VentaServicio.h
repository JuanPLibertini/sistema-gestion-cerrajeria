#pragma once

#include "Fecha.h"

class VentaServicio {
private:
    int   idVenta;
    int   idCliente;
    int   idServicio;
    Fecha fecha;
    float total;
    bool  eliminado;

public:
    VentaServicio();

    bool Cargar();
    void Mostrar() const;

    int getIdVenta() const;
    int getIdCliente() const;
    int getIdServicio() const;
    Fecha getFecha() const;
    float getTotal() const;
    bool getEliminado() const;

    void setIdVenta(int id);
    void setIdCliente(int id);
    void setIdServicio(int id);
    void setFecha(const Fecha& f);
    void setTotal(float t);
    void setEliminado(bool e);
};
