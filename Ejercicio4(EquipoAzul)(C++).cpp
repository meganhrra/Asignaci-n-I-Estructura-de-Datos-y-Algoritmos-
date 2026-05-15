/*
    Ejercicio 4 (ICPC) - Reasignacion optima entre almacenes
    Asignacion I - Estructura de Datos y Algoritmos
    Equipo Azul

    Redistribuye productos entre 6 almacenes para que ninguno
    quede por debajo del umbral minimo, minimizando el costo
    total de transporte (cantidad * distancia).

    Estrategia greedy: para cada deficit, traer del excedente
    mas cercano.
*/

#include <iostream>
#include <string>
using namespace std;


struct Movimiento {
    int producto;
    int origen;
    int destino;
    int cantidad;
    int costo;
};


class Redistribuidor {
private:
    static const int CANT_ALMACENES = 6;
    static const int CANT_PRODUCTOS = 15;
    static const int MAX_MOVS = CANT_ALMACENES * CANT_PRODUCTOS * 2;

    int stock[CANT_ALMACENES][CANT_PRODUCTOS];
    int distancia[CANT_ALMACENES][CANT_ALMACENES];
    int umbral[CANT_PRODUCTOS];

    Movimiento movimientos[MAX_MOVS];
    int cantMovimientos;
    int costoTotal;

public:
    Redistribuidor() {
        cantMovimientos = 0;
        costoTotal = 0;
        cargarDatos();
    }

    void cargarDatos() {
        int datosStock[CANT_ALMACENES][CANT_PRODUCTOS] = {
            //P0  P1  P2  P3  P4  P5  P6  P7  P8  P9  P10 P11 P12 P13 P14
            { 50, 30, 15, 40, 25, 18, 35, 20, 22, 28, 16, 45, 10, 12, 38}, // Alm 0
            { 25, 20, 18, 30, 22, 15, 28, 10, 35, 12, 40, 20, 10, 25, 16}, // Alm 1
            { 15, 12, 10, 14, 10, 18, 11, 10, 10, 13, 10, 12,  5, 11, 10}, // Alm 2
            { 40, 35, 28, 22, 30, 25, 18,  0, 32, 20, 15, 38, 10, 16, 22}, // Alm 3
            { 22, 18, 25, 16, 12, 30, 20, 10, 18, 22, 16, 14, 10, 20, 13}, // Alm 4
            { 30, 22, 18, 25, 15, 20, 22, 10, 12, 28, 18, 30, 15, 22, 14}  // Alm 5
        };

        int datosDist[CANT_ALMACENES][CANT_ALMACENES] = {
            {0,  4,  6,  7,  8,  9 },
            {4,  0,  3,  6,  7,  8 },
            {6,  3,  0,  4,  6,  5 },
            {7,  6,  4,  0,  3,  6 },
            {8,  7,  6,  3,  0,  4 },
            {9,  8,  5,  6,  4,  0 }
        };

        for (int i = 0; i < CANT_ALMACENES; i++) {
            for (int j = 0; j < CANT_PRODUCTOS; j++) {
                stock[i][j] = datosStock[i][j];
            }
            for (int j = 0; j < CANT_ALMACENES; j++) {
                distancia[i][j] = datosDist[i][j];
            }
        }

        for (int j = 0; j < CANT_PRODUCTOS; j++) {
            umbral[j] = 10;
        }
    }

    void mostrarStock(string titulo) {
        cout << "\n--- " << titulo << " ---" << endl;
        cout << "\t";
        for (int j = 0; j < CANT_PRODUCTOS; j++) {
            cout << "P" << j << "\t";
        }
        cout << endl;

        for (int i = 0; i < CANT_ALMACENES; i++) {
            cout << "Alm" << i << "\t";
            for (int j = 0; j < CANT_PRODUCTOS; j++) {
                cout << stock[i][j] << "\t";
            }
            cout << endl;
        }
    }

    void mostrarDistancias() {
        cout << "\n--- Matriz de distancias ---" << endl;
        cout << "\t";
        for (int j = 0; j < CANT_ALMACENES; j++) {
            cout << "Alm" << j << "\t";
        }
        cout << endl;

        for (int i = 0; i < CANT_ALMACENES; i++) {
            cout << "Alm" << i << "\t";
            for (int j = 0; j < CANT_ALMACENES; j++) {
                cout << distancia[i][j] << "\t";
            }
            cout << endl;
        }
    }

    void mostrarUmbrales() {
        cout << "\nUmbrales minimos por producto: ";
        for (int j = 0; j < CANT_PRODUCTOS; j++) {
            cout << umbral[j] << " ";
        }
        cout << endl;
    }

    // Busca el primer almacen con deficit para el producto p.
    // Devuelve -1 si no hay.
    int buscarDeficit(int p) {
        for (int i = 0; i < CANT_ALMACENES; i++) {
            if (stock[i][p] < umbral[p]) {
                return i;
            }
        }
        return -1;
    }

    // Busca el almacen excedente mas cercano al deficitario para
    // el producto p. Devuelve -1 si no hay excedentes.
    int buscarFuenteMasCercana(int almDeficit, int p) {
        int almFuente = -1;
        int menorDist = -1;

        for (int j = 0; j < CANT_ALMACENES; j++) {
            if (j != almDeficit && stock[j][p] > umbral[p]) {
                if (almFuente == -1 || distancia[almDeficit][j] < menorDist) {
                    almFuente = j;
                    menorDist = distancia[almDeficit][j];
                }
            }
        }

        return almFuente;
    }

    void redistribuir() {
        cantMovimientos = 0;
        costoTotal = 0;

        for (int p = 0; p < CANT_PRODUCTOS; p++) {
            bool huboMovimiento = true;

            while (huboMovimiento) {
                huboMovimiento = false;

                int almDeficit = buscarDeficit(p);
                if (almDeficit == -1) break;

                int almFuente = buscarFuenteMasCercana(almDeficit, p);
                if (almFuente == -1) break;

                // Mover el minimo entre lo que falta y lo que sobra
                int falta = umbral[p] - stock[almDeficit][p];
                int sobra = stock[almFuente][p] - umbral[p];
                int aMover = (falta < sobra) ? falta : sobra;

                stock[almFuente][p]  -= aMover;
                stock[almDeficit][p] += aMover;

                int costo = aMover * distancia[almFuente][almDeficit];
                costoTotal += costo;

                movimientos[cantMovimientos].producto = p;
                movimientos[cantMovimientos].origen   = almFuente;
                movimientos[cantMovimientos].destino  = almDeficit;
                movimientos[cantMovimientos].cantidad = aMover;
                movimientos[cantMovimientos].costo    = costo;
                cantMovimientos++;

                huboMovimiento = true;
            }
        }
    }

    void mostrarResultado() {
        cout << "\n--- Resultado de la redistribucion ---" << endl;

        if (cantMovimientos == 0) {
            cout << "No fue necesario realizar ningun movimiento." << endl;
            return;
        }

        for (int i = 0; i < cantMovimientos; i++) {
            cout << "Producto " << movimientos[i].producto
                 << ": " << movimientos[i].cantidad
                 << " unidades movidas de Almacen " << movimientos[i].origen
                 << " a Almacen " << movimientos[i].destino
                 << ". Costo: " << movimientos[i].costo << endl;
        }

        cout << "\nTotal de movimientos realizados: " << cantMovimientos << endl;
        cout << "Costo total: " << costoTotal << endl;
    }

    void verificarDeficitsRestantes() {
        cout << "\n--- Verificacion final ---" << endl;
        int deficitsRest = 0;

        for (int i = 0; i < CANT_ALMACENES; i++) {
            for (int j = 0; j < CANT_PRODUCTOS; j++) {
                if (stock[i][j] < umbral[j]) {
                    cout << "Aviso: Almacen " << i
                         << ", Producto " << j
                         << " sigue con " << stock[i][j]
                         << " < umbral " << umbral[j]
                         << " (no habia excedentes suficientes)" << endl;
                    deficitsRest++;
                }
            }
        }

        if (deficitsRest == 0) {
            cout << "Todos los almacenes quedaron por encima del umbral." << endl;
        }
    }
};


int main() {
    Redistribuidor sistema;

    cout << "===========================================" << endl;
    cout << "  REASIGNACION OPTIMA ENTRE ALMACENES (ICPC)" << endl;
    cout << "===========================================" << endl;

    sistema.mostrarStock("Stock INICIAL");
    sistema.mostrarDistancias();
    sistema.mostrarUmbrales();

    sistema.redistribuir();

    sistema.mostrarResultado();
    sistema.mostrarStock("Stock FINAL");
    sistema.verificarDeficitsRestantes();

    return 0;
}