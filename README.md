# Calculo de Cobinatoria C(n,k)

Este programa calcula con 3 metodos distintos la combinatoria de n sobre k. Se implementan versiones optimizadas
con programacion dinamica (memoizacion), eliminacion de recursividad (version iterativa) y representacion en base 256.

Version de compilador: Ubuntu 13.3.0-6ubuntu2 24.04 13.3.0 (WSL)
IDE: Visual Studio Code
RAM: 5,62 Gb
Porcesador: 64 bits

Ejecucion: ./salida-final.exe -o n k

o en {0,1,2,3,4,5,6,7,8,9,10,11,12,13}

0: First Method - Recursive Factorial
1: First Method - Recursive Factorial with Memoization
2: First Method - Iterative Factorial
3: First Method - Iterative Factorial with Memoization
4: Second Method Recursive
5: Second Method Recursive with Memoization
6: Third Method Recursive
7: Third Method Recursive with Memoization
8: First Method Multiplicative
9: Second Method Multiplicative
10: Third Method Multiplicative
11: First Method Multiplicative - 256 Base
12: Second Method Multiplicative - 256 Base
13: Third Method Multiplicative - 256 Base

Salida: resultado de C(n,k) y tiempo de CPU

Datos de prueba: Maximo resultado de C(n,k) (el maximo teorico de n y k se especifica en el informe)
-0 20 10
-1 20 10
-2 20 10
-3 20 10
-4 40 20 
-5 67 33 
-6 62 31
-7 62 31
-8 62 31
-9 63 31
-10 62 31
-11 1000000 500000
-12 700000 350000
-13 1000000 500000

OBS: Sobre los valores maximos teoricos el resultado es erroneo o se produce overflow