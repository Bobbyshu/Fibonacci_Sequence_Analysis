//
// Created by Yunmu shu on 2023/2/26.
//
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

// over 94 will overflow
#define MAX 94
typedef uint64_t ull;

static ull memo[MAX];

/*
 Because all the number in series is positive, when the number comes
 to overflow, it will become negative so b[i] / b[i - 1] will less
 than 1, at that time we can find the maximum number available for
 unsigned long long
 res = 94
 */
void findMax() {
    int i;
    ull a[200];
    a[0] = 0;
    a[1] = 1;
    for (i = 2; a[i] / a[i - 1] >= 1; ++i) {
        a[i + 1] = a[i] + a[i - 1];
    }

    printf("Max input in unsigned long long: %d", i);
}

//recursive version
ull fib_recursive(int n) {
    // base case
    if (n <= 1) {
        return n;
    }

    return fib_recursive(n - 1) + fib_recursive(n - 2);
}

// dp with memo table
ull fib_dp(int n) {
    // base case
    if (n <= 1) {
        return n;
    }

    // check memo
    if (memo[n] != -1) {
        return memo[n];
    }

    // store value
    memo[n] = fib_dp(n - 1) + fib_dp(n - 2);
    return memo[n];
}

// dp with iterative
ull fib_iterative(int n) {
    if (n <= 1) {
        return n;
    }
    // pre for dp[i - 1] cur for dp[i] next for dp[i + 1]
    int pre = 0, cur = 0, next = 1;
    for (int i = 2; i <= n; ++i) {
        pre = cur;
        cur = next;
        next = pre + cur;
    }
    return next;
}

// get n fib numbers
void getFibSeries(int n, int type, bool print) {
    ull entire_row[n];

    if (type == 0) {
        for (int i = 0; i < n; i++) {
            entire_row[i] = fib_iterative(i);
        }
    } else if (type == 1) {
        for (int i = 0; i < n; i++) {
            entire_row[i] = fib_recursive(i);
        }
    } else if (type == 2) {
        // Arrays.fill(memo, -1)
        for (int i = 0; i < MAX; i++) {
            memo[i] = -1;
        }

        // initialize
        memo[0] = 0;
        memo[1] = 1;

        for (int i = 0; i < n; i++) {
            entire_row[i] = fib_dp(i);
        }
    }

    if (print) {
        for (int i = 0; i < n; i++) {
            printf("%llu ", entire_row[i]);
        }
        printf("\n");
    }
}

// print Nth fib number
void getNth(int n, int type) {
    if (type == 0) {
        printf("%llu\n", fib_iterative(n));
    } else if (type == 1) {
        printf("%llu\n", fib_recursive(n));
    } else if (type == 2) {
        for (int i = 0; i < MAX; i++) {
            memo[i] = -1;
        }

        memo[0] = 0;
        memo[1] = 1;

        printf("%llu\n", fib_dp(n));
    }
}

void help() {
    printf("./fibonacci.out N [Type] [Print Level]\n");
    printf("\tN is Nth value of the Fibonacci Series, required.\n");
    printf("\t[Type] is either 0 for iterative version, defaults to 0, 1 for recursive version, 2 for dynamic programming version.\n");
    printf("\t[Print Level] is 0 for no print/speed compare only, 1 for print Nth number, 2 for print entire row, defaults to 0.\n");

}

int main(int argc, char *argv[]) {

    if (argc < 2) {
        printf("at least two arguments needed!\n");
        help();
        return 1;
    }

    const int n = atoi(argv[1]);
    int type = 0;
    int print = 0;
    if (argc > 2) {
        type = atoi(argv[2]);
    }
    if (argc > 3) {
        print = atoi(argv[3]);
    }

    bool print_it = false;
    if (print > 1) {
        print_it = true;
    }

    getFibSeries(n, type, print_it);
    if (print == 1) {
        getNth(n - 1, type);
    }


    return 0;
}