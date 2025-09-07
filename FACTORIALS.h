#include <stdio.h> 
#include <stdlib.h>

// Funcion para calcular de manera recursiva el factorial de num (num!)
unsigned long long int FactorialRec(unsigned int num) {

    if(num == 0 || num == 1) { // Caso base (0! = 1! = 1)
        return 1;
    }
        
    return num * FactorialRec(num - 1); // Recursion (n! = n * (n - 1)!)
}

// Funcion para calcular de manera recursiva el factorial de num, con memoizacion (programacion dinamica)
unsigned long long int FactorialRecMemo(unsigned int num, unsigned long long int *memo) {

    if(num == 0 || num == 1) { // Casos base (0! = 1! = 1)
        memo[0] = 1; // Ambos almacenados en la primera posicion del arreglo dinamico
        return memo[0];
    }

    if (memo[num - 1] != 0) { // Si el valor del factorial ya fue calculado, se devuelve el valor...
        return memo[num - 1]; // ...almacenado en la posicion = num - 1, para num!
    }
    else { // En caso contrario, se calcula el factorial, se guarda en el arreglo dinamico memo
        memo[num - 1] = num * FactorialRecMemo(num - 1, memo); // Recursion (n! = n * (n - 1)!)
        return memo[num - 1]; // Una vez termiandas las llamadas recursivas, se devuleve el valor del utlimo facotrial calculado
    }
}

// Funcion para calcular de manera iterativa el factorial de num (num!)
unsigned long long int Factorial(unsigned int num) {

    unsigned long long int prod;
    unsigned int i;

    if (num == 0 || num == 1) { // Caso base (0! = 1! = 1)
        return 1;
    }
        
    prod = 1; // Neutro multiplicativo para almacenar el factorial como producto iterativo

    for (i = 2; i <= num; i = i + 1) { // Iteracion sobre el producto de numeros desde 2 hasta num
        prod = prod * i;
    }

    return prod;
}

// Funcion para calcular de manera iterativa el factorial de num, con memoizacion (programacion dinamica)
unsigned long long int FactorialMemo(unsigned int num, unsigned long long int *memo) {

    unsigned int i;

    memo[0] = 1; // Primer elemento del arreglo dinamico y casos base 0! = 1! = 1

    for (i = 2; i <= num; i = i + 1) { // Iteracion sobre los elementos del arreglo dinamico, multiplicando con 2 hasta num y...
        memo[i - 1] = memo[i - 2] * i; // ...almacenando el resultado en la posicion correspondiente (i - 1 para i!)
    }

    return memo[num - 1]; // Devolvemos la utima posicion del arreglo con el valor de num!
}