#include <stdio.h>
#define MAX 100000 // Maximo de "bloques"
#define BASE 1000000000  // 2^63 = 9223372036854775808
#define DIGITS 9 // log10(2^63) ≈ 18.96 → 19 dígitos

void factorial(int n) {
    unsigned long long int result[MAX], extra, prod;
    int size = 1, i, j, k;
    result[0] = 1;

    for (i = 2; i <= n; i = i + 1) {
        extra = 0;
        for (j = 0; j < size; j = j + 1) {
            prod = result[j] * (unsigned long long int)i + extra; // Multiplicacion de a bloques de digitos segun la base
            result[j] = prod % BASE; // Guardamos la cantidad de digitos contenidos por la base 
            extra = prod / BASE; // Obtenemos los digitos extra para sumarlos al siguiente producto de digitos
        }
        while (extra != 0) { // Propagamos los digitos extra hacia los digitos diguientes a multiplicar
            result[size] = extra % BASE;
            extra = extra / BASE;
            size = size + 1;
        }
    }

    // imprimir (la ultima sin ceros, las demas con DIGITS digitos)
    printf("%d! = %llu", n, result[size - 1]);
    for (k = size - 2; k >= 0; k = k - 1) {
        printf("%0*llu", DIGITS, result[k]);
    }
    printf("\n");
}

int main() {
    int num; // MAXIMO = 12309

    do {
        printf("\nIngrese un valor entero positivo: "); scanf("%d", &num);
    } while (num < 0);

    factorial(num);

    printf("\n");
    return 0;
}
