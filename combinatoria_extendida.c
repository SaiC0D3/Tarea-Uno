#include <stdio.h>

#define MAX 20000   // número de bloques (ajustar según n máximo)
#define BASE 256    // cada bloque almacena un valor 0-255

// Inicializa result = 1
void initBigInt(unsigned char result[], int *size) {
    for (int i = 0; i < MAX; i++) result[i] = 0;
    result[0] = 1;
    *size = 1;
}

// Multiplica result * m
void mulBigInt(unsigned char result[], int *size, int m) {
    unsigned long long prod, carry = 0;
    for (int i = 0; i < *size; i++) {
        prod = (unsigned long long)result[i] * m + carry;
        result[i] = prod % BASE;
        carry = prod / BASE;
    }
    while (carry > 0) {
        result[(*size)++] = carry % BASE;
        carry /= BASE;
    }
}

// Divide result / m (exacto)
void divBigInt(unsigned char result[], int *size, int m) {
    unsigned long long rem = 0, cur;
    for (int i = *size - 1; i >= 0; i--) {
        cur = rem * BASE + result[i];
        result[i] = cur / m;
        rem = cur % m;
    }
    while (*size > 1 && result[*size - 1] == 0) (*size)--;
}

// Imprime en decimal el número en base 256
void printBigInt(unsigned char result[], int size) {
    int decimal[MAX * 3]; // almacenamiento temporal en base 10
    int dec_size = 1;
    decimal[0] = 0;

    for (int j = size - 1; j >= 0; j--) {
        int carry = result[j];
        for (int k = 0; k < dec_size; k++) {
            int val = decimal[k] * BASE + carry;
            decimal[k] = val % 10;
            carry = val / 10;
        }
        while (carry > 0) {
            decimal[dec_size++] = carry % 10;
            carry /= 10;
        }
    }

    for (int k = dec_size - 1; k >= 0; k--) printf("%d", decimal[k]);
}

// Calcula combinatoria C(n,k)
void combinatoria(int n, int k) {
    if (k < 0 || k > n) {
        printf("C(%d,%d) = 0\n", n, k);
        return;
    }
    if (k > n - k) k = n - k;  // simetría

    unsigned char result[MAX];
    int size;
    initBigInt(result, &size);

    for (int i = 1; i <= k; i++) {
        mulBigInt(result, &size, n - k + i);
        divBigInt(result, &size, i);
    }

    printf("C(%d,%d) = ", n, k);
    printBigInt(result, size);
    printf("\n");
}

int main() {
    int n, k;
    printf("Ingrese n y k: ");
    scanf("%d %d", &n, &k);
    combinatoria(n, k);
    return 0;
}
