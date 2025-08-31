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

// Metodos de ejecucion para el calculo de C(n,k) y n!
#define FIRST_REC        0
#define FIRST_REC_MEMO   1
#define FIRST_ITE        2
#define FIRST_ITE_MEMO   3
#define SECOND           4
#define SECOND_MULT_MEMO 5
#define THIRD            6
#define THIRD_SIM        7
#define FIRST_MULT_MEMO  8

/*
 *
 */


// Funcion para indicar el modo de ejecucion del programa
void Usage(char const *);

// Funcion para verificar las condiciones necesarias de entrada para los metodos
unsigned long long int CheckValues(unsigned long long int n, unsigned long long int k);

// Funcion para calcular de manera recursiva el factorial de num (num!)
unsigned long long int FactorialRec(unsigned long long int num);

// Funcion para calcular de manera recursiva el factorial de num, con memoizacion (programacion dinamica)
unsigned long long int FactorialRecMemo(unsigned long long int num, unsigned long long int *memo);

// Funcion para calcular de manera iterativa el factorial de num (num!)
unsigned long long int Factorial(unsigned long long int num);

// Funcion para calcular de manera iterativa el factorial de num, con memoizacion (programacion dinamica)
unsigned long long int FactorialMemo(unsigned long long int num, unsigned long long int *memo);

// Primer metodo combinatorial: C(n,k) = n! / (n - k)! * k! con calculo de factorial recursivo y memoizacion
unsigned int FirstMethodRec(unsigned long long int n, unsigned long long int k, unsigned long long int *memo, unsigned char op);

// Primer metodo combinatorial: C(n,k) = n! / (n - k)! * k! con calculo de factorial recursivo y memoizacion
unsigned int FirstMethodIte(unsigned long long int n, unsigned long long int k, unsigned long long int *memo, unsigned char op);

// Segundo metodo combinatorial: C(n,k) = C(n-1,k-1) + C(n-1,k)
unsigned long long int SecondMethod(unsigned long long int n, unsigned long long int k);

// Segundo metodo combinatorial optimizado con simplificacion
unsigned int SecondMethodOptimized(unsigned long long int n, unsigned long long int k, unsigned long long int *memo);

// Tercer metodo combinatorial: PI_{i=1}^{k} (n - i + 1 / i) mas optimizacion con simetria
unsigned int ThirdMethod(unsigned long long int n, unsigned long long int k, unsigned char op);

// Primermetodo combinatorial simplificado: C(n,k) = (1/k!) * (PI_{i=0}^{k-1} (n - i)) con memoizacion
unsigned int FirstMethodOptimized(unsigned long long int n, unsigned long long int k, unsigned long long int *memo);

/*
 *
 */

// 20! = 2.432.902.008.176.640.000  |  ull -> 0 a 18,446,744,073,709,551,615
int main(int argc, char const **argv) {
    
    unsigned long long int n, k, *cache;
    unsigned int result = 0;
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

            printf("\n%llu - CPU time %f\n", n, E_cpu);

            printf("\nFirst method - recursive factorial: C(%llu,%llu) = %u\n", n, k, result);
        } 
        else if (strcmp(argv[1], "-1") == 0) {
            method = FIRST_REC_MEMO;
            cache = (unsigned long long int *)calloc(n, sizeof(unsigned long long int));
            
            csc = clock(); // cpu start
            result = FirstMethodRec(n, k, cache, method);
            cec = clock(); // cpu exit

            E_cpu = (float)(cec - csc) / CLOCKS_PER_SEC;

            printf("\n%llu - CPU time %f\n", n, E_cpu);

            printf("\nFirst method - recursive factorial with memoization: C(%llu,%llu) = %u\n", n, k, result);
        } 
        else if (strcmp(argv[1], "-2") == 0) {
            method = FIRST_ITE;
            cache = (unsigned long long int *)calloc(n, sizeof(unsigned long long int));

            csc = clock(); // cpu start
            result = FirstMethodIte(n, k, cache, method);
            cec = clock(); // cpu exit

            E_cpu = (float)(cec - csc) / CLOCKS_PER_SEC;

            printf("\n%llu - CPU time %f\n", n, E_cpu);

            printf("\nFirst method - iterative factorial: C(%llu,%llu) = %u\n", n, k, result);
        } 
        else if (strcmp(argv[1], "-3") == 0) {
            method = FIRST_ITE_MEMO;
            cache = (unsigned long long int *)calloc(n, sizeof(unsigned long long int));

            csc = clock(); // cpu start
            result = FirstMethodIte(n, k, cache, method);
            cec = clock(); // cpu exit

            E_cpu = (float)(cec - csc) / CLOCKS_PER_SEC;

            printf("\n%llu - CPU time %f\n", n, E_cpu);

            printf("\nFirst method - iterative factorial with memoization: C(%llu,%llu) = %u\n", n, k, result);
        }
        else if (strcmp(argv[1], "-4") == 0) {
            method = SECOND;

            if (k < 1) {
                printf("\nEnter a valid value for k (1 <= k < n)\n");
                exit(EXIT_FAILURE);
            }
            
            csc = clock(); // cpu start
            result = SecondMethod(n, k);
            cec = clock(); // cpu exit

            E_cpu = (float)(cec - csc) / CLOCKS_PER_SEC;

            printf("\n%llu - CPU time %f\n", n, E_cpu);

            printf("\nSecond method recursive: C(%llu,%llu) = %u\n", n, k, result);
        }
        else if (strcmp(argv[1], "-5") == 0) {
            method = SECOND_MULT_MEMO;
            cache = (unsigned long long int *)calloc(n, sizeof(unsigned long long int));

            if (k < 1) {
                printf("\nEnter a valid value for k (1 <= k < n)\n");
                exit(EXIT_FAILURE);
            }
            
            csc = clock(); // cpu start
            result = SecondMethodOptimized(n, k, cache);
            cec = clock(); // cpu exit

            E_cpu = (float)(cec - csc) / CLOCKS_PER_SEC;

            printf("\n%llu - CPU time %f\n", n, E_cpu);

            printf("\nSecond method multiplicative with memoization: C(%llu,%llu) = %u\n", n, k, result);
        }
        else if (strcmp(argv[1], "-6") == 0) {
            method = THIRD;

            csc = clock(); // cpu start
            result = ThirdMethod(n, k, method);
            cec = clock(); // cpu exit

            E_cpu = (float)(cec - csc) / CLOCKS_PER_SEC;

            printf("\n%llu - CPU time %f\n", n, E_cpu);

            printf("\nThird method multiplicative: C(%llu,%llu) = %u\n", n, k, result);
        }
        else if (strcmp(argv[1], "-7") == 0) {
            method = THIRD_SIM;

            csc = clock(); // cpu start
            result = ThirdMethod(n, k, method);
            cec = clock(); // cpu exit

            E_cpu = (float)(cec - csc) / CLOCKS_PER_SEC;

            printf("\n%llu - CPU time %f\n", n, E_cpu);

            printf("\nThird method multiplicative with simetry: C(%llu,%llu) = %u\n", n, k, result);
        }
        else if (strcmp(argv[1], "-8") == 0) {
            method = FIRST_MULT_MEMO;
            cache = (unsigned long long int *)calloc(n, sizeof(unsigned long long int));

            csc = clock(); // cpu start
            result = FirstMethodOptimized(n, k, cache);
            cec = clock(); // cpu exit

            E_cpu = (float)(cec - csc) / CLOCKS_PER_SEC;

            printf("\n%llu - CPU time %f\n", n, E_cpu);

            printf("\nFirst method multiplicative with memoization: C(%llu,%llu) = %u\n", n, k, result);
        } 
        else {
            printf("\nEnter a valid modes (0 <= o <= 8)\n");
            exit(EXIT_FAILURE);
        } 
    }
    else {
        Usage(argv[0]);
    }

    free(cache);
    cache = NULL;
    
    printf("\n\n");
    return 0;
}

/*
 *
 */

void Usage(char const *msg) {
    printf("\nUsage: %s -o n k", msg);
    printf("\n\no in {0,1,2,3,4,5,6,7,8}\n\n");
    printf("0: FIRST_RMEM\n");
    printf("1: FIRST_REC_MEMO\n");
    printf("2: FIRST_ITE\n");
    printf("3: FIRST_ITE_MEMO\n");
    printf("4: SECOND\n");
    printf("5: SECOND_MULT_MEMO\n");
    printf("6: THIRD\n");
    printf("7: THIRD_SIM\n");
    printf("8: FIRST_MULT_MEMO\n");
}

unsigned long long int CheckValues(unsigned long long int n, unsigned long long int k) {

    if(k == 0 || k == n) { // Casos base (C(n,0) = C(n,n) = 1)
        return 1;
    }
    else if(k == 1) { // Caso especial (C(n,1) = n)
        return n;
    }
}

unsigned long long int FactorialRec(unsigned long long int num) {

    if(num == 0 || num == 1) { // Caso base (1! = 0! = 1)
        return 1;
    }
        
    return num * FactorialRec(num - 1); // Recursion (n! = n * (n - 1)!)
}

unsigned long long int FactorialRecMemo(unsigned long long int num, unsigned long long int *memo) {

    unsigned long long int factorial;

    if(num == 0 || num == 1) { // Caso base (1! = 0! = 1)
        memo[0] = 1;
        return memo[0];
    }

    if (memo[num - 1] != 0) { // Si el valor del factorial ya fue calculado, se devuelve
        return memo[num - 1];
    }
    else { // Se calcula el factorial, se guarda en el arreglo memo y se devuelve el valor
        factorial = num * FactorialRecMemo(num - 1, memo); // Recursion (n! = n * (n - 1)!)
        memo[num - 1] = factorial;
        return memo[num - 1];
    }
}

unsigned long long int Factorial(unsigned long long int num) {

    unsigned long long int i, prod = 1;

    if (num == 0 || num == 1) { // Convencion (0! = 1! = 1)
        return 1;
    }
        
    for (i = 2; i <= num; i = i + 1) { // Iteracion sobre el producto de numeros desde 2 hasta num
        prod = prod * i;
    }

    return prod;
}

unsigned long long int FactorialMemo(unsigned long long int num, unsigned long long int *memo) {

    unsigned long long int i, result;

    memo[0] = 1;
        
    for (i = 2; i <= num; i = i + 1) {
        memo[i - 1] = memo[i - 2] * i;
        result = memo[i - 1];
    }

    return result;
}

unsigned int FirstMethodRec(unsigned long long int n, unsigned long long int k, unsigned long long int *memo, unsigned char op) {

    if (op == FIRST_REC) {
        return ((FactorialRec(n)) / (FactorialRec(n - k) * (FactorialRec(k))));
    }
    else if (op == FIRST_REC_MEMO) {
        return ((FactorialRecMemo(n, memo)) / (FactorialRecMemo(n - k, memo) * (FactorialRecMemo(k, memo))));
    }
}

unsigned int FirstMethodIte(unsigned long long int n, unsigned long long int k, unsigned long long int *memo, unsigned char op) {

    //unsigned int result;

    if (op = FIRST_ITE) { // Primer metodo con factorial iterativo
        return ((Factorial(n)) / (Factorial(n - k) * (Factorial(k))));
    }
    else if (op == FIRST_ITE_MEMO) { // Segundo metodo con factorial recursivo
        return ((FactorialMemo(n, memo)) / (FactorialMemo(n - k, memo) * (FactorialMemo(k, memo))));
    } 

    //return result;
}

unsigned long long int SecondMethod(unsigned long long int n, unsigned long long int k) {

    // No se usa la funcion CheckValues por las llamadas recursivas, para evitar desbordamiento de la pila
    if(k == 0 || k == n) { // Casos base (C(n,0) = C(n,n) = 1)
        return 1;
    }
    else if(k == 1) { // Caso especial (C(n,1) = n)
        return n;
    }

    return (SecondMethod(n - 1, k - 1) + SecondMethod(n - 1, k)); // Recursion (C(n,k) = C(n-1,k-1) + C(n-1,k))
}

unsigned int SecondMethodOptimized(unsigned long long int n, unsigned long long int k, unsigned long long int *memo) {

    unsigned long long int i, first_mult = 1, second_mult = 1;
    unsigned int result1, result2;

    CheckValues(n, k); // Ver casos base

    // Resuelve la multiplicidad (simplificacion) del primer sumando
    for (i = 1; i <= k - 1; i = i + 1) {
        first_mult = first_mult * (n - i);
    }
    result1 = first_mult / FactorialMemo(k - 1, memo);

    // Resuelve la multiplicidad (simplificacion) del segundo sumando
    for (i = 1; i <= k; i = i + 1) {
        second_mult = second_mult * (n - i);
    }  
    result2 = second_mult / FactorialMemo(k, memo); // C(n,k) = [(1/(k-1)!) * (PI_{1}^{k-1} (n - i))] + [(1/k!) * (PI_{1}^{k} (n - i))]

    return (result1 + result2);
}

unsigned int ThirdMethod(unsigned long long int n, unsigned long long int k, unsigned char op) {

    unsigned long long int i, prod = 1;
    unsigned int result;

    CheckValues(n, k); // Ver casos base

    // Propiedad de simetria: C(n,k) = C(n,n-k)
    if (op == THIRD_SIM) {
        if (k > n / 2) {
            k = n - k;
        }
    }      

    for (i = 1; i <= k; i = i + 1) {
        prod = (prod * (n + 1 - i)) / i;
    }
     
    return prod;
}

unsigned int FirstMethodOptimized(unsigned long long int n, unsigned long long int k, unsigned long long int *memo) {

    unsigned long long int i, prod = 1;
    unsigned int result;

    CheckValues(n, k); // Ver casos base 

    for (i = 0; i <= k - 1; i = i + 1) {
       prod = prod * (n - i);
    }
    result = prod / FactorialMemo(k, memo);
    
    return result;
}
