#pragma once

class Proveedor {
private:
    int  idProveedor;
    char nombre[50];
    char telefono[20];
    char direccion[100];
    char email[50];
    bool eliminado;

    void copiarCadena(char* destino, const char* origen, int tamanio);

public:
    Proveedor();
    bool Cargar();
    void Mostrar(bool mostrarEliminados = false) const;


    void setIdProveedor(int id);
    void setNombre(const char* n);
    void setTelefono(const char* t);
    void setDireccion(const char* d);
    void setEmail(const char* e);
    void setEliminado(bool estado);

    int getIdProveedor() const;
    const char* getNombre() const;
    const char* getTelefono() const;
    const char* getDireccion() const;
    const char* getEmail() const;
    bool getEliminado() const;
};


