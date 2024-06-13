"""
Author: Yunmu Shu
Semester: Spring 2023
"""
from enum import Enum
from functools import lru_cache
import click
import sys

STACK_LIMIT = 1000
FIB_MAX = 94
sys.setrecursionlimit(100000)


class FibonacciType(Enum):
    DP = 2
    RECURSIVE = 1
    ITERATIVE = 0


# initialize memo
memo = {0: 0, 1: 1}


def fib_recursive(n: int) -> int:
    if n <= 1:
        return n

    return fib_recursive(n - 1) + fib_recursive(n - 2)


@lru_cache(maxsize=None)
def fib_dp(n: int) -> int:
    if n <= 1:
        return n

    if memo[n] != -1:
        return memo[n]

    memo[n] = fib_dp(n - 1) + fib_dp(n - 2)
    return memo[n]


def fib_iterative(n: int) -> int:
    if n <= 1:
        return n

    pre, cur, nxt = 0, 0, 1
    for i in range(2, n + 1):
        pre = cur
        cur = nxt
        nxt = pre + cur
    return nxt


def get_fib_series(n: int, version: int, print_it: bool) -> None:
    entire_row = []

    if version == 0:
        for i in range(n):
            entire_row.append(fib_iterative(i))
    elif version == 1:
        for i in range(n):
            entire_row.append(fib_recursive(i))
    elif version == 2:
        # Arrays.fill(memo, -1)
        for i in range(FIB_MAX):
            memo[i] = -1

        memo[0] = 0
        memo[1] = 1

        for i in range(n):
            entire_row.append(fib_dp(i))

    if print_it:
        print(entire_row)


def get_nth(n: int, fib_type: int) -> None:
    if fib_type == 0:
        print(fib_iterative(n))
    elif fib_type == 1:
        print(fib_recursive(n))
    elif fib_type == 2:
        for i in range(FIB_MAX):
            memo[i] = -1

        memo[0] = 0
        memo[1] = 1

        print(fib_dp(n))


@click.command()
@click.argument("n", type=click.IntRange(min=0, max=50000, clamp=True))
@click.option("--algo", type=click.Choice(['recursive', 'dp', 'iterative'], case_sensitive=False), default='iterative')
@click.option("--print-type", type=click.Choice(['all', 'none', 'Nth'], case_sensitive=False), default='none')
def main(n: int, algo: int, print_type: str):
    """
    Prints the string the row/ generates the row of the fibonacci series.

    Args:
        algo:
        print_type:
        n: the nth row to generate
    """
    print_it = print_type == 'all'
    f = FibonacciType.ITERATIVE
    if algo == 'recursive':
        f = FibonacciType.RECURSIVE
    elif algo == 'dp':
        f = FibonacciType.DP
    fib = get_fib_series(n, f.value, print_it)

    if print_type == 'single':
        # get_fib_series(n, f.value, print_it)
        print(fib)


if __name__ == '__main__':
    main()
