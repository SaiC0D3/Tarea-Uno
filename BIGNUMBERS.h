#include <stdio.h> 
#include <stdlib.h>

#define MAX_BLOCKS 99999 // Cantidad maxima de bloques para almacenar una combinatoria en base 256 (1Mb en el stack)
#define BASE 256          // Cantidad de digitos (0-255) por cada bloque

struct BigNum {
    unsigned char digits[MAX_BLOCKS]; // Digitos en base 256
    int size;                         // Cantidad de bloques usados
};

// Funcion para inicializar en cero los digitos del numero grande
void InitBigNum(struct BigNum *num) {

    int i;

    for (i = 0; i < MAX_BLOCKS; i = i + 1) {
        num->digits[i] = 0;
    }

    num->size = 1; // Establecemos el largo del BigNum en 1 bloque
    num->digits[0] = 1; // Establecemos el primer bloque en 1 a conveniencia para la aritmetica 
}

// Multiplica un BigNum por un entero x: result = result * x
void MulBigNum(struct BigNum *result, unsigned int x) {

    unsigned long long int prod, carry;
    int i;

    carry = 0; // Acarreo inicial nulo

    // Multiplicacion bloque a bloque
    for (i = 0; i < result->size; i = i + 1) {
        prod = (unsigned long long int)result->digits[i] * x + carry; // Calculamos el producto de bloque actual por x con acarreo
        result->digits[i] = prod % BASE; // Almacenamos el producto en base 256 como digito del bloque actual
        carry = prod / BASE; // Obtenemos el acarreo para el siguiente bloque
    }

    // Si quedan acarreos al terminar, agregamos mas bloques al BigInt
    while (carry > 0 && result->size < MAX_BLOCKS) {
        result->digits[result->size] = carry % BASE; // Guardamos el acarreo en base 256 al nuevo bloque
        carry = carry / BASE; // Reducimos el acarreo en la base
        result->size = result->size + 1; // Aumentamos el largo del BigInt
    }
}

// Divide un BigNum por un entero x: result = result / x
void DivBigNum(struct BigNum *result, unsigned int x) {

    unsigned long long int rem, current;
    int i;

    rem = 0; // Resto inicial nulo

    // Division en orden inverso bloque a bloque
    for (i = result->size - 1; i >= 0; i = i - 1) {
        current = rem * BASE + result->digits[i]; // Agregamos el acarreo (resto veces la BASE) al bloque actual
        result->digits[i] = current / x; // Calculamos la division del bloque actual por x
        rem = current % x; // Obtenemos el nuevo resto
    }

    // Elimiamos ceros sobrantes en los ultimos bloques, ajustando el largo del BigInt
    while (result->size > 1 && result->digits[result->size - 1] == 0) {
        result->size = result->size - 1;
    }
}

// Suma de BigNum: result1 = result1 + resul2
void AddTwoBigNums(struct BigNum *result1, struct BigNum *result2) {
    
    unsigned int carry, sum;
    int i;

    carry = 0; // Acarreo inicial nulo

    // Suma de los BigInt bloque a bloque mientras queden digitos en alguno o quede acarreo
    for (i = 0; i < result1->size || i < result2->size || carry > 0; i = i + 1) {
        if (i >= result1->size) {  // Si el primero era mas chico, extendemos su largo para la suma con el segundo
            result1->digits[i] = 0; // Inicializacion en cero
            result1->size = result1->size + 1;
        }

        if (i < result2->size) { // Mientras queden bloques del segundo, los sumamos con los del primero mas el acarreo
            sum = result1->digits[i] + result2->digits[i] + carry;
        }
        else { // Si no quedan bloques del segundo, sumamos el acarreo restante
            sum = result1->digits[i] + carry;
        }

        result1->digits[i] = sum % BASE; // Reducimos la suma resultante en base 256 y la almacenamos en el bloque actual del primero
        carry = sum / BASE; // Obtenemos el acarreo ára elsiguiente bloque
    }
}

// Convierte un BigNum en base 256 a decimal y lo imprime
void PrintDecimal(struct BigNum *num) {

    int i, j, k, dec_size, carry, val, decimal[MAX_BLOCKS * 3]; // Se reserva un arreglo mas grande dado que cada byte (0–255) puede generar hasta 3 digitos decimales

    dec_size = 1; // Establecemos el largo del nuemro decimal en 1 digito
    decimal[0] = 0; // Inicializamos el primer digito en 0

    // Convertimos de base 256 a base 10 bloque a bloque en orden inverso
    for (i = num->size - 1; i >= 0; i = i - 1) {
        carry = num->digits[i]; // Obtenemos el acarreo como digitos del bloque actual

        for (j = 0; j < dec_size; j = j + 1) { 
            val = decimal[j] * BASE + carry; // Multiplicamos por 256 y sumamos el acarreo 
            decimal[j] = val % 10; // Obtenemos el valor en base 10 del bloque actual
            carry = val / 10; // Obtenemos el acarreo restante
        }

        // Si quedan acarreos pendientes, extendemos el largo del numero decimal
        while (carry > 0) {
            decimal[dec_size] = carry % 10; // Almacenamos el acarreo en base 10
            carry = carry / 10; // Reducimos el acarreo en base 10
            dec_size = dec_size + 1;
        }
    }

    // Imprimimos en orden inverso el numero decimal
    for (k = dec_size - 1; k >= 0; k = k - 1) {
        printf("%u", decimal[k]);
    }
}