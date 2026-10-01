#pragma once

#include "ClienteArchivo.h"

class ClienteManager {
private:
    ClienteArchivo _repo;

public:
    ClienteManager();

    void altaCliente();
    bool listarClientes();
    bool bajaCliente(int id);
    bool existeCliente(int id);
    bool reactivarCliente(int id);
    void modificarCliente();

    // LISTADO DE CLIENTES
    void listarClientesPorApellido();
    void listarClientesPorNombre();
    bool listarClientesEliminados();

    // CONSULTA DE CLIENTES
    bool buscarClientePorNombre();
    bool buscarClientePorApellido();
};
