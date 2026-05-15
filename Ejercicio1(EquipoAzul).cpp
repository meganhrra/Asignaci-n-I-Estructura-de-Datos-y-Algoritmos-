/*
    Ejercicio 1 - Gestion de Pasajeros por Clase
    Asignacion I - Estructura de Datos y Algoritmos
    Equipo Azul

    Sistema para vender boletos de un vuelo distribuyendo los
    asientos en 3 clases (15% primera, 25% segunda, 60% tercera).
*/

#include <iostream>
#include <string>
using namespace std;


class Pasajero
{
private:
    string nombreCompleto;
    int numeroAsiento;

public:
    Pasajero()
    {
        nombreCompleto = "";
        numeroAsiento = 0;
    }

    Pasajero(string nombre, int asiento)
    {
        this->nombreCompleto = nombre;
        this->numeroAsiento = asiento;
    }

    string getNombreCompleto() const { return nombreCompleto; }
    int getNumeroAsiento() const     { return numeroAsiento; }
};


class Avion
{
private:
    string matricula;
    string modelo;
    int capacidadTotal;
    int asientos1ra;
    int asientos2da;
    int asientos3ra;

public:
    Avion()
    {
        matricula = "";
        modelo = "";
        capacidadTotal = 0;
        asientos1ra = 0;
        asientos2da = 0;
        asientos3ra = 0;
    }

    Avion(string matricula, string modelo, int capacidad)
    {
        this->matricula = matricula;
        this->modelo = modelo;
        this->capacidadTotal = capacidad;
        calcularDistribucionAsientos();
    }

    // Aplica los porcentajes 15/25/60 sobre la capacidad total
    void calcularDistribucionAsientos()
    {
        asientos1ra = (capacidadTotal * 15) / 100;
        asientos2da = (capacidadTotal * 25) / 100;
        asientos3ra = capacidadTotal - asientos1ra - asientos2da;
    }

    string getMatricula() const   { return matricula; }
    string getModelo() const      { return modelo; }
    int getCapacidadTotal() const { return capacidadTotal; }
    int getAsientos1ra() const    { return asientos1ra; }
    int getAsientos2da() const    { return asientos2da; }
    int getAsientos3ra() const    { return asientos3ra; }

    void mostrarInformacionAvion() const
    {
        cout << "\n========== INFORMACION DEL AVION ==========" << endl;
        cout << "Matricula: " << matricula << endl;
        cout << "Modelo:    " << modelo << endl;
        cout << "Capacidad total: " << capacidadTotal << " asientos" << endl;
        cout << "\nDistribucion por clase:" << endl;
        cout << "  1ra clase: " << asientos1ra << " asientos (15%)" << endl;
        cout << "  2da clase: " << asientos2da << " asientos (25%)" << endl;
        cout << "  3ra clase: " << asientos3ra << " asientos (60%)" << endl;
    }
};


class Vuelo
{
private:
    static const int MAX_1RA = 40;
    static const int MAX_2DA = 60;
    static const int MAX_3RA = 130;

    // Precios fijos por clase
    static constexpr double PRECIO_1RA = 15000.0;
    static constexpr double PRECIO_2DA = 9000.0;
    static constexpr double PRECIO_3RA = 5000.0;

    int numeroVuelo;
    string ciudadOrigen;
    string ciudadDestino;
    Avion avion;

    // Tres arreglos, uno por clase
    Pasajero pasajeros1ra[MAX_1RA];
    Pasajero pasajeros2da[MAX_2DA];
    Pasajero pasajeros3ra[MAX_3RA];

    int vendidos1ra;
    int vendidos2da;
    int vendidos3ra;

public:
    Vuelo()
    {
        // Datos iniciales del vuelo y el avion
        avion = Avion("HI-1234", "Boeing 737", 100);
        numeroVuelo = 205;
        ciudadOrigen = "Santiago";
        ciudadDestino = "Miami";

        vendidos1ra = 0;
        vendidos2da = 0;
        vendidos3ra = 0;

        precargarPasajeros();
    }

    // Algunos boletos ya vendidos para mostrar el sistema funcionando
    void precargarPasajeros()
    {
        // 2 pasajeros en primera clase
        pasajeros1ra[0] = Pasajero("Ana Garcia", 1);
        pasajeros1ra[1] = Pasajero("Maria Lopez", 2);
        vendidos1ra = 2;

        // 3 pasajeros en segunda clase
        pasajeros2da[0] = Pasajero("Luis Reyes", 1);
        pasajeros2da[1] = Pasajero("Carlos Diaz", 2);
        pasajeros2da[2] = Pasajero("Sofia Mendez", 3);
        vendidos2da = 3;

        // 5 pasajeros en tercera clase
        pasajeros3ra[0] = Pasajero("Pedro Rojas", 1);
        pasajeros3ra[1] = Pasajero("Laura Vargas", 2);
        pasajeros3ra[2] = Pasajero("Juan Tavarez", 3);
        pasajeros3ra[3] = Pasajero("Rosa Pena", 4);
        pasajeros3ra[4] = Pasajero("Pablo Gonzalez", 5);
        vendidos3ra = 5;
    }

    // Inciso a) Registrar venta de boletos hasta llenar el avion
    void venderBoleto()
    {
        int totalVendidos = vendidos1ra + vendidos2da + vendidos3ra;
        if (totalVendidos >= avion.getCapacidadTotal())
        {
            cout << "\nLo siento, el vuelo esta completo." << endl;
            return;
        }

        cout << "\n========== VENDER BOLETO ==========" << endl;

        string nombre;
        cout << "Nombre completo del pasajero: ";
        cin.ignore();
        getline(cin, nombre);

        int clase;
        cout << "\nSeleccione la clase:" << endl;
        cout << "  1. Primera clase" << endl;
        cout << "  2. Segunda clase" << endl;
        cout << "  3. Tercera clase" << endl;
        cout << "Opcion: ";
        cin >> clase;

        while (clase < 1 || clase > 3)
        {
            cout << "Clase invalida. Ingrese 1, 2 o 3: ";
            cin >> clase;
        }

        // El sistema asigna automaticamente el numero de asiento
        // segun cuantos lleva vendidos en la clase elegida
        if (clase == 1)
        {
            if (vendidos1ra >= avion.getAsientos1ra())
            {
                cout << "No quedan asientos en primera clase." << endl;
                return;
            }
            int asiento = vendidos1ra + 1;
            pasajeros1ra[vendidos1ra] = Pasajero(nombre, asiento);
            vendidos1ra++;
            cout << "\nBoleto vendido en PRIMERA clase." << endl;
            cout << "Pasajero: " << nombre << endl;
            cout << "Asiento numero: " << asiento << endl;
        }
        else if (clase == 2)
        {
            if (vendidos2da >= avion.getAsientos2da())
            {
                cout << "No quedan asientos en segunda clase." << endl;
                return;
            }
            int asiento = vendidos2da + 1;
            pasajeros2da[vendidos2da] = Pasajero(nombre, asiento);
            vendidos2da++;
            cout << "\nBoleto vendido en SEGUNDA clase." << endl;
            cout << "Pasajero: " << nombre << endl;
            cout << "Asiento numero: " << asiento << endl;
        }
        else
        {
            if (vendidos3ra >= avion.getAsientos3ra())
            {
                cout << "No quedan asientos en tercera clase." << endl;
                return;
            }
            int asiento = vendidos3ra + 1;
            pasajeros3ra[vendidos3ra] = Pasajero(nombre, asiento);
            vendidos3ra++;
            cout << "\nBoleto vendido en TERCERA clase." << endl;
            cout << "Pasajero: " << nombre << endl;
            cout << "Asiento numero: " << asiento << endl;
        }
    }

    // Inciso b) Mostrar asientos vendidos por clase
    void mostrarVendidosPorClase() const
    {
        cout << "\n========== ASIENTOS VENDIDOS POR CLASE ==========" << endl;
        cout << "1ra clase: " << vendidos1ra << " / " << avion.getAsientos1ra() << endl;
        cout << "2da clase: " << vendidos2da << " / " << avion.getAsientos2da() << endl;
        cout << "3ra clase: " << vendidos3ra << " / " << avion.getAsientos3ra() << endl;

        int total = vendidos1ra + vendidos2da + vendidos3ra;
        cout << "Total vendidos: " << total << " / " << avion.getCapacidadTotal() << endl;
    }

    // Inciso c) Ingreso estimado por clase
    void calcularIngresosPorClase() const
    {
        double ingreso1 = vendidos1ra * PRECIO_1RA;
        double ingreso2 = vendidos2da * PRECIO_2DA;
        double ingreso3 = vendidos3ra * PRECIO_3RA;
        double total = ingreso1 + ingreso2 + ingreso3;

        cout << "\n========== INGRESO ESTIMADO POR CLASE ==========" << endl;
        cout << "1ra clase: " << vendidos1ra << " boletos x " << PRECIO_1RA << " = " << ingreso1 << endl;
        cout << "2da clase: " << vendidos2da << " boletos x " << PRECIO_2DA << " = " << ingreso2 << endl;
        cout << "3ra clase: " << vendidos3ra << " boletos x " << PRECIO_3RA << " = " << ingreso3 << endl;
        cout << "-----------------------------------------------" << endl;
        cout << "INGRESO TOTAL DEL VUELO: " << total << endl;
    }

    void listarPasajeros() const
    {
        int total = vendidos1ra + vendidos2da + vendidos3ra;
        if (total == 0)
        {
            cout << "\nNo hay pasajeros registrados." << endl;
            return;
        }

        cout << "\n========== LISTADO DE PASAJEROS ==========" << endl;

        cout << "\n--- PRIMERA CLASE (" << vendidos1ra << " pasajeros) ---" << endl;
        for (int i = 0; i < vendidos1ra; i++)
        {
            cout << "  " << (i + 1) << ". "
                 << pasajeros1ra[i].getNombreCompleto()
                 << " | Asiento: " << pasajeros1ra[i].getNumeroAsiento() << endl;
        }

        cout << "\n--- SEGUNDA CLASE (" << vendidos2da << " pasajeros) ---" << endl;
        for (int i = 0; i < vendidos2da; i++)
        {
            cout << "  " << (i + 1) << ". "
                 << pasajeros2da[i].getNombreCompleto()
                 << " | Asiento: " << pasajeros2da[i].getNumeroAsiento() << endl;
        }

        cout << "\n--- TERCERA CLASE (" << vendidos3ra << " pasajeros) ---" << endl;
        for (int i = 0; i < vendidos3ra; i++)
        {
            cout << "  " << (i + 1) << ". "
                 << pasajeros3ra[i].getNombreCompleto()
                 << " | Asiento: " << pasajeros3ra[i].getNumeroAsiento() << endl;
        }
    }

    void mostrarInformacionVuelo() const
    {
        cout << "\n========== INFORMACION DEL VUELO ==========" << endl;
        cout << "Numero de vuelo: " << numeroVuelo << endl;
        cout << "Origen:  " << ciudadOrigen << endl;
        cout << "Destino: " << ciudadDestino << endl;
        avion.mostrarInformacionAvion();
    }
};


int main()
{
    Vuelo vuelo;
    int opcion;

    do
    {
        cout << "\n=================================================" << endl;
        cout << "         SISTEMA DE GESTION DE AEROLINEA" << endl;
        cout << "=================================================" << endl;
        cout << "1. Vender boleto" << endl;
        cout << "2. Mostrar asientos vendidos por clase" << endl;
        cout << "3. Calcular ingresos por clase" << endl;
        cout << "4. Listar pasajeros por clase" << endl;
        cout << "5. Ver informacion del vuelo" << endl;
        cout << "0. Salir" << endl;
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion)
        {
            case 1: vuelo.venderBoleto(); break;
            case 2: vuelo.mostrarVendidosPorClase(); break;
            case 3: vuelo.calcularIngresosPorClase(); break;
            case 4: vuelo.listarPasajeros(); break;
            case 5: vuelo.mostrarInformacionVuelo(); break;
            case 0: cout << "\nSaliendo del sistema..." << endl; break;
            default: cout << "Opcion invalida. Intente de nuevo." << endl;
        }
    } while (opcion != 0);

    return 0;
}