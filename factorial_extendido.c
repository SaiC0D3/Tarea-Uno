#include <stdio.h>
#include <stdlib.h>

#define MAX 100000   // Número de bloques (elementos del arreglo) : Maxima capacidad de la pila (1Mb windows - 4Mb linux)
#define BASE 256    // Cada bloque es 1 byte (0–255)

// Tamaño estimado del arreglo decimal (3 dígitos por byte de base 256)
#define DEC_MAX (MAX * 3)

// Calcula n! y lo imprime en decimal
void factorial_dinamic(int n) {
    // --- Representación en base 256 ---
    // Cada bloque es un "byte" de 0 a 255
    unsigned char result[MAX];
    unsigned long long prod, extra;
    int size = 1;   // número de bloques usados

    // Inicializamos el resultado en 1
    for (int i = 0; i < MAX; i++) result[i] = 0;
    result[0] = 1;

    // --- Cálculo de n! ---
    for (int i = 2; i <= n; i++) {
        extra = 0;
        for (int j = 0; j < size; j++) {
            // Multiplicamos bloque por i y añadimos el acarreo
            prod = (unsigned long long)result[j] * i + extra;
            result[j] = prod % BASE;   // guardamos el valor reducido al rango [0,255]
            extra = prod / BASE;       // lo que "sobra" pasa al siguiente bloque
        }
        // Si aún queda acarreo, agregamos bloques adicionales
        while (extra > 0) {
            result[size++] = extra % BASE;
            extra /= BASE;
        }
    }

    // --- Conversión a decimal ---
    // Representaremos el número decimal en un arreglo de caracteres.
    // Como cada byte puede aportar hasta 3 cifras decimales, reservamos de sobra.
    char *decimal = (char *)calloc(DEC_MAX, sizeof(char));
    int dec_size = 1;
    decimal[0] = '0';  // empezamos en "0"

    // Convertimos de base 256 a base 10 (simulando divisiones)
    for (int j = size - 1; j >= 0; j--) {
        int carry = result[j];
        for (int k = 0; k < dec_size; k++) {
            int val = (decimal[k] - '0') * BASE + carry;
            decimal[k] = (val % 10) + '0';
            carry = val / 10;
        }
        while (carry > 0) {
            decimal[dec_size++] = (carry % 10) + '0';
            carry /= 10;
        }
    }

    // --- Impresión ---
    printf("%d! = ", n);
    for (int k = dec_size - 1; k >= 0; k--) {
        printf("%c", decimal[k]);
    }
    printf("\n");

    free(decimal);
}

int main() {
    int num;
    unsigned int modo;

    do {
        printf("\nIngrese un valor entero positivo: "); scanf("%d", &num);
    } while (num < 0);

    printf("\nIngrese el modo (1: E, 2: D): "); scanf("%u", &modo);

    if (modo == 1) {
        factorial_static(num);
    }
    else {
        factorial_dinamic(num);
    }

    printf("\n");
    return 0;
}
