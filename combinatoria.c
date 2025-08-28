/*
*   Programa:        combinatoria.c
*   Descripcion:     Determinar los valores maximos para n y k al calcular C(n,k) con
*                    tres metodos distintos y realizar eventuales optimizaciones
*   Autores:         Matías Olivares, Delian Santis
*   Fecha:           25-08-2025  
*   Ultima revision: 27-08-2025 21:00
*   Compilador:      gcc.exe (MinGW.org GCC-6.3.0-1) 6.3.0 en VSCode
*
*/

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define FIRST_REC 1
#define FIRST     2
#define SECOND    3
#define SECOND_OP 4
#define THIRD     5
#define THIRD_OP  6

/*
*
*
*/

// Funcion para indicar el modo de ejecucion del programa
void Usage(char const *);

// Funcion para verificar las condiciones necesarias de entrada para los metodos
unsigned long int CheckValues(unsigned long int n, unsigned long int k);

// Funcion para calcular de manera recursiva el factorial de num (num!)
unsigned long int FactorialRec(unsigned long int num);

// Funcion para calcular de manera iterativa el factorial de num (num!)
unsigned long int Factorial(unsigned long int num);

// Primer metodo combinatorial: C(n,k) = n! / (n - k)! * k! mas modo de calculo de factorial
unsigned long int FirstMethod(unsigned long int n, unsigned long int k, unsigned char op);

// Segundo metodo combinatorial: C(n,k) = C(n-1,k-1) + C(n-1,k)
unsigned long int SecondMethod(unsigned long int n, unsigned long int k);

/*
    ( n-1! / k-1! * ((n - 1) -(k - 1))! ) + ( n-1! / (k! * (n - 1 - k)! ) SIN SIMPLIFICAR
    
    ( n-1! / k-1! * (n - k)! ) + ( n-1! / (k! * (n - 1 - k)! ) CON SIMPLIFICAR


    MULTIPLICIDAD Y FACTORIAL RESUELTO (está en el for)

    la primera parte se queda simplificada como:
        Multiplicidad de i = 1 hasta k + 1 de (n - i) / (k - 1)!
*/

// Segundo metodo combinatorial optimizado con simplificacion
unsigned long int SecondMethodOptimized(unsigned long int n, unsigned long int k);

// Tercer metodo combinatorial: multiplicatoria_{i=1}^{k} (n - i + 1 / i) mas optimizacion con simetria
unsigned long int ThirdMethod(unsigned long int n, unsigned long int k, unsigned char op);

/*
*
*
*/

int main(int argc, char const **argv) {
    
    unsigned long int n, k, result;
    unsigned char method;

    if (argc == 4) {
        
        n = strtoul(argv[2], NULL, 10); // Para convertir los argumentos de entrada a unsigned long int
        k = strtoul(argv[3], NULL, 10);

        if (n < 0 || k < 1 || k > n) {
            printf("\nEnter a valid value for n and k (n >= 0, k >= 0, k <= n)\n");
            exit(EXIT_FAILURE);
        }
        
        if (strcmp(argv[1], "-1") == 0) {
            method = FIRST;

            printf("\nFirst method: C(%lu,%lu) = ", n, k);
            result = FirstMethod(n, k, method);
            printf("%lu\n", result);
        } 
        else if (strcmp(argv[1], "-2") == 0) {
            method = FIRST_REC;

            printf("\nFirst method using recursion: C(%lu,%lu) = ", n, k);
            result = FirstMethod(n, k, method);
            printf("%lu\n", result);
        } 
        else if (strcmp(argv[1], "-3") == 0) {
            method = SECOND;

            if (k < 1) {
                printf("\nEnter a valid value for k (1 <= k < n)\n");
                exit(EXIT_FAILURE);
            }
            
            printf("\nSecond method: C(%lu,%lu) = ", n, k);
            result = SecondMethod(n, k);
            printf("%lu\n", result);
        }
        else if (strcmp(argv[1], "-4") == 0) {
            method = SECOND_OP;

            printf("\nSecond method optimized: C(%lu,%lu) = ", n, k);
            result = SecondMethodOptimized(n, k);
            printf("%lu\n", result);
        }
        else if (strcmp(argv[1], "-5") == 0) {
            method = THIRD;

            printf("\nThird method: C(%lu,%lu) = ", n, k);
            result = ThirdMethod(n, k, method);
            printf("%lu\n", result);
        }
        else if (strcmp(argv[1], "-6") == 0) {
            method = THIRD_OP;

            printf("\nThird method optimized: C(%lu,%lu) = ", n, k);
            result = ThirdMethod(n, k, method);
            printf("%lu\n", result);
        }
        else {
            printf("\nEnter a valid modes (1 <= o <= 10)\n");
            exit(EXIT_FAILURE);
        } 
    }
    else {
        Usage(argv[0]);
    }
    
    return 0;
    printf("\n\n");
}

/*
*
*
*/

void Usage(char const *msg) {
    printf("\nUsage: %s -o n k", msg);
    printf("\n\no in {1,2,3,4,5,6,7,8,9,10}\n\n");
    printf("1: FIRST_REC\n");
    printf("2: FIRST\n");
    printf("3: SECOND\n");
    printf("4: SECOND_OP\n");
    printf("5: THIRD\n");
    printf("6: THIRD_OP\n");
    printf("7: \n");
    printf("8: \n");
    printf("9: \n");
    printf("10: \n");
}

unsigned long int CheckValues(unsigned long int n, unsigned long int k) {

    if(k == 0 || k == n) { // Casos base (C(n,0) = C(n,n) = 1)
        return 1;
    }
    else if(k == 1) { // Caso especial (C(n,1) = n)
        return n;
    }
}

unsigned long int FactorialRec(unsigned long int num) {

    if(num == 0 || num == 1) { // Caso base (1! = 0! = 1)
        return 1;
    }
        
    return num * FactorialRec(num - 1); // Recursion (n! = n * (n - 1)!)
}

unsigned long int Factorial(unsigned long int num) {

    unsigned int i;
    unsigned long int prod = 1;

    if (num == 0 || num == 1) { // Convencion (0! = 1! = 1)
        return 1;
    }
        
    for (i = 1; i <= num; i = i + 1) { // Iteracion sobre el producto de numeros desde 1 hasta num
        prod = prod * i;
    }

    return prod;
}

unsigned long int FirstMethod(unsigned long int n, unsigned long int k, unsigned char op) {

    if (op = FIRST) { // Primer metodo con factorial iterativo
        return (Factorial(n)) / (Factorial(n - k) * (Factorial(k)));
    }
    else if (op == FIRST_REC) { // Segundo emtodo con factorial recursivo
        return (FactorialRec(n)) / (FactorialRec(n - k) * (FactorialRec(k)));
    }
}

unsigned long int SecondMethod(unsigned long int n, unsigned long int k) {

    unsigned int i;

    // No se usa la funcion CheckValues por las llamadas recursivas, para evitar desbordamiento de la pila
    if(k == 0 || k == n) { // Casos base (C(n,0) = C(n,n) = 1)
        return 1;
    }
    else if(k == 1) { // Caso especial (C(n,1) = n)
        return n;
    }

    return (SecondMethod(n - 1, k - 1) + SecondMethod(n - 1, k)); // Recursion (C(n,k) = C(n-1,k-1) + C(n-1,k))
}

unsigned long int SecondMethodOptimized(unsigned long int n, unsigned long int k) {

    unsigned int i;
    unsigned long int multiplicity = 1, result;

    CheckValues(n, k); // Ver casos base

    // Resuelve la multiplicidad (simplificacion)
    for (i = 1; i <= k - 1; i = i + 1) {
        multiplicity = multiplicity * (n - i);
    }
        
    result = multiplicity / Factorial(k - 1);

    return (result + Factorial(n - 1) / (Factorial(k) * Factorial(n - 1 - k)));
}

unsigned long int ThirdMethod(unsigned long int n, unsigned long int k, unsigned char op) {

    unsigned int i;
    unsigned long int result = 1;

    CheckValues(n, k); // Ver casos base

    // Propiedad de simetría: C(n,k) = C(n,n-k)
    if (op == THIRD_OP) {
        if (k > n - k) {
            k = n - k;
        }
    }      

    for (i = 1; i <= k; i = i + 1) {
        result = result * ((n - i + 1) / i);
    }

    return result;
}
