#include <iostream>
using namespace std;

void pausa() {
    cout << "\nPresione ENTER para continuar...";
    cin.ignore();
}

void limpiarEntrada() {
    cin.ignore();
}

int leerOpcion() {
    int op;
    cin >> op;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        return -1;
    }
    cin.ignore(1000, '\n');
    return op;
}
