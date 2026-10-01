#pragma once

class Cliente {
private:
    int idCliente;
    char nombre[30];
    char apellido[30];
    char telefono[20];
    char direccion[100];
    char email[50];
    bool eliminado;

    void copiarCadena(char* destino, const char* origen, int tamanio);

public:
    Cliente();

    bool Cargar();
    void Mostrar(bool mostrarEliminados = false) const;
    void MostrarPorNombre() const;
    void MostrarPorApellido() const;

    void setIdCliente(int id);
    void setNombre(const char* nuevoNombre);
    void setApellido(const char* nuevoApellido);
    void setTelefono(const char* nuevoTelefono);
    void setDireccion(const char* nuevaDireccion);
    void setEmail(const char* nuevoEmail);
    void setEliminado(bool e);

    int getIdCliente() const;
    const char* getNombre() const;
    const char* getApellido() const;
    const char* getTelefono() const;
    const char* getDireccion() const;
    const char* getEmail() const;
    bool getEliminado() const;
};
