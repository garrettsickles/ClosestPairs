# ClosestPairs
Various methods of solving the [closest pairs problem](http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1186) for UVA Online Judge.

The optimal minimal runtimes are as follows:

Algorithm         | Runtime (sec)
----------------- | -------------
Heuristic (LR)    | 0.069
Divide & Conquer  | 0.074

## Method 1: Divide and Conquer
The first approach to solving the  is a divide and conquer approach. This approach achieves a time complexity of O(nlog(n)) by using basic computational geometry to rule out many of the possibilities. This approach is implemented in *working.cpp*.

### Specifications
Compiler:  C++ 4.8.2 - GNU C++ Compiler with options: -lm -lcrypt -O2 -pipe -DONLINE_JUDGE

## Method 2: L-R Heuristic
The second approach to solving the closest pair problem is a left to right heuristic where we compute the distance between the two left most points and proceed right, recalculating is the x distance is less than the closest previous distance. This approach achieves a time complexity of O(n<sup>2</sup>). This approach is implemented in *heuristic.c*.

### Specifications
Compiler: ANSI C 4.8.2 - GNU C Compiler with options: -lm -lcrypt -O2 -pipe -ansi -DONLINE_JUDGE
