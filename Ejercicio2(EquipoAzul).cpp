/*
    Ejercicio 2 - Sistema de Gestion de Reservas Hotelera
    Asignacion I - Estructura de Datos y Algoritmos
    Equipo Azul

    Hotel con 15 habitaciones precargadas (5 Sencillas, 6 Dobles,
    4 Suites). Permite registrar reservas, calcular ocupacion,
    ver disponibles por tipo y consultar la mas cara disponible.
    Maximo 50 habitaciones segun el enunciado.
*/

#include <iostream>
#include <string>
using namespace std;


class Cliente
{
private:
    string nombre;
    string cedula;

public:
    Cliente()
    {
        nombre = "";
        cedula = "";
    }

    Cliente(string nombre, string cedula)
    {
        this->nombre = nombre;
        this->cedula = cedula;
    }

    string getNombre() const { return nombre; }
    string getCedula() const { return cedula; }

    void setNombre(string n) { nombre = n; }
    void setCedula(string c) { cedula = c; }
};


class Habitacion
{
private:
    int numero;
    string tipo;
    double precioNoche;
    bool ocupada;
    Cliente cliente;
    int noches;

public:
    Habitacion()
    {
        numero = 0;
        tipo = "";
        precioNoche = 0.0;
        ocupada = false;
        noches = 0;
    }

    Habitacion(int numero, string tipo, double precioNoche)
    {
        this->numero = numero;
        this->tipo = tipo;
        this->precioNoche = precioNoche;
        this->ocupada = false;
        this->noches = 0;
    }

    int getNumero() const         { return numero; }
    string getTipo() const        { return tipo; }
    double getPrecioNoche() const { return precioNoche; }
    bool estaOcupada() const      { return ocupada; }
    int getNoches() const         { return noches; }
    Cliente getCliente() const    { return cliente; }

    void reservar(Cliente c, int noches)
    {
        this->cliente = c;
        this->noches = noches;
        this->ocupada = true;
    }

    void liberar()
    {
        this->ocupada = false;
        this->noches = 0;
        this->cliente = Cliente();
    }

    double calcularSubtotal() const
    {
        if (ocupada)
            return precioNoche * noches;
        return 0.0;
    }

    void mostrar() const
    {
        cout << "Habitacion " << numero
             << " | Tipo: " << tipo
             << " | Precio/noche: " << precioNoche
             << " | Estado: ";

        if (ocupada)
        {
            cout << "Ocupada"
                 << " | Cliente: " << cliente.getNombre()
                 << " | Noches: " << noches;
        }
        else
        {
            cout << "Disponible";
        }
        cout << endl;
    }
};


class Hotel
{
private:
    static const int MAX_HABITACIONES = 50;

    Habitacion habitaciones[MAX_HABITACIONES];
    int cantidad;

public:
    Hotel()
    {
        cantidad = 0;
        precargarHabitaciones();
    }

    // Carga las 15 habitaciones iniciales del hotel
    void precargarHabitaciones()
    {
        // 5 Sencillas en el piso 1
        for (int i = 0; i < 5; i++)
        {
            habitaciones[cantidad] = Habitacion(101 + i, "Sencilla", 1500.0);
            cantidad++;
        }

        // 6 Dobles en el piso 2
        for (int i = 0; i < 6; i++)
        {
            habitaciones[cantidad] = Habitacion(201 + i, "Doble", 2500.0);
            cantidad++;
        }

        // 4 Suites en el piso 3
        for (int i = 0; i < 4; i++)
        {
            habitaciones[cantidad] = Habitacion(301 + i, "Suite", 6000.0);
            cantidad++;
        }
    }

    void restaurarEstadoInicial()
    {
        cantidad = 0;
        precargarHabitaciones();
        cout << "\nHotel restaurado al estado inicial (15 habitaciones)." << endl;
    }

    int buscarPorNumero(int numero) const
    {
        for (int i = 0; i < cantidad; i++)
        {
            if (habitaciones[i].getNumero() == numero)
                return i;
        }
        return -1;
    }

    void registrarHabitacion()
    {
        if (cantidad >= MAX_HABITACIONES)
        {
            cout << "\nNo se pueden registrar mas habitaciones (limite "
                 << MAX_HABITACIONES << ")." << endl;
            return;
        }

        cout << "\n========== REGISTRAR NUEVA HABITACION ==========" << endl;

        int numero;
        cout << "Numero de habitacion: ";
        cin >> numero;

        if (buscarPorNumero(numero) != -1)
        {
            cout << "Ya existe una habitacion con ese numero." << endl;
            return;
        }

        int op;
        cout << "Tipo de habitacion:" << endl;
        cout << "  1. Sencilla" << endl;
        cout << "  2. Doble" << endl;
        cout << "  3. Suite" << endl;
        cout << "Opcion: ";
        cin >> op;

        while (op < 1 || op > 3)
        {
            cout << "Tipo invalido. Ingrese 1, 2 o 3: ";
            cin >> op;
        }

        string tipo;
        if (op == 1)
            tipo = "Sencilla";
        else if (op == 2)
            tipo = "Doble";
        else
            tipo = "Suite";

        double precio;
        cout << "Precio por noche: ";
        cin >> precio;

        while (precio <= 0)
        {
            cout << "El precio debe ser positivo. Ingrese de nuevo: ";
            cin >> precio;
        }

        habitaciones[cantidad] = Habitacion(numero, tipo, precio);
        cantidad++;

        cout << "Habitacion registrada correctamente." << endl;
    }

    // Inciso a) Registrar reservas
    void registrarReserva()
    {
        if (cantidad == 0)
        {
            cout << "\nNo hay habitaciones registradas todavia." << endl;
            return;
        }

        cout << "\n========== REGISTRAR RESERVA ==========" << endl;
        cout << "Numero de habitacion a reservar: ";
        int numero;
        cin >> numero;

        int pos = buscarPorNumero(numero);
        if (pos == -1)
        {
            cout << "No existe una habitacion con ese numero." << endl;
            return;
        }

        if (habitaciones[pos].estaOcupada())
        {
            cout << "Esa habitacion ya esta ocupada." << endl;
            return;
        }

        string nombre, cedula;
        cin.ignore();
        cout << "Nombre del cliente: ";
        getline(cin, nombre);
        cout << "Cedula del cliente: ";
        getline(cin, cedula);

        int noches;
        cout << "Cantidad de noches: ";
        cin >> noches;

        while (noches <= 0)
        {
            cout << "Las noches deben ser un valor positivo: ";
            cin >> noches;
        }

        Cliente c(nombre, cedula);
        habitaciones[pos].reservar(c, noches);

        double total = habitaciones[pos].calcularSubtotal();
        cout << "\nReserva realizada exitosamente." << endl;
        cout << "Total a pagar: " << total << endl;
    }

    void liberarHabitacion()
    {
        cout << "\n========== CHECK-OUT (LIBERAR HABITACION) ==========" << endl;
        cout << "Numero de habitacion: ";
        int numero;
        cin >> numero;

        int pos = buscarPorNumero(numero);
        if (pos == -1)
        {
            cout << "No existe esa habitacion." << endl;
            return;
        }

        if (!habitaciones[pos].estaOcupada())
        {
            cout << "Esa habitacion ya estaba disponible." << endl;
            return;
        }

        habitaciones[pos].liberar();
        cout << "Habitacion liberada correctamente." << endl;
    }

    // Inciso b) Calcular ocupacion total e ingreso estimado
    void calcularOcupacionEIngreso() const
    {
        if (cantidad == 0)
        {
            cout << "\nNo hay habitaciones registradas." << endl;
            return;
        }

        int ocupadas = 0;
        double ingresoTotal = 0.0;

        for (int i = 0; i < cantidad; i++)
        {
            if (habitaciones[i].estaOcupada())
            {
                ocupadas++;
                ingresoTotal += habitaciones[i].calcularSubtotal();
            }
        }

        double porcentaje = (ocupadas * 100.0) / cantidad;

        cout << "\n========== REPORTE DE OCUPACION ==========" << endl;
        cout << "Habitaciones totales:    " << cantidad << endl;
        cout << "Habitaciones ocupadas:   " << ocupadas << endl;
        cout << "Habitaciones libres:     " << (cantidad - ocupadas) << endl;
        cout << "Porcentaje de ocupacion: " << porcentaje << " %" << endl;
        cout << "Ingreso estimado total:  " << ingresoTotal << endl;
    }

    // Inciso c) Mostrar habitaciones disponibles por tipo
    void mostrarDisponiblesPorTipo() const
    {
        if (cantidad == 0)
        {
            cout << "\nNo hay habitaciones registradas." << endl;
            return;
        }

        cout << "\n========== DISPONIBLES POR TIPO ==========" << endl;
        cout << "Tipo a consultar:" << endl;
        cout << "  1. Sencilla" << endl;
        cout << "  2. Doble" << endl;
        cout << "  3. Suite" << endl;
        cout << "Opcion: ";

        int op;
        cin >> op;

        string tipoBuscado;
        if (op == 1)
            tipoBuscado = "Sencilla";
        else if (op == 2)
            tipoBuscado = "Doble";
        else if (op == 3)
            tipoBuscado = "Suite";
        else
        {
            cout << "Tipo invalido." << endl;
            return;
        }

        int encontradas = 0;
        cout << "\nHabitaciones " << tipoBuscado << " disponibles:" << endl;

        for (int i = 0; i < cantidad; i++)
        {
            if (habitaciones[i].getTipo() == tipoBuscado &&
                !habitaciones[i].estaOcupada())
            {
                cout << "  - Habitacion " << habitaciones[i].getNumero()
                     << " | Precio/noche: "
                     << habitaciones[i].getPrecioNoche() << endl;
                encontradas++;
            }
        }

        if (encontradas == 0)
            cout << "  No hay habitaciones disponibles de ese tipo." << endl;
        else
            cout << "\nTotal encontradas: " << encontradas << endl;
    }

    // Inciso d) Habitacion mas cara disponible
    void habitacionMasCaraDisponible() const
    {
        if (cantidad == 0)
        {
            cout << "\nNo hay habitaciones registradas." << endl;
            return;
        }

        int posMayor = -1;

        for (int i = 0; i < cantidad; i++)
        {
            if (!habitaciones[i].estaOcupada())
            {
                if (posMayor == -1 ||
                    habitaciones[i].getPrecioNoche() > habitaciones[posMayor].getPrecioNoche())
                {
                    posMayor = i;
                }
            }
        }

        if (posMayor == -1)
        {
            cout << "\nNo hay habitaciones disponibles en este momento." << endl;
            return;
        }

        cout << "\n========== HABITACION MAS CARA DISPONIBLE ==========" << endl;
        cout << "Numero: " << habitaciones[posMayor].getNumero() << endl;
        cout << "Tipo:   " << habitaciones[posMayor].getTipo() << endl;
        cout << "Precio: " << habitaciones[posMayor].getPrecioNoche() << endl;
    }

    void listarTodas() const
    {
        if (cantidad == 0)
        {
            cout << "\nNo hay habitaciones registradas." << endl;
            return;
        }

        cout << "\n========== LISTADO DE HABITACIONES ("
             << cantidad << " en total) ==========" << endl;
        for (int i = 0; i < cantidad; i++)
        {
            habitaciones[i].mostrar();
        }
    }
};


int main()
{
    Hotel hotel;
    int opcion;

    do
    {
        cout << "\n=================================================" << endl;
        cout << "    SISTEMA DE GESTION DE RESERVAS HOTELERA" << endl;
        cout << "=================================================" << endl;
        cout << "1. Registrar nueva habitacion" << endl;
        cout << "2. Registrar reserva" << endl;
        cout << "3. Check-out (liberar habitacion)" << endl;
        cout << "4. Calcular ocupacion e ingreso estimado" << endl;
        cout << "5. Mostrar habitaciones disponibles por tipo" << endl;
        cout << "6. Habitacion mas cara disponible" << endl;
        cout << "7. Listar todas las habitaciones" << endl;
        cout << "8. Restaurar estado inicial (15 habitaciones)" << endl;
        cout << "0. Salir" << endl;
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion)
        {
            case 1: hotel.registrarHabitacion(); break;
            case 2: hotel.registrarReserva(); break;
            case 3: hotel.liberarHabitacion(); break;
            case 4: hotel.calcularOcupacionEIngreso(); break;
            case 5: hotel.mostrarDisponiblesPorTipo(); break;
            case 6: hotel.habitacionMasCaraDisponible(); break;
            case 7: hotel.listarTodas(); break;
            case 8: hotel.restaurarEstadoInicial(); break;
            case 0: cout << "\nSaliendo del sistema..." << endl; break;
            default: cout << "Opcion invalida. Intente de nuevo." << endl;
        }
    } while (opcion != 0);

    return 0;
}