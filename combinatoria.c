/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *   Programa:        combinatoria.c
 *   Descripcion:     Determinar los valores maximos para n y k al calcular C(n,k) con
 *                    tres metodos distintos y realizar eventuales optimizaciones
 *   Autores:         Matías Olivares y Delian Santis
 *   Fecha revision:  31-08-2025  
 *   Compilador:      gcc.exe (MinGW.org GCC-6.3.0-1) 6.3.0 en VSCode
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>

#define MAX 100000   // número de bloques (ajustar según n máximo)
#define BASE 256    // cada bloque almacena un valor 0-255

// Metodos de ejecucion para el calculo de C(n,k) y n!
#define FIRST_REC        0
#define FIRST_REC_MEMO   1
#define FIRST_ITE        2
#define FIRST_ITE_MEMO   3
#define SECOND_REC       4
#define SECOND_MEMO      5
#define THIRD            6
//#define THIRD_SIM        7
#define FIRST_MULT_MEMO  8
#define SECOND_MULT_MEMO 9
#define FIRST_MULT_256   10

/*
 *
 */


// Funcion para indicar el modo de ejecucion del programa
void Usage(char const *);

// Funcion para verificar las condiciones necesarias de entrada para los metodos
unsigned int CheckValues(unsigned int n, unsigned int k);

// Funcion para calcular de manera recursiva el factorial de num (num!)
unsigned long long int FactorialRec(unsigned int num);

// Funcion para calcular de manera recursiva el factorial de num, con memoizacion (programacion dinamica)
unsigned long long int FactorialRecMemo(unsigned int num, unsigned long long int *memo);

// Funcion para calcular de manera iterativa el factorial de num (num!)
unsigned long long int Factorial(unsigned int num);

// Funcion para calcular de manera iterativa el factorial de num, con memoizacion (programacion dinamica)
unsigned long long int FactorialMemo(unsigned int num, unsigned long long int *memo);

// Primer metodo combinatorial: C(n,k) = n! / (n - k)! * k! con calculo de factorial recursivo y memoizacion
unsigned long long int FirstMethodRec(unsigned int n, unsigned int k, unsigned long long int *memo, unsigned char op);

// Primer metodo combinatorial: C(n,k) = n! / (n - k)! * k! con calculo de factorial recursivo y memoizacion
unsigned long long int FirstMethodIte(unsigned int n, unsigned int k, unsigned long long int *memo, unsigned char op);

// Segundo metodo combinatorial: C(n,k) = C(n-1,k-1) + C(n-1,k)
unsigned long long int SecondMethod(unsigned int n, unsigned int k);

// Segundo metodo combinatorial: C(n,k) = C(n-1,k-1) + C(n-1,k) con memoizacion
unsigned long long int SecondMethodMemoized(unsigned int n, unsigned int k, unsigned long long int **memo);

// Tercer metodo combinatorial: PI_{i=1}^{k} (n - i + 1 / i) mas optimizacion con simetria
unsigned long long int ThirdMethod(unsigned int n, unsigned int k);

// Primer metodo combinatorial simplificado: C(n,k) = PI_{i=1}^{k} (n - k + i)
unsigned long long int FirstMethodSimplified(unsigned int n, unsigned int k);

// Segundo metodo combinatorial simplificado: C(n,k) = [PI_{1}^{k-1} {(n - i) / i})] + [PI_{1}^{k} {(n - i) / i})]
unsigned long long int SecondMethodSimplified(unsigned int n, unsigned int k);

// Multiplica result * x
void MulBase256(unsigned char result[], int *size, unsigned int x);

// Divide result / m (exacto)
void DivBase256(unsigned char result[], int *size, unsigned int x);

// Imprime en decimal el número en base 256
void PrintDecimal(unsigned char result[], int size);

// Calcula combinatoria C(n,k) con el primer metodo simplificado
void FirstMethodSimplified256(unsigned int n, unsigned int k);

/*
 *
 */

int main(int argc, char const **argv) {
    
    unsigned long long int result, *cache = NULL, **table = NULL;
    unsigned int i, n, k;
    unsigned char method;
    float E_cpu;
    clock_t csc, cec;

    if (argc == 4) {
        
        n = strtoul(argv[2], NULL, 10); // Para convertir los argumentos de entrada a unsigned long long int
        k = strtoul(argv[3], NULL, 10);

        if (n < 0 || k < 0 || k > n) {
            printf("\nEnter a valid value for n and k (n >= 0, k >= 0, k <= n)\n");
            exit(EXIT_FAILURE);
        }
        
        if (strcmp(argv[1], "-0") == 0) {
            method = FIRST_REC;
            cache = (unsigned long long int *)calloc(n, sizeof(unsigned long long int));

            csc = clock(); // cpu start
            result = FirstMethodRec(n, k, cache, method);
            cec = clock(); // cpu exit

            E_cpu = (float)(cec - csc) / CLOCKS_PER_SEC;

            printf("\n%u - CPU time %f\n", n, E_cpu);

            printf("\nFirst method - recursive factorial: C(%u,%u) = %llu\n", n, k, result);
        } 
        else if (strcmp(argv[1], "-1") == 0) {
            method = FIRST_REC_MEMO;
            cache = (unsigned long long int *)calloc(n, sizeof(unsigned long long int));
            
            csc = clock(); // cpu start
            result = FirstMethodRec(n, k, cache, method);
            cec = clock(); // cpu exit

            E_cpu = (float)(cec - csc) / CLOCKS_PER_SEC;

            printf("\n%u - CPU time %f\n", n, E_cpu);

            printf("\nFirst method - recursive factorial with memoization: C(%u,%u) = %llu\n", n, k, result);
        } 
        else if (strcmp(argv[1], "-2") == 0) {
            method = FIRST_ITE;
            cache = (unsigned long long int *)calloc(n, sizeof(unsigned long long int));

            csc = clock(); // cpu start
            result = FirstMethodIte(n, k, cache, method);
            cec = clock(); // cpu exit

            E_cpu = (float)(cec - csc) / CLOCKS_PER_SEC;

            printf("\n%u - CPU time %f\n", n, E_cpu);

            printf("\nFirst method - iterative factorial: C(%u,%u) = %llu\n", n, k, result);
        } 
        else if (strcmp(argv[1], "-3") == 0) {
            method = FIRST_ITE_MEMO;
            cache = (unsigned long long int *)calloc(n, sizeof(unsigned long long int));

            csc = clock(); // cpu start
            result = FirstMethodIte(n, k, cache, method);
            cec = clock(); // cpu exit

            E_cpu = (float)(cec - csc) / CLOCKS_PER_SEC;

            printf("\n%u - CPU time %f\n", n, E_cpu);

            printf("\nFirst method - iterative factorial with memoization: C(%u,%u) = %llu\n", n, k, result);
        }
        else if (strcmp(argv[1], "-4") == 0) {
            method = SECOND_REC;

            if (k < 1) {
                printf("\nEnter a valid value for k (1 <= k < n)\n");
                exit(EXIT_FAILURE);
            }
            
            csc = clock(); // cpu start
            result = SecondMethod(n, k);
            cec = clock(); // cpu exit

            E_cpu = (float)(cec - csc) / CLOCKS_PER_SEC;

            printf("\n%u - CPU time %f\n", n, E_cpu);

            printf("\nSecond method recursive: C(%u,%u) = %llu\n", n, k, result);
        }
        else if (strcmp(argv[1], "-5") == 0) {
            method = SECOND_MEMO;

            if (k < 1) {
                printf("\nEnter a valid value for k (1 <= k < n)\n");
                exit(EXIT_FAILURE);
            }

            table = (unsigned long long int **)calloc(n, sizeof(unsigned long long int *));
            for (i = 0; i < n; i = i + 1) {
                table[i] = (unsigned long long int *)calloc(k, sizeof(unsigned long long int));
            }

            csc = clock(); // cpu start
            result = SecondMethodMemoized(n, k, table);
            cec = clock(); // cpu exit

            E_cpu = (float)(cec - csc) / CLOCKS_PER_SEC;

            printf("\n%u - CPU time %f\n", n, E_cpu);

            printf("\nSecond method recursive with memoization: C(%u,%u) = %llu\n", n, k, result);
        }
        else if (strcmp(argv[1], "-6") == 0) {
            method = THIRD;

            csc = clock(); // cpu start
            result = ThirdMethod(n, k);
            cec = clock(); // cpu exit

            E_cpu = (float)(cec - csc) / CLOCKS_PER_SEC;

            printf("\n%u - CPU time %f\n", n, E_cpu);

            printf("\nThird method multiplicative: C(%u,%u) = %llu\n", n, k, result);
        }
        else if (strcmp(argv[1], "-7") == 0) {
            // method = THIRD_SIM;

            // csc = clock(); // cpu start
            // result = ThirdMethod(n, k);
            // cec = clock(); // cpu exit

            // E_cpu = (float)(cec - csc) / CLOCKS_PER_SEC;

            // printf("\n%u - CPU time %f\n", n, E_cpu);

            // printf("\nThird method multiplicative with simetry: C(%u,%u) = %llu\n", n, k, result);
        }
        else if (strcmp(argv[1], "-8") == 0) {
            method = FIRST_MULT_MEMO;
            
            csc = clock(); // cpu start
            result = FirstMethodSimplified(n, k);
            cec = clock(); // cpu exit

            E_cpu = (float)(cec - csc) / CLOCKS_PER_SEC;

            printf("\n%u - CPU time %f\n", n, E_cpu);

            printf("\nFirst method multiplicative: C(%u,%u) = %llu\n", n, k, result);
        }
        else if (strcmp(argv[1], "-9") == 0) {
            method = SECOND_MULT_MEMO;
            
            if (k < 1) {
                printf("\nEnter a valid value for k (1 <= k < n)\n");
                exit(EXIT_FAILURE);
            }
            
            csc = clock(); // cpu start
            result = SecondMethodSimplified(n, k);
            cec = clock(); // cpu exit

            E_cpu = (float)(cec - csc) / CLOCKS_PER_SEC;

            printf("\n%u - CPU time %f\n", n, E_cpu);

            printf("\nSecond method multiplicative: C(%u,%u) = %llu\n", n, k, result);
        }
        else if (strcmp(argv[1], "-10") == 0) {
            method = FIRST_MULT_256;

            csc = clock(); // cpu start
            FirstMethodSimplified256(n, k);
            //FirstMethodSimplified256(n, k);
            cec = clock(); // cpu exit

            E_cpu = (float)(cec - csc) / CLOCKS_PER_SEC;

            printf("\n%u - CPU time %f\n", n, E_cpu);
        } 
        else {
            printf("\nEnter a valid modes (0 <= o <= 12)\n");
            exit(EXIT_FAILURE);
        } 
    }
    else {
        Usage(argv[0]);
    }

    // Liberacion de memoria asignada (si corresponde)
    if (cache != NULL) {
        free(cache);
    }

    if (table != NULL) {
        for (i = 0; i < n; i = i + 1) {
            free(table[i]);
        }
        free(table);
    }
    
    printf("\n\n");
    return 0;
}

/*
 *
 */

void Usage(char const *msg) {
    printf("\nUsage: %s -o n k", msg);
    printf("\n\no in {0,1,2,3,4,5,6,7,8}\n\n");
    printf("0: FIRST_REC\n");
    printf("1: FIRST_REC_MEMO\n");
    printf("2: FIRST_ITE\n");
    printf("3: FIRST_ITE_MEMO\n");
    printf("4: SECOND_REC\n");
    printf("5: SECOND_REC_MEMO\n");
    printf("6: THIRD\n");
    printf("7: THIRD_SIM\n");
    printf("8: FIRST_MULT_MEMO\n");
    printf("9: SECOND_MULT_MEMO\n");
    printf("10: FIRST_MULT_256\n");
}

unsigned int CheckValues(unsigned int n, unsigned int k) {

    if(k == 0 || k == n) { // Casos base (C(n,0) = C(n,n) = 1)
        return 1;
    }
    else if(k == 1) { // Caso especial (C(n,1) = n)
        return n;
    }

    return 0;
}

unsigned long long int FactorialRec(unsigned int num) {

    if(num == 0 || num == 1) { // Caso base (1! = 0! = 1)
        return 1;
    }
        
    return num * FactorialRec(num - 1); // Recursion (n! = n * (n - 1)!)
}

unsigned long long int FactorialRecMemo(unsigned int num, unsigned long long int *memo) {

    if(num == 0 || num == 1) { // Caso base (1! = 0! = 1)
        memo[0] = 1;
        return memo[0];
    }

    if (memo[num - 1] != 0) { // Si el valor del factorial ya fue calculado, se devuelve
        return memo[num - 1];
    }
    else { // Se calcula el factorial, se guarda en el arreglo memo y se devuelve el valor
        memo[num - 1] = num * FactorialRecMemo(num - 1, memo); // Recursion (n! = n * (n - 1)!)
        return memo[num - 1];
    }
}

unsigned long long int Factorial(unsigned int num) {

    unsigned long long int prod;
    unsigned int i;

    if (num == 0 || num == 1) { // Convencion (0! = 1! = 1)
        return 1;
    }
        
    prod = 1;

    for (i = 2; i <= num; i = i + 1) { // Iteracion sobre el producto de numeros desde 2 hasta num
        prod = prod * i;
    }

    return prod;
}

unsigned long long int FactorialMemo(unsigned int num, unsigned long long int *memo) {

    unsigned long long int result;
    unsigned int i;

    memo[0] = 1;

    for (i = 2; i <= num; i = i + 1) {
        memo[i - 1] = memo[i - 2] * i;
        result = memo[i - 1];
    }

    return result;
}

unsigned long long int FirstMethodRec(unsigned int n, unsigned int k, unsigned long long int *memo, unsigned char op) {

    unsigned long long int base = CheckValues(n, k); 

    if (base != 0) { // Si es caso base, retornar directamente
        return base;
    }

    if (op == FIRST_REC) {
        return ((FactorialRec(n)) / (FactorialRec(n - k) * (FactorialRec(k))));
    }
    else if (op == FIRST_REC_MEMO) {
        return ((FactorialRecMemo(n, memo)) / (FactorialRecMemo(n - k, memo) * (FactorialRecMemo(k, memo))));
    }
}

unsigned long long int FirstMethodIte(unsigned int n, unsigned int k, unsigned long long int *memo, unsigned char op) {

    unsigned long long int base = CheckValues(n, k); 

    if (base != 0) { // Si es caso base, retornar directamente
        return base;
    }

    if (op = FIRST_ITE) { // Primer metodo con factorial iterativo
        return ((Factorial(n)) / (Factorial(n - k) * (Factorial(k))));
    }
    else if (op == FIRST_ITE_MEMO) { // Segundo metodo con factorial recursivo
        return ((FactorialMemo(n, memo)) / (FactorialMemo(n - k, memo) * (FactorialMemo(k, memo))));
    } 
}

unsigned long long int SecondMethod(unsigned int n, unsigned int k) {

    // No se usa la funcion CheckValues por las llamadas recursivas, para evitar desbordamiento de la pila
    if(k == 0 || k == n) { // Casos base (C(n,0) = C(n,n) = 1)
        return 1;
    }
    else if(k == 1) { // Caso especial (C(n,1) = n)
        return n;
    }

    return (SecondMethod(n - 1, k - 1) + SecondMethod(n - 1, k)); // Recursion (C(n,k) = C(n-1,k-1) + C(n-1,k))
}

unsigned long long int SecondMethodMemoized(unsigned int n, unsigned int k, unsigned long long int **memo) {

    unsigned int i;

    // No se usa la funcion CheckValues por las llamadas recursivas, para evitar desbordamiento de la pila
    if(k == 0 || k == n) { // Casos base (C(n,0) = C(n,n) = 1)
        memo[n-1][k-1] = 1;
        return memo[n-1][k-1];
    }
    else if(k == 1) { // Caso especial (C(n,1) = n)
        memo[n-1][k-1] = n;
        return memo[n-1][k-1];
    }

    if(memo[n-1][k-1] != 0) { // Verifica si ya esta calculado la combinatoria
        return memo[n-1][k-1];
    }
    else {
        memo[n-1][k-1] = SecondMethodMemoized(n - 1, k - 1, memo) + SecondMethodMemoized(n - 1, k, memo);
        return memo[n-1][k-1];
    }
}

unsigned long long int ThirdMethod(unsigned int n, unsigned int k) {

    unsigned long long int prod, base = CheckValues(n, k); 
    unsigned int i;

    // No se usa la funcion CheckValues por las llamadas recursivas, para evitar desbordamiento de la pila
    if(k == 0 || k == n) { // Casos base (C(n,0) = C(n,n) = 1)
        return 1;
    }
    else if(k == 1) { // Caso especial (C(n,1) = n)
        return n;
    }

    return (n * ThirdMethod(n - 1, k - 1)) / k;; // Recursion (C(n,k) = n/k * C(n-1,k-1))
}

unsigned long long int FirstMethodSimplified(unsigned int n, unsigned int k) {

    unsigned long long int prod, base = CheckValues(n, k); 
    unsigned int i;

    if (base != 0) { // Si es caso base, retornar directamente
        return base;
    }

    prod = 1;

    for (i = 1; i <= k; i = i + 1) {
       prod = prod * (n - k + i);
       prod = prod / i;
    }

    return prod;
}

unsigned long long int SecondMethodSimplified(unsigned int n, unsigned int k) {

    unsigned long long int first_mult, second_mult, base = CheckValues(n, k);
    unsigned int i;

    if (base != 0) { // Si es caso base, retornar directamente
        return base;
    }

    first_mult = 1; 

    for (i = 1; i <= k - 1; i = i + 1) { // Resuelve la multiplicidad (simplificacion) del primer sumando
        first_mult = first_mult * (n - i);
        first_mult = first_mult / i;
    }

    second_mult = 1;

    for (i = 1; i <= k; i = i + 1) { // Resuelve la multiplicidad (simplificacion) del segundo sumando
        second_mult = second_mult * (n - i);
        second_mult = second_mult / i;
    }  

    return (first_mult + second_mult);
}

// result * x
void MulBase256(unsigned char result[], int *size, unsigned int x) {

    unsigned long long int prod, carry;
    int i;

    carry = 0;

    for (i = 0; i < *size; i = i + 1) {
        prod = (unsigned long long int)result[i] * x + carry;
        result[i] = prod % BASE;
        carry = prod / BASE;
    }
    while (carry > 0 && *size < MAX) {
        result[*size] = carry % BASE;
        carry = carry / BASE;
        *size = *size + 1;
    }
}

// result / x
void DivBase256(unsigned char result[], int *size, unsigned int x) {

    unsigned long long int rem, cur;
    int i;

    rem = 0;

    for (i = *size - 1; i >= 0; i = i - 1) {
        cur = rem * BASE + result[i];
        result[i] = cur / x;
        rem = cur % x;
    }
    while (*size > 1 && result[*size - 1] == 0) {
        *size = *size - 1;
    }
}

void PrintDecimal(unsigned char result[], int size) {

    int i, j, k, dec_size, carry, val, decimal[MAX * 3]; // almacenamiento temporal en base 10

    dec_size = 1;
    decimal[0] = 0;

    for (i = size - 1; i >= 0; i = i - 1) {
        carry = result[i];
        for (j = 0; j < dec_size; j = j + 1) {
            val = decimal[j] * BASE + carry;
            decimal[j] = val % 10;
            carry = val / 10;
        }
        while (carry > 0) {
            decimal[dec_size] = carry % 10;
            carry = carry / 10;
            dec_size = dec_size + 1;
        }
    }

    for (k = dec_size - 1; k >= 0; k = k - 1) {
        printf("%u", decimal[k]);
    }
}

void FirstMethodSimplified256(unsigned int n, unsigned int k) {
    
    unsigned char result[MAX];
    int i, size;

    // Propiedad de simetria: C(n,k) = C(n,n-k)
    if (k > n / 2) {
        k = n - k;
    } 
    
    for (i = 0; i < MAX; i = i + 1) { 
        result[i] = 0;
    }
    result[0] = 1;

    size = 1;

    for (i = 1; i <= k; i = i + 1) {
        MulBase256(result, &size, n - k + i);
        DivBase256(result, &size, i);
    }

    printf("\nFirst method multiplicative with 256 base: C(%u,%u) = ", n, k);
    PrintDecimal(result, size);
    printf("\n");
}