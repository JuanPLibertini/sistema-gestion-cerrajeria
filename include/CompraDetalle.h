#pragma once

class CompraDetalle {
private:
    int   idCompra;
    int   idProducto;
    int   cantidad;
    float precioUnitario;
    bool  eliminado;

public:
    CompraDetalle();

    bool Cargar();
    void Mostrar() const;

    void setIdCompra(int id);
    void setIdProducto(int id);
    void setCantidad(int c);
    void setPrecioUnitario(float p);
    void setEliminado(bool e);

    int getIdCompra() const;
    int getIdProducto() const;
    int getCantidad() const;
    float getPrecioUnitario() const;
    bool getEliminado() const;
};
