#include <stdio.h>
#include <stdlib.h>

#define N (10 * 1000 * 1000)

int primes[N] = {2};
size_t primes_count = 1;

int is_prime(int x)
{
    for (size_t i = 0; primes[i] * primes[i] <= x; ++i) {
        if (x % primes[i] == 0) {
            return 0;
        }
    }

    return 1;
}

int main(int argc, char *argv[])
{
    for (int x = 3; primes_count < N; ++x) {
        if (is_prime(x)) {
            primes[primes_count++] = x;
        }
    }

    printf("%d\n", primes[primes_count - 1]);

    return 0;
}
