#pragma once

#include "Fecha.h"

class Compra {
private:
    int idCompra;
    int idProveedor;
    int idEmpleado;
    Fecha fechaCompra;
    float totalCompra;
    bool eliminado;

    void copiarCadena(char* destino, const char* origen, int tamanio);

public:
    Compra();
    bool Cargar();
    void Mostrar(bool mostrarEliminados = false) const;
    void MostrarPorEmpleado(bool mostrarEliminados = false) const;
    void MostrarPorProveedor(bool mostrarEliminados = false) const;
    void MostrarPorFecha(bool mostrarEliminados = false) const;

    void setIdCompra(int id);
    void setIdProveedor(int id);
    void setIdEmpleado(int id);

    void setFechaCompra(const Fecha& f);
    void setTotalCompra(float t);
    void setEliminado(bool e);

    int getIdCompra() const;
    int getIdProveedor() const;
    int getIdEmpleado() const;
    Fecha getFechaCompra() const;
    float getTotalCompra() const;
    bool getEliminado() const;

};
