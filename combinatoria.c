/*
*   Programa:        calculo_combinatoria.c
*   Descripcion: 
*   Autores:         Delian Santis, Matías Olivares
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

void Usage(char const *);

// Funcion de factorial recursiva para el valor num
unsigned long int FactorialRec(unsigned long int num);

// Funcion de factorial iterativa para el valor num
unsigned long int Factorial(unsigned long int num);

// Primer metodo: C(n,k) = n! / (n-k)! * k!
unsigned long int FirstMethod(unsigned long int n, unsigned long int k, unsigned char op);

// Segundo metodo: C(n,k) = C(n-1,k-1) + C(n-1,k)
/*
    ( n-1! / k-1! * ((n - 1) -(k - 1))! ) + ( n-1! / (k! * (n - 1 - k)! ) SIN SIMPLIFICAR
    
    ( n-1! / k-1! * (n - k)! ) + ( n-1! / (k! * (n - 1 - k)! ) CON SIMPLIFICAR


    MULTIPLICIDAD Y FACTORIAL RESUELTO (está en el for)

    la primera parte se queda simplificada como:
        Multiplicidad de i = 1 hasta k + 1 de (n - i) / (k - 1)!
*/

unsigned long int SecondMethod(unsigned long int n, unsigned long int k);

unsigned long int SecondMethodOptimized(unsigned long int n, unsigned long int k);

// Tercer metodo: multiplicatoria_{i=1}^{k} (n-i+1/i)
unsigned long int ThirdMethod(unsigned long int n, unsigned long int k, unsigned char op);

/*
*
*
*/

int main(int argc, char const **argv) { // 'argc' contiene la cantidad de parámetros de entrada, 'argv' contiene cada parámetro ingresado (cadena de cadenas, doble vector)
    
    unsigned long int n, k, result;
    unsigned char method;

    if (argc == 4) { // Cantidad de parámetros para ejecutar el programa (1 parámetro además del nombre del ejecutable = 2 indices de arreglo)
        
        n = strtoul(argv[2], NULL, 10);
        k = strtoul(argv[3], NULL, 10);

        if (n < 0 || k < 1 || k > n) {
            printf("\nLos valores de k y n deben ser enteros positivos y además 1 <= k < n \n");
            exit(EXIT_FAILURE);
        }
        
        if (strcmp(argv[1], "-1") == 0) {
            method = FIRST;
            printf("\nFirst method: C(%lu,%lu) = ", n, k);
            result = FirstMethod(n, k, method);
            printf("%lu", result);
        } 
        else if (strcmp(argv[1], "-2") == 0) {
            method = FIRST_REC;
            printf("\nFirst method using recursion: C(%lu,%lu) = ", n, k);
            result = FirstMethod(n, k, method);
            printf("%lu", result);
        } 
        else if (strcmp(argv[1], "-3") == 0) {
            method = SECOND;
            printf("\nSecond method: C(%lu,%lu) = ", n, k);
            result = SecondMethod(n, k);
            printf("%lu", result);
        }
        else if (strcmp(argv[1], "-4") == 0) {
            method = SECOND_OP;
            printf("\nSecond method optimized: C(%lu,%lu) = ", n, k);
            result = SecondMethodOptimized(n, k);
            printf("%lu", result);
        }
        else if (strcmp(argv[1], "-5") == 0) {
            method = THIRD;
            printf("\nThird method: C(%lu,%lu) = ", n, k);
            result = ThirdMethod(n, k, method);
            printf("%lu", result);
        }
        else if (strcmp(argv[1], "-6") == 0) {
            method = THIRD_OP;
            printf("\nThird method optimized: C(%lu,%lu) = ", n, k);
            result = ThirdMethod(n, k, method);
            printf("%lu", result);
        }
        
        else {
            printf("\nEnter a valid mode! (1 <= o <= 10)\n");
            exit(EXIT_FAILURE);
        } 
    }
    else {
        Usage(argv[0]);
    }
    
    printf("\n\n");
    return 0;
}

/*
*
*
*/

void Usage(char const *msg) {
    printf("\nUsage: %s -o n k", msg);
    printf("\n\no in {0,1,2,3}\n\n");
}

unsigned long int FactorialRec(unsigned long int num) {

    if(num == 0 || num == 1){
        return 1;
    }
        
    return num * FactorialRec(num - 1);
}

unsigned long int Factorial(unsigned long int num) {

    unsigned int i;
    unsigned long int prod = 1;

    if (num == 0) {
        return 1;
    }
        
    for (i = 1; i <= num; i = i + 1) {
        prod = prod * i;
    }

    return prod;
}

unsigned long int FirstMethod(unsigned long int n, unsigned long int k, unsigned char op) {

    if (op = FIRST) {
        return (Factorial(n)) / (Factorial(n - k) * (Factorial(k)));
    }
    else if (op == FIRST_REC) {
        return (FactorialRec(n)) / (FactorialRec(n - k) * (FactorialRec(k)));
    }
}

unsigned long int SecondMethod(unsigned long int n, unsigned long int k) {

    unsigned int i;
    unsigned long int result;

    if(k == 0 || k == n) {
        return 1;
    }

    return (SecondMethod(n - 1, k - 1) + SecondMethod(n - 1, k));
}

unsigned long int SecondMethodOptimized(unsigned long int n, unsigned long int k) {

    unsigned int i;
    unsigned long int multiplicity = 1, result;

    // Resuelve la multiplicidad (simplificacion)
    for (i = 1; i <= k - 1; i = i + 1) {
        multiplicity = (n - i) * multiplicity;
    }
        
    result = multiplicity / Factorial(k - 1);

    return (result + Factorial(n - 1) / (Factorial(k) * Factorial(n - 1 - k)));
}

unsigned long int ThirdMethod(unsigned long int n, unsigned long int k, unsigned char op) {

    unsigned int i;
    unsigned long int result = 1;

    if (k > n) {
        return 0;
    }
    else if(k == 0 || k == n) {
        return 1;
    }

    // Usamos simetría C(n,k) = C(n,n-k)
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
