#pragma once

#include <string>

class Fecha {
private:
    int _dia, _mes, _anio;
    static bool fechaValida(int d, int m, int a);
    static int diasEnMes(int mes, int anio);

public:
    Fecha(int d = 1, int m = 1, int a = 2000);

    bool Cargar();
    void Mostrar() const;
    std::string toString() const;

    int getDia() const;
    int getMes() const;
    int getAnio() const;

    void setDia(int d);
    void setMes(int m);
    void setAnio(int a);

    void setCurrentDate();
    static Fecha fechaActual();

    bool esMayorQue(const Fecha& otra) const;
    bool esIgualA(const Fecha& otra) const;
    bool esFechaValida(int dia, int mes, int anio) const;
    bool validarFechaStr(const std::string& fecha);
    bool operator>(const Fecha& otra) const;
    bool operator<(const Fecha& otra) const;
    bool operator==(const Fecha& otra) const;


};

