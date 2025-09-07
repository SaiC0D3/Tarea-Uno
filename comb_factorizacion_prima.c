#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DIGITS 20000   // tamaño máximo del resultado en dígitos decimales

// Representación de enteros grandes en base 10
typedef struct {
    int digits[MAX_DIGITS];
    int size; // número de dígitos usados
} BigInt;

// Inicializa BigInt = 1
void bigint_init(BigInt *a) {
    memset(a->digits, 0, sizeof(a->digits));
    a->digits[0] = 1;
    a->size = 1;
}

// Multiplica BigInt * x (entero pequeño)
void bigint_mul_small(BigInt *a, int x) {
    int carry = 0;
    for (int i = 0; i < a->size; i++) {
        long long prod = 1LL * a->digits[i] * x + carry;
        a->digits[i] = prod % 10;
        carry = prod / 10;
    }
    while (carry > 0) {
        a->digits[a->size++] = carry % 10;
        carry /= 10;
    }
}

// Eleva primo^exp y lo multiplica al BigInt
void bigint_pow_mul(BigInt *a, int prime, unsigned long long exp) {
    for (unsigned long long i = 0; i < exp; i++) {
        bigint_mul_small(a, prime);
    }
}

// Imprime BigInt
void bigint_print(const BigInt *a) {
    for (int i = a->size - 1; i >= 0; i--) {
        printf("%d", a->digits[i]);
    }
    printf("\n");
}

// Exponente del primo p en n!
unsigned long long exp_prime_factorial(unsigned long long n, unsigned long long p) {
    unsigned long long exp = 0;
    while (n) {
        n /= p;
        exp += n;
    }
    return exp;
}

// Criba de Eratóstenes
void sieve(int n, int **primes, int *count) {
    char *is_prime = calloc(n+1, 1);
    for (int i = 2; i <= n; i++) is_prime[i] = 1;

    for (int i = 2; i*i <= n; i++) {
        if (is_prime[i]) {
            for (int j = i*i; j <= n; j += i) is_prime[j] = 0;
        }
    }

    *count = 0;
    for (int i = 2; i <= n; i++) if (is_prime[i]) (*count)++;

    *primes = malloc((*count) * sizeof(int));
    int idx = 0;
    for (int i = 2; i <= n; i++) if (is_prime[i]) (*primes)[idx++] = i;

    free(is_prime);
}

void binomial_prime_factorization(unsigned long long n, unsigned long long k, BigInt *result) {
    int *primes, count;
    sieve(n, &primes, &count);

    bigint_init(result);

    for (int i = 0; i < count; i++) {
        int p = primes[i];
        unsigned long long e = exp_prime_factorial(n, p)
                             - exp_prime_factorial(k, p)
                             - exp_prime_factorial(n-k, p);
        if (e > 0) {
            bigint_pow_mul(result, p, e);
        }
    }

    free(primes);
}

int main(int argc, char const **argv) {
    BigInt result;
    unsigned long long n, k;  // puedes probar con valores grandes

    n = strtoul(argv[1], NULL, 10); // Para convertir los argumentos de entrada a unsigned long long int
    k = strtoul(argv[2], NULL, 10);

    binomial_prime_factorization(n, k, &result);

    bigint_print(&result);

    return 0;
}
