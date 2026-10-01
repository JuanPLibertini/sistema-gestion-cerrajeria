#pragma once
#include "MenuProducto.h"
#include "MenuProveedor.h"
#include "MenuCliente.h"
#include "MenuEmpleado.h"
#include "MenuCompra.h"
#include "MenuServicio.h"
#include "MenuVenta.h"
#include "MenuInforme.h"

class MenuPrincipal {
private:
    MenuProducto   _menuProducto;
    MenuProveedor  _menuProveedor;
    MenuCliente    _menuCliente;
    MenuEmpleado   _menuEmpleado;
    MenuCompra     _menuCompra;
    MenuServicio   _menuServicio;
    MenuVenta      _menuVenta;
    MenuInforme    _menuInforme;

public:
    void mostrar();
};
