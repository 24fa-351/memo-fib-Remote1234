// By:Eymard Alarcon //

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>
#include <time.h>

typedef unsigned long long *FibFunc(int fibIndex);
typedef __int128 fib_type;

#define MAX_FIB 1000

int can_add(fib_type a, fib_type b) {
    return !(a > 0 && b > 0 && a > (INTMAX_MAX - b));
}

fib_type memo_r[MAX_FIB + 1] = {0};

fib_type memo_i[MAX_FIB + 1] = {0};

fib_type fib_r_core(fib_type n) {
    if (n == 0) return 0;
    if (n == 1) return 0; 
    if (n == 2) return 1;

    if (memo_r[n] != 0) return memo_r[n];

    memo_r[n] = fib_r_core(n - 1) + fib_r_core(n - 2);
    return memo_r[n];
}

fib_type fib_i_core(fib_type n) {
    if (n == 0) return 0;
    if (n == 1) return 0;
    if (n == 2) return 1;

    if (memo_i[n] != 0) return memo_i[n];

    fib_type a = 0, b = 1, fib = 0;
    for (fib_type i = 3; i <= n; i++) {
        if (!can_add(a, b)) {
            printf("Overflow would occur at Fibonacci(%lld)\n", (long long)i);
            return -1;
        }
        fib = a + b;
        a = b;
        b = fib;
        memo_i[i] = fib; 
    }
    return b;
}

fib_type fib_r(fib_type n) {
    return fib_r_core(n);
}

fib_type fib_i(fib_type n) {
    return fib_i_core(n);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <integer> <r|i>\n", argv[0]);
        return 1;
    }

    fib_type N = atoll(argv[1]);
    char method = argv[2][0];

    fib_type result = 0;

    if (method == 'r') {
        result = fib_r(N);
    } else if (method == 'i') {
        result = fib_i(N);
    } else {
        printf("Error: Invalid method '%c'. Use 'r' for recursive or 'i' for iterative.\n", method);
        return 1;
    }

    printf("%lld\n", (long long)result);

    return 0;
}
