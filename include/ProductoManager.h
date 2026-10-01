#pragma once

#include "ProductoArchivo.h"

class ProductoManager {
private:
    ProductoArchivo _repo;

public:
    ProductoManager();

    void altaProducto();
    bool listarProductos();
    bool bajaProducto(int id);
    bool existeProducto(int id);
    void modificarProducto();
    bool reactivarProducto(int id);

    // LISTADO DE PRODUCTOS
    void listarProductoPorNombre();
    void listarProductoPorMarca();
    void listarProductoPorPrecio();
    void listarProductoPorStock();
    bool listarProductoEliminados();

    // CONSULTA DE PRODUCTOS
    bool buscarProductoPorNombre();
    bool buscarProductoPorTipo();
    bool buscarProductoPorRangoPrecio();
    bool buscarProductoPorProveedor();
};
