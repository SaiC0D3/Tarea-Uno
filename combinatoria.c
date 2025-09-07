/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *   Programa:        combinatoria.c
 *   Descripcion:     Calcula C(n,k) con tres metodos distintos, sus versiones optimizadas sin recursion,
 *                    algunas con memoizacion y otras con covnersion a base 256, ademas del tiempo CPU
 *   Autores:         Matias Olivares Morales y Delian Santis Lopez
 *   Ultima revision: 07-09-2025  
 *   Compilador:      gcc.exe (MinGW.org GCC-6.3.0-1) 6.3.0
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include "FACTORIALS.h"
#include "BIGNUMBERS.h"

#define FIRST_REC_FACT        0
#define FIRST_REC_FACT_MEMO   1
#define FIRST_ITE_FACT        2
#define FIRST_ITE_FACT_MEMO   3

// Funcion para indicar el modo de ejecucion correcto del programa
void Usage(char const *);

// Funcion para verificar las condiciones necesarias de entrada para los metodos
unsigned int CheckValues(unsigned int n, unsigned int k);

// Primer metodo combinatorial: C(n,k) = n! / (n - k)! * k! con calculo de factorial recursivo y memoizacion
unsigned long long int FirstMethodRecursiveFact(unsigned int n, unsigned int k, unsigned long long int *memo, unsigned char op);

// Primer metodo combinatorial: C(n,k) = n! / (n - k)! * k! con calculo de factorial recursivo y memoizacion
unsigned long long int FirstMethodIterativeFact(unsigned int n, unsigned int k, unsigned long long int *memo, unsigned char op);

// Segundo metodo combinatorial: C(n,k) = C(n-1,k-1) + C(n-1,k)
unsigned long long int SecondMethod(unsigned int n, unsigned int k);

// Segundo metodo combinatorial: C(n,k) = C(n-1,k-1) + C(n-1,k) con memoizacion
unsigned long long int SecondMethodMemoized(unsigned int n, unsigned int k, unsigned long long int **memo);

// Tercer metodo combinatorial: C(n,k) = n/k * C(n-1,k-1)
unsigned long long int ThirdMethod(unsigned int n, unsigned int k);

// Tercer metodo combinatorial: C(n,k) = n/k * C(n-1,k-1) con memoizacion
unsigned long long int ThirdMethodMemoized(unsigned int n, unsigned int k, unsigned long long int **memo);

// Primer metodo combinatorial simplificado (con simetria): C(n,k) = PI_{i=1}^{k} ((n - k + i) / i)
unsigned long long int FirstMethodSimplified(unsigned int n, unsigned int k);

// Segundo metodo combinatorial simplificado (con simetria): C(n,k) = [PI_{1}^{k-1} ((n - i) / i))] + [PI_{1}^{k} ((n - i) / i))]
unsigned long long int SecondMethodSimplified(unsigned int n, unsigned int k);

// Tercer metodo combinatorial simplificado (con simetria): C(n,k) = (n / k) * (PI_{i=1}^{k-1} (n - i))
unsigned long long int ThirdMethodSimplified(unsigned int n, unsigned int k);

// Primer metodo combinatorial simplificado con base 256: C(n,k) = PI_{i=1}^{k} ((n - k + i) / i)
void FirstMethodSimplified256(unsigned int n, unsigned int k);

// Segundo metodo combinatorial simplificado con base 256: C(n,k) = [PI_{1}^{k-1} ((n - i) / i))] + [PI_{1}^{k} ((n - i) / i))]
void SecondMethodSimplified256(unsigned int n, unsigned int k);

// Tercer metodo combinatorial simplificado con base 256: C(n,k) = (n / k) * (PI_{i=1}^{k-1} (n - i))
void ThirdMethodSimplified256(unsigned int n, unsigned int k);

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

            method = FIRST_REC_FACT;
            cache = (unsigned long long int *)calloc(n, sizeof(unsigned long long int));

            csc = clock(); // cpu start
            result = FirstMethodRecursiveFact(n, k, cache, method);
            cec = clock(); // cpu exit

            E_cpu = (float)(cec - csc) / CLOCKS_PER_SEC;

            printf("%u  %f\n", n, E_cpu);

            //printf("\nFirst method - recursive factorial: C(%u,%u) = %llu\n", n, k, result);
        } 
        else if (strcmp(argv[1], "-1") == 0) {

            method = FIRST_REC_FACT_MEMO;
            cache = (unsigned long long int *)calloc(n, sizeof(unsigned long long int));
            
            csc = clock(); // cpu start
            result = FirstMethodRecursiveFact(n, k, cache, method);
            cec = clock(); // cpu exit

            E_cpu = (float)(cec - csc) / CLOCKS_PER_SEC;

            printf("%u  %f\n", n, E_cpu);

            //printf("\nFirst method - recursive factorial with memoization: C(%u,%u) = %llu\n", n, k, result);
        } 
        else if (strcmp(argv[1], "-2") == 0) {

            method = FIRST_ITE_FACT;
            cache = (unsigned long long int *)calloc(n, sizeof(unsigned long long int));

            csc = clock(); // cpu start
            result = FirstMethodIterativeFact(n, k, cache, method);
            cec = clock(); // cpu exit

            E_cpu = (float)(cec - csc) / CLOCKS_PER_SEC;

            printf("%u  %f\n", n, E_cpu);

            //printf("\nFirst method - iterative factorial: C(%u,%u) = %llu\n", n, k, result);
        } 
        else if (strcmp(argv[1], "-3") == 0) {

            method = FIRST_ITE_FACT_MEMO;
            cache = (unsigned long long int *)calloc(n, sizeof(unsigned long long int));

            csc = clock(); // cpu start
            result = FirstMethodIterativeFact(n, k, cache, method);
            cec = clock(); // cpu exit

            E_cpu = (float)(cec - csc) / CLOCKS_PER_SEC;

            printf("%u  %f\n", n, E_cpu);

            //printf("\nFirst method - iterative factorial with memoization: C(%u,%u) = %llu\n", n, k, result);
        }
        else if (strcmp(argv[1], "-4") == 0) {

            if (k < 1) {
                printf("\nEnter a valid value for k (1 <= k < n)\n");
                exit(EXIT_FAILURE);
            }
            
            csc = clock(); // cpu start
            result = SecondMethod(n, k);
            cec = clock(); // cpu exit

            E_cpu = (float)(cec - csc) / CLOCKS_PER_SEC;

            printf("%u  %f\n", n, E_cpu);

            //printf("\nSecond method recursive: C(%u,%u) = %llu\n", n, k, result);
        }
        else if (strcmp(argv[1], "-5") == 0) {

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

            printf("%u  %f\n", n, E_cpu);

            //printf("\nSecond method recursive with memoization: C(%u,%u) = %llu\n", n, k, result);
        }
        else if (strcmp(argv[1], "-6") == 0) {

            csc = clock(); // cpu start
            result = ThirdMethod(n, k);
            cec = clock(); // cpu exit

            E_cpu = (float)(cec - csc) / CLOCKS_PER_SEC;

            printf("%u  %f\n", n, E_cpu);

            //printf("\nThird method recursive: C(%u,%u) = %llu\n", n, k, result);
        }
        else if (strcmp(argv[1], "-7") == 0) {

            table = (unsigned long long int **)calloc(n, sizeof(unsigned long long int *));
            for (i = 0; i < n; i = i + 1) {
                table[i] = (unsigned long long int *)calloc(k, sizeof(unsigned long long int));
            }

            csc = clock(); // cpu start
            result = ThirdMethodMemoized(n, k, table);
            cec = clock(); // cpu exit

            E_cpu = (float)(cec - csc) / CLOCKS_PER_SEC;

            printf("%u  %f\n", n, E_cpu);

            //printf("\nThird method recursive with memoization: C(%u,%u) = %llu\n", n, k, result);
        }
        else if (strcmp(argv[1], "-8") == 0) {

            csc = clock(); // cpu start
            result = FirstMethodSimplified(n, k);
            cec = clock(); // cpu exit

            E_cpu = (float)(cec - csc) / CLOCKS_PER_SEC;

            printf("%u  %f\n", n, E_cpu);

            //printf("\nFirst method multiplicative: C(%u,%u) = %llu\n", n, k, result);
        }
        else if (strcmp(argv[1], "-9") == 0) {

            if (k < 1) {
                printf("\nEnter a valid value for k (1 <= k < n)\n");
                exit(EXIT_FAILURE);
            }
            
            csc = clock(); // cpu start
            result = SecondMethodSimplified(n, k);
            cec = clock(); // cpu exit

            E_cpu = (float)(cec - csc) / CLOCKS_PER_SEC;

            printf("%u  %f\n", n, E_cpu);

            //printf("\nSecond method multiplicative: C(%u,%u) = %llu\n", n, k, result);
        }
        else if (strcmp(argv[1], "-10") == 0) {

            csc = clock(); // cpu start
            result = ThirdMethodSimplified(n, k);
            cec = clock(); // cpu exit

            E_cpu = (float)(cec - csc) / CLOCKS_PER_SEC;

            printf("%u  %f\n", n, E_cpu);

            //printf("\nThird method multiplicative: C(%u,%u) = %llu\n", n, k, result);
        }
        else if (strcmp(argv[1], "-11") == 0) {

            csc = clock(); // cpu start
            FirstMethodSimplified256(n, k);
            cec = clock(); // cpu exit

            E_cpu = (float)(cec - csc) / CLOCKS_PER_SEC;

            printf("%u  %f\n", n, E_cpu);
        } 
        else if (strcmp(argv[1], "-12") == 0) {

            csc = clock(); // cpu start
            SecondMethodSimplified256(n, k);
            cec = clock(); // cpu exit

            E_cpu = (float)(cec - csc) / CLOCKS_PER_SEC;

            printf("%u  %f\n", n, E_cpu);
        }
        else if (strcmp(argv[1], "-13") == 0) {

            csc = clock(); // cpu start
            ThirdMethodSimplified256(n, k);
            cec = clock(); // cpu exit

            E_cpu = (float)(cec - csc) / CLOCKS_PER_SEC;

            printf("%u  %f\n", n, E_cpu);
        }
        else {
            printf("\nEnter a valid mode (0 <= o <= 13)\n\n");
            exit(EXIT_FAILURE);
        } 
    }
    else {
        Usage(argv[0]);
    }

    // Liberacion de memoria dinamica asignada (si corresponde)
    if (cache != NULL) {
        free(cache);
    }

    if (table != NULL) {
        for (i = 0; i < n; i = i + 1) {
            free(table[i]);
        }
        free(table);
    }
    
    //printf("\n");
    return 0;
}

/*
 *
 */
void Usage(char const *msg) {
    printf("\nUsage: %s -o n k", msg);
    printf("\n\no in {0,1,2,3,4,5,6,7,8,9,10,11,12,13}\n\n");
    printf("0: First Method - Recursive Factorial\n");
    printf("1: First Method - Recursive Factorial with Memoization\n");
    printf("2: First Method - Iterative Factorial\n");
    printf("3: First Method - Iterative Factorial with Memoization\n");
    printf("4: Second Method Recursive\n");
    printf("5: Second Method Recursive with Memoization\n");
    printf("6: Third Method Recursive\n");
    printf("7: Third Method Recursive with Memoization\n");
    printf("8: First Method Multiplicative\n");
    printf("9: Second Method Multiplicative\n");
    printf("10: Third Method Multiplicative\n");
    printf("11: First Method Multiplicative - 256 Base\n");
    printf("12: Second Method Multiplicative - 256 Base\n");
    printf("13: Third Method Multiplicative - 256 Base\n");
}

unsigned int CheckValues(unsigned int n, unsigned int k) {

    if(k == 0 || k == n) { // Casos base (C(n,0) = C(n,n) = 1)
        return 1;
    }
    else if(k == 1) { // Caso especial (C(n,1) = n)
        return n;
    }

    return 0; // No es un caso base
}

unsigned long long int FirstMethodRecursiveFact(unsigned int n, unsigned int k, unsigned long long int *memo, unsigned char op) {

    unsigned long long int base;

    base = CheckValues(n, k);

    if (base != 0) { // Si alguno de los casos base ocurre, devolvemos el valor correspondiente
        return base;
    }

    if (op == FIRST_REC_FACT) { // Primer metodo con factorial recurisvo (C(n,k) = n! / (n - k)! * k!)
        return ((FactorialRec(n)) / (FactorialRec(n - k) * (FactorialRec(k))));
    }
    else if (op == FIRST_REC_FACT_MEMO) { // Primer metodo con factorial recurisvo + memoizacion (C(n,k) = n! / (n - k)! * k!)
        return ((FactorialRecMemo(n, memo)) / (FactorialRecMemo(n - k, memo) * (FactorialRecMemo(k, memo))));
    }
}

unsigned long long int FirstMethodIterativeFact(unsigned int n, unsigned int k, unsigned long long int *memo, unsigned char op) {

    unsigned long long int base;

    base = CheckValues(n, k);

    if (base != 0) { // Si alguno de los casos base ocurre, devolvemos el valor correspondiente
        return base;
    }

    if (op == FIRST_ITE_FACT) { // Primer metodo con factorial iterativo (C(n,k) = n! / (n - k)! * k!)
        return ((Factorial(n)) / (Factorial(n - k) * (Factorial(k))));
    }
    else if (op == FIRST_ITE_FACT_MEMO) { // Primer metodo con factorial iterativo + memoizacion (C(n,k) = n! / (n - k)! * k!)
        return ((FactorialMemo(n, memo)) / (FactorialMemo(n - k, memo) * (FactorialMemo(k, memo))));
    } 
}

unsigned long long int SecondMethod(unsigned int n, unsigned int k) {

    if(k == 0 || k == n) { // Casos base (C(n,0) = C(n,n) = 1)
        return 1;
    }
    else if(k == 1) { // Caso especial (C(n,1) = n)
        return n;
    }

    return (SecondMethod(n - 1, k - 1) + SecondMethod(n - 1, k)); // Recursion (C(n,k) = C(n-1,k-1) + C(n-1,k))
}

unsigned long long int SecondMethodMemoized(unsigned int n, unsigned int k, unsigned long long int **memo) {

    if(k == 0 || k == n) { // Casos base (C(n,0) = C(n,n) = 1)
        memo[n-1][k-1] = 1;
        return memo[n-1][k-1];
    }
    else if(k == 1) { // Caso especial (C(n,1) = n)
        memo[n-1][k-1] = n;
        return memo[n-1][k-1];
    }

    if(memo[n-1][k-1] != 0) { // Si ya se ha calculado la combinatoria, se devuelve el valor...
        return memo[n-1][k-1]; // ...almacenado en la posicion = (n-1,k-1) para C(n,k)
    }
    else { // En caso contrario, se calcula la combinatoria, se guarda en la matriz dinamica memo
        memo[n-1][k-1] = SecondMethodMemoized(n - 1, k - 1, memo) + SecondMethodMemoized(n - 1, k, memo); // Recursion (C(n,k) = C(n-1,k-1) + C(n-1,k))
        return memo[n-1][k-1]; // Una vez termiandas las llamadas recursivas, se devuleve el valor de la ultima combinatoria calculada
    }
}

unsigned long long int ThirdMethod(unsigned int n, unsigned int k) {

    if(k == 0 || k == n) { // Casos base (C(n,0) = C(n,n) = 1)
        return 1;
    }
    else if(k == 1) { // Caso especial (C(n,1) = n)
        return n;
    }

    return ((n * ThirdMethod(n - 1, k - 1)) / k); // Recursion (C(n,k) = (n / k) * C(n-1,k-1))
}

unsigned long long int ThirdMethodMemoized(unsigned int n, unsigned int k, unsigned long long int **memo) {

    if(k == 0 || k == n) { // Casos base (C(n,0) = C(n,n) = 1)
        memo[n-1][k-1] = 1;
        return memo[n-1][k-1];
    }
    else if(k == 1) { // Caso especial (C(n,1) = n)
        memo[n-1][k-1] = n;
        return memo[n-1][k-1];
    }

    if(memo[n-1][k-1] != 0) { // Si ya se ha calculado la combinatoria, se devuelve el valor...
        return memo[n-1][k-1]; // ...almacenado en la posicion = (n-1,k-1) para C(n,k)
    }
    else { // En caso contrario, se calcula la combinatoria, se guarda en la matriz dinamica memo
        memo[n-1][k-1] = (n * ThirdMethodMemoized(n - 1, k - 1, memo)) / k; // Recursion (C(n,k) = (n / k) * C(n-1,k-1))
        return memo[n-1][k-1]; // Una vez termiandas las llamadas recursivas, se devuleve el valor de la ultima combinatoria calculada
    }
}

unsigned long long int FirstMethodSimplified(unsigned int n, unsigned int k) {

    unsigned long long int prod, base;
    unsigned int i;

    base = CheckValues(n, k);

    if (base != 0) { // Si alguno de los casos base ocurre, devolvemos el valor correspondiente
        return base;
    }

    // Propiedad de simetria: C(n,k) = C(n,n-k)
    if (k > n / 2) {
        k = n - k;
    }

    prod = 1; // Neutro multiplicativo para almacenar la combinatoria como multiplicatoria

    for (i = 1; i <= k; i = i + 1) { 
       prod = prod * (n - k + i);
       prod = prod / i;
    }

    return prod; // C(n,k) = PI_{i=1}^{k} ((n - k + i) / i)
}

unsigned long long int SecondMethodSimplified(unsigned int n, unsigned int k) {

    unsigned long long int first_mult, second_mult, base;
    unsigned int i;

    base = CheckValues(n, k);

    if (base != 0) { // Si alguno de los casos base ocurre, devolvemos el valor correspondiente
        return base;
    }

    // Propiedad de simetria: C(n,k) = C(n,n-k)
    if (k > n / 2) {
        k = n - k;
    } 

    first_mult = 1; // Neutro multiplicativo para almacenar el primer sumando de la combinatoria como multiplicatoria

    for (i = 1; i <= k - 1; i = i + 1) { 
        first_mult = first_mult * (n - i);
        first_mult = first_mult / i;
    }

    second_mult = 1; // Neutro multiplicativo para almacenar el segundo sumando de la combinatoria como multiplicatoria

    for (i = 1; i <= k; i = i + 1) {
        second_mult = second_mult * (n - i);
        second_mult = second_mult / i;
    }  

    return (first_mult + second_mult); // C(n,k) = [PI_{1}^{k-1} ((n - i) / i))] + [PI_{1}^{k} ((n - i) / i))]
}


unsigned long long int ThirdMethodSimplified(unsigned int n, unsigned int k) {

    unsigned long long int prod, base;
    unsigned int i;

    base = CheckValues(n, k);

    if (base != 0) { // Si alguno de los casos base ocurre, devolvemos el valor correspondiente
        return base;
    }

    // Propiedad de simetria: C(n,k) = C(n,n-k)
    if (k > n / 2) {
        k = n - k;
    } 

    prod = 1; // Neutro multiplicativo para almacenar el factorial como multiplicatoria

    for (i = 1; i <= k - 1; i = i + 1) {
       prod = prod * (n - i);
       prod = prod / i;
    }

    return ((n * prod) / k); //  C(n,k) = (n / k) * (PI_{i=1}^{k-1} (n - i))
}

void FirstMethodSimplified256(unsigned int n, unsigned int k) {
    
    struct BigNum result;
    unsigned int base, i;

    base = CheckValues(n, k);

    if (base == 1) { // Si alguno de los casos base ocurre, mostramos el valor correspondiente
        printf("\nFirst method multiplicative with 256 base: C(%u,%u) = %u\n", n, k, base);
    }
    else if (base == n) {
        printf("\nFirst method multiplicative with 256 base: C(%u,%u) = %u\n", n, k, base);
    }
    else {
        InitBigNum(&result);

        // Propiedad de simetria: C(n,k) = C(n,n-k)
        if (k > n / 2) {
            k = n - k;
        } 

        for (i = 1; i <= k; i = i + 1) {
            MulBigNum(&result, n - k + i);
            DivBigNum(&result, i);
        }

        // printf("\nFirst method multiplicative with 256 base: C(%u,%u) = ", n, k);
        PrintDecimal(&result);
        // printf("\n");
    }
}


void SecondMethodSimplified256(unsigned int n, unsigned int k) {

    struct BigNum result1, result2;
    unsigned int base, i;

    base = CheckValues(n, k);

    if (base == 1) { // Si alguno de los casos base ocurre, mostramos el valor correspondiente
        printf("\nSecond method multiplicative with 256 base: C(%u,%u) = %u\n", n, k, base);
    }
    else if (base == n) {
        printf("\nSecond method multiplicative with 256 base: C(%u,%u) = %u\n", n, k, base);
    }
    else {
        InitBigNum(&result1);
        InitBigNum(&result2);

        // Propiedad de simetria: C(n,k) = C(n,n-k)
        if (k > n / 2) {
            k = n - k;
        } 

        for (i = 1; i <= k - 1; i = i + 1) { 
            MulBigNum(&result1, n - i);
            DivBigNum(&result1, i);
        }

        for (i = 1; i <= k; i = i + 1) {
            MulBigNum(&result2, n - i);
            DivBigNum(&result2, i);
        } 

        AddTwoBigNums(&result1, &result2);

        // printf("\nSecond method multiplicative with 256 base: C(%u,%u) = ", n, k);
        PrintDecimal(&result1);
        // printf("\n");
    }
}

void ThirdMethodSimplified256(unsigned int n, unsigned int k) {

    struct BigNum result;
    unsigned int base, i;

    base = CheckValues(n, k);

    if (base == 1) { // Si alguno de los casos base ocurre, mostramos el valor correspondiente
        printf("\nThird method multiplicative with 256 base: C(%u,%u) = %u\n", n, k, base);
    }
    else if (base == n) {
        printf("\nThird method multiplicative with 256 base: C(%u,%u) = %u\n", n, k, base);
    }
    else {
        InitBigNum(&result);

        // Propiedad de simetria: C(n,k) = C(n,n-k)
        if (k > n / 2) {
            k = n - k;
        }

        for (i = 1; i <= k - 1; i = i + 1) {
            MulBigNum(&result, n - i);
            DivBigNum(&result, i);
        }

        MulBigNum(&result, n);
        DivBigNum(&result, k);

        // printf("\nThird method multiplicative with 256 base: C(%u,%u) = ", n, k);
        PrintDecimal(&result);
        // printf("\n");
    }
}