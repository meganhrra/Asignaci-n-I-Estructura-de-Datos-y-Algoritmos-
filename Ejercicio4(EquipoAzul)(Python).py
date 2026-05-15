# Ejercicio 4 (ICPC) - Reasignacion optima entre almacenes
# Asignacion I - Estructura de Datos y Algoritmos
# Equipo Azul
#
# Version Python (el enunciado pide tambien Python para ICPC).
# Redistribuye productos entre 6 almacenes para que ninguno
# quede por debajo del umbral minimo, minimizando el costo
# total de transporte (cantidad * distancia).


class Redistribuidor:
    CANT_ALMACENES = 6
    CANT_PRODUCTOS = 15

    def __init__(self):
        self.movimientos = []
        self.costo_total = 0
        self.cargar_datos()

    def cargar_datos(self):
        self.stock = [
            #P0  P1  P2  P3  P4  P5  P6  P7  P8  P9  P10 P11 P12 P13 P14
            [50, 30, 15, 40, 25, 18, 35, 20, 22, 28, 16, 45, 10, 12, 38],  # Alm 0
            [25, 20, 18, 30, 22, 15, 28, 10, 35, 12, 40, 20, 10, 25, 16],  # Alm 1
            [15, 12, 10, 14, 10, 18, 11, 10, 10, 13, 10, 12,  5, 11, 10],  # Alm 2
            [40, 35, 28, 22, 30, 25, 18,  0, 32, 20, 15, 38, 10, 16, 22],  # Alm 3
            [22, 18, 25, 16, 12, 30, 20, 10, 18, 22, 16, 14, 10, 20, 13],  # Alm 4
            [30, 22, 18, 25, 15, 20, 22, 10, 12, 28, 18, 30, 15, 22, 14]   # Alm 5
        ]

        self.distancia = [
            [0, 4, 6, 7, 8, 9],
            [4, 0, 3, 6, 7, 8],
            [6, 3, 0, 4, 6, 5],
            [7, 6, 4, 0, 3, 6],
            [8, 7, 6, 3, 0, 4],
            [9, 8, 5, 6, 4, 0]
        ]

        self.umbral = [10] * self.CANT_PRODUCTOS

    def mostrar_stock(self, titulo):
        print(f"\n--- {titulo} ---")
        print("\t" + "\t".join(f"P{j}" for j in range(self.CANT_PRODUCTOS)))
        for i in range(self.CANT_ALMACENES):
            fila = "\t".join(str(self.stock[i][j]) for j in range(self.CANT_PRODUCTOS))
            print(f"Alm{i}\t{fila}")

    def mostrar_distancias(self):
        print("\n--- Matriz de distancias ---")
        print("\t" + "\t".join(f"Alm{j}" for j in range(self.CANT_ALMACENES)))
        for i in range(self.CANT_ALMACENES):
            fila = "\t".join(str(self.distancia[i][j]) for j in range(self.CANT_ALMACENES))
            print(f"Alm{i}\t{fila}")

    def mostrar_umbrales(self):
        umbrales_str = " ".join(str(u) for u in self.umbral)
        print(f"\nUmbrales minimos por producto: {umbrales_str}")

    def buscar_deficit(self, p):
        for i in range(self.CANT_ALMACENES):
            if self.stock[i][p] < self.umbral[p]:
                return i
        return -1

    def buscar_fuente_mas_cercana(self, alm_deficit, p):
        alm_fuente = -1
        menor_dist = -1

        for j in range(self.CANT_ALMACENES):
            if j != alm_deficit and self.stock[j][p] > self.umbral[p]:
                if alm_fuente == -1 or self.distancia[alm_deficit][j] < menor_dist:
                    alm_fuente = j
                    menor_dist = self.distancia[alm_deficit][j]

        return alm_fuente

    def redistribuir(self):
        self.movimientos = []
        self.costo_total = 0

        for p in range(self.CANT_PRODUCTOS):
            hubo_movimiento = True

            while hubo_movimiento:
                hubo_movimiento = False

                alm_deficit = self.buscar_deficit(p)
                if alm_deficit == -1:
                    break

                alm_fuente = self.buscar_fuente_mas_cercana(alm_deficit, p)
                if alm_fuente == -1:
                    break

                # Mover el minimo entre lo que falta y lo que sobra
                falta = self.umbral[p] - self.stock[alm_deficit][p]
                sobra = self.stock[alm_fuente][p] - self.umbral[p]
                a_mover = min(falta, sobra)

                self.stock[alm_fuente][p]  -= a_mover
                self.stock[alm_deficit][p] += a_mover

                costo = a_mover * self.distancia[alm_fuente][alm_deficit]
                self.costo_total += costo

                self.movimientos.append({
                    "producto": p,
                    "origen": alm_fuente,
                    "destino": alm_deficit,
                    "cantidad": a_mover,
                    "costo": costo
                })

                hubo_movimiento = True

    def mostrar_resultado(self):
        print("\n--- Resultado de la redistribucion ---")

        if not self.movimientos:
            print("No fue necesario realizar ningun movimiento.")
            return

        for m in self.movimientos:
            print(f"Producto {m['producto']}: {m['cantidad']} "
                  f"unidades movidas de Almacen {m['origen']} a "
                  f"Almacen {m['destino']}. Costo: {m['costo']}")

        print(f"\nTotal de movimientos realizados: {len(self.movimientos)}")
        print(f"Costo total: {self.costo_total}")

    def verificar_deficits_restantes(self):
        print("\n--- Verificacion final ---")
        deficits = 0

        for i in range(self.CANT_ALMACENES):
            for j in range(self.CANT_PRODUCTOS):
                if self.stock[i][j] < self.umbral[j]:
                    print(f"Aviso: Almacen {i}, Producto {j} sigue con "
                          f"{self.stock[i][j]} < umbral {self.umbral[j]} "
                          f"(no habia excedentes suficientes)")
                    deficits += 1

        if deficits == 0:
            print("Todos los almacenes quedaron por encima del umbral.")


def main():
    sistema = Redistribuidor()

    print("===========================================")
    print("  REASIGNACION OPTIMA ENTRE ALMACENES (ICPC)")
    print("===========================================")

    sistema.mostrar_stock("Stock INICIAL")
    sistema.mostrar_distancias()
    sistema.mostrar_umbrales()

    sistema.redistribuir()

    sistema.mostrar_resultado()
    sistema.mostrar_stock("Stock FINAL")
    sistema.verificar_deficits_restantes()


if __name__ == "__main__":
    main()