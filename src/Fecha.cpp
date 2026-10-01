#include <iostream>
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <limits>
using namespace std;
#include "fecha.h"
#include "rlutil.h"

Fecha::Fecha(int d, int m, int a) {
    if (fechaValida(d, m, a)) {
        _dia = d; _mes = m; _anio = a;
    } else {
        _dia = 1; _mes = 1; _anio = 2000;
    }
}

bool Fecha::fechaValida(int d, int m, int a) {
    if (a <= 0) return false;
    if (m < 1 || m > 12) return false;
    if (d < 1 || d > diasEnMes(m, a)) return false;
    return true;
}

int Fecha::diasEnMes(int mes, int anio) {
    int dias[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    if (mes == 2 && (anio % 4 == 0 && (anio % 100 != 0 || anio % 400 == 0))) {
        return 29;
    }
    return dias[mes - 1];
}

bool Fecha::Cargar() {
    int d, m, a;
    char buffer[50];

    while (true) {
        cout << "Dia (o 'salir'): ";
        cin.getline(buffer, 50);
        if (strcmp(buffer, "salir") == 0) return false;

        stringstream ss(buffer);
        if (!(ss >> d) || d < 1 || d > 31) {
            rlutil::setColor(rlutil::RED);
            cout << "Dia invalido.\n";
            rlutil::setColor(rlutil::WHITE);
            continue;
        }
        break;
    }

    while (true) {
        cout << "Mes (o 'salir'): ";
        cin.getline(buffer, 50);
        if (strcmp(buffer, "salir") == 0) return false;

        stringstream ss(buffer);
        if (!(ss >> m) || m < 1 || m > 12) {
            rlutil::setColor(rlutil::RED);
            cout << "Mes invalido.\n";
            rlutil::setColor(rlutil::WHITE);
            continue;
        }
        break;
    }

    while (true) {
        cout << "Anio (o 'salir'): ";
        cin.getline(buffer, 50);
        if (strcmp(buffer, "salir") == 0) return false;

        stringstream ss(buffer);
        if (!(ss >> a) || a < 1930 || a > 2026) {
            rlutil::setColor(rlutil::RED);
            cout << "Anio invalido. Debe estar entre 1930 y 2026.\n";
            rlutil::setColor(rlutil::WHITE);
            continue;
        }
        break;
    }

    if (!fechaValida(d, m, a)) {
        rlutil::setColor(rlutil::RED);
        cout << "Fecha invalida (revise los dias del mes). Reingrese.\n";
        rlutil::setColor(rlutil::WHITE);
        return Cargar();
    }

    Fecha hoy = Fecha::fechaActual();
    Fecha ingresada(d, m, a);
    if (ingresada.esMayorQue(hoy)) {
        rlutil::setColor(rlutil::RED);
        cout << "Fecha invalida: no se permiten fechas futuras. Reingrese.\n";
        rlutil::setColor(rlutil::WHITE);
        return Cargar();
    }

    _dia = d; _mes = m; _anio = a;
    return true;
}

void Fecha::Mostrar() const {
    cout << setw(2) << setfill('0') << _dia << "/"
         << setw(2) << setfill('0') << _mes << "/"
         << _anio;
}

string Fecha::toString() const {
    ostringstream oss;
    oss << setw(2) << setfill('0') << _dia << "/"
        << setw(2) << setfill('0') << _mes << "/"
        << _anio;
    return oss.str();
}

int Fecha::getDia() const { return _dia; }
int Fecha::getMes() const { return _mes; }
int Fecha::getAnio() const { return _anio; }

void Fecha::setDia(int d) {
    if (fechaValida(d, _mes, _anio)) _dia = d;
}
void Fecha::setMes(int m) {
    if (fechaValida(_dia, m, _anio)) _mes = m;
}
void Fecha::setAnio(int a) {
    if (fechaValida(_dia, _mes, a)) _anio = a;
}

void Fecha::setCurrentDate() {
    auto now = chrono::system_clock::now();
    time_t now_c = chrono::system_clock::to_time_t(now);
    tm* localTime = localtime(&now_c);
    _dia = localTime->tm_mday;
    _mes = localTime->tm_mon + 1;
    _anio = localTime->tm_year + 1900;
}

Fecha Fecha::fechaActual() {
    auto now = chrono::system_clock::now();
    time_t now_c = chrono::system_clock::to_time_t(now);
    tm* localTime = localtime(&now_c);
    return Fecha(localTime->tm_mday, localTime->tm_mon + 1, localTime->tm_year + 1900);
}

bool Fecha::esMayorQue(const Fecha& otra) const {
    if (_anio != otra._anio) return _anio > otra._anio;
    if (_mes != otra._mes) return _mes > otra._mes;
    return _dia > otra._dia;
}

bool Fecha::esIgualA(const Fecha& otra) const {
    return _dia == otra._dia && _mes == otra._mes && _anio == otra._anio;
}

bool Fecha::operator>(const Fecha& otra) const {
    if (_anio != otra._anio) return _anio > otra._anio;
    if (_mes != otra._mes) return _mes > otra._mes;
    return _dia > otra._dia;
}

bool Fecha::operator<(const Fecha& otra) const {
    if (_anio != otra._anio) return _anio < otra._anio;
    if (_mes != otra._mes) return _mes < otra._mes;
    return _dia < otra._dia;
}

bool Fecha::operator==(const Fecha& otra) const {
    return _dia == otra._dia && _mes == otra._mes && _anio == otra._anio;
}



bool Fecha::esFechaValida(int dia, int mes, int anio) const {
    return fechaValida(dia, mes, anio);
}

bool Fecha::validarFechaStr(const string& fecha) {
    if (fecha.length() != 10) return false;
    if (fecha[2] != '/' || fecha[5] != '/') return false;
    int d = stoi(fecha.substr(0, 2));
    int m = stoi(fecha.substr(3, 2));
    int a = stoi(fecha.substr(6, 4));
    return fechaValida(d, m, a);
}



