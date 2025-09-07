#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

// Función para calcular nCk = n! / (k!(n-k)!)
void combinatoria(mpz_t result, unsigned int n, unsigned int k) {
    mpz_t fact_n, fact_k, fact_nk, denom;

    mpz_inits(fact_n, fact_k, fact_nk, denom, NULL);

    // fact_n = n!
    mpz_fac_ui(fact_n, n);

    // fact_k = k!
    mpz_fac_ui(fact_k, k);

    // fact_nk = (n-k)!
    mpz_fac_ui(fact_nk, n - k);

    // denom = k! * (n-k)!
    mpz_mul(denom, fact_k, fact_nk);

    // result = n! / denom
    mpz_divexact(result, fact_n, denom);

    // Liberar memoria
    mpz_clears(fact_n, fact_k, fact_nk, denom, NULL);
}

int main(int argc, char const **argv) {
    mpz_t res;
    unsigned int n, k; // Ejemplo con números grandes

    n = strtoul(argv[1], NULL, 10); // Para convertir los argumentos de entrada a unsigned long long int
    k = strtoul(argv[2], NULL, 10);

    mpz_init(res);

    combinatoria(res, n, k);

    gmp_printf("\nC(%u, %u) = %Zd\n", n, k, res);

    mpz_clear(res);
    return 0;
}
