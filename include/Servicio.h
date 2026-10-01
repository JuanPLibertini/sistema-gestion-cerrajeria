#pragma once
#include "Fecha.h"

class Servicio {
private:
    int idServicio;
    int idProducto;
    Fecha fecha;
    char descripcion[100];
    int tipo;        // 1 = local, 2 = calle
    int precio;
    bool eliminado;


    void copiarCadena(char* destino, const char* origen, int tamanio);

public:
    Servicio();

    bool Cargar();
    void Mostrar(bool mostrarEliminados = false) const;
    void mostrarListadoServicios()const;
    void MostrarPorTipo() const;
    void MostrarPorPrecio() const;
    void MostrarPorDescripcion() const;

    void setIdServicio(int id);
    void setIdProducto(int id);
    void setFecha(const Fecha& f);
    void setDescripcion(const char* d);
    void setTipo(int t);
    void setPrecio(int p);
    void setEliminado(bool e);

    int getIdServicio() const;
    int getIdProducto() const;
    Fecha getFecha() const;
    const char* getDescripcion() const;
    int getTipo() const;
    int getPrecio() const;
    bool getEliminado() const;
};
