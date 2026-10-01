#pragma once

class VentaDetalle {
private:
    int   idVenta;
    int   idProducto;
    int   cantidad;
    float precioUnitario;
    bool  eliminado;

public:
    VentaDetalle();

    bool Cargar();
    void Mostrar() const;

    void setIdVenta(int id);
    void setIdProducto(int id);
    void setCantidad(int c);
    void setPrecioUnitario(float p);
    void setEliminado(bool e);

    int getIdVenta() const;
    int getIdProducto() const;
    int getCantidad() const;
    float getPrecioUnitario() const;
    bool getEliminado() const;
};
