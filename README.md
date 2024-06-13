# Report on Analysis of Fibonacci  Series
* **Author**: Yunmu Shu
* **Languages Used**: c, python

## Overview
This report focuses on the speed differences between implementations of Fibonacci Series. Fibonacci Series describe seies that each number is the sum of the two preceding ones. It can be presented mathematically as:

$$ F(0) = 0, F(1) = 1 $$   
$$ F(n) = F(n - 1) + F(n - 2), for (n > 1)$$

A typical series, to N = 5 would look like the following:
```text
0
0 + 1
0 + (0 + 1)
(0 + 1) + (0 + 0 + 1)
(0 + 0 + 1) + (0 + 1 + 0 + 0 + 1)
(0 + 1 + 0 + 0 + 1) + (0 + 0 + 1 + 0 + 1 + 0 + 0 + 1)
```

Fibonacci Series may be implemented in a variety of methods in code, each of which is showed below in Big O number in this analysis.
| Version |  Big O | Space Used | 
| :-- | :-- |  :-- |
| Recursive | $O(2^n)$  | $O(n)$ or $O(1)$(if ignore system stack)|
| Memorization | $O(n)$  | $O(n)$ |
| Dynamic Programming(iterative) | $O(n)$ | $O(1)$ |
 
### Recursive version:
Based on the definition of Fibonacci Series, we can write pseudo codes and draw the recursion tree for the calculating process:
```text 
fib(n)
  if n == 1 or n == 0 return n
  return fib(n - 1) + fib(n - 2)
```
I put the analysis of time complexity in Language analysis both for C and Python. You can check them in Language analysis module.
Here's the brief analysis for time complexity, recursive has O(2^n) time complexity because we can draw the recursive tree and we found that the amount of tree node is exponential and it should traverse every node, the space complexity is O(N) because system will use stack repeatedly for each layer of tree. For dynamic programming version, because we use memory table to store computed value, so we can decrease the time complexity to O(N), we just need to traverse each value once and the path from tree to list. For space complexity of dynamic programming, it still has O(N) complexity becuase it need to store each value. Finally, for iterative version, we have O(N) time complexity becuase we use the mechanism of dynamic programming and we use O(1) space complexity(just 3 constant) to register the computed value and we realize the optimization.

## Empirical Data & Discussion 
For all empirical results, I wirte a code to explore when will the unsigned long long will overflow. The mechanism of the code is that in Fibnacci Series, the next number will always bigger than first number(assume no negative number in series). So, we set the requirement of loop and print i when loop finish.
```text 
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
```
We can generate that unsigned long long can only been used for n == 94. Over 94, unsigned long long will become 0 and we will quit loop. So, under this data, we can make the csv and test the speed of recursive method.
### Recursive Versions
![C_Recursive]  
The C recursive version start becoming sharp in very early period(>40) which can show that it's in exponential time complexity.
![P_Recursive]  
For Python recursive version, it became sharp earlier than C because Python is an interpreted language, it first gets compiled into byte code. This byte code is then interpreted and executed by the Python Virtual Machine(PVM). This compilation and execution are what make Python slower than C/C++. But this graph can also show that recursive version in exponential time complexity.

### Iterative and Dynamic Programming Versions
![C_DPandIT]  
From the graph, we can see that this two method doesn't have too much difference in speed because they all in linear time complexity. However, due to the limit of number(< 94), the existing instability should be considered by us.
![P_DPandIT]  
From python, it shows the same conclusion of C. However, we can find that in python, dynamic programming(recursive with memo table) is slower than iterative. It's understandable because iterative don't need to assess number in array, it just use 3 constant.

The similarity of speed is that they are all small when n is small and they increase in different speed based on the algorithm we used. The difference is decided on implemented algorithm.

Although I didn't test large number, but I think we can generate the conclusion from current data. It's obvious to find that dynamic programming and iterative are faster than recursive. Besides, iterative is slightly better than dynamic programming in speed and it has constant space complexity.

## Language Analysis
The code writing can be found in the following files:
* [fibonacci.c]  -- implementation of functions in c
* [fibonacci.py] -- implementation of function in python
* [test_runner.py] -- run script to help with tests and keep timings

I implemented fibonacci series in two language python and c. Actually, I think they also have similarity in some places. So, the mechanism of the programming is same. For this analysis, I selected Python for my second language. The reason for this selection, other than it is a well known language, is that it has builtin functions to assist with dynamic programming knowing as and in the builtin functools library. This allowed to experiment with the builtin tools, while also writing in a language designed for quick development and experimentation lru_cache

### Language 1: C
For C Language, the advantage of using it is that it's faster than python. However, it also has the disadvantage like long long overflow and has longer code compared to Python.  
I have solved this problem in leetcode few months ago and I solved it in recursive version because I think that's most code-efficient way to finish it. However, when I start searching about fibonacci series in google. I found that recursion is not so efficient in time complexity. For example, we can draw the recursion tree of Fib(10):
![Recursive Tree] 
From the recursion tree we can see that the amount of tree nodes is in 2^n level.So, it's a quite time-consuming algorithm. Although it has less code, recursion calculates some numbers repeatly. So, I decided to use dynamic programming with memorization to optimize this solution.
First, we need to generate a n-size memo table filled with -1:
```text 
ull memo[n + 1]
for (int i = 0; i <= n; i++) {
  fib_table[i] = -1;
}
```
Then, instead of returning value directly, we store the value into memo table first, and then we return the memo table value.
```text 
ull fib_dp(int n) {
    if (n <= 1) {
        return n;
    }

    if (memo[n] != -1) {
        return memo[n];
    }

    memo[n] = fib_dp(n - 1) + fib_dp(n - 2);
    return memo[n];
}
```
Because we use -1 to sign that we haven't go through this path. We can return memo[i] directly if memo[i] != -1 which means that we have passed this road. In this way, we can set a memory table to store the val of tree node. So, next time when we need to calculate any nodes that has been calculated before, we can use the value that stored in table to realize O(1) time complexity in each step and the total complexity will be optimized to O(n).we can easily decrease those duplicate steps and let the tree become a linkedlist and only traverse each element once. Here's the new path for traversing:
![Memorization]
For iterative, I solve it in python first. So, I will explain it in part of python. Here's the C code:
```text 
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
```

### Language 2: Python
For the python, the advantage of using it is that after I read the code of instruction and learned about how to use enum and click in python to optimize my code. Click library cna handle program arguments and using python can make me write less utility code. However, it's slower than C because Python should be interpreted first before executed by computer.  
From the recursion with memory table, we can find that it's a way that from up to bottom and it use O(n) space complexity in whole process. However, during the each time we traverse, we only need former 2 element to calculate the third element. So, we try to generate the series from bottom to top and condese the memory table into 3 numbers, previous, current and next. 
Python code:
```text 
def fib(n):
  if n <= 1:
    return n
  
  pre, cur, nxt = 0, 0, 1
  for i in range(2, n + 1):
      pre = cur
      cur = nxt
      nxt = pre + cur

  return nxt
```
In this way, we can decrease the space complexity from O(n) to O(1) because we only use 3 constant to simulate the process.

For recursive and memorization method, we can generate code based on C language:
```text 
def fib_recursive(n: int) -> int:
    if n <= 1:
        return n

    return fib_recursive(n - 1) + fib_recursive(n - 2)


# initialize memo
memo = memo = [-1] * FIB_MAX


@lru_cache(maxsize=None)
def fib_dp(n: int) -> int:
    if n <= 1:
        return n

    if memo[n] != -1:
        return memo[n]

    memo[n] = fib_dp(n - 1) + fib_dp(n - 2)
    return memo[n]
```

### Comparison and Discussion Between Experiences
Python certainly runs slower than C, because iterative programming always outperforms dynamic programming even when their respective Big O are the same. But, I think there are may be other improvements to the recursive version that I didn't know which may improve the efficiency. Making such modifications in the iterative version would have been significantly more difficult. The iterative code was also more difficult to develop, and compared to earlier versions, it took me longer to think and visualization the whole process. I mean the shorter the code, the more difficult for people to read it and understand the meaning of them.  
However, they also have same mechanism to implement so I can easily translate C to Python. I think it's because the mind of programming can make me both think in C and Python. Finally, I want to show that we can still optimize the time complexity in using Squaring Exponentiality. Using linear algebra, we can generate such formula:
![Square]  
By calculating M^N, we can generate outcome. Besides, we can use Binary Exponentiation to get the result in O(logN) time comlexity. Because I use java in solving algorithm problem, I will supply java version for this optimization.
```text
// generally we use 1e9 + 7 as module 
int mod = (int) 1e9 + 7
long quickPow(long a, long b) {
    long res = 1;
    while (b > 0) {
        // if pow is odd
        if ((b & 1) == 1) {
            res = (res % mod * a % mod) % mod;
        }
        // even can be divided
        a = (a * a) % mod;
        b >>= 1;
    }
    return res;
}
```



## Conclusions / Reflection
In conclusion, besides the slowest version recursive, the iterative solution is fastest during three ways. I think that's because it don't need to assess value in array. Although dynamic programming with memory table and iterative have same time complexity, they have slightly difference in realizing. Dynamic programming use array to store the value that has been computed, while iterative just use 3 constant to register whole process which has the rolling influence during whole process. Besides, something the iterative version would not allow is precaching the data, whereas the dynamic programming would adapt nicely if the program kept caches of previous runs and leaded those runs as needed.

During the research of fibonacci series, I really learn a lot. I solved this problem in few months ago in leetcode. However, I even didn't know that integer will overflow at that time. So, even after finishing this question, I still use a lot of time to learn about their mechanism in this research. I should have explored more of the squaring exponential and Math formula to optimize the time complexity, but in effort to get out this assignment in time, I ended up not fully exploring those solutions. The most meaningful thing I receive from this time homework is that I know a way to improve current programming structure. From the original recursive with exponential time complexity and linear space complexity, I optimize the program to linear time complexity and constant space complexity. I think that's the magic of algorithm and I get the sense of achievement after optimizing the fibonacci series program.



## References

1. Wikipedia, "https://en.wikipedia.org/wiki/Fibonacci_number"
2. GeeksforGeeks, "https://www.geeksforgeeks.org/c-program-for-fibonacci-numbers/"
3. Binary Exponentiation, https://cp-algorithms.com/algebra/binary-exp.html

<!-- auto references -->
[fibonacci.c]: fibonacci.c
[fibonacci.py]: fibonacci.py
[test_runner.py]: test_runner.py
[Recursive Tree]: RecursionTree.png
[Memorization]: memorization.png
[C_Recursive]: C_Recursive.png
[C_Iterative]: C_Iterative.png
[C_DP]: C_DP.png
[C_DPandIT]: C_DPandIT.png
[P_Recursive]: P_Recursive.png
[P_Iterative]: P_Iterative.png
[P_DP]: P_DP.png
[P_DPandIT]: P_DPandIT.png
[Square]: Square.png
