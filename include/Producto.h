#pragma once

class Producto {
private:
    int idProducto;
    char nombre[50];
    char descripcion[100];
    char marca[50];
    char tipo[6];
    float precio;
    int stock;
    int idProveedor;
    bool eliminado;

    void copiarCadena(char* destino, const char* origen, int tamanio);

public:
    Producto();

    bool Cargar();
    void Mostrar(bool mostrarEliminados = false) const;
    void MostrarProductoPorMarca(bool mostrarEliminados = false) const;
    void MostrarProductoPorPrecio(bool mostrarEliminados = false) const;
    void MostrarProductoPorStock(bool mostrarEliminados = false) const;


    void setIdProducto(int id);
    void setNombre(const char* nuevoNombre);
    void setDescripcion(const char* nuevaDescripcion);
    void setTipo(const char* nuevoTipo);
    void setPrecio(float nuevoPrecio);
    void setStock(int nuevoStock);
    void setIdProveedor(int id);
    void setEliminado(bool e);
    void setMarca(const char* nuevaMarca);

    int getIdProducto() const;
    const char* getNombre() const;
    const char* getDescripcion() const;
    const char* getTipo() const;
    const char* getMarca() const;
    float getPrecio() const;
    int getStock() const;
    int getIdProveedor() const;
    bool getEliminado() const;
};
