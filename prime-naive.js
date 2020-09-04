const N = 10 * 1000 * 1000;
const primes = [2];

function is_prime(x) {
    for (let i = 0; primes[i] * primes[i] <= x; ++i) {
        if (x % primes[i] == 0) {
            return false;
        }
    }
    return true;
}

for (let x = 3; primes.length < N; ++x) {
    if (is_prime(x)) {
        primes.push(x);
    }
}

console.log(primes[primes.length - 1]);
