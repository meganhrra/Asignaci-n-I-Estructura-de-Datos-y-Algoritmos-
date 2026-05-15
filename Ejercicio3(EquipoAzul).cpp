#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class Almacen {
private:
	static const int CANT_ALMACENES = 6;
	static const int CANT_PRODUCTOS = 15;
	
	int stock[CANT_ALMACENES][CANT_PRODUCTOS];
	int umbral[CANT_PRODUCTOS];
	
public:
	Almacen() {
		// Inicializa los umbrales en 10 por defecto
		for (int j = 0; j < CANT_PRODUCTOS; j++) {
			umbral[j] = 10;
		}
		
		// Carga la cantidad actual del inventario en cada almacen
		cargarInventarioActual();
	}
	
	// La empresa ya tiene inventario en los almacenes, asi que
	// el sistema arranca con los datos reales de la matriz
	void cargarInventarioActual() {
		int datos[CANT_ALMACENES][CANT_PRODUCTOS] = {
			{50, 30, 15, 40, 25, 18, 35, 20, 22, 28, 16, 45, 10, 12, 38},
			{25, 20, 18, 30, 22, 15, 28, 10, 35, 12, 40, 20, 10, 25, 16},
			{15, 12, 10, 14, 10, 18, 11, 10, 10, 13, 10, 12,  5, 11, 10},
			{40, 35, 28, 22, 30, 25, 18,  0, 32, 20, 15, 38, 10, 16, 22},
			{22, 18, 25, 16, 12, 30, 20, 10, 18, 22, 16, 14, 10, 20, 13},
			{30, 22, 18, 25, 15, 20, 22, 10, 12, 28, 18, 30, 15, 22, 14}
		};
		
		for (int i = 0; i < CANT_ALMACENES; i++) {
			for (int j = 0; j < CANT_PRODUCTOS; j++) {
				stock[i][j] = datos[i][j];
			}
		}
	}
	
	void configurarUmbrales() {
		cout << "\n=== CONFIGURAR UMBRALES MINIMOS ===\n";
		cout << "Ingrese el umbral minimo para cada producto:\n";
		
		for (int j = 0; j < CANT_PRODUCTOS; j++) {
			do {
				cout << "Producto #" << j + 1 << ": ";
				cin >> umbral[j];
				
				if (umbral[j] < 0) {
					cout << "Error: el umbral no puede ser negativo.\n";
				}
				
			} while (umbral[j] < 0);
		}
		
		cout << "Umbrales configurados correctamente.\n";
	}
	
	// Inciso a) Registrar las existencias por producto y almacen
	void registrarExistencias() {
		cout << "\n=== REGISTRO DE EXISTENCIAS ===\n";
		
		for (int i = 0; i < CANT_ALMACENES; i++) {
			cout << "\nAlmacen #" << i + 1 << endl;
			
			for (int j = 0; j < CANT_PRODUCTOS; j++) {
				do {
					cout << "Cantidad del producto #" << j + 1 << ": ";
					cin >> stock[i][j];
					
					if (stock[i][j] < 0) {
						cout << "Error: la cantidad no puede ser negativa.\n";
					}
					
				} while (stock[i][j] < 0);
			}
		}
	}
	
	void mostrarInventario() {
		cout << "\n=== MATRIZ DE INVENTARIO ===\n\n";
		
		cout << setw(10) << "Almacen";
		
		for (int j = 0; j < CANT_PRODUCTOS; j++) {
			cout << setw(5) << "P" + to_string(j + 1);
		}
		
		cout << endl;
		
		for (int i = 0; i < CANT_ALMACENES; i++) {
			cout << setw(10) << i + 1;
			
			for (int j = 0; j < CANT_PRODUCTOS; j++) {
				cout << setw(5) << stock[i][j];
			}
			
			cout << endl;
		}
	}
	
	// Inciso b) Detectar productos agotados por sucursal
	void detectarProductosAgotados() {
		cout << "\n=== PRODUCTOS AGOTADOS POR SUCURSAL ===\n";
		
		bool hayAgotados = false;
		
		for (int i = 0; i < CANT_ALMACENES; i++) {
			bool sucursalTieneAgotados = false;
			
			cout << "\nAlmacen #" << i + 1 << ": ";
			
			for (int j = 0; j < CANT_PRODUCTOS; j++) {
				if (stock[i][j] == 0) {
					cout << "Producto #" << j + 1 << " ";
					hayAgotados = true;
					sucursalTieneAgotados = true;
				}
			}
			
			if (!sucursalTieneAgotados) {
				cout << "No tiene productos agotados.";
			}
			
			cout << endl;
		}
		
		if (!hayAgotados) {
			cout << "\nNo hay productos agotados en ningun almacen.\n";
		}
	}
	
	int calcularStockTotalPorAlmacen(int indiceAlmacen) {
		int total = 0;
		
		for (int j = 0; j < CANT_PRODUCTOS; j++) {
			total += stock[indiceAlmacen][j];
		}
		
		return total;
	}
	
	// Inciso c) Identificar el almacen con menor stock total
	void identificarAlmacenMenorStock() {
		int menorStock = calcularStockTotalPorAlmacen(0);
		int almacenMenor = 0;
		
		for (int i = 1; i < CANT_ALMACENES; i++) {
			int total = calcularStockTotalPorAlmacen(i);
			
			if (total < menorStock) {
				menorStock = total;
				almacenMenor = i;
			}
		}
		
		cout << "\n=== ALMACEN CON MENOR STOCK TOTAL ===\n";
		cout << "El almacen con menor stock es el almacen #" << almacenMenor + 1 << endl;
		cout << "Stock total: " << menorStock << " unidades\n";
	}
	
	// Inciso d) Emitir alertas por debajo del umbral minimo
	void emitirAlertasStockBajo() {
		cout << "\n=== ALERTAS DE STOCK BAJO ===\n";
		
		bool hayAlertas = false;
		
		for (int i = 0; i < CANT_ALMACENES; i++) {
			for (int j = 0; j < CANT_PRODUCTOS; j++) {
				if (stock[i][j] < umbral[j]) {
					cout << "Alerta: Almacen #" << i + 1
						<< ", Producto #" << j + 1
						<< " tiene " << stock[i][j]
						<< " unidades (umbral: " << umbral[j] << ")\n";
					
					hayAlertas = true;
				}
			}
		}
		
		if (!hayAlertas) {
			cout << "No hay productos por debajo del umbral minimo.\n";
		}
	}
};

int main() {
	Almacen almacen;
	int opcion;
	
	do {
		cout << "\n=====================================\n";
		cout << " SISTEMA DE CONTROL DE INVENTARIO\n";
		cout << "=====================================\n";
		cout << "1. Configurar umbrales minimos\n";
		cout << "2. Registrar existencias\n";
		cout << "3. Mostrar inventario\n";
		cout << "4. Detectar productos agotados\n";
		cout << "5. Identificar almacen con menor stock\n";
		cout << "6. Emitir alertas de stock bajo\n";
		cout << "7. Salir\n";
		cout << "Seleccione una opcion: ";
		cin >> opcion;
		
		switch (opcion) {
		case 1:
			almacen.configurarUmbrales();
			break;
			
		case 2:
			almacen.registrarExistencias();
			break;
			
		case 3:
			almacen.mostrarInventario();
			break;
			
		case 4:
			almacen.detectarProductosAgotados();
			break;
			
		case 5:
			almacen.identificarAlmacenMenorStock();
			break;
			
		case 6:
			almacen.emitirAlertasStockBajo();
			break;
			
		case 7:
			cout << "Saliendo del sistema...\n";
			break;
			
		default:
			cout << "Opcion invalida. Intente nuevamente.\n";
			break;
		}
		
	} while (opcion != 7);
	
	return 0;
}