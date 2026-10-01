#pragma once

#include "ProveedorArchivo.h"

class ProveedorManager {
private:
    ProveedorArchivo _repo;

public:
    ProveedorManager();

    void altaProveedor();
    bool bajaProveedor(int id);
    bool reactivarProveedor(int id);
    bool existeProveedor(int id);
    void modificarProveedor();

    // LISTADO DE PROVEEDORES
    bool listarProveedores();
    bool listarProveedoresPorNombre();
    bool listarProveedorEliminados();

    // CONSULTA DE PROVEEDORES
    bool buscarProveedorPorNombre();
};

